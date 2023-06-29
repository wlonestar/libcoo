#ifndef vector_h
#define vector_h

#include <assert.h>
#include <memory.h>
#include <stdbool.h>
#include <stddef.h>

#define DECLARE_VECTOR(vector, T)                                              \
  typedef struct vector {                                                      \
    T *_data;                                                                  \
    size_t _capacity;                                                          \
    size_t _size;                                                              \
    /* Member functions */                                                     \
    void (*assign)(struct vector * self, size_t count, T value);               \
    void (*assign_range)(struct vector * self, T *first, T *last);             \
    /* Element access */                                                       \
    T (*at)(struct vector * self, size_t pos);                                 \
    T (*front)(struct vector * self);                                          \
    T (*back)(struct vector * self);                                           \
    T *(*data)(struct vector * self);                                          \
    /* not iterators */                                                        \
    T *(*begin)(struct vector * self);                                         \
    T *(*end)(struct vector * self);                                           \
    /* Capacity */                                                             \
    bool (*empty)(struct vector * self);                                       \
    size_t (*size)(struct vector * self);                                      \
    void (*reserve)(struct vector * self, size_t new_cap);                     \
    size_t (*capacity)(struct vector * self);                                  \
    void (*shrink_to_fit)(struct vector * self);                               \
    /* Modifiers */                                                            \
    void (*clear)(struct vector * self);                                       \
    T *(*insert)(struct vector * self, T *pos, T value);                       \
    T *(*insert_n)(struct vector * self, T *pos, size_t count, T value);       \
    T *(*insert_range)(struct vector * self, T *pos, T *first, T *last);       \
    T *(*erase)(struct vector * self, T *pos);                                 \
    T *(*erase_range)(struct vector * self, T *first, T *last);                \
    void (*push_back)(struct vector * self, T value);                          \
    void (*pop_back)(struct vector * self);                                    \
    void (*resize)(struct vector * self, size_t count, T value);               \
    void (*swap)(struct vector * self, struct vector *other);                  \
    /* debug print vector */                                                   \
    void (*print)(struct vector * self);                                       \
  } vector;                                                                    \
  /* implementations */                                                        \
  static void _vector_##vector##_assign(struct vector *self, size_t count,     \
                                        T value) {                             \
    self->_capacity = self->_capacity < count ? (2 * count) : self->_capacity; \
    self->_size = count;                                                       \
    self->_data = (T *)realloc(self->_data, self->_capacity);                  \
    for (size_t i = 0; i < self->_size; i++) {                                 \
      self->_data[i] = value;                                                  \
    }                                                                          \
  }                                                                            \
  static void _vector_##vector##_assign_range(struct vector *self, T *first,   \
                                              T *last) {                       \
    size_t count = last - first - 1;                                           \
    self->_capacity = self->_capacity < count ? (2 * count) : self->_capacity; \
    self->_size = count;                                                       \
    self->_data = (T *)realloc(self->_data, self->_capacity);                  \
    size_t i = 0;                                                              \
    for (T *p = first; p != last; p++) {                                       \
      self->_data[i++] = *p;                                                   \
    }                                                                          \
  }                                                                            \
  static T _vector_##vector##_at(struct vector *self, size_t pos) {            \
    return self->_data[pos];                                                   \
  }                                                                            \
  static T _vector_##vector##_front(struct vector *self) {                     \
    return self->_data[0];                                                     \
  }                                                                            \
  static T _vector_##vector##_back(struct vector *self) {                      \
    return self->_data[self->_size - 1];                                       \
  }                                                                            \
  static T *_vector_##vector##_data(struct vector *self) {                     \
    return self->_data;                                                        \
  }                                                                            \
  static T *_vector_##vector##_begin(struct vector *self) {                    \
    return self->_data;                                                        \
  }                                                                            \
  static T *_vector_##vector##_end(struct vector *self) {                      \
    return self->_data + self->_size;                                          \
  }                                                                            \
  static bool _vector_##vector##_empty(struct vector *self) {                  \
    return self->_size == 0;                                                   \
  }                                                                            \
  static size_t _vector_##vector##_size(struct vector *self) {                 \
    return self->_size;                                                        \
  }                                                                            \
  static void _vector_##vector##_reserve(struct vector *self,                  \
                                         size_t new_cap) {                     \
    if (new_cap < self->_capacity) {                                           \
      return;                                                                  \
    }                                                                          \
    size_t old_cap = self->_capacity;                                          \
    self->_capacity = new_cap;                                                 \
    T *old = malloc(sizeof(T) * old_cap);                                      \
    for (size_t i = 0; i < old_cap; i++) {                                     \
      old[i] = self->_data[i];                                                 \
    }                                                                          \
    self->_data = (T *)realloc(self->_data, sizeof(T) * self->_capacity);      \
    assert(self->_capacity >= self->_size);                                    \
    assert(old_cap >= self->_size);                                            \
    for (size_t i = 0; i < self->_size; i++) {                                 \
      assert(i < self->_capacity);                                             \
      assert(i < old_cap);                                                     \
      self->_data[i] = old[i];                                                 \
    }                                                                          \
    free(old);                                                                 \
  }                                                                            \
  static size_t _vector_##vector##_capacity(struct vector *self) {             \
    return self->_capacity;                                                    \
  }                                                                            \
  static void _vector_##vector##_shrink_to_fit(struct vector *self) {          \
    if (self->_size == self->_capacity) {                                      \
      return;                                                                  \
    }                                                                          \
    if (self->_size * 4 > self->_capacity) {                                   \
      return;                                                                  \
    }                                                                          \
    self->_capacity /= 2;                                                      \
    T *old = self->_data;                                                      \
    self->_data = (T *)realloc(self->_data, self->_capacity);                  \
    for (size_t i = 0; i < self->_size; i++) {                                 \
      self->_data[i] = old[i];                                                 \
    }                                                                          \
    free(old);                                                                 \
  }                                                                            \
  static void _vector_##vector##_clear(struct vector *self) {                  \
    size_t size = self->_size;                                                 \
    for (int i = 0; i < size; i++) {                                           \
      self->pop_back(self);                                                    \
    }                                                                          \
  }                                                                            \
  static T *_vector_##vector##_insert(struct vector *self, T *pos, T value) {  \
    if (self->_size + 1 > self->_capacity) {                                   \
      self->reserve(self, self->_size + 5);                                    \
    }                                                                          \
    T *ret = pos;                                                              \
    T *end = self->end(self);                                                  \
    for (T *i = end; i != pos - 1; i--) {                                      \
      T val = *(i - 1);                                                        \
      *i = val;                                                                \
    }                                                                          \
    *pos = value;                                                              \
    self->_size++;                                                             \
    return ret;                                                                \
  }                                                                            \
  static T *_vector_##vector##_insert_n(struct vector *self, T *pos,           \
                                        size_t count, T value) {               \
    if (count == 0) {                                                          \
      return pos;                                                              \
    }                                                                          \
    if (self->_size + count > self->_capacity) {                               \
      self->reserve(self, self->_size + count + 5);                            \
    }                                                                          \
    T *ret = pos;                                                              \
    for (size_t i = 0; i < count; i++) {                                       \
      self->insert(self, pos, value);                                          \
    }                                                                          \
    return ret;                                                                \
  }                                                                            \
  static T *_vector_##vector##_insert_range(struct vector *self, T *pos,       \
                                            T *first, T *last) {               \
    if (first == last) {                                                       \
      return pos;                                                              \
    }                                                                          \
    if (self->_size + last - first > self->_capacity) {                        \
      self->reserve(self, self->_size + last - first + 5);                     \
    }                                                                          \
    T *ret = pos;                                                              \
    for (T *i = first; i != last; i++) {                                       \
      T val = *i;                                                              \
      pos = self->insert(self, pos, val);                                      \
      pos++;                                                                   \
    }                                                                          \
    return ret;                                                                \
  }                                                                            \
  static T *_vector_##vector##_erase(struct vector *self, T *pos) {            \
    T *end = self->end(self);                                                  \
    for (T *i = pos; i != (end - 1); i++) {                                    \
      T val = *(i + 1);                                                        \
      *i = val;                                                                \
    }                                                                          \
    self->_size--;                                                             \
    return pos == (end - 1) ? self->end(self) : pos;                           \
  }                                                                            \
  static T *_vector_##vector##_erase_range(struct vector *self, T *first,      \
                                           T *last) {                          \
    if (first == last) {                                                       \
      return last;                                                             \
    }                                                                          \
    size_t removed = last - first;                                             \
    T *end = self->end(self);                                                  \
    if (last == end) {                                                         \
      self->_size -= removed;                                                  \
      return self->end(self);                                                  \
    }                                                                          \
    for (T *i = last; i != end; i++) {                                         \
      T val = *i;                                                              \
      *(i - removed) = val;                                                    \
    }                                                                          \
    self->_size -= removed;                                                    \
    return first;                                                              \
  }                                                                            \
  static void _vector_##vector##_push_back(struct vector *self, T value) {     \
    if (self->_size + 1 > self->_capacity) {                                   \
      self->reserve(self, self->_size + 5);                                    \
    }                                                                          \
    self->_data[self->_size] = value;                                          \
    self->_size++;                                                             \
  }                                                                            \
  static void _vector_##vector##_pop_back(struct vector *self) {               \
    self->_size--;                                                             \
  }                                                                            \
  static void _vector_##vector##_resize(struct vector *self, size_t count,     \
                                        T value) {                             \
    if (self->_size >= count) {                                                \
      self->_size = count;                                                     \
      return;                                                                  \
    }                                                                          \
    self->reserve(self, count);                                                \
    size_t old_size = self->_size;                                             \
    for (size_t i = 0; i < count - old_size; i++) {                            \
      self->push_back(self, value);                                            \
    }                                                                          \
  }                                                                            \
  static void _vector_##vector##_swap(struct vector *self,                     \
                                      struct vector *other) {                  \
    T *tmp = self->_data;                                                      \
    self->_data = other->_data;                                                \
    other->_data = tmp;                                                        \
    size_t tmp_s = self->_size;                                                \
    self->_size = other->_size;                                                \
    other->_size = tmp_s;                                                      \
    size_t tmp_c = self->_capacity;                                            \
    self->_capacity = other->_capacity;                                        \
    other->_capacity = tmp_c;                                                  \
  }                                                                            \
  static void _vector_##vector##_print(struct vector *self) {                  \
    fprintf(stderr, "print method cannot implemented as generic\n");           \
  }                                                                            \
  static void _vector_##vector##_assign_method(struct vector *obj) {           \
    obj->assign = _vector_##vector##_assign;                                   \
    obj->assign_range = _vector_##vector##_assign_range;                       \
    obj->at = _vector_##vector##_at;                                           \
    obj->front = _vector_##vector##_front;                                     \
    obj->back = _vector_##vector##_back;                                       \
    obj->data = _vector_##vector##_data;                                       \
    obj->begin = _vector_##vector##_begin;                                     \
    obj->end = _vector_##vector##_end;                                         \
    obj->empty = _vector_##vector##_empty;                                     \
    obj->size = _vector_##vector##_size;                                       \
    obj->reserve = _vector_##vector##_reserve;                                 \
    obj->capacity = _vector_##vector##_capacity;                               \
    obj->shrink_to_fit = _vector_##vector##_shrink_to_fit;                     \
    obj->clear = _vector_##vector##_clear;                                     \
    obj->insert = _vector_##vector##_insert;                                   \
    obj->insert_n = _vector_##vector##_insert_n;                               \
    obj->insert_range = _vector_##vector##_insert_range;                       \
    obj->erase = _vector_##vector##_erase;                                     \
    obj->erase_range = _vector_##vector##_erase_range;                         \
    obj->push_back = _vector_##vector##_push_back;                             \
    obj->pop_back = _vector_##vector##_pop_back;                               \
    obj->resize = _vector_##vector##_resize;                                   \
    obj->swap = _vector_##vector##_swap;                                       \
    obj->print = _vector_##vector##_print;                                     \
  }                                                                            \
  static struct vector *_vector_##vector##_init_vector() {                     \
    struct vector *obj = (struct vector *)malloc(sizeof(struct vector));       \
    obj->_capacity = 0;                                                        \
    obj->_data = (T *)malloc(sizeof(T) * obj->_capacity);                      \
    obj->_size = 0;                                                            \
    _vector_##vector##_assign_method(obj);                                     \
    return obj;                                                                \
  }                                                                            \
  static struct vector *_vector_##vector##_init_vector_n(size_t count,         \
                                                         T value) {            \
    struct vector *obj = _vector_##vector##_init_vector();                     \
    obj->_capacity = count;                                                    \
    obj->_data = (T *)realloc(obj->_data, sizeof(T) * obj->_capacity);         \
    for (size_t i = 0; i < count; i++) {                                       \
      obj->push_back(obj, value);                                              \
    }                                                                          \
    return obj;                                                                \
  }                                                                            \
  static struct vector *_vector_##vector##_init_vector_array(T *begin,         \
                                                             T *end) {         \
    struct vector *obj = _vector_##vector##_init_vector();                     \
    obj->_capacity = end - begin;                                              \
    obj->_data = (T *)realloc(obj->_data, sizeof(T) * obj->_capacity);         \
    for (T *i = begin; i != end; i++) {                                        \
      T val = i[0];                                                            \
      obj->push_back(obj, val);                                                \
    }                                                                          \
    return obj;                                                                \
  }                                                                            \
  static void _vector_##vector##_free_vector(struct vector *self) {            \
    self->clear(self);                                                         \
    free(self->_data);                                                         \
    free(self);                                                                \
  }

#define CREATE_VECTOR(vector, obj)                                             \
  vector *obj = _vector_##vector##_init_vector();

#define CREATE_VECTOR_N(vector, obj, n, val)                                   \
  vector *obj = _vector_##vector##_init_vector_n(n, val);

#define CREATE_VECTOR_ARRAY(vector, obj, begin, end)                           \
  vector *obj = _vector_##vector##_init_vector_array(begin, end);

#define FREE_VECTOR(vector, obj) _vector_##vector##_free_vector(obj);

#endif
