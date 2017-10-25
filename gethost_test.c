#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#ifndef INADDR_NONE
#define INADDR_NONE -1
#endif

static struct hostent * getHost(char *hostname) {
    struct hostent *h = NULL;
    struct in_addr ipv4addr;
    unsigned long in;
    printf("in getHost\n");

    //if ( (in = inet_addr(hostname)) != INADDR_NONE) {
    if ( (inet_pton(AF_INET, hostname, &ipv4addr)) != INADDR_NONE) {
        printf("inet_addr(hostname) != INADDR_NONE\n");
        if ( (h = gethostbyaddr((char *)&ipv4addr, sizeof(ipv4addr),
                        AF_INET)) == NULL) {
            fprintf(stderr, "gethostbyaddr(2) failed for %s\n", hostname);
        } else {
            printf("gethostbyaddr not NULL\n");
            //printf("h->h_name >>%s<<\n", h->h_name);
        }
    } else if ( (h = gethostbyname(hostname)) == NULL) {
            printf("gethostbyname(hostname) == NULL)\n");
            fprintf(stderr, "gethostbyname(2) failed for %s\n", hostname);
    }
    return (h);

}

int main(int argc, char **argv) {
    struct hostent *he; 
    //char *hostname = "127.0.0.1";
    char *hostname = "localhost";
    he = getHost(hostname);
    printf("getHost he->h_addr returned >>%s<<\n", he->h_addr);

    printf("getHost he->h_name returned >>%s<<\n", he->h_name);

    return 0;
}


