/*   Example: learn_urlge -p 8080 -x my-proxy.my.site http://www.from.here 
 */
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

#define LEAST_SIZE_PROGRESS BUFSIZE
#define BUFSIZE (2048 * 5)

typedef enum {
    URG_OK = 0,
    URG_COULDNT_CONNECT,
    URG_COULDNT_RESOLVE_HOST
} UrgError;

/* config struct */
struct UrlData {
    FILE *out;  // the fetched file goes here
    FILE *in;   // the uploaded file is read from here
    char *url;  // what to get
    unsigned short port;  // which port to use

    // function that stores the output
    size_t (*fwrite) (char *buffer,
                      int size,
                      int nitems,
                      FILE *outstream);
    // function that reads the input
    size_t (*fread)(char *buffer,
                    int size,
                    int nitems,
                    FILE *outstream);
    long timeout;  // in seconds, 0 means no timeout
    // fields only set and used without _urlget()
    int firstsocket;    // the main socket to use
    int secondarysocket;// for i.e ftp transfers
    char buffer[BUFSIZE+1];
};

static void infof(struct UrlData *data, char *fmt, ...) {
    int verbose = 1;
    if (verbose)
        printf("verbose: ");
    fprintf(stderr, fmt);
}

#ifndef INADDR_NONE
#define INADDR_NONE -1
#endif
static struct hostent * GetHost(struct UrlData *data, char *hostname) {
    struct hostent *h = NULL;
    unsigned long in;

    if ( (in = inet_addr(hostname)) != INADDR_NONE) {
        if ( (h = gethostbyaddr((char *)&in, sizeof(in),
                        AF_INET)) == NULL) {
            infof(data, "gethostbyaddr(2) failed for %s\n", hostname);
        }
    } else if ( (h = gethostbyname(hostname)) == NULL) {
            infof(data, "gethostbyname(2) failed for %s\n", hostname);
    }
    return (h);
}


/* sendf() sends the str to the server */
static int sendf(int fd, struct UrlData *data, char *str) {
    char s[1024];

    printf("sending %s\n", s);
    return (send(fd, s, strlen(s), 0));
}

/* This is where a lot of the action happens */

static UrgError _urlget(struct UrlData *data) {
    struct hostent *he;
    struct hostent *hp = NULL;
    struct sockaddr_in serv_addr;
    char path[512]="/";
    char *buf;
    size_t nread;
    buf = data->buffer;
    // short circuit...
    int local = 1;
    int web = 1;
    char * name = "127.0.0.1";
    if (web)
        data->port = 80;

    data->url = "/";
    if (!(hp = GetHost(data, name))) {
        fprintf(stderr, "Could not resolve %s", name);
        return URG_COULDNT_RESOLVE_HOST;
    }

    data->firstsocket = socket(AF_INET, SOCK_STREAM, 0);
    memset((char*) &serv_addr, '\0', sizeof(serv_addr));
    memcpy((char*) &(serv_addr.sin_addr), 
            hp->h_addr, hp->h_length);
    serv_addr.sin_family = hp->h_addrtype;
    serv_addr.sin_port = htons(data->port);
    if (connect(data->firstsocket, 
                (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        if (errno) {
            fprintf(stderr, "Could not connect to server\n");
            return URG_COULDNT_CONNECT;
        }
    }
        
    char *str = "hello";
    int ret = sendf(data->firstsocket, data, str);      
    //TODO: implement
    return ret;
}

void urlfree(struct UrlData *data) {
    if (-1 != data->secondarysocket)
        close(data->secondarysocket);
    if (-1 != data->firstsocket)
        close(data->firstsocket);
    free(data);
}

int main(int argc, char **argv) {
    char *str = "hello there";
    struct UrlData *data;
    int res;

    data = malloc(sizeof(struct UrlData));

    if (data) {
        memset(data, 0, sizeof(struct UrlData));
        // set some defaults...
        data->out = stdout;
        data->in = stdin;
        data->firstsocket = -1; // no file descriptor
        // use fwrite as default function to store output
        data->fwrite = (size_t (*)(char *, int, int, FILE *))fwrite;
        // use fread as default function to read input
        data->fread = (size_t (*)(char *, int, int, FILE *))fread;

    }
    res= _urlget(data);

    urlfree(data);
    return 0;
}

