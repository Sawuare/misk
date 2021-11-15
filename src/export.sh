#! /bin/sh

# export.sh - export the output of some programs to ../dat/

set -e

echo "Entering ../dat/"

cd ../dat/

echo "Exporting data"

# Assume that build.sh has been executed
hjjs.py
mts.py   > mts.txt
print.py > print.txt
waves

echo "Done"
