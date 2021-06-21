# Linked List implementation in C

## Singly Linked List

The first approach is to a use a linked list only with next pointers. This makes it easy to implement but has higher cost especially when appending because it needs to be traversed to till the last element.

We can use `struct` as a wrapper to linked list so that its length can be stored. The stored data is a void pointer, so it can store pointer of any type.

```c
struct ListItem {
  void *data;
  struct ListItem *next;
};

struct LinkedList {
  struct ListItem *head;
  size_t length;
};
```

For conviniece, we can create shorthand for the struct type as shown below,

``` c
typedef struct ListItem ListItem;
typedef struct LinkedList LinkedList;
```

We can also define initial state for a linked list,

``` c
LinkedList DefaultLinkedList = {.head = NULL, .length = 0};
```

We can use `malloc` to allocate new struct on heap so that the `struct` persists outside the function call,

``` c
ListItem *item = malloc(sizeof(ListItem));
```
Let's run example for singly linked list,

``` shell
$ gcc -g -o x singleLinkedListExample.c singleLinkedList.c
$ ./x
9 8 7 6 5 0 1 2 3 4  (size 10)
6 5 0 1 2 3 4  (size 7)
6 5 0 1  (size 4)
6 5 1  (size 3)
 (size 0)
```

Then, we need to make sure that whenever we remove an element from list it is removed. To help check it, we can run `valgrind` on the executable to detect possible unfreed memories.
```
$ valgrind --leak-check=full ./x
==2675== Memcheck, a memory error detector
==2675== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==2675== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==2675== Command: ./x
==2675== 
9 8 7 6 5 0 1 2 3 4  (size 10)
6 5 0 1 2 3 4  (size 7)
6 5 0 1  (size 4)
6 5 1  (size 3)
 (size 0)
==2675== 
==2675== HEAP SUMMARY:
==2675==     in use at exit: 0 bytes in 0 blocks
==2675==   total heap usage: 11 allocs, 11 frees, 1,184 bytes allocated
==2675== 
==2675== All heap blocks were freed -- no leaks are possible
==2675== 
==2675== For counts of detected and suppressed errors, rerun with: -v
==2675== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```



