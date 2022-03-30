#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>


int main(int argc, char** argv) {

    system("clear");

    if (argc == 1) {
        fprintf(stderr, "No arguments supplied...\n");
        return 1;
    }

    struct addrinfo hints, *ai, *ai0;
	int i;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = PF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    char buffer[1000];
    memset(buffer, 0, 1000);


    for (int j=1; j<argc; j++) {

        if ((i = getaddrinfo(argv[j], "80", &hints, &ai0)) != 0) { 
            printf("Error: unable to lookup IP address %s", gai_strerror(i));
            return 1;
        }

        
        for (ai=ai0; ai!=NULL; ai=ai->ai_next) {

            if (ai -> ai_family == AF_INET) {
                inet_ntop(ai->ai_family, &(((struct sockaddr_in *) ai->ai_addr)->sin_addr), buffer, 1000);
                printf("%s IPv4 %s\n",argv[j], buffer);

            } else if (ai -> ai_family == AF_INET6) {
                inet_ntop(ai->ai_family, &(((struct sockaddr_in6 *) ai->ai_addr)->sin6_addr), buffer, 1000);
                printf("%s IPv6 %s\n",argv[j], buffer);
            
            } else {
                printf("Unknown address family...");
                return 1;
            }
        }
    }
     return 0;
}