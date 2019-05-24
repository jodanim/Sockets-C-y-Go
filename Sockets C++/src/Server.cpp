#include "../lib/Socket.hpp"
#include "../lib/FileManager.hpp"


/**
 * arg1: repeticiones
 * arg2: extension del archivo
 * arg3: puerto
 */
int main(int argc, char **argv){
	FileManager fm;

	int childpid;
	char buffer[0];
	Socket s1('s',false), *s2;

	s1.Bind( std::atoi(argv[3]) );
	s1.Listen( 5 );
	
	for(int i = 0; i < 16; i++){
                std::string filename = "data/"+std::to_string(65536*(i+1))+"B"+argv[2];
		fm.openTransferFile(filename);
		std::string file = fm.readFile();

		int counter = 0;
		while(counter < std::atoi(argv[1])){
			s2 = s1.Accept();
			childpid = fork();
			if(childpid < 0)perror("server: Error de bifurcación.");
			else if (0 == childpid) { 
				s1.Close();
				s2->Read(buffer, 0);
				int n = file.length(); 
				char char_array[n + 1]; 
				strcpy(char_array, file.c_str());
				s2->Write(char_array);
				_exit(0);	
			}
			s2->Close();
			counter++;
		}
		fm.closeTransferFile();
	}
	return 0;
}
