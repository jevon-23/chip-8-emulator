#include <gtest/gtest.h>

extern "C" {
#include "../../../include/cpu.h"
#include "../../../include/display.h"
#include "../../../include/mem.h"
}
namespace {
TEST(makeCpuTest, makeCpu) {
  mem *m = buildMem();
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);
  EXPECT_EQ(c.maxInstructionsPerSec, 700);
  EXPECT_EQ(240, (int)*(c.memory->RAM + fontStart)); // '0xF0'
  EXPECT_EQ(false, **(c.screen->visual));
}

TEST(fetchInstructionTest, fetchInstruction) {
  unsigned char instruct[2] = {0x01, 0x02};
  mem *m = buildMem();
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);
  memcpy(c.PC, instruct, 2);
  unsigned char *out = fetchInstruction(&c);
  for (int i = 0; i < 2; i++) {
    EXPECT_EQ(instruct[i], *(out + i));
  }
}

// decode is tested in src/instruction

TEST(clearScreenTest, clearScreen) {
  mem *m = buildMem();
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);
  clearScreen(&c);
  for (int i = 0; i < numDisplayRows; i++) {
    for (int j = 0; j < numDisplayCols; j++) {
      EXPECT_EQ(false, *((*((c.screen)->visual) + i) + j));
    }
  }
}

TEST(jumpTest, jump) {
  mem *m = buildMem();
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);
  unsigned char instruct[2] = {0x1A, 0x2A};
  instruction i = makeInstruction(instruct);
  jump(&c, i);
  unsigned char expected[2] = {0x0A, 0x2A};
  for (int i = 0; i < 2; i++) {
    EXPECT_EQ(expected[i], *(c.PC + i));
  }
}

TEST(subRoutinePushTest, subRoutinePush) {
  mem *m = buildMem();
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);

  unsigned char instructStack[2] = {0x1A, 0x2A};
  instruction iStack = makeInstruction(instructStack);
  jump(&c, iStack);
  unsigned char expectedStack[2] = {0x0A, 0x2A};

  unsigned char instruct[2] = {0x2A, 0x2B};
  instruction i = makeInstruction(instruct);
  subRoutinePush(&c, i);
  unsigned char expected[2] = {0x0A, 0x2B};

  unsigned char *stackOut = peak(&(c._stack));
  for (int i = 0; i < 2; i++) {
    EXPECT_EQ(expected[i], *(c.PC + i));
    EXPECT_EQ(expectedStack[i], *(stackOut + i));
  }
}

TEST(subRoutinePopTest, subRoutinePop) {
  mem *m = buildMem();
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);

  unsigned char instructStack[2] = {0x1A, 0x2A};
  instruction iStack = makeInstruction(instructStack);
  jump(&c, iStack);
  unsigned char expected[2] = {0x0A, 0x2A};

  unsigned char instruct[2] = {0x2A, 0x2B};
  instruction i = makeInstruction(instruct);
  subRoutinePush(&c, i);

  unsigned char instructPop[3] = {0x00, 0xEE};
  instruction iPop = makeInstruction(instructPop);
  subRoutinePop(&c, iPop);

  for (int i = 0; i < 2; i++) {
    EXPECT_EQ(expected[i], *(c.PC + i));
  }
}

TEST(skip3xFailTest, skip) {
  mem *m = buildMem();
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);

  unsigned char instruct[2] = {0x30, 0x2A};
  instruction i = makeInstruction(instruct);
  unsigned char *V0 = getRegister(0);
  *V0 = 0x01;

  unsigned char fakeI1[2] = {0x12, 0x34};
  unsigned char fakeI2[2] = {0x15, 0x19};

  memcpy(c.PC, fakeI1, 2);
  memcpy((c.PC + 2), fakeI2, 2);
  skip(&c, i);

  for (int i = 0; i < 2; i++) {
    EXPECT_EQ(fakeI1[i], *(c.PC + i));
  }
}

TEST(skip3xPassTest, skip) {
  mem *m = buildMem();
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);

  unsigned char instruct[2] = {0x30, 0x2A};
  instruction i = makeInstruction(instruct);
  unsigned char *V0 = getRegister(0);
  *V0 = 0x2A;

  unsigned char fakeI1[2] = {0x12, 0x34};
  unsigned char fakeI2[2] = {0x15, 0x19};

  memcpy(c.PC, fakeI1, 2);
  memcpy((c.PC + 2), fakeI2, 2);
  skip(&c, i);

  for (int i = 0; i < 2; i++) {
    EXPECT_EQ(fakeI2[i], *(c.PC + i));
  }
}

