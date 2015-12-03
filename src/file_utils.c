#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#include "file_utils.h"

void read_to_stdin(char *fname) {
    int fd = open_for_rdir_in(fname);
    char buf[BUFSIZE];
    int cnt = read(fd, buf, sizeof buf);
		if (cnt < 0) {
		    perror("read");
			  close(fd);
		    exit(1);
		}
    if (write(STDIN_FILENO, buf, cnt) < 0) {
			perror("write");
			close(fd);
			exit(1);
		}
    close(fd);
}

void write_from_stdout(char *fname) {
    int fd = open_for_rdir_out(fname);
    char buf[BUFSIZE];
    int cnt = read(STDOUT_FILENO, buf, sizeof buf);
		if (cnt < 0) {
		    perror("read");
			  close(fd);
		    exit(1);
		}
    if (write(fd, buf, cnt) < 0) {
			perror("write");
			close(fd);
			exit(1);
		}
    close(fd);
}

int open_for_rdir_in(char *fname)
{
    int fd1;
    if ((fd1 = open(fname, O_RDONLY)) < 0) {
        perror("open");
		    exit(1);
    }
    return fd1;
}

int open_for_rdir_out(char *fname)
{
    int fd1;
    if ((fd1 = open(fname, O_WRONLY|O_CREAT|O_EXCL, 0644)) < 0) {
        perror("open");
		    exit(1);
    }
    return fd1;
}
