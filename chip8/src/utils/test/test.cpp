#include <gtest/gtest.h>
#include <string.h>
extern "C" {
#include "../../../include/utils.h"
#include <unistd.h>
}

namespace {
TEST(readFileTest, readFile) {
  char fp[200];
  getcwd(fp, sizeof(fp));
  strcat(fp, "/src/utils/test/help.txt");
  aFile theFile = readFile(fp);
  EXPECT_EQ(**theFile.contents, 'g'); // broken down in terms of u_char
}
} // namespace
