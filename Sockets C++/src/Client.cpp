#include "../lib/Time.hpp"
#include "../lib/Socket.hpp"
#include "../lib/FileManager.hpp"
#include <sys/wait.h>

/*
 * arg1: ip
 * arg2: puerto
 */

int BUF_SIZE = 1048576;

int main(int argc, char**argv){

	Time time;
	FileManager fileManager;

	fileManager.open("output/output.csv",1);
	fileManager.writeln("Size(B),iter,time(ns)");

	char buffer[BUF_SIZE];

	Socket *s;
	s = new Socket('s',false);
	s->Connect(argv[1], std::atoi(argv[2]));
	s->Write("hello");
	s->Read(buffer, BUF_SIZE);
	s->Close();

	int repetitions = std::atoi(buffer);

	std::cout<<"Total repetitions per file size: "<<repetitions<<std::endl<<std::endl;

	for(int i = 0; i < 16; i++){
        // Itera sobre cada tamaño de archivo

		std::cout<<"Receiving file group number \033[33m" << i+1 << "\033[0m\n";

        int val = (65536*(i+1));
		for(int j = 0; j < repetitions; j++){
            // Itera sobre las 100 repeticiones para cada tamaño

			s = new Socket('s',false);
			s->Connect(argv[1], std::atoi(argv[2]));

			time.start();
			s->Write("");
			s->Read(buffer, val);
			s->Close();
			int endTime = time.end();

			fileManager.writeln(std::to_string(65536*(i+1))+","+std::to_string(j+1)+","+std::to_string(endTime));

		}
	}
	fileManager.close();
	time.programEnd();
	return 0;
}
