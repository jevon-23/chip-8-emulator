#include <stdbool.h>
/*
Just a mapping between the name of a file and the contents that file holds just
to make my life a little easier in the future Going to make all of these, the
head of the list will always be the the file that we are running search on
*/

#ifndef UTILS_H // header guard
#define UTILS_H

typedef struct aFile {
  char *name;      // Name of file
  unsigned char **contents; // Contents in file
  int fileSize;
} aFile;

aFile readFile(char *fileName);
void readContents(aFile theFile);
void printSpace();

#endif // PARSER_H
