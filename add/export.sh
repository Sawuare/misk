#! /bin/sh

# export.sh - export the output of some programs to ../out/

set -e

cd ../out/

echo "Exporting output"

# Assume that build.sh has been executed
hjjs
midi      > midi.txt
printable > printable.txt

echo "Done"
