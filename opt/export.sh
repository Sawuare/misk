#! /bin/sh

# export.sh - export the output of some programs to ../dat/

set -e

echo "Entering ../dat/"

cd ../dat/

echo "Exporting data"

# Assume that build.sh has been executed
hjjs
midi      > midi.txt
printable > printable.txt
waves

echo "Done"
