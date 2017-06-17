CC = gcc
CFLAGS = -Wall -ggdb -Wextra -Wpedantic -std=c99 
OBJS = main.o node.o btree.o queue.o queuell.o 
PROG = bt 
LOCALLIBDIR = /usr/local/lib
LDFLAGS = -L$(LOCALLIBDIR)
LDLIBS = 

all: $(PROG) qllt


$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

qllt: qmain.o node.o queuell.o
	$(CC) $(CFLAGS) $? -o $@ $(LDFLAGS) $(LDLIBS)

qmain.o: qmain.c
main.o: main.c
btree.o: btree.h
node.o: node.h
queue.o: queue.h
queuell.o: queuell.h

clean:
	rm -f *~ *.o $(PROG) core a.out qltt

valg: $(PROG)
	valgrind -v --leak-check=full ./$(PROG)

valgq:
	valgrind -v --leak-check=full ./qllt

clang:
	scan-build make all
