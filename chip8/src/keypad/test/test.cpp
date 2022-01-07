#include <gtest/gtest.h>
extern "C" {
    #include "../../../include/keypad.h"
}

namespace {
    TEST(keyboard2keypadTest, keyboard2keypad) {
        EXPECT_EQ('4', keyboard2keypad('q'));
    }
}
