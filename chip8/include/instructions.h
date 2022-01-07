#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

typedef struct instruction {
  // nibble = 4 bits
  // byte = 8 bits
  unsigned char *_instruction; // 2 bytes
  unsigned char type;  // 1st nibble
  unsigned char x;     // 2nd nibble
  unsigned char y;     // 3rd nibble
  unsigned char n;     // 4th nibble
  unsigned char nn;    // 2nd byte
  unsigned char *nnn; // nibbles 2-4 (12 bits)
} instruction;

instruction makeInstruction(unsigned char *instruct);
unsigned char get4bits(unsigned char bitString, int startBit);
#endif
