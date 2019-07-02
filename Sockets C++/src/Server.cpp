#include "../lib/Time.hpp"
#include "../lib/Socket.hpp"
#include "../lib/FileManager.hpp"
#include <sys/wait.h>
#include <pthread.h>

#define BUF_SIZE 4096
#define forever for(;;)

class pargs {
public:
    char *buffer;
    int length;
    Socket *s;
};

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

	std::cout<<"\nServing the file \033[33m\""<< filename << "\"\033[0m on the port \033[33m"<<argv[1]<<"\033[0m." << std::endl;

    char *buffer;
    int buffer_len;
    fileManager.open(filename);
    buffer = fileManager.readFile(&buffer_len);
    fileManager.close();

    int tid = 0;
    std::cout<<std::endl;
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

        std::cout << "\033[sRequested \033[33m" << ++tid <<"\033[0m times \n\033[u";
	}
}
