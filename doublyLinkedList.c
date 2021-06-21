
#include <stddef.h> // size_it
#include <stdlib.h> // malloc
#include "doublyLinkedList.h"
#include <stdio.h>
LinkedList DefaultList = {.first = NULL, .last = NULL, .length = 0};

ListItem* addItem(void *data, ListItem *next, ListItem *prev) {
  ListItem *item = malloc(sizeof(ListItem));
  item->data = data;
  item->next = next;
  item->prev = prev;
  return item;
}

void addToEmptyList(LinkedList *list, void *data) {
  if(list->length == 0) {
	list->first = addItem(data, NULL, NULL);
	list->last = list->first;
	list->length = 1;
  }
}

void addItemToEmptyList(LinkedList *list, ListItem *item) {
  if(list->length == 0) {
	list->first = item;
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

void appendItem(LinkedList *list, ListItem *item) {
  if(list->length == 0) {
	addItemToEmptyList(list, item);
	return;
  }

  ListItem* secondlast = list->last;
  secondlast->next = item;
  item->prev = secondlast;
  item->next = NULL;
  list->last = item;
  list->length++;
}

// merge lists where list1 is followed by list2
// pointer to list2 should be discarded
LinkedList* merge(LinkedList *list1, LinkedList *list2) {
  if(!list1) { return list2; }
  else if(!list2) { return list1; }

  list1->last->next = list2->first;
  list2->first->prev = list1->last;
  list1->last = list2->last;
  list1->length += list2->length;
  return list1;
}

void removeAll(LinkedList *list) {
  ListItem *current = list->first;
  while(current) {
	ListItem *next = current->next;
	free(current);
	current = next;
  }
  list->first = NULL;
  list->last = NULL;
  list->length = 0;
}

void removeFirst(LinkedList *list) {
  if(list->length <= 1) {
	removeAll(list);
	return;
  }
  
  ListItem* newFirst = list->first->next;
  newFirst->prev = NULL;
  free(list->first);
  list->first = newFirst;
  list->length--;
}

void removeLast(LinkedList *list) {
  if(list->length <= 1) {
	removeAll(list);
	return;
  }

  ListItem* newLast = list->last->prev;
  newLast->next = NULL;
  free(list->last);
  list->last = newLast;
  list->length--;
}

void removeByIndex(LinkedList *list, size_t index) {
  // check index is within list length
  // comparing size_t which is unsigned, so if argument for index was (int) -1 then it would be implicitly converted to the largest unsigned int
  if(index >= list->length) {
	return;
  } else if(index == 0) {
	removeFirst(list);
	return;
  } else if(index + 1 == list->length) {
	removeLast(list);
	return;
  }

  int idx = 0;
  ListItem* current = list->first;
  while(current) {
	if(idx == index) break;
	idx++;
	current = current->next;
  }

  // assume there exists non-null prev and next, since current cannot be neither first nor last item in the list
  ListItem* prev = current->prev;
  ListItem* next = current->next;

  prev->next = next;
  next->prev = prev;
  free(current);
  list->length--;
}

ListItem* findItemBy(LinkedList *list, int (*comp) (void *a)) {
  ListItem *current = list->first;

  while(current) {
	if( (*comp) (current->data) ) {
	  return current;
	}
	current = current->next;
  }

  return NULL;
}

void* findBy(LinkedList *list, int (*comp) (void *a)) {
  ListItem* item = findItemBy(list, comp);

  if(item) {
	return item->data;
  } else {
	return NULL;
  }
} 

void* findRemove(LinkedList *list, int (*comp) (void *a)) {
  ListItem* item = findItemBy(list, comp);

  if(!item) { return NULL; }

  if(item->prev && item->next) {  // prev -> item -> next => prev -> next
	item->prev->next = item->next;
	item->next->prev = item->prev;
  } else if(item->prev) {  // prev -> item -> NULL => prev -> NULL
	item->prev->next = NULL;
	list->last = item->prev;
  } else {  // NULL -> item -> next => NULL -> next
	item->next->prev = NULL;
	list->first = item->next;
  }

  void *data = item->data;
  free(item);
  list->length--;
  return data;
}

void map(LinkedList *list, void* (*f) (void *a)) {
  ListItem *current = list->first;
  while(current) {
	current->data = (*f) (current->data);
	current = current->next;
  }
}

// Remove pointers to and from item
// assume item is in the list
void extractItem(LinkedList *list, ListItem *item) {
  if(!item) { return; }
  if(list->length == 1) {
	list->first = NULL;
	list->last = NULL;
  } else  if(item->prev && item->next) {
	item->prev->next = item->next;
	item->next->prev = item->prev;
  } else if(!item->prev) { // item is first in the list
	list->first = item->next;
	list->first->prev = NULL;
  } else if(!item->next) { // item is last in the list
	list->last = item->prev;
	list->last->next = NULL;
  }
  
  item->next = NULL;
  item->prev = NULL;
  list->length--;
}

// Extract filtered items out of list
// Append extracted items to filtered list
void filter(LinkedList *list, LinkedList *filtered, int (*comp) (void *a)) {
  ListItem* current = list->first;
  //ListItem* addTo = filtered->first;
  while(current) {
	ListItem* next = current->next;
	if(!(*comp) (current->data)) {
	  extractItem(list, current);
	  if(filtered) {
		appendItem(filtered, current);
	  }
	}
	current = next;
  }
}

void foldl(LinkedList *list, void (*acc) (void *accumulator, void *b), void *initialValue) {
  ListItem *current = list->first;
  while(current) {
	(*acc) (initialValue, current->data);
	current = current->next;
  }
}
