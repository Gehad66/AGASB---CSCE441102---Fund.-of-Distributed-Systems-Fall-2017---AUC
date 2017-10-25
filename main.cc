#include "Message.h"
#include <string.h>

/* int main(int argc, char *argv[])
{
  Message m(0, argv[1], strlen(argv[1]), 0);
  return 0;
} */

int main()
{
  Message m(0, const_cast<char*>("hello"), 5, 0);
  return 0;
}
