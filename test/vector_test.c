#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void test_vector_cap() {
  {
    vector *v = init_vector();
    assert(v->capacity(v) == 0);  
  }
  {
    vector *v = init_vector_n(100, 0);
    assert(v->capacity(v) == 100);
    v->push_back(v, 0);
    assert(v->capacity(v) > 101);
  }
}

void test_vector_empty() {
  vector *c = init_vector();
  assert(c->empty(c));
  c->push_back(c, 1);
  assert(!c->empty(c));
  c->clear(c);
  assert(c->empty(c));
}

void test_vector_reserve() {
  {
    vector *v;
    v->reserve(v, 10);
    assert(v->capacity(v) >= 10);
  }
}

void test_vector_capacity() {
  test_vector_cap();
  test_vector_empty();
  test_vector_reserve();
}

int main() {
  test_vector_capacity();
  return 0;
}
