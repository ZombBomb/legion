package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

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

			switch strings.TrimSuffix(command, "\r\n") {
			case "Close":
				go closeProgramm()
			default:
				fmt.Println("Unknown command: ", command)
			}
		}

	}

}

func closeProgramm() {
	fmt.Println("Programm Closed")
	os.Exit(0)
}
func main() {

	writes := make(chan string)
	go reader(writes)
	go commandManager(writes)
	for {
	}
}
