#! /bin/sh

# output.sh - put the output of some programs in ../out/

set -e

cd ../out/

echo "Outputting"

# Assume that build.sh has been executed
hqz-seq
midi      > midi.txt
printable > printable.txt

echo "Done"
