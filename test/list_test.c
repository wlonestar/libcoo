#include "list.h"
#include <assert.h>

void test_list_empty() {
  list *c = init_list();
  assert(c->empty(c));
  c->push_back(c, 1);
  assert(!c->empty(c));
  c->clear(c);
  assert(c->empty(c));
}

void test_list_resize() {
  {
    list *l = init_list_n(10, 0);
    l->resize(l, 5);
    assert(l->size(l) == 5);
  }
  {
    list *l = init_list_n(10, 0);
    l->resize(l, 20);
    assert(l->size(l) == 20);
  }
  {
    list *l = init_list_n(5, 2);
    l->resize(l, 2);
    assert(l->size(l) == 2);
  }
  {
    list *l = init_list_n(5, 2);
    l->resize(l, 10);
    assert(l->size(l) == 10);
    assert(l->front(l) == 2);
    assert(l->back(l) == 0);
  }
}

void test_list_size() {
  list *c = init_list();
  assert(c->size(c) == 0);
  c->push_back(c, 2);
  assert(c->size(c) == 1);
  c->push_back(c, 1);
  assert(c->size(c) == 2);
  c->push_back(c, 3);
  assert(c->size(c) == 3);
  c->erase(c, c->begin(c));
  assert(c->size(c) == 2);
  c->erase(c, c->begin(c));
  assert(c->size(c) == 1);
  c->erase(c, c->begin(c));
  assert(c->size(c) == 0);
}

void test_list_capacity() {
  test_list_empty();
  test_list_resize();
  test_list_size();
}

void test_list_clear() {
  int a[] = {1, 2, 3};
  list *c = init_list_array(a, a + 3);
  c->clear(c);
  assert(c->empty(c));
}

void test_list_insert() {
  {
    list *d = init_list_n(10, 1);
    d->insert(d, d->begin(d)->next->next, 6);
    d->insert(d, d->begin(d)->next->next, 5);
    d->insert(d, d->begin(d)->next->next, 4);
    d->insert(d, d->begin(d)->next->next, 3);
    assert(d->size(d) == 14);
    struct list_node *i = d->begin(d);
    assert(i->data == 1);
    i = i->next;
    assert(i->data == 1);
    i = i->next;
    assert(i->data == 3);
    i = i->next;
    assert(i->data == 4);
    i = i->next;
    assert(i->data == 5);
    i = i->next;
    assert(i->data == 6);
    i = i->next;
    assert(i->data == 1);
    i = i->next;
    assert(i->data == 1);
    i = i->next;
    assert(i->data == 1);
    i = i->next;
    assert(i->data == 1);
    i = i->next;
    assert(i->data == 1);
    i = i->next;
    assert(i->data == 1);
    i = i->next;
    assert(i->data == 1);
    i = i->next;
    assert(i->data == 1);
    i = i->next;
  }
  {
    int a1[] = {1, 2, 3};
    list *l = init_list();
    struct list_node *i = l->insert_range(l, l->begin(l), a1, a1 + 3);
    assert(i = l->begin(l));
    assert(l->size(l) == 3);
    assert(i->data == 1);
    i = i->next;
    assert(i->data == 2);
    i = i->next;
    assert(i->data == 3);
    int a2[] = {4, 5, 6};
    i = l->insert_range(l, i, a2, a2 + 3);
    assert(i->data == 4);
    assert(l->size(l) == 6);
    i = l->begin(l);
    assert(i->data == 1);
    i = i->next;
    assert(i->data == 2);
    i = i->next;
    assert(i->data == 4);
    i = i->next;
    assert(i->data == 5);
    i = i->next;
    assert(i->data == 6);
    i = i->next;
    assert(i->data == 3);
  }
}

void test_list_pop_back() {
  int a[] = {1, 2, 3};
  list *c = init_list_array(a, a + 3);
  c->pop_back(c);
  assert(c->front(c) == 1);
  assert(c->begin(c)->next->data == 2);
  c->pop_back(c);
  assert(c->front(c) == 1);
  c->pop_back(c);
  assert(c->empty(c));
}

