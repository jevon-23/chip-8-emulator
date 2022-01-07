#include <gtest/gtest.h>
extern "C" {
    #include "../../../include/display.h"
}

namespace {
    TEST(makeDisplayTest, makeDisplay) {
        display *d = makeDisplay();
      for (int i = 0; i < numDisplayRows; i++) {
        for (int j = 0; j < numDisplayCols; j++) {
          EXPECT_EQ((*(*(d->visual + i) + j)), false);  
        }
      } 
    }
}
