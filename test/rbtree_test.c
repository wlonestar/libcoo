#include "rbtree.h"
#include <assert.h>

void test_insert() {
  rbtree *t1 = rbtree_init_rbtree();
  for (int i = 0; i < 18; i++) {
    t1->insert(t1, i);
  }
  t1->print(t1);
  rbtree *t2 = rbtree_init_rbtree_comp(greater);
  for (int i = 0; i < 12; i++) {
    t2->insert(t2, i);
  }
  t2->print(t2);
  t2->in_order(t2);
}

void test_erase() {
  rbtree *t = rbtree_init_rbtree();
  for (int i = 0; i < 12; i++) {
    t->insert(t, i);
  }
  t->print(t);
  t->erase(t, t->_root);
  t->erase(t, t->_root->left);
  t->print(t);
  t->in_order(t);
  t->erase(t, 0);
  t->in_order(t);
  t->erase(t, 12);
  t->in_order(t);
  t->clear(t);
  assert(t->size(t) == 0);
  for (int i = 0; i < 12; i++) {
    t->insert(t, i);
  }
  t->in_order(t);
  t->insert(t, 1);
  t->in_order(t);
}

void test_traverse() {
  rbtree *t = rbtree_init_rbtree();
  t->pre_order(t);
  t->in_order(t);
  t->post_order(t);
  t->level_order(t);
  for (int i = 1; i <= 7; i++) {
    t->insert(t, i);
  }
  t->print(t);
  assert(t->size(t) == 7);
  t->pre_order(t);
  t->in_order(t);
  t->post_order(t);
  t->level_order(t);
}

int main() {
  test_insert();
  test_erase();
  test_traverse();
  return 0;
}
