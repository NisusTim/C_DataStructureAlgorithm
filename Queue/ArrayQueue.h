#ifndef ARRAYQUEUE_H_
#define ARRAYQUEUE_H_

// Initialize: memory allocation
// Enqueue/Dequeue: memory duplication by memcpy()
// Delete: memory deallocation
// Resize: memory reallocation by malloc() and memcpy(), rather than realloc()

typedef struct ArrayQueue {
  void **body;
  size_t mem_size;    // memory size of generic data
  size_t capacity;    // max of queue_size
  size_t queue_size;  // current queue_size
  size_t head;
  size_t tail;        // index of the one after last one
} AQueue;

int Initialize(AQueue *que, size_t capacity, size_t mem_size);  // allocation
int Enqueue(AQueue *que, const void *data);  // push(), insert element by memcpy()
int Dequeue(AQueue *que, void *data);        // pop(), remove element by memcpy()
void Delete(AQueue *que);                    // deallocation
int Resize(AQueue *que, size_t capacity);

int IsEmpty(AQueue *que);
int IsFull(AQueue *que);
int GetCapacity(AQueue *que);
int GetSize(AQueue *que);
int GetHead(AQueue *que, void *data);
int GetTail(AQueue *que, void *data);

void PrintQueue(AQueue *que);  // for integer data use
void Test(void);

#endif  // ARRAYQUEUE_H_
