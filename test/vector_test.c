#include "vector.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

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

}

void test_vector_modifiers() { 
  test_vector_clear();
  test_vector_erase();
}

int main() {
  test_vector_capacity();
  test_vector_data();
  test_vector_modifiers();
  return 0;
}
