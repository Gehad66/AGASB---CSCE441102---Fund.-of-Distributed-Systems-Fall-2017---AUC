#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stddef.h>
#include <netinet/in.h>
#include <stdio.h>
/*receive two messages through port given as argument*/
void
receiver (int port)
{
  int SIZE = 10;
  char message1[SIZE], message2[SIZE];
  struct sockaddr_in mySocketAddress, aSocketAddress;
  int s, aLength, n;

  if ((s = socket (AF_INET, SOCK_DGRAM, 0)) < 0)
    {
      perror ("socket  failed");
      return;
    }

  makeReceiverSA (&mySocketAddress, port);

  if (bind (s, &mySocketAddress, sizeof (struct sockaddr_in)) != 0)
    {
      perror ("Bind  failed\n");

      close (s);
      return;
    }

  aLength = sizeof (aSocketAddress);
  aSocketAddress.sin_family = AF_INET;	/* note that this is needed */
  printf ("Before receiving msg1\n");
  if ((n = recvfrom (s, message1, SIZE, 0, &aSocketAddress, &aLength)) < 0)
    {
      perror ("Receive 1");
    }

  printf ("Before receiving msg2\n");
  if ((n = recvfrom (s, message2, SIZE, 0, &aSocketAddress, &aLength)) < 0)
    {
      perror ("Receive 2");
    }
  printf ("%s \n", message1);
  printf ("%s", message2);
  close (s);
}

void makeReceiverSA (struct sockaddr_in *sa, int port)
{
  sa->sin_family = AF_INET;
  sa->sin_port = htons (port);
  sa->sin_addr.s_addr = htonl (INADDR_ANY);
}

void
main ()
{
  receiver (8080);
}
