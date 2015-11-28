OBJS = build/main.o
CC = gcc
CFLAGS = -std=c99 -g -c
LFLAGS = -std=c99 -g

$(PROGRAM) : $(OBJS)
	$(CC) -o $(PROGRAM) $^

gsh: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o gsh

build/main.o : src/main.c
	$(CC) $(CFLAGS) src/main.c -o build/main.o

build:
	mkdir -p build/

clean :
	$(RM)  *.o *~
