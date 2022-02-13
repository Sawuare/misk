// getendian.c - print the system endianness

#include <stdio.h>

_Static_assert(sizeof (long long) > 1, "The size of `long long` is not greater than 1 byte!");

int main(void) {
  union {long long ll; unsigned char bytes[sizeof (long long)];} one = {1};

  puts(one.bytes[0] ? "Little" : "Big");
}
