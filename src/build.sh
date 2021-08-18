#! /bin/sh

# build.sh - build some sources and get executables and headers to /usr/local/

set -e

BIN="/usr/local/bin/"
INC="/usr/local/include/"

# C

echo "Compiling C programs"

OPT="-std=c11 -march=native -O3 -Wno-dangling-else"

cc $OPT -fsyntax-only test.c

cc $OPT -o aeca       aeca.c
cc $OPT -o amorse     amorse.c
cc $OPT -o ctime      ctime.c
cc $OPT -o fb         fb.c
cc $OPT -o fb2png     fb2png.c    -lpng -lz
cc $OPT -o getendian  getendian.c
cc $OPT -o getlocale  getlocale.c
cc $OPT -o hacc       hacc.c
cc $OPT -o limits     limits.c
cc $OPT -o morse      morse.c
cc $OPT -o pp         pp.c
cc $OPT -o waves      waves.c     -lFLAC

echo "Moving C programs"

sudo mv aeca amorse ctime fb fb2png getendian getlocale hacc limits morse pp waves $BIN

echo "Copying C headers"

sudo cp --preserve=ownership *.h $INC

# Haskell

echo "Compiling Haskell program"

ghc -no-keep-hi-files -no-keep-o-files -v0 -O2 -o qda qda.hs

echo "Moving Haskell program"

sudo mv qda $BIN

# Python

echo "Copying Python programs"

sudo cp --preserve=ownership *.py $BIN

echo "Done"
