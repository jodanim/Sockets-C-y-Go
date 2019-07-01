#include "../lib/Time.hpp"
#include "../lib/Socket.hpp"
#include "../lib/FileManager.hpp"
#include <sys/wait.h>
#include <pthread.h>

class pargs {
public:
    char *buffer;
    int length;
    Socket *s;
};

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

void* ProcessConnection(void* args) {
    pargs* cast = (pargs*) args;
    cast->s->Write(cast->buffer, cast->length);
    cast->s->Close();

    delete cast;
    int tid = 0;
    pthread_exit(NULL);
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
	Socket s1('s',false);
	if(s1.Bind(std::atoi(argv[1]))==-1)exit(EXIT_FAILURE);
	s1.Listen( 5 );

	std::string filename = argv[2];
	int connection = 0;

	std::cout<<"\nServing the file \033[33m\""<< filename << "\"\033[0m.\n";

    char *buffer;
    int buffer_len;
    fileManager.open(filename);
    buffer = fileManager.readFile(&buffer_len);
    fileManager.close();

    std::cout<<"\033[sWaiting for client to connect on the port \033[33m"<<argv[1]<<"\033[0m." << std::endl;
    int tid = 0;

	forever {
        pargs *args;
        args = new pargs;

        args->buffer = buffer;
        args->length = buffer_len;
        args->s = s1.Accept();

        pthread_t hijo;
        int rc = pthread_create(&hijo, NULL, ProcessConnection, (void*)args);
        if (rc) {
            std::cout << "Couldn't create thread" << std::endl;
            exit(-1);
        }

        rc = pthread_detach(hijo);
        if (rc) {
            std::cout << "Couldn't detach thread" << std::endl;
            exit(-1);
        }

        std::cout << "Spawned thread " << ++tid << std::endl;
	}
}
