package main

import (
    "flag"
    "server"
    "log"
)

func main()  {

    log.Println("hola mundo")
    var filename string
    var port int

    flag.StringVar(&filename, "filename", "test.txt", "Nombre del archivo que va a pedir al servidor")
    flag.IntVar(&port, "port", 9000, "Puerto del servidor")

    flag.Parse()

    server.ServeFile(filename, port)

}
