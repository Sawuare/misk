// morse.c - encode arguments into printable adapted International Morse code

#include <stdio.h>

int main(int wordc, char* wordv[wordc + 1]) {
  char* codev[123] = {0};

  codev['A'] = codev['a'] = ".-";
  codev['B'] = codev['b'] = "-...";
  codev['C'] = codev['c'] = "-.-.";
  codev['D'] = codev['d'] = "-..";
  codev['E'] = codev['e'] = ".";
  codev['F'] = codev['f'] = "..-.";
  codev['G'] = codev['g'] = "--.";
  codev['H'] = codev['h'] = "....";
  codev['I'] = codev['i'] = "..";
  codev['J'] = codev['j'] = ".---";
  codev['K'] = codev['k'] = "-.-";
  codev['L'] = codev['l'] = ".-..";
  codev['M'] = codev['m'] = "--";
  codev['N'] = codev['n'] = "-.";
  codev['O'] = codev['o'] = "---";
  codev['P'] = codev['p'] = ".--.";
  codev['Q'] = codev['q'] = "--.-";
  codev['R'] = codev['r'] = ".-.";
  codev['S'] = codev['s'] = "...";
  codev['T'] = codev['t'] = "-";
  codev['U'] = codev['u'] = "..-";
  codev['V'] = codev['v'] = "...-";
  codev['W'] = codev['w'] = ".--";
  codev['X'] = codev['x'] = "-..-";
  codev['Y'] = codev['y'] = "-.--";
  codev['Z'] = codev['z'] = "--..";

  codev['1'] = ".----";
  codev['2'] = "..---";
  codev['3'] = "...--";
  codev['4'] = "....-";
  codev['5'] = ".....";
  codev['6'] = "-....";
  codev['7'] = "--...";
  codev['8'] = "---..";
  codev['9'] = "----.";
  codev['0'] = "-----";

  codev[ '.'] = ".-.-.-";
  codev[ ','] = "--..--";
  codev[ ':'] = "---...";
  codev[ '?'] = "..--..";
  codev['\''] = ".----.";
  codev[ '-'] = "-....-";
  codev[ '/'] = "-..-.";
  codev[ '('] = "-.--.";
  codev[ ')'] = "-.--.-";
  codev['\"'] = ".-..-.";
  codev[ '='] = "-...-";
  codev[ '+'] = ".-.-.";
  codev[ '@'] = ".--.-.";

  int wordi = 1;

  while (wordi != wordc) {
    char* word = wordv[wordi++];

    while (*word) {
      fputs(codev[*word++], stdout);
      fputc(*word ? ' ' : '\n', stdout);
    }
  }
}
