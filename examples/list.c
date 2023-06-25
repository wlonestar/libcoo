#include "list.h"

typedef struct point2d {
  int x, y;
} point2d;

DECLARE_LIST(point_list, point2d*)

static void point_list_print(point_list *self) {
  printf("point list: [ ");
  for (point_list_node *p = self->begin(self); p != self->end(self); p = p->next) {
    printf("[%d, %d] ", p->data->x, p->data->y);
  }
  printf("]\n");
}

DECLARE_LIST(string_list, char *)

static void string_list_print(string_list *self) {
  printf("string list: [ ");
  for (string_list_node *p = self->begin(self); p != self->end(self); p = p->next) {
    printf("%s ", p->data);
  }
  printf("]\n");
}

int main() {
  CREATE_LIST(point_list, l);
  l->print = point_list_print;
  for (int i = 0; i < 5; i++) {
    point2d *p = (point2d *) malloc(sizeof(point2d));
    p->x = i;
    p->y = i;
    l->push_back(l, p);    
  }
  l->print(l);

  CREATE_LIST(string_list, c);
  c->print = string_list_print;
  for (int i = 0; i < 5; i++) {
    c->push_back(c, "hello");
  }
  c->print(c);

  return 0;
}
