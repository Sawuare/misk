Here is my hobby software, including headers for terminal control and programs about
audio, graphics, patterns, physics, mathematics, utility, and fun. The programs only
have terminal interfaces. Some programs use features of POSIX or Linux, so I
recommend GNU/Linux for using them.

The directories and files in here are:

  aux/
    Auxiliary scripts which must be executed from this directory.

    *.sh -> POSIX shell scripts

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

  .bashrc
    My Bash configuration file.

  .nanorc
    My nano configuration file.

  LICENSE.txt
    The MIT License under which everything else is licensed.

  README.txt
    This file.

For a summary of every program and header, execute

  $ cd aux/ && ./summarize.sh

To get started, see aux/build.sh.

Questions and comments are welcome! Send them to sawuare@gmail.com.
