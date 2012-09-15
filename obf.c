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

int Main()
{
    syscall0(SYS_exit);
    return 0;
}


