#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stddef.h>

#include "client.h"
#include "socket_operations.cc"

Client::Client(char * _server_ip, int _server_port, int _local_port){
  this->server_ip = new char(strlen(_server_ip) + 1);
  strcpy(this->server_ip, _server_ip);
  this->server_port = _server_port;
  this->local_port = _local_port;
}

Message Client::execute(Message * _message){
  socket_operations::send(*_message, this->server_ip, this->server_port, this->local_port);
  socket_operations::ReceivedMessage response = socket_operations::receive(this->local_port);
  return response.message;
}

Client::~Client() {
  delete this->server_ip;
}

