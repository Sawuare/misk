#! /bin/sh

# build.sh - build some programs and get executables and headers to /usr/local/

# Requires permission to write and execute /usr/local/bin/ and /usr/local/include/,
# which likely requires being the superuser.
#
# Some programs depend on some of these compilers, interpreters, and libraries:
#
#   cc  (as either Clang or GCC)
#   ghc (as the Galsgow Haskell Compiler)
#
#   python3
#
#   libFLAC
#   libpng
#   zlib
#
# To install them on Debian or a derivative of it, execute
#
#   # apt install clang ghc python3 libflac8 libflac-dev libpng16-16 libpng-dev \
#   > zlib1g zlib1g-dev
#
# The external program "aplay", an ALSA utility, is recommended but not a dependency.
# The programs aeca and amorse use it to play raw audio files. To install it, execute
#
#   # apt install alsa-utils

set -e

echo "Entering ../src/"

cd ../src/

BIN="/usr/local/bin/"
INC="/usr/local/include/"

# Python

echo "Copying Python programs"

OPT="--preserve=ownership"

sudo cp $OPT eca2fb.py     $BIN/eca2fb
sudo cp $OPT hjjs.py       $BIN/hjjs
sudo cp $OPT midi.py       $BIN/midi
sudo cp $OPT printable.py  $BIN/printable
sudo cp $OPT projectile.py $BIN/projectile

# C

echo "Copying C headers"

sudo cp $OPT *.h $INC

echo "Compiling C programs"

OPT="-std=c17 -march=native -O3"

cc $OPT -o aeca       aeca.c
cc $OPT -o amorse     amorse.c
cc $OPT -o ctime      ctime.c
cc $OPT -o getendian  getendian.c
cc $OPT -o getlocale  getlocale.c
cc $OPT -o hacc       hacc.c
cc $OPT -o hj2fb      hj2fb.c
cc $OPT -o hj2png     hj2png.c    -lpng -lz
cc $OPT -o limits     limits.c
cc $OPT -o morse      morse.c
cc $OPT -o pp         pp.c
cc $OPT -o waves      waves.c     -lFLAC

echo "Moving C programs"

sudo mv aeca amorse ctime getendian getlocale hacc hj2fb hj2png limits morse pp waves $BIN

# Haskell

echo "Compiling Haskell program"

ghc -no-keep-hi-files -no-keep-o-files -v0 -O2 -o qda qda.hs

echo "Moving Haskell program"

sudo mv qda $BIN

echo "Done"
