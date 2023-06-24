#ifndef list_h
#define list_h

#include "alloc.h"

typedef struct list_node {
  int data;
  struct list_node *prev, *next;
} list_node;

typedef struct list {
  list_node *_head;
  size_t _size;

  int (*front)(struct list *self);
  int (*back)(struct list *self);

  struct list_node *(*begin)(struct list *self);
  struct list_node *(*end)(struct list *self);

  bool (*empty)(struct list *self);
  size_t (*size)(struct list *self);

  void (*clear)(struct list *self);
  struct list_node *(*insert)(struct list *self, struct list_node *pos,
                              int value);
  struct list_node *(*insert_n)(struct list *self, struct list_node *pos,
                                size_t count, int value);
  struct list_node *(*insert_range)(struct list *self, struct list_node *pos,
                                    int *first, int *last);
  struct list_node *(*erase)(struct list *self, struct list_node *pos);
  struct list_node *(*erase_range)(struct list *self, struct list_node *first,
                                   struct list_node *last);
  void (*push_back)(struct list *self, int value);
  void (*push_front)(struct list *self, int value);
  void (*pop_back)(struct list *self);
  void (*pop_front)(struct list *self);
  void (*resize)(struct list *self, size_t count);
  void (*resize_value)(struct list *self, size_t count, int value);
  void (*swap)(struct list *self, struct list *other);

  void (*merge)(struct list *self, struct list *other);
  void (*merge_by)(struct list *self, struct list *other,
                   bool (*cmp)(int a, int b));
  void (*splice)(struct list *self, struct list_node *pos, struct list *other);
  void (*splice_from)(struct list *self, struct list_node *pos,
                      struct list *other, struct list_node *it);
  void (*splice_range)(struct list *self, struct list_node *pos,
                       struct list *other, struct list_node *first,
                       struct list_node *last);
  size_t (*remove)(struct list *self, int value);
  size_t (*remove_if)(struct list *self, bool (*pred)(int n));
  void (*reverse)(struct list *self);
  size_t (*unique)(struct list *self);
  size_t (*unique_by)(struct list *self, bool (*p)(int a, int b));
  void (*sort)(struct list *self);
  void (*sort_by)(struct list *self, bool (*cmp)(int a, int b));

  void (*print)(struct list *self); /* for debug */
} list;

// implementations here

static int list_front(struct list *self) { return self->_head->next->data; }

static int list_back(struct list *self) { return self->_head->prev->data; }

//

static struct list_node *list_begin(struct list *self) {
  return self->_head->next;
}

static struct list_node *list_end(struct list *self) { return self->_head; }

//

static bool list_empty(struct list *self) { return self->_size == 0; }

static size_t list_size(struct list *self) { return self->_size; }

//

static void list_clear(struct list *self) {
  while (self->_size != 0) {
    self->pop_back(self);
  }
}

static struct list_node *list_insert(struct list *self, struct list_node *pos,
                                     int value) {
  struct list_node *new_node =
      (struct list_node *)malloc(sizeof(struct list_node));
  new_node->data = value;
  new_node->next = pos;
  new_node->prev = pos->prev;
  pos->prev->next = new_node;
  pos->prev = new_node;
  self->_size++;
  return new_node;
}

static struct list_node *list_insert_n(struct list *self, struct list_node *pos,
                                       size_t count, int value) {
  if (count == 0) {
    return pos;
  }
  struct list_node *ret = pos->prev;
  for (int i = 0; i < count; i++) {
    self->insert(self, pos, value);
  }
  return ret->next;
}

static struct list_node *list_insert_range(struct list *self,
                                           struct list_node *pos, int *first,
                                           int *last) {
  if (first == last) {
    return pos;
  }
  struct list_node *ret = pos->prev;
  for (int *p = first; p != last; p++) {
    pos = self->insert(self, pos, *p);
    pos = pos->next;
  }
  return ret->next;
}

static struct list_node *list_erase(struct list *self, struct list_node *pos) {
  struct list_node *ret = pos->next;
  pos->prev->next = pos->next;
  pos->next->prev = pos->prev;
  self->_size--;
  return ret;
}

static struct list_node *list_erase_range(struct list *self,
                                          struct list_node *first,
                                          struct list_node *last) {
  struct list_node *p = first;
  while (p != last->next) {
    p = self->erase(self, p);
  }
  return p;
}

static void list_push_back(struct list *self, int value) {
  struct list_node *new_node =
      (struct list_node *)malloc(sizeof(struct list_node));
  new_node->data = value;
  new_node->prev = self->_head->prev;
  new_node->next = self->_head;
  self->_head->prev->next = new_node;
  self->_head->prev = new_node;
  self->_size++;
}

