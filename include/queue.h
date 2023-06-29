#ifndef queue_h
#define queue_h

#include "list.h"

#define DECLARE_QUEUE(queue, T)                                                \
  DECLARE_LIST(_queue_##queue##_container, T)                                  \
  typedef struct queue {                                                       \
    _queue_##queue##_container *c;                                             \
    T (*front)(struct queue * self);                                           \
    T (*back)(struct queue * self);                                            \
    bool (*empty)(struct queue * self);                                        \
    size_t (*size)(struct queue * self);                                       \
    void (*push)(struct queue * self, T value);                                \
    void (*pop)(struct queue * self);                                          \
    void (*swap)(struct queue * self, struct queue *other);                    \
    void (*print)(struct queue * self);                                        \
  } queue;                                                                     \
  static void _queue_##queue##_front(struct queue *self) {                     \
    return self->c->front(self->c);                                            \
  }                                                                            \
  static void _queue_##queue##_back(struct queue *self) {                      \
    return self->c->back(self->c);                                             \
  }                                                                            \
  static bool _queue_##queue##_empty(struct queue *self) {                     \
    return self->c->empty(self->c);                                            \
  }                                                                            \
  static size_t _queue_##queue##_size(struct queue *self) {                    \
    return self->c->size(self->c);                                             \
  }                                                                            \
  static void _queue_##queue##_push(struct queue *self, T value) {             \
    self->c->push_back(self->c, value);                                        \
  }                                                                            \
  static void _queue_##queue##_pop(struct queue *self) {                       \
    self->c->pop_front(self->c);                                               \
  }                                                                            \
  static void _queue_##queue##_swap(struct queue *self, struct queue *other) { \
    self->c->swap(self->c, other->c);                                          \
  }                                                                            \
  static void _queue_##queue##_print(struct queue *self) {                     \
    fprintf(stderr, "print method cannot implemented as generic\n");           \
  }                                                                            \
  static void _queue_##queue##_assign_method(struct queue *obj) {              \
    obj->front = _queue_##queue##_front;                                       \
    obj->back = _queue_##queue##_back;                                         \
    obj->empty = _queue_##queue##_empty;                                       \
    obj->size = _queue_##queue##_size;                                         \
    obj->push = _queue_##queue##_push;                                         \
    obj->pop = _queue_##queue##_pop;                                           \
    obj->swap = _queue_##queue##_swap;                                         \
    obj->print = _queue_##queue##_print;                                       \
  }                                                                            \
  static struct queue *_queue##queue##_init_queue() {                          \
    struct queue *obj = (struct queue *)malloc(sizeof(struct queue));          \
    CREATE_LIST(_queue_##queue##_container, con);                              \
    obj->c = con;                                                              \
    _queue_##queue##_assign_method(obj);                                       \
    return obj;                                                                \
  }                                                                            \
  static struct queue *_queue##queue##_init_queue_n(size_t count, T value) {   \
    struct queue *obj = (struct queue *)malloc(sizeof(struct queue));          \
    CREATE_LIST_N(_queue_##queue##_container, con, count, value);              \
    obj->c = con;                                                              \
    _queue_##queue##_assign_method(obj);                                       \
    return obj;                                                                \
  }                                                                            \
  static struct queue *_queue##queue##_init_queue_array(T *begin, T *end) {    \
    struct queue *obj = (struct queue *)malloc(sizeof(struct queue));          \
    CREATE_LIST_ARRAY(_queue_##queue##_container, con, begin, end);            \
    obj->c = con;                                                              \
    _queue_##queue##_assign_method(obj);                                       \
    return obj;                                                                \
  }                                                                            \
  static void _queue_##queue##_free_queue(struct queue *self) {                \
    self->c->clear(self->c);                                                   \
    free(self);                                                                \
  }

#define CREATE_QUEUE(queue, obj) queue *obj = _queue##queue##_init_queue();

#define CREATE_QUEUE_N(queue, obj, n, val)                                     \
  queue *obj = _queue##queue##_init_queue_n(n, val);

#define CREATE_QUEUE_ARRAY(queue, obj, begin, end)                             \
  queue *obj = _queue##queue##_init_queue_array(begin, end);

#define FREE_QUEUE(queue, obj) _queue_##queue##_free_queue(obj);

#endif
