#include "vector.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

DECLARE_VECTOR(vector, int)

void assert_vector(vector *v, int *first, int *last) {
  int *p = v->begin(v);
  for (int *i = first; i != last; i++) {
    assert(*p == *i);
    p++;
  }
}

void test_vector_cap() {
  {
    CREATE_VECTOR(vector, v);
    assert(v->capacity(v) == 0);
    FREE_VECTOR(vector, v);
  }
  {
    CREATE_VECTOR_N(vector, v, 100, 0);
    assert(v->capacity(v) == 100);
    v->push_back(v, 0);
    assert(v->capacity(v) > 101);
    FREE_VECTOR(vector, v);
  }
}

void test_vector_empty() {
  CREATE_VECTOR(vector, c);
  assert(c->empty(c));
  c->push_back(c, 1);
  assert(!c->empty(c));
  c->clear(c);
  assert(c->empty(c));
  FREE_VECTOR(vector, c);
}

void test_vector_reserve() {
  {
    CREATE_VECTOR(vector, v)
    v->reserve(v, 10);
    assert(v->capacity(v) >= 10);
    FREE_VECTOR(vector, v)
  }
  {
    CREATE_VECTOR_N(vector, v, 100, 0);
    assert(v->capacity(v) == 100);
    v->reserve(v, 50);
    assert(v->size(v) == 100);
    assert(v->capacity(v) == 100);
    v->reserve(v, 150);
    assert(v->size(v) == 100);
    assert(v->capacity(v) == 150);
    FREE_VECTOR(vector, v)
  }
}

void test_vector_resize() {
  {
    CREATE_VECTOR_N(vector, v, 100, 0);
    v->resize(v, 50, 0);
    assert(v->size(v) == 50);
    assert(v->capacity(v) == 100);
    v->resize(v, 200, 0);
    assert(v->size(v) == 200);
    assert(v->capacity(v) >= 200);
    FREE_VECTOR(vector, v)
  }
  {
    CREATE_VECTOR_N(vector, v, 100, 0);
    v->resize(v, 50, 1);
    assert(v->size(v) == 50);
    assert(v->capacity(v) == 100);
    v->resize(v, 200, 1);
    assert(v->size(v) == 200);
    assert(v->capacity(v) >= 200);
    FREE_VECTOR(vector, v)
  }
}

void test_vector_shrink_to_fit() {
  CREATE_VECTOR_N(vector, v, 100, 0);
  v->push_back(v, 1);
  v->shrink_to_fit(v);
  assert(v->capacity(v) >= 101);
  assert(v->size(v) == 101);
  FREE_VECTOR(vector, v)
}

void test_vector_size() {
  CREATE_VECTOR(vector, v)
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
  FREE_VECTOR(vector, v)
}

void test_vector_swap() {
  CREATE_VECTOR_N(vector, v1, 100, 0);
  CREATE_VECTOR_N(vector, v2, 200, 0);
  v1->swap(v1, v2);
  assert(v1->size(v1) == 200);
  assert(v1->capacity(v1) == 200);
  assert(v2->size(v2) == 100);
  assert(v2->capacity(v2) == 100);
  FREE_VECTOR(vector, v1);
  FREE_VECTOR(vector, v2);
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
  CREATE_VECTOR_N(vector, v, 100, 0);
  assert(*v->data(v) == v->front(v));
  FREE_VECTOR(vector, v)
}

void test_vector_clear() {
  int a[] = {1, 2, 3};
  CREATE_VECTOR_ARRAY(vector, v, a, a + 3);
  v->clear(v);
  assert(v->empty(v));
  FREE_VECTOR(vector, v)
}

void test_vector_erase() {
  {
    int a[] = {1, 2, 3, 4, 5};
    CREATE_VECTOR_ARRAY(vector, v, a, a + 5);
    v->erase(v, v->begin(v));
    assert_vector(v, a + 1, a + 5);
    FREE_VECTOR(vector, v)
  }
  {
    int a[] = {1, 2, 3, 4, 5};
    int e[] = {1, 3, 4, 5};
    CREATE_VECTOR_ARRAY(vector, v, a, a + 5);
    v->erase(v, v->begin(v) + 1);
    assert_vector(v, e, e + 4);
    FREE_VECTOR(vector, v)
  }
  {
    int a[] = {1, 2, 3};
    CREATE_VECTOR_ARRAY(vector, v, a, a + 3);
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
    FREE_VECTOR(vector, v)
  }
}

void test_vector_erase_range() {
  int a[] = {1, 2, 3};
  {
    CREATE_VECTOR_ARRAY(vector, v, a, a + 3);
    int *i = v->erase_range(v, v->begin(v), v->begin(v));
    assert(v->size(v) == 3);
    assert(i == v->begin(v));
    FREE_VECTOR(vector, v)
  }
  {
    CREATE_VECTOR_ARRAY(vector, v, a, a + 3);
    int *i = v->erase_range(v, v->begin(v), v->begin(v) + 1);
    assert(v->size(v) == 2);
    assert(i == v->begin(v));
    assert_vector(v, a + 1, a + 3);
    FREE_VECTOR(vector, v)
  }
  {
    CREATE_VECTOR_ARRAY(vector, v, a, a + 3);
    int *i = v->erase_range(v, v->begin(v), v->begin(v) + 2);
    assert(v->size(v) == 1);
    assert(i == v->begin(v));
    assert_vector(v, a + 2, a + 3);
    FREE_VECTOR(vector, v)
  }
  {
    CREATE_VECTOR_ARRAY(vector, v, a, a + 3);
    int *i = v->erase_range(v, v->begin(v), v->begin(v) + 3);
    assert(v->size(v) == 0);
    assert(i == v->begin(v));
    FREE_VECTOR(vector, v)
  }
}

