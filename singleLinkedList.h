#ifndef SINGLELINKEDLIST_H
#define SINGLELINKEDLIST_H
#include <stddef.h> // size_t

struct ListItem {
  void *data;
  struct ListItem *next;
};

struct LinkedList {
  struct ListItem *head;
  size_t length;
};

typedef struct ListItem ListItem;
typedef struct LinkedList LinkedList;
LinkedList DefaultLinkedList;

ListItem* newListItem(void *data, ListItem *next);
void append(LinkedList *list, void *data);
void prepend(LinkedList *list, void *data);
void removeFirst(LinkedList *list);
void removeLast(LinkedList *list);
void removeByIndex(LinkedList *list, size_t index);
void removeAll(LinkedList *list);
#endif
