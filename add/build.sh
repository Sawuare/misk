#! /bin/sh

# build.sh - build programs and get executables and headers to /usr/local/

# Requires permission to write and execute /usr/local/bin/ and /usr/local/include/,
# which likely requires being the superuser.
#
# All programs depend on the C compiler cc, which may be a link to GCC or Clang.
# Some programs that write PNG files depend on the C libraries libpng and zlib.
#
# To install the dependencies on Debian or a derivative of it, execute
#
#   # apt install clang libpng16-16 libpng-dev zlib1g zlib1g-dev

set -e

cd ../src/

BIN="/usr/local/bin/"
INC="/usr/local/include/"

echo "Copying libraries"

sudo cp --preserve=ownership *.h $INC

echo "Compiling programs"

OPT="-march=native -O3"

cc $OPT -o ctime      ctime.c
cc $OPT -o eca2png    eca2png.c -lpng -lz
cc $OPT -o eca2txt    eca2txt.c
cc $OPT -o eca2wav    eca2wav.c
cc $OPT -o getlocale  getlocale.c
cc $OPT -o hacc       hacc.c
cc $OPT -o hj2fb      hj2fb.c
cc $OPT -o hj2png     hj2png.c -lpng -lz
cc $OPT -o hjjs       hjjs.c
cc $OPT -o hxy        hxy.c -lpng -lz
cc $OPT -o limits     limits.c
cc $OPT -o midi       midi.c -lm
cc $OPT -o morse      morse.c
cc $OPT -o pp         pp.c
cc $OPT -o printable  printable.c
cc $OPT -o projectile projectile.c -lm
cc $OPT -o sumber     sumber.c -lm

echo "Moving programs"

sudo mv ctime eca2png eca2txt eca2wav getlocale hacc hj2fb hj2png hjjs hxy limits midi morse pp printable projectile sumber $BIN

echo "Done"
