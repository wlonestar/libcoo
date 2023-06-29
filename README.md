# generic containers in C

- [x] vector

- [x] list

- [ ] stack

## Usage

### Just see example

1. Clone this repo

```bash
git clone https://github.com/wlonestar/generic_stack.git
```

2. Build and run test case

```bash
make && ./stack
```

You will see custom print function output.

```
0 1 2 3 4 5 6 7 8 9 
0.000000 1.000000 2.000000 3.000000 4.000000 5.000000 6.000000 7.000000 8.000000 9.000000 
a b c d e f g h i j 
(0 0.000000) (1 0.100000) (2 0.200000) (3 0.300000) (4 0.400000) (5 0.500000) (6 0.600000) (7 0.700000) (8 0.800000) (9 0.900000)
```

### Use in existing project

1. Add `stack.h` in project.

2. Define a stack container.

Use macro `DECLARE_STACK` to define a stack named `struct_name` with type of `value_type`.

```c
DECLARE_STACK(struct_name, value_type)
```

3. Create an instance of the object

Use macro `CREATE_STACK` to create a struct pointer `obj_name` of struct `struct_name`.

```c
CREATE_STACK(struct_name, obj_name)
```

4. Use method in project

Now you have an object-oriented style stack container.

Here is the example code.

```c
// define a int type stack
DECLARE_STACK(int_stack, int)

// write print method
static void int_stack_print(int_stack *self) {
  for (int i = 0; i < self->size(self); i++) {
    printf("%d ", self->data[i]);
  }
  printf("\n");
}

// test function for int_stack
void test_int_stack(int_stack *stk) {
  assert(stk->empty(stk) == true);
  for (int i = 0; i < 10; i++) {
    stk->push(stk, i);
    assert(stk->top(stk) == i);
  }
  assert(stk->size(stk) == 10);
  stk->print(stk);
  for (int i = 0; i < 10; i++) {
    assert(stk->top(stk) == 9 - i);
    stk->pop(stk);
  }
  assert(stk->size(stk) == 0);
}

int main() {
  // create an instance of int_stack
  CREATE_STACK(int_stack, stk)
  // override print method
  stk->print = int_stack_print;
  test_int_stack(stk);
  // free stack
  FREE_STACK(stk)

  return 0;
}
```

In the container inner, I use function pointer to define method, so you can override them if necessary.

```c
value_type  (*top)(struct struct_name* self);
bool        (*empty)(struct struct_name* self);
size_t      (*size)(struct struct_name* self);
void        (*push)(struct struct_name* self, value_type value);
void        (*pop)(struct struct_name* self);
void        (*print)(struct struct_name* self);
```
