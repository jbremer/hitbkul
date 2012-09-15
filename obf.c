#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/syscall.h>

long int syscall(long int syscall_number, long int arg1, long int arg2,
    long int arg3, long int arg4, long int arg5)
{
    long ret = 0;
    __asm__("int $0x80" : "=a" (ret) : "a" (syscall_number),
        "b" (arg1), "c" (arg2), "d" (arg3), "S" (arg4), "D" (arg5));
    return ret;
}

int main(int argc, char *argv[])
{
    printf("a: %ld\n", syscall(SYS_gettid, 0, 0, 0, 0, 0));
}


