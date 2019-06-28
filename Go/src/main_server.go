package main

import (
    "flag"
    "server"
    "log"
    "os"
)

func main()  {

    // log.SetOutput(os.Stdout)
    log.Println("Server program startup")
    var path string
    var port int
    var file_info os.FileInfo

    flag.StringVar(&path, "path", "test.txt", "Nombre del archivo o directorio con archivos que va a pedir al servidor")
    flag.IntVar(&port, "port", 9000, "Puerto del servidor")

    flag.Parse()

    file_info, err := os.Stat(path)

    if (err != nil) {
        log.Println(err)
        return
    }

    if (file_info.IsDir()) {
        server.ServeDir(path, port)
    } else {
        server.ServeFile(path, port)
    }

}
