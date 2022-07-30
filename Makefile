# vim: ts=4 sw=4 noet cc=80

.POSIX:

# build vars
LDFLAGS = `pkg-config --libs epoxy glfw3`

# build rules
all: triangle
triangle: triangle.o util.o renderer.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ triangle.o util.o renderer.o
triangle.o: triangle.c util.h
util.o: util.c util.h
renderer.o: renderer.c renderer.h util.h
clean:
	@rm -f prog triangle triangle.o util.o renderer.o

# install rules
install:
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp triangle $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/triangle
uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/triangle
