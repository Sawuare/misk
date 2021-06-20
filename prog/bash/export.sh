#! /bin/bash

# export.sh - export data to ~/data/

function is_ok {
	if [ $? ]
	then
		echo "OK!"
	else
		exit
	fi
}

echo "Entering ~/data/"

cd ~/data/

is_ok

echo "Exporting data"

MTS.py    > MTS.txt    &&
fbzs.py                &&
getendian > endian.txt &&
getlocale > locale.txt &&
hah.py    > hah.txt    &&
hello     > hello.txt  &&
limits    > limits.txt &&
print.py  > print.txt  &&
sudoku.py > sudoku.txt &&
waves

is_ok
