CC=gcc
CFLAGS+= -s -Wall -pedantic

all: psfto8x16c charset

charset: charset.c
	${CC} ${CFLAGS} charset.c -o charset

psfto8x16c: psfto8x16c.c unicodes_iso.h
	${CC} ${CFLAGS} psfto8x16c.c -o psfto8x16c

clean:
	if [ -f psfto8x16c ] ; then rm psfto8x16c ; fi
	if [ -f charset ] ; then rm charset ; fi
