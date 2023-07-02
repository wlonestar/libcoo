#ifndef rbtree_h
#define rbtree_h

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "vector.h"
#include "stack.h"
#include "queue.h"

enum rb_color {
  RB_RED,
  RB_BLACK,
};

typedef struct rbtree_node {
  struct rbtree_node *parent;
  struct rbtree_node *left;
  struct rbtree_node *right;
  char color;
  int value;
} rbtree_node;

DECLARE_VECTOR(__rb_vector, int)
DECLARE_STACK(__rb_stack, struct rbtree_node *)
DECLARE_QUEUE(__rb_queue, struct rbtree_node *)
typedef bool (*Comp)(int a, int b);
typedef struct rbtree {
  struct rbtree_node *nil;
  struct rbtree_node *_root;
  size_t _size;
  Comp comp;
  /* Node operation */
  struct rbtree_node *(*min_child)(struct rbtree *self, struct rbtree_node *p);
  struct rbtree_node *(*max_child)(struct rbtree *self, struct rbtree_node *p);
  void (*rotate_left)(struct rbtree *self, struct rbtree_node *p);
  void (*rotate_right)(struct rbtree *self, struct rbtree_node *p);
  /* Element access */
  struct rbtree_node *(*root)(struct rbtree *self);
  /* Capacity */
  bool (*empty)(struct rbtree *self);
  size_t (*size)(struct rbtree *self);
  /* Modifiers */
  void (*clear)(struct rbtree *self);
  void (*insert_fixup)(struct rbtree *self, struct rbtree_node *p);
  struct rbtree_node *(*insert_node)(struct rbtree *self, struct rbtree_node *p);
  struct rbtree_node *(*insert)(struct rbtree *self, int value);
  void (*transplant)(struct rbtree *self, struct rbtree_node *u, struct rbtree_node *v);
  void (*erase_fixup)(struct rbtree *self, struct rbtree_node *x);
  void (*erase_node)(struct rbtree *self, struct rbtree_node *p);
  void (*erase)(struct rbtree *self, int value);
  /* Lookup */
  struct rbtree_node *(*find_from)(struct rbtree *self, struct rbtree_node *p, int value);
  struct rbtree_node *(*find)(struct rbtree *self, int value);
  /* Traverse */
  void (*pre_order)(struct rbtree *self);
  void (*in_order)(struct rbtree *self);
  void (*_post_order)(struct rbtree *self, struct rbtree_node *p, __rb_vector *v);
  void (*post_order)(struct rbtree *self);
  void (*level_order)(struct rbtree *self);
  /* Print */
  void (*print_from)(struct rbtree *self, struct rbtree_node *p, int prefix);
  void (*print)(struct rbtree *self);
} rbtree;

static rbtree_node *rbtree_min_child(rbtree *self, rbtree_node *p) {
  while (p->left != self->nil) {
    p = p->left;
  }
  return p;
}

static rbtree_node *rbtree_max_child(rbtree *self, rbtree_node *p) {
  while (p->right != self->nil) {
    p = p->right;
  }
  return p;
}

static void rbtree_rotate_left(rbtree *self, rbtree_node *p) {
  rbtree_node *y = p->right;
  p->right = y->left;
  if (y->left != self->nil) {
    y->left->parent = p;
  }
  y->parent = p->parent;
  if (p->parent == self->nil) {
    self->_root = y;
  } else if (p == p->parent->left) {
    p->parent->left = y;
  } else {
    p->parent->right = y;
  }
  y->left = p;
  p->parent = y;
}

static void rbtree_rotate_right(rbtree *self, rbtree_node *p) {
  rbtree_node *y = p->left;
  p->left = y->right;
  if (y->right != self->nil) {
    y->right->parent = p;
  }
  y->parent = p->parent;
  if (p->parent == self->nil) {
    self->_root = y;
  } else if (p == p->parent->right) {
    p->parent->right = y;
  } else {
    p->parent->left = y;
  }
  y->right = p;
  p->parent = y;
}

static rbtree_node *rbtree_root(rbtree *self) {
  return self->_root;
}

