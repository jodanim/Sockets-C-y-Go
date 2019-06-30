#include "../lib/Time.hpp"
#include "../lib/Socket.hpp"
#include "../lib/FileManager.hpp"
#include <sys/wait.h>

void debug(std::string data, int t = 0){
	sleep(t);
	std::cout<<"\033[47;30m"<<data<<"\033[0m"<<std::endl;
}

void debug(int data, int t = 0){
	sleep(t);
	std::cout<<"\033[47;30m"<<data<<"\033[0m"<<std::endl;
}

#define BUF_SIZE 4096
#define forever for(;;)

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
 * arg2: file name
 */
int main(int argc, char **argv){
	Time time;
	FileManager fileManager;
	int childpid;

	// building socket
	Socket s1('s',false), *s2;
	if(s1.Bind(std::atoi(argv[1]))==-1)exit(EXIT_FAILURE);
	s1.Listen( 5 );

	// waiting for conection
	// std::cout<<"\nWaiting for client to connect on the port \033[33m"<<argv[1]<<"\033[0m.\n\n";	
	// s2 = s1.Accept();
		
	// opening the first file
	// std::string filename("data/");
	// filename += argv[2];
	// fileManager.open(filename);
	
	// int bytes = fileManager.getBytes();
	// int size = bytes;
	// std::string dataMeasurement = getDataMeasurement(size);
	// fileManager.close();

	// std::string extension(argv[3]);
	// extension = extension.substr(extension.size()-4);
	// filename = "data/"+std::to_string(size)+dataMeasurement+extension;

	std::string filename = argv[2];
	
	// std::cout<<"Sending file the file \033[33m" << filename << "\033[0m, \033[33m"<< repetitions << "\033[0m time"<<(repetitions==1?"":"s")<<".\n";
	// s2->Write(std::to_string(bytes).c_str());
	int connection = 0;
	std::cout<<"\nServing the file \033[33m\""<< filename << "\"\033[0m.\n";	
	forever{
		std::cout<<"\033[sWaiting for client to connect on the port \033[33m"<<argv[1]<<"\033[0m.";	
		childpid = fork();
		if(childpid < 0)perror("server: fork error.");
		else if (0 == childpid){ 
			s2 = s1.Accept();
			fileManager.open(filename);
			std::string buffer = "";
			int bufferSize = 0;
			s1.Close();
			do{
				buffer = fileManager.readSome(BUF_SIZE);
				bufferSize+=buffer.size();
				s2->Write(buffer.c_str());	
			}while(buffer.size() != 0);	
			s2->Close();
			fileManager.close();
			_exit(0);
		}
		std::cout<<"\nConnections: \033[33m"<< ++connection <<"\033[0m.";
		wait(0);
		// std::cout<<"\033[u\033[0JThe file \033[33m"<< filename <<"\033[0m was sent.\n\n";
		
		
		
		std::cout<<"\033[u\033[0K";
	}
}