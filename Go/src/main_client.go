package main

import (
    "flag"
    "client"
    "log"
)

func main()  {

    log.Println("hola mundo")
    var server string
    var port int

    flag.StringVar(&server, "host", "localhost", "Dirección del servidor")
    flag.IntVar(&port, "port", 9000, "Puerto del servidor")

    flag.Parse()


    client.GetFile(server, port)



}
