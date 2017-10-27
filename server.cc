#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "message.h"
#include "server.h"
#include "socket_operations.cc"

Server::Server(int _listen_port) {
  this->listen_port = _listen_port;
}

void Server::serveRequest(){ 
  while(true){
    socket_operations::ReceivedMessage received = socket_operations::receive(this->listen_port);

    pid_t pid = fork();
    if (pid) {
      // parent process
      if (!strcmp("q", (const char *) received.message.getMessage())) {
        break;
      }
    }
    else {
      // child process
      Message reply = doOperation(&received.message);
      socket_operations::send(reply, inet_ntoa(received.socket.sin_addr), ntohs(received.socket.sin_port));
      break;
    }
  }
}

Server::~Server() {}

Message * Server::getRequest() {}

Message Server::doOperation(Message * _message) {
  char vowels[6] = "aeioy";
  char * s = new char[_message->getMessageSize() + 1];
  int counter = 0;
  for (char * c = (char*) _message->getMessage(); *c; ++c) {
    if (!std::binary_search(vowels, vowels + 5, *c)) {
      s[counter++] = *c;
    }
  }
  s[counter] = 0;
  return Message(0, (void *) s, counter, 0, Reply);
}

void Server::sendReply (Message * _message) {}

