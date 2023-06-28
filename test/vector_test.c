#include "vector.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void assert_vector(vector *v, int *first, int *last) {
  int *p = v->begin(v);
  for (int *i = first; i != last; i++) {
    assert(*p == *i);
    p++;
  }
}

void test_vector_cap() {
  {
    vector *v = init_vector();
    assert(v->capacity(v) == 0);
    free_vector(v);
  }
  {
    vector *v = init_vector_n(100, 0);
    assert(v->capacity(v) == 100);
    v->push_back(v, 0);
    assert(v->capacity(v) > 101);
    free_vector(v);
  }
}

void test_vector_empty() {
  vector *c = init_vector();
  assert(c->empty(c));
  c->push_back(c, 1);
  assert(!c->empty(c));
  c->clear(c);
  assert(c->empty(c));
  free_vector(c);
}

void test_vector_reserve() {
  {
    vector *v = init_vector();
    v->reserve(v, 10);
    assert(v->capacity(v) >= 10);
    free_vector(v);
  }
  {
    vector *v = init_vector_n(100, 0);
    assert(v->capacity(v) == 100);
    v->reserve(v, 50);
    assert(v->size(v) == 100);
    assert(v->capacity(v) == 100);
    v->reserve(v, 150);
    assert(v->size(v) == 100);
    assert(v->capacity(v) == 150);
    free_vector(v);
  }
}

void test_vector_resize() {
  {
    vector *v = init_vector_n(100, 0);
    v->resize(v, 50, 0);
    assert(v->size(v) == 50);
    assert(v->capacity(v) == 100);
    v->resize(v, 200, 0);
    assert(v->size(v) == 200);
    assert(v->capacity(v) >= 200);
    free_vector(v);
  }
  {
    vector *v = init_vector_n(100, 0);
    v->resize(v, 50, 1);
    assert(v->size(v) == 50);
    assert(v->capacity(v) == 100);
    v->resize(v, 200, 1);
    assert(v->size(v) == 200);
    assert(v->capacity(v) >= 200);
    free_vector(v);
  }
}

void test_vector_shrink_to_fit() {
  vector *v = init_vector_n(100, 0);
  v->push_back(v, 1);
  v->shrink_to_fit(v);
  assert(v->capacity(v) >= 101);
  assert(v->size(v) == 101);
  free_vector(v);
}

void test_vector_size() {
  vector *v = init_vector();
  assert(v->size(v) == 0);
  v->push_back(v, 2);
  assert(v->size(v) == 1);
  v->push_back(v, 1);
  assert(v->size(v) == 2);
  v->push_back(v, 3);
  assert(v->size(v) == 3);
  v->erase(v, v->begin(v));
  assert(v->size(v) == 2);
  v->erase(v, v->begin(v));
  assert(v->size(v) == 1);
  v->erase(v, v->begin(v));
  assert(v->size(v) == 0);
  free_vector(v);
}

void test_vector_swap() {
  vector *v1 = init_vector_n(100, 0);
  vector *v2 = init_vector_n(200, 0);
  v1->swap(v1, v2);
  assert(v1->size(v1) == 200);
  assert(v1->capacity(v1) == 200);
  assert(v2->size(v2) == 100);
  assert(v2->capacity(v2) == 100);
  free_vector(v1);
  free_vector(v2);
}

void test_vector_capacity() {
  test_vector_cap();
  test_vector_empty();
  test_vector_reserve();
  test_vector_resize();
  test_vector_shrink_to_fit();
  test_vector_size();
  test_vector_swap();
}

void test_vector_data() {
  vector *v = init_vector_n(100, 0);
  assert(*v->data(v) == v->front(v));
  free_vector(v);
}

void test_vector_clear() {
  int a[] = {1, 2, 3};
  vector *v = init_vector_array(a, a + 3);
  v->clear(v);
  assert(v->empty(v));
  free_vector(v);
}

void test_vector_erase() {
  {
    int a[] = {1, 2, 3, 4, 5};
    vector *v = init_vector_array(a, a + 5);
    v->erase(v, v->begin(v));
    assert_vector(v, a + 1, a + 5);
    free_vector(v);
  }
  {
    int a[] = {1, 2, 3, 4, 5};
    int e[] = {1, 3, 4, 5};
    vector *v = init_vector_array(a, a + 5);
    v->erase(v, v->begin(v) + 1);
    assert_vector(v, e, e + 4);
    free_vector(v);
  }
  {
    int a[] = {1, 2, 3};
    vector *v = init_vector_array(a, a + 3);
    int *i = v->begin(v);
    i++;
    int *j = v->erase(v, i);
    assert(v->size(v) == 2);
    assert(*j == 3);
    assert(*(v->begin(v)) == 1);
    assert(*(v->begin(v) + 1) == 3);
    j = v->erase(v, j);
    assert(j == v->end(v));
    assert(v->size(v) == 1);
    assert(*(v->begin(v)) == 1);
    j = v->erase(v, v->begin(v));
    assert(j == v->end(v));
    free_vector(v);
  }
}

void test_vector_erase_range() {
  int a[] = {1, 2, 3};
  {
    vector *v = init_vector_array(a, a + 3);
    int *i = v->erase_range(v, v->begin(v), v->begin(v));
    assert(v->size(v) == 3);
    assert(i == v->begin(v));
    free_vector(v);
  }
  {
    vector *v = init_vector_array(a, a + 3);
    int *i = v->erase_range(v, v->begin(v), v->begin(v) + 1);
    assert(v->size(v) == 2);
    assert(i == v->begin(v));
    assert_vector(v, a + 1, a + 3);
    free_vector(v);
  }
  {
    vector *v = init_vector_array(a, a + 3);
    int *i = v->erase_range(v, v->begin(v), v->begin(v) + 2);
    assert(v->size(v) == 1);
    assert(i == v->begin(v));
    assert_vector(v, a + 2, a + 3);
    free_vector(v);
  }
  {
    vector *v = init_vector_array(a, a + 3);
    int *i = v->erase_range(v, v->begin(v), v->begin(v) + 3);
    assert(v->size(v) == 0);
    assert(i == v->begin(v));
    free_vector(v);
  }
}

void test_vector_insert() {
  {
    vector *v = init_vector_n(100, 0);
    int val = 1;
    int *i = v->insert(v, v->begin(v) + 10, val);
    assert(v->size(v) == 101);
    assert(i = v->begin(v) + 10);
    int j;
    for ( j = 0; j < 10; j++) {
      assert(v->at(v, j) == 0);
    }
    assert(v->at(v, j++) == 1);
    for (; j < 101; j ++) {
      assert(v->at(v, j) == 0);
    }
    free_vector(v);
  }
}

void test_vector_modifiers() {
  test_vector_clear();
  test_vector_erase();
  test_vector_erase_range();
  test_vector_insert();
}

int main() {
  test_vector_capacity();
  test_vector_data();
  test_vector_modifiers();
  return 0;
}
