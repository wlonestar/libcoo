#include "rbtree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_string(char *s) { printf("%s", s); }

DECLARE_RBTREE(string_rbtree, char *, print_string)

bool string_comp(char *s1, char *s2) {
  return strcmp(s1, s2) <= 0 ? true : false;
}

void test_string_rbtree() {
  CREATE_RBTREE_COMP(string_rbtree, t, string_comp)
  for (int i = 0; i < 5; i++) {
    char *buf = (char *)malloc(sizeof(char) * 16);
    snprintf(buf, 15, "str%d", i);
    t->insert(t, buf);
  }
  t->print(t);
  t->pre_order(t);
  t->in_order(t);
  t->post_order(t);
  t->level_order(t);
  FREE_RBTREE(string_rbtree, t)
}

void print_float(float v) {
  printf("%.2f", v);
}

DECLARE_RBTREE(float_rbtree, float, print_float)

bool float_comp(float a, float b) {
  return a >= b;
}

void test_float_rbtree() {
  CREATE_RBTREE_COMP(float_rbtree, t, float_comp)
  for (int i = 0; i < 10; i++) {
    int base = rand() % 100;
    int scale = rand() % 10;
    float val = base * (scale * 1.0) / 100.0;
    t->insert(t, val);
  }
  t->print(t);
  t->pre_order(t);
  t->in_order(t);
  t->post_order(t);
  t->level_order(t);
  FREE_RBTREE(float_rbtree, t)
}

int main() {
  test_string_rbtree();
  test_float_rbtree();
  return 0;
}
