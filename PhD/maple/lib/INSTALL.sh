#!/bin/bash

#INSTALLPATH="$HOME/maple/lib"
INSTALLPATH="/Applications/Maple.app/Contents/MacOS/lib"
# For system-wide install, use
# INSTALLPATH=/opt/maple/lib

#SOURCEPATH="$HOME/maple/lib"
SOURCEPATH="$PWD"

################################
cd $SOURCEPATH
rm -f $SOURCEPATH/Commutator.lib \
      $SOURCEPATH/Commutator.ind \
      $SOURCEPATH/Commutator.m \
      $INSTALLPATH/Commutator.lib \
      $INSTALLPATH/Commutator.ind \
      $INSTALLPATH/Commutator.m

sed -e "s:TEMPSTRING:$INSTALLPATH:" Commutator.txt > Commutator.tmp
maple Commutator.tmp
rm -f Commutator.tmp
