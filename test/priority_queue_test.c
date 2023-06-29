#include "priority_queue.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

DECLARE_PRIORITY_QUEUE(priority_queue, int)

int main() {
  CREATE_PRIORITY_QUEUE(priority_queue, q)
  for (int i = 0; i < 10; i++) {
    q->push(q, i);
    int val = q->top(q);
    printf("max value: %d\n", val);
  }
  for (int i = 0; i < 10; i++) {
    int val = q->top(q);
    q->pop(q);
    printf("del value: %d\n", val);
  }
  assert(q->size(q) == 0);
}
