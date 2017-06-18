CC = gcc
CFLAGS = -Wall -ggdb -Wextra -Wpedantic -std=c99 
OBJS = main.o helper.o node.o btree.o queue.o queuell.o 
PROG = ex
LOCALLIBDIR = /usr/local/lib
LDFLAGS = -L$(LOCALLIBDIR)
LDLIBS = 

all: $(PROG) testq test


$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

testq: testq.o helper.o node.o queuell.o
	$(CC) $(CFLAGS) $? -o $@ $(LDFLAGS) $(LDLIBS)

test: test.o helper.o node.o btree.o queue.o queuell.o 
	$(CC) $(CFLAGS) $? -o $@ $(LDFLAGS) $(LDLIBS)



main.o: main.c
testq.o: testq.c
test.o: test.c
btree.o: btree.h
node.o: node.h
queue.o: queue.h
queuell.o: queuell.h
helper.o: helper.h


clean:
	rm -f *~ *.o $(PROG) core a.out testq test

valg: $(PROG)
	valgrind -v --leak-check=full ./$(PROG)

valgq:
	valgrind -v --leak-check=full ./testq

valgt:
	valgrind -v --leak-check=full ./test

clang:
	scan-build make all
