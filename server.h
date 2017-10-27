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
int listen_port;

Message * getRequest();
Message doOperation(Message *);
void sendReply (Message * _message);

public:

Server(int _listen_port);
void serveRequest();
~Server();
};
#endif // SERVER_H
