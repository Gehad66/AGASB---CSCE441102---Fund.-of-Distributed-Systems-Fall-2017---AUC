/* Args:
 *   argv[1]: Server IP address.
 *   argv[2]: Server port number.
 *   argv[3]: Listen port number.
 *   argv[4]: Message string to be sent to the server.
 *
 * Example:
 * ./client_main 127.0.0.1 8080 8081 hello
 */
#include <string.h>
#include <stdio.h>

#include "message.h"
#include "client.h"
#include "server.h"

int main(int argc, char *argv[])
{
	while(true){
    char *s;
    s = (char*)malloc(256);
    scanf("%255s", s); 
    
    if (strncmp(s, "q", strlen(s)) == 0)
      break;
    
    Client client(argv[1], atoi(argv[2]), atoi(argv[3]));
    Message m(0, s, strlen(s), 0);
    client.execute(&m);
    
    free(s);
}
  return 0;
}

