#ifndef priority_queue_h
#define priority_queue_h

#include "vector.h"
#include <stdbool.h>
#include <stddef.h>

#define _heap_left(i) (2 * (i) + 1)
#define _heap_right(i) (2 * (i) + 2)
#define _heap_parent(i) ((i - 1) / 2)

#define DECLARE_PRIORITY_QUEUE(priority_queue, T)                              \
  DECLARE_VECTOR(_pq_##priority_queue##_container, T)                          \
  typedef struct priority_queue {                                              \
    _pq_##priority_queue##_container *c;                                       \
    T (*top)(struct priority_queue * self);                                    \
    bool (*empty)(struct priority_queue * self);                               \
    size_t (*size)(struct priority_queue * self);                              \
    void (*push)(struct priority_queue * self, T value);                       \
    void (*pop)(struct priority_queue * self);                                 \
    void (*swap)(struct priority_queue * self, struct priority_queue *other);  \
  } priority_queue;                                                            \
  static T _pq_##priority_queue##_top(struct priority_queue *self) {           \
    return self->c->front(self->c);                                            \
  }                                                                            \
  static bool _pq_##priority_queue##_empty(struct priority_queue *self) {      \
    return self->c->empty(self->c);                                            \
  }                                                                            \
  static size_t _pq_##priority_queue##_size(struct priority_queue *self) {     \
    return self->c->size(self->c);                                             \
  }                                                                            \
  static void _pq_##priority_queue##_max_heapify(                              \
      _pq_##priority_queue##_container *v, size_t heap_size, size_t i) {       \
    size_t l = _heap_left(i);                                                  \
    size_t r = _heap_right(i);                                                 \
    size_t largest = i;                                                        \
    if (l < heap_size && v->at(v, l) > v->at(v, i)) {                          \
      largest = l;                                                             \
    }                                                                          \
    if (r < heap_size && v->at(v, r) > v->at(v, largest)) {                    \
      largest = r;                                                             \
    }                                                                          \
    if (largest != i) {                                                        \
      T tmp = v->at(v, i);                                                     \
      v->_data[i] = v->at(v, largest);                                         \
      v->_data[largest] = tmp;                                                 \
      _pq_##priority_queue##_max_heapify(v, heap_size, largest);               \
    }                                                                          \
  }                                                                            \
  static T _pq_##priority_queue##_heap_extract_max(                            \
      _pq_##priority_queue##_container *v) {                                   \
    size_t heap_size = v->size(v);                                             \
    assert(heap_size >= 1);                                                    \
    T max = v->at(v, 0);                                                       \
    v->_data[0] = v->at(v, heap_size - 1);                                     \
    heap_size -= 1;                                                            \
    _pq_##priority_queue##_max_heapify(v, heap_size, 0);                       \
    v->erase(v, v->end(v) - 1);                                                \
    return max;                                                                \
  }                                                                            \
  static void _pq_##priority_queue##_heap_increase_key(                        \
      _pq_##priority_queue##_container *v, size_t i, T key) {                  \
    assert(key >= v->at(v, i));                                                \
    v->_data[i] = key;                                                         \
    while (i > 0 && v->_data[_heap_parent(i)] < v->_data[i]) {                 \
      T tmp = v->_data[i];                                                     \
      v->_data[i] = v->_data[_heap_parent(i)];                                 \
      v->_data[_heap_parent(i)] = tmp;                                         \
      i = _heap_parent(i);                                                     \
    }                                                                          \
  }                                                                            \
  static void _pq_##priority_queue##_max_heap_insert(                          \
      _pq_##priority_queue##_container *v, T key) {                            \
    v->push_back(v, 0);                                                        \
    _pq_##priority_queue##_heap_increase_key(v, v->size(v) - 1, key);          \
  }                                                                            \
  static void _pq_##priority_queue##_push(struct priority_queue *self,         \
                                          T value) {                           \
    _pq_##priority_queue##_max_heap_insert(self->c, value);                    \
  }                                                                            \
  static void _pq_##priority_queue##_pop(struct priority_queue *self) {        \
    _pq_##priority_queue##_heap_extract_max(self->c);                          \
  }                                                                            \
  static void _pq_##priority_queue##_swap(struct priority_queue *self,         \
                                          struct priority_queue *other) {      \
    self->c->swap(self->c, other->c);                                          \
  }                                                                            \
  static void _pq_##priority_queue##_assign_method(                            \
      struct priority_queue *obj) {                                            \
    obj->top = _pq_##priority_queue##_top;                                     \
    obj->empty = _pq_##priority_queue##_empty;                                 \
    obj->size = _pq_##priority_queue##_size;                                   \
    obj->push = _pq_##priority_queue##_push;                                   \
    obj->pop = _pq_##priority_queue##_pop;                                     \
    obj->swap = _pq_##priority_queue##_swap;                                   \
  }                                                                            \
  static struct priority_queue *_pq_##priority_queue##_init_pq() {             \
    struct priority_queue *obj =                                               \
        (struct priority_queue *)malloc(sizeof(struct priority_queue));        \
    CREATE_VECTOR(_pq_##priority_queue##_container, con);                      \
    obj->c = con;                                                              \
    _pq_##priority_queue##_assign_method(obj);                                 \
    return obj;                                                                \
  }                                                                            \
  static struct priority_queue *_pq_##priority_queue##_init_pq_array(T *begin, \
                                                                     T *end) { \
    struct priority_queue *obj =                                               \
        (struct priority_queue *)malloc(sizeof(struct priority_queue));        \
    CREATE_VECTOR_ARRAY(_pq_##priority_queue##_container, con, begin, end);    \
    obj->c = con;                                                              \
    _pq_##priority_queue##_assign_method(obj);                                 \
    return obj;                                                                \
  }                                                                            \
  static void _pq_##priority_queue##_free_pq(struct priority_queue *self) {    \
    self->c->clear(self->c);                                                   \
    free(self);                                                                \
  }

#define CREATE_PRIORITY_QUEUE(priority_queue, obj)                             \
  priority_queue *obj = _pq_##priority_queue##_init_pq();

#define CREATE_PRIORITY_QUEUE_ARRAY(priority_queue, obj, begin, end)           \
  priority_queue *obj = _pq_##priority_queue##_init_pq_array(begin, end);

#define FREE_PRIORITY_QUEUE(priority_queue, obj)                               \
  _pq_##priority_queue##_free_pq(obj);

#endif
