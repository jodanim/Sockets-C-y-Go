#include "../lib/Time.hpp"
#include "../lib/Socket.hpp"
#include "../lib/FileManager.hpp"
#include <sys/wait.h>

/*
 * arg1: ip
 * arg2: puerto
 */
int main(int argc, char**argv){
	Time time;
	FileManager fileManager;
	fileManager.open("output/output.csv",1);
	fileManager.writeln("Size(B),iter,time(ns)");
	char buffer[1048576];
	Socket *s;
	s = new Socket('s',false);
	s->Connect(argv[1], std::atoi(argv[2]));
	s->Write("hello");
	s->Read(buffer, 1048576);
	s->Close();
	int repetitions = std::atoi(buffer);
	std::cout<<"Total repetitions per file size: "<<repetitions<<std::endl<<std::endl;
	for(int i = 0; i < 16; i++){
		std::cout<<"Receiving file group number \033[33m" << i+1 << "\033[0m\n";
		for(int j = 0; j < repetitions; j++){
			s = new Socket('s',false);
			s->Connect(argv[1], std::atoi(argv[2]));
			time.start();
			s->Write("");
			s->Read(buffer, 1048576);
			int endTime = time.end();
			fileManager.writeln(std::to_string(65536*(i+1))+","+std::to_string(j+1)+","+std::to_string(endTime));
			s->Close();
		}
	}
	fileManager.close();
	time.programEnd();
	return 0;
}
