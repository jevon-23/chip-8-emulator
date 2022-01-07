#include "../../include/stack.h"
#include <float.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maxStackSize = 10;
stack *makeStack() {
  stack *out = (stack *)malloc(sizeof(stack));
  out->contents = (unsigned char **)malloc((sizeof(unsigned char *)) * maxStackSize);
  for (int i = 0; i < maxStackSize; i++) {
    *(out->contents + i) = (unsigned char *) malloc(sizeof(unsigned char) * 2);
  }
  out->top = -1;
  out->maxLen = maxStackSize;
  return out;
}

int size(stack _stack) { return (_stack.top + 1); }

bool isEmpty(stack _stack) { return (_stack.top == -1); }

bool isFull(stack _stack) { return (_stack.top == _stack.maxLen - 1); }

void push(stack **_stack, unsigned char *value) {
  if (isFull(**_stack)) {
    printf("the stack has overflowed!\n\n");
    exit(-1);
  }
  (*_stack)->top++;
  memcpy(*((*_stack)->contents + (*_stack)->top), value, 2);
//  *((*_stack)->contents + (*_stack)->top) = value;
}

unsigned char *pop(stack **_stack) {
  if (!isEmpty(**_stack)) {
    (*_stack)->top--;
    return *((*_stack)->contents + (*_stack)->top + 1);
  }
  printf("the stack is empty\n\n");
  exit(-1);
}

unsigned char *peak(stack **_stack) {
  if (!isEmpty(**_stack)) {
    return *((*_stack)->contents + (*_stack)->top);
  }
  printf("the stack is empty\n\n");
  exit(-1);
}

