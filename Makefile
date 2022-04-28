# vim: ts=4 sw=4 noet cc=80

.POSIX:

# Build variables
CC       = gcc
CFLAGS   = -std=c99 -O1 -g
LDFLAGS != pkg-config --libs epoxy glfw3

# Build targets
all: prog
prog: main.c util.o renderer.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ main.c util.o renderer.o
util.o: util.c util.h
renderer.o: renderer.c renderer.h util.h
clean:
	@rm -f prog util.o renderer.o

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $<
