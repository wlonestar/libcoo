#ifndef queue_h
#define queue_h

#define DECLARE_QUEUE(struct_name, value_type)                                 \
  typedef struct struct_name {                                                 \
    value_type *data;                                                          \
    size_t _size;                                                              \
    size_t _capacity;                                                          \
    value_type (*front)(struct struct_name * self);                            \
    value_type (*back)(struct struct_name * self);                             \
    bool (*empty)(struct struct_name * self);                                  \
    size_t (*size)(struct struct_name * self);                                 \
    void (*push)(struct struct_name * self, value_type value);                 \
    void (*pop)(struct struct_name * self);                                    \
    void (*print)(struct struct_name * self);                                  \
  } struct_name;                                                               \
  static value_type _queue_##struct_name##_front(struct struct_name *self) {   \
    return self->data[0];                                                      \
  }                                                                            \
  static value_type _queue_##struct_name##_back(struct struct_name *self) {    \
    return self->data[self->_size - 1];                                        \
  }                                                                            \
  static bool _queue_##struct_name##_empty(struct struct_name *self) {         \
    return self->_size == 0;                                                   \
  }                                                                            \
  static size_t _queue_##struct_name##_size(struct struct_name *self) {        \
    return self->_size;                                                        \
  }                                                                            \
  static void _queue_##struct_name##_push(struct struct_name *self,            \
                                          value_type value) {                  \
    if (self->_capacity < self->_size + 1) {                                   \
      int old_cap = self->_capacity;                                           \
      self->_capacity = GROW_CAPACITY(old_cap);                                \
      self->data =                                                             \
          GROW_ARRAY(value_type, self->data, old_cap, self->_capacity);        \
    }                                                                          \
    self->data[self->_size] = value;                                           \
    self->_size++;                                                             \
  }                                                                            \
  static void _queue_##struct_name##_pop(struct struct_name *self) {           \
    self->_size--;                                                             \
  }                                                                            \
  static void _queue_##struct_name##_print(struct struct_name *self) {         \
    fprintf(stderr, "queue print cannot implement generically!\n");            \
    exit(-1);                                                                  \
  }                                                                            \
  struct_name *_queue_##struct_name##_init() {                                 \
    struct_name *obj_name = (struct_name *)malloc(sizeof(struct_name));        \
    obj_name->_capacity = 0;                                                   \
    obj_name->_size = 0;                                                       \
    obj_name->data = NULL;                                                     \
    obj_name->top = _queue_##struct_name##_top;                                \
    obj_name->empty = _queue_##struct_name##_empty;                            \
    obj_name->size = _queue_##struct_name##_size;                              \
    obj_name->push = _queue_##struct_name##_push;                              \
    obj_name->pop = _queue_##struct_name##_pop;                                \
    obj_name->print = _queue_##struct_name##_print;                            \
    return obj_name;                                                           \
  }

#define CREATE_QUEUE(struct_name, obj_name)                                    \
  struct_name *obj_name = _queue_##struct_name##_init();

#define FREE_QUEUE(obj_name)                                                   \
  FREE_ARRAY(typeof(obj_name->data), obj_name->data, obj_name->_size);         \
  free(obj_name);

#endif
