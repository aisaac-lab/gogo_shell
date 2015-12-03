#ifndef FILE_UTILS_H_
#define FILE_UTILS_H_

#define BUFSIZE 1024

void read_to_stdin(char *fname);
void write_from_stdout(char *fname);
int open_for_rdir_in(char *fname);
int open_for_rdir_out(char *fname);

#endif