static bool rbtree_empty(rbtree *self) {
  return self->_size == 0;
}

static size_t rbtree_size(rbtree *self) {
  return self->_size;
}

static void rbtree_clear(rbtree *self) {
  while (self->_size > 0) {
    self->erase_node(self, self->_root);
  }
}

static void rbtree_insert_fixup(rbtree *self, rbtree_node *p) {
  while (p->parent->color == RB_RED) {
    rbtree_node *y;
    if (p->parent == p->parent->parent->left) {
      y = p->parent->parent->right;
      if (y->color == RB_RED) {
        p->parent->color = RB_BLACK;
        y->color = RB_BLACK;
        p->parent->parent->color = RB_RED;
        p = p->parent->parent;
      } else if (p == p->parent->right) {
        p = p->parent;
        self->rotate_left(self, p);
      } else {
        p->parent->color = RB_BLACK;
        p->parent->parent->color = RB_RED;
        self->rotate_right(self, p->parent->parent);
      }
    } else if (p->parent == p->parent->parent->right) {
      y = p->parent->parent->left;
      if (y->color == RB_RED) {
        p->parent->color = RB_BLACK;
        y->color = RB_BLACK;
        p->parent->parent->color = RB_RED;
        p = p->parent->parent;
      } else if (p == p->parent->left) {
        p = p->parent;
        self->rotate_right(self, p);
      } else {
        p->parent->color = RB_BLACK;
        p->parent->parent->color = RB_RED;
        self->rotate_left(self, p->parent->parent);
      }
    }
  }
  self->_root->color = RB_BLACK;
}

