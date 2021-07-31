// getendian.c

#include <stdio.h>

int main(void) {
  union {int i; unsigned char bytes[sizeof (int)];} one = {1};

  puts(one.bytes[0] ? "little" : "big");
}
