#include <string.h>
#include <stdio.h>

#include "Message.h"
#include "Client.h"
#include "Server.h"

using namespace std; 

int main()
{
  Server server("127.0.0.1", 8080);
  server.serveRequest();
  return 0;
}  
