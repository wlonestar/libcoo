#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct point2d {
  int x, y;
} point2d;

DECLARE_VECTOR(point_vector, point2d)

static void point_vector_print(point_vector *self) {
  printf("point list: [ ");
  for (point2d *p = self->begin(self); p != self->end(self); p++) {
    printf("[%d, %d] ", p->x, p->y);
  }
  printf("]\n");
}

DECLARE_VECTOR(string_vector, char *)

static void string_vector_print(string_vector *self) {
  printf("string list: [ ");
  for (int i = 0; i < self->size(self); i++) {
    printf("%s ", self->data(self)[i]);
  }
  printf("]\n");
}

DECLARE_VECTOR(float_vector, float)

static void float_vector_print(float_vector *self) {
  printf("float list: [ ");
  for (int i = 0; i < self->size(self); i++) {
    printf("%f ", self->data(self)[i]);
  }
  printf("]\n");
}

int main() {
  CREATE_VECTOR(point_vector, v)
  v->print = point_vector_print;
  for (int i = 0; i < 5; i++) {
    point2d d = {i, i};
    v->push_back(v, d);
  }
  v->print(v);
  FREE_VECTOR(point_vector, v)

  point2d *plist = (point2d *)malloc(sizeof(point2d) * 9);
  for (int i = 0; i < 9; i++) {
    point2d d = {i, i};
    plist[i] = d;
  }
  CREATE_VECTOR_ARRAY(point_vector, ll, plist, plist + 9)
  ll->print = point_vector_print;
  ll->print(ll);
  FREE_VECTOR(point_vector, ll)

  CREATE_VECTOR(string_vector, c)
  c->print = string_vector_print;
  for (int i = 0; i < 5; i++) {
    c->push_back(c, "hello");
  }
  c->print(c);
  FREE_VECTOR(string_vector, c)

  float a[] = {1.1, 2.22, 3.333, 4.4444, 5.55555};
  CREATE_VECTOR_ARRAY(float_vector, fl, a, a + 5);
  fl->print = float_vector_print;
  fl->print(fl);

  return 0;
}
