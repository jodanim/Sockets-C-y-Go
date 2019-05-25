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

    addr := fmt.Sprintf(":%d", port)
    listener, err := net.Listen("tcp4", addr)

    if err != nil {
        fmt.Println(err)
        log.Fatal("BLA2")
    }


    return listener
}

func handleConection(conn net.Conn, data []byte) {

    defer conn.Close()
    log.Println("Incoming client connection", conn.RemoteAddr())
    bytes_written, err := conn.Write(data)

    if err != nil {
        fmt.Println(err)
    }
    log.Printf("Wrote %d bytes to client\n", bytes_written)

}

func ServeFile(path string, port int)  {

    fileStream := loadFile(path)
    listener := makeListener(port)

    log.Printf("Serving file %s of size %d\n B", path, len(fileStream))
    log.Println("Listening on address", listener.Addr())

    for {

        clientConn, err := listener.Accept()
        if err != nil {
            fmt.Println(err)
            clientConn.Close()
            continue
        }

        go handleConection(clientConn, fileStream)
    }
}
