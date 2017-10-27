#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stddef.h>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace socket_operations
{
  void print(const char * message){
    printf("Socket Operations: %s\n", message);
  }
  void makeLocalSA (struct sockaddr_in *sa, int port)
  {
    sa->sin_family = AF_INET;
    sa->sin_port = htons (port);
    sa->sin_addr.s_addr = htonl (INADDR_ANY);
  }

  void makeDestSA (struct sockaddr_in *sa, char *hostname, int port)
  {
    struct hostent *host;
    sa->sin_family = AF_INET;
    if ((host = gethostbyname (hostname)) == NULL)
      {
	perror("Unknown host name.");
	exit (-1);
      }
    sa->sin_addr = *(struct in_addr *) (host->h_addr);
    sa->sin_port = htons (port);
  }

  void send (const Message & message, char *hostname, int port, int local_port = 0)
  {
    int s, n;
    struct sockaddr_in mySocketAddress, yourSocketAddress;

    if ((s = socket (AF_INET, SOCK_DGRAM, 0)) < 0)
      {
	perror ("socket failed");
	exit(-1);
      }
    makeLocalSA (&mySocketAddress, local_port);

    if (bind (s, (const sockaddr*) &mySocketAddress, sizeof (struct sockaddr_in)) != 0)
      {
	perror ("Bind Failed");
	close (s);
	exit(-1);
      }

    makeDestSA (&yourSocketAddress, hostname, port);
    if ((n =
	 sendto (s, message.getMessage (), strlen ((const char *) message.getMessage ()), 0,
		 (const sockaddr*) &yourSocketAddress, sizeof (struct sockaddr_in))) < 0)
      {perror ("Send failed");}

    char tmp[32];
    sprintf(tmp, "Sent to %s: %d from %d", hostname, port, local_port);
    print(tmp);
    print((const char *) message.getMessage());

    close (s);
  }				//end of send

  class ReceivedMessage {
  public:
    ReceivedMessage(const Message & _message, const struct sockaddr_in & _socket) {
      message = _message;
      socket = _socket;
    }
    Message message;
    struct sockaddr_in socket;
  };

  ReceivedMessage receive (int port)
  {
    int SIZE = 1 << 13;
    char message[SIZE];
    struct sockaddr_in mySocketAddress, aSocketAddress;
    int s, aLength, n;

    if ((s = socket (AF_INET, SOCK_DGRAM, 0)) < 0)
      {
	perror ("Socket  failed");
	exit(-1);
      }

    makeLocalSA (&mySocketAddress, port);

    if (bind (s, (const sockaddr*) &mySocketAddress, sizeof (struct sockaddr_in)) != 0)
      {
	perror ("Bind  failed");
	close (s);
	exit(-1);
      }

    aLength = sizeof (aSocketAddress);
    aSocketAddress.sin_family = AF_INET;	/* note that this is needed */
    if ((n = recvfrom (s, message, SIZE, 0, (sockaddr*) &aSocketAddress, (socklen_t*) &aLength)) < 0)
      {
	perror ("Receive failed");
        exit(-1);
      }
    Message received_message(0, (void *)message, n, 0, Reply);
    char tmp[32];
    sprintf(tmp, "Received from %s: %d on %d.", inet_ntoa(aSocketAddress.sin_addr), ntohs(aSocketAddress.sin_port), port);
    print(tmp);
    print((const char *) received_message.getMessage());

    close (s);
    return ReceivedMessage(received_message, aSocketAddress);
  }
}
