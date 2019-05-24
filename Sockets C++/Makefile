all: Socket.obj FileManager.obj Time.obj Server.obj Client.obj Server Client
all_d: Socket.obj_d FileManager.obj_d Time.obj_d Server.obj_d Client.obj_d Server_d Client_d

Socket.obj: lib/Socket.hpp src/Socket.cpp
	g++ -c src/Socket.cpp -o obj/Socket.obj

Socket.obj_d: lib/Socket.hpp src/Socket.cpp
	g++ -g -c src/Socket.cpp -o obj/debug/Socket.obj

FileManager.obj: lib/FileManager.hpp src/FileManager.cpp
	g++ -c src/FileManager.cpp -o obj/FileManager.obj

FileManager.obj_d: lib/FileManager.hpp src/FileManager.cpp
	g++ -g -c src/FileManager.cpp -o obj/debug/FileManager.obj

Time.obj: lib/Time.hpp src/Time.cpp
	g++ -c src/Time.cpp -o obj/Time.obj

Time.obj_d: lib/Time.hpp src/Time.cpp
	g++ -g -c src/Time.cpp -o obj/debug/Time.obj

###########################################################

Server.obj: src/Server.cpp
	g++ -c src/Server.cpp -o obj/Server.obj

Server.obj_d: src/Server.cpp
	g++ -g -c src/Server.cpp -o obj/debug/Server.obj

Client.obj: src/Client.cpp
	g++ -c src/Client.cpp -o obj/Client.obj

Client.obj_d: src/Client.cpp
	g++ -g -c src/Client.cpp -o obj/debug/Client.obj

Server: Socket.obj Time.obj FileManager.obj Server.obj 
	g++ obj/Server.obj obj/Socket.obj obj/Time.obj obj/FileManager.obj -o bin/Server

Server_d: Socket.obj_d Time.obj_d FileManager.obj_d Server.obj_d 
	g++ -g obj/debug/Server.obj obj/debug/Socket.obj obj/debug/Time.obj obj/debug/FileManager.obj -o bin/debug/Server

Client: Socket.obj Time.obj FileManager.obj Client.obj
	g++ obj/Client.obj obj/Socket.obj obj/Time.obj obj/FileManager.obj -o bin/Client

Client_d: Socket.obj_d Time.obj_d FileManager.obj_d Client.obj_d
	g++ -g obj/debug/Client.obj obj/debug/Socket.obj obj/debug/Time.obj obj/debug/FileManager.obj -o bin/debug/Client

run_server: Server
	.\/bin/Server 20 .txt 1101
	
run_client: Client 
	.\/bin/Client 20 1101 10.1.137.83
	

