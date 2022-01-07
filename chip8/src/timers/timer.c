#include "../../include/timer.h"
#include <float.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void waitSec(time_t startTime) {
    time_t currTime;
    time(&currTime);
    if (difftime(currTime, startTime) >= 1) {
        return;
    }
    // put into inf loop so that it only stops after 1 min as past.
    return waitSec(startTime);
}

delayTimer *makeDelayTimer() {
    delayTimer *out = (delayTimer *) malloc(sizeof(delayTimer));
    out->timer = clockInit;
    time(&(out->start));
    return out;
}

void decrementDelayTimer(delayTimer *clock) {
    // should be decremented by 60 every 1 minute (60 seconds). might need to use some clock func we gon see in a sec.
    if (clock->timer == 0) {
        waitSec(clock->start);
        (*clock).timer = clockInit;
        return;
    } else if (clock->timer > 60) {
        printf("outside of range for timers\n");
        exit(-1);
    }
    (*clock).timer--;
}

soundTimer *makeSoundTimer() {
    soundTimer *out = (soundTimer *) malloc(sizeof(soundTimer));
    out->timer = clockInit;
    time(&(out->start));
    return out;
}

void decrementSoundTimer(soundTimer *clock) {
    // should be decremented by 60 every 1 minute (60 seconds). might need to use some clock func we gon see in a sec.
    if (clock->timer == 0) {
        waitSec(clock->start);
        (*clock).timer = clockInit;
        return;
    } else if (clock->timer > 60) {
        printf("outside of range for timers\n");
        exit(-1);
    }
    (*clock).timer--;
    printf("making a sound! \n");
}


