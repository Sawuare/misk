// getlocale.c

#include <locale.h>
#include <stdio.h>

int main(void) {
	puts(setlocale(LC_ALL, ""));
}
