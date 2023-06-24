#ifndef alloc_h
#define alloc_h

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

void *reallocate(void *pointer, size_t old_size, size_t new_size) {
  if (new_size == 0) {
    free(pointer);
    return NULL;
  }
  void *result = realloc(pointer, new_size);
  if (result == NULL) {
    fprintf(stderr, "no enough to malloc\n");
    exit(-1);
  }
  return result;
}

#define GROW_CAPACITY(capacity) ((capacity) < 8 ? 8 : (capacity) * 2)

#define GROW_ARRAY(type, ptr, old_cnt, new_cnt) \
  (type *) reallocate(ptr, sizeof(type) * (old_cnt), sizeof(type) * (new_cnt))

#define FREE_ARRAY(type, pointer, old_count) \
  reallocate(pointer, sizeof(type) * (old_count), 0)

#endif
