CC = gcc
CFLAGS = -Wall -ggdb -Wextra -Wpedantic -std=c99 
OBJS = main.o listalinear.o listadupla.o noarv.o abb.o elem.o helper.o node.o btree.o queue.o queuell.o 
PROG = main

BOBJS = bmain.o helper.o node.o btree.o queue.o queuell.o 
BPROG = bmain

LOCALLIBDIR = /usr/local/lib
LDFLAGS = -L$(LOCALLIBDIR)
LDLIBS = 

all: $(PROG) $(BPROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

$(BPROG): $(BOBJS)
	$(CC) $(CFLAGS) $(BOBJS) -o $@ $(LDFLAGS) $(LDLIBS)

abb.o: abb.c 
bmain.o: bmain.c
btree.o: btree.c 
elem.o: elem.c
helper.o: helper.c 
listadupla.o: listadupla.c
listalinear.o: listalinear.c
main.o: main.c
noarv.o: noarv.c
node.o: node.c 
queuell.o: queuell.c
queue.o: queue.c 
test.o: test.c
testq.o: testq.c

clean:
	rm -f *~ *.o $(PROG) $(BPROG) core a.out 

valg: $(PROG)
	valgrind -v --leak-check=full ./$(PROG)

valgb: $(BPROG)
	valgrind -v --leak-check=full ./$(BPROG)

clang:
	scan-build make all