void test_vector_insert() {
  {
    CREATE_VECTOR_N(vector, v, 100, 0);
    int val = 1;
    int *i = v->insert(v, v->begin(v) + 10, val);
    assert(v->size(v) == 101);
    assert(i = v->begin(v) + 10);
    int j;
    for (j = 0; j < 10; j++) {
      assert(v->at(v, j) == 0);
    }
    assert(v->at(v, j++) == 1);
    for (; j < 101; j++) {
      assert(v->at(v, j) == 0);
    }
    FREE_VECTOR(vector, v)
  }
  {
    size_t n = 100;
    CREATE_VECTOR_N(vector, v, n, 0);
    v->reserve(v, n + 1);
    int val = 1;
    int *i = v->insert(v, v->begin(v) + n, val);
    assert(v->size(v) == n + 1);
    assert(i = v->begin(v) + n);
    for (size_t i = 0; i < n; i++) {
      assert(v->at(v, i) == 0);
    }
    assert(v->at(v, n) == val);
    FREE_VECTOR(vector, v)
  }
}

void test_vector_insert_n() {
  {
    CREATE_VECTOR_N(vector, v, 100, 0);
    int *i = v->insert_n(v, v->begin(v) + 10, 5, 1);
    assert(v->size(v) == 105);
    assert(i == v->begin(v) + 10);
    int j;
    for (j = 0; j < 10; j++) {
      assert(v->at(v, j) == 0);
    }
    for (; j < 15; j++) {
      assert(v->at(v, j) == 1);
    }
    for (++j; j < 105; j++) {
      assert(v->at(v, j) == 0);
    }
  }
  {
    CREATE_VECTOR_N(vector, v, 100, 0);
    v->reserve(v, 128);
    size_t sz = v->size(v);
    int *i = v->insert_n(v, v->begin(v) + 10, 5, 1);
    assert(v->size(v) == sz + 5);
    assert(i == v->begin(v) + 10);
    int j;
    for (j = 0; j < 10; j++) {
      assert(v->at(v, j) == 0);
    }
    for (; j < 15; j++) {
      assert(v->at(v, j) == 1);
    }
    for (++j; j < v->size(v); j++) {
      assert(v->at(v, j) == 0);
    }
  }
}

void test_vector_insert_range() {
  {
    CREATE_VECTOR_N(vector, v, 100, 0);
    int a[] = {1, 2, 3, 4, 5};
    int N = 5;
    int *i = v->insert_range(v, v->begin(v) + 10, a, a + N);
    assert(v->size(v) == 100 + N);
    assert(i == v->begin(v) + 10);
    int j;
    for (j = 0; j < 10; j++) {
      assert(v->at(v, j) == 0);
    }
    for (int k = 0; k < N; ++j, ++k) {
      assert(v->at(v, j) == a[k]);
    }
    for (; j < 105; j++) {
      assert(v->at(v, j) == 0);
    }
    FREE_VECTOR(vector, v)
  }
  {
    CREATE_VECTOR_N(vector, v, 100, 0);
    while (v->size(v) < v->capacity(v)) {
      v->push_back(v, 0);
    }
    size_t sz = v->size(v);
    int a[] = {1, 2, 3, 4, 5};
    int N = 5;
    int *i = v->insert_range(v, v->begin(v) + 10, a, a + N);
    assert(v->size(v) == sz + N);
    assert(i == v->begin(v) + 10);
    int j;
    for (j = 0; j < 10; j++) {
      assert(v->at(v, j) == 0);
    }
    for (int k = 0; k < N; ++j, ++k) {
      assert(v->at(v, j) == a[k]);
    }
    for (; j < v->size(v); j++) {
      assert(v->at(v, j) == 0);
    }
    FREE_VECTOR(vector, v)
  }
  {
    CREATE_VECTOR_N(vector, v, 100, 0);
    v->reserve(v, 128);
    size_t sz = v->size(v);
    int a[] = {1, 2, 3, 4, 5};
    int N = 5;
    int *i = v->insert_range(v, v->begin(v) + 10, a, a + N);
    assert(v->size(v) == sz + N);
    assert(i == v->begin(v) + 10);
    int j;
    for (j = 0; j < 10; j++) {
      assert(v->at(v, j) == 0);
    }
    for (int k = 0; k < N; ++j, ++k) {
      assert(v->at(v, j) == a[k]);
    }
    for (; j < v->size(v); j++) {
      assert(v->at(v, j) == 0);
    }
    FREE_VECTOR(vector, v)
  }
}

void test_vector_modifiers() {
  test_vector_clear();
  test_vector_erase();
  test_vector_erase_range();
  test_vector_insert();
  test_vector_insert_n();
  test_vector_insert_range();
}

int main() {
  test_vector_capacity();
  test_vector_data();
  test_vector_modifiers();
  return 0;
}
