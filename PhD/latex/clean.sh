#!/bin/bash

CLEANTEMP=$PWD
cd ~/phd/latex
if [ ! $PWD = ~/phd/latex ] ; then cd $CLEANTEMP ; exit 1 ; fi
/bin/rm -f *.fmt *.ps *.pdf *.dvi *.log *.aux *.toc *.bak \#*\# _region_.tex *.bbl *.blg *~ *.ini
/bin/rm -rf *.prv auto
chmod a-x *.tex

cd ~/phd/thesis
if [ ! $PWD = ~/phd/thesis ] ; then cd $CLEANTEMP ; exit 1 ; fi
/bin/rm -f *.fmt *.ps *.pdf *.dvi *.log *.aux *.toc *.bak \#*\# _region_.tex *.bbl *.blg *~ *.ini
/bin/rm -rf *.prv auto
chmod a-x *.tex

cd ~/phd/c

# HACK!!
if [ `uname` = "SunOS" ] ; then
    TEMPDIR=/opt/bin
fi
export PATH=$TEMPDIR:$PATH
make clean

cd $CLEANTEMP
