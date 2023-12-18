package main

import (
	"fmt"
	"math"
	"os"
	"sort"
	"strings"
	"strconv"
)

type FreqMap map[rune]uint8
type HandType uint8

const (
	HighCard HandType = iota
	OnePair
	TwoPair
	ThreeOfAKind
	FullHouse
	FourOfAKind
	FiveOfAKind
)

var CardValMap = make(FreqMap)

type HandWithBid struct {
	hand string
	bid uint16
}

func (h HandWithBid) getCardFreqMap() FreqMap {
	var cardFreqMap = make(FreqMap)

	for _, char := range h.hand {
		_, isPresent := cardFreqMap[char]

		if isPresent {
			cardFreqMap[char]++
		} else {
			cardFreqMap[char] = 1
		}
	}

	return cardFreqMap
}

func (h HandWithBid) getHandType() HandType {
	cardFreqMap := h.getCardFreqMap()
	var highestFreq uint8 = 0
	var secondHighestFreq uint8 = 0

	for _, freq := range cardFreqMap {
		if freq >= highestFreq {
			secondHighestFreq = highestFreq
			highestFreq = freq
		} else if freq > secondHighestFreq {
			secondHighestFreq = freq
		}
	}

	var handType HandType

	switch highestFreq {
		case 1:
			handType = HighCard
		case 2:
			if secondHighestFreq == 2 {
				handType = TwoPair
			} else {
				handType = OnePair
			}
		case 3:
			if secondHighestFreq == 2 {
				handType = FullHouse
			} else {
				handType = ThreeOfAKind
			}
		case 4:
			handType = FourOfAKind
		case 5:
			handType = FiveOfAKind
		default:
			panic("Failed handType or smthn idk.")
	}

	return handType
}

func (h HandWithBid) hash() int {
	sum := 0
	i := 4

	for _, char := range h.hand {
		sum += int(CardValMap[char]) * int(math.Pow(13.0, float64(i)))
		i--
	}

	return sum
}

func parse(data string) []HandWithBid {
	dataSplit := strings.Split(data, "\n")
	var parsedHandWithBids []HandWithBid

	for _, text := range dataSplit {
		s := strings.Split(text, " ")
	
		if len(s) == 1 {
			break
		}
		
		hand, bidString := s[0], s[1]

		if bidString[len(bidString) - 1] == '\r' {
			bidString = bidString[0 : len(bidString) - 1]
		}

		bid, err := strconv.Atoi(bidString)
		
		if err != nil {
			panic(err)
		}

		parsedHandWithBids = append(parsedHandWithBids, HandWithBid{hand, uint16(bid)})
	}

	return parsedHandWithBids
}

func init() {
	cardsString := "23456789TJQKA"

	for n, char := range cardsString {
		CardValMap[char] = uint8(n)
	}
}

func main() {
	if len(os.Args) < 2 {
		panic("No input file.")
	}

	data, err := os.ReadFile(os.Args[1])

	if err != nil {
		panic("Something went wrong with reading.")
	}

	handWithBidLists := parse(string(data))
	sort.Slice(handWithBidLists, func(i, j int) bool {
		firstHand := handWithBidLists[i]
		secondHand := handWithBidLists[j]

		if firstHand.getHandType() < secondHand.getHandType() {
			return true
		} else if firstHand.getHandType() > secondHand.getHandType() {
			return false
		}

		return firstHand.hash() < secondHand.hash()
	})

	var count uint16 = uint16(len(handWithBidLists))
	var sum uint64 = 0
	var i uint16
	for i = 0; i < count ; i++ {
		sum += uint64(handWithBidLists[i].bid) * uint64(i+1)
	}

	fmt.Println("Sum:", sum)
}
