#include "priority_queue.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

DECLARE_PRIORITY_QUEUE(pq, int)

void test_queue_ctor() {
  {
    CREATE_PRIORITY_QUEUE(pq, q);
    assert(q->size(q) == 0);
    q->push(q, 1);
    q->push(q, 2);
    assert(q->size(q) == 2);
    assert(q->top(q) == 2);
    FREE_PRIORITY_QUEUE(pq, q);
  }
  {
    int a[] = {0, 1, 2, 3, 4};
    CREATE_PRIORITY_QUEUE_ARRAY(pq, q, a, a + 5);
    assert(q->size(q) == 5);
    assert(q->top(q) == 4);
    FREE_PRIORITY_QUEUE(pq, q);
  }
  {
    int a[] = {3, 5, 2, 0, 6, 8, 1};
    CREATE_PRIORITY_QUEUE_ARRAY(pq, q, a, a + 7)
    assert(q->size(q) == 7);
    assert(q->top(q) == 8);
    FREE_PRIORITY_QUEUE(pq, q);
  }
}

void test_queue_cons() { test_queue_ctor(); }

void test_queue_top() {
  CREATE_PRIORITY_QUEUE(pq, q);
  q->push(q, 1);
  assert(q->top(q) == 1);
  q->push(q, 3);
  assert(q->top(q) == 3);
  q->push(q, 2);
  assert(q->top(q) == 3);
  FREE_PRIORITY_QUEUE(pq, q);
}

void test_queue_empty() {
  CREATE_PRIORITY_QUEUE(pq, q);
  assert(q->empty(q));
  q->push(q, 1);
  assert(!q->empty(q));
  q->pop(q);
  assert(q->empty(q));
  FREE_PRIORITY_QUEUE(pq, q);
}

void test_queue_size() {
  CREATE_PRIORITY_QUEUE(pq, q);
  assert(q->size(q) == 0);
  q->push(q, 1);
  assert(q->size(q) == 1);
  q->pop(q);
  assert(q->size(q) == 0);
  FREE_PRIORITY_QUEUE(pq, q);
}

void test_queue_push() {
  CREATE_PRIORITY_QUEUE(pq, q);
  q->push(q, 1);
  assert(q->top(q) == 1);
  q->push(q, 3);
  assert(q->top(q) == 3);
  q->push(q, 2);
  assert(q->top(q) == 3);
  FREE_PRIORITY_QUEUE(pq, q);
}

void test_queue_pop() {
  CREATE_PRIORITY_QUEUE(pq, q);
  assert(q->size(q) == 0);
  q->push(q, 1);
  assert(q->top(q) == 1);
  q->push(q, 3);
  assert(q->top(q) == 3);
  q->push(q, 2);
  assert(q->top(q) == 3);
  q->pop(q);
  assert(q->top(q) == 2);
  q->pop(q);
  assert(q->top(q) == 1);
  q->pop(q);
  assert(q->empty(q));
  FREE_PRIORITY_QUEUE(pq, q);
}

void test_queue_swap() {
  CREATE_PRIORITY_QUEUE(pq, q1);
  CREATE_PRIORITY_QUEUE(pq, q2);
  q1->push(q1, 1);
  q1->push(q1, 3);
  q1->push(q1, 2);
  q1->swap(q1, q2);
  assert(q1->empty(q1));
  assert(q2->size(q2) == 3);
  assert(q2->top(q2) == 3);
  FREE_PRIORITY_QUEUE(pq, q1);
  FREE_PRIORITY_QUEUE(pq, q2);
}

void test_queue_defn() {
  test_queue_top();
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