static rbtree_node *rbtree_insert_node(rbtree *self, rbtree_node *p) {
  rbtree_node *y = self->nil;
  rbtree_node *x = self->_root;
  while (x != self->nil) {
    y = x;
    if (self->comp(p->value, x->value)) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  p->parent = y;
  if (y == self->nil) {
    self->_root = p;
  } else if (self->comp(p->value, y->value)) {
    y->left = p;
  } else {
    y->right = p;
  }
  self->_size++;
  p->left = self->nil;
  p->right = self->nil;
  p->color = RB_RED;
  self->insert_fixup(self, p);
  return p;
}

static rbtree_node *rbtree_insert(rbtree *self, int value) {
  rbtree_node *p = (rbtree_node *) malloc(sizeof(rbtree_node));
  p->value = value;
  return self->insert_node(self, p);
}

static void rbtree_transplant(rbtree *self, rbtree_node *u, rbtree_node *v) {
  if (u->parent == self->nil) {
    self->_root = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  v->parent = u->parent;
}

static void rbtree_erase_fixup(rbtree *self, rbtree_node *x) {
  while (x != self->_root && x->color == RB_BLACK) {
    if (x == x->parent->left) {
      rbtree_node *w = x->parent->right;
      if (w->color == RB_RED) {
        w->color = RB_BLACK;
        x->parent->color = RB_RED;
        self->rotate_left(self, x->parent);
        w = x->parent->right;
      }
      if (w->left->color == RB_BLACK && w->right->color == RB_BLACK) {
        w->color = RB_RED;
        x = x->parent;
      } else if (w->right->color == RB_BLACK) {
        w->left->color = RB_BLACK;
        w->color = RB_RED;
        self->rotate_right(self, w);
        w = x->parent->right;
      } else {
        w->color = x->parent->color;
        x->parent->color = RB_BLACK;
        w->right->color = RB_BLACK;
        self->rotate_left(self, x->parent);
        x = self->_root;
      }
    } else {
      rbtree_node *w = x->parent->left;
      if (w->color == RB_RED) {
        w->color = RB_BLACK;
        x->parent->color = RB_RED;
        self->rotate_right(self, x->parent);
        w = x->parent->left;
      }
      if (w->right->color == RB_BLACK && w->left->color == RB_BLACK) {
        w->color = RB_RED;
        x = x->parent;
      } else if (w->left->color == RB_BLACK) {
        w->right->color = RB_BLACK;
        w->color = RB_RED;
        self->rotate_left(self, w);
        w = x->parent->left;
      } else {
        w->color = x->parent->color;
        x->parent->color = RB_BLACK;
        w->left->color = RB_BLACK;
        self->rotate_right(self, x->parent);
        x = self->_root;
      }
    }
  }
  x->color = RB_BLACK;
}

static void rbtree_erase_node(rbtree *self, rbtree_node *p) {
  rbtree_node *y = p;
  rbtree_node *x = (rbtree_node *) malloc(sizeof(rbtree_node));
  char y_color = y->color;
  if (p->left == self->nil) {
    x = p->right;
    self->transplant(self, p, p->right);
  } else if (p->right == self->nil) {
    x = p->left;
    self->transplant(self, p, p->left);
  } else {
    y = self->min_child(self, p->right);
    y_color = y->color;
    x = y->right;
    if (y->parent == p) {
      x->parent = y;
    } else {
      self->transplant(self, y, y->right);
      y->right = p->right;
      y->right->parent = y;
    }
    self->transplant(self, p, y);
    y->left = p->left;
    y->left->parent = y;
    y->color = p->color;
  }
  self->_size--;
  if (y_color == RB_BLACK) {
    self->erase_fixup(self, x);
  }
}

static void rbtree_erase(rbtree *self, int value) {
  rbtree_node *p = self->find(self, value);
  if (p == NULL) {
    return ;
  }
  self->erase_node(self, p);
}

static rbtree_node *rbtree_find_from(rbtree *self, rbtree_node *p, int value) {
  while (p != NULL && value != p->value) {
    if (self->comp(value, p->value)) {
      p = p->left;
    } else {
      p = p->right;
    }
  }
  return p;
}

static rbtree_node *rbtree_find(rbtree *self, int value) {
  return self->find_from(self, self->_root, value);
}

static void rbtree_pre_order(rbtree *self) {
  rbtree_node *p = self->_root;
  CREATE_VECTOR(__rb_vector, v)
  CREATE_STACK(__rb_stack, s)
  while (true) {
    while (p != self->nil && p != NULL) {
      int val = p->value;
      v->push_back(v, val);
      s->push(s, p->right);
      p = p->left;
    }
    if (s->empty(s)) {
      break;
    }
    p = s->top(s);
    s->pop(s);
  }
  for (int i = 0; i < v->size(v); i++) {
    printf("%d ", v->at(v, i));
  }
  printf("\n");
  FREE_STACK(__rb_stack, s)
  FREE_VECTOR(__rb_vector, v)
}

static void rbtree_in_order(rbtree *self) {
  rbtree_node *p = self->_root;
  CREATE_VECTOR(__rb_vector, v)
  CREATE_STACK(__rb_stack, s)
  while (true) {
    while (p != self->nil && p != NULL) {
      s->push(s, p);
      p = p->left;
    }
    if (s->empty(s)) {
      break;
    }
    p = s->top(s);
    s->pop(s);
    int val = p->value;
    v->push_back(v, val);
    p = p->right;
  }
  for (int i = 0; i < v->size(v); i++) {
    printf("%d ", v->at(v, i));
  }
  printf("\n");
  FREE_STACK(__rb_stack, s)
  FREE_VECTOR(__rb_vector, v)
}

static void __rbtree_post_order(rbtree *self, rbtree_node *p, __rb_vector *v) {
  if (p == self->nil || p == NULL) {
    return;
  }
  self->_post_order(self, p->left, v);
  self->_post_order(self, p->right, v);
  v->push_back(v, p->value);
}

static void rbtree_post_order(rbtree *self) {
  CREATE_VECTOR(__rb_vector, v)
  self->_post_order(self, self->_root, v);
  for (int i = 0; i < v->size(v); i++) {
    printf("%d ", v->at(v, i));
  }
  printf("\n");
  FREE_VECTOR(__rb_vector, v)
}

static void rbtree_level_order(rbtree *self) {
  rbtree_node *p = self->_root;
  CREATE_VECTOR(__rb_vector, v)
  if (p == NULL || p == self->nil) {
    return;
  }
  CREATE_QUEUE(__rb_queue, q)
  q->push(q, p);
  while (!q->empty(q)) {
    p = q->front(q);
    q->pop(q);
    int val = p->value;
    v->push_back(v, val);
    if (p->left != self->nil) {
      q->push(q, p->left);
    }
    if (p->right != self->nil) {
      q->push(q, p->right);
    }
  }
  for (int i = 0; i < v->size(v); i++) {
    printf("%d ", v->at(v, i));
  }
  printf("\n");
  FREE_QUEUE(__rb_queue, q)
  FREE_VECTOR(__rb_vector, v)
}

static void rbtree_print_from(rbtree *self, rbtree_node *p, int prefix) {
  char prefix_str[prefix];
  for (int i = 0; i < prefix; i++) {
    prefix_str[i] = ' ';
  }
  prefix_str[prefix] = '\0';
  if (p == self->nil) {
    return;
  }
  printf("%s", prefix_str);
  if (p == self->_root) {
    printf("--");
  } else if (p == p->parent->left) {
    printf("->");
  } else if (p == p->parent->right) {
    printf("=>");
  }
  if (p->color == RB_RED) {
    printf("\033[31m%d\033[0m\n", p->value);
  } else {
    printf("\033[0m%d\033[0m\n", p->value);
  }
  self->print_from(self, p->left, prefix + 2);
  self->print_from(self, p->right, prefix + 2);
}

static void rbtree_print(rbtree *self) {
  self->print_from(self, self->_root, 0);
}

static void rbtree_assign_method(struct rbtree *obj) {
  obj->min_child = rbtree_min_child;
  obj->max_child = rbtree_max_child;
  obj->rotate_left = rbtree_rotate_left;
  obj->rotate_right = rbtree_rotate_right;
  obj->root = rbtree_root;
  obj->empty = rbtree_empty;
  obj->size = rbtree_size;
  obj->clear = rbtree_clear;
  obj->insert_fixup = rbtree_insert_fixup;
  obj->insert_node = rbtree_insert_node;
  obj->insert = rbtree_insert;
  obj->transplant = rbtree_transplant;
  obj->erase_fixup = rbtree_erase_fixup;
  obj->erase_node = rbtree_erase_node;
  obj->erase = rbtree_erase;
  obj->find_from = rbtree_find_from;
  obj->find = rbtree_find;
  obj->pre_order = rbtree_pre_order;
  obj->in_order = rbtree_in_order;
  obj->_post_order = __rbtree_post_order;
  obj->post_order = rbtree_post_order;
  obj->level_order = rbtree_level_order;
  obj->print_from = rbtree_print_from;
  obj->print = rbtree_print;
}

bool less(int a, int b) { return a <= b; }

bool greater(int a, int b) { return a > b; }

static struct rbtree *rbtree_init_rbtree() {
  struct rbtree *obj = (struct rbtree *) malloc(sizeof(struct rbtree));
  obj->nil = (struct rbtree_node *) malloc(sizeof(struct rbtree_node));
  obj->nil->parent = NULL;
  obj->nil->left = NULL;
  obj->nil->right = NULL;
  obj->nil->color = RB_BLACK;
  obj->_root = obj->nil;
  obj->_size = 0;
  obj->comp = less;
  rbtree_assign_method(obj);
  return obj;
}

static struct rbtree *rbtree_init_rbtree_comp(bool (*comp)(int a, int b)) {
  struct rbtree *obj = (struct rbtree *) malloc(sizeof(struct rbtree));
  obj->nil = (struct rbtree_node *) malloc(sizeof(struct rbtree_node));
  obj->nil->parent = NULL;
  obj->nil->left = NULL;
  obj->nil->right = NULL;
  obj->nil->color = RB_BLACK;
  obj->_root = obj->nil;
  obj->_size = 0;
  obj->comp = comp;
  rbtree_assign_method(obj);
  return obj;
}

static void rbtree_free_rbtree(struct rbtree *obj) {
  obj->clear(obj);
  free(obj->_root);
  free(obj);
}

#endif
