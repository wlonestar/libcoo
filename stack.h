#ifndef stack_h
#define stack_h

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

void *reallocate(void *pointer, size_t old_size, size_t new_size) {
  if (new_size == 0) {
    free(pointer);
    return NULL;
  }
  void *result = realloc(pointer, new_size);
  if (result == NULL) {
    fprintf(stderr, "no enough to malloc\n");
    exit(-1);
  }
  return result;
}

#define GROW_CAPACITY(capacity) ((capacity) < 8 ? 8 : (capacity) * 2)

#define GROW_ARRAY(type, ptr, old_cnt, new_cnt) \
  (type *) reallocate(ptr, sizeof(type) * (old_cnt), sizeof(type) * (new_cnt))

#define FREE_ARRAY(type, pointer, old_count) \
  reallocate(pointer, sizeof(type) * (old_count), 0)

#define DECLARE_STACK(struct_name, value_type)                             \
  typedef struct struct_name {                                             \
    value_type *data;                                                      \
    size_t _size;                                                          \
    size_t _capacity;                                                      \
    value_type (*top)(struct struct_name* self);                           \
    bool (*empty)(struct struct_name* self);                               \
    size_t (*size)(struct struct_name* self);                              \
    void (*push)(struct struct_name* self, value_type value);              \
    void (*pop)(struct struct_name* self);                                 \
    void (*print)(struct struct_name* self);                               \
  } struct_name;                                                           \
  static value_type _stack_##struct_name##_top(struct struct_name *self) { \
    return self->data[self->_size - 1];                                    \
  }                                                                        \
  static bool _stack_##struct_name##_empty(struct struct_name *self) {     \
    return self->_size == 0;                                               \
  }                                                                        \
  static size_t _stack_##struct_name##_size(struct struct_name *self) {    \
    return self->_size;                                                    \
  }                                                                        \
  static void _stack_##struct_name##_push(struct struct_name *self,        \
                                          value_type value) {              \
    if (self->_capacity < self->_size + 1) {                               \
      int old_cap = self->_capacity;                                       \
      self->_capacity = GROW_CAPACITY(old_cap);                            \
      self->data =                                                         \
        GROW_ARRAY(value_type, self->data, old_cap, self->_capacity);      \
    }                                                                      \
    self->data[self->_size] = value;                                       \
    self->_size++;                                                         \
  }                                                                        \
  static void _stack_##struct_name##_pop(struct struct_name *self) {       \
    self->_size--;                                                         \
  }                                                                        \
  static void _stack_##struct_name##_print(struct struct_name *self) {     \
    fprintf(stderr, "stack print cannot implement generically!\n");        \
    exit(-1);                                                              \
  }

#define CREATE_STACK(struct_name, value_type, obj_name)                \
  struct_name *obj_name = (struct_name *) malloc(sizeof(struct_name)); \
  obj_name->_capacity = 0;                                             \
  obj_name->_size = 0;                                                 \
  obj_name->data = NULL;                                               \
  obj_name->top = _stack_##struct_name##_top;                          \
  obj_name->empty = _stack_##struct_name##_empty;                      \
  obj_name->size = _stack_##struct_name##_size;                        \
  obj_name->push = _stack_##struct_name##_push;                        \
  obj_name->pop = _stack_##struct_name##_pop;                          \
  obj_name->print = _stack_##struct_name##_print;

#define FREE_STACK(value_type, obj_name)                   \
  FREE_ARRAY(value_type, obj_name->data, obj_name->_size); \
  free(obj_name);

#endif
