#!/bin/bash

# NOTE: this function is a waste of time because head has this functionality
antitail()
{
# antitail N <file>
# display a file with N lines removed from the end
    if [ -z "$1" ] || [ -z "$2" ] || [ "$1" = "--help" ] ; then
        echo "usage: antitail N <file>"
        echo 'display a file with N lines removed from the end'
        return 1
    fi
# NEED AN INTEGER CHECK
#    if [ ____$1 is an integer____ ] ; then
#        echo "$1 is either non-positive or is not an integer"
#        return 1
#    fi
    if [ ! -f "$2" ] ; then
        echo "'$2' does not exist."
        return 1
    fi
    if [ `echo $2 | grep -c ':'` -gt 0 ] ; then
        echo 'antitail cannot handle files with : characters in their name.'
        return 1
    fi

#    echo "DEBUGGING \"\$2\" = \"$2\""
    AT_TOTALLINES=`wc -l "$2" | sed "s:$2::" | sed 's: ::g'`
#    echo "DEBUGGING: AT_TOTALLINES = $AT_TOTALLINES"
    if [ $1 -gt $AT_TOTALLINES ] ; then
        echo "Number of lines to clip ($1) is greater than file size ($AT_TOTALLINES)"
        return 1
    fi
    let AT_LINES=$AT_TOTALLINES-$1
#    echo "DEBUGGING: AT_LINES = $AT_LINES"
    head -n $AT_LINES "$2"
}

#M=`head -n 1 /tmp/$USER.addfactM | sed 's/ //g'`
#Q=`head -n 1 /tmp/$USER.addfactQ | sed 's/ //g'`
M=`cat /tmp/$USER.addfactM`
Q=`cat /tmp/$USER.addfactQ`

# pointless optimisation, but saves a needless use of c-code
#OUT="$HOME/work/c/cache/$M-$Q"
OUT="/Users/samuel/Documents/phd/c/cache/$M-$Q"
if [ -f "$OUT.gz" ] ; then
    gzip -cd "$OUT.gz"
else
    /Users/samuel/Documents/phd/c/addfact $Q $M > /tmp/$USER.addfact
    NUMBER=`tail -n 1 /tmp/$USER.addfact`
    #echo "maxk:=$NUMBER;"
    #echo "local K;"
    echo "h:=Matrix(1...$NUMBER,1...$Q):" > "$OUT"
    antitail 1 /tmp/$USER.addfact >> "$OUT"
    cat "$OUT"
    gzip "$OUT"
    rm -f /tmp/$USER.addfact*
fi
