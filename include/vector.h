#ifndef vector_h
#define vector_h

#include "alloc.h"

typedef struct vector {
  int *_data;
  size_t _capacity;
  size_t _size;

  void (*assign)(struct vector *self, size_t count, int value);
  void (*assign_range)(struct vector *self, int *first, int *last);

  int (*at)(struct vector *self, size_t pos);
  int (*front)(struct vector *self);
  int (*back)(struct vector *self);
  int *(*data)(struct vector *self);

  int *(*begin)(struct vector *self);
  int *(*end)(struct vector *self);

  bool (*empty)(struct vector *self);
  size_t (*size)(struct vector *self);
  void (*reserve)(struct vector *self, size_t new_cap);
  size_t (*capacity)(struct vector *self);
  void (*shrink_to_fit)(struct vector *self);

  void (*clear)(struct vector *self);
  int *(*insert)(struct vector *self, int *pos, int value);
  int *(*insert_n)(struct vector *self, int *pos, size_t count, int value);
  int *(*insert_range)(struct vector *self, int *pos, int *first, int *last);
  int *(*erase)(struct vector *self, int *pos);
  int *(*erase_range)(struct vector *self, int *first, int *last);
  void (*push_back)(struct vector *self, int value);
  void (*pop_back)(struct vector *self);
  void (*resize)(struct vector *self, size_t count, int value);
  void (*swap)(struct vector *self, struct vector *other);

  void (*print)(struct vector *self);
} vector;

//

static void vector_assign(struct vector *self, size_t count, int value) {
  self->_capacity = self->_capacity < count ? (2 * count) : self->_capacity;
  self->_size = count;
  self->_data = (int *)realloc(self->_data, self->_capacity);
  for (size_t i = 0; i < self->_size; i++) {
    self->_data[i] = value;
  }
}

static void vector_assign_range(struct vector *self, int *first, int *last) {
  size_t count = last - first - 1;
  self->_capacity = self->_capacity < count ? (2 * count) : self->_capacity;
  self->_size = count;
  self->_data = (int *)realloc(self->_data, self->_capacity);
  size_t i = 0;
  for (int *p = first; p != last; p++) {
    self->_data[i++] = *p;
  }
}

//

static int vector_at(struct vector *self, size_t pos) {
  return self->_data[pos];
}

static int vector_front(struct vector *self) { return self->_data[0]; }

static int vector_back(struct vector *self) {
  return self->_data[self->_size - 1];
}

static int *vector_data(struct vector *self) { return self->_data; }

//

static int *vector_begin(struct vector *self) { return self->_data; }

static int *vector_end(struct vector *self) {
  return self->_data + self->_size;
}

//

static bool vector_empty(struct vector *self) { return self->_size == 0; }

static size_t vector_size(struct vector *self) { return self->_size; }

static void vector_reserve(struct vector *self, size_t new_cap) {
  if (new_cap < self->_capacity) {
    return;
  }
  self->_capacity = new_cap;
  int *old = self->_data;
  self->_data = (int *)realloc(self->_data, self->_capacity);
  for (size_t i = 0; i < self->_size; i++) {
    self->_data[i] = old[i];
  }
}

static size_t vector_capacity(struct vector *self) { return self->_capacity; }

static void vector_shrink_to_fit(struct vector *self) {
  if (self->_size * 4 > self->_capacity) {
    return;
  }
  self->_capacity /= 2;
  int *old = self->_data;
  self->_data = (int *)realloc(self->_data, self->_capacity);
  for (size_t i = 0; i < self->_size; i++) {
    self->_data[i] = old[i];
  }
}

//

static void vector_clear(struct vector *self) {
  size_t size = self->_size;
  for (int i = 0; i < size; i++) {
    self->pop_back(self);
  }
}

static int *vector_insert(struct vector *self, int *pos, int value) {
  int *end = self->end(self);
  for (int *i = end; i != (pos - 1); i--) {
    int t = *(i - 1);
    *i = t;
  }
  *(pos - 1) = value;
  self->_size++;
  return (pos - 1);
}

static int *vector_insert_n(struct vector *self, int *pos, size_t count,
                            int value) {
  if (count == 0) {
    return pos;
  }
  int *ret = pos;
  for (size_t i = 0; i < count; i++) {
    self->insert(self, pos, value);
  }
  return (ret - 1);
}