void test_list_pop_front() {
  int a[] = {1, 2, 3};
  list *c = init_list_array(a, a + 3);
  c->pop_back(c);
  assert(c->front(c) == 1);
  assert(c->begin(c)->next->data == 2);
  c->pop_back(c);
  assert(c->front(c) == 1);
  c->pop_back(c);
  assert(c->empty(c));
}

void test_list_push_back() {
  list *c = init_list();
  for (int i = 0; i < 5; i++) {
    c->push_back(c, i);
  }
  int a[] = {0, 1, 2, 3, 4};
  struct list_node *p = c->begin(c);
  for (int i = 0; i < 5; i++) {
    assert(p->data == a[i]);
    p = p->next;
  }
}

void test_list_push_front() {
  list *c = init_list();
  for (int i = 0; i < 5; i++) {
    c->push_front(c, i);
  }
  int a[] = {4, 3, 2, 1, 0};
  struct list_node *p = c->begin(c);
  for (int i = 0; i < 5; i++) {
    assert(p->data == a[i]);
    p = p->next;
  }
}

void test_list_modifiers() {
  test_list_clear();
  test_list_insert();
  test_list_pop_back();
  test_list_pop_front();
  test_list_push_back();
  test_list_push_front();
}

void test_list_merge() {
  int a1[] = {1, 3, 7, 9, 10};
  int a2[] = {0, 2, 4, 5, 6, 8, 11};
  int a3[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  list *c1 = init_list_array(a1, a1 + 5);
  list *c2 = init_list_array(a2, a2 + 7);
  c1->merge(c1, c2);
  struct list_node *p = c1->begin(c1);
  for (int i = 0; i < 12; i++) {
    assert(p->data == a3[i]);
    p = p->next;
  }
  assert(c2->empty(c2));
}

bool greater(int a, int b) { return a >= b; }

void test_list_merge_by() {
  int a1[] = {10, 9, 7, 3, 1};
  int a2[] = {11, 8, 6, 5, 4, 2, 0};
  int a3[] = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  list *c1 = init_list_array(a1, a1 + 5);
  list *c2 = init_list_array(a2, a2 + 7);
  c1->merge_by(c1, c2, greater);
  struct list_node *p = c1->begin(c1);
  for (int i = 0; i < 12; i++) {
    assert(p->data == a3[i]);
    p = p->next;
  }
  assert(c2->empty(c2));
}

void test_list_remove() {
  int a1[] = {1, 2, 3, 4};
  int a2[] = {1, 2, 4};
  list *c = init_list_array(a1, a1 + 4);
  assert(c->remove(c, 3) == 1);
  c->remove(c, 3);
  struct list_node *p = c->begin(c);
  for (int i = 0; i < 3; i++) {
    assert(p->data == a2[i]);
    p = p->next;
  }
}

bool pred(int n) { return n < 3; }

void test_list_remove_if() {
  int a1[] = {1, 2, 3, 4};
  int a2[] = {3, 4};
  list *c = init_list_array(a1, a1 + 4);
  assert(c->remove_if(c, pred) == 2);
  c->remove_if(c, pred);
  struct list_node *p = c->begin(c);
  for (int i = 0; i < 2; i++) {
    assert(p->data == a2[i]);
    p = p->next;
  }
}

void test_list_reverse() {
  int a1[] = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  int a2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  list *c = init_list_array(a1, a1 + 12);
  c->reverse(c);
  struct list_node *p = c->begin(c);
  for (int i = 0; i < 12; i++) {
    assert(p->data == a2[i]);
    p = p->next;
  }
}

void test_list_sort() {
  int a1[] = {4, 8, 1, 0, 5, 7, 2, 3, 6, 11, 10, 9};
  int a2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  list *c = init_list_array(a1, a1 + 12);
  c->sort(c);
  struct list_node *p = c->begin(c);
  for (int i = 0; i < 12; i++) {
    assert(p->data == a2[i]);
    p = p->next;
  }
}

void test_list_sort_by() {
  int a1[] = {4, 8, 1, 0, 5, 7, 2, 3, 6, 11, 10, 9};
  int a2[] = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  list *c = init_list_array(a1, a1 + 12);
  c->sort_by(c, greater);
  struct list_node *p = c->begin(c);
  for (int i = 0; i < 12; i++) {
    assert(p->data == a2[i]);
    p = p->next;
  }
}

void test_list_splice() {
  int a1[] = {1, 2, 3};
  int a2[] = {4, 5, 6};
  {
    list *l1 = init_list();
    list *l2 = init_list();
    l1->splice(l1, l1->end(l1), l2);
    assert(l1->size(l1) == 0);
    assert(l2->size(l2) == 0);
  }
  {
    list *l1 = init_list();
    list *l2 = init_list_array(a2, a2 + 1);
    l1->splice(l1, l1->end(l1), l2);
    assert(l1->size(l1) == 1);
    assert(l2->size(l2) == 0);
    struct list_node *i = l1->begin(l1);
    assert(i->data == 4);
  }
  {
    list *l1 = init_list();
    list *l2 = init_list_array(a2, a2 + 2);
    l1->splice(l1, l1->end(l1), l2);
    assert(l1->size(l1) == 2);
    assert(l2->size(l2) == 0);
    struct list_node *i = l1->begin(l1);
    assert(i->data == 4);
    i = i->next;
    assert(i->data == 5);
  }
  {
    list *l1 = init_list();
    list *l2 = init_list_array(a2, a2 + 3);
    l1->splice(l1, l1->end(l1), l2);
    assert(l1->size(l1) == 3);
    assert(l2->size(l2) == 0);
    struct list_node *i = l1->begin(l1);
    assert(i->data == 4);
    i = i->next;
    assert(i->data == 5);
    i = i->next;
    assert(i->data == 6);
  }
  {
    list *l1 = init_list_array(a1, a1 + 1);
    list *l2 = init_list();
    l1->splice(l1, l1->begin(l1), l2);
    assert(l1->size(l1) == 1);
    assert(l2->size(l2) == 0);
    struct list_node *i = l1->begin(l1);
    assert(i->data == 1);
  }
  {
    list *l1 = init_list_array(a1, a1 + 1);
    list *l2 = init_list();
    l1->splice(l1, l1->end(l1), l2);
    assert(l1->size(l1) == 1);
    assert(l2->size(l2) == 0);
    struct list_node *i = l1->begin(l1);
    assert(i->data == 1);
  }
  {
    list *l1 = init_list_array(a1, a1 + 1);
    list *l2 = init_list_array(a2, a2 + 1);
    l1->splice(l1, l1->begin(l1), l2);
    assert(l1->size(l1) == 2);
    assert(l2->size(l2) == 0);
    struct list_node *i = l1->begin(l1);
    assert(i->data == 4);
    i = i->next;
    assert(i->data == 1);
  }
  {
    list *l1 = init_list_array(a1, a1 + 1);
    list *l2 = init_list_array(a2, a2 + 1);
    l1->splice(l1, l1->end(l1), l2);
    assert(l1->size(l1) == 2);
    assert(l2->size(l2) == 0);
    struct list_node *i = l1->begin(l1);
    assert(i->data == 1);
    i = i->next;
    assert(i->data == 4);
  }
  {
    list *l1 = init_list_array(a1, a1 + 1);
    list *l2 = init_list_array(a2, a2 + 2);
    l1->splice(l1, l1->begin(l1), l2);
    assert(l1->size(l1) == 3);
    assert(l2->size(l2) == 0);
    struct list_node *i = l1->begin(l1);
    assert(i->data == 4);
    i = i->next;
    assert(i->data == 5);
    i = i->next;
    assert(i->data == 1);
  }
  {
    list *l1 = init_list_array(a1, a1 + 1);
    list *l2 = init_list_array(a2, a2 + 2);
    l1->splice(l1, l1->end(l1), l2);
    assert(l1->size(l1) == 3);
    assert(l2->size(l2) == 0);
    struct list_node *i = l1->begin(l1);
    assert(i->data == 1);
    i = i->next;
    assert(i->data == 4);
    i = i->next;
    assert(i->data == 5);
  }
  {
    list *l1 = init_list_array(a1, a1 + 1);
    list *l2 = init_list_array(a2, a2 + 3);
    l1->splice(l1, l1->begin(l1), l2);
    assert(l1->size(l1) == 4);
    assert(l2->size(l2) == 0);
    struct list_node *i = l1->begin(l1);
    assert(i->data == 4);
    i = i->next;
    assert(i->data == 5);
    i = i->next;
    assert(i->data == 6);
    i = i->next;
    assert(i->data == 1);
  }
  {
    list *l1 = init_list_array(a1, a1 + 1);
    list *l2 = init_list_array(a2, a2 + 3);
    l1->splice(l1, l1->end(l1), l2);
    assert(l1->size(l1) == 4);
    assert(l2->size(l2) == 0);
    struct list_node *i = l1->begin(l1);
    assert(i->data == 1);
    i = i->next;
    assert(i->data == 4);
    i = i->next;
    assert(i->data == 5);
    i = i->next;
    assert(i->data == 6);
  }
  {
    list *l1 = init_list_array(a1, a1 + 2);
    list *l2 = init_list_array(a2, a2 + 1);
    l1->splice(l1, l1->begin(l1), l2);
    assert(l1->size(l1) == 3);
    assert(l2->size(l2) == 0);
    struct list_node *i = l1->begin(l1);
    assert(i->data == 4);
    i = i->next;
    assert(i->data == 1);
    i = i->next;
    assert(i->data == 2);
  }
  {
    list *l1 = init_list_array(a1, a1 + 2);
    list *l2 = init_list_array(a2, a2 + 1);
    l1->splice(l1, l1->begin(l1)->next, l2);
    assert(l1->size(l1) == 3);
    assert(l2->size(l2) == 0);
    struct list_node *i = l1->begin(l1);
    assert(i->data == 1);
    i = i->next;
    assert(i->data == 4);
    i = i->next;
    assert(i->data == 2);
  }
}

void test_list_splice_from() {
  int a1[] = {1, 2, 3};
  int a2[] = {4, 5, 6};
  {
    list *l1 = init_list();
    list *l2 = init_list_array(a2, a2 + 1);
    l1->splice_from(l1, l1->end(l1), l2, l2->begin(l2));
    assert(l1->size(l1) == 1);
    assert(l2->size(l2) == 0);
    struct list_node *i = l1->begin(l1);
    assert(i->data == 4);
  }
  {
    list *l1 = init_list();
    list *l2 = init_list_array(a2, a2 + 2);
    l1->splice_from(l1, l1->end(l1), l2, l2->begin(l2));
    assert(l1->size(l1) == 1);
    assert(l2->size(l2) == 1);
    struct list_node *i = l1->begin(l1);
    assert(i->data == 4);
    i = l2->begin(l2);
    assert(i->data == 5);
  }
  {
    list *l1 = init_list();
    list *l2 = init_list_array(a2, a2 + 2);
    l1->splice_from(l1, l1->end(l1), l2, l2->begin(l2)->next);
    assert(l1->size(l1) == 1);
    assert(l2->size(l2) == 1);
    struct list_node *i = l1->begin(l1);
    assert(i->data == 5);
    i = l2->begin(l2);
    assert(i->data == 4);
  }
  {
    list *l1 = init_list();
    list *l2 = init_list_array(a2, a2 + 3);
    l1->splice_from(l1, l1->end(l1), l2, l2->begin(l2));
    assert(l1->size(l1) == 1);
    assert(l2->size(l2) == 2);
    struct list_node *i = l1->begin(l1);
    assert(i->data == 4);
    i = l2->begin(l2);
    assert(i->data == 5);
    i = i->next;
    assert(i->data == 6);
  }
  {
    list *l1 = init_list();
    list *l2 = init_list_array(a2, a2 + 3);
    l1->splice_from(l1, l1->end(l1), l2, l2->begin(l2)->next);
    assert(l1->size(l1) == 1);
    assert(l2->size(l2) == 2);
    struct list_node *i = l1->begin(l1);
    assert(i->data == 5);
    i = l2->begin(l2);
    assert(i->data == 4);
    i = i->next;
    assert(i->data == 6);
  }
}

void test_list_splice_range() {
  int a1[] = {1, 2, 3};
  int a2[] = {4, 5, 6};
  {
    list *l1 = init_list_array(a1, a1 + 3);
    l1->splice_range(l1, l1->begin(l1), l1, l1->begin(l1)->next,
                     l1->begin(l1)->next);
    assert(l1->size(l1) == 3);
    struct list_node *i = l1->begin(l1);
    assert(i->data == 1);
    i = i->next;
    assert(i->data == 2);
    i = i->next;
    assert(i->data == 3);
  }
  {
    list *l1 = init_list_array(a1, a1 + 3);
    l1->splice_range(l1, l1->begin(l1), l1, l1->begin(l1)->next,
                     l1->begin(l1)->next->next);
    assert(l1->size(l1) == 3);
    struct list_node *i = l1->begin(l1);
    assert(i->data == 2);
    i = i->next;
    assert(i->data == 1);
    i = i->next;
    assert(i->data == 3);
  }
  {
    list *l1 = init_list_array(a1, a1 + 3);
    l1->splice_range(l1, l1->begin(l1), l1, l1->begin(l1)->next,
                     l1->begin(l1)->next->next->next);
    assert(l1->size(l1) == 3);
    struct list_node *i = l1->begin(l1);
    assert(i->data == 2);
    i = i->next;
    assert(i->data == 3);
    i = i->next;
    assert(i->data == 1);
  }
  {
    list *l1 = init_list_array(a1, a1 + 3);
    list *l2 = init_list_array(a2, a2 + 3);
    l1->splice_range(l1, l1->begin(l1), l2, l2->begin(l2)->next, l2->end(l2));
    assert(l1->size(l1) == 5);
    struct list_node *i = l1->begin(l1);
    assert(i->data == 5);
    i = i->next;
    assert(i->data == 6);
    i = i->next;
    assert(i->data == 1);
    i = i->next;
    assert(i->data == 2);
    i = i->next;
    assert(i->data == 3);
    assert(l2->size(l2) == 1);
    i = l2->begin(l2);
    assert(i->data == 4);
  }
  {
    list *l1 = init_list_array(a1, a1 + 3);
    list *l2 = init_list_array(a2, a2 + 3);
    l1->splice_range(l1, l1->begin(l1)->next, l2, l2->begin(l2)->next,
                     l2->end(l2));
    assert(l1->size(l1) == 5);
    struct list_node *i = l1->begin(l1);
    assert(i->data == 1);
    i = i->next;
    assert(i->data == 5);
    i = i->next;
    assert(i->data == 6);
    i = i->next;
    assert(i->data == 2);
    i = i->next;
    assert(i->data == 3);
    assert(l2->size(l2) == 1);
    i = l2->begin(l2);
    assert(i->data == 4);
  }
  {
    list *l1 = init_list_array(a1, a1 + 3);
    list *l2 = init_list_array(a2, a2 + 3);
    l1->splice_range(l1, l1->end(l1), l2, l2->begin(l2)->next, l2->end(l2));
    assert(l1->size(l1) == 5);
    struct list_node *i = l1->begin(l1);
    assert(i->data == 1);
    i = i->next;
    assert(i->data == 2);
    i = i->next;
    assert(i->data == 3);
    i = i->next;
    assert(i->data == 5);
    i = i->next;
    assert(i->data == 6);
    assert(l2->size(l2) == 1);
    i = l2->begin(l2);
    assert(i->data == 4);
  }
}

void test_list_unique() {
  int a1[] = {2, 1, 1, 4, 4, 4, 4, 3, 3};
  int a2[] = {2, 1, 4, 3};
  list *c = init_list_array(a1, a1 + 9);
  assert(c->unique(c) == 5);
}

void test_list_operations() {
  test_list_merge();
  test_list_merge_by();
  test_list_remove();
  test_list_remove_if();
  test_list_reverse();
  test_list_sort();
  test_list_sort_by();
  test_list_splice();
  test_list_splice_from();
  test_list_splice_range();
  test_list_unique();
}

int main() {
  test_list_capacity();
  test_list_modifiers();
  test_list_operations();
  return 0;
}
