#include <cstdio>
#include <gtest/gtest.h>
extern "C" {
#include "../../../include/instructions.h"
}

namespace {
TEST(get4bitsTest, get4bits) {
  unsigned char bString = 155; // 9b
  unsigned char b1 = get4bits(bString, 0);
  unsigned char b2 = get4bits(bString, 4);
  printf("bString = %x ~ b1 = %x ~ b2 = %x\n", bString, b1, b2);
  EXPECT_EQ(b1, '\t'); // 0x09 = \t in ascii
  EXPECT_EQ(b2, '\v'); // 0x0b = \v in ascii
}

TEST(makeInstructionTest, makeInstruction) {
  unsigned char *bStrings = (unsigned char *)malloc(sizeof(unsigned char) * 2);
  unsigned char b1 = '\xAF';
  unsigned char b2 = '\xBD';
  *bStrings = b1;       // 0x9b
  *(bStrings + 1) = b2; // 0xd9
  instruction val = makeInstruction(bStrings);
  EXPECT_EQ(val.type, '\x0A');
  EXPECT_EQ(val.x, '\x0F');
  EXPECT_EQ(val.y, '\x0B');
  EXPECT_EQ(val.n, '\x0D');
  EXPECT_EQ(val.nn, b2); // been here for ab 3 hours and just found this
                             // out... thuoght it was %
  EXPECT_EQ(*val.nnn, '\x0F');
  EXPECT_EQ(*(val.nnn + 1), b2);
}
} // namespace
