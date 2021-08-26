// getlocale.c - print the system locale

#include <locale.h>
#include <stdio.h>

int main(void) {
  char* locale = setlocale(LC_ALL, "");

  if (locale)
    puts(locale);
  else
    return 1;
}
