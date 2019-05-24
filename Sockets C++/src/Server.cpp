#include "../lib/Socket.hpp"
#include "../lib/FileManager.hpp"
#include <math.h> 

int main(int argc, char **argv){
	FileManager fm;

	int childpid;
	char buffer[0];
	Socket s1('s',false), *s2;

	s1.Bind( 11011 );
	s1.Listen( 5 );
	
	for(int i = 0; i < 10; i++){
		std::string filename = "data/"+std::to_string((int)(pow(2,4+i)))+"B";
		fm.openTransferFile(filename);
		std::string file = fm.readFile();

		int counter = 0;
		while(counter<100){
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
			std::cout<<counter;
		}
		fm.closeTransferFile();
	}
	return 0;
}