TEST(skip4xPassTest, skip) {
  mem *m = buildMem();
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);

  unsigned char instruct[2] = {0x40, 0x2A};
  instruction i = makeInstruction(instruct);
  unsigned char *V0 = getRegister(0);
  *V0 = 0x2B;

  unsigned char fakeI1[2] = {0x12, 0x34};
  unsigned char fakeI2[2] = {0x15, 0x19};

  memcpy(c.PC, fakeI1, 2);
  memcpy((c.PC + 2), fakeI2, 2);
  skip(&c, i);

  for (int i = 0; i < 2; i++) {
    EXPECT_EQ(fakeI2[i], *(c.PC + i));
  }
}

TEST(skip4xFailTest, skip) {
  mem *m = buildMem();
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);

  unsigned char instruct[2] = {0x40, 0x2A};
  instruction i = makeInstruction(instruct);
  unsigned char *V0 = getRegister(0);
  *V0 = 0x2A;

  unsigned char fakeI1[2] = {0x12, 0x34};
  unsigned char fakeI2[2] = {0x15, 0x19};

  memcpy(c.PC, fakeI1, 2);
  memcpy((c.PC + 2), fakeI2, 2);
  skip(&c, i);

  for (int i = 0; i < 2; i++) {
    EXPECT_EQ(fakeI1[i], *(c.PC + i));
  }
}

TEST(skip5xFailTest, skip) {
  mem *m = buildMem();
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);

  unsigned char instruct[2] = {0x50, 0x10};
  instruction i = makeInstruction(instruct);
  unsigned char *V0 = getRegister(0);
  unsigned char *V1 = getRegister(1);
  *V0 = 0x2B;
  *V1 = 0x2A;

  unsigned char fakeI1[2] = {0x12, 0x34};
  unsigned char fakeI2[2] = {0x15, 0x19};

  memcpy(c.PC, fakeI1, 2);
  memcpy((c.PC + 2), fakeI2, 2);
  skip(&c, i);

  for (int i = 0; i < 2; i++) {
    EXPECT_EQ(fakeI1[i], *(c.PC + i));
  }
}

TEST(skip5xPassTest, skip) {
  mem *m = buildMem();
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);

  unsigned char instruct[2] = {0x50, 0x10};
  instruction i = makeInstruction(instruct);
  unsigned char *V0 = getRegister(0);
  unsigned char *V1 = getRegister(1);
  *V0 = 0x2B;
  *V1 = 0x2B;

  unsigned char fakeI1[2] = {0x12, 0x34};
  unsigned char fakeI2[2] = {0x15, 0x19};

  memcpy(c.PC, fakeI1, 2);
  memcpy((c.PC + 2), fakeI2, 2);
  skip(&c, i);

  for (int i = 0; i < 2; i++) {
    EXPECT_EQ(fakeI2[i], *(c.PC + i));
  }
}

TEST(skip9xPassTest, skip) {
  mem *m = buildMem();
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);

  unsigned char instruct[2] = {0x90, 0x10};
  instruction i = makeInstruction(instruct);
  unsigned char *V0 = getRegister(0);
  unsigned char *V1 = getRegister(1);
  *V0 = 0x2B;
  *V1 = 0x2A;

  unsigned char fakeI1[2] = {0x12, 0x34};
  unsigned char fakeI2[2] = {0x15, 0x19};

  memcpy(c.PC, fakeI1, 2);
  memcpy((c.PC + 2), fakeI2, 2);
  skip(&c, i);

  for (int i = 0; i < 2; i++) {
    EXPECT_EQ(fakeI2[i], *(c.PC + i));
  }
}

TEST(skip9xFailTest, skip) {
  mem *m = buildMem();
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);

  unsigned char instruct[2] = {0x90, 0x10};
  instruction i = makeInstruction(instruct);
  unsigned char *V0 = getRegister(0);
  unsigned char *V1 = getRegister(1);
  *V0 = 0x2B;
  *V1 = 0x2B;

  unsigned char fakeI1[2] = {0x12, 0x34};
  unsigned char fakeI2[2] = {0x15, 0x19};

  memcpy(c.PC, fakeI1, 2);
  memcpy((c.PC + 2), fakeI2, 2);
  skip(&c, i);

  for (int i = 0; i < 2; i++) {
    EXPECT_EQ(fakeI1[i], *(c.PC + i));
  }
}

