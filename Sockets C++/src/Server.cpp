#include "../lib/Time.hpp"
#include "../lib/Socket.hpp"
#include "../lib/FileManager.hpp"

/**
 * arg1: repeticiones
 * arg2: puerto
 * arg3: extensión del archivo
 */
int main(int argc, char **argv){
	Time time;
	FileManager fileManager;
	int childpid;
	char buffer[0];
	std::cout<<"Waiting for a client to connect\n\n";
	Socket s1('s',false), *s2;
	s1.Bind( std::atoi(argv[2]) );
	s1.Listen( 5 );
	s2 = s1.Accept();
	s2->Read(buffer, 0);
	s2->Write(argv[1]);
	s2->Close();
	for(int i = 0; i < 16; i++){
		std::string filename = "data/"+std::to_string(65536*(i+1))+"B"+argv[3];
		fileManager.open(filename);
		std::string file = fileManager.readFile();
		std::cout<<"Loading the file \033[33m" << filename << "\033[0m into the buffer\n";
		int counter = 0;
		while(counter < std::atoi(argv[1])){
			s2 = s1.Accept();
			childpid = fork();
			if(childpid < 0)perror("server: Error de bifurcación.");
			else if (0 == childpid) { 
				s1.Close();
				s2->Read(buffer, 0);
				s2->Write(file.c_str());
				_exit(0);
			}
			s2->Close();
			counter++;
		}
		fileManager.close();
	}
	time.programEnd();
	return 0;
}
