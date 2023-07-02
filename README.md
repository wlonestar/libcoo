<center>
libcoo: generic containers in C
</center>

An Object-Oriented style generic containers library in C

## Usage

### Just see example

clone repo and build

```bash
git clone https://github.com/wlonestar/libcoo.git && cd libcoo
make
```

then you will see built test case and example files in `/build` dir, you can run just by executable file's name, such as:


```bash
make run NAME=rbtree_example
```

You will see two different type rbtrees print out.

```
--str1
  ->str0
  =>str3
    ->str2
    =>str4
str1 str0 str3 str2 str4 
str0 str1 str2 str3 str4 
str0 str2 str4 str3 str1 
str1 str0 str3 str2 str4 
--3.85
  ->1.72
    ->0.49
    =>3.78
      ->2.40
  =>4.65
    ->4.34
      ->4.32
    =>4.98
      =>8.10
3.85 1.72 0.49 3.78 2.40 4.65 4.34 4.32 4.98 8.10 
0.49 1.72 2.40 3.78 3.85 4.32 4.34 4.65 4.98 8.10 
0.49 2.40 3.78 1.72 4.32 4.34 8.10 4.98 4.65 3.85 
3.85 1.72 4.65 0.49 3.78 4.34 4.98 2.40 4.32 8.10
```

### Use in existing project

just put header files in your project, in case of complex containers may depends on basic conntainers, just like `rbtree` depends `vector`, `stack` and `queue`. 

declare a container with a type just like:

```c
DECLARE_STACK(stack_name, value_type)
```

create an instance of the object:

```c
CREATE_STACK(stack_name, obj_name)
```

and free instance by using:

```c
FREE_STACK(stack_name, obj_name)
```

more details you can read source code and it is easy to understand.

## TODO

- [ ] hashtable

- ...

