#ifndef KEYPAD_H
#define KEYPAD_H

/* The keypad for the chip-8 is basically labeled
 * 0-16 in hex, so we map those values on the keypad
 * to values on our keyboard. Basically, whatever input
 * our program receives from our user, we convert it to 
 * what it would be on the original key pad.
 * "1, 2, 3, 4, q, w, e, r, a, s, d, f, z, x, c, v"
 *  1  2  3  c  4  5  6  d  7  8  9  e  a  0  b  f 
 */

typedef struct keypad keypad;

unsigned char keyboard2keypad(unsigned char key);

#endif
