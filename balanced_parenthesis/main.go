package main

import (
	"fmt"
	"log"

	"github.com/golang-collections/collections/stack"
)

func isBalanced(input string) bool {
	stack := stack.New()

	for _, char := range input {
		if char == '(' {
			stack.Push(char)
		} else if char == ')' {
			if stack.Pop() != '(' {
				return false
			}

		} else {
			log.Fatalf("Unexpected character: %q\n", char)
		}
	}

	return stack.Len() == 0
}

func main() {

	var input string

	input = "()()()"
	fmt.Printf("Input:%s Is balanced: %t\n", input, isBalanced(input))

	input = "((()"
	fmt.Printf("Input:%s Is balanced: %t\n", input, isBalanced(input))

	input = "()))"
	fmt.Printf("Input:%s Is balanced: %t\n", input, isBalanced(input))

	input = "((()()()))"
	fmt.Printf("Input:%s Is balanced: %t\n", input, isBalanced(input))

	input = "("
	fmt.Printf("Input:%s Is balanced: %t\n", input, isBalanced(input))

	input = "((()())())()"
	fmt.Printf("Input:%s Is balanced: %t\n", input, isBalanced(input))
}
