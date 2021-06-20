#! /bin/bash

# make.sh - make and move binaries and headers to /usr/local/

function is_ok {
	if [ $? ]
	then
		echo "OK!"
	else
		exit
	fi
}

BIN=/usr/local/bin/
INC=/usr/local/include/

# Bash

echo "Entering ~/prog/bash/"

cd ~/prog/bash/

is_ok

echo "Copying Bash programs"

sudo cp --preserve=ownership *.sh $BIN

is_ok

# C

echo "Entering ~/prog/c/"

cd ~/prog/c/

is_ok

echo "Compiling C programs"

OPT="-std=c17 -march=native -O3"

cc $OPT       -fsyntax-only test.c      &&

cc $OPT        -o AECA       AECA.c      &&
cc $OPT        -o amorse     amorse.c    &&
cc $OPT        -o args       args.c      &&
cc $OPT        -o fb         fb.c        &&
cc $OPT -lpng  -o fb2png     fb2png.c    &&
cc $OPT        -o getendian  getendian.c &&
cc $OPT        -o getlocale  getlocale.c &&
cc $OPT        -o hacc       hacc.c      &&
cc $OPT        -o hello      hello.c     &&
cc $OPT        -o limits     limits.c    &&
cc $OPT        -o morse      morse.c     &&
cc $OPT        -o pp         pp.c        &&
cc $OPT -lFLAC -o waves      waves.c

is_ok

echo "Moving C programs"

sudo mv AECA amorse args fb fb2png getendian getlocale hacc hello limits morse pp waves $BIN

is_ok

echo "Copying C headers"

sudo cp --preserve=ownership *.h $INC

is_ok

# Haskell

echo "Entering ~/prog/haskell/"

cd ~/prog/haskell/

is_ok

echo "Compiling Haskell program"

ghc -v0 -O -o QDA QDA.hs

is_ok

rm QDA.hi QDA.o

echo "Moving Haskell program"

sudo mv QDA $BIN

is_ok

# Python

echo "Entering ~/prog/python/"

cd ~/prog/python/

is_ok

echo "Copying Python programs"

sudo cp --preserve=ownership *.py $BIN

is_ok
