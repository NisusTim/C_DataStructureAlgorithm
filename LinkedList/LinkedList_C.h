#ifndef LINKEDLIST_C_H_
#define LINKEDLIST_C_H_

struct ListNode {
  int key;
  struct ListNode *next;
  struct ListNode *prev;
};
typedef struct ListNode Node;

struct LinkedList {
  Node *head;
  Node *tail;
  Node *max;
  Node *min;
};
typedef struct LinkedList List;

// Queries
void PrintList(List *list);                         // exception: loop list
Node *SearchFirstKey(List *list, int k);
Node *SearchNode(List *list, Node *target);
Node *SearchNthNode(List *list, int n);
Node *SearchNthNodeFromTail(List *list, int n);
Node *SearchIntersection(Node *head1, Node *head2);
Node *GetHead(List *list);
Node *GetTail(List *list);
Node *Maximum(List *list);
Node *Minimum(List *list);
Node *Successor(List *list, Node *target);
Node *Predecessor(List *list, Node *target);
int GetSize(List *list);                            // Length
int CompareList(List *list1, List *list2);          // return 0: if equal, -1: list1 < list2, +1: list1 > list2
int CompareListRec(Node *head1, Node *head2);       // return 0: if equal, -1: head1 < head2, +1: head1 > head2
int DetectLoop(List *list);                         // return 0: if no loop or NULL, 1: if so
int DetectLoopType(List *list);                     // return 0: if no loop or NULL, 1: if loop, 2: circular

// Modifying Operations
Node *NewNode(int k);                               // private
// Insert: allocate new memory
Node *InsertHead(List *list, int k);                // PushFront
Node *InsertTail(List *list, int k);                // PushBack  or via Node *tail
Node *InsertSorted(List *list, int k);              // ascended
Node *InsertPosition(List *list, int k, int p);     // p = 0: head; out of range: return NULL
//Node *InsertPrev(Node **node, Node *target, int k);
Node *InsertNext(List *list, Node *target, int k);  // if not found: return NULL
Node *InsertNode(List *list, Node *node);
Node *InsertSortedNode(List *list, Node *node);  // 

int CopyList(List *dst, List *src);                 // dst, src
int CopyListReversed(List *dst, List *src);         // dst, src
Node *CopyListReversedRec(Node *src_head, Node *new_prev);  // new_prev = NULL, return dst_head

Node *ReverseList(List *list);
Node *ReverseListRec(List *list, Node *prev);       // prev = NULL for initial case
Node *SortList(List *list);
// Delete: free memory, 
int DeleteHead(List *list);
int DeleteTail(List *list);
int DeleteKey(List *list, int k);  // using curr as a traverser
int DeletePosition(List *list, int p);
//int DeletePrev(List *list, Node *target);
int DeleteNext(List *list, Node *target);
int DeleteNode(List *list, Node *target);
int DeleteNodeTASTE(List *list, Node *target);
int DeleteDuplicate(List *list);                    // for sorted list
int DeleteDuplicateRec(Node *head, Node *prev);     // for sorted list
int ClearNodes(List *list);                         // Delete all nodes of list

#endif  // LINKEDLIST_C_H_
