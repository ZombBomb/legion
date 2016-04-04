package progectsEditor

import (
	"fmt"
	"os"
)

var truncPath = ""

func OpenTrunc(inputTruncPath ...string) bool {
	//TODO: check address

	res := false
	if inputTruncPath[0] != "" && isPathExist(inputTruncPath[0]) {
		truncPath = inputTruncPath[0]
		res = true
	} else if inputTruncPath[0] == "" {
		if isPathExist(truncPath) {
			res = true
		} else {
			fmt.Println("Incorrect trunc path: ", truncPath)
		}
	} else if !isPathExist(inputTruncPath[0]) {
		fmt.Println("Path not found: ", inputTruncPath[0])
	}

	return res
}

func isPathExist(path string) bool {
	if _, err := os.Stat(path); err == nil {
		return true
	} else {
		return false
	}
}
