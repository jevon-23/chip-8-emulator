#include "../../include/display.h"
#include <stdbool.h>
#include <stdlib.h>

display *makeDisplay() {
    display *out = (display *) malloc(displaySize);
    out->visual = (bool **) malloc(sizeof(bool *) * numDisplayRows);
    for (int i = 0; i < numDisplayRows; i++) {
        *((out->visual) + i) = (bool *) calloc(numDisplayCols, sizeof(bool));
    }
    return out;
}
