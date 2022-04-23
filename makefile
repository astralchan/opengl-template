# vim: ts=4 sw=4 noet cc=80

.POSIX:

# Build variables
CC       = gcc
CFLAGS   = -std=c99 -O1 -g
LDFLAGS != pkg-config --libs epoxy glfw3

# Build targets
all: prog
prog: main.o util.o renderer.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ main.o util.o renderer.o
main.o: main.c util.h renderer.h
util.o: util.c util.h
renderer.o: renderer.c renderer.h
clean:
	@rm -f prog main.o util.o renderer.o

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $<
