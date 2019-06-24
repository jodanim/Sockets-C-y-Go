#ifndef SOCKET_HPP
#define SOCKET_HPP

//#include <sys/types.h>
//#include <sys/wait.h>
//include <sys/socket.h>
//#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
//#include <errno.h>

class Socket{
	public:
		Socket(char t = 's', bool ipv6 = false);
		Socket(int new_sockfd);
		~Socket();
		int Connect(char * Host, int Port);
		int Connect(char * Host, char * Service);
		int Read(char * text, int len);
		int Write(const char * text);
		int Shutdown(int);
		int Close();
		int Listen(int Queue);
		int Bind(int Port);
		Socket* Accept();
		int HostnameToIp(char *Hostname, char *ip);
	private:
		int sockfd;
};

#endif