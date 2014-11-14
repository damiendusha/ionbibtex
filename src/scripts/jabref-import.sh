#!/bin/bash

SELF=`basename "$0"`
PROCESSES=`ps aux | grep jabref | grep -v grep | grep -v "$SELF" | grep -c jabref`

if [ $PROCESSES -eq 0 ] ; then
    echo "ERROR: Jabref must be opened first"
    exit 1
fi

echo "Importing contents with filename $1"
echo "Contents:"
cat $1

`which jabref` -i --importToOpen "$*"