static void list_push_front(struct list *self, int value) {
  struct list_node *new_node =
      (struct list_node *)malloc(sizeof(struct list_node));
  new_node->data = value;
  new_node->prev = self->_head;
  new_node->next = self->_head->next;
  self->_head->next->prev = new_node;
  self->_head->next = new_node;
  self->_size++;
}

static void list_pop_back(struct list *self) {
  self->_head->prev->prev->next = self->_head;
  self->_head->prev = self->_head->prev->prev;
  self->_size--;
}

static void list_pop_front(struct list *self) {
  self->_head->next->next->prev = self->_head;
  self->_head->next = self->_head->next->next;
  self->_size--;
}

static void list_resize(struct list *self, size_t count) {
  if (count == self->_size) {
    return;
  } else if (self->_size > count) {
    while (self->_size > count) {
      self->pop_back(self);
    }
  } else {
    int addi = count - self->_size;
    for (int i = 0; i < addi; i++) {
      self->push_back(self, 0);
    }
  }
}

static void list_resize_value(struct list *self, size_t count, int value) {
  if (count == self->_size) {
    return;
  } else if (self->_size > count) {
    while (self->_size > count) {
      self->pop_back(self);
    }
  } else {
    int addi = count - self->_size;
    for (int i = 0; i < addi; i++) {
      self->push_back(self, value);
    }
  }
}

static void list_swap(struct list *self, struct list *other) {
  struct list_node *tmp = self->_head;
  self->_head = other->_head;
  other->_head = tmp;

  size_t tmp_s = self->_size;
  self->_size = other->_size;
  other->_size = tmp_s;
}

//

static void list_merge(struct list *self, struct list *other) {
  if (self == other) {
    return;
  }
  struct list_node *p = self->begin(self), *q = other->begin(other);
  while (q != other->_head) {
    if (p->data > q->data) {
      self->insert(self, p, q->data);
    } else {
      struct list_node *r = p;
      while (r != self->_head) {
        if (r->data > q->data) {
          break;
        }
        r = r->next;
      }
      p = self->insert(self, r, q->data);
    }
    q = other->erase(other, q);
  }
}

static void list_merge_by(struct list *self, struct list *other,
                          bool (*cmp)(int a, int b)) {
  if (self == other) {
    return;
  }
  struct list_node *p = self->begin(self), *q = other->begin(other);
  while (q != other->_head) {
    if (!cmp(p->data, q->data)) {
      self->insert(self, p, q->data);
    } else {
      struct list_node *r = p;
      while (r != self->_head) {
        if (!cmp(r->data, q->data)) {
          break;
        }
        r = r->next;
      }
      p = self->insert(self, r, q->data);
    }
    q = other->erase(other, q);
  }
}

static void list_splice(struct list *self, struct list_node *pos,
                        struct list *other) {
  struct list_node *p = pos;
  struct list_node *i = other->begin(other);
  while (i != other->_head) {
    p = self->insert(self, p, i->data);
    p = p->next;
    i = other->erase(other, i);
  }
}

static void list_splice_from(struct list *self, struct list_node *pos,
                             struct list *other, struct list_node *it) {
  struct list_node *p = pos;
  struct list_node *i = it;
  self->insert(self, p, i->data);
  other->erase(other, i);
}

static void list_splice_range(struct list *self, struct list_node *pos,
                              struct list *other, struct list_node *first,
                              struct list_node *last) {
  struct list_node *p = pos;
  struct list_node *i = first;
  while (i != last) {
    p = self->insert(self, p, i->data);
    p = p->next;
    i = other->erase(other, i);
  }
}

static size_t list_remove(struct list *self, int value) {
  size_t ret = 0;
  struct list_node *p = self->begin(self);
  while (p != self->_head) {
    if (p->data == value) {
      p = self->erase(self, p);
      ret++;
    } else {
      p = p->next;
    }
  }
  return ret;
}

static size_t list_remove_if(struct list *self, bool (*pred)(int n)) {
  size_t ret = 0;
  struct list_node *p = self->begin(self);
  while (p != self->_head) {
    if (pred(p->data)) {
      p = self->erase(self, p);
      ret++;
    } else {
      p = p->next;
    }
  }
  return ret;
}

static void list_reverse(struct list *self) {
  size_t times = self->_size / 2;
  struct list_node *p = self->_head->next;
  struct list_node *q = self->_head->prev;
  int i = 0;
  while (i < times) {
    int tmp = p->data;
    p->data = q->data;
    q->data = tmp;
    p = p->next;
    q = q->prev;
    i++;
  }
}

