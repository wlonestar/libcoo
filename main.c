#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "stack.h"

/**
 * int stack
 */

DECLARE_STACK(int_stack, int)

static void int_stack_print(int_stack *self) {
  for (int i = 0; i < self->size(self); i++) {
    printf("%d ", self->data[i]);
  }
  printf("\n");
}

void test_int_stack(int_stack *stk) {
  assert(stk->empty(stk) == true);
  for (int i = 0; i < 10; i++) {
    stk->push(stk, i);
    assert(stk->top(stk) == i);
  }
  assert(stk->size(stk) == 10);
  stk->print(stk);
  for (int i = 0; i < 10; i++) {
    assert(stk->top(stk) == 9 - i);
    stk->pop(stk);
  }
  assert(stk->size(stk) == 0);
}

/**
 * float stack
 */

DECLARE_STACK(float_stack, float)

static void float_stack_print(float_stack *self) {
  for (int i = 0; i < self->size(self); i++) {
    printf("%f ", self->data[i]);
  }
  printf("\n");
}

void test_float_stack(float_stack *stk) {
  assert(stk->empty(stk) == true);
  for (int i = 0; i < 10; i++) {
    stk->push(stk, i);
    assert(stk->top(stk) == i);
  }
  assert(stk->size(stk) == 10);
  stk->print(stk);
  for (int i = 0; i < 10; i++) {
    assert(stk->top(stk) == 9 - i);
    stk->pop(stk);
  }
  assert(stk->size(stk) == 0);
}

/**
 * string stack
 */

DECLARE_STACK(string_stack, char *)

static void string_stack_print(string_stack *self) {
  for (int i = 0; i < self->size(self); i++) {
    printf("%s ", self->data[i]);
  }
  printf("\n");
}

void test_string_stack(string_stack *stk) {
  assert(stk->empty(stk) == true);
  for (int i = 0; i < 10; i++) {
    char *val = (char [2]) {'a' + i, '\0'};
    char *tmp = malloc(sizeof(char) * 2);
    strcpy(tmp, val);
    stk->push(stk, tmp);
    assert(stk->top(stk) == tmp);
  }
  assert(stk->size(stk) == 10);
  stk->print(stk);
  for (int i = 9; i >= 0; i--) {
    char *val = (char [2]) {'a' + i, '\0'};
    char *tmp = malloc(sizeof(char) * 2);
    strcpy(tmp, val);
    assert(strcmp(stk->top(stk), tmp) == 0);
    stk->pop(stk);
  }
  assert(stk->size(stk) == 0);
}

/**
 * struct stack
*/

typedef struct foo {
  int bar;
  float baz;
} foo;

DECLARE_STACK(foo_stack, foo)

static void foo_stack_print(foo_stack *self) {
  for (int i = 0; i < self->size(self); i++) {
    printf("(%d %f) ", self->data[i].bar, self->data[i].baz);
  }
  printf("\n");
}

void test_foo_stack(foo_stack *stk) {
  assert(stk->empty(stk) == true);
  for (int i = 0; i < 10; i++) {
    foo f = { .bar = i, .baz = i * 0.1f };
    stk->push(stk, f);
    assert(stk->top(stk).bar == f.bar && stk->top(stk).baz == f.baz);
  }
  assert(stk->size(stk) == 10);
  stk->print(stk);
  for (int i = 9; i >= 0; i--) {
    assert(stk->top(stk).bar == i && stk->top(stk).baz == i * 0.1f);
    stk->pop(stk);
  }
  assert(stk->size(stk) == 0);
}

int main() {
  CREATE_STACK(int_stack, stk1)
  stk1->print = int_stack_print;

  CREATE_STACK(float_stack, stk2)
  stk2->print = float_stack_print;
  
  CREATE_STACK(string_stack, stk3)
  stk3->print = string_stack_print;
  
  CREATE_STACK(foo_stack, stk4)
  stk4->print = foo_stack_print;

  test_int_stack(stk1);
  test_float_stack(stk2);
  test_string_stack(stk3);
  test_foo_stack(stk4);

  FREE_STACK(stk1)
  FREE_STACK(stk2)
  FREE_STACK(stk3)
  FREE_STACK(stk4)

  return 0;
}
