package main

import (
	"fmt"
	"log"
)

// Grammar defines a grammar
type Grammar struct {
	startSymbol  string
	currentIndex int
	indexes      map[string]int
	productions  map[string][][]string
}

// NewGrammar instantiates a new grammar object
func NewGrammar(startSymbol string) *Grammar {
	return &Grammar{
		startSymbol:  startSymbol,
		currentIndex: 1,
		indexes:      make(map[string]int),
		productions:  make(map[string][][]string),
	}
}

// AddProduction modifies the grammar, it can add a production in the Chomsky form.
// symbol -> [symbol, symbol]
func (g *Grammar) AddProduction(symbol string, productions []string) {
	if _, exist := g.productions[symbol]; !exist {
		g.productions[symbol] = make([][]string, 1)
		g.indexes[symbol] = g.currentIndex
		g.currentIndex++
	}

	g.productions[symbol] = append(g.productions[symbol], productions)
}

// IsTerminal returns if a given symbol is terminal.
func (g *Grammar) IsTerminal(symbol string) bool {
	_, exist := g.productions[symbol]
	return !exist
}

// ProducesTerminal tells if a symbol produce a single non terminal
func (g *Grammar) ProducesTerminal(symbol string, terminal string) bool {
	if g.IsTerminal(symbol) {
		log.Print("Symbol does not produce anything", symbol)
		return false
	}

	productions := g.productions[symbol]
	for _, producedSymbols := range productions {
		if len(producedSymbols) == 1 && producedSymbols[0] == terminal {
			return true
		}
	}

	return false
}

// ProducesNonTerminals tells if a symbol produces two non terminal symbols
func (g *Grammar) ProducesNonTerminals(symbol string) bool {
	if g.IsTerminal(symbol) {
		log.Print("Symbol does not produce anything", symbol)
		return false
	}

	productions := g.productions[symbol]
	for _, producedSymbols := range productions {
		if len(producedSymbols) == 2 && !g.IsTerminal(producedSymbols[0]) && !g.IsTerminal(producedSymbols[1]) {
			return true
		}
	}

	return false
}

// CanGenerate runs the CYK algorithm to determine if the grammar can produce the input
func (g *Grammar) CanGenerate(input []string) bool {
	// Initialization
	n := len(input) - 1
	r := g.currentIndex
	P := make([][][]bool, n+1)
	for i := 1; i <= n; i++ {
		P[i] = make([][]bool, n+1)
		for j := 1; j <= n; j++ {
			P[i][j] = make([]bool, r+1)
		}
	}

	for s := 1; s <= n; s++ {
		for symbol := range g.productions {
			v := g.indexes[symbol]
			P[1][s][v] = g.ProducesTerminal(symbol, input[s])
		}
	}

	for l := 2; l <= n; l++ {
		for s := 1; s <= n-l+1; s++ {
			for p := 1; p <= l-1; p++ {
				for Ra := range g.productions {
					// production Ra -> Rb Rc
					if g.IsTerminal(Ra) {
						continue
					}

					for _, producedSymbols := range g.productions[Ra] {

						if len(producedSymbols) == 2 {
							Rb := producedSymbols[0]
							Rc := producedSymbols[1]

							if !g.IsTerminal(Rb) && !g.IsTerminal(Rc) {
								a := g.indexes[Ra]
								b := g.indexes[Rb]
								c := g.indexes[Rc]

								if P[p][s][b] && P[l-p][s+p][c] {
									P[l][s][a] = true
								}
							}
						}
					}
				}
			}
		}
	}

	return P[n][1][1]
}

func main() {
	grammar := NewGrammar("S")
	grammar.AddProduction("S", []string{"NP", "VP"})
	grammar.AddProduction("VP", []string{"VP", "PP"})
	grammar.AddProduction("VP", []string{"V", "NP"})
	grammar.AddProduction("VP", []string{"eats"})
	grammar.AddProduction("PP", []string{"P", "NP"})
	grammar.AddProduction("NP", []string{"Det", "N"})
	grammar.AddProduction("NP", []string{"she"})
	grammar.AddProduction("V", []string{"eats"})
	grammar.AddProduction("P", []string{"with"})
	grammar.AddProduction("N", []string{"fish"})
	grammar.AddProduction("N", []string{"fork"})
	grammar.AddProduction("Det", []string{"a"})

	var input []string

	input = []string{
		"",
		"she",
		"eats",
		"a",
		"fish",
		"with",
		"a",
		"fork",
	}

	fmt.Println("Input:", input)
	fmt.Println("Can generate:", grammar.CanGenerate(input))

	input = []string{
		"",
		"random",
		"eats",
		"a",
		"word",
		"with",
		"a",
		"fork",
	}

	fmt.Println("Input:", input)
	fmt.Println("Can generate:", grammar.CanGenerate(input))
}
