#include <stdbool.h>
#ifndef DISPLAY_H
#define DISPLAY_H

/* Displays are 64 pixels wide (cols) by 32 pixels high (colums).
 * Pixels can be "on or off" => we will repr them as booleans =>
 * Display will be a list of booleans, which will be turned on and
 * off when necessary.
 */

#define numDisplayRows 32
#define numDisplayCols 64

#define clockSpeedhz 60 // hz
#define clockSpeedMs 17 // ms

typedef struct display {
    bool **visual; // bool array repr our screen
} display;

#define displaySize (sizeof(display) + (sizeof(bool) *(numDisplayRows * numDisplayCols)))

// functions

display *makeDisplay();
#endif
