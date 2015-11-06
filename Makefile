PROGRAM = gsh
OBJS = main.o
CC = gcc
CFLAGS = -std=c99 -g

$(PROGRAM) : $(OBJS)
	$(CC) -o $(PROGRAM) $^

main.o : main.c
	$(CC) $(CFLAGS) -c $<

clean :
	$(RM)  *.o *~
