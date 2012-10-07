#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <fcntl.h>

__attribute__((always_inline))
long syscall(long syscall_number, long arg1, long arg2, long arg3, long arg4,
    long arg5)
{
    long ret = 0;
    __asm__("int $0x80" : "=a" (ret) : "a" (syscall_number),
        "b" (arg1), "c" (arg2), "d" (arg3), "S" (arg4), "D" (arg5));
    return ret;
}

long syscall0(long syscall_number)
{
    return syscall(syscall_number, 0, 0, 0, 0, 0);
}

long syscall1(long syscall_number, long arg1)
{
    return syscall(syscall_number, arg1, 0, 0, 0, 0);
}

long syscall2(long syscall_number, long arg1, long arg2)
{
    return syscall(syscall_number, arg1, arg2, 0, 0, 0);
}

long syscall3(long syscall_number, long arg1, long arg2, long arg3)
{
    return syscall(syscall_number, arg1, arg2, arg3, 0, 0);
}

long syscall4(long syscall_number, long arg1, long arg2, long arg3, long arg4)
{
    return syscall(syscall_number, arg1, arg2, arg3, arg4, 0);
}

#define write(a, b, c) syscall3(SYS_write, a, (long) b, c)
#define open(a, b) syscall2(SYS_open, (long) a, b)
#define lseek(a, b, c) syscall3(SYS_lseek, a, b, c)
#define close(a) syscall1(SYS_close, a)
#define socket(a, b, c) syscall3(SYS_socket, a, b, c)
#define bind(a, b) syscall2(SYS_bind, a, (long) b)
#define listen(a, b) syscall2(SYS_listen, a, b)
#define accept(a, b, c) syscall3(SYS_accept, a, (long) b, c)

void error(const char *func, const char *msg)
{
    write(2, func, strlen(func));
    write(2, ": ", 2);
    write(2, msg, strlen(msg));
    write(2, "\n", 1);
    syscall0(SYS_exit);
}

unsigned short htons(unsigned short value)
{
    return ((value & 0xff) << 8) + (value >> 8);
}

int Main()
{
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sfd < 0) {
        error("socket", "error opening a socket");
    }

    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(51337);

    if(bind(sfd, &addr, sizeof(addr)) < 0) {
        error("bind", "error binding socket to address");
    }

    if(listen(sfd, 5) < 0) {
        error("listen", "error listening on socket");
    }

    int a = SYS_socketcall;

    while (1) {
        int cfd = accept(sfd, NULL, 0);
        if(cfd < 0) break;

        // do stuff
    }

    syscall0(SYS_exit);
    return 0;
}
