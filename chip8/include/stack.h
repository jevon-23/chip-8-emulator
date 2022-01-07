#include <stdlib.h>
#include <stdbool.h>
#ifndef STACK_H
#define STACK_H

typedef struct stack {
    unsigned char **contents;
    int top;
    int maxLen;
} stack;

// https://en.wikipedia.org/wiki/CHIP-8#The_stack
// chip-8 allocated 48 bytes of memory for the stack
// we are using longs which are 8 bytes
// 48 bytes = 6 long ints
// going to give it a little bit of overhead just in case.
extern const int maxStackSize; // 80 bytes

// functions
stack *makeStack();
bool isEmpty(stack _stack);
bool isFull(stack _stack);
void push(stack **_stack, unsigned char *value);
unsigned char *pop(stack **_stack);
unsigned char *peak(stack **_stack);
#endif
