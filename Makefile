#
# Makefile for keycut.c
#
CC	= gcc
CCOPTS	= -O2
IDIR	=.
CFLAGS	=-I$(IDIR) $(CCOPTS)
LDFLAGS	= -L ./
LIBS	=
DEPS	=
OBJS	= keycut.o

%.o:		%.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

all:	keycut

keycut:		$(OBJS)
		$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *~ *.o core

cleanall:
	rm -f *~ *.o core keycut

install:
	install -s keycut /usr/local/sbin
