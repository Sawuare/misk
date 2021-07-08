#! /bin/bash

# make.sh - make and move binaries and headers to /usr/local/

set -e

BIN='/usr/local/bin/'
INC='/usr/local/include/'

# Bash

echo 'Entering ~/prog/bash/'

cd ~/prog/bash/

echo 'Copying Bash programs'

sudo cp --preserve=ownership *.sh $BIN

# C

echo 'Entering ~/prog/c/'

cd ~/prog/c/

echo 'Compiling C programs'

OPT='-std=c11 -march=native -O3'

cc $OPT -fsyntax-only test.c

cc $OPT -o AECA       AECA.c
cc $OPT -o amorse     amorse.c
cc $OPT -o args       args.c
cc $OPT -o ctime      ctime.c
cc $OPT -o fb         fb.c
cc $OPT -o fb2png     fb2png.c    -lpng -lz
cc $OPT -o getendian  getendian.c
cc $OPT -o getlocale  getlocale.c
cc $OPT -o hacc       hacc.c
cc $OPT -o hello      hello.c
cc $OPT -o limits     limits.c
cc $OPT -o morse      morse.c
cc $OPT -o pp         pp.c
cc $OPT -o waves      waves.c     -lFLAC

echo 'Moving C programs'

sudo mv AECA amorse args ctime fb fb2png getendian getlocale hacc hello limits morse pp waves $BIN

echo 'Copying C headers'

sudo cp --preserve=ownership *.h $INC

# Haskell

echo 'Entering ~/prog/haskell/'

cd ~/prog/haskell/

echo 'Compiling Haskell program'

ghc -v0 -O -o QDA QDA.hs

rm QDA.hi QDA.o

echo 'Moving Haskell program'

sudo mv QDA $BIN

# Python

echo 'Entering ~/prog/python/'

cd ~/prog/python/

echo 'Copying Python programs'

sudo cp --preserve=ownership *.py $BIN

echo 'Done'
