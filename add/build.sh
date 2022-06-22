#! /bin/sh

# build.sh - build some programs and get executables and headers to /usr/local/

# Requires permission to write and execute /usr/local/bin/ and /usr/local/include/,
# which likely requires being the superuser.
#
# Some programs depend on some of these compilers, interpreters, and libraries:
#
#   cc (as either Clang or GCC)
#
#   python3
#
#   libpng
#   zlib
#
# To install them on Debian or a derivative of it, execute
#
#   # apt install clang python3 libpng16-16 libpng-dev zlib1g zlib1g-dev

set -e

echo "Entering ../src/"

cd ../src/

BIN="/usr/local/bin/"
INC="/usr/local/include/"

# Python

echo "Copying Python programs"

OPT="--preserve=ownership"

sudo cp $OPT hjjs.py       $BIN/hjjs
sudo cp $OPT printable.py  $BIN/printable
sudo cp $OPT projectile.py $BIN/projectile

# C

echo "Copying C headers"

sudo cp $OPT *.h $INC

echo "Compiling C programs"

OPT="-march=native -O3"

cc $OPT -o ctime     ctime.c
cc $OPT -o eca2png   eca2png.c -lpng -lz
cc $OPT -o eca2txt   eca2txt.c
cc $OPT -o eca2wav   eca2wav.c
cc $OPT -o getendian getendian.c
cc $OPT -o getlocale getlocale.c
cc $OPT -o hacc      hacc.c
cc $OPT -o hj2fb     hj2fb.c
cc $OPT -o hj2png    hj2png.c -lpng -lz
cc $OPT -o limits    limits.c
cc $OPT -o midi      midi.c -lm
cc $OPT -o morse     morse.c
cc $OPT -o pp        pp.c
cc $OPT -o qda       qda.c -lm

echo "Moving C programs"

sudo mv ctime eca2png eca2txt eca2wav getendian getlocale hacc hj2fb hj2png limits midi morse pp qda $BIN

echo "Done"
