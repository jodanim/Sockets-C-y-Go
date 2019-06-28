#include "../lib/Time.hpp"
#include "../lib/Socket.hpp"
#include "../lib/FileManager.hpp"
#include <sys/wait.h>

#define BUF_SIZE 4096


std::string getDataMeasurement(int &size,std::string dm = "B"){
	std::string dataMeasuremet[] = {"B","KB","MB","GB","TB"};
	int measure = 0;
	while(dataMeasuremet[measure] != dm)measure++;
	while(size/1024>=1){
		size/=1024;
		measure++;
	}
	return dataMeasuremet[measure];
}

/**
 * arg1: port
 * arg2: repetitions
 * arg3: file name
 */
int main(int argc, char **argv){
	if(argc<4){
		std::cout<<"Wrong number of arguments\n";
		exit(EXIT_FAILURE);
	}
	Time time;
	FileManager fileManager;
	int childpid;
	char * input;
	// building socket
	Socket s1('s',false), *s2;
	if(s1.Bind(std::atoi(argv[1]))==-1)exit(EXIT_FAILURE);
	s1.Listen( 5 );

	// waiting for conection
	std::cout<<"\nWaiting for client to connect on the port \033[33m"<<argv[1]<<"\033[0m.\n\n";	
	s2 = s1.Accept();
	// setting file quantity and repetitions for server and client
	
	s2->Write(argv[2]);
	int repetitions = std::atoi(argv[2]);
	
	// opening the first file
	std::string filename("data/");
	filename += argv[3];
	fileManager.open(filename);
	
	int bytes = fileManager.getBytes();
	int size = bytes;
	std::string dataMeasurement = getDataMeasurement(size);
	fileManager.close();

	std::string extension(argv[3]);
	extension = extension.substr(extension.size()-4);
	filename = "data/"+std::to_string(size)+dataMeasurement+extension;

	std::cout<<"Sending file the file \033[33m" << filename << "\033[0m, \033[33m"<< repetitions << "\033[0m time"<<(repetitions==1?"":"s")<<".\n";
	s2->Write(std::to_string(bytes).c_str());
	for(int j = 0; j < repetitions; j++){// number of repetitions loop
		childpid = fork();
		if(childpid < 0)perror("server: fork error.");
		else if (0 == childpid){ 
			fileManager.open(filename);
			std::string buffer = "";
			int bufferSize = 0;
			s1.Close();
			while(bufferSize<bytes){	
				buffer = fileManager.readSome(BUF_SIZE);
				bufferSize+=buffer.size();
				s2->Write(buffer.c_str());
			}	
			s2->Close();
			fileManager.close();
			_exit(0);
		}else{
			wait(0);
		}
	}

	s2->Close();
	time.programEnd();
	return EXIT_SUCCESS;
}