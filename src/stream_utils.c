#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void
stream_utils_write(char *mes, int fd)
{
    write(fd, mes, strlen(mes));
}

void
stream_utils_read(int fd)
{
    char buf[128];
    read(fd, buf, sizeof(char) * 128);
    printf("%s\n", buf);
}

void
stream_utils_attach_skt(int pfd_n, int fd)
{
    close(fd);
    dup2(pfd_n, fd);
    close(pfd_n);
}
