#ifndef CLIENT_H
#define CLIENT_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stddef.h>
#include <netinet/in.h>
#include <stdio.h>

#include "Message.h"

class Client
{
private:
// UDPClientSocket * udpSocket;
char * hostname;
int port;
void send(Message *);
void makeLocalSA (struct sockaddr_in *sa);
void makeDestSA (struct sockaddr_in *sa);
void receive();
public:
Client(char * _hostname, int _port);
Message * execute(Message * _message);
~Client();
};
#endif // CLIENT_H
