// ctime.c - print local time in the form Www Mmm dd hh:mm:ss yyyy

#include <stdio.h>
#include <time.h>

int main(void) {
  fputs(ctime(&((time_t) {time(0)})), stdout);
}
