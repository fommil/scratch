CC=gcc
CFLAGS+= -s -Wall -pedantic -Werror -std=c99

all: 100 126 160

100: 100.c
	${CC} ${CFLAGS} 100.c -o 100

126: 126.c
	${CC} ${CFLAGS} 126.c -o 126

160: 160.c
	${CC} ${CFLAGS} 160.c -o 160

indent:
	indent -br *.c
	rm *.c~

clean:
	if [ -f 100 ] ; then rm 100 ; fi
	if [ -f 126 ] ; then rm 126 ; fi
	if [ -f 160 ] ; then rm 160 ; fi
