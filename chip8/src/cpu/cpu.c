#include "../../include/cpu.h"
#include "../../include/display.h"
#include "../../include/instructions.h"
#include "../../include/keypad.h"
#include "../../include/mem.h"
#include "../../include/timer.h"
#include <float.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// variable registers
unsigned char V0 = 0;
unsigned char V1 = 0;
unsigned char V2 = 0;
unsigned char V3 = 0;
unsigned char V4 = 0;
unsigned char V5 = 0;
unsigned char V6 = 0;
unsigned char V7 = 0;
unsigned char V8 = 0;
unsigned char V9 = 0;
unsigned char VA = 0;
unsigned char VB = 0;
unsigned char VC = 0;
unsigned char VD = 0;
unsigned char VE = 0;
unsigned char VF = 0;

cpu makeCpu(mem *memory, display *screen) {
  cpu out;
  out.indexRegister = (unsigned char *)malloc(sizeof(unsigned char) * 16);
  out.maxInstructionsPerSec = 700;
  out.memory = (mem *)malloc(sizeof(mem));
  *(out.memory) = *memory;
  out.PC = (unsigned char *)malloc(sizeof(unsigned char) * 2);
  (out.PC) = (memory->RAM + interpEnding);
  (out.screen) = (display *)malloc(displaySize);
  *(out.screen) = *(screen);
  out._stack = makeStack();
  out.dTimer = makeDelayTimer();
  out.sTimer = makeSoundTimer();
  return out;
}

unsigned char *fetchInstruction(cpu *core) {
  unsigned char *out = (unsigned char *)malloc(sizeof(unsigned char) * 2);
  memmove(out, (core->PC), 2);
  core->PC += 2;
  return out;
}

instruction decode(unsigned char *inst) { return makeInstruction(inst); }

void runCpu(cpu *core) {
  const int maxInstructionsPerMin = 700;
  int numInstructions = 0;

  while (true) {
    printf("made it inside of loop for checking, about to break!\n");
    break;
    if (numInstructions == maxInstructionsPerMin) {
      // waitMin()
      numInstructions = 0;
    }
    // char *instruction = fetechInstruction();
    // char *decoded = decodeInstruction(instruction);
    // execute(decoded);
    numInstructions++;
  }
}

// instruction set

void clearScreen(cpu *core) { // 00E0
  for (int i = 0; i < numDisplayRows; i++) {
    for (int j = 0; j < numDisplayCols; j++) {
      *((*((core->screen)->visual) + i) + j) = false;
    }
  }
}

void updatePC(cpu *core, unsigned char *address) {
  memcpy(core->PC, address, 2);
}

void jump(cpu *core, instruction command) { // 1NNN
  updatePC(core, command.nnn);
}

void subRoutinePush(cpu *core, instruction command) { // 2NNN
  unsigned char *value = (unsigned char *)malloc(sizeof(unsigned char) * 2);
  memcpy(value, core->PC, 2);
  push(&(core->_stack), value);
  jump(core, command);
}

void subRoutinePop(cpu *core, instruction command) { // 00EE
  unsigned char *help = pop(&(core->_stack));
  memcpy(core->PC, help, 2);
}

unsigned char *getRegister(int num) {
  switch (num) {
  case 0:
    return &V0;
  case 1:
    return &V1;
  case 2:
    return &V2;
  case 3:
    return &V3;
  case 4:
    return &V4;
  case 5:
    return &V5;
  case 6:
    return &V6;
  case 7:
    return &V7;
  case 8:
    return &V8;
  case 9:
    return &V9;
  case 10:
    return &VA;
  case 11:
    return &VB;
  case 12:
    return &VC;
  case 13:
    return &VD;
  case 14:
    return &VE;
  case 15:
    return &VF;
  default:
    printf("register VX is out of range of available registers\n");
    exit(-1);
  }
}

bool charcmp(unsigned char a, unsigned char b, bool not ) {
  if (not ) {
    return a != b;
  }
  return a == b;
}

void VXcmpNN(cpu *core, instruction command, bool not ) {
  unsigned char *VX = getRegister((int)command.x);
  if (charcmp(*VX, command.nn, not )) {
    (*core).PC += 2;
  }
}

void VXcmpVY(cpu *core, instruction command, bool not ) {
  unsigned char *VX = getRegister((int)command.x);
  unsigned char *VY = getRegister((int)command.y);
  if (charcmp(*VX, *VY, not )) {
    (*core).PC += 2;
  }
}

