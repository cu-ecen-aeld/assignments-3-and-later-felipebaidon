#!/bin/bash

if [ $# -lt 2 ]; then
	echo "Unsuficient arguments"
	exit 1
fi

WRITEFILE=$1
WRITESTR=$2

PATHNAME=$(dirname $WRITEFILE)

if [ ! -d $PATHNAME ]; then
	mkdir -p $PATHNAME
fi

echo $WRITESTR > $WRITEFILE
