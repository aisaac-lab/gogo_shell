OBJS = build/main.o build/stream_utils.o
CC = gcc
CFLAGS = -std=c99 -g -c
LFLAGS = -std=c99 -g

$(PROGRAM) : $(OBJS)
	$(CC) -o $(PROGRAM) $^

gsh: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o gsh

build/main.o : src/main.c
	$(CC) $(CFLAGS) src/main.c -o build/main.o

build/stream_utils.o : src/stream_utils.c
	$(CC) $(CFLAGS) src/stream_utils.c -o build/stream_utils.o

build:
	mkdir -p build/

clean :
	$(RM)  *.o *~
