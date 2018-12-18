CC = gcc
CFLAGS = -I.
# DEPS = 
CLEANFILES = core core.* *.core *.o temp.* *.out

PROGS = k-mean 

all: ${PROGS}


k-mean: k-mean.o 
	$(CC) $(CFLAGS) -o $@ k-mean.o



.PHONY: clean
clean:
	rm -f $(PROGS) $(CLEANFILES)

# CC=gcc
# CFLAGS=-I.
# DEPS = hellomake.h

# %.o: %.c $(DEPS)
# 	$(CC) -c -o $@ $< $(CFLAGS)

# hellomake: hellomake.o hellofunc.o 
# 	$(CC) -o hellomake hellomake.o hellofunc.o 