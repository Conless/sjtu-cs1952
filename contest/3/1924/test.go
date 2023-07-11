package main

import "fmt"
import "time"

func main() {
	var M uint64 = 11653310467824836911
	var m uint64 = 341369454837
	check := func(min, max uint64) {
		for i := min; i < max; i++ {
			if i%100000000 == 0 {
				fmt.Println(i)
			}
			if M%i == 0 {
				fmt.Println(i, M/i)
				return
			}
		}
	}
	var i uint64
	for i = 0; i < 10; i++ {
		var min uint64 = m/10*i - 1
		var max uint64 = m/10*(i+1) + 1
		if min < 2 {
			min = 2
		}
		go check(min, max)
	}
	go check(2, m)
	time.Sleep(time.Duration(1000) * time.Second)
}
