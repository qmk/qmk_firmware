// Package for taking a mapping of words to keys and outputing a
// combo engine commpatible def

package main

import (
	"io/ioutil"
	"fmt"
	"encoding/json"
	"os"
	"sort"
	"strings"
	"hash/crc64"
	//"encoding/base64"
)

func main() {
	// Show Usage
	if len(os.Args) < 3 {
		fmt.Println("Usage: ./keymap-gen inputfile outfile")
		fmt.Println("Outputs dict in current dir")
		return
	}

	// Read the source
	data, err := ioutil.ReadFile(os.Args[1])
	if err != nil {
		panic(err)
	}

	// Unbundle Data
	var FullDict map[string]string
	var output   []string
	json.Unmarshal(data, &FullDict)

	// Loop over entries and store
	for i,v := range FullDict {
		// This checks for colllisions, Generates hash
		hash := crc64.Checksum([]byte(v), crc64.MakeTable(crc64.ECMA))
		hashStr := fmt.Sprintf("txt_%x", hash)[:10]

		// Format keys into combo
		var keys string
		for _, k := range(v) {
			keys += fmt.Sprintf("KC_%v, ", string(k))

		}
		keys = keys[:len(keys)-2]

		// Append to output
		spacer := strings.Repeat(" ", 15-len(i))
		output = append(output, fmt.Sprintf("SUBS(%v, %v\"%v\", %v)\n", hashStr, spacer, i, keys))
	}


	sort.Slice(output, func (i,j int) bool {
		return strings.Count(output[i], " ") > strings.Count(output[j], " ")
	})
	ioutil.WriteFile(os.Args[2], []byte(strings.Join(output, "")), 0555)
}
