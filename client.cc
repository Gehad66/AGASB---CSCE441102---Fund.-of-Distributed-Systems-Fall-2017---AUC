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

#include "client.h"
#include "socket_operations.cc"

Client::Client(char * _hostname, int _port){
  this->hostname = new char(strlen(_hostname) + 1);
  strcpy(this->hostname, _hostname);
  this->port = _port;
}

Message* Client::execute(Message * _message){
  socket_operations::send(*_message, this->hostname, this->port);
  // this->send(_message);
}

void Client::makeLocalSA (struct sockaddr_in *sa)
{
  sa->sin_family = AF_INET;
  sa->sin_port = htons (0);
  sa->sin_addr.s_addr = htonl (INADDR_ANY);
}

void Client::makeDestSA (struct sockaddr_in *sa)
{
  struct hostent *host;
  sa->sin_family = AF_INET;
  if ((host = gethostbyname (hostname)) == NULL)
    {
      printf ("Unknown host name\n");
      exit (-1);
    }
  sa->sin_addr = *(struct in_addr *) (host->h_addr);
  sa->sin_port = htons (port);
}


void Client::send(Message *_message)
{
  int s, n;
  struct sockaddr_in mySocketAddress, yourSocketAddress;

  if ((s = socket (AF_INET, SOCK_DGRAM, 0)) < 0)
    {
      perror ("Socket construction failed");
      return;
    }

  makeLocalSA (&mySocketAddress);

  if (bind (s, (const sockaddr*) &mySocketAddress, sizeof (struct sockaddr_in)) != 0)
    {
      perror ("Bind Failed!");
      close (s);
      return;


    }

  makeDestSA (&yourSocketAddress);
  if ((n =
       sendto (s, _message->getMessage(), strlen ((char*)_message->getMessage()), 0, (const sockaddr*)&yourSocketAddress,
	       sizeof (struct sockaddr_in))) < 0) {
    perror ("Send failed\n");
  }
  printf ("Send successful\n");
  close(s);
  printf ("Socket close successful\n");
}

void Client::receive() {}

Client::~Client(){}

