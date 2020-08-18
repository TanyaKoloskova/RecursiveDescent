#!/bin/bash
FILE=test_strings
while read LINE; do
	PREV_LINE=$LINE && read LINE && echo -e "$LINE\tCALCULATOR:\c" &&
	RESULT=$(./calculator " $PREV_LINE" 2>&1)
	echo -e "$RESULT\c" && echo -e "\tEXPRESSION:$PREV_LINE" 
done < $FILE
