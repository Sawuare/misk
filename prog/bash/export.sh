#! /bin/bash

# export.sh - export data to ~/data/

set -e

echo 'Entering ~/data/'

cd ~/data/

echo 'Exporting data'

# Assume make.sh has been run
fbzs.py
getendian > endian.txt
getlocale > locale.txt
hah.py    > hah.txt
limits    > limits.txt
mts.py    > mts.txt
print.py  > print.txt
sudoku.py > sudoku.txt
waves

echo 'Done'
