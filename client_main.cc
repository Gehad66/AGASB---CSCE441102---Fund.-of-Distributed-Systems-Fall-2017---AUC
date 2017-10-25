/* Args:
 *   argv[1]: IP address of the server.
 *   argv[2]: Message string to be sent to the server.
 */
#include <string.h>
#include <stdio.h>

#include "message.h"
#include "client.h"
#include "server.h"

int main(int argc, char *argv[])
{
  Client client(argv[1], 8080);
  Message m(0, argv[2], strlen(argv[2]), 0);
  client.execute(&m);
  return 0;
}
