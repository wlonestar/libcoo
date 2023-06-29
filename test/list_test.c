#include "list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

DECLARE_LIST(list, int)

void assert_list(list *l, int *first, int *last) {
  list_node *p = l->begin(l);
  for (int *i = first; i != last; i++) {
    assert(p->data == *i);
    p = p->next;
  }
}

void test_list_empty() {
  CREATE_LIST(list, c);
  assert(c->empty(c));
  c->push_back(c, 1);
  assert(!c->empty(c));
  c->clear(c);
  assert(c->empty(c));
  FREE_LIST(list, c);
}

void test_list_resize() {
  {
    CREATE_LIST_N(list, l, 10, 0);
    l->resize(l, 5);
    assert(l->size(l) == 5);
    FREE_LIST(list, l);
  }
  {
    CREATE_LIST_N(list, l, 10, 0);
    l->resize(l, 20);
    assert(l->size(l) == 20);
    FREE_LIST(list, l);
  }
  {
    CREATE_LIST_N(list, l, 5, 2);
    l->resize(l, 2);
    assert(l->size(l) == 2);
    FREE_LIST(list, l);
  }
  {
    CREATE_LIST_N(list, l, 5, 2);
    l->resize(l, 10);
    assert(l->size(l) == 10);
    assert(l->front(l) == 2);
    assert(l->back(l) == 0);
    FREE_LIST(list, l);
  }
}

void test_list_size() {
  CREATE_LIST(list, c);
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
  FREE_LIST(list, c);
}

void test_list_capacity() {
  test_list_empty();
  test_list_resize();
  test_list_size();
}

void test_list_clear() {
  int a[] = {1, 2, 3};
  CREATE_LIST_ARRAY(list, c, a, a + 3);
  c->clear(c);
  assert(c->empty(c));
  FREE_LIST(list, c);
}

void test_list_insert() {
  {
    CREATE_LIST_N(list, d, 10, 1);
    d->insert(d, d->begin(d)->next->next, 6);
    d->insert(d, d->begin(d)->next->next, 5);
    d->insert(d, d->begin(d)->next->next, 4);
    d->insert(d, d->begin(d)->next->next, 3);
    assert(d->size(d) == 14);
    list_node *i = d->begin(d);
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
    FREE_LIST(list, d);
  }
  {
    int a1[] = {1, 2, 3};
    CREATE_LIST(list, l);
    list_node *i = l->insert_range(l, l->begin(l), a1, a1 + 3);
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
    FREE_LIST(list, l);
  }
}

void test_list_pop_back() {
  int a[] = {1, 2, 3};
  CREATE_LIST_ARRAY(list, c, a, a + 3);
  c->pop_back(c);
  assert(c->front(c) == 1);
  assert(c->begin(c)->next->data == 2);
  c->pop_back(c);
  assert(c->front(c) == 1);
  c->pop_back(c);
  assert(c->empty(c));
  FREE_LIST(list, c);
}

void test_list_pop_front() {
  int a[] = {1, 2, 3};
  CREATE_LIST_ARRAY(list, c, a, a + 3);
  c->pop_back(c);
  assert(c->front(c) == 1);
  assert(c->begin(c)->next->data == 2);
  c->pop_back(c);
  assert(c->front(c) == 1);
  c->pop_back(c);
  assert(c->empty(c));
  FREE_LIST(list, c);
}

void test_list_push_back() {
  CREATE_LIST(list, c);
  for (int i = 0; i < 5; i++) {
    c->push_back(c, i);
  }
  int a[] = {0, 1, 2, 3, 4};
  assert_list(c, a, a + 5);
  FREE_LIST(list, c);
}

void test_list_push_front() {
  CREATE_LIST(list, c);
  for (int i = 0; i < 5; i++) {
    c->push_front(c, i);
  }
  int a[] = {4, 3, 2, 1, 0};
  assert_list(c, a, a + 5);
  FREE_LIST(list, c);
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
  CREATE_LIST_ARRAY(list, c1, a1, a1 + 5);
  CREATE_LIST_ARRAY(list, c2, a2, a2 + 7);
  c1->merge(c1, c2);
  assert_list(c1, a3, a3 + 12);
  assert(c2->empty(c2));
  FREE_LIST(list, c1);
  FREE_LIST(list, c2);
}

