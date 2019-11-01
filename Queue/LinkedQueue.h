#ifndef LINKEDQUEUE_H_
#define LINKEDQUEUE_H_

// Initialize: set listed queue properties
// Enqueue/Dequeue: memory allocation/deallocation for a single Node and data
// and memory duplication by memcpy()
// Delete: memory deallocation for all Nodes
// SetCapacity: set listed queue property

typedef struct ListNode {
  void *data;
  struct ListNode *next;
} Node;

typedef struct LinkedQueue {
  size_t mem_size;    // memory size of generic data
  size_t capacity;    // max of queue_size
  size_t queue_size;  // current queue_size
  Node *head;
  Node *tail;
} LQueue;

void Initialize(LQueue *que, size_t capacity, size_t mem_size);
int Enqueue(LQueue *que, const void *data);  // push(), insert element, allocation 
int Dequeue(LQueue *que, void *data);        // pop(), remove element, deallocation
void Delete(LQueue *que);                    // deallocation
int SetCapacity(LQueue *que, size_t capacity);

int IsEmpty(LQueue *que);
int IsFull(LQueue *que);
int GetCapacity(LQueue *que);
int GetSize(LQueue *que);
int GetHead(LQueue *que, void *data);
int GetTail(LQueue *que, void *data);

void PrintQueue(LQueue *que);  // for integer data use
void Test(void);

#endif  // LINKEDQUEUE_H_
