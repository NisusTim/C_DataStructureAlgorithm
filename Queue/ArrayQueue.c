#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayQueue.h"

int main(void) {
  Test();
  return 0;
}

int Initialize(AQueue *que, size_t capacity, size_t mem_size) {
  // dynamic memory allocation for array
  que->body = (void **)malloc(capacity * (sizeof(void *) + mem_size));
  if (NULL == que->body)
    return -1;
  void *p_seg = (void *)(que->body + capacity);
  for (int i = 0; i < capacity; ++i, p_seg += mem_size)
    (que->body)[i] = p_seg;
  // initialize array queue
  que->mem_size = mem_size;
  que->capacity = capacity;
  que->queue_size = 0;
  que->head = 0;
  que->tail = 0;
  return 0;
}

int Enqueue(AQueue *que, const void *data) {
  // if queue is full 
  if (que->capacity <= que->queue_size)
    return -1;
  // memory duplication into array
  memcpy((que->body)[que->tail], data, que->mem_size);
  // renew array queue 
  ++que->queue_size;
  que->tail = ++que->tail % que->capacity;
  return 0;
}

int Dequeue(AQueue *que, void *data) {
  // if queue is empty
  if (0 == que->queue_size)
    return -1;
  // memory duplication out of array
  if (NULL != data)
    memcpy(data, (que->body)[que->head], que->mem_size);
  // renew array queue
  --que->queue_size;
  que->head = ++que->head % que->capacity;
  return 0;
}

int Resize(AQueue *que, size_t capacity) {
  // new capacity not enough for current data
  if (que->queue_size > capacity)
    return -1;
  // new memory allocation
  void **new_body =
    (void **)malloc(capacity * (sizeof(void *) + que->mem_size));
  if (NULL == new_body)
    return -1;
  void *p_seg = (void *)(new_body + capacity);
  for (int i = 0; i < capacity; ++i, p_seg += que->mem_size) {
    new_body[i] = p_seg;
    if (i < que->queue_size)
      memcpy(new_body[i], 
             (que->body)[(que->head + i) % que->capacity], que->mem_size);
  }
  free(que->body);
  // renew array queue
  que->body = new_body;
  que->capacity = capacity;
  que->head = 0;
  que->tail = que->queue_size;
  return 0;
}

void Delete(AQueue *que) {
  // memory deallocation
  free(que->body);
  // renew array queue
  que->queue_size = 0;
  que->head = que->tail;
}

int IsEmpty(AQueue *que) {
  return 0 == que->queue_size;
}

int IsFull(AQueue *que) {
  return que->capacity <= que->queue_size;
}

int GetCapacity(AQueue *que) {
  return que->capacity;
}

int GetSize(AQueue *que) {
  return que->queue_size;
}

int GetHead(AQueue *que, void *data) {
  if (0 != que->queue_size && NULL != data) {
    memcpy(data, (que->body)[que->head], que->mem_size);
    return 0;
  }
  return -1;
}

int GetTail(AQueue *que, void *data) {
  if (0 != que->queue_size && NULL != data) {
    memcpy(data, 
           (que->body)[(que->tail + que->capacity - 1) % que->capacity],
           que->mem_size);
    return 0;
  }
  return -1;
}

void Test(void) {
  int d = 10;
  int *p = &d;
  int e;
  int *r = &e;
  AQueue q;
  Initialize(&q, 10, sizeof(d));
  for (int i = 0; i < 18; ++i) {
    Enqueue(&q, p);
    ++(*p);
    if (q.queue_size == q.capacity)
      Dequeue(&q, NULL);
    PrintQueue(&q);
    GetHead(&q, r);
    /*printf("%d\n", *r);*/
  }
  printf("Cap: %3d\n", GetCapacity(&q));
  Resize(&q, 8);
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

void PrintQueue(AQueue *que) {
  for (int i = 0; i < que->queue_size; ++i)
    printf("%3d, ", *((int *)(que->body)[(que->head + i) % que->capacity]));
  printf("NULL\n");
}
