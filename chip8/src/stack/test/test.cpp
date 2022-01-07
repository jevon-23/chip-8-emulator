#include <gtest/gtest.h>
#include <string.h>
extern "C" {
#include "../../../include/stack.h"
}

namespace {
TEST(makeStackTest, makeStack) {
  stack *s = makeStack();
  EXPECT_EQ(s->top, -1);
}
TEST(isEmptyTest, isEmpty) {
  stack *s = makeStack();
  EXPECT_EQ(isEmpty(*s), true);
}

TEST(isFullTest, isFull) {
  stack *s = makeStack();
  EXPECT_EQ(isFull(*s), false);
}

TEST(pushTest, push) {
  stack *s = makeStack();
  unsigned char *expected = (unsigned char *)malloc(sizeof(unsigned char) * 2);
  *expected = (unsigned char)'a';
  *(expected + 1) = (unsigned char)'z';
  push(&s, expected);
  unsigned char *out = peak(&s);
  EXPECT_EQ(*out, 'a');
  EXPECT_EQ(*(out + 1), 'z');
}

TEST(popTest, pop) {
  stack *s = makeStack();
  unsigned char *expected = (unsigned char *)malloc(sizeof(unsigned char) * 2);
  *expected = (unsigned char)'a';
  *(expected + 1) = (unsigned char)'z';
  push(&s, expected);
  unsigned char *out = pop(&s);
  EXPECT_EQ(*out, 'a');
  EXPECT_EQ(*(out + 1), 'z');
}

} // namespace
