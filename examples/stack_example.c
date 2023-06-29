#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct point2d {
  int x, y;
} point2d;

DECLARE_STACK(point_stack, point2d *)

DECLARE_STACK(string_stack, char *)

DECLARE_STACK(float_stack, float)

int main() {
  CREATE_STACK(point_stack, l)
  for (int i = 0; i < 5; i++) {
    point2d *p = (point2d *)malloc(sizeof(point2d));
    p->x = i;
    p->y = i;
    l->push(l, p);
  }
  FREE_STACK(point_stack, l)

  point2d **plist = (point2d **)malloc(sizeof(point2d *) * 9);
  for (int i = 0; i < 9; i++) {
    point2d *p = (point2d *)malloc(sizeof(point2d));
    p->x = i;
    p->y = i;
    plist[i] = p;
  }
  CREATE_STACK_ARRAY(point_stack, ll, plist, plist + 9)
  FREE_STACK(point_stack, ll)

  CREATE_STACK(string_stack, c);
  for (int i = 0; i < 5; i++) {
    c->push(c, "hello");
  }
  FREE_STACK(string_stack, c)

  float a[] = {1.1, 2.22, 3.333, 4.4444, 5.55555};
  CREATE_STACK_ARRAY(float_stack, fl, a, a + 5);
  FREE_STACK(float_stack, fl)

  return 0;
}
