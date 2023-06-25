#ifndef vector_h
#define vector_h

#include "alloc.h"

static const int default_capacity = 5;

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
  if (self->_capacity < default_capacity * 2) {
    return;
  }
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
  int *new_end = self->end(self) + 1;
  for (int *i = new_end; i != pos; i--) {
    int t = *(i - 1);
    *i = t;
  }
  *pos = value;
  self->_size++;
  return pos;
}

static int *vector_insert_n(struct vector *self, int *pos, size_t count,
                            int value) {}

static int *vector_insert_range(struct vector *self, int *pos, int *first,
                                int *last) {}

static int *vector_erase(struct vector *self, int *pos) {}

static int *vector_erase_range(struct vector *self, int *first, int *last) {}

static void vector_push_back(struct vector *self, int value) {}

static void vector_pop_back(struct vector *self) {}

static void vector_resize(struct vector *self, size_t count, int value) {}

static void vector_swap(struct vector *self, struct vector *other) {}

#endif
