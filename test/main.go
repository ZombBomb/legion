package main

import (
	"bufio"
	"bytes"
	"fmt"
	"io"
	"os"
	"strings"
)

func check(e error) {
	if e != nil {
		panic(e)
	}
}

func reader(writes chan<- string) {
	reader := bufio.NewReader(os.Stdin)

	for {
		line, err := reader.ReadString('\n')

		if err != nil {
			// You may check here if err == io.EOF
			fmt.Println(err)
			break
		}
		writes <- line
	}
}

func commandManager(writes <-chan string) {
	for {
		select {
		case command := <-writes:
			if commandsList[strings.TrimSuffix(command, "\r\n")] != nil {
				go commandsList[strings.TrimSuffix(command, "\r\n")]()
			} else {
				fmt.Println("Unknown command: ", command)
			}
		}

	}

}

//=============================================================================
type ProcFunc func()

func SayHello() {
	fmt.Printf("Hello!\n")
}

func closeProgramm() {
	fmt.Println("Programm Closed")
	os.Exit(0)
}

func readDataFrom() { //address string) {
	//TODO: check address

	address := "tmp.txt"
	f, err := os.Open(address)
	check(err)
	defer f.Close()
	buf := bytes.NewBuffer(nil)
	io.Copy(buf, f)
	fmt.Print(buf)
}

var commandsList = map[string]ProcFunc{
	"Hello": SayHello,
	"Close": closeProgramm,
	"Read":  readDataFrom,
}

//=============================================================================

func main() {

	writes := make(chan string)
	go reader(writes)
	go commandManager(writes)
	for {
	}
}
