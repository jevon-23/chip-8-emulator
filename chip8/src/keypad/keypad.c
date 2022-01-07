#include <float.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/keypad.h"

unsigned char keyboard2keypad(unsigned char key) {
  switch (key) {
  case '1':
    return '1';
  case '2':
    return '2';
  case '3':
    return '3';
  case '4':
    return 'C';
  case 'q':
    return '4';
  case 'Q':
    return '4';
  case 'w':
    return '5';
  case 'W':
    return '5';
  case 'e':
    return '6';
  case 'E':
    return '6';
  case 'r':
    return 'D';
  case 'R':
    return 'D';
  case 'a':
    return '7';
  case 'A':
    return '7';
  case 's':
    return '8';
  case 'S':
    return '8';
  case 'd':
    return '9';
  case 'D':
    return '9';
  case 'f':
    return 'E';
  case 'F':
    return 'E';
  case 'z':
    return 'A';
  case 'Z':
    return 'A';
  case 'x':
    return '0';
  case 'X':
    return '0';
  case 'c':
    return 'b';
  case 'C':
    return 'B';
  case 'v':
    return 'F';
  case 'V':
    return 'F';
  }
  printf("invalid key, possible keys to be pressed are \n");
  printf("1, 2, 3, 4, q, w, e, r, a, s, d, f, z, x, c, v");
  return 0; // returning null so that we recall this func and not exit
               // program
}
