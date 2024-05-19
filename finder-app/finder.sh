#!/bin/sh

echo "Path: $1";
echo "SearchString: $2";


# Check if the correct number of arguments are passed
if [ $# -lt 2 ]
then 
	echo "Wrong Arguments"
	exit 1
fi
Path=$1
SearchString=$2

# Check if the path does not exist
if [ ! -d $Path ]
then
	echo "Wrong Path"
	exit 1
fi

# Count files and find matching lines
file_count=$(find "$Path" -type f | wc -l)
match_count=$(grep -r "$SearchString" "$Path" | wc -l)

# print the output
echo "The number of files are $file_count and the number of matching lines are $match_count"
  

