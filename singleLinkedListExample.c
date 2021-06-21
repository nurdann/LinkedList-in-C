#include <stdio.h> // printf
#include "singleLinkedList.h"

void printList(LinkedList *list) {
  ListItem *current = list->head;
  while(current) {
	printf("%d ", *(int *) current->data);
	current = current->next;
  }
  printf(" (size %lu)\n", list->length);
}

int main(int argc, char* argv[]) {
  LinkedList list = {.length = 0};
  int arr[10];
  for(int i = 0; i < 5; i++) {
	arr[i] = i;
	append(&list, (void*) (arr + i));	
  }

  for(int i = 5; i < 10; i++) {
	arr[i] = i;
	prepend(&list, (void*) (arr + i));
  }

  printList(&list);

  for(int i=0; i<3; i++)
	removeFirst(&list);
  printList(&list);
  for(int i=0; i<3; i++) removeLast(&list);
  printList(&list);
  removeByIndex(&list, 2);
  printList(&list);
  removeAll(&list);
  printList(&list);
  return 0;
}
