all: compile compile_d finished

################################################################################

obj/Socket.obj: src/Socket.cpp
	@echo "\033[1;35mGenerating \033[0;33m$@\033[0m"
	@g++ -c $^ -o $@

obj/debug/Socket.obj: src/Socket.cpp
	@echo "\033[1;36mGenerating \033[0;33m$@\033[0m"
	@g++ -g -c $^ -o $@

#-------------------------------------------------------------------------------

obj/Time.obj: src/Time.cpp
	@echo "\033[1;35mGenerating \033[0;33m$@\033[0m"
	@g++ -c $^ -o $@

obj/debug/Time.obj: src/Time.cpp
	@echo "\033[1;36mGenerating \033[0;33m$@\033[0m"
	@g++ -g -c $^ -o $@

#-------------------------------------------------------------------------------

obj/FileManager.obj: src/FileManager.cpp
	@echo "\033[1;35mGenerating \033[0;33m$@\033[0m"
	@g++ -c $^ -o $@


obj/debug/FileManager.obj: src/FileManager.cpp
	@echo "\033[1;36mGenerating \033[0;33m$@\033[0m"
	@g++ -g -c $^ -o $@

#-------------------------------------------------------------------------------

obj/Client.obj: src/Client.cpp
	@echo "\033[1;35mGenerating \033[0;33m$@\033[0m"
	@g++ -c $^ -o $@

obj/debug/Client.obj: src/Client.cpp
	@echo "\033[1;36mGenerating \033[0;33m$@\033[0m"
	@g++ -g -c $^ -o $@

#-------------------------------------------------------------------------------

obj/Server.obj: src/Server.cpp
	@echo "\033[1;35mGenerating \033[0;33m$@\033[0m"
	@g++ -c $^ -o $@

obj/debug/Server.obj: src/Server.cpp
	@echo "\033[1;36mGenerating \033[0;33m$@\033[0m"
	@g++ -g -c $^ -o $@

################################################################################

bin/Client: obj/Socket.obj obj/FileManager.obj obj/Time.obj obj/Client.obj
	@echo "\033[1;35mGenerating \033[0;33m$@\033[0m"
	@g++ -pthread $^ -o $@

bin/debug/Client: obj/debug/Socket.obj obj/debug/FileManager.obj obj/debug/Time.obj obj/debug/Client.obj 
	@echo "\033[1;36mGenerating \033[0;33m$@\033[0m"
	@g++ -pthread -g $^ -o $@

#-------------------------------------------------------------------------------

bin/Server: obj/Socket.obj obj/FileManager.obj obj/Time.obj obj/Server.obj
	@echo "\033[1;35mGenerating \033[0;33m$@\033[0m"
	@g++ -pthread $^ -o $@

bin/debug/Server: obj/debug/Socket.obj obj/debug/FileManager.obj obj/debug/Time.obj obj/debug/Server.obj 
	@echo "\033[1;36mGenerating \033[0;33m$@\033[0m"
	@g++ -pthread -g $^ -o $@

################################################################################

compile:compileMessage bin/Client bin/Server
	
compile_d:compileMessage bin/debug/Client bin/debug/Server

#-------------------------------------------------------------------------------

run_Client:compile runMessage 
	@.\/bin/Client 192.168.0.16 1101
	@make finished --no-print-directory

debug_Client:compile_d debugMessage
	@gdb bin/debug/Client
	@make finished --no-print-directory

#-------------------------------------------------------------------------------

run_Server:compile runMessage 
	@.\/bin/Server 100 1101 .txt
	@make finished --no-print-directory

debug_Server:compile_d debugMessage
	@gdb bin/debug/Server
	@make finished --no-print-directory

################################################################################

compileMessage:
	clear
	@echo "\033[1;31m------------------------------------------------\033[0m"
	@echo "\033[1;33m                   Compiling                    \033[0m"
	@echo "\033[1;31m------------------------------------------------\033[0m\n"

runMessage:
	@echo "\n\033[1;31m------------------------------------------------\033[0m"
	@echo   "\033[1;33m                    Running                     \033[0m"
	@echo   "\033[1;31m------------------------------------------------\033[0m\n"

debugMessage:
	@echo "\n\033[1;31m------------------------------------------------\033[0m"
	@echo   "\033[1;33m                   Debugging                    \033[0m"
	@echo   "\033[1;31m------------------------------------------------\033[0m\n"

finished:
	@echo "\n\033[1;31m------------------------------------------------\033[0m"
	@echo   "\033[1;33m                    Finished                    \033[0m"
	@echo   "\033[1;31m------------------------------------------------\033[0m\n"

help:
	clear
	@echo "\033[1;31m------------------------------------------------\033[0m"
	@echo "\033[1;33m                      Help                      \033[0m"
	@echo "\033[1;31m------------------------------------------------\033[0m\n"
	@echo "\033[1m To run the client give as parameters:\033[0m"
	@echo "\033[1;32m 	1- \033[0mServer Ip\033[0m"
	@echo "\033[1;32m 	2- \033[0mPort number\033[0m"
	@echo "\033[1m To run the server give as parameters:\033[0m"
	@echo "\033[1;32m 	1- \033[0mNumber of repetitions\033[0m"
	@echo "\033[1;32m 	2- \033[0mPort number\033[0m"
	@echo "\033[1;32m 	3- \033[0mFile extention (Ex: .txt)\033[0m\n"
	@echo "\033[1;31m------------------------------------------------\033[0m"
	@echo "\033[1;33m                      Help                      \033[0m"
	@echo "\033[1;31m------------------------------------------------\033[0m\n"

################################################################################