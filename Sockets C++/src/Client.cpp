#include "../lib/Time.hpp"
#include "../lib/Socket.hpp"
#include "../lib/FileManager.hpp"
#include <sys/wait.h>

#define BUF_SIZE 4096

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

	std::cout<<"\nReceiving file \033[33m"<< repetitions << "\033[0m time"<<(repetitions==1?"":"s")<<" on port \033[33m"<< port <<"\033[0m.\n\n";

	for(int j = 0; j < repetitions; j++){// Itera sobre las n repeticiones

		int bytes = 0, size = 0;	
		s1 = new Socket('s',false);
		if(s1->Connect(serverIp, port)==-1)exit(EXIT_FAILURE);
		time.start();
		do{
			size +=	bytes = s1->Read(buffer, BUF_SIZE);
		}while(bytes != 0);
		double endTime = time.end();
		s1->Close();
		fileManager.writeln(std::to_string(size)+","+std::to_string(j+1)+","+std::to_string(endTime));
		std::cout<<"\033[sConnection \033[33m#"<< j+1 <<"\033[0m\n\033[u";
	}
	fileManager.close();
	std::cout<<std::endl;
	time.programEnd();
	return EXIT_SUCCESS;
}