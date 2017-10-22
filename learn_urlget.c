/*   Example: learn_urlget -p 8080 -x my-proxy.my.site http://www.from.here 
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>


#define LEAST_SIZE_PROGRESS BUFSIZE
#define BUFSIZE (2048 * 5)

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

#include <stdio.h>

/* sendf() sends the str to the server */
static int sendf(int fd, struct UrlData *data, char *str) {
    char s[1024];

    return (send(fd, s, strlen(s), 0));
}

int main(int argc, char **argv) {
    char *str = "hello there";
    struct UrlData *data;
    data = malloc(sizeof(struct UrlData));

    if (data) {
        memset(data, 0, sizeof(struct UrlData));
        // set some defaults...
        data->out = stdout;
        data->in = stdin;
        data->firstsocket = -1; // no file descriptor
        // use fwrite as default function to store output
        data->fwrite = (size_t (*)(char *, int, int, FILE *))fwrite;
        
    }

    int ret = sendf(fd, data, str);      
    return 0;
}

