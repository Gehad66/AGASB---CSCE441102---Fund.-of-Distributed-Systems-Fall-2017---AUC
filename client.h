#ifndef CLIENT_H
#define CLIENT_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stddef.h>
#include <netinet/in.h>
#include <stdio.h>

#include "message.h"

class Client
{
private:
// UDPClientSocket * udpSocket;
char * server_ip;
int server_port;
int local_port;
public:
Client(char * _server_ip, int _server_port, int _listen_port);
Message execute(Message * _message);
~Client();
};
#endif // CLIENT_H
