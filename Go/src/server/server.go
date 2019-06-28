package server

import (
    "fmt"
    "net"
    "io/ioutil"
    "log"
    "os"
    ospath "path"
    "time"
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

    log.Printf("Serving file %s of size %d B\n", path, len(fileStream))
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

func ServeDir(path string, port int) {

    d, err := os.Open(path)

    if (err != nil) {
        log.Println(err)
        return
    }

    stats, err := d.Readdir(-1)
    d.Close()

    if (err != nil) {
        log.Println(err)
        return
    }

    filenames := make([]string, len(stats))
    filenames = filenames[:0]

    for i := 0; i < len(stats); i++ {
        if (!stats[i].IsDir()) {
            filenames = append(filenames, stats[i].Name())
        }
    }

    for i := 0; i < len(filenames); i++ {
        file := ospath.Join(path, filenames[i])
        p := port + i
        log.Printf("Serving file %s on port %d", file, p)
        go ServeFile(file, p)
    }

    log.Println("Waiting...")
    for {
        time.Sleep(1 * time.Second)
    }
}
