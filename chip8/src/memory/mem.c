#include "../../include/mem.h"
#include "../../include/utils.h"
#include <float.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const unsigned char font[16][5] = {
    {0xF0, 0x90, 0x90, 0x90, 0xF0}, // 0
    {0x20, 0x60, 0x20, 0x20, 0x70}, // 1
    {0xF0, 0x10, 0xF0, 0x80, 0xF0}, // 2
    {0xF0, 0x10, 0xF0, 0x10, 0xF0}, // 3
    {0x90, 0x90, 0xF0, 0x10, 0x10}, // 4
    {0xF0, 0x80, 0xF0, 0x10, 0xF0}, // 5
    {0xF0, 0x80, 0xF0, 0x90, 0xF0}, // 6
    {0xF0, 0x10, 0x20, 0x40, 0x40}, // 7
    {0xF0, 0x90, 0xF0, 0x90, 0xF0}, // 8
    {0xF0, 0x90, 0xF0, 0x10, 0xF0}, // 9
    {0xF0, 0x90, 0xF0, 0x90, 0x90}, // A
    {0xE0, 0x90, 0xE0, 0x90, 0xE0}, // B
    {0xF0, 0x80, 0x80, 0x80, 0xF0}, // C
    {0xE0, 0x90, 0x90, 0x90, 0xE0}, // D
    {0xF0, 0x80, 0xF0, 0x80, 0xF0}, // E
    {0xF0, 0x80, 0xF0, 0x80, 0x80}  // F
};

void writeGameFile(mem **memory, aFile gameFile) {
  memcpy(((*memory)->RAM + (interpEnding)), *gameFile.contents , gameFile.fileSize);
}

void inputFont(mem **memory) {
  int memCounter = 0;
  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 5; j++, memCounter++) {
      memcpy(((*memory)->RAM + (fontStart + memCounter)), (font[i] + j), 1);
    }
  }
}

mem *buildMem() {
  mem *out = (mem *)malloc(sizeof(memSize));
  out->RAM = (unsigned char *)malloc(sizeof(unsigned char) * ramSize);
  inputFont(&out);
  return out;
}
