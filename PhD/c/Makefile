CC=gcc
CFLAGS+= -s -Wall -pedantic
#CFLAGS=-O3 -fomit-frame-pointer -Wall
# 64 Bit Machines
#CFLAGS=+ "-m64 -DINT64"

all: addfact increment matlab2gnuplot

install: matlab2gnuplot
	install -m 755 matlab2gnuplot $(HOME)/bin/`bash --version | head -n 1 | sed 's|.*(||' | sed 's|\-.*||'`/`uname`/bin

addfact: addfact.c
	${CC} ${CFLAGS} addfact.c -o addfact -lm

increment: increment.c
	${CC} ${CFLAGS} increment.c -o increment -lm

matlab2gnuplot: matlab2gnuplot.c
	${CC} ${CFLAGS} -DMAX=100 -o matlab2gnuplot matlab2gnuplot.c

clean:
	if [ -f addfact ] ; then rm addfact ; fi
	if [ -f increment ] ; then rm increment ; fi
	if [ -f matlab2gnuplot ] ; then rm matlab2gnuplot ; fi
