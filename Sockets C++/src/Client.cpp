#include "../lib/Time.hpp"
#include "../lib/Socket.hpp"
#include "../lib/FileManager.hpp"
#include <sys/wait.h>

/**
 * arg1: repeticiones
 * arg2: puerto
 * arg3: ip
 */
int main(int argc, char**argv){
	Time time;
	FileManager fileManager;
	fileManager.open("output/output.csv",1);
	fileManager.writeln("Size(B),iter,time(ns)");
	char buffer[1048576];
	Socket *s;
	int childpid;
	for(int i = 0; i < 16; i++){
		for(int j = 0; j < std::atoi(argv[1]); j++){
			s = new Socket('s',false);
			s->Connect(argv[3], std::atoi(argv[2]));
			time.start();
			s->Write((const char *)argv[0]);
			s->Read(buffer, 1048576);
			int endTime = time.end();
			fileManager.writeln(std::to_string(65536*(i+1))+","+std::to_string(j)+","+std::to_string(endTime));
			s->Close();
		}
	}
	fileManager.close();
	return 0;
}
