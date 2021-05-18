#! /bin/bash

# make.sh - make and move programs and headers to /usr/local/

function is_ok {
	if [ $? ]
	then
		echo "OK!"
	else
		exit
	fi
}

# Bash

cd ~/prog/bash/

echo -n "Copying Bash programs...     "

sudo cp --preserve=ownership archive.sh make.sh /usr/local/bin/

is_ok

# C

cd ~/prog/c/

echo -n "Compiling C programs...      "

OPT="-std=c17 -O"

cc $OPT       -fsyntax-only test.c &&

cc $OPT       -o AECA       AECA.c &&
cc $OPT       -o amorse     amorse.c &&
cc $OPT       -o args       args.c &&
cc $OPT       -o fb         fb.c &&
cc $OPT -lpng -o fb2png     fb2png.c &&
cc $OPT       -o getendian  getendian.c &&
cc $OPT       -o getlocale  getlocale.c &&
cc $OPT       -o hacc       hacc.c &&
cc $OPT       -o hello      hello.c &&
cc $OPT       -o limits     limits.c &&
cc $OPT       -o morse      morse.c &&
cc $OPT       -o pp         pp.c &&
cc $OPT -lm   -o waves      waves.c

is_ok

echo -n "Moving C programs...         "

sudo mv AECA amorse args fb fb2png getendian getlocale hacc hello limits morse pp waves /usr/local/bin/

is_ok

echo -n "Copying C headers...         "

sudo cp --preserve=ownership DECTCEM.h ECMA-48.h fade.h fb.h macros.h /usr/local/include/

is_ok

# Haskell

cd ~/prog/haskell/

echo -n "Compiling Haskell program... "

ghc -v0 -O -o QDA QDA.hs

is_ok

rm QDA.hi QDA.o

echo -n "Moving Haskell program...    "

sudo mv QDA /usr/local/bin/

is_ok

# Python

cd ~/prog/python

echo -n "Copying Python programs...   "

sudo cp --preserve=ownership ECA.py MTS.py fibonaccis.py hah.py padovans.py print.py projectile.py sudoku.py /usr/local/bin/

is_ok
