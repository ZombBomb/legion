package main

import (
	"./progectsEditor"
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
			commandName, commandArgs := splitCommand(command)

			if commandsList[commandName] != nil { //have artefacts here: null string, command without args
				go commandsList[commandName](commandArgs...)
			} else {
				fmt.Println("Unknown command: ", command)
			}
		}
	}

}

func splitCommand(commandString string) (string, []string) {
	splitRes := strings.Split(strings.TrimSuffix(commandString, "\r\n"), " ")
	return splitRes[0], splitRes[1:]
}

//=============================================================================
type ProcFunc func(args ...string) bool

func SayHello(names ...string) bool {
	for _, name := range names {
		fmt.Println("Hello, ", name)
	}
	return true
}

func closeProgramm(args ...string) bool {
	fmt.Println("Programm Closed")
	os.Exit(0)
	return true
}

func readDataFrom(address ...string) bool {
	//TODO: check address

	f, err := os.Open(address[0])
	check(err)
	defer f.Close()
	buf := bytes.NewBuffer(nil)
	io.Copy(buf, f)
	fmt.Print(buf)
	return true
}

var commandsList = map[string]ProcFunc{
	"Hello":     SayHello,
	"Close":     closeProgramm,
	"Read":      readDataFrom,
	"OpenTrunc": progectsEditor.OpenTrunc,
}

//=============================================================================

func main() {

	writes := make(chan string)
	go reader(writes)
	go commandManager(writes)
	for {
	}
}
