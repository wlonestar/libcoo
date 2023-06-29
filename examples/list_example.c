#include "list.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct point2d {
  int x, y;
} point2d;

DECLARE_LIST(point_list, point2d *)

static void point_list_print(point_list *self) {
  printf("point list: [ ");
  for (point_list_node *p = self->begin(self); p != self->end(self);
       p = p->next) {
    printf("[%d, %d] ", p->data->x, p->data->y);
  }
  printf("]\n");
}

DECLARE_LIST(string_list, char *)

static void string_list_print(string_list *self) {
  printf("string list: [ ");
  for (string_list_node *p = self->begin(self); p != self->end(self);
       p = p->next) {
    printf("%s ", p->data);
  }
  printf("]\n");
}

DECLARE_LIST(float_list, float)

static void float_list_print(float_list *self) {
  printf("float list: [ ");
  for (float_list_node *p = self->begin(self); p != self->end(self);
       p = p->next) {
    printf("%f ", p->data);
  }
  printf("]\n");
}

int main() {
  CREATE_LIST(point_list, l)
  l->print = point_list_print;
  for (int i = 0; i < 5; i++) {
    point2d *p = (point2d *)malloc(sizeof(point2d));
    p->x = i;
    p->y = i;
    l->push_back(l, p);
  }
  l->print(l);
  FREE_LIST(point_list, l)

  point2d **plist = (point2d **)malloc(sizeof(point2d *) * 9);
  for (int i = 0; i < 9; i++) {
    point2d *p = (point2d *)malloc(sizeof(point2d));
    p->x = i;
    p->y = i;
    plist[i] = p;
  }
  CREATE_LIST_ARRAY(point_list, ll, plist, plist + 9)
  ll->print = point_list_print;
  ll->print(ll);
  FREE_LIST(point_list, ll)

  CREATE_LIST(string_list, c);
  c->print = string_list_print;
  for (int i = 0; i < 5; i++) {
    c->push_back(c, "hello");
  }
  c->print(c);
  FREE_LIST(string_list, c)

  float a[] = {1.1, 2.22, 3.333, 4.4444, 5.55555};
  CREATE_LIST_ARRAY(float_list, fl, a, a + 5);
  fl->print = float_list_print;
  fl->print(fl);
  FREE_LIST(float_list, fl)

  return 0;
}
