// getlocale.c - print the current locale

#include <locale.h>
#include <stdio.h>

int main(void) {
  char *locale = setlocale(LC_ALL, "");

  if (!locale)
    return 1;

  puts(locale);
}
