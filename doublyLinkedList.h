#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <stddef.h> // size_t

struct ListItem {
  void *data;
  struct ListItem *next, *prev;
};

struct LinkedList {
  struct ListItem *first;
  struct ListItem *last;
  size_t length;
};

typedef struct ListItem ListItem;
typedef struct LinkedList LinkedList;

LinkedList DefaultList;

void prepend(LinkedList *list, void *data);
void append(LinkedList *list, void *data);
LinkedList* merge(LinkedList *list1, LinkedList *list2);
void removeAll(LinkedList *list);
void removeFirst(LinkedList *list);
void removeLast(LinkedList *list);
void removeByIndex(LinkedList *list, size_t index);
void* findBy(LinkedList *list, int (*comp) (void *a));
void* findRemove(LinkedList *list, int (*comp) (void *a));
void map(LinkedList *list, void* (*f) (void *a));
void filter(LinkedList *list, LinkedList *filtered, int (*comp) (void *a));
void foldl(LinkedList *list, void (*acc) (void *accumulator, void *b), void *initialValue);

#endif
