#include <float.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/utils.h"
#include "../../include/cpu.h"
#include "../../include/mem.h"
#include "../../include/instructions.h"
#include "../../include/display.h"


int processCLI(int argc, char **argv, char **filename) {
  if (argc != 2) {
    printf("usage: ./chip8 <rom/filename>");
    exit(-1);
  }
  *filename = (char *)malloc(sizeof(char *) * strlen(*(argv + 1)));
  strcpy(*filename, *(argv + 1));
  return 0;
}

int main(int arg, char *argv[]) {
  char *filename;
  processCLI(arg, argv, &filename);
  aFile gameFile = readFile(filename);
  mem *memory = buildMem();
  writeGameFile(&memory, gameFile);
  display *screen = makeDisplay();
  cpu core = makeCpu(memory, screen);
  printf("printing out the memory real quick\n");
  for (int i =0 ; i < ramSize; i++) {
      printf("mem + %d = %x\n", i,  *(memory->RAM + i));
  }
  
  printf("Successful build! Running cpu!\n");
//   buildWindow();
  runCpu(&core);
  
  return 0;
}
