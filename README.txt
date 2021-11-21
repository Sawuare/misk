Here is my hobby software, including headers for terminal control and programs about
audio, graphics, patterns, physics, mathematics, utility, and fun. The programs only
have terminal interfaces. Some programs use features of C, POSIX, or Linux, so I
recommend GNU/Linux for using them.

The folders and files in here are:

  dat/
    Data exported by the programs.

  doc/
    Documentation of the programs and headers.

  src/
    Source code in several languages.

    *.c  -> C source files
    *.h  -> C headers
    *.hs -> Haskell files
    *.py -> Python scripts
    *.sh -> POSIX shell scripts

  .bashrc
    My Bash configuration file.

  .nanorc
    My nano configuration file.

  LICENSE.txt
    The MIT License under which everything else is licensed.

  README.txt
    This file.

For a one-line description of every program and header, execute

  $ awk "FNR==2;FNR==3{nextfile}" doc/*

To get started, read doc/build.txt then execute src/build.sh to build and install
everything automatically or read it to learn how individual programs are compiled.

Questions and comments are welcome! Send them to sawuare@gmail.com.
