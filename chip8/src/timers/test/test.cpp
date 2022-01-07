#include <gtest/gtest.h>
extern "C" {
#include "../../../include/timer.h"
}

namespace {
TEST(makeDelayTimerTest, makeDelayTimer) {
  delayTimer *t = makeDelayTimer();
  EXPECT_EQ(clockInit, t->timer);
}

TEST(makeSoundTimerTest, makeSoundTimer) {
  soundTimer *t = makeSoundTimer();
  EXPECT_EQ(clockInit, t->timer);
}

TEST(decrementDelayTimerTest, decrementDelayTimer) {
  delayTimer *t = makeDelayTimer();
  decrementDelayTimer(t);
  EXPECT_EQ(clockInit - 1, t->timer);
}

TEST(decrementSoundTimerTest, decrementSoundTimer) {
  soundTimer *t = makeSoundTimer();
  decrementSoundTimer(t);
  EXPECT_EQ(clockInit - 1, t->timer);
}
} // namespace
