#include <gtest/gtest.h>
extern "C" {
#include "../../../include/mem.h"
#include "../../../include/utils.h"
}

namespace {

TEST(buildMemTest, buildMem) {
  mem *out = buildMem();
  int memCounter = 0;
  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 5; j++, memCounter++) {
      EXPECT_EQ(font[i][j], *(out->RAM + (fontStart + memCounter)));
    }
  }
}
TEST(writeGameFileTest, writeGameFile) {
  mem *testMem = buildMem();
  char fp[200];
  getcwd(fp, sizeof(fp));
  strcat(fp, "/src/memory/test/help.txt");
  aFile theFile = readFile(fp);
  writeGameFile(&testMem, theFile);
  EXPECT_EQ('g', *(testMem->RAM + (interpEnding)));
}

} // namespace
