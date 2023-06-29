#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct point2d {
  int x, y;
} point2d;

DECLARE_QUEUE(point_queue, point2d *)

DECLARE_QUEUE(string_queue, char *)

DECLARE_QUEUE(float_queue, float)

int main() {
  CREATE_QUEUE(point_queue, l)
  for (int i = 0; i < 5; i++) {
    point2d *p = (point2d *)malloc(sizeof(point2d));
    p->x = i;
    p->y = i;
    l->push(l, p);
  }
  FREE_QUEUE(point_queue, l)

  point2d **plist = (point2d **)malloc(sizeof(point2d *) * 9);
  for (int i = 0; i < 9; i++) {
    point2d *p = (point2d *)malloc(sizeof(point2d));
    p->x = i;
    p->y = i;
    plist[i] = p;
  }
  CREATE_QUEUE_ARRAY(point_queue, ll, plist, plist + 9)
  FREE_QUEUE(point_queue, ll)

  CREATE_QUEUE(string_queue, c);
  for (int i = 0; i < 5; i++) {
    c->push(c, "hello");
  }
  FREE_QUEUE(string_queue, c)

  float a[] = {1.1, 2.22, 3.333, 4.4444, 5.55555};
  CREATE_QUEUE_ARRAY(float_queue, fl, a, a + 5);
  FREE_QUEUE(float_queue, fl)

  return 0;
}