TEST(setImmediateTest, setImmediate) {
  mem *m = buildMem();
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);

  unsigned char instruct[2] = {0x60, 0x10};
  instruction i = makeInstruction(instruct);
  unsigned char *V0 = getRegister(0);
  setImmediate(&c, i);

  EXPECT_EQ(0x10, *V0);
}

TEST(addImmediateTest, addImmediate) {
  mem *m = buildMem();
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);

  unsigned char instruct[2] = {0x70, 0x10};
  instruction i = makeInstruction(instruct);
  unsigned char *V0 = getRegister(0);
  *V0 = 0x01;
  addImmediate(&c, i);

  EXPECT_EQ(0x11, *V0);
}

TEST(setRegTest, setReg) {
  mem *m = buildMem();
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);

  unsigned char instruct[2] = {0x80, 0x10};
  instruction i = makeInstruction(instruct);
  unsigned char *V0 = getRegister(0);
  unsigned char *V1 = getRegister(1);
  *V0 = 0x01;
  *V1 = 0xf1;

  setReg(&c, i);
  EXPECT_EQ(0xf1, *V0);
}

TEST(binOrTest, binOr) {
  mem *m = buildMem();
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);

  unsigned char instruct[2] = {0x80, 0x11};
  instruction i = makeInstruction(instruct);
  unsigned char *V0 = getRegister(0);
  unsigned char *V1 = getRegister(1);
  *V0 = 0xa1;
  *V1 = 0xf1;

  binOr(&c, i);
  EXPECT_EQ(0xa1 | 0xf1, *V0);
}

TEST(binAndTest, binAnd) {
  mem *m = buildMem();
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);

  unsigned char instruct[2] = {0x80, 0x12};
  instruction i = makeInstruction(instruct);
  unsigned char *V0 = getRegister(0);
  unsigned char *V1 = getRegister(1);
  *V0 = 0xa1;
  *V1 = 0xf1;

  binAnd(&c, i);
  EXPECT_EQ(0xa1 & 0xf1, *V0);
}

TEST(binXorTest, binXor) {
  mem *m = buildMem();
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);

  unsigned char instruct[2] = {0x80, 0x13};
  instruction i = makeInstruction(instruct);
  unsigned char *V0 = getRegister(0);
  unsigned char *V1 = getRegister(1);
  *V0 = 0xa1;
  *V1 = 0xf1;

  binXor(&c, i);
  EXPECT_EQ(0xa1 ^ 0xf1, *V0);
}

TEST(addRegTest, addReg) {
  mem *m = buildMem();
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);

  unsigned char instruct[2] = {0x80, 0x14};
  instruction i = makeInstruction(instruct);
  unsigned char *V0 = getRegister(0);
  unsigned char *V1 = getRegister(1);
  *V0 = 0xa1;
  *V1 = 0x01;

  addReg(&c, i);
  EXPECT_EQ(0xa1 + 0x01, *V0);
}

TEST(subRegForwardTest, subReg) {
  mem *m = buildMem();
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);

  unsigned char instruct[2] = {0x80, 0x15};
  instruction i = makeInstruction(instruct);
  unsigned char *V0 = getRegister(0);
  unsigned char *V1 = getRegister(1);
  *V0 = 0xa1;
  *V1 = 0x01;

  subReg(&c, i, true);
  EXPECT_EQ(0xa1 - 0x01, *V0);
}

TEST(subRegBackwardTest, subReg) {
  mem *m = buildMem();
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);

  unsigned char instruct[2] = {0x80, 0x15};
  instruction i = makeInstruction(instruct);
  unsigned char *V0 = getRegister(0);
  unsigned char *V1 = getRegister(1);
  *V0 = 0xa1;
  *V1 = 0x01;

  subReg(&c, i, false);
  EXPECT_EQ((unsigned char)-0xa1 + 0x01, *V0);
}

TEST(shiftLeftTest, shift) {
  mem *m = buildMem();
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);

  unsigned char instruct[2] = {0x80, 0x1E};
  instruction i = makeInstruction(instruct);
  unsigned char *V0 = getRegister(0);
  unsigned char *VF = getRegister(15);
  *V0 = 0xa1;

  shift(&c, i, true);
  EXPECT_EQ((unsigned char)(0xa1 << 1), *V0);
  EXPECT_EQ(0, *VF);
}

TEST(shiftRightTest, shift) {
  mem *m = buildMem();
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);

  unsigned char instruct[2] = {0x80, 0x16};
  instruction i = makeInstruction(instruct);
  unsigned char *V0 = getRegister(0);
  unsigned char *V1 = getRegister(1);
  *V0 = 0xa1;

  shift(&c, i, false);
  EXPECT_EQ((unsigned char)(0xa1 >> 1), *V0);
}

