package main

import (
    "flag"
    "client"
    "log"
    "fmt"
    "time"
    "os"
)

func main()  {

    var server, output_file string
    var port, rep, files int

    flag.StringVar(&server, "host", "localhost", "Dirección del servidor")
    flag.StringVar(&output_file, "output", "result.csv", "Nombre del archivo donde escribir el resultado")
    flag.IntVar(&port, "port", 9000, "Puerto del servidor")
    flag.IntVar(&rep, "rep", 100, "Cantidad de repticiones")
    flag.IntVar(&files, "files", 1, "Cantidad de pruebas/archivos")

    flag.Parse()

    file, err := os.Create(output_file)
    if err != nil {
        log.Fatal("Fatal error while opening file", err)
    }
    defer file.Close()

    file.WriteString("Size (B), Iter, Time (ns)\n")

    for n := 0; n < files; n++ {

        log.Printf("Iniciando prueba %d\n", n)
        var size int
        var time time.Duration


        status := 20
        for i := 0; i < rep; i++ {
            size, time = client.GetFile(server, port+n)
            line := fmt.Sprintf("%d,%d,%d\n", size, i+1, time)
            file.WriteString(line)

            if i % status == 0 {
                fmt.Println("...repeticion", i)
            }
        }
        log.Println("Fin, resultados escritos en", output_file)
    }
    file.WriteString("\n")
}