bool greater(int a, int b) { return a >= b; }

void test_list_merge_by() {
  int a1[] = {10, 9, 7, 3, 1};
  int a2[] = {11, 8, 6, 5, 4, 2, 0};
  int a3[] = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  CREATE_LIST_ARRAY(list, c1, a1, a1 + 5);
  CREATE_LIST_ARRAY(list, c2, a2, a2 + 7);
  c1->merge_by(c1, c2, greater);
  assert_list(c1, a3, a3 + 12);
  assert(c2->empty(c2));
  FREE_LIST(list, c1);
  FREE_LIST(list, c2);
}

void test_list_remove() {
  int a1[] = {1, 2, 3, 4};
  int a2[] = {1, 2, 4};
  CREATE_LIST_ARRAY(list, c, a1, a1 + 4);
  assert(c->remove(c, 3) == 1);
  c->remove(c, 3);
  assert_list(c, a2, a2 + 3);
  FREE_LIST(list, c);
}

bool pred(int n) { return n < 3; }

void test_list_remove_if() {
  int a1[] = {1, 2, 3, 4};
  int a2[] = {3, 4};
  CREATE_LIST_ARRAY(list, c, a1, a1 + 4);
  assert(c->remove_if(c, pred) == 2);
  c->remove_if(c, pred);
  assert_list(c, a2, a2 + 2);
  FREE_LIST(list, c);
}

void test_list_reverse() {
  int a1[] = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  int a2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  CREATE_LIST_ARRAY(list, c, a1, a1 + 12);
  c->reverse(c);
  assert_list(c, a2, a2 + 12);
  FREE_LIST(list, c);
}

void test_list_sort() {
  int a1[] = {4, 8, 1, 0, 5, 7, 2, 3, 6, 11, 10, 9};
  int a2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  CREATE_LIST_ARRAY(list, c, a1, a1 + 12);
  c->sort(c);
  assert_list(c, a2, a2 + 12);
  FREE_LIST(list, c);
}

void test_list_sort_by() {
  int a1[] = {4, 8, 1, 0, 5, 7, 2, 3, 6, 11, 10, 9};
  int a2[] = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  CREATE_LIST_ARRAY(list, c, a1, a1 + 12);
  c->sort_by(c, greater);
  assert_list(c, a2, a2 + 12);
  FREE_LIST(list, c);
}