static size_t list_unique(struct list *self) {
  if (self->_size < 2) {
    return 0;
  }
  size_t old_size = self->_size;
  struct list_node *p = self->begin(self);
  struct list_node *l, *r;
  while (p != self->_head) {
    l = p->next;
    if (p->data == l->data) {
      r = l->next;
      while (r != self->_head) {
        if (r->data == l->data) {
          r = r->next;
        } else {
          break;
        }
      }
      p = self->erase_range(self, l, r);
    } else {
      p = p->next;
    }
  }
  return old_size - self->_size;
}

static size_t list_unique_by(struct list *self, bool (*pred)(int a, int b)) {
  if (self->_size < 2) {
    return 0;
  }
  size_t old_size = self->_size;
  struct list_node *p = self->_head->next;
  struct list_node *l, *r;
  while (p != self->_head) {
    l = p->next;
    if (pred(p->data, l->data)) {
      r = l->next;
      while (r != self->_head) {
        if (pred(r->data, l->data)) {
          r = r->next;
        } else {
          break;
        }
      }
      p = self->erase_range(self, l, r);
    } else {
      p = p->next;
    }
  }
  return old_size - self->_size;
}

static void list_sort(struct list *self) {
  struct list_node *j = self->begin(self)->next;
  while (j != self->_head) {
    struct list_node *i = j->prev;
    while (i != self->_head && i->data > j->data) {
      i = i->prev;
    }
    int value = j->data;
    j = self->erase(self, j);
    self->insert(self, i->next, value);
  }
}

static void list_sort_by(struct list *self, bool (*cmp)(int a, int b)) {
  struct list_node *j = self->begin(self)->next;
  while (j != self->_head) {
    struct list_node *i = j->prev;
    while (i != self->_head && !cmp(i->data, j->data)) {
      i = i->prev;
    }
    int value = j->data;
    j = self->erase(self, j);
    self->insert(self, i->next, value);
  }
}

static void list_print(struct list *self) {
  printf("list: [ ");
  for (struct list_node *p = self->_head->next; p != self->_head; p = p->next) {
    printf("%d ", p->data);
  }
  printf("]\n");
}

//

static void list_init_head(struct list *obj) {
  obj->_head = (struct list_node *)malloc(sizeof(struct list_node));
  obj->_head->data = -114514; /* for int type */
  obj->_head->prev = obj->_head;
  obj->_head->next = obj->_head;
}

static void list_assign_method(struct list *obj) {
  obj->front = list_front;
  obj->back = list_back;

  obj->begin = list_begin;
  obj->end = list_end;

  obj->empty = list_empty;
  obj->size = list_size;

  obj->clear = list_clear;
  obj->insert = list_insert;
  obj->insert_n = list_insert_n;
  obj->insert_range = list_insert_range;
  obj->erase = list_erase;
  obj->erase_range = list_erase_range;
  obj->push_back = list_push_back;
  obj->push_front = list_push_front;
  obj->pop_back = list_pop_back;
  obj->pop_front = list_pop_front;
  obj->resize = list_resize;
  obj->resize_value = list_resize_value;
  obj->swap = list_swap;

  obj->merge = list_merge;
  obj->merge_by = list_merge_by;
  obj->splice = list_splice;
  obj->splice_from = list_splice_from;
  obj->splice_range = list_splice_range;
  obj->remove = list_remove;
  obj->remove_if = list_remove_if;
  obj->reverse = list_reverse;
  obj->unique = list_unique;
  obj->unique_by = list_unique_by;
  obj->sort = list_sort;
  obj->sort_by = list_sort_by;

  obj->print = list_print;
}

static struct list *malloc_list() {
  return (struct list *)malloc(sizeof(struct list));
}

static struct list *init_list() {
  struct list *obj = malloc_list();
  list_init_head(obj);
  obj->_size = 0;
  list_assign_method(obj);
  return obj;
}

static struct list *init_list_n(size_t count, int value) {
  struct list *obj = init_list();
  for (int i = 0; i < count; i++) {
    obj->push_back(obj, value);
  }
  return obj;
}

static struct list *init_list_array(int *begin, int *end) {
  struct list *obj = init_list();
  for (int *p = begin; p != end; p++) {
    obj->push_back(obj, *p);
  }
  return obj;
}

void free_list(struct list *self) {
  self->clear(self);
  free(self->_head);
  free(self);
}

#endif
