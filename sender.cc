#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stddef.h>
#include <netinet/in.h>
#include <stdio.h>

void sender (char *message1, char *message2, char *machine, int port)
{
  int s, n;
  struct sockaddr_in mySocketAddress, yourSocketAddress;

  if ((s = socket (AF_INET, SOCK_DGRAM, 0)) < 0)
    {
      perror ("socket failed");
      return;
    }

  //setBoardcast(s);

  makeLocalSA (&mySocketAddress);

  if (bind (s, &mySocketAddress, sizeof (struct sockaddr_in)) != 0)
    {
      perror ("Bind Failed");
      close (s);
      return;


    }

  makeDestSA (&yourSocketAddress, machine, port);
  printf ("Before sending\n");
  if ((n =
       sendto (s, message1, strlen (message1), 0, &yourSocketAddress,
	       sizeof (struct sockaddr_in))) < 0)
    perror ("Send 2 failed\n");
  if ((n =
       sendto (s, message2, strlen (message2), 0, &yourSocketAddress,
	       sizeof (struct sockaddr_in))) < 0)
    perror ("Send 2 failed\n");
  printf ("after sending\n");
  close (s);

  printf ("after closing\n");
}				//end of sender


void makeLocalSA (struct sockaddr_in *sa)
{
  sa->sin_family = AF_INET;
  sa->sin_port = htons (0);
  sa->sin_addr.s_addr = htonl (INADDR_ANY);
}

void makeDestSA (struct sockaddr_in *sa, char *hostname, int port)
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

void main ()
{
  sender("Hi", "hiiiii", "10.7.57.178", 8080);
}
