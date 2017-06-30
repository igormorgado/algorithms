CC = gcc
CFLAGS = -Wall -ggdb -Wextra -Wpedantic -std=c99 
OBJS = abb.o
PROG = abb
LOCALLIBDIR = /usr/local/lib
LDFLAGS = -L$(LOCALLIBDIR)
LDLIBS = 

all: $(PROG) 


$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)


abb.o: abb.c


clean:
	rm -f *~ *.o $(PROG) core a.out 

valg: $(PROG)
	valgrind -v --leak-check=full ./$(PROG)

clang:
	scan-build make all
