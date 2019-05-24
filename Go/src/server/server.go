package server

import (
    "fmt"
    "net"
    "io/ioutil"
    "log"
)

func loadFile(path string) []byte {

    contents, err := ioutil.ReadFile(path)

    if err != nil {
        fmt.Println(err)
        log.Fatal("BLA")
    }

    // contentsStr := string(contents)
    // fmt.Println("File contents:\n", contentsStr)

    return contents
}

func makeListener(port int) net.Listener {

    addr := fmt.Sprintf("localhost:%d", port)
    listener, err := net.Listen("tcp4", addr)

    if err != nil {
        fmt.Println(err)
        log.Fatal("BLA2")
    }

    fmt.Println("Listening on address", listener.Addr())

    return listener
}

func handleConection(conn net.Conn, data []byte) {

    fmt.Println("Incoming client connection", conn.RemoteAddr())
    bytes_written, err := conn.Write(data)

    if err != nil {
        fmt.Println(err)
    }
    fmt.Printf("Wrote %d bytes to client\n", bytes_written)

}

func ServeFile(path string, port int)  {

    fileStream := loadFile(path)

    listener := makeListener(port)

    for {

        clientConn, err := listener.Accept()
        if err != nil {
            fmt.Println(err)
            clientConn.Close()
            continue
        }

        handleConection(clientConn, fileStream)
        clientConn.Close()
    }
}
