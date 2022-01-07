#include "utils.h"
#ifndef MEM_H
#define MEM_H

// Memory Section
typedef struct mem {
  unsigned char *RAM; // all memory in chip-8 is read-access-memory
} mem;

#define memSize sizeof(mem) + sizeof(unsigned char *)

#define ramSize 4098 // num bytes allowed for the ram

// from 0x000 -> 0x1FF intepreter should live, programs are stored after 512
#define interpEnding 512

#define fontStart 80 // 0x050

// fonts stored in a 16 x 5 matrix
extern const unsigned char font[16][5];

// fucntions

/* Output: mem* memory =>
 *  Allocates space that simulates amount of space
 *  that chip-8 at its use = 4096 byres = ramSize
 *  (called ramSize because chip-8 has all read-only memory
 *  which they considered to be ram)
 */
mem *buildMem();
void writeGameFile(mem **memory, aFile gameFile);
#endif
