#include "stack.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

DECLARE_STACK(stack, int)

void test_stack_ctor() {
  {
    int a[] = {0, 1, 2, 3, 4};
    CREATE_STACK_ARRAY(stack, q, a, a + 5);
    assert(q->size(q) == 5);
    int i = 4;
    while (!q->empty(q)) {
      assert(q->top(q) == a[i]);
      q->pop(q);
      i--;
    }
    FREE_STACK(stack, q);
  }
  {
    CREATE_STACK(stack, q);
    assert(q->size(q) == 0);
    q->push(q, 1);
    assert(q->size(q) == 1);
    assert(q->top(q) == 1);
    q->push(q, 2);
    assert(q->size(q) == 2);
    assert(q->top(q) == 2);
    FREE_STACK(stack, q);
  }
  {
    int a[] = {4, 3, 2, 1};
    CREATE_STACK_ARRAY(stack, q, a, a + 4)
    assert(q->top(q) == 1);
    q->pop(q);
    assert(q->top(q) == 2);
    q->pop(q);
    assert(q->top(q) == 3);
    q->pop(q);
    assert(q->top(q) == 4);
    q->pop(q);
    assert(q->empty(q));
    FREE_STACK(stack, q);
  }
}

void test_stack_cons() { test_stack_ctor(); }

void test_stack_top() {
  CREATE_STACK(stack, q);
  assert(q->size(q) == 0);
  q->push(q, 1);
  q->push(q, 2);
  q->push(q, 3);
  int val = q->top(q);
  assert(val == 3);
  FREE_STACK(stack, q);
}

void test_stack_empty() {
  CREATE_STACK(stack, q);
  assert(q->empty(q));
  q->push(q, 1);
  assert(!q->empty(q));
  q->pop(q);
  assert(q->empty(q));
  FREE_STACK(stack, q);
}

void test_stack_size() {
  CREATE_STACK(stack, q);
  assert(q->size(q) == 0);
  q->push(q, 1);
  assert(q->size(q) == 1);
  FREE_STACK(stack, q);
}

void test_stack_push() {
  CREATE_STACK(stack, q);
  q->push(q, 1);
  assert(q->size(q) == 1);
  assert(q->top(q) == 1);
  q->push(q, 2);
  assert(q->size(q) == 2);
  assert(q->top(q) == 2);
  q->push(q, 3);
  assert(q->size(q) == 3);
  assert(q->top(q) == 3);
  FREE_STACK(stack, q);
}

void test_stack_pop() {
  CREATE_STACK(stack, q);
  assert(q->size(q) == 0);
  q->push(q, 1);
  q->push(q, 2);
  q->push(q, 3);
  assert(q->size(q) == 3);
  assert(q->top(q) == 3);
  q->pop(q);
  assert(q->size(q) == 2);
  assert(q->top(q) == 2);
  q->pop(q);
  assert(q->size(q) == 1);
  assert(q->top(q) == 1);
  q->pop(q);
  assert(q->size(q) == 0);
  FREE_STACK(stack, q);
}

void test_stack_swap() {
  int a1[] = {0, 1, 2, 3, 4};
  int a2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  CREATE_STACK_ARRAY(stack, q1, a1, a1 + 5);
  CREATE_STACK_ARRAY(stack, q2, a2, a2 + 10);
  q1->swap(q1, q2);
  FREE_STACK(stack, q1);
  FREE_STACK(stack, q2);
}

void test_stack_defn() {
  test_stack_top();
  test_stack_empty();
  test_stack_size();
  test_stack_push();
  test_stack_pop();
  test_stack_swap();
}

int main() {
  test_stack_cons();
  test_stack_defn();
  return 0;
}
