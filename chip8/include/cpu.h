#include "display.h"
#include "instructions.h"
#include "mem.h"
#include "stack.h"
#include "timer.h"
#include <stdlib.h>
#include <time.h>
#ifndef CPU_H
#define CPU_H

typedef struct cpu {
  unsigned char *PC;
  unsigned char *indexRegister; // register that points @ some location in mem
  time_t clockStartTime;
  int numInstructionsExecuted;
  int maxInstructionsPerSec;
  mem *memory;
  display *screen;
  stack *_stack;
  delayTimer *dTimer;
  soundTimer *sTimer;
} cpu;

// functions
cpu makeCpu(mem *memory, display *screen);
void runCpu(cpu *core);
unsigned char *fetchInstruction(cpu *core);
void execute(cpu *core, instruction command);
void clearScreen(cpu *core, instruction command);
void jump(cpu *core, instruction command);
void subRoutinePush(cpu *core, instruction command);
void subRoutinePop(cpu *core, instruction command);
void skip(cpu *core, instruction command);
unsigned char *getRegister(int num);
void setImmediate(cpu *core, instruction command);
void addImmediate(cpu *core, instruction command);
void setReg(cpu *core, instruction command);
void binOr(cpu *core, instruction command);
void binAnd(cpu *core, instruction command);
void binXor(cpu *core, instruction command);
void addReg(cpu *core, instruction command);
void subReg(cpu *core, instruction command, bool subForward);
void shift(cpu *core, instruction command, bool left);
void setIndexRegister(cpu *core, instruction command);
void jumpW_offset(cpu *core, instruction command);
void randNN(cpu *core, instruction command);
void updateDisplay(cpu *core, instruction command);
void skipIfPressed(cpu *core, instruction command, bool no,
                   bool test);                              // EX9E & EXA1
void setVx2DelayTimer(cpu *core, instruction command);      // FX07
void setDelayTimer2Vx(cpu *core, instruction command);      // FX16
void setSoundTimer2Vx(cpu *core, instruction command);      // FX18
void add2Index(cpu *core, instruction command);             // FX1E
void getKey(cpu *core, instruction command, bool test);     // FX0A
void fontChar(cpu *core, instruction command);              // FX29
void binCodedDecConversion(cpu *core, instruction command); // FX33
void store(cpu *core, instruction command);
void load(cpu *core, instruction command);

// Variable regiesters
extern unsigned char V0;
extern unsigned char V1;
extern unsigned char V2;
extern unsigned char V3;
extern unsigned char V4;
extern unsigned char V5;
extern unsigned char V6;
extern unsigned char V7;
extern unsigned char V8;
extern unsigned char V9;
extern unsigned char VA;
extern unsigned char VB;
extern unsigned char VC;
extern unsigned char VD;
extern unsigned char VE;
extern unsigned char VF;

#endif