void test_list_splice() {
  int a1[] = {1, 2, 3};
  int a2[] = {4, 5, 6};
  {
    CREATE_LIST(list, l1);
    CREATE_LIST(list, l2);
    l1->splice(l1, l1->end(l1), l2);
    assert(l1->size(l1) == 0);
    assert(l2->size(l2) == 0);
    FREE_LIST(list, l1);
    FREE_LIST(list, l2);
  }
  {
    CREATE_LIST(list, l1);
    CREATE_LIST_ARRAY(list, l2, a2, a2 + 1);
    l1->splice(l1, l1->end(l1), l2);
    assert(l1->size(l1) == 1);
    assert(l2->size(l2) == 0);
    list_node *i = l1->begin(l1);
    assert(i->data == 4);
    FREE_LIST(list, l1);
    FREE_LIST(list, l2);
  }
  {
    CREATE_LIST(list, l1);
    CREATE_LIST_ARRAY(list, l2, a2, a2 + 2);
    l1->splice(l1, l1->end(l1), l2);
    assert(l1->size(l1) == 2);
    assert(l2->size(l2) == 0);
    list_node *i = l1->begin(l1);
    assert(i->data == 4);
    i = i->next;
    assert(i->data == 5);
    FREE_LIST(list, l1);
    FREE_LIST(list, l2);
  }
  {
    CREATE_LIST(list, l1);
    CREATE_LIST_ARRAY(list, l2, a2, a2 + 3);
    l1->splice(l1, l1->end(l1), l2);
    assert(l1->size(l1) == 3);
    assert(l2->size(l2) == 0);
    list_node *i = l1->begin(l1);
    assert(i->data == 4);
    i = i->next;
    assert(i->data == 5);
    i = i->next;
    assert(i->data == 6);
    FREE_LIST(list, l1);
    FREE_LIST(list, l2);
  }
  {
    CREATE_LIST_ARRAY(list, l1, a1, a1 + 1);
    CREATE_LIST(list, l2);
    l1->splice(l1, l1->begin(l1), l2);
    assert(l1->size(l1) == 1);
    assert(l2->size(l2) == 0);
    list_node *i = l1->begin(l1);
    assert(i->data == 1);
    FREE_LIST(list, l1);
    FREE_LIST(list, l2);
  }
  {
    CREATE_LIST_ARRAY(list, l1, a1, a1 + 1);
    CREATE_LIST(list, l2);
    l1->splice(l1, l1->end(l1), l2);
    assert(l1->size(l1) == 1);
    assert(l2->size(l2) == 0);
    list_node *i = l1->begin(l1);
    assert(i->data == 1);
    FREE_LIST(list, l1);
    FREE_LIST(list, l2);
  }
  {
    CREATE_LIST_ARRAY(list, l1, a1, a1 + 1);
    CREATE_LIST_ARRAY(list, l2, a2, a2 + 1);
    l1->splice(l1, l1->begin(l1), l2);
    assert(l1->size(l1) == 2);
    assert(l2->size(l2) == 0);
    list_node *i = l1->begin(l1);
    assert(i->data == 4);
    i = i->next;
    assert(i->data == 1);
    FREE_LIST(list, l1);
    FREE_LIST(list, l2);
  }
  {
    CREATE_LIST_ARRAY(list, l1, a1, a1 + 1);
    CREATE_LIST_ARRAY(list, l2, a2, a2 + 1);
    l1->splice(l1, l1->end(l1), l2);
    assert(l1->size(l1) == 2);
    assert(l2->size(l2) == 0);
    list_node *i = l1->begin(l1);
    assert(i->data == 1);
    i = i->next;
    assert(i->data == 4);
    FREE_LIST(list, l1);
    FREE_LIST(list, l2);
  }
  {
    CREATE_LIST_ARRAY(list, l1, a1, a1 + 1);
    CREATE_LIST_ARRAY(list, l2, a2, a2 + 2);
    l1->splice(l1, l1->begin(l1), l2);
    assert(l1->size(l1) == 3);
    assert(l2->size(l2) == 0);
    list_node *i = l1->begin(l1);
    assert(i->data == 4);
    i = i->next;
    assert(i->data == 5);
    i = i->next;
    assert(i->data == 1);
    FREE_LIST(list, l1);
    FREE_LIST(list, l2);
  }
  {
    CREATE_LIST_ARRAY(list, l1, a1, a1 + 1);
    CREATE_LIST_ARRAY(list, l2, a2, a2 + 2);
    l1->splice(l1, l1->end(l1), l2);
    assert(l1->size(l1) == 3);
    assert(l2->size(l2) == 0);
    list_node *i = l1->begin(l1);
    assert(i->data == 1);
    i = i->next;
    assert(i->data == 4);
    i = i->next;
    assert(i->data == 5);
    FREE_LIST(list, l1);
    FREE_LIST(list, l2);
  }
  {
    CREATE_LIST_ARRAY(list, l1, a1, a1 + 1);
    CREATE_LIST_ARRAY(list, l2, a2, a2 + 3);
    l1->splice(l1, l1->begin(l1), l2);
    assert(l1->size(l1) == 4);
    assert(l2->size(l2) == 0);
    list_node *i = l1->begin(l1);
    assert(i->data == 4);
    i = i->next;
    assert(i->data == 5);
    i = i->next;
    assert(i->data == 6);
    i = i->next;
    assert(i->data == 1);
    FREE_LIST(list, l1);
    FREE_LIST(list, l2);
  }
  {
    CREATE_LIST_ARRAY(list, l1, a1, a1 + 1);
    CREATE_LIST_ARRAY(list, l2, a2, a2 + 3);
    l1->splice(l1, l1->end(l1), l2);
    assert(l1->size(l1) == 4);
    assert(l2->size(l2) == 0);
    list_node *i = l1->begin(l1);
    assert(i->data == 1);
    i = i->next;
    assert(i->data == 4);
    i = i->next;
    assert(i->data == 5);
    i = i->next;
    assert(i->data == 6);
    FREE_LIST(list, l1);
    FREE_LIST(list, l2);
  }
  {
    CREATE_LIST_ARRAY(list, l1, a1, a1 + 2);
    CREATE_LIST_ARRAY(list, l2, a2, a2 + 1);
    l1->splice(l1, l1->begin(l1), l2);
    assert(l1->size(l1) == 3);
    assert(l2->size(l2) == 0);
    list_node *i = l1->begin(l1);
    assert(i->data == 4);
    i = i->next;
    assert(i->data == 1);
    i = i->next;
    assert(i->data == 2);
    FREE_LIST(list, l1);
    FREE_LIST(list, l2);
  }
  {
    CREATE_LIST_ARRAY(list, l1, a1, a1 + 2);
    CREATE_LIST_ARRAY(list, l2, a2, a2 + 1);
    l1->splice(l1, l1->begin(l1)->next, l2);
    assert(l1->size(l1) == 3);
    assert(l2->size(l2) == 0);
    list_node *i = l1->begin(l1);
    assert(i->data == 1);
    i = i->next;
    assert(i->data == 4);
    i = i->next;
    assert(i->data == 2);
    FREE_LIST(list, l1);
    FREE_LIST(list, l2);
  }
}

