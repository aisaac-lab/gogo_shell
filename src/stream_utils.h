#ifndef STREAM_UTILS_H_
#define STREAM_UTILS_H_
void stream_utils_write(char *mes, int fd);
void stream_utils_read(int fd);
void stream_utils_attach_skt(int pfd_n, int fd);
#endif
