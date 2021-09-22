Here is my hobby software, including programs about audio, images, patterns, physics,
mathematics, utility, and fun, and modules useful for other programs. Some of them
use features of C, less use features of POSIX, and even less use features of Linux.
The external program "aplay", an ALSA utility, is recommended but not a dependency.

These are the folders and files in here:

  dat/
    Data exported by the programs.

  doc/
    Documentation of the programs.

  src/
    Sources and scripts in several languages.

    *.c  -> C files
    *.h  -> C headers
    *.hs -> Haskell files
    *.py -> Python 3 scripts
    *.sh -> POSIX shell scripts

  .bashrc
    Bash configuration file.

  .nanorc
    Nano configuration file.

  LICENSE.txt
    The MIT license under which everything else is licensed.

  README.txt
    This file.

For a one-line description of every program, execute this command line:

  sed -n -s 2p doc/*

To get started, read doc/build.txt then execute src/build.sh to build and install
everything automatically or read it to learn how individual programs are compiled.

Questions, comments, and contributions are welcome! Send them to sawuare@gmail.com.
