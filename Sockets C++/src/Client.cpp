#include "../lib/Time.hpp"
#include "../lib/Socket.hpp"
#include "../lib/FileManager.hpp"
#include <sys/wait.h>

#define BUF_SIZE 4096

void debug(std::string data, int t = 0){
	sleep(t);
	std::cout<<"\033[47;30m"<<data<<"\033[0m"<<std::endl;
}

void debug(int data, int t = 0){
	sleep(t);
	std::cout<<"\033[47;30m"<<data<<"\033[0m"<<std::endl;
}

/*
 * arg1: ip
 * arg2: puerto
 * arg3: rep
 * arg4: output
 */
int main(int argc, char**argv){
	Time time;
	FileManager fileManager;

	char serverIp[15];
	strncpy(serverIp,argv[1],15);
	int port = atoi(argv[2]);
	int repetitions = atoi(argv[3]);
	std::string output = "output/";
	output += argv[4];
	output += ".csv";
	fileManager.open(output,1);

	fileManager.writeln("Size(B),iter,time(ns)");
	char buffer[BUF_SIZE];
	
	Socket *s1;
	

	std::cout<<"\nReceiving file \033[33m"<< repetitions << "\033[0m time"<<(repetitions==1?"":"s")<<".\n";

	for(int j = 0; j < repetitions; j++){// Itera sobre las n repeticiones

		int bytes = 0, size = 0;	
		s1 = new Socket('s',false);
		if(s1->Connect(serverIp, port)==-1)exit(EXIT_FAILURE);
		usleep(10000);
		int i = 0;
		time.start();
		do{
			size += bytes;
			bytes = s1->Read(buffer, BUF_SIZE);
		}while(bytes != 0);
		int endTime = time.end();
		debug(size,1);
	
		s1->Close();
		fileManager.writeln(std::to_string(size)+","+std::to_string(j+1)+","+std::to_string(endTime));
	}
	fileManager.close();
	time.programEnd();
	return EXIT_SUCCESS;
}