#include <string.h>
#include <stdio.h>

#include "message.h"
#include "client.h"
#include "server.h"

int main(int argc, char *argv[])
{
  Message m(0, argv[1], strlen(argv[1]), 0);
  Client client("127.0.0.1", 8080);
  client.execute(&m);
  return 0;
}  
