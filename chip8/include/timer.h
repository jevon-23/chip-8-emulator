#include <time.h>
#ifndef TIMER_H
#define TIMER_H
/*
 *"They both work the same way; they’re one byte in size, and as long as their
 *value is above 0, they should be decremented by one 60 times per second (ie.
 *at 60 Hz)."
 */
#define clockInit 60

typedef struct delayTimer {
  char timer;
  time_t start;
} delayTimer;

typedef struct soundTimer {
  int timer;
  time_t start;
} soundTimer;

delayTimer *makeDelayTimer();
void decrementDelayTimer(delayTimer *clock);
soundTimer *makeSoundTimer();
void decrementSoundTimer(soundTimer *clock);
#endif
