#include "../lib/Time.hpp"
#include "../lib/Socket.hpp"
#include "../lib/FileManager.hpp"
#include <sys/wait.h>

#define BUF_SIZE 4096
/*
 * arg1: ip
 * arg2: puerto
 */
int main(int argc, char**argv){
	Time time;
	FileManager fileManager;

	fileManager.open("output/output.csv",1);
	fileManager.writeln("Size(B),iter,time(ns)");
	char buffer[BUF_SIZE];
	
	Socket *s1, *s2;
	s1 = new Socket('s',false);

	s1->Connect(argv[1], std::atoi(argv[2]));

	s1->Read(buffer, BUF_SIZE);
	int repetitions = std::atoi(buffer);

	s1->Read(buffer, BUF_SIZE);
	int bytes = atoi(buffer);

	std::cout<<"\nReceiving file with \033[33m" << bytes << "\033[0m bytes \033[33m"<< repetitions << "\033[0m time"<<(repetitions==1?"":"s")<<".\n";

	for(int j = 0; j < repetitions; j++){// Itera sobre las n repeticiones
		int size = 0;	

		time.start();
		while(size < bytes){
			size += s1->Read(buffer, BUF_SIZE);
		}
		int endTime = time.end();
		fileManager.writeln(std::to_string(size)+","+std::to_string(j+1)+","+std::to_string(endTime));
	}
	fileManager.close();
	time.programEnd();
	return EXIT_SUCCESS;
}