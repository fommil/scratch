#!/bin/bash

#grep '\\cite' abstract.tex thanks.tex introduction.tex pglimits.tex liebranes.tex starformalism.tex fieldtheory.tex conclusion.tex | sed 's|.*\cite{||' | sed 's|}.*||' > allcites.txt

> citessofar.txt
> newbib.tex
while read A ; do
    if [ `grep -c $A citessofar.txt` = 0 ] ; then
        echo $A >> citessofar.txt
        grep $A bib.tex >> newbib.tex
    fi
done < allcites.txt
