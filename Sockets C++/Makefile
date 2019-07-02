all: clear compile_client compile_server finished

################################################################################

obj/Socket.obj: src/Socket.cpp
	@echo "\033[1;35mGenerating \033[0;33m$@\033[0m"
	@g++ -c $^ -o $@

#-------------------------------------------------------------------------------

obj/Time.obj: src/Time.cpp
	@echo "\033[1;35mGenerating \033[0;33m$@\033[0m"
	@g++ -c $^ -o $@

#-------------------------------------------------------------------------------

obj/FileManager.obj: src/FileManager.cpp
	@echo "\033[1;35mGenerating \033[0;33m$@\033[0m"
	@g++ -c $^ -o $@

#-------------------------------------------------------------------------------

obj/Client.obj: src/Client.cpp
	@echo "\033[1;35mGenerating \033[0;33m$@\033[0m"
	@g++ -c $^ -o $@

#-------------------------------------------------------------------------------

obj/Server.obj: src/Server.cpp
	@echo "\033[1;35mGenerating \033[0;33m$@\033[0m"
	@g++ -c $^ -o $@

################################################################################

bin/Client: obj/Socket.obj obj/FileManager.obj obj/Time.obj obj/Client.obj
	@echo "\033[1;35mGenerating \033[0;33m$@\033[0m"
	@g++ -pthread $^ -o $@

#-------------------------------------------------------------------------------

bin/Server: obj/Socket.obj obj/FileManager.obj obj/Time.obj obj/Server.obj
	@echo "\033[1;35mGenerating \033[0;33m$@\033[0m"
	@g++ -pthread $^ -o $@

################################################################################

compile_client: clear compileMessage bin/Client
compile_server: clear compileMessage bin/Server

#-------------------------------------------------------------------------------

run_client:compile_client runClientMessage 
	@.\/bin/Client 0.0.0.0 9000 100 output
	@make finished --no-print-directory

#-------------------------------------------------------------------------------

run_server:compile_server runServerMessage
	@.\/bin/Server 9000 data/64KB.txt
	@make finished --no-print-directory

run_server_arg:
	@.\/bin/Server 9000 $(repetitions) $(file)

################################################################################

clear:
	clear

compileMessage:
	@echo "\033[1;31m------------------------------------------------\033[0m"
	@echo "\033[1;33m                   Compiling                    \033[0m"
	@echo "\033[1;31m------------------------------------------------\033[0m\n"

runClientMessage:
	@echo "\n\033[1;31m------------------------------------------------\033[0m"
	@echo   "\033[1;33m                 Running Client                 \033[0m"
	@echo   "\033[1;31m------------------------------------------------\033[0m"

runServerMessage:
	@echo "\n\033[1;31m------------------------------------------------\033[0m"
	@echo   "\033[1;33m                 Running Server                 \033[0m"
	@echo   "\033[1;31m------------------------------------------------\033[0m"

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
	@echo "\033[1;32m 	3- \033[0mNumber of repetitions\033[0m"
	@echo "\033[1;32m 	3- \033[0mCsv file name.\033[0m\n"
	@echo "\033[1m To run the server give as parameters:\033[0m"
	@echo "\033[1;32m 	1- \033[0mPort number\033[0m"
	@echo "\033[1;32m 	2- \033[0mFile path\033[0m\n"
	@echo "\033[1;31m------------------------------------------------\033[0m"
	@echo "\033[1;33m                      Help                      \033[0m"
	@echo "\033[1;31m------------------------------------------------\033[0m\n"

################################################################################
