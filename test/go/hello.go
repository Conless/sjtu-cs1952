package main

import (
	"fmt"
	"math/cmplx"
	"math/rand"
	"runtime"
	"sort"
	"sync"
	"time"
)

const (
	a = 1 << 10
	b = 1<<10 + 1
)

func JudgeOS() {
	switch os := runtime.GOOS; os {
	case "darwin":
		fmt.Println("OS X")
	case "linux":
		fmt.Println("Linux")
	default:
		break
	}
	println(runtime.GOOS)
}

func VariableTest() {
	var ToBe bool = false
	var MaxInt uint64 = 1<<64 - 1
	var z complex128 = cmplx.Sqrt(-5 + 12i)
	const i = 1 << 100
	const j = 1<<100 - 1
	if j < i {
		println(j - i)
	}

	var k = 0
	for k = 0; ; k++ {
		k++
		break
	}

	fmt.Printf("Type: %T Value: %v\n", ToBe, ToBe)
	fmt.Printf("Type: %T Value: %v\n", MaxInt, MaxInt)
	fmt.Printf("Type: %T Value: %v\n", z, z)

}

func DeferTest() {
	fmt.Println("Defer test starts:")
	for i := 0; i < 10; i++ {
		defer fmt.Printf("%d ", i)
	}
}

func ArgumentTest(t *int) {
	*t++
}

// func VertexTest(a *Vertex) {
// 	a.X++
// 	a.Y++
// }

func SqrtTest(a float64) float64 {
	var l = 0.0
	var r = 2.0
	var small = 1.0 >> 2
	fmt.Println(small)
	for r-l > 0.00001 {
		var mid = (l + r) / 2
		if mid*mid < a {
			l = mid + 0.00001
		} else {
			r = mid - 0.00001
		}
	}
	return r
}

func RangeTest() {
	var a = make([]int, 10)
	var b = a[:5]

	if a == nil {
		fmt.Println("nil")
	}
	if b == nil {
		fmt.Println("nil")
	}

}

func SliceTest() {
	a := [5]int{1, 2, 3, 4, 5}
	slice := a[:]
	slice = append(slice, 1)
	fmt.Println(slice)
	fmt.Println(a)
}

func Pic(dx, dy int) [][]uint8 {
	arr := make([][]uint8, dy)
	for i := range arr {
		arr[i] = make([]uint8, dx)
		for j := range arr[i] {
			arr[i][j] = uint8(rand.Int())
		}
	}
	return arr
}

type Vertex struct {
	first, second float64
}

func MapTest() {

	var m = map[string]Vertex{
		"Bell Labs": Vertex{
			40.68433, -74.39967,
		},
		"Google": Vertex{
			37.42202, -122.08408,
		},
	}
	for i := range m {
		fmt.Println(i, m[i])
	}
	fmt.Println(m)
	value, exist := m["a"]
	fmt.Println(value, exist)
}

func FuncFuncTest(y int) func(int) int {
	return func(x int) int { return x + y }
}

func (v *Vertex) MethodTest() {
	v.first++
}

type Interface interface {
	a() string
}

func (v *Vertex) a() string {
	// var i int = 0
	var s string
	return s
}

func InterfaceTest() {
	var i Interface = &Vertex{1, 2}
	i.a()
	fmt.Println(i.(*Vertex).first)
	var str fmt.Stringer
	fmt.Println(str.String())
}

func sum(s []int, c chan int) {
	sum := 0
	for _, v := range s {
		sum += v
	}
	c <- sum // 将和送入 c
}

func GoRountineTest() {
	s := []int{7, 2, 8, -9, 4, 0}

	c := make(chan int)
	go sum(s[:len(s)/2], c)
	go sum(s[len(s)/2:], c)
	x, y := <-c, <-c // 从 c 中接收

	fmt.Println(x, y, x+y)
}

func fibonacci(c, quit chan int) {
	x, y := 0, 1
	for {
		select {
		case c <- x:
			x, y = y, x+y
		case <-quit:
			fmt.Println("quit")
			return
		}
	}
}

func GoRountineTest1() {
	c := make(chan int)
	quit := make(chan int)

	go func() {
		for i := 0; i < 10; i++ {
			fmt.Println(<-c)
		}
		quit <- 0
	}()
	go fibonacci(c, quit)
	time.Sleep(1 * time.Second)
}

func Add10000(x *int, ch chan int) {
	for j := 0; j < 10000; j++ {
		*x++
	}
	time.Sleep(1 * time.Second)
	ch <- 0
}

func GoRountineTest2() {
	i := 0
	ch := make(chan int)
	for j := 0; j < 10; j++ {
		go Add10000(&i, ch)
	}
	// for j := 0; j < 10; j++ {
	<-ch
	// }
	fmt.Println(i)
}

type Tree struct {
	Left  *Tree
	Value int
	Right *Tree
}

