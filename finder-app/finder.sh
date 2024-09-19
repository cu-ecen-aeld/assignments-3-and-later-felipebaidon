#!/bin/sh
if [ $# -lt 2 ]; then 
	echo "Unsuficient arguments"
	exit 1
fi

FILESDIR=$1
SEARCHSTR=$2

if [ ! -d "$FILESDIR" ]; then
	echo "Directory does not exist."
	exit 1
else
	NOFILES=$(find $FILESDIR -type f | wc -l)
	NOMATCH=$(grep -r $SEARCHSTR $FILESDIR | wc -l)
	echo "The number of files are $NOFILES and the number of matching lines are $NOMATCH"
fi

