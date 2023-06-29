#ifndef stack_h
#define stack_h

#include "list.h"

#define DECLARE_STACK(stack, T)                                                \
  DECLARE_LIST(_stack_##stack##_container, T)                                  \
  typedef struct stack {                                                       \
    _stack_##stack##_container *c;                                             \
    T (*top)(struct stack * self);                                             \
    bool (*empty)(struct stack * self);                                        \
    size_t (*size)(struct stack * self);                                       \
    void (*push)(struct stack * self, T value);                                \
    void (*pop)(struct stack * self);                                          \
    void (*swap)(struct stack * self, struct stack *other);                    \
    void (*print)(struct stack * self);                                        \
  } stack;                                                                     \
  static void _stack_##stack##_top(struct stack *self) {                       \
    return self->c->back(self->c);                                             \
  }                                                                            \
  static bool _stack_##stack##_empty(struct stack *self) {                     \
    return self->c->empty(self->c);                                            \
  }                                                                            \
  static size_t _stack_##stack##_size(struct stack *self) {                    \
    return self->c->size(self->c);                                             \
  }                                                                            \
  static void _stack_##stack##_push(struct stack *self, T value) {             \
    self->c->push_back(self->c, value);                                        \
  }                                                                            \
  static void _stack_##stack##_pop(struct stack *self) {                       \
    self->c->pop_back(self->c);                                                \
  }                                                                            \
  static void _stack_##stack##_swap(struct stack *self, struct stack *other) { \
    self->c->swap(self->c, other->c);                                          \
  }                                                                            \
  static void _stack_##stack##_print(struct stack *self) {                     \
    fprintf(stderr, "print method cannot implemented as generic\n");           \
  }                                                                            \
  static void _stack_##stack##_assign_method(struct stack *obj) {              \
    obj->top = _stack_##stack##_top;                                           \
    obj->empty = _stack_##stack##_empty;                                       \
    obj->size = _stack_##stack##_size;                                         \
    obj->push = _stack_##stack##_push;                                         \
    obj->pop = _stack_##stack##_pop;                                           \
    obj->swap = _stack_##stack##_swap;                                         \
    obj->print = _stack_##stack##_print;                                       \
  }                                                                            \
  static struct stack *_stack_##stack##_init_stack() {                         \
    struct stack *obj = (struct stack *)malloc(sizeof(struct stack));          \
    CREATE_LIST(_stack_##stack##_container, con);                              \
    obj->c = con;                                                              \
    _stack_##stack##_assign_method(obj);                                       \
    return obj;                                                                \
  }                                                                            \
  static struct stack *_stack_##stack##_init_stack_n(size_t count, T value) {  \
    struct stack *obj = (struct stack *)malloc(sizeof(struct stack));          \
    CREATE_LIST_N(_stack_##stack##_container, con, count, value);              \
    obj->c = con;                                                              \
    _stack_##stack##_assign_method(obj);                                       \
    return obj;                                                                \
  }                                                                            \
  static struct stack *_stack_##stack##_init_stack_array(T *begin, T *end) {   \
    struct stack *obj = (struct stack *)malloc(sizeof(struct stack));          \
    CREATE_LIST_ARRAY(_stack_##stack##_container, con, begin, end);            \
    obj->c = con;                                                              \
    _stack_##stack##_assign_method(obj);                                       \
    return obj;                                                                \
  }                                                                            \
  static void _stack_##stack##_free_stack(struct stack *self) {                \
    self->c->clear(self->c);                                                   \
    free(self);                                                                \
  }

#define CREATE_STACK(stack, obj) stack *obj = _stack_##stack##_init_stack();

#define CREATE_STACK_N(stack, obj, n, val)                                     \
  stack *obj = _stack_##stack##_init_stack_n(n, val);

#define CREATE_STACK_ARRAY(stack, obj, begin, end)                             \
  stack *obj = _stack_##stack##_init_stack_array(begin, end);

#define FREE_STACK(stack, obj) _stack_##stack##_free_stack(obj);

#endif
