#include "Message.h"
#include "Server.h"
#include "socket_operations.cc"
#include <sys/types.h>
#include <stdio.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

Server::Server(char * _listen_hostname, int _listen_port) {
  this->listen_hostname = _listen_hostname;
  this->listen_port = _listen_port;
}

void Server::serveRequest(){
 
  while(true){
    socket_operations::ReceivedMessage received = socket_operations::receive(this->listen_port);
    pid_t pid = fork();
    if (pid) {
      // parent process - do nothing
    }
    else {
      Message reply = doOperation(&received.message);
      printf("received from %s: %d\n", inet_ntoa(received.socket.sin_addr), (int) received.socket.sin_port);
      // socket_operations::send(reply, inet_ntoa(received.socket.sin_addr), (int) received.socket.sin_port);
      socket_operations::send(reply, inet_ntoa(received.socket.sin_addr), 8080);
      break;
    }
  }


}
Server::~Server() {}

Message * Server::getRequest() {}
Message Server::doOperation(Message * _message) {
  return Message(0, const_cast<void *>((const void*)"Server reply"), strlen("Server reply"), 0);
}
void Server::sendReply (Message * _message) {}


/* void Server::receive ()
{
  int SIZE = 1 << 13;
  char message[SIZE];
  struct sockaddr_in mySocketAddress, aSocketAddress;
  int s, aLength, n;

  if ((s = socket (AF_INET, SOCK_DGRAM, 0)) < 0)
    {
      perror ("socket  failed");
      return;
    }

  makeReceiverSA (&mySocketAddress);

  if (bind (s, (const sockaddr*) &mySocketAddress, sizeof (struct sockaddr_in)) != 0)
    {
      perror ("Bind  failed\n");

      close (s);
      return;
    }

  aLength = sizeof (aSocketAddress);
  aSocketAddress.sin_family = AF_INET;	// note that this is needed
  printf ("Before receiving msg\n");
  if ((n = recvfrom (s, message, SIZE, 0, (struct sockaddr*) &aSocketAddress, (socklen_t*) &aLength)) < 0)
    {
      perror ("Receive 1");
    }

  printf ("%s\n", message);
  close (s);
} */

void Server::makeReceiverSA (struct sockaddr_in *sa)
{
  sa->sin_family = AF_INET;
  sa->sin_port = htons (this->listen_port);
  sa->sin_addr.s_addr = htonl (INADDR_ANY);
}