void test_list_splice_from() {
  int a1[] = {1, 2, 3};
  int a2[] = {4, 5, 6};
  {
    CREATE_LIST(list, l1);
    CREATE_LIST_ARRAY(list, l2, a2, a2 + 1);
    l1->splice_from(l1, l1->end(l1), l2, l2->begin(l2));
    assert(l1->size(l1) == 1);
    assert(l2->size(l2) == 0);
    list_node *i = l1->begin(l1);
    assert(i->data == 4);
    FREE_LIST(list, l1);
    FREE_LIST(list, l2);
  }
  {
    CREATE_LIST(list, l1);
    CREATE_LIST_ARRAY(list, l2, a2, a2 + 2);
    l1->splice_from(l1, l1->end(l1), l2, l2->begin(l2));
    assert(l1->size(l1) == 1);
    assert(l2->size(l2) == 1);
    list_node *i = l1->begin(l1);
    assert(i->data == 4);
    i = l2->begin(l2);
    assert(i->data == 5);
    FREE_LIST(list, l1);
    FREE_LIST(list, l2);
  }
  {
    CREATE_LIST(list, l1);
    CREATE_LIST_ARRAY(list, l2, a2, a2 + 2);
    l1->splice_from(l1, l1->end(l1), l2, l2->begin(l2)->next);
    assert(l1->size(l1) == 1);
    assert(l2->size(l2) == 1);
    list_node *i = l1->begin(l1);
    assert(i->data == 5);
    i = l2->begin(l2);
    assert(i->data == 4);
    FREE_LIST(list, l1);
    FREE_LIST(list, l2);
  }
  {
    CREATE_LIST(list, l1);
    CREATE_LIST_ARRAY(list, l2, a2, a2 + 3);
    l1->splice_from(l1, l1->end(l1), l2, l2->begin(l2));
    assert(l1->size(l1) == 1);
    assert(l2->size(l2) == 2);
    list_node *i = l1->begin(l1);
    assert(i->data == 4);
    i = l2->begin(l2);
    assert(i->data == 5);
    i = i->next;
    assert(i->data == 6);
    FREE_LIST(list, l1);
    FREE_LIST(list, l2);
  }
  {
    CREATE_LIST(list, l1);
    CREATE_LIST_ARRAY(list, l2, a2, a2 + 3);
    l1->splice_from(l1, l1->end(l1), l2, l2->begin(l2)->next);
    assert(l1->size(l1) == 1);
    assert(l2->size(l2) == 2);
    list_node *i = l1->begin(l1);
    assert(i->data == 5);
    i = l2->begin(l2);
    assert(i->data == 4);
    i = i->next;
    assert(i->data == 6);
    FREE_LIST(list, l1);
    FREE_LIST(list, l2);
  }
  {
    CREATE_LIST_ARRAY(list, l1, a1, a1 + 1);
    l1->splice_from(l1, l1->begin(l1), l1, l1->begin(l1));
    assert(l1->size(l1) == 1);
    list_node *i = l1->begin(l1);
    assert(i->data == 1);
    FREE_LIST(list, l1);
  }
  {
    CREATE_LIST_ARRAY(list, l1, a1, a1 + 1);
    CREATE_LIST_ARRAY(list, l2, a2, a2 + 1);
    l1->splice_from(l1, l1->begin(l1), l2, l2->begin(l2));
    assert(l1->size(l1) == 2);
    assert(l2->size(l2) == 0);
    list_node *i = l1->begin(l1);
    assert(i->data == 4);
    i = i->next;
    assert(i->data == 1);
    FREE_LIST(list, l1);
    FREE_LIST(list, l2);
  }
  {
    CREATE_LIST_ARRAY(list, l1, a1, a1 + 1);
    CREATE_LIST_ARRAY(list, l2, a2, a2 + 1);
    l1->splice_from(l1, l1->begin(l1)->next, l2, l2->begin(l2));
    assert(l1->size(l1) == 2);
    assert(l2->size(l2) == 0);
    list_node *i = l1->begin(l1);
    assert(i->data == 1);
    i = i->next;
    assert(i->data == 4);
    FREE_LIST(list, l1);
    FREE_LIST(list, l2);
  }
  {
    CREATE_LIST_ARRAY(list, l1, a1, a1 + 2);
    l1->splice_from(l1, l1->begin(l1), l1, l1->begin(l1));
    assert(l1->size(l1) == 2);
    list_node *i = l1->begin(l1);
    assert(i->data == 1);
    i = i->next;
    assert(i->data == 2);
    FREE_LIST(list, l1);
  }
  {
    CREATE_LIST_ARRAY(list, l1, a1, a1 + 2);
    l1->splice_from(l1, l1->begin(l1), l1, l1->begin(l1)->next);
    assert(l1->size(l1) == 2);
    list_node *i = l1->begin(l1);
    assert(i->data == 2);
    i = i->next;
    assert(i->data == 1);
    FREE_LIST(list, l1);
  }
  {
    CREATE_LIST_ARRAY(list, l1, a1, a1 + 2);
    l1->splice_from(l1, l1->begin(l1)->next, l1, l1->begin(l1));
    assert(l1->size(l1) == 2);
    list_node *i = l1->begin(l1);
    assert(i->data == 1);
    i = i->next;
    assert(i->data == 2);
    FREE_LIST(list, l1);
  }
  {
    CREATE_LIST_ARRAY(list, l1, a1, a1 + 2);
    l1->splice_from(l1, l1->begin(l1)->next, l1, l1->begin(l1)->next);
    assert(l1->size(l1) == 2);
    list_node *i = l1->begin(l1);
    assert(i->data == 1);
    i = i->next;
    assert(i->data == 2);
    FREE_LIST(list, l1);
  }
}

