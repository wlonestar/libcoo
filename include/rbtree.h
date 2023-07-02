#ifndef rbtree_h
#define rbtree_h

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "stack.h"
#include "vector.h"

enum rb_color {
  RB_RED,
  RB_BLACK,
};

#define DECLARE_RBTREE(rbtree, T, custom_print)                                \
  bool __##rbtree##_less(T a, T b) { return a <= b; }                          \
  bool __##rbtree##_greater(T a, T b) { return a > b; }                        \
  /* rbtree_node */                                                            \
  typedef struct rbtree##_node {                                               \
    struct rbtree##_node *parent;                                              \
    struct rbtree##_node *left;                                                \
    struct rbtree##_node *right;                                               \
    char color;                                                                \
    T value;                                                                   \
  } rbtree##_node;                                                             \
  /* containers for rbtree */                                                  \
  DECLARE_VECTOR(__##rbtree##_vector, T)                                       \
  DECLARE_STACK(__##rbtree##_stack, struct rbtree##_node *)                    \
  DECLARE_QUEUE(__##rbtree##_queue, struct rbtree##_node *)                    \
  typedef bool (*rbtree##_Comp)(T a, T b);                                     \
  typedef struct rbtree {                                                      \
    struct rbtree##_node *nil;                                                 \
    struct rbtree##_node *_root;                                               \
    size_t _size;                                                              \
    rbtree##_Comp comp;                                                        \
    /* Node operation */                                                       \
    struct rbtree##_node *(*min_child)(struct rbtree * self,                   \
                                       struct rbtree##_node *p);               \
    struct rbtree##_node *(*max_child)(struct rbtree * self,                   \
                                       struct rbtree##_node *p);               \
    void (*rotate_left)(struct rbtree * self, struct rbtree##_node *p);        \
    void (*rotate_right)(struct rbtree * self, struct rbtree##_node *p);       \
    /* Element access */                                                       \
    struct rbtree##_node *(*root)(struct rbtree * self);                       \
    /* Capacity */                                                             \
    bool (*empty)(struct rbtree * self);                                       \
    size_t (*size)(struct rbtree * self);                                      \
    /* Modifiers */                                                            \
    void (*clear)(struct rbtree * self);                                       \
    void (*insert_fixup)(struct rbtree * self, struct rbtree##_node *p);       \
    struct rbtree##_node *(*insert_node)(struct rbtree * self,                 \
                                         struct rbtree##_node *p);             \
    struct rbtree##_node *(*insert)(struct rbtree * self, T value);            \
    void (*transplant)(struct rbtree * self, struct rbtree##_node *u,          \
                       struct rbtree##_node *v);                               \
    void (*erase_fixup)(struct rbtree * self, struct rbtree##_node *x);        \
    void (*erase_node)(struct rbtree * self, struct rbtree##_node *p);         \
    void (*erase)(struct rbtree * self, T value);                              \
    /* Lookup */                                                               \
    struct rbtree##_node *(*find_from)(struct rbtree * self,                   \
                                       struct rbtree##_node *p, T value);      \
    struct rbtree##_node *(*find)(struct rbtree * self, int value);            \
    /* Traverse */                                                             \
    void (*pre_order)(struct rbtree * self);                                   \
    void (*in_order)(struct rbtree * self);                                    \
    void (*_post_order)(struct rbtree * self, struct rbtree##_node *p,         \
                        __##rbtree##_vector *v);                               \
    void (*post_order)(struct rbtree * self);                                  \
    void (*level_order)(struct rbtree * self);                                 \
    /* Print */                                                                \
    void (*print_from)(struct rbtree * self, struct rbtree##_node *p,          \
                       int prefix);                                            \
    void (*print)(struct rbtree * self);                                       \
  } rbtree;                                                                    \
  static rbtree##_node *_rbtree_##rbtree##_min_child(rbtree *self,             \
                                                     rbtree##_node *p) {       \
    while (p->left != self->nil) {                                             \
      p = p->left;                                                             \
    }                                                                          \
    return p;                                                                  \
  }                                                                            \
  static rbtree##_node *_rbtree_##rbtree##_max_child(rbtree *self,             \
                                                     rbtree##_node *p) {       \
    while (p->right != self->nil) {                                            \
      p = p->right;                                                            \
    }                                                                          \
    return p;                                                                  \
  }                                                                            \
  static void _rbtree_##rbtree##_rotate_left(rbtree *self, rbtree##_node *p) { \
    rbtree##_node *y = p->right;                                               \
    p->right = y->left;                                                        \
    if (y->left != self->nil) {                                                \
      y->left->parent = p;                                                     \
    }                                                                          \
    y->parent = p->parent;                                                     \
    if (p->parent == self->nil) {                                              \
      self->_root = y;                                                         \
    } else if (p == p->parent->left) {                                         \
      p->parent->left = y;                                                     \
    } else {                                                                   \
      p->parent->right = y;                                                    \
    }                                                                          \
    y->left = p;                                                               \
    p->parent = y;                                                             \
  }                                                                            \
  static void _rbtree_##rbtree##_rotate_right(rbtree *self,                    \
                                              rbtree##_node *p) {              \
    rbtree##_node *y = p->left;                                                \
    p->left = y->right;                                                        \
    if (y->right != self->nil) {                                               \
      y->right->parent = p;                                                    \
    }                                                                          \
    y->parent = p->parent;                                                     \
    if (p->parent == self->nil) {                                              \
      self->_root = y;                                                         \
    } else if (p == p->parent->right) {                                        \
      p->parent->right = y;                                                    \
    } else {                                                                   \
      p->parent->left = y;                                                     \
    }                                                                          \
    y->right = p;                                                              \
    p->parent = y;                                                             \
  }                                                                            \
  static rbtree##_node *_rbtree_##rbtree##_root(rbtree *self) {                \
    return self->_root;                                                        \
  }                                                                            \
  static bool _rbtree_##rbtree##_empty(rbtree *self) {                         \
    return self->_size == 0;                                                   \
  }                                                                            \
  static size_t _rbtree_##rbtree##_size(rbtree *self) { return self->_size; }  \
  static void _rbtree_##rbtree##_clear(rbtree *self) {                         \
    while (self->_size > 0) {                                                  \
      self->erase_node(self, self->_root);                                     \
    }                                                                          \
  }                                                                            \
  static void _rbtree_##rbtree##_insert_fixup(rbtree *self,                    \
                                              rbtree##_node *p) {              \
    while (p->parent->color == RB_RED) {                                       \
      rbtree##_node *y;                                                        \
      if (p->parent == p->parent->parent->left) {                              \
        y = p->parent->parent->right;                                          \
        if (y->color == RB_RED) {                                              \
          p->parent->color = RB_BLACK;                                         \
          y->color = RB_BLACK;                                                 \
          p->parent->parent->color = RB_RED;                                   \
          p = p->parent->parent;                                               \
        } else if (p == p->parent->right) {                                    \
          p = p->parent;                                                       \
          self->rotate_left(self, p);                                          \
        } else {                                                               \
          p->parent->color = RB_BLACK;                                         \
          p->parent->parent->color = RB_RED;                                   \
          self->rotate_right(self, p->parent->parent);                         \
        }                                                                      \
      } else if (p->parent == p->parent->parent->right) {                      \
        y = p->parent->parent->left;                                           \
        if (y->color == RB_RED) {                                              \
          p->parent->color = RB_BLACK;                                         \
          y->color = RB_BLACK;                                                 \
          p->parent->parent->color = RB_RED;                                   \
          p = p->parent->parent;                                               \
        } else if (p == p->parent->left) {                                     \
          p = p->parent;                                                       \
          self->rotate_right(self, p);                                         \
        } else {                                                               \
          p->parent->color = RB_BLACK;                                         \
          p->parent->parent->color = RB_RED;                                   \
          self->rotate_left(self, p->parent->parent);                          \
        }                                                                      \
      }                                                                        \
    }                                                                          \
    self->_root->color = RB_BLACK;                                             \
  }                                                                            \
  static rbtree##_node *_rbtree_##rbtree##_insert_node(rbtree *self,           \
                                                       rbtree##_node *p) {     \
    rbtree##_node *y = self->nil;                                              \
    rbtree##_node *x = self->_root;                                            \
    while (x != self->nil) {                                                   \
      y = x;                                                                   \
      if (self->comp(p->value, x->value)) {                                    \
        x = x->left;                                                           \
      } else {                                                                 \
        x = x->right;                                                          \
      }                                                                        \
    }                                                                          \
    p->parent = y;                                                             \
    if (y == self->nil) {                                                      \
      self->_root = p;                                                         \
    } else if (self->comp(p->value, y->value)) {                               \
      y->left = p;                                                             \
    } else {                                                                   \
      y->right = p;                                                            \
    }                                                                          \
    self->_size++;                                                             \
    p->left = self->nil;                                                       \
    p->right = self->nil;                                                      \
    p->color = RB_RED;                                                         \
    self->insert_fixup(self, p);                                               \
    return p;                                                                  \
  }                                                                            \
  static rbtree##_node *_rbtree_##rbtree##_insert(rbtree *self, T value) {     \
    rbtree##_node *p = (rbtree##_node *)malloc(sizeof(rbtree##_node));         \
    p->value = value;                                                          \
    return self->insert_node(self, p);                                         \
  }                                                                            \
  static void _rbtree_##rbtree##_transplant(rbtree *self, rbtree##_node *u,    \
                                            rbtree##_node *v) {                \
    if (u->parent == self->nil) {                                              \
      self->_root = v;                                                         \
    } else if (u == u->parent->left) {                                         \
      u->parent->left = v;                                                     \
    } else {                                                                   \
      u->parent->right = v;                                                    \
    }                                                                          \
    v->parent = u->parent;                                                     \
  }                                                                            \
  static void _rbtree_##rbtree##_erase_fixup(rbtree *self, rbtree##_node *x) { \
    while (x != self->_root && x->color == RB_BLACK) {                         \
      if (x == x->parent->left) {                                              \
        rbtree##_node *w = x->parent->right;                                   \
        if (w->color == RB_RED) {                                              \
          w->color = RB_BLACK;                                                 \
          x->parent->color = RB_RED;                                           \
          self->rotate_left(self, x->parent);                                  \
          w = x->parent->right;                                                \
        }                                                                      \
        if (w->left->color == RB_BLACK && w->right->color == RB_BLACK) {       \
          w->color = RB_RED;                                                   \
          x = x->parent;                                                       \
        } else if (w->right->color == RB_BLACK) {                              \
          w->left->color = RB_BLACK;                                           \
          w->color = RB_RED;                                                   \
          self->rotate_right(self, w);                                         \
          w = x->parent->right;                                                \
        } else {                                                               \
          w->color = x->parent->color;                                         \
          x->parent->color = RB_BLACK;                                         \
          w->right->color = RB_BLACK;                                          \
          self->rotate_left(self, x->parent);                                  \
          x = self->_root;                                                     \
        }                                                                      \
      } else {                                                                 \
        rbtree##_node *w = x->parent->left;                                    \
        if (w->color == RB_RED) {                                              \
          w->color = RB_BLACK;                                                 \
          x->parent->color = RB_RED;                                           \
          self->rotate_right(self, x->parent);                                 \
          w = x->parent->left;                                                 \
        }                                                                      \
        if (w->right->color == RB_BLACK && w->left->color == RB_BLACK) {       \
          w->color = RB_RED;                                                   \
          x = x->parent;                                                       \
        } else if (w->left->color == RB_BLACK) {                               \
          w->right->color = RB_BLACK;                                          \
          w->color = RB_RED;                                                   \
          self->rotate_left(self, w);                                          \
          w = x->parent->left;                                                 \
        } else {                                                               \
          w->color = x->parent->color;                                         \
          x->parent->color = RB_BLACK;                                         \
          w->left->color = RB_BLACK;                                           \
          self->rotate_right(self, x->parent);                                 \
          x = self->_root;                                                     \
        }                                                                      \
      }                                                                        \
    }                                                                          \
    x->color = RB_BLACK;                                                       \
  }                                                                            \
  static void _rbtree_##rbtree##_erase_node(rbtree *self, rbtree##_node *p) {  \
    rbtree##_node *y = p;                                                      \
    rbtree##_node *x = (rbtree##_node *)malloc(sizeof(rbtree##_node));         \
    char y_color = y->color;                                                   \
    if (p->left == self->nil) {                                                \
      x = p->right;                                                            \
      self->transplant(self, p, p->right);                                     \
    } else if (p->right == self->nil) {                                        \
      x = p->left;                                                             \
      self->transplant(self, p, p->left);                                      \
    } else {                                                                   \
      y = self->min_child(self, p->right);                                     \
      y_color = y->color;                                                      \
      x = y->right;                                                            \
      if (y->parent == p) {                                                    \
        x->parent = y;                                                         \
      } else {                                                                 \
        self->transplant(self, y, y->right);                                   \
        y->right = p->right;                                                   \
        y->right->parent = y;                                                  \
      }                                                                        \
      self->transplant(self, p, y);                                            \
      y->left = p->left;                                                       \
      y->left->parent = y;                                                     \
      y->color = p->color;                                                     \
    }                                                                          \
    self->_size--;                                                             \
    if (y_color == RB_BLACK) {                                                 \
      self->erase_fixup(self, x);                                              \
    }                                                                          \
  }                                                                            \
  static void _rbtree_##rbtree##_erase(rbtree *self, T value) {                \
    rbtree##_node *p = self->find(self, value);                                \
    if (p == NULL) {                                                           \
      return;                                                                  \
    }                                                                          \
    self->erase_node(self, p);                                                 \
  }                                                                            \
  static rbtree##_node *_rbtree_##rbtree##_find_from(                          \
      rbtree *self, rbtree##_node *p, T value) {                               \
    while (p != NULL && value != p->value) {                                   \
      if (self->comp(value, p->value)) {                                       \
        p = p->left;                                                           \
      } else {                                                                 \
        p = p->right;                                                          \
      }                                                                        \
    }                                                                          \
    return p;                                                                  \
  }                                                                            \
  static rbtree##_node *_rbtree_##rbtree##_find(rbtree *self, T value) {       \
    return self->find_from(self, self->_root, value);                          \
  }                                                                            \
  static void _rbtree_##rbtree##_pre_order(rbtree *self) {                     \
    rbtree##_node *p = self->_root;                                            \
    CREATE_VECTOR(__##rbtree##_vector, v)                                      \
    CREATE_STACK(__##rbtree##_stack, s)                                        \
    while (true) {                                                             \
      while (p != self->nil && p != NULL) {                                    \
        T val = p->value;                                                      \
        v->push_back(v, val);                                                  \
        s->push(s, p->right);                                                  \
        p = p->left;                                                           \
      }                                                                        \
      if (s->empty(s)) {                                                       \
        break;                                                                 \
      }                                                                        \
      p = s->top(s);                                                           \
      s->pop(s);                                                               \
    }                                                                          \
    for (int i = 0; i < v->size(v); i++) {                                     \
      custom_print(v->at(v, i));                                               \
      printf(" ");                                                             \
    }                                                                          \
    printf("\n");                                                              \
    FREE_STACK(__##rbtree##_stack, s)                                          \
    FREE_VECTOR(__##rbtree##_vector, v)                                        \
  }                                                                            \
  static void _rbtree_##rbtree##_in_order(rbtree *self) {                      \
    rbtree##_node *p = self->_root;                                            \
    CREATE_VECTOR(__##rbtree##_vector, v)                                      \
    CREATE_STACK(__##rbtree##_stack, s)                                        \
    while (true) {                                                             \
      while (p != self->nil && p != NULL) {                                    \
        s->push(s, p);                                                         \
        p = p->left;                                                           \
      }                                                                        \
      if (s->empty(s)) {                                                       \
        break;                                                                 \
      }                                                                        \
      p = s->top(s);                                                           \
      s->pop(s);                                                               \
      T val = p->value;                                                        \
      v->push_back(v, val);                                                    \
      p = p->right;                                                            \
    }                                                                          \
    for (int i = 0; i < v->size(v); i++) {                                     \
      custom_print(v->at(v, i));                                               \
      printf(" ");                                                             \
    }                                                                          \
    printf("\n");                                                              \
    FREE_STACK(__##rbtree##_stack, s)                                          \
    FREE_VECTOR(__##rbtree##_vector, v)                                        \
  }                                                                            \
  static void __rbtree_##rbtree##_post_order(rbtree *self, rbtree##_node *p,   \
                                             __##rbtree##_vector *v) {         \
    if (p == self->nil || p == NULL) {                                         \
      return;                                                                  \
    }                                                                          \
    self->_post_order(self, p->left, v);                                       \
    self->_post_order(self, p->right, v);                                      \
    v->push_back(v, p->value);                                                 \
  }                                                                            \
  static void _rbtree_##rbtree##_post_order(rbtree *self) {                    \
    CREATE_VECTOR(__##rbtree##_vector, v)                                      \
    self->_post_order(self, self->_root, v);                                   \
    for (int i = 0; i < v->size(v); i++) {                                     \
      custom_print(v->at(v, i));                                               \
      printf(" ");                                                             \
    }                                                                          \
    printf("\n");                                                              \
    FREE_VECTOR(__##rbtree##_vector, v)                                        \
  }                                                                            \
  static void _rbtree_##rbtree##_level_order(rbtree *self) {                   \
    rbtree##_node *p = self->_root;                                            \
    CREATE_VECTOR(__##rbtree##_vector, v)                                      \
    if (p == NULL || p == self->nil) {                                         \
      return;                                                                  \
    }                                                                          \
    CREATE_QUEUE(__##rbtree##_queue, q)                                        \
    q->push(q, p);                                                             \
    while (!q->empty(q)) {                                                     \
      p = q->front(q);                                                         \
      q->pop(q);                                                               \
      T val = p->value;                                                        \
      v->push_back(v, val);                                                    \
      if (p->left != self->nil) {                                              \
        q->push(q, p->left);                                                   \
      }                                                                        \
      if (p->right != self->nil) {                                             \
        q->push(q, p->right);                                                  \
      }                                                                        \
    }                                                                          \
    for (int i = 0; i < v->size(v); i++) {                                     \
      custom_print(v->at(v, i));                                               \
      printf(" ");                                                             \
    }                                                                          \
    printf("\n");                                                              \
    FREE_QUEUE(__##rbtree##_queue, q)                                          \
    FREE_VECTOR(__##rbtree##_vector, v)                                        \
  }                                                                            \
  static void _rbtree_##rbtree##_print_from(rbtree *self, rbtree##_node *p,    \
                                            int prefix) {                      \
    char prefix_str[prefix];                                                   \
    for (int i = 0; i < prefix; i++) {                                         \
      prefix_str[i] = ' ';                                                     \
    }                                                                          \
    prefix_str[prefix] = '\0';                                                 \
    if (p == self->nil) {                                                      \
      return;                                                                  \
    }                                                                          \
    printf("%s", prefix_str);                                                  \
    if (p == self->_root) {                                                    \
      printf("--");                                                            \
    } else if (p == p->parent->left) {                                         \
      printf("->");                                                            \
    } else if (p == p->parent->right) {                                        \
      printf("=>");                                                            \
    }                                                                          \
    p->color == RB_RED ? printf("\033[31m") : printf("\033[0m");               \
    custom_print(p->value);                                                    \
    printf("\033[0m\n");                                                       \
    self->print_from(self, p->left, prefix + 2);                               \
    self->print_from(self, p->right, prefix + 2);                              \
  }                                                                            \
  static void _rbtree_##rbtree##_print(rbtree *self) {                         \
    self->print_from(self, self->_root, 0);                                    \
  }                                                                            \
  static void _rbtree_##rbtree##_assign_method(struct rbtree *obj) {           \
    obj->min_child = _rbtree_##rbtree##_min_child;                             \
    obj->max_child = _rbtree_##rbtree##_max_child;                             \
    obj->rotate_left = _rbtree_##rbtree##_rotate_left;                         \
    obj->rotate_right = _rbtree_##rbtree##_rotate_right;                       \
    obj->root = _rbtree_##rbtree##_root;                                       \
    obj->empty = _rbtree_##rbtree##_empty;                                     \
    obj->size = _rbtree_##rbtree##_size;                                       \
    obj->clear = _rbtree_##rbtree##_clear;                                     \
    obj->insert_fixup = _rbtree_##rbtree##_insert_fixup;                       \
    obj->insert_node = _rbtree_##rbtree##_insert_node;                         \
    obj->insert = _rbtree_##rbtree##_insert;                                   \
    obj->transplant = _rbtree_##rbtree##_transplant;                           \
    obj->erase_fixup = _rbtree_##rbtree##_erase_fixup;                         \
    obj->erase_node = _rbtree_##rbtree##_erase_node;                           \
    obj->erase = _rbtree_##rbtree##_erase;                                     \
    obj->find_from = _rbtree_##rbtree##_find_from;                             \
    obj->find = _rbtree_##rbtree##_find;                                       \
    obj->pre_order = _rbtree_##rbtree##_pre_order;                             \
    obj->in_order = _rbtree_##rbtree##_in_order;                               \
    obj->_post_order = __rbtree_##rbtree##_post_order;                         \
    obj->post_order = _rbtree_##rbtree##_post_order;                           \
    obj->level_order = _rbtree_##rbtree##_level_order;                         \
    obj->print_from = _rbtree_##rbtree##_print_from;                           \
    obj->print = _rbtree_##rbtree##_print;                                     \
  }                                                                            \
  static struct rbtree *_rbtree_##rbtree##_init_rbtree() {                     \
    struct rbtree *obj = (struct rbtree *)malloc(sizeof(struct rbtree));       \
    obj->nil = (struct rbtree##_node *)malloc(sizeof(struct rbtree##_node));   \
    obj->nil->parent = NULL;                                                   \
    obj->nil->left = NULL;                                                     \
    obj->nil->right = NULL;                                                    \
    obj->nil->color = RB_BLACK;                                                \
    obj->_root = obj->nil;                                                     \
    obj->_size = 0;                                                            \
    obj->comp = __##rbtree##_less;                                             \
    _rbtree_##rbtree##_assign_method(obj);                                     \
    return obj;                                                                \
  }                                                                            \
  static struct rbtree *_rbtree_##rbtree##init_rbtree_comp(                    \
      bool (*comp)(T a, T b)) {                                                \
    struct rbtree *obj = (struct rbtree *)malloc(sizeof(struct rbtree));       \
    obj->nil = (struct rbtree##_node *)malloc(sizeof(struct rbtree##_node));   \
    obj->nil->parent = NULL;                                                   \
    obj->nil->left = NULL;                                                     \
    obj->nil->right = NULL;                                                    \
    obj->nil->color = RB_BLACK;                                                \
    obj->_root = obj->nil;                                                     \
    obj->_size = 0;                                                            \
    obj->comp = comp;                                                          \
    _rbtree_##rbtree##_assign_method(obj);                                     \
    return obj;                                                                \
  }                                                                            \
  static void _rbtree_##rbtree##_free_rbtree(struct rbtree *obj) {             \
    obj->clear(obj);                                                           \
    free(obj->_root);                                                          \
    free(obj);                                                                 \
  }

#define CREATE_RBTREE(rbtree, obj)                                             \
  rbtree *obj = _rbtree_##rbtree##_init_rbtree();

#define CREATE_RBTREE_COMP(rbtree, obj, comp)                                  \
  rbtree *obj = _rbtree_##rbtree##_init_rbtree(comp);

#define FREE_RBTREE(rbtree, obj) _rbtree_##rbtree##_free_rbtree(obj);

#endif