static int *vector_insert_range(struct vector *self, int *pos, int *first,
                                int *last) {
  if (first == last) {
    return pos;
  }
  int *ret = pos;
  for (int *i = first; i != last; i++) {
    int val = *i;
    pos = self->insert(self, pos, val);
    pos++;
  }
  return (ret - 1);
}

static int *vector_erase(struct vector *self, int *pos) {
  for (int *i = pos; i != self->end(self); i++) {
    int val = *(i + 1);
    *i = val;
  }
  self->_size--;
  return pos == (self->end(self) - 1) ? self->end(self) : pos;
}

static int *vector_erase_range(struct vector *self, int *first, int *last) {
  if (first == last) {
    return last;
  }
  size_t removed = last - first;
  for (int *i = first; i != self->end(self); i++) {
    int val = *(i + removed);
    *i = val;
  }
  self->_size -= removed;
  if (last == self->end(self)) {
    return self->end(self);
  }
  return last;
}

static void vector_push_back(struct vector *self, int value) {
  if (self->_size + 1 > self->_capacity) {
    self->reserve(self, self->_size + 5);
  }
  self->_data[self->_size] = value;
  self->_size++;
}

static void vector_pop_back(struct vector *self) { self->_size--; }

static void vector_resize(struct vector *self, size_t count, int value) {
  if (self->_size >= count) {
    self->_size = count;
    return;
  }
  self->reserve(self, count);
  size_t old_size = self->_size;
  for (size_t i = 0; i < count - old_size; i++) {
    self->push_back(self, value);
  }
}

static void vector_swap(struct vector *self, struct vector *other) {
  int *tmp = self->_data;
  self->_data = other->_data;
  other->_data = tmp;
  size_t tmp_s = self->_size;
  self->_size = other->_size;
  other->_size = tmp_s;
  size_t tmp_c = self->_capacity;
  self->_capacity = other->_capacity;
  other->_capacity = tmp_c;
}

static void vector_print(struct vector *self) {
  printf("vector: [ ");
  for (int *i = self->begin(self); i != self->end(self); i++) {
    printf("%d ", *i);
  }
  printf("]\n");
}

static void vector_assign_method(struct vector *obj) {
  obj->assign = vector_assign;
  obj->assign_range = vector_assign_range;
  obj->at = vector_at;
  obj->front = vector_front;
  obj->back = vector_back;
  obj->data = vector_data;
  obj->begin = vector_begin;
  obj->end = vector_end;
  obj->empty = vector_empty;
  obj->size = vector_size;
  obj->reserve = vector_reserve;
  obj->capacity = vector_capacity;
  obj->shrink_to_fit = vector_shrink_to_fit;
  obj->clear = vector_clear;
  obj->insert = vector_insert;
  obj->insert_n = vector_insert_n;
  obj->insert_range = vector_insert_range;
  obj->erase = vector_erase;
  obj->erase_range = vector_erase_range;
  obj->push_back = vector_push_back;
  obj->pop_back = vector_pop_back;
  obj->resize = vector_resize;
  obj->swap = vector_swap;
  obj->print = vector_print;
}

static struct vector *malloc_vector() {
  return (struct vector *)malloc(sizeof(struct vector));
}

static struct vector *init_vector() {
  struct vector *obj = malloc_vector();
  obj->_capacity = 0;
  obj->_data = (int *)malloc(sizeof(int) * obj->_capacity);
  obj->_size = 0;
  vector_assign_method(obj);
  return obj;
}

static struct vector *init_vector_n(size_t count, int value) {
  struct vector *obj = init_vector();
  obj->_capacity = count;
  obj->_data = (int *)realloc(obj->_data, sizeof(int) * count);
  for (size_t i = 0; i < count; i++) {
    obj->push_back(obj, value);
  }
  return obj;
}

static struct vector *init_vector_array(int *begin, int *end) {
  struct vector *obj = init_vector();
  for (int *i = begin; i != end; i++) {
    int val = i[0];
    obj->push_back(obj, val);
  }
  return obj;
}

static void free_vector(struct vector *self) {
  self->clear(self);
  free(self->_data);
  free(self);
}

#endif
