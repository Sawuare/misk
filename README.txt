Here is my hobby software, including programs about audio, images, patterns, physics,
mathematics, utility, and fun, and modules useful for other programs. Some of them
use features of POSIX, less use features of C, and even less use features of Linux.
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
    My Bash configuration file.

  .nanorc
    My nano configuration file.

  LICENSE.txt
    The MIT License under which everything else is licensed.

  README.txt
    This file.

For a one-line description of every program and module, execute this command line:

  awk "FNR==2;FNR==3{nextfile}" doc/*

To get started, read doc/build.txt then execute src/build.sh to build and install
everything automatically or read it to learn how individual programs are compiled.

Questions and comments are welcome! Send them to sawuare@gmail.com.