void skip(cpu *core, instruction command) { // 3XNN, 4XNN, 5XY0, 9XY0
  if (command.type == 0x3) {
    VXcmpNN(core, command, false);
  } else if (command.type == 0x4) {
    VXcmpNN(core, command, true);
  } else if (command.type == 0x5) {
    VXcmpVY(core, command, false);
  } else if (command.type == 0x9) {
    VXcmpVY(core, command, true);
  } else {
    printf("invalid skip instruction\n");
    exit(-1);
  }
}

void setImmediate(cpu *core, instruction command) { // 6XNN
  unsigned char *VX = getRegister((int)command.x);
  memcpy(VX, &command.nn, 1);
}

void addImmediate(cpu *core, instruction command) { // 7XNN
  unsigned char *VX = getRegister((int)command.x);
  *VX += (command.nn);
}

void setReg(cpu *core, instruction command) { // 8XY0
  unsigned char *VX = getRegister((int)command.x);
  unsigned char *VY = getRegister((int)command.y);
  *VX = *VY;
}

void binOr(cpu *core, instruction command) { // 8XY1
  unsigned char *VX = getRegister((int)command.x);
  unsigned char *VY = getRegister((int)command.y);
  *VX = (*VX | *VY);
}

void binAnd(cpu *core, instruction command) { // 8XY2
  unsigned char *VX = getRegister((int)command.x);
  unsigned char *VY = getRegister((int)command.y);
  *VX = (*VX & *VY);
}

void binXor(cpu *core, instruction command) { // 8XY3
  unsigned char *VX = getRegister((int)command.x);
  unsigned char *VY = getRegister((int)command.y);
  *VX = (*VX ^ *VY);
}

void addReg(cpu *core, instruction command) { // 8XY4
  unsigned char *VX = getRegister((int)command.x);
  unsigned char *VY = getRegister((int)command.y);
  *VX = (*VX + *VY);
  if (*VX > 255) {
    VF = 1;
  } else {
    VF = 0;
  }
}

void subReg(cpu *core, instruction command, bool subForward) { // 8XY5 ~ 8XY7
  unsigned char *VX = getRegister((int)command.x);
  unsigned char *VY = getRegister((int)command.y);
  if (subForward) {
    *VX = (*VX - *VY);
  } else {
    *VX = (*VY - *VX);
  }
  if (*VX < 0) {
    VF = 1;
  } else {
    VF = 0;
  }
}

// zero - indexed, byte len == 16
bool checkNBit(unsigned char byte, int n) {
  if (n > 16) {
    printf("invalid shift len\n");
    exit(-1);
  }
  return ((byte >> (n)) & 1);
}

void shift(cpu *core, instruction command, bool left) { // 8XY6 = R && 8XYE = L
  // setReg(core, command);
  unsigned char *VX = getRegister((int)command.x);
  if (left) {
    VF = (int)checkNBit(*VX, 15);
    *VX = (*VX) << 1;
    return;
  }
  VF = (int)checkNBit(*VX, 0);
  *VX = *VX >> 1;
}

void setIndexRegister(cpu *core, instruction command) { // ANNN
  memcpy(core->indexRegister, command.nnn, 2);
}

void little2bigEndian(unsigned char **command) {
  // https://stackoverflow.com/questions/42812150/why-memcpy-memmove-reverse-data-when-copying-int-to-bytes-buffer
  // tldr: Multibyte numbers (anything bigger than a uint8_t) are stored in
  // little endian
  unsigned char helper[2];
  helper[0] = *(*command + 1);
  helper[1] = **command;
  memcpy(*command, helper, 2);
}

unsigned char *addTypes(unsigned char *ptr, unsigned short num) {

  unsigned short ptrShort = ((*ptr) << 8) | *(ptr + 1);
  ptrShort += num;
  unsigned char *out = (unsigned char *)malloc(sizeof(unsigned char) * 2);
  memcpy(out, &ptrShort, 2);
  little2bigEndian(&out);
  return out;
}

void jumpW_offset(cpu *core, instruction command) { // BXNN
  // note: unsigned short int = 2 bytes = len( command.nnn)
  unsigned char *VX = getRegister(command.x);
  // unsigned short offSet = ((*command.nnn) << 8) | *(command.nnn + 1);
  // offSet += (unsigned short)*VX;
  unsigned char *jumpInstructionHelp =
      addTypes(command.nnn, (unsigned short)*VX);

  updatePC(core, jumpInstructionHelp);
  free(jumpInstructionHelp);
}

void randNN(cpu *core, instruction command) { // CXNN
  srand(time(0));
  int randNum = rand();
  
  unsigned char out = ((unsigned char)randNum) & command.nn;
  unsigned char *VX = getRegister((int)command.x);
  *VX = out;
  if (out == 0 || out == '\0') {
    randNN(core, command);
  }
}

