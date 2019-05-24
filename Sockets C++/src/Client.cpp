#include "../lib/Time.hpp"
#include "../lib/Socket.hpp"
#include "../lib/FileManager.hpp"


/**
 * arg1: repeticiones
 * arg2: puerto
 * arg3: ip
 */
int main(int argc, char**argv){
    Time t;
    FileManager fm;
	fm.openCsv("output.csv");
	char buffer[8192];

	int childpid;
	Socket *s;	

	for(int j = 0; j < 16; j++){
		fm.writeHeader("Tiempo de archivos: "+std::to_string(65536*(j+1)));
		for(int i = 0; i < std::atoi(argv[1]); i++){
			s = new Socket('s',false);
			s->Connect(argv[3], std::atoi(argv[2]));
			childpid = fork();
			if(childpid < 0)perror("client: Error de bifurcación.");
			else if (0 == childpid) { 
				t.setStartTime();
				s->Write(argv[0]);
				s->Read(buffer, 1024);
				t.setEndTime();
				fm.writeTotal(t.getDiff());
				_exit(0);	
			}
			s->Close();
		}
	}
	return 0;
}
