#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedQueue.h"

/*
int main(void) {
  Test();
  return 0;
}
*/

void Initialize(LQueue *que, size_t capacity, size_t mem_size) {
  que->mem_size = mem_size;
  que->capacity = capacity;
  que->queue_size = 0;
  que->head = que->tail = NULL;
}

int Enqueue(LQueue *que, const void *data) {
  // if queue is full
  if (que->capacity <= que->queue_size)
    return -1;
  // memory allocation for Node
  Node *new_node = (Node *)calloc(1, sizeof(data));
  if (NULL == new_node)
    return -1;
  // memory allocation for data
  new_node->data = malloc(sizeof(que->mem_size));
  if (NULL == new_node->data) {
    free(new_node);
    return -1;
  }
  memcpy(new_node->data, data, que->mem_size);
  // renew listed queue
  if (NULL == que->head)
    que->head = que->tail = new_node;
  else {
    que->tail->next = new_node;
    que->tail = que->tail->next;
  }
  ++que->queue_size;
  return 0;
}

int Dequeue(LQueue *que, void *data) {
  // if queue is empty
  if (0 == que->queue_size)
    return -1;
  // memory duplication and release
  Node *temp = que->head;
  que->head = que->head->next;
  if (NULL != data)
    memcpy(data, temp->data, que->mem_size);
  free(temp->data);
  free(temp);
  // renew listed queue
  if (1 == que->queue_size--)
    que->tail = NULL;
  return 0;
}

void Delete(LQueue *que) {
  // traversing and memory deallocation
  for (Node *thru = que->head, *temp; NULL != thru; ) {
    temp = thru;
    thru = thru->next;
    free(temp->data);
    free(temp);
  }
  // renew listed queue
  que->queue_size = 0;
  que->head = que->tail = NULL;
}

int SetCapacity(LQueue *que, size_t capacity) {
  if (que->queue_size > capacity)
    return -1;
  que->capacity = capacity;
  return 0;
}

int IsEmpty(LQueue *que) {
  return 0 == que->queue_size;
}

int IsFull(LQueue *que) {
  return que->capacity <= que->queue_size;
}

int GetCapacity(LQueue *que) {
  return que->capacity;
}

int GetSize(LQueue *que) {
  return que->queue_size;
}

int GetHead(LQueue *que, void *data) {
  if (0 != que->queue_size && NULL != data) {
    memcpy(data, que->head->data, que->mem_size);
    return 0;
  }
  return -1;
}

int GetTail(LQueue *que, void *data) {
  if (0 != que->queue_size && NULL != data) {
    memcpy(data, que->tail->data, que->mem_size);
    return 0;
  }
  return -1;
}

void Test(void) {
  int d = 10;
  int *p = &d;
  int e;
  int *r = &e;
  LQueue q;
  Initialize(&q, 10, sizeof(d));
  for (int i = 0; i < 18; ++i) {
    Enqueue(&q, p);
    ++(*p);
    if (q.queue_size == q.capacity)
      Dequeue(&q, NULL);
    PrintQueue(&q);
    GetTail(&q, r);
    /*printf("%d\n", *r);*/
  }
  printf("Cap: %3d\n", GetCapacity(&q));
  SetCapacity(&q, 8);
  printf("Cap: %3d\n", GetCapacity(&q));
  for (int i = 0; i < 8; ++i) {
    Enqueue(&q, p);
    ++(*p);
    PrintQueue(&q);
  }
  Delete(&q);
  PrintQueue(&q);
  Initialize(&q, 5, sizeof(d));
  PrintQueue(&q);
  for (int i = 0; i < 8; ++i) {
    Enqueue(&q, p);
    ++(*p);
    PrintQueue(&q);
  }
}

void PrintQueue(LQueue *que) {
  Node *thru = que->head;
  for (int i = 0; i < que->queue_size && NULL != thru; ++i, thru = thru->next)
    printf("%3d >> ", *((int *)thru->data));
  printf("NULL\n");
}
