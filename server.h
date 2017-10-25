#ifndef SERVER_H
#define SERVER_H
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stddef.h>
#include <netinet/in.h>

#include "message.h"

class Server
{
private:
// UDPServerSocket * udpServerSocket;
char * listen_hostname;
int listen_port;
Message * getRequest();
Message * doOperation();
void sendReply (Message * _message);
void receive();
void makeReceiverSA (struct sockaddr_in *sa);
public:
Server(char * _listen_hostname, int _listen_port);
void serveRequest();
~Server();
};
#endif // SERVER_H
