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

echo -n "Entering ~/prog/bash/     "

cd ~/prog/bash/

is_ok

echo -n "Copying Bash programs     "

sudo cp --preserve=ownership *.sh $BIN

is_ok

# C

echo -n "Entering ~/prog/c/        "

cd ~/prog/c/

is_ok

echo -n "Compiling C programs      "

OPT="-std=c17 -O"

cc $OPT       -fsyntax-only test.c      &&

cc $OPT       -o AECA       AECA.c      &&
cc $OPT       -o amorse     amorse.c    &&
cc $OPT       -o args       args.c      &&
cc $OPT       -o fb         fb.c        &&
cc $OPT -lpng -o fb2png     fb2png.c    &&
cc $OPT       -o getendian  getendian.c &&
cc $OPT       -o getlocale  getlocale.c &&
cc $OPT       -o hacc       hacc.c      &&
cc $OPT       -o hello      hello.c     &&
cc $OPT       -o limits     limits.c    &&
cc $OPT       -o morse      morse.c     &&
cc $OPT       -o pp         pp.c        &&
cc $OPT -lm   -o waves      waves.c

is_ok

echo -n "Moving C programs         "

sudo mv AECA amorse args fb fb2png getendian getlocale hacc hello limits morse pp waves $BIN

is_ok

echo -n "Copying C headers         "

sudo cp --preserve=ownership *.h $INC

is_ok

# Haskell

echo -n "Entering ~/prog/haskell/  "

cd ~/prog/haskell/

is_ok

echo -n "Compiling Haskell program "

ghc -v0 -O -o QDA QDA.hs

is_ok

rm QDA.hi QDA.o

echo -n "Moving Haskell program    "

sudo mv QDA $BIN

is_ok

# Python

echo -n "Entering ~/prog/python/   "

cd ~/prog/python/

is_ok

echo -n "Copying Python programs   "

sudo cp --preserve=ownership *.py $BIN

is_ok