TEST(setIndexRegisterTest, setIndexRegister) {
  mem *m = buildMem();
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);

  unsigned char instruct[2] = {0xAB, 0x16};
  instruction i = makeInstruction(instruct);
  setIndexRegister(&c, i);
  unsigned char expected[2] = {0x0B, 0x16};
  for (int i = 0; i < 2; i++) {
    EXPECT_EQ(expected[i], *(c.indexRegister + i));
  }
}

TEST(jumpW_offsetTest, jumpW_offset) {
  mem *m = buildMem();
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);

  unsigned char instruct[2] = {0xB1, 0x16};
  instruction i = makeInstruction(instruct);
  unsigned char *V1 = getRegister(1);
  *V1 = 0;

  jumpW_offset(&c, i);
  unsigned char expected[2] = {0x01, 0x16};

  for (int i = 0; i < 2; i++) {
    EXPECT_EQ(expected[i], *(c.PC + i));
  }
}

TEST(randNNTest, randNN) {
  mem *m = buildMem();
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);

  unsigned char instruct[2] = {0xC0, 0x16};
  instruction i = makeInstruction(instruct);
  unsigned char *V0 = getRegister(0);
  *V0 = 0;
  randNN(&c, i);
  EXPECT_NE(0, *V0);
}

TEST(updateDisplayTest, updateDisplay) {
  mem *m = buildMem();
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);

  unsigned char instruct[2] = {0xD0, 0x11};
  instruction i = makeInstruction(instruct);
  unsigned char sprite = 0xff;
  memcpy((c.memory->RAM + ((int)*(c.indexRegister))), &sprite, 1);
  unsigned char *V0 = getRegister(0);
  unsigned char *V1 = getRegister(1);
  *V0 = 0;
  *V1 = 1;
  updateDisplay(&c, i);
  for (int i = 0; i < 8; i++) {
    EXPECT_EQ(*(*(c.screen->visual + 1) + i), true);
  }
}

TEST(skipIfPressedTrueTest, skipIfPressed) {
  mem *m = buildMem();
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);

  unsigned char instruct[2] = {0xE0, 0x9E};
  instruction i = makeInstruction(instruct);
  unsigned char *V0 = getRegister(0);
  *V0 = 0;
  unsigned char fake1[2] = {0xFF, 0xFF};
  unsigned char fake2[2] = {0xDD, 0xDD};
  memcpy(c.PC, fake1, 2);
  memcpy((c.PC + 2), fake2, 2);
  skipIfPressed(&c, i, false, true);
  for (int i = 0; i < 2; i++) {
    EXPECT_EQ(fake2[i], *(c.PC + i));
  }
}

TEST(skipIfPressedFalseTest, skipIfPressed) {
  mem *m = buildMem();
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);

  unsigned char instruct[2] = {0xE0, 0x9E};
  instruction i = makeInstruction(instruct);
  unsigned char *V0 = getRegister(0);
  *V0 = 1;
  unsigned char fake1[2] = {0xFF, 0xFF};
  unsigned char fake2[2] = {0xDD, 0xDD};
  memcpy(c.PC, fake1, 2);
  memcpy((c.PC + 2), fake2, 2);
  skipIfPressed(&c, i, false, true);
  for (int i = 0; i < 2; i++) {
    EXPECT_EQ(fake1[i], *(c.PC + i));
  }
}

TEST(notSkipIfPressedFalseTest, skipIfPressed) {
  mem *m = buildMem();
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);

  unsigned char instruct[2] = {0xE0, 0xA1};
  instruction i = makeInstruction(instruct);
  unsigned char *V0 = getRegister(0);
  *V0 = 0;
  unsigned char fake1[2] = {0xFF, 0xFF};
  unsigned char fake2[2] = {0xDD, 0xDD};
  memcpy(c.PC, fake1, 2);
  memcpy((c.PC + 2), fake2, 2);
  skipIfPressed(&c, i, true, true);
  for (int i = 0; i < 2; i++) {
    EXPECT_EQ(fake1[i], *(c.PC + i));
  }
}

TEST(notSkipIfPressedTrueTest, skipIfPressed) {
  mem *m = buildMem();
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);

  unsigned char instruct[2] = {0xE0, 0xA1};
  instruction i = makeInstruction(instruct);
  unsigned char *V0 = getRegister(0);
  *V0 = 1;
  unsigned char fake1[2] = {0xFF, 0xFF};
  unsigned char fake2[2] = {0xDD, 0xDD};
  memcpy(c.PC, fake1, 2);
  memcpy((c.PC + 2), fake2, 2);
  skipIfPressed(&c, i, true, true);
  for (int i = 0; i < 2; i++) {
    EXPECT_EQ(fake2[i], *(c.PC + i));
  }
}

