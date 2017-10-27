/* Args:
 *   argv[1]: Listen port.
 *
 * Example:
 * ./server_main 8080
 */

#include <string.h>
#include <stdio.h>

#include "message.h"
#include "server.h"

using namespace std; 

int main(int argc, char *argv[])
{
  Server server(atoi(argv[1]));
  server.serveRequest();
  return 0;
}