func New(k int) *Tree {
	var t *Tree
	for _, v := range rand.Perm(10) {
		t = insert(t, (1+v)*k)
	}
	return t
}

func insert(t *Tree, v int) *Tree {
	if t == nil {
		return &Tree{nil, v, nil}
	}
	if v < t.Value {
		t.Left = insert(t.Left, v)
	} else {
		t.Right = insert(t.Right, v)
	}
	return t
}

func Walk(t *Tree, ch chan int) {
	if t == nil {
		return
	}
	go Walk(t.Left, ch)
	ch <- t.Value
	go Walk(t.Right, ch)
}

func Same(t1, t2 *Tree) bool {
	s1 := []int{}
	s2 := []int{}
	ch := make(chan int, 10)
	Walk(t1, ch)
	for i := 0; i < 10; i++ {
		s1 = append(s1, <-ch)
	}
	sort.Slice(s1, func(i, j int) bool { return s1[i] < s1[j] })
	fmt.Println(s1)
	Walk(t2, ch)
	for i := 0; i < 10; i++ {
		s2 = append(s2, <-ch)
	}
	sort.Slice(s2, func(i, j int) bool { return s2[i] < s2[j] })
	fmt.Println(s2)
	for i := 0; i < 10; i++ {
		if s1[i] != s2[i] {
			return false
		}
	}
	return true
}

func GoRountineTest3() {
	t1 := New(1)
	t2 := New(2)
	Same(t1, t2)
}

type Fetcher interface {
	// Fetch 返回 URL 的 body 内容，并且将在这个页面上找到的 URL 放到一个 slice 中。
	Fetch(url string) (body string, urls []string, err error)
}

type SafeMap struct {
	m   map[string]int
	mux sync.Mutex
}

// Crawl 使用 fetcher 从某个 URL 开始递归的爬取页面，直到达到最大深度。
func (m *SafeMap) Crawl(url string, depth int, fetcher Fetcher) {
	// TODO: 并行的抓取 URL。
	// TODO: 不重复抓取页面。
	// 下面并没有实现上面两种情况：
	if depth <= 0 {
		return
	}
	m.mux.Lock()
	m.m[url]++
	m.mux.Unlock()
	body, urls, err := fetcher.Fetch(url)
	if err != nil {
		fmt.Println(err)
		return
	}
	fmt.Printf("found: %s %q\n", url, body)
	for _, u := range urls {
		m.mux.Lock()
		_, ok := m.m[u]
		m.mux.Unlock()
		if !ok {
			go m.Crawl(u, depth-1, fetcher)
		}
	}
}

func FetchTest() {
	tmp := SafeMap{m: make(map[string]int)}
	tmp.Crawl("https://golang.org/", 4, fetcher)
	time.Sleep(1 * time.Second)
}

// fakeFetcher 是返回若干结果的 Fetcher。
type fakeFetcher map[string]*fakeResult

type fakeResult struct {
	body string
	urls []string
}

func (f fakeFetcher) Fetch(url string) (string, []string, error) {
	if res, ok := f[url]; ok {
		return res.body, res.urls, nil
	}
	return "", nil, fmt.Errorf("not found: %s", url)
}

// fetcher 是填充后的 fakeFetcher。
var fetcher = fakeFetcher{
	"https://golang.org/": &fakeResult{
		"The Go Programming Language",
		[]string{
			"https://golang.org/pkg/",
			"https://golang.org/cmd/",
		},
	},
	"https://golang.org/pkg/": &fakeResult{
		"Packages",
		[]string{
			"https://golang.org/",
			"https://golang.org/cmd/",
			"https://golang.org/pkg/fmt/",
			"https://golang.org/pkg/os/",
		},
	},
	"https://golang.org/pkg/fmt/": &fakeResult{
		"Package fmt",
		[]string{
			"https://golang.org/",
			"https://golang.org/pkg/",
		},
	},
	"https://golang.org/pkg/os/": &fakeResult{
		"Package os",
		[]string{
			"https://golang.org/",
			"https://golang.org/pkg/",
		},
	},
}

func main() {
	// fmt.Printf("Hello, World! from %.2f\n", math.Pi)
	// fmt.Printf("Hello, World from 1 + 2 = ")
	// fmt.Println(file1.Test(1, 2))
	// file2.Test()
	// DeferTest()
	// JudgeOS()
	// var value = 0
	// ArgumentTest(&value)
	// fmt.Println(value)
	// fmt.Println(SqrtTest(2))
	// RangeTest()
	// SliceTest()
	// MapTest()
	// fmt.Println(FuncFuncTest(1)(2))
	// var v = Vertex{1, 2}
	// v.MethodTest()
	// fmt.Println(v.first)
	// InterfaceTest()
	// GoRountineTest3()
	FetchTest()
}
