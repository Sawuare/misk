// args.c - print arguments and their indices

#include <stdio.h>

int main(int argc, char* argv[argc + 1]) {
  for (int argi = 0; argi < argc; ++argi)
    printf("argv[%d]: %s\n", argi, argv[argi]);
}
