package client

import (
    "fmt"
    "net"
    "bufio"
    "io"
)

func resolveAddr(host string, port int) *net.TCPAddr {
    addr := fmt.Sprintf("%s:%d", host, port)
    tcpAddr, _ := net.ResolveTCPAddr("tcp4", addr)

    fmt.Printf("Address: %s\n", tcpAddr)

    return tcpAddr
}

func OpenBuffered(addr *net.TCPAddr) *bufio.ReadWriter {
    conn, err := net.DialTCP("tcp4", nil, addr)

    if err != nil {
        fmt.Println("Error en la conexión", err)
        return nil
    }

    // fmt.Println("Conexión establecida con", conn.LocalAddr())
    return bufio.NewReadWriter(bufio.NewReader(conn), bufio.NewWriter(conn))
}

func Open(addr *net.TCPAddr) *net.TCPConn {
    conn, err := net.DialTCP("tcp4", nil, addr)

    if err != nil {
        fmt.Println("Error en la conexión", err)
        return nil
    }

    return conn
}

func ReadFile(conn *net.TCPConn) []byte {

    BUF_SIZE := 256
    var buffer_in, file_buff []byte
    buffer_in = make([]byte, BUF_SIZE)
    file_buff = make([]byte, 0, BUF_SIZE)
    var size int
    var err error

    err = nil
    //size, err = buffered_rw.WriteString("GET\n")
    //size, err = buffered_rw.ReadBytes()

    for err == nil {
        size, err = conn.Read(buffer_in)
        if err == io.EOF {
            fmt.Println("Fin del archivo")
            break
        } else if err != nil {
            fmt.Println("No se pudo leer", err)
            break
        }
        // var texto string = string(buffer)
        fmt.Printf("Recibimos %d bytes\n", size)
        fmt.Println(string(buffer_in[:size]))
        file_buff = append(file_buff, buffer_in[:size]...)
    }

    return file_buff
}

func GetFile(host string, port int) {

    addr := resolveAddr(host, port)

    conn := Open(addr)
    defer conn.Close()

    file := ReadFile(conn)

    fmt.Println("Conexión finalizada")
    fmt.Println(string(file))

    return
}