// returns which bit we want from right to left (0-indexed)
bool getBit(unsigned char hex, int bit) { return (hex >> bit) & 1; }

// each bit corresponds to a horizontal pixel
void draw(cpu *core, unsigned char *sprite, unsigned char n, unsigned char x,
          unsigned char y) {
  x %= numDisplayRows;
  y %= numDisplayCols;
  bool **vis = (*core).screen->visual;
  unsigned char *VF = getRegister(15);
  *VF = 0;
  for (int i = 0; (i < n) && (x + i < numDisplayRows); i++) {
    for (int j = 0; (j < 8) && (y + j < numDisplayCols); j++) {
      if (getBit(*(sprite + i), j)) {
        *(*(vis + x + i) + y + j) = !(*(*(vis + x + i) + y + j));
        if (!(*(*(core->screen->visual + x + i) + y + j)) && !(*VF)) {
          *VF = 1;
        }
      }
    }
  }
}

void updateDisplay(cpu *core, instruction command) { // DXYN
  unsigned char *VX = getRegister(command.x);
  unsigned char *VY = getRegister(command.y);
  unsigned char yLen = command.n;
  unsigned char *sprite = (unsigned char *)malloc(sizeof(unsigned char) * yLen);
  memcpy(sprite, (core->memory->RAM + ((int)*(core->indexRegister))), yLen);
  // y corresponds with rows, x corresponds with cols.
  draw(core, sprite, command.n, *VY, *VX);
}

unsigned char keyIsPressed(bool test) {
  if (test) {
    return 0x0;
  }
  int getKeyPressed = getchar();
  unsigned char keyPressed = keyboard2keypad((unsigned char)getKeyPressed);
  return keyPressed;
}

void skipIfPressed(cpu *core, instruction command, bool not,
                   bool test) { // EX9E & EXA1
  unsigned char *VX = getRegister(command.x);
  if (not ) {
    if (keyIsPressed(test) != *VX) {
      (*core).PC += 2;
    }
    return;
  }
  if (keyIsPressed(test) == *VX) {
    (*core).PC += 2;
  }
}

void setVx2DelayTimer(cpu *core, instruction command) { // FX07
  unsigned char *VX = getRegister(command.x);
  *VX = (unsigned char)core->dTimer->timer;
}

void setDelayTimer2Vx(cpu *core, instruction command) { // FX15
  unsigned char *VX = getRegister(command.x);
  (*core).dTimer->timer = (int)*VX;
}

void setSoundTimer2Vx(cpu *core, instruction command) { // FX18
  unsigned char *VX = getRegister(command.x);
  (*core).sTimer->timer = (int)*VX;
}

void add2Index(cpu *core, instruction command) { // FX1E
  unsigned char *VX = getRegister(command.x);
  unsigned char *helper = addTypes(core->indexRegister, (unsigned short)*VX);
  memcpy(core->indexRegister, helper, 2);
  if (*helper >= 0x10) {
    unsigned char *VF = getRegister(15);
    *VF = 1;
  }
}

void getKey(cpu *core, instruction command, bool test) { // FX0A
  unsigned char keyPressed = keyIsPressed(test);
  if (keyPressed != 0 || test) {
    unsigned char *VX = getRegister(command.x);
    *VX = keyPressed;
  }
  (*core).PC -= 2;
}

void fontChar(cpu *core, instruction command) { // FX29
  unsigned char *VX = getRegister(command.x);
  memcpy((*core).indexRegister,
         (core->memory->RAM + (fontStart) + (*VX & 0x0f)),
         1); // says that we should look @ last niblbe
}

void binCodedDecConversion(cpu *core, instruction command) { // FX33
  unsigned char *VX = getRegister(command.x);
  int bin2dec = (int)*VX;
  for (int i = 0; i < 3; i++) {
    *((*core).indexRegister + (3 - i - 1)) = (unsigned char)bin2dec % 10;
    bin2dec = bin2dec / 10;
  }
}

void store(cpu *core, instruction command) { // FX55
  unsigned char numRegisters = command.x;
  for (int i = 0; i <= (int)numRegisters; i++) {
    unsigned char *VX = getRegister(i);
    *((*core).indexRegister + i) = *VX;
  }
}

void load(cpu *core, instruction command) { // FX65
  unsigned char numRegisters = command.x;
  for (int i = 0; i <= (int)numRegisters; i++) {
    unsigned char *VX = getRegister(i);
    *VX = *((*core).indexRegister + i);
  }
}
