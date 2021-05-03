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

cc -std=c17 -fsyntax-only                        test.c &&
cc -std=c17                     -O -o AECA       AECA.c &&
cc -std=c17                     -O -o args       args.c &&
cc -std=c17                     -O -o fb         fb.c &&
cc -std=c17               -lpng -O -o fb2png     fb2png.c &&
cc -std=c17                     -O -o fibonaccis fibonaccis.c &&
cc -std=c17                     -O -o getendian  getendian.c &&
cc -std=c17                     -O -o getlocale  getlocale.c &&
cc -std=c17                     -O -o hacc       hacc.c &&
cc -std=c17                     -O -o hello      hello.c &&
cc -std=c17                     -O -o limits     limits.c &&
cc -std=c17                     -O -o morse      morse.c &&
cc -std=c17                     -O -o padovans   padovans.c &&
cc -std=c17                     -O -o pp         pp.c &&
cc -std=c17               -lm   -O -o projectile projectile.c &&
cc -std=c17                     -O -o sudoku     sudoku.c &&
cc -std=c17               -lm   -O -o waves      waves.c

is_ok

echo -n "Moving C programs...         "

sudo mv AECA args fb fb2png fibonaccis getendian getlocale hacc hello limits morse padovans pp projectile sudoku waves /usr/local/bin/

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

sudo cp --preserve=ownership ECA.py MTS.py print.py /usr/local/bin/

is_ok
