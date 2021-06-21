# Linked List implementation in C

## Singly Linked List

The first approach is to a use a linked list only with next pointers. This makes it easy to implement but has higher cost especially when appending because it needs to be traversed till the last element.

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

For convenience, we can create shorthand for the struct type as shown below,

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

## Doubly Linked List

For the doubly linked datastructure we need two pointers for previous and consecutive items which makes adding and removing elements from both ends have constant time complexity.

The `struct` for the linked list has a length member as well as pointers to the first and last elements of the list,

``` c
struct ListItem {
  void *data;
  struct ListItem *next, *prev;
};

struct LinkedList {
  struct ListItem *first;
  struct ListItem *last;
  size_t length;
};
```


The `length` member allows for checking the list size efficiently. In addition, we can modularize code by creating subroutines that can be reused. For example,

``` c
void addToEmptyList(LinkedList *list, void *data) {
  if(list->length == 0) {
	list->first = addItem(data, NULL, NULL);
	list->last = list->first;
	list->length = 1;
  }
}

void prepend(LinkedList *list, void *data) {
  if(list->length == 0) {
	addToEmptyList(list, data);
	return;
  }
  ListItem* second = list->first;
  ListItem* newFirst = addItem(data, second, NULL);
  second->prev = newFirst;
  list->first = newFirst;
  list->length++;
}
```

Inside the function `prepend`, we check whether list empty and if so call `addToEmptyList`. Now, the code below the if-statement can assume that the list has at least one item so we do not need worry about `list->last` pointer because it will keep pointing to the last item. In similar fashion below, we can apply the same method for `append` where we do not modify `list->first`,

``` c
void append(LinkedList *list, void *data) {
  if(list->length == 0) {
	addToEmptyList(list, data);
	return;
  }

  ListItem* secondlast = list->last;
  ListItem* newLast = addItem(data, NULL, secondlast);
  secondlast->next = newLast;
  list->last = newLast;
  list->length++;
}
```


We can run example file `doublyLinkedListExample.c` and again check with `valgrind` that the heap allocated items are freed,

``` c
$ gcc -o x doublyLinkedListExample.c doublyLinkedList.c
$ valgrind --leak-check=full ./x
==20815== Memcheck, a memory error detector
==20815== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==20815== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==20815== Command: ./x
==20815== 
List1 after prepends
3 2 1  (size 3)
1 2 3  (size 3)
List2 after appends
4 5 6 7 8 9 10  (size 7)
10 9 8 7 6 5 4  (size 7)
List1 after removing 2
3 1  (size 2)
After merging List1 and List2
3 1 4 5 6 7 8 9 10  (size 9)
10 9 8 7 6 5 4 1 3  (size 9)
After filtering even numbers in List1
4 6 8 10  (size 4)
3 1 5 7 9  (size 5)
Sum of even numbers is 28
==20815== 
==20815== HEAP SUMMARY:
==20815==     in use at exit: 0 bytes in 0 blocks
==20815==   total heap usage: 11 allocs, 11 frees, 1,264 bytes allocated
==20815== 
==20815== All heap blocks were freed -- no leaks are possible
==20815== 
==20815== For counts of detected and suppressed errors, rerun with: -v
==20815== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

