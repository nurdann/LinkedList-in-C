#include "singleLinkedList.h"
#include <stdlib.h>
LinkedList DefaultLinkedList = {.head = NULL, .length = 0};

ListItem* newListItem(void *data, ListItem *next) {
  ListItem *item = malloc(sizeof(ListItem));
  item->data = data;
  item->next = next;
  return item;
}

void append(LinkedList *list, void *data) {
  if(list->length == 0) {
	list->head = newListItem(data, NULL);
  } else {
	ListItem *last = list->head;
	while(last->next) { last = last->next; }
	last->next = newListItem(data, NULL);
  }
  list->length++;
}

void prepend(LinkedList *list, void *data) {
  if(list->length == 0) {
	list->head = newListItem(data, NULL);
  } else {
	ListItem *second = list->head;
	list->head = newListItem(data, NULL);
	list->head->next = second;
  }
  list->length++;
}

void removeFirst(LinkedList *list) {
  if(list->length == 0) return;

  ListItem *second = list->head->next;
  free(list->head);
  list->head = second;
  list->length--;
}

void removeLast(LinkedList *list) {
  if(list->length == 0) return;
  else if (list->length == 1) {
	removeFirst(list);
	return;
  }
  
  ListItem *secondlast = list->head;

  while(secondlast->next->next) { secondlast = secondlast->next; }

  free(secondlast->next);
  secondlast->next = NULL;
  list->length--;
}

void removeByIndex(LinkedList *list, size_t index) {
  if(index == 0) {
	removeFirst(list);
	return;
  } else if(index + 1 == list->length) {
	removeLast(list);
	return;
  }
  int kth = 0;
  ListItem *current = list->head;
  while(current->next) {
	kth++;
	if(kth == index) break;
	current = current->next;
  }

  if(current->next) {
	ListItem *newnext = current->next->next;
	free(current->next);
	current->next = newnext;
	list->length--;
  }
}

void removeAll(LinkedList *list) {
  ListItem *current = list->head;
  while(current) {
	ListItem *prev = current;
	current = current->next;
	free(prev);
  }
  list->head = NULL;
  list->length = 0;
}
