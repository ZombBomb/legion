package main

import (
	//"fmt"
	"golang.org/x/net/websocket"
	"io"
	"log"
	"net/http"
	"os"
	"strconv"
	"strings"
)

const MAXBACKLOG = 100

type (
	Msg struct {
		clientKey string
		text      string
	}

	NewClientEvent struct {
		clientKey string
		msgChan   chan *Msg
	}
)

var (
	dirPath           string
	clientRequests    = make(chan *NewClientEvent, 100)
	clientDisconnects = make(chan string, 1000)
	messages          = make(chan *Msg, 100)
)

func IndexPage(w http.ResponseWriter, req *http.Request, filename string) {
	fp, err := os.Open(dirPath + "/" + filename)
	if err != nil {
		log.Println("Open file error", err.Error())
		return
	}

	defer fp.Close()
	_, err = io.Copy(w, fp)
	if err != nil {
		log.Println("Could not send file contents", err.Error())
		return
	}
}

func ChatServer(ws *websocket.Conn) {
	lenBuf := make([]byte, 5)

	msgChan := make(chan *Msg, 100)
	clientKey := ws.RemoteAddr().String()
	clientRequests <- &NewClientEvent{clientKey, msgChan}
	defer func() { clientDisconnects <- clientKey }()

	go func() {
		for msg := range msgChan {
			ws.Write([]byte(msg.text))
		}
	}()
	for {
		_, err := ws.Read(lenBuf)
		if err != nil {
			log.Println("Error: ", err.Error())
			return
		}

		length, _ := strconv.Atoi(strings.TrimSpace(string(lenBuf)))
		if length > 65536 {
			log.Println("Error: too big length: ", length)
			return
		}

		if length <= 0 {
			log.Println("Empty length")
			return
		}

		buf := make([]byte, length)
		_, err = ws.Read(buf)

		if err != nil {
			log.Println("Could not read", length)
			return
		}

		messages <- &Msg{clientKey, string(buf)}
	}
}

func router() {
	clients := make(map[string]chan *Msg)

	for {
		select {
		case req := <-clientRequests:
			clients[req.clientKey] = req.msgChan
			log.Println("Websocket connected: ", req.clientKey)
		case clientKey := <-clientDisconnects:
			close(clients[clientKey])
			delete(clients, clientKey)
			log.Println("Websocket disconnected: ", clientKey)
		case msg := <-messages:
			for _, msgChan := range clients {
				if len(msgChan) < cap(msgChan) {
					msgChan <- msg
				}
			}
		}
	}
}
func main() {
	if len(os.Args) < 2 {
		log.Fatal("no args")
	}
	dirPath = os.Args[1]
	log.Println(dirPath)

	go router()

	http.HandleFunc("/", func(w http.ResponseWriter, req *http.Request) {
		IndexPage(w, req, "index.html")
	})
	http.HandleFunc("/index.js", func(w http.ResponseWriter, req *http.Request) {
		IndexPage(w, req, "index.js")
	})
	http.Handle("/ws", websocket.Handler(ChatServer))

	err := http.ListenAndServe(":8080", nil)
	if err != nil {
		log.Fatal("ListenhAndServe", err)
	}
}
