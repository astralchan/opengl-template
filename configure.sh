#!/bin/sh

# vim: ts=4 sw=4 noet cc=80

# Setup Makefile config with appropriate variables

# build variables
CC=cc
CFLAGS="-std=c99 -O1"
LDFLAGS=$(pkg-config --libs epoxy glfw3)

# install variables
DESTDIR=
PREFIX=/usr/local

for arg; do
	opt=${arg%%=*}
	val=${arg#*=}
	case $opt in
	--cc) CC=$val ;;
	--cflags) CFLAGS=$val ;;
	--ldflags) LDFLAGS=$val ;;
	--destdir) DESTDIR=$val ;;
	--prefix) PREFIX=$val ;;
	--debug) CFLAGS="$CFLAGS -g" ;;
	--reset)
		[ -f Makefile ] && { make clean; mv Makefile Makefile.in; }
		rm -f config.mk
		exit 0
		;;
	*) printf "Unknown option: %s\n" "$val"
	esac
done

cat << _EOF
Configuring...

Build variables:
CC      = $CC
CFLAGS  = $CFLAGS
LDFLAGS = $LDFLAGS

Install variables:
DESTDIR = $DESTDIR
PREFIX  = $PREFIX
_EOF

cat << _EOF > config.mk
# build variables
CC      = $CC
CFLAGS  = $CFLAGS
LDFLAGS = $LDFLAGS

# install variables
DESTDIR = $DESTDIR
PREFIX  = $PREFIX
_EOF

[ -f Makefile.in ] && mv Makefile.in Makefile

exit 0
