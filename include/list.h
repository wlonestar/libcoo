#ifndef list_h
#define list_h

#include <stddef.h>
#include <stdbool.h>

#define DECLARE_LIST(list, T)                                                  \
  typedef struct list##_node {                                                 \
    T data;                                                                    \
    struct list##_node *prev, *next;                                           \
  } list##_node;                                                               \
  /* doubly linked list */                                                     \
  typedef struct list {                                                        \
    list##_node *_head;                                                        \
    size_t _size;                                                              \
    /* Element access */                                                       \
    T (*front)(struct list * self);                                            \
    T (*back)(struct list * self);                                             \
    /* not iterators */                                                        \
    struct list##_node *(*begin)(struct list * self);                          \
    struct list##_node *(*end)(struct list * self);                            \
    /* Capacity */                                                             \
    bool (*empty)(struct list * self);                                         \
    size_t (*size)(struct list * self);                                        \
    /* Modifiers */                                                            \
    void (*clear)(struct list * self);                                         \
    struct list##_node *(*insert)(struct list * self, struct list##_node *pos, \
                                  T value);                                    \
    struct list##_node *(*insert_n)(struct list * self,                        \
                                    struct list##_node *pos, size_t count,     \
                                    T value);                                  \
    struct list##_node *(*insert_range)(struct list * self,                    \
                                        struct list##_node *pos, T *first,     \
                                        T *last);                              \
    struct list##_node *(*erase)(struct list * self, struct list##_node *pos); \
    struct list##_node *(*erase_range)(struct list * self,                     \
                                       struct list##_node *first,              \
                                       struct list##_node *last);              \
    void (*push_back)(struct list * self, T value);                            \
    void (*push_front)(struct list * self, T value);                           \
    void (*pop_back)(struct list * self);                                      \
    void (*pop_front)(struct list * self);                                     \
    void (*resize)(struct list * self, size_t count);                          \
    void (*resize_value)(struct list * self, size_t count, T value);           \
    void (*swap)(struct list * self, struct list *other);                      \
    /* Operations */                                                           \
    void (*merge)(struct list * self, struct list *other);                     \
    void (*merge_by)(struct list * self, struct list *other,                   \
                     bool (*cmp)(T a, T b));                                   \
    void (*splice)(struct list * self, struct list##_node *pos,                \
                   struct list *other);                                        \
    void (*splice_from)(struct list * self, struct list##_node *pos,           \
                        struct list *other, struct list##_node *it);           \
    void (*splice_range)(struct list * self, struct list##_node *pos,          \
                         struct list *other, struct list##_node *first,        \
                         struct list##_node *last);                            \
    size_t (*remove)(struct list * self, T value);                             \
    size_t (*remove_if)(struct list * self, bool (*pred)(T n));                \
    void (*reverse)(struct list * self);                                       \
    size_t (*unique)(struct list * self);                                      \
    size_t (*unique_by)(struct list * self, bool (*p)(T a, T b));              \
    void (*sort)(struct list * self);                                          \
    void (*sort_by)(struct list * self, bool (*cmp)(T a, T b));                \
    /* debug print list */                                                     \
    void (*print)(struct list * self); /* for debug */                         \
  } list;                                                                      \
  /* implementations */                                                        \
  static T _list_##list##_front(struct list *self) {                           \
    return self->_head->next->data;                                            \
  }                                                                            \
  static T _list_##list##_back(struct list *self) {                            \
    return self->_head->prev->data;                                            \
  }                                                                            \
  static struct list##_node *_list_##list##_begin(struct list *self) {         \
    return self->_head->next;                                                  \
  }                                                                            \
  static struct list##_node *_list_##list##_end(struct list *self) {           \
    return self->_head;                                                        \
  }                                                                            \
  static bool _list_##list##_empty(struct list *self) {                        \
    return self->_size == 0;                                                   \
  }                                                                            \
  static size_t _list_##list##_size(struct list *self) { return self->_size; } \
  static void _list_##list##_clear(struct list *self) {                        \
    while (self->_size != 0) {                                                 \
      self->pop_back(self);                                                    \
    }                                                                          \
  }                                                                            \
  static struct list##_node *_list_##list##_insert(                            \
      struct list *self, struct list##_node *pos, T value) {                   \
    struct list##_node *new_node =                                             \
        (struct list##_node *)malloc(sizeof(struct list##_node));              \
    new_node->data = value;                                                    \
    new_node->next = pos;                                                      \
    new_node->prev = pos->prev;                                                \
    pos->prev->next = new_node;                                                \
    pos->prev = new_node;                                                      \
    self->_size++;                                                             \
    return new_node;                                                           \
  }                                                                            \
  static struct list##_node *_list_##list##_insert_n(                          \
      struct list *self, struct list##_node *pos, size_t count, T value) {     \
    if (count == 0) {                                                          \
      return pos;                                                              \
    }                                                                          \
    struct list##_node *ret = pos->prev;                                       \
    for (int i = 0; i < count; i++) {                                          \
      self->insert(self, pos, value);                                          \
    }                                                                          \
    return ret->next;                                                          \
  }                                                                            \
  static struct list##_node *_list_##list##_insert_range(                      \
      struct list *self, struct list##_node *pos, T *first, T *last) {         \
    if (first == last) {                                                       \
      return pos;                                                              \
    }                                                                          \
    struct list##_node *ret = pos->prev;                                       \
    for (T *p = first; p != last; p++) {                                       \
      pos = self->insert(self, pos, *p);                                       \
      pos = pos->next;                                                         \
    }                                                                          \
    return ret->next;                                                          \
  }                                                                            \
  static struct list##_node *_list_##list##_erase(struct list *self,           \
                                                  struct list##_node *pos) {   \
    struct list##_node *ret = pos->next;                                       \
    pos->prev->next = pos->next;                                               \
    pos->next->prev = pos->prev;                                               \
    self->_size--;                                                             \
    return ret;                                                                \
  }                                                                            \
  static struct list##_node *_list_##list##_erase_range(                       \
      struct list *self, struct list##_node *first,                            \
      struct list##_node *last) {                                              \
    struct list##_node *p = first;                                             \
    while (p != last->next) {                                                  \
      p = self->erase(self, p);                                                \
    }                                                                          \
    return p;                                                                  \
  }                                                                            \
  static void _list_##list##_push_back(struct list *self, T value) {           \
    struct list##_node *new_node =                                             \
        (struct list##_node *)malloc(sizeof(struct list##_node));              \
    new_node->data = value;                                                    \
    new_node->prev = self->_head->prev;                                        \
    new_node->next = self->_head;                                              \
    self->_head->prev->next = new_node;                                        \
    self->_head->prev = new_node;                                              \
    self->_size++;                                                             \
  }                                                                            \
  static void _list_##list##_push_front(struct list *self, T value) {          \
    struct list##_node *new_node =                                             \
        (struct list##_node *)malloc(sizeof(struct list##_node));              \
    new_node->data = value;                                                    \
    new_node->prev = self->_head;                                              \
    new_node->next = self->_head->next;                                        \
    self->_head->next->prev = new_node;                                        \
    self->_head->next = new_node;                                              \
    self->_size++;                                                             \
  }                                                                            \
  static void _list_##list##_pop_back(struct list *self) {                     \
    self->_head->prev->prev->next = self->_head;                               \
    self->_head->prev = self->_head->prev->prev;                               \
    self->_size--;                                                             \
  }                                                                            \
  static void _list_##list##_pop_front(struct list *self) {                    \
    self->_head->next->next->prev = self->_head;                               \
    self->_head->next = self->_head->next->next;                               \
    self->_size--;                                                             \
  }                                                                            \
  static void _list_##list##_resize(struct list *self, size_t count) {         \
    if (count == self->_size) {                                                \
      return;                                                                  \
    } else if (self->_size > count) {                                          \
      while (self->_size > count) {                                            \
        self->pop_back(self);                                                  \
      }                                                                        \
    } else {                                                                   \
      int addi = count - self->_size;                                          \
      for (int i = 0; i < addi; i++) {                                         \
        self->push_back(self, 0);                                              \
      }                                                                        \
    }                                                                          \
  }                                                                            \
  static void _list_##list##_resize_value(struct list *self, size_t count,     \
                                          T value) {                           \
    if (count == self->_size) {                                                \
      return;                                                                  \
    } else if (self->_size > count) {                                          \
      while (self->_size > count) {                                            \
        self->pop_back(self);                                                  \
      }                                                                        \
    } else {                                                                   \
      int addi = count - self->_size;                                          \
      for (int i = 0; i < addi; i++) {                                         \
        self->push_back(self, value);                                          \
      }                                                                        \
    }                                                                          \
  }                                                                            \
  static void _list_##list##_swap(struct list *self, struct list *other) {     \
    struct list##_node *tmp = self->_head;                                     \
    self->_head = other->_head;                                                \
    other->_head = tmp;                                                        \
    size_t tmp_s = self->_size;                                                \
    self->_size = other->_size;                                                \
    other->_size = tmp_s;                                                      \
  }                                                                            \
  static void _list_##list##_merge(struct list *self, struct list *other) {    \
    if (self == other) {                                                       \
      return;                                                                  \
    }                                                                          \
    struct list##_node *p = self->begin(self), *q = other->begin(other);       \
    while (q != other->_head) {                                                \
      if (p->data > q->data) {                                                 \
        self->insert(self, p, q->data);                                        \
      } else {                                                                 \
        struct list##_node *r = p;                                             \
        while (r != self->_head) {                                             \
          if (r->data > q->data) {                                             \
            break;                                                             \
          }                                                                    \
          r = r->next;                                                         \
        }                                                                      \
        p = self->insert(self, r, q->data);                                    \
      }                                                                        \
      q = other->erase(other, q);                                              \
    }                                                                          \
  }                                                                            \
  static void _list_##list##_merge_by(struct list *self, struct list *other,   \
                                      bool (*cmp)(T a, T b)) {                 \
    if (self == other) {                                                       \
      return;                                                                  \
    }                                                                          \
    struct list##_node *p = self->begin(self), *q = other->begin(other);       \
    while (q != other->_head) {                                                \
      if (!cmp(p->data, q->data)) {                                            \
        self->insert(self, p, q->data);                                        \
      } else {                                                                 \
        struct list##_node *r = p;                                             \
        while (r != self->_head) {                                             \
          if (!cmp(r->data, q->data)) {                                        \
            break;                                                             \
          }                                                                    \
          r = r->next;                                                         \
        }                                                                      \
        p = self->insert(self, r, q->data);                                    \
      }                                                                        \
      q = other->erase(other, q);                                              \
    }                                                                          \
  }                                                                            \
  static void _list_##list##_splice(                                           \
      struct list *self, struct list##_node *pos, struct list *other) {        \
    struct list##_node *p = pos;                                               \
    struct list##_node *i = other->begin(other);                               \
    while (i != other->_head) {                                                \
      p = self->insert(self, p, i->data);                                      \
      p = p->next;                                                             \
      i = other->erase(other, i);                                              \
    }                                                                          \
  }                                                                            \
  static void _list_##list##_splice_from(                                      \
      struct list *self, struct list##_node *pos, struct list *other,          \
      struct list##_node *it) {                                                \
    struct list##_node *p = pos;                                               \
    struct list##_node *i = it;                                                \
    self->insert(self, p, i->data);                                            \
    other->erase(other, i);                                                    \
  }                                                                            \
  static void _list_##list##_splice_range(                                     \
      struct list *self, struct list##_node *pos, struct list *other,          \
      struct list##_node *first, struct list##_node *last) {                   \
    struct list##_node *p = pos;                                               \
    struct list##_node *i = first;                                             \
    while (i != last) {                                                        \
      p = self->insert(self, p, i->data);                                      \
      p = p->next;                                                             \
      i = other->erase(other, i);                                              \
    }                                                                          \
  }                                                                            \
  static size_t _list_##list##_remove(struct list *self, T value) {            \
    size_t ret = 0;                                                            \
    struct list##_node *p = self->begin(self);                                 \
    while (p != self->_head) {                                                 \
      if (p->data == value) {                                                  \
        p = self->erase(self, p);                                              \
        ret++;                                                                 \
      } else {                                                                 \
        p = p->next;                                                           \
      }                                                                        \
    }                                                                          \
    return ret;                                                                \
  }                                                                            \
  static size_t _list_##list##_remove_if(struct list *self,                    \
                                         bool (*pred)(T n)) {                  \
    size_t ret = 0;                                                            \
    struct list##_node *p = self->begin(self);                                 \
    while (p != self->_head) {                                                 \
      if (pred(p->data)) {                                                     \
        p = self->erase(self, p);                                              \
        ret++;                                                                 \
      } else {                                                                 \
        p = p->next;                                                           \
      }                                                                        \
    }                                                                          \
    return ret;                                                                \
  }                                                                            \
  static void _list_##list##_reverse(struct list *self) {                      \
    size_t times = self->_size / 2;                                            \
    struct list##_node *p = self->_head->next;                                 \
    struct list##_node *q = self->_head->prev;                                 \
    int i = 0;                                                                 \
    while (i < times) {                                                        \
      T tmp = p->data;                                                         \
      p->data = q->data;                                                       \
      q->data = tmp;                                                           \
      p = p->next;                                                             \
      q = q->prev;                                                             \
      i++;                                                                     \
    }                                                                          \
  }                                                                            \
  static size_t _list_##list##_unique(struct list *self) {                     \
    if (self->_size < 2) {                                                     \
      return 0;                                                                \
    }                                                                          \
    size_t old_size = self->_size;                                             \
    struct list##_node *p = self->begin(self);                                 \
    struct list##_node *l, *r;                                                 \
    while (p != self->_head) {                                                 \
      l = p->next;                                                             \
      if (p->data == l->data) {                                                \
        r = l->next;                                                           \
        while (r != self->_head) {                                             \
          if (r->data == l->data) {                                            \
            r = r->next;                                                       \
          } else {                                                             \
            break;                                                             \
          }                                                                    \
        }                                                                      \
        p = self->erase_range(self, l, r);                                     \
      } else {                                                                 \
        p = p->next;                                                           \
      }                                                                        \
    }                                                                          \
    return old_size - self->_size;                                             \
  }                                                                            \
  static size_t _list_##list##_unique_by(struct list *self,                    \
                                         bool (*pred)(T a, T b)) {             \
    if (self->_size < 2) {                                                     \
      return 0;                                                                \
    }                                                                          \
    size_t old_size = self->_size;                                             \
    struct list##_node *p = self->_head->next;                                 \
    struct list##_node *l, *r;                                                 \
    while (p != self->_head) {                                                 \
      l = p->next;                                                             \
      if (pred(p->data, l->data)) {                                            \
        r = l->next;                                                           \
        while (r != self->_head) {                                             \
          if (pred(r->data, l->data)) {                                        \
            r = r->next;                                                       \
          } else {                                                             \
            break;                                                             \
          }                                                                    \
        }                                                                      \
        p = self->erase_range(self, l, r);                                     \
      } else {                                                                 \
        p = p->next;                                                           \
      }                                                                        \
    }                                                                          \
    return old_size - self->_size;                                             \
  }                                                                            \
  static void _list_##list##_sort(struct list *self) {                         \
    struct list##_node *j = self->begin(self)->next;                           \
    while (j != self->_head) {                                                 \
      struct list##_node *i = j->prev;                                         \
      while (i != self->_head && i->data > j->data) {                          \
        i = i->prev;                                                           \
      }                                                                        \
      T value = j->data;                                                       \
      j = self->erase(self, j);                                                \
      self->insert(self, i->next, value);                                      \
    }                                                                          \
  }                                                                            \
  static void _list_##list##_sort_by(struct list *self,                        \
                                     bool (*cmp)(T a, T b)) {                  \
    struct list##_node *j = self->begin(self)->next;                           \
    while (j != self->_head) {                                                 \
      struct list##_node *i = j->prev;                                         \
      while (i != self->_head && !cmp(i->data, j->data)) {                     \
        i = i->prev;                                                           \
      }                                                                        \
      T value = j->data;                                                       \
      j = self->erase(self, j);                                                \
      self->insert(self, i->next, value);                                      \
    }                                                                          \
  }                                                                            \
  static void _list_##list##_print(struct list *self) {                        \
    fprintf(stderr, "print method cannot implemented as generic\n");           \
  }                                                                            \
  static void _list_##list##_list_init_head(struct list *obj) {                \
    obj->_head = (struct list##_node *)malloc(sizeof(struct list##_node));     \
    /* obj->_head->data = -114514; */ /* for int type */                       \
    obj->_head->prev = obj->_head;                                             \
    obj->_head->next = obj->_head;                                             \
  }                                                                            \
  static void _list_##list##_list_assignn_method(struct list *obj) {           \
    obj->front = _list_##list##_front;                                         \
    obj->back = _list_##list##_back;                                           \
    obj->begin = _list_##list##_begin;                                         \
    obj->end = _list_##list##_end;                                             \
    obj->empty = _list_##list##_empty;                                         \
    obj->size = _list_##list##_size;                                           \
    obj->clear = _list_##list##_clear;                                         \
    obj->insert = _list_##list##_insert;                                       \
    obj->insert_n = _list_##list##_insert_n;                                   \
    obj->insert_range = _list_##list##_insert_range;                           \
    obj->erase = _list_##list##_erase;                                         \
    obj->erase_range = _list_##list##_erase_range;                             \
    obj->push_back = _list_##list##_push_back;                                 \
    obj->push_front = _list_##list##_push_front;                               \
    obj->pop_back = _list_##list##_pop_back;                                   \
    obj->pop_front = _list_##list##_pop_front;                                 \
    obj->resize = _list_##list##_resize;                                       \
    obj->resize_value = _list_##list##_resize_value;                           \
    obj->swap = _list_##list##_swap;                                           \
    obj->merge = _list_##list##_merge;                                         \
    obj->merge_by = _list_##list##_merge_by;                                   \
    obj->splice = _list_##list##_splice;                                       \
    obj->splice_from = _list_##list##_splice_from;                             \
    obj->splice_range = _list_##list##_splice_range;                           \
    obj->remove = _list_##list##_remove;                                       \
    obj->remove_if = _list_##list##_remove_if;                                 \
    obj->reverse = _list_##list##_reverse;                                     \
    obj->unique = _list_##list##_unique;                                       \
    obj->unique_by = _list_##list##_unique_by;                                 \
    obj->sort = _list_##list##_sort;                                           \
    obj->sort_by = _list_##list##_sort_by;                                     \
    obj->print = _list_##list##_print;                                         \
  }                                                                            \
  static struct list *_list_##list##_malloc_list() {                           \
    return (struct list *)malloc(sizeof(struct list));                         \
  }                                                                            \
  static struct list *_list_##list##_init_list() {                             \
    struct list *obj = _list_##list##_malloc_list();                           \
    _list_##list##_list_init_head(obj);                                        \
    obj->_size = 0;                                                            \
    _list_##list##_list_assignn_method(obj);                                   \
    return obj;                                                                \
  }                                                                            \
  static struct list *_list_##list##_init_list_n(size_t count, T value) {      \
    struct list *obj = _list_##list##_init_list();                             \
    for (int i = 0; i < count; i++) {                                          \
      obj->push_back(obj, value);                                              \
    }                                                                          \
    return obj;                                                                \
  }                                                                            \
  static struct list *_list_##list##_init_list_array(T *begin, T *end) {       \
    struct list *obj = _list_##list##_init_list();                             \
    for (T *p = begin; p != end; p++) {                                        \
      T val = p[0];                                                            \
      obj->push_back(obj, val);                                                \
    }                                                                          \
    return obj;                                                                \
  }                                                                            \
  void _list_##list##_free_list(struct list *self) {                           \
    self->clear(self);                                                         \
    free(self->_head);                                                         \
    free(self);                                                                \
  }

#define CREATE_LIST(list, obj) list *obj = _list_##list##_init_list();

#define CREATE_LIST_N(list, obj, n, val)                                       \
  list *obj = _list_##list##_init_list_n(n, val);

#define CREATE_LIST_ARRAY(list, obj, begin, end)                               \
  list *obj = _list_##list##_init_list_array(begin, end);

#define FREE_LIST(obj) _list_##list##_free_list(obj);

#endif
