#include "../../include/instructions.h"
#include <float.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char get4bits(unsigned char bitString, int startBit) {
    unsigned char out;
    // put the 4 bits we want in the last 4 bits of bitString
    // int shiftAmount = 8 - (4 + startBit);
    unsigned char y = bitString << startBit;
    out = (y >> 4); // shift right 4 to put us back at the top of the bit string.
    return out;
}

instruction makeInstruction(unsigned char *instruct) {
  instruction out;
  out._instruction = (unsigned char *)malloc(sizeof(unsigned char) * 2);
  memcpy(out._instruction, instruct, 2);
  out.type = get4bits(*instruct, 0);
  out.x = get4bits(*instruct, 4);
  out.y = get4bits(*(instruct + 1), 0);
  out.n = get4bits(*(instruct + 1), 4);
  out.nn = *(instruct + 1);
  out.nnn = (unsigned char *)malloc(sizeof(unsigned char) * 2);
  memcpy(out.nnn, &out.x, 1);
  memcpy((out.nnn + 1), &out.nn, 1);
  return out;
}

