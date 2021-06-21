#include <stdio.h> // printf
#include "doublyLinkedList.h"

void printList(LinkedList *list) {
  ListItem *current = list->first;
  while(current) {
	printf("%d ", *(int *) current->data);
	current = current->next;
  }
  printf(" (size %lu)\n", list->length);
}

int isEven(void *a) {
  return *(int *) a % 2 == 0;
}

void* mult2(void *a) {
  int *p = a;
  *p = *p * 2;
  return p;
}

void sumAcc(void *accumulator, void *num) {
  int *acc = accumulator;
  int *b = num;
  *acc = *acc + *b;
}

void printListReverse(LinkedList *list) {
  ListItem *current = list->last;
  while(current) {
	printf("%d ", *(int *) current->data);
	current = current->prev;
  }
  printf(" (size %lu)\n", list->length);
}

int main(int argc, char* argv[]) {
  LinkedList list = DefaultList, list2 = DefaultList;
  int arr[10] = {1,2,3,4,5,6,7,8,9,10};
  int i = 0;
  for(; i < 3; i++) {
	prepend(&list, arr + i);
  }
  printf("List1 after prepends\n");
  printList(&list);
  printListReverse(&list);

  for(; i < 10; i++) {
	append(&list2, arr + i);
  }
  printf("List2 after appends\n");
  printList(&list2);
  printListReverse(&list2);


  int *removed = findRemove(&list, &isEven);
  printf("List1 after removing %d\n", *removed);
  printList(&list);

  list = *merge(&list, &list2);
  printf("After merging List1 and List2\n");
  printList(&list);
  printListReverse(&list);

  printf("After filtering even numbers in List1\n");
  LinkedList list3 = DefaultList;
  filter(&list, &list3, &isEven);
  printList(&list);
  printList(&list3);

  int sumValue = 0;
  foldl(&list, &sumAcc, &sumValue);
  printf("Sum of even numbers is %d\n", sumValue);

  removeAll(&list);
  removeAll(&list3);
  return 0;
}