void test_list_splice_range() {
  int a1[] = {1, 2, 3};
  int a2[] = {4, 5, 6};
  {
    CREATE_LIST_ARRAY(list, l1, a1, a1 + 3);
    l1->splice_range(l1, l1->begin(l1), l1, l1->begin(l1)->next,
                     l1->begin(l1)->next);
    assert(l1->size(l1) == 3);
    list_node *i = l1->begin(l1);
    assert(i->data == 1);
    i = i->next;
    assert(i->data == 2);
    i = i->next;
    assert(i->data == 3);
    FREE_LIST(list, l1);
  }
  {
    CREATE_LIST_ARRAY(list, l1, a1, a1 + 3);
    l1->splice_range(l1, l1->begin(l1), l1, l1->begin(l1)->next,
                     l1->begin(l1)->next->next);
    assert(l1->size(l1) == 3);
    list_node *i = l1->begin(l1);
    assert(i->data == 2);
    i = i->next;
    assert(i->data == 1);
    i = i->next;
    assert(i->data == 3);
    FREE_LIST(list, l1);
  }
  {
    CREATE_LIST_ARRAY(list, l1, a1, a1 + 3);
    l1->splice_range(l1, l1->begin(l1), l1, l1->begin(l1)->next,
                     l1->begin(l1)->next->next->next);
    assert(l1->size(l1) == 3);
    list_node *i = l1->begin(l1);
    assert(i->data == 2);
    i = i->next;
    assert(i->data == 3);
    i = i->next;
    assert(i->data == 1);
    FREE_LIST(list, l1);
  }
  {
    CREATE_LIST_ARRAY(list, l1, a1, a1 + 3);
    CREATE_LIST_ARRAY(list, l2, a2, a2 + 3);
    l1->splice_range(l1, l1->begin(l1), l2, l2->begin(l2)->next, l2->end(l2));
    assert(l1->size(l1) == 5);
    list_node *i = l1->begin(l1);
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
    FREE_LIST(list, l1);
    FREE_LIST(list, l2);
  }
  {
    CREATE_LIST_ARRAY(list, l1, a1, a1 + 3);
    CREATE_LIST_ARRAY(list, l2, a2, a2 + 3);
    l1->splice_range(l1, l1->begin(l1)->next, l2, l2->begin(l2)->next,
                     l2->end(l2));
    assert(l1->size(l1) == 5);
    list_node *i = l1->begin(l1);
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
    FREE_LIST(list, l1);
    FREE_LIST(list, l2);
  }
  {
    CREATE_LIST_ARRAY(list, l1, a1, a1 + 3);
    CREATE_LIST_ARRAY(list, l2, a2, a2 + 3);
    l1->splice_range(l1, l1->end(l1), l2, l2->begin(l2)->next, l2->end(l2));
    assert(l1->size(l1) == 5);
    list_node *i = l1->begin(l1);
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
    FREE_LIST(list, l1);
    FREE_LIST(list, l2);
  }
}

