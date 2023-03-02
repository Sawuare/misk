#! /bin/sh

# output.sh - put the output of some programs in ../out/

# Assumes that build.sh has been executed.

set -e

echo "Outputting"

cd ../out/

midi      > midi.txt
printable > printable.txt

cd hpq-seq/

hpq-seq

echo "Done"