TEST(setVx2DTimerTest, setVX2DTimer) {
  mem *m = buildMem();
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);

  unsigned char instruct[2] = {0xF0, 0x07};
  instruction i = makeInstruction(instruct);
  unsigned char *V0 = getRegister(0);
  *V0 = 1;
  setVx2DelayTimer(&c, i);

  EXPECT_EQ(clockInit, *V0);
}

TEST(setDtimer2VXTest, setDtimer2VX) {
  mem *m = buildMem();
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);

  unsigned char instruct[2] = {0xF0, 0x15};
  instruction i = makeInstruction(instruct);
  unsigned char *V0 = getRegister(0);
  *V0 = 1;
  setDelayTimer2Vx(&c, i);

  EXPECT_EQ(c.dTimer->timer, *V0);
}

TEST(setStimer2VXTest, setStimer2VX) {
  mem *m = buildMem();
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);

  unsigned char instruct[2] = {0xF0, 0x18};
  instruction i = makeInstruction(instruct);
  unsigned char *V0 = getRegister(0);
  *V0 = 1;
  setSoundTimer2Vx(&c, i);

  EXPECT_EQ(c.sTimer->timer, *V0);
}

TEST(add2IndexTest, add2Index) {
  mem *m = buildMem();
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);

  unsigned char instruct[2] = {0xF0, 0x1E};
  instruction i = makeInstruction(instruct);
  unsigned char *V0 = getRegister(0);
  *V0 = 1;
  *c.indexRegister = 0x0;
  *(c.indexRegister) = 0x0;

  add2Index(&c, i);
  for (int i = 0; i < 2; i++) {
    EXPECT_EQ(i, *(c.indexRegister + i));
  }
}

TEST(getKeyTest, getKey) {
  mem *m = buildMem();
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);

  unsigned char instruct[2] = {0xF0, 0x0A};
  instruction i = makeInstruction(instruct);
  unsigned char *V0 = getRegister(0);
  *V0 = 1;
  getKey(&c, i, true);
  EXPECT_EQ(0x0, *V0);
}

TEST(fontCharTest, fontChar) {
  mem *m = buildMem();
  unsigned char expected = 0xff;
  *(m->RAM + fontStart + 2) = expected;
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);

  unsigned char instruct[2] = {0xF0, 0x29};
  instruction i = makeInstruction(instruct);
  unsigned char *V0 = getRegister(0);
  *V0 = 2;
  fontChar(&c, i);

  EXPECT_EQ(expected, *(c.memory->RAM + fontStart + 2));
}

TEST(binCodeDecTest, binCodeDec) {
  mem *m = buildMem();
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);

  unsigned char instruct[2] = {0xF0, 0x33};
  instruction i = makeInstruction(instruct);
  unsigned char *V0 = getRegister(0);
  *V0 = 0xff;

  binCodedDecConversion(&c, i);
  unsigned char expected[3] = {0x2, 0x5, 0x5};
  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(expected[i], *(c.indexRegister + i));
  }
}

TEST(storeTest, store) {
  mem *m = buildMem();
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);

  unsigned char instruct[2] = {0xF1, 0x55};
  instruction i = makeInstruction(instruct);
  unsigned char *V0 = getRegister(0);
  unsigned char *V1 = getRegister(1);
  *V0 = 0xff;
  *V1 = 0xaa;
  store(&c, i);
  
  unsigned char expected[2] = {0xff, 0xaa};
  for (int i = 0; i < 2; i++) {
    EXPECT_EQ(expected[i], *(c.indexRegister+i));
  }
}

TEST(loadTest, load) {
  mem *m = buildMem();
  display *d = makeDisplay();
  cpu c = makeCpu(m, d);

  unsigned char instruct[2] = {0xF1, 0x55};
  instruction i = makeInstruction(instruct);
  *(c.indexRegister) = 0xff;
  *(c.indexRegister + 1) = 0xaa;
  load(&c, i);
  unsigned char *V0 = getRegister(0);
  unsigned char *V1 = getRegister(1);
  unsigned char expected[2] = {0xff, 0xaa};
  EXPECT_EQ(*V0, expected[0]);
  EXPECT_EQ(*V1, expected[1]);
  
}


} // namespace
