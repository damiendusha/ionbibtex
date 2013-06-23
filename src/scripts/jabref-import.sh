#!/bin/bash

echo "Importing contents with filename $1"
echo "Contents:"
cat $1

`which jabref` -i --importToOpen "$*"
