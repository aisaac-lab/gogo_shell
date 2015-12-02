OBJS = build/main.o build/read_line.o build/get_tokens.o build/parse_cmd.o build/process_utils.o
#  build/stream_utils.o
CC = gcc
CFLAGS = -std=c99 -g -c
LFLAGS = -std=c99 -g

$(PROGRAM) : $(OBJS)
	$(CC) -o $(PROGRAM) $^

gsh: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o gsh

build/main.o : src/main.c
	$(CC) $(CFLAGS) src/main.c -o build/main.o

build/read_line.o : src/read_line.c
	$(CC) $(CFLAGS) src/read_line.c -o build/read_line.o

build/get_tokens.o : src/get_tokens.c
	$(CC) $(CFLAGS) src/get_tokens.c -o build/get_tokens.o

build/parse_cmd.o : src/parse_cmd.c
	$(CC) $(CFLAGS) src/parse_cmd.c -o build/parse_cmd.o

build/process_utils.o : src/process_utils.c
	$(CC) $(CFLAGS) src/process_utils.c -o build/process_utils.o

build:
	mkdir -p build/

clean :
	rm -rf  build/
