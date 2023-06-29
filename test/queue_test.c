#include "queue.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

DECLARE_QUEUE(queue, int)

void test_queue_ctor() {
  {
    int a[] = {0, 1, 2, 3, 4};
    CREATE_QUEUE_ARRAY(queue, q, a, a + 5);
    assert(q->size(q) == 5);
    for (size_t i = 0; i < q->size(q); ++i) {
      assert(q->front(q) == a[i]);
      q->pop(q);
    }
    FREE_QUEUE(queue, q);
  }
  {
    CREATE_QUEUE(queue, q);
    assert(q->size(q) == 0);
    q->push(q, 1);
    q->push(q, 2);
    assert(q->size(q) == 2);
    assert(q->front(q) == 1);
    assert(q->back(q) == 2);
    FREE_QUEUE(queue, q);
  }
  {
    int a[] = {4, 3, 2, 1};
    CREATE_QUEUE_ARRAY(queue, q, a, a + 4)
    assert(q->front(q) == 4);
    q->pop(q);
    assert(q->front(q) == 3);
    q->pop(q);
    assert(q->front(q) == 2);
    q->pop(q);
    assert(q->front(q) == 1);
    q->pop(q);
    assert(q->empty(q));
    FREE_QUEUE(queue, q);
  }
}

void test_queue_cons() { test_queue_ctor(); }

void test_queue_front() {
  CREATE_QUEUE(queue, q);
  assert(q->size(q) == 0);
  q->push(q, 1);
  q->push(q, 2);
  q->push(q, 3);
  int val = q->front(q);
  assert(val == 1);
  FREE_QUEUE(queue, q);
}

void test_queue_back() {
  CREATE_QUEUE(queue, q);
  assert(q->size(q) == 0);
  q->push(q, 1);
  q->push(q, 2);
  q->push(q, 3);
  int val = q->back(q);
  assert(val == 3);
  FREE_QUEUE(queue, q);
}

void test_queue_empty() {
  CREATE_QUEUE(queue, q);
  assert(q->empty(q));
  q->push(q, 1);
  assert(!q->empty(q));
  q->pop(q);
  assert(q->empty(q));
  FREE_QUEUE(queue, q);
}

void test_queue_size() {
  CREATE_QUEUE(queue, q);
  assert(q->size(q) == 0);
  q->push(q, 1);
  assert(q->size(q) == 1);
  FREE_QUEUE(queue, q);
}

void test_queue_push() {
  CREATE_QUEUE(queue, q);
  q->push(q, 1);
  assert(q->size(q) == 1);
  assert(q->front(q) == 1);
  assert(q->back(q) == 1);
  q->push(q, 2);
  assert(q->size(q) == 2);
  assert(q->front(q) == 1);
  assert(q->back(q) == 2);
  q->push(q, 3);
  assert(q->size(q) == 3);
  assert(q->front(q) == 1);
  assert(q->back(q) == 3);
  FREE_QUEUE(queue, q);
}

void test_queue_pop() {
  CREATE_QUEUE(queue, q);
  assert(q->size(q) == 0);
  q->push(q, 1);
  q->push(q, 2);
  q->push(q, 3);
  assert(q->size(q) == 3);
  assert(q->front(q) == 1);
  assert(q->back(q) == 3);
  q->pop(q);
  assert(q->size(q) == 2);
  assert(q->front(q) == 2);
  assert(q->back(q) == 3);
  q->pop(q);
  assert(q->size(q) == 1);
  assert(q->front(q) == 3);
  assert(q->back(q) == 3);
  q->pop(q);
  assert(q->size(q) == 0);
  FREE_QUEUE(queue, q);
}

void test_queue_swap() {
  int a1[] = {0, 1, 2, 3, 4};
  int a2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  CREATE_QUEUE_ARRAY(queue, q1, a1, a1 + 5);
  CREATE_QUEUE_ARRAY(queue, q2, a2, a2 + 10);
  q1->swap(q1, q2);
  assert(q1->back(q1) == 9);
  assert(q2->back(q2) == 4);
  FREE_QUEUE(queue, q1);
  FREE_QUEUE(queue, q2);
}

void test_queue_defn() {
  test_queue_front();
  test_queue_back();
  test_queue_empty();
  test_queue_size();
  test_queue_push();
  test_queue_pop();
  test_queue_swap();
}

int main() {
  test_queue_cons();
  test_queue_defn();
  return 0;
}