void test_list_unique() {
  int a1[] = {2, 1, 1, 4, 4, 4, 4, 3, 3};
  int a2[] = {2, 1, 4, 3};
  CREATE_LIST_ARRAY(list, c, a1, a1 + 9);
  assert(c->unique(c) == 5);
  assert_list(c, a2, a2 + 4);
  FREE_LIST(list, c);
}

bool equal(int a, int b) { return a == b; }

void test_list_unique_by() {
  int a1[] = {2, 1, 1, 4, 4, 4, 4, 3, 3};
  int a2[] = {2, 1, 4, 3};
  CREATE_LIST_ARRAY(list, c, a1, a1 + 9);
  assert(c->unique_by(c, equal) == 5);
  assert_list(c, a2, a2 + 4);
  FREE_LIST(list, c);
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
  test_list_unique_by();
}

void test_list_swap() {
  {
    int a1[] = {1, 3, 7, 9, 10};
    int a2[] = {0, 2, 4, 5, 6, 8, 11};
    CREATE_LIST_ARRAY(list, c1, a1, a1 + 5);
    CREATE_LIST_ARRAY(list, c2, a2, a2 + 7);
    list_node *it1 = c1->begin(c1);
    list_node *it2 = c2->begin(c2);
    c1->swap(c1, c2);
    assert_list(c1, a2, a2 + 7);
    assert_list(c2, a1, a1 + 5);
    assert(it1 == c2->begin(c2)); // Iterators remain valid
    assert(it2 == c1->begin(c1)); // Iterators remain valid
    FREE_LIST(list, c1);
    FREE_LIST(list, c2);
  }
  {
    int a2[] = {0, 2, 4, 5, 6, 8, 11};
    CREATE_LIST(list, c1);
    CREATE_LIST_ARRAY(list, c2, a2, a2 + 7);
    c1->swap(c1, c2);
    assert_list(c1, a2, a2 + 7);
    assert(c2->empty(c2));
    FREE_LIST(list, c1);
    FREE_LIST(list, c2);
  }
  {
    int a1[] = {1, 3, 7, 9, 10};
    CREATE_LIST_ARRAY(list, c1, a1, a1 + 5);
    CREATE_LIST(list, c2);
    c1->swap(c1, c2);
    assert(c1->empty(c1));
    assert_list(c2, a1, a1 + 5);
    FREE_LIST(list, c1);
    FREE_LIST(list, c2);
  }
  {
    CREATE_LIST(list, c1);
    CREATE_LIST(list, c2);
    c1->swap(c1, c2);
    assert(c1->empty(c1));
    assert(c2->empty(c2));
    FREE_LIST(list, c1);
    FREE_LIST(list, c2);
  }
}

void test_list_special() { test_list_swap(); }

int main() {
  test_list_capacity();
  test_list_modifiers();
  test_list_operations();
  test_list_special();
  return 0;
}
