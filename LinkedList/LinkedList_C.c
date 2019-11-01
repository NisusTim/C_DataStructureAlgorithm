#include <stdio.h>
#include <stdlib.h>
#include "LinkedList_C.h"

int main(int argc, char *argv[]) {
  /*int arr[] = {9, 5, 2, 7};*/
  int arr[] = {1, 3, 5, 7};
  int size = sizeof(arr) / sizeof(arr[0]);
  List *sll = (List *)calloc(1, sizeof(List));

  Node *x;
  for (int i = 0; i < size; ++i)
    InsertTail(sll, arr[i]);
  InsertSorted(sll, 6);
  x = SearchNthNodeFromTail(sll, 0);
  /*DeleteTail(sll);*/
  /*DeleteDuplicateRec(sll->head, NULL);*/
    PrintList(sll);
  DeleteNodeTASTE(sll, x);
    PrintList(sll);
  List *sll2 = (List *)calloc(1, sizeof(List));
  /*InsertHead(sll2, 0);*/
  /*InsertTail(sll2, 1);*/
  /*x = InsertTail(sll2, 2);*/
  /*x->next = sll2->head->next->next;*/

  printf("GetSize(sll): %d\n", GetSize(sll));
  /*CopyListReversed(sll2, sll);*/
  /*sll2->head = CopyListReversedRec(sll->head, NULL);*/
  /*CopyList(sll2, sll);*/
  /*InsertSortedNode(sll2, x);*/
  /*DeleteTail(sll2);*/
    /*PrintList(sll2);*/
  printf("%d", DetectLoopType(sll2));
  int c = CompareListRec(sll->head, sll2->head);
  if (c == 0)
    printf("equal\n");
  else if (c > 0)
    printf("sll\n");
  else
    printf("sll2\n");
    
    /*
  x = SearchNode(sll, x);
  printf("%s\n", x == NULL ? " NULL" : "Exist");
  printf("%4d\n", x ? x->key : -1);
  
    PrintList(sll);
  InsertTail(sll, 5);
  InsertTail(sll, 3);
  InsertHead(sll, 9);
    PrintList(sll);
  InsertTail(sll, 4);
  DeleteKey(sll, 9);
  InsertHead(sll, 1);
    PrintList(sll);
  //ReverseList(sll);
  ReverseListRec(sll, NULL);
    PrintList(sll);
  //InsertPosition(sll, 99, 9);
    PrintList(sll);

  char buff[10];
  printf("%s\n", x == NULL ? " NULL" : "   OK");
  ClearNodes(sll);
    PrintList(sll);
    */
}

// Node *thru: single node for traversing
// Node *curr, *prev, *next: more than one node for traversing
// Node 

// All functions assume List *list is NOT NULL
// If there's at least one possibility to insert, traversing by "thru->next" to
// stay at tail eventually. If not, traversing by "thru".

// ######## Queries
void PrintList(List *list) {
  Node *thru = list->head;
  while (NULL != thru) {  // traversing
    printf("%4d ->", thru->key);
    thru = thru->next;
  }
  printf(" NULL\n");
}

Node *SearchFirstKey(List *list, int k) {
  Node *thru = list->head;
  // traversing, less or equal one result could be found, put thru->key into
  // while condition
  while (NULL != thru && k != thru->key)  
    thru = thru->next;
  return thru;
}

Node *SearchNode(List *list, Node *target) {
  Node *thru = list->head;
  while (NULL != thru && target != thru)  // traversing
    thru = thru->next;
  return thru;
}

Node *SearchNthNode(List *list, int n) {
  Node *thru = list->head;
  for (; NULL != thru && n > 0; thru = thru->next)
    --n;
  return thru;
}

Node *SearchNthNodeFromTail(List *list, int n) {
  Node *lead = list->head;
  Node *follow = NULL;
  for (; NULL != lead; lead = lead->next) {
    if (n > 0)
      --n;
    else if (n == 0) {
      follow = list->head;
      --n;
    } else
      follow = follow->next;
  }
  return follow;
}

int GetSize(List *list) {
  Node *thru = list->head;
  int id = 0;
  for (; NULL != thru; thru = thru->next) 
    ++id;
  return id;
}

int CompareList(List *list1, List *list2) {
  Node *thru1 = list1->head;
  Node *thru2 = list2->head;
  for (; NULL != thru1 && NULL != thru2; thru1 = thru1->next, thru2 = thru2->next) {
    if (thru1->key < thru2->key)
      return -1;
    else if (thru1->key > thru2->key)
      return 1;
  }
  if (NULL == thru1 && NULL == thru2)
    return 0;
  else if (NULL == thru1)
    return -1;
  else if (NULL == thru2)
    return 1;
}

int CompareListRec(Node *head1, Node *head2) {
  if (NULL == head1 && NULL == head2)
    return 0;
  else if (NULL == head1)
    return -1;
  else if (NULL == head2)
    return 1;
  else if (head1->key > head2->key)
    return 1;
  else if (head1->key < head2->key)
    return -1;
  return CompareListRec(head1->next, head2->next);
}

int DetectLoop(List *list) {
  Node *slow = list->head;
  Node *fast = list->head;
  while (NULL != fast && NULL != fast->next) {
    fast = fast->next->next;
    slow = slow->next;
    if (slow == fast)
      return 1;
  }
  return 0;
}

int DetectLoopType(List *list) {
  Node *slow = list->head;
  Node *fast = list->head;
  while (NULL != fast && NULL != fast->next) {
    fast = fast->next->next;
    slow = slow->next;
    if (list->head == fast)
      return 2;
    else if (slow == fast)
      return 1;
  }
  return 0;
}

// ######## Modifying Operations
Node *NewNode(int k) {
  Node *new_node = (Node *)calloc(1, sizeof(Node));
  if (NULL != new_node)
    new_node->key = k;
  return new_node;
}

Node *InsertHead(List *list, int k) {
  Node *new_head = NewNode(k);  // memory allocation
  if (NULL == new_head)
    return NULL;
  new_head->next = list->head;  // insert at head
  return list->head = new_head;
}

Node *InsertTail(List *list, int k) {
  Node *new_tail = NewNode(k);  // memory allocation
  if (NULL == new_tail)
    return NULL;
  // case 1: NULL head, insert at head
  if (NULL == list->head)
    return list->head = new_tail;
  // case 2: traversing by thru->next, until thru reaching tail
  Node *thru = list->head;
  while (NULL != thru->next)  
    thru = thru->next;
  return thru->next = new_tail;
}

Node *InsertSorted(List *list, int k) {
  Node *new_node = NewNode(k);  // memory allocation
  if (NULL == new_node)
    return NULL;
  // case 1: NULL head or k is smallest, insert at head
  if (NULL == list->head || k <= list->head->key) {  
    new_node->next = list->head;
    return list->head = new_node;
  }
  // case 2: traversing by thru-next, until thru reaching tail or proper position
  Node *thru = list->head;
  while (NULL != thru->next && k > thru->next->key)  
    thru = thru->next;
  new_node->next = thru->next;
  return thru->next = new_node;
}

Node *InsertPosition(List *list, int k, int p) {
  Node *new_node = NewNode(k);  // memory allocation
  if (NULL == new_node)
    return NULL;
  // case 1: NULL head and p != 0
  if (NULL == list->head && 0 != p)
    return NULL;
  // case 2: p == 0, insert at head
  if (0 == p) {
    new_node->next = list->head;
    return list->head = new_node;
  }
  // case 3: p != 0, traversing by thru
  int node_id = 1;
  Node *thru = list->head;
  while (NULL != thru) {
    if (node_id++ == p) {
      new_node->next = thru->next;
      return thru->next = new_node;
    }
    thru = thru->next;
  }
  return NULL;  // p is out of range
}

Node *InsertNext(List *list, Node *target, int k) {
  Node *new_node = NewNode(k);  // memory allocation
  if (NULL == new_node)
    return NULL;
  // case 1: traversing by thru
  Node *thru = list->head;
  while (NULL != thru) {
    if (target == thru) {
      new_node->next = thru->next;
      return thru->next = new_node;
    }
    thru = thru->next;
  }
  return NULL;  // target is not found
}

Node *InsertSortedNode(List *list, Node *node) {
  if (NULL == node)
    return NULL;
  return InsertSorted(list, node->key);
}

int CopyList(List *dst, List *src) {
  Node *new_head = NULL;
  Node *new_prev = NULL;
  for (Node *thru = src->head; NULL != thru; thru = thru->next) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->key = thru->key;
    new_node->next = NULL;
    if (thru != src->head)
      new_prev->next = new_node;
    else
      new_head = new_node;
    new_prev = new_node;
  }
  dst->head = new_head;
  return 0;
}

int CopyListReversed(List *dst, List *src) {
  Node *new_prev = NULL;
  for (Node *thru = src->head; NULL != thru; thru = thru->next) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->key = thru->key;
    new_node->next = new_prev;
    new_prev = new_node;
  }
  dst->head = new_prev;
}

Node *CopyListReversedRec(Node *src_head, Node *new_prev) {
  if (NULL == src_head)
    return new_prev;
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->next = new_prev;
  Node *new_head = CopyListReversedRec(src_head->next, new_node);
  new_node->key = src_head->key;
  return new_head;
}

Node *ReverseList(List *list) {
  // case 1: zero node or single node
  if (NULL == list->head || NULL == list->head->next)
    return list->head;
  // case 2: multiple nodes
  Node *prev = NULL;
  Node *curr = list->head;
  Node *next = curr->next;
  while (NULL != next) {
    curr->next = prev;
    prev = curr;
    curr = next;
    next = next->next;
  }
  curr->next = prev;
  return list->head = curr;
}

Node *ReverseListRec(List *list, Node *prev) {
  // case 1: zero node at head, NULL head
  if (NULL == list->head)
    return list->head;
  // case 2: Termination: connect with prev at tail
  if (NULL == list->head->next) {
    list->head->next = prev;
    return list->head;
  }
  Node *new_prev = list->head;  // can NOT use prev->next, prev may be NULL
  Node *new_head = list->head->next;  // head->next need to point to prev
  list->head->next = prev;
  list->head = new_head;
  return ReverseListRec(list, new_prev);
}

Node *SortList(List *list) {

}

int DeleteHead(List *list) {
  // case 1: zero node, NULL head
  if (NULL == list->head)
    return 0;
  // case 2: normal case
  Node *old_head = list->head;
  list->head = list->head->next;
  free(old_head);  // memory freed
  return 0;
}

int DeleteTail(List *list) {
  // case 1: zero node
  if (NULL == list->head)
    return 0;
  // case 2: single node
  if (NULL == list->head->next) {
    free(list->head);  // memory freed
    list->head = NULL;  // reset head
    return 0;
  }
  // case 3: multiple nodes, traversing by thru->next->next, until thru->next reaching tail
  Node *thru = list->head;
  while (NULL != thru->next->next)
    thru = thru->next;
  free(thru->next);  // memory freed
  thru->next = NULL;  // MUST reset new_tail->next = NULL; !!
  return 0;
}

int DeleteKey(List *list, int k) {
  // case 1: NULL head
  // if (NULL == list->head)
  //  return 0;
  // case 2: 
  Node *prev = NULL;
  Node *curr = list->head;
  while (NULL != curr) {
    if (k == curr->key) {
      Node *temp = curr;
      curr = curr->next;
      if (list->head == temp)  // at head
        list->head = curr;
      else
        prev->next = curr;
      free(temp);
    } else {
      prev = curr;
      curr = curr->next;
    }
  }
  return 0;
}

int DeletePosition(List *list, int p) {
}

int DeleteNext(List *list, Node *target) {
}

int DeleteNode(List *list, Node *target) {
  if (NULL == list->head || NULL == target)
    return 0;
  Node *prev = NULL;
  Node *curr = list->head;
  while (NULL != curr) {
    if (target == curr) {
      Node *temp = curr;
      curr = curr->next;
      if (list->head == temp)
        list->head = curr;
      else
        prev->next = curr;
      free(temp);
    } else {
      prev = curr;
      curr = curr->next;
    }
  }
  return 0;
}

int DeleteNodeTASTE(List *list, Node *target) {
  for (Node **indirect = &list->head; NULL != *indirect; indirect = &(*indirect)->next)
    if (target == *indirect) {
      Node *temp = target;
      *indirect = target->next;
      free(temp);
      break;
    }
    /*
  for (Node *thru = list->head; NULL != thru; thru = thru->next)
    if (target == thru) {
      Node *temp = target;
      thru = target->next;
      free(temp);
      break;
    }
    */
  return 0;
}

int DeleteDuplicate(List *list) {
  // case 1: zero node or single node
  if (NULL == list->head || NULL == list->head->next)
    return 0;
  // case 2: multiple nodes
  Node *thru = list->head;
  while (NULL != thru->next) {
    if (thru->key == thru->next->key) {
      Node *temp = thru->next;
      thru->next = thru->next->next;
      free(temp);
    } else {
      thru = thru->next;
    }
  }
  return 0;
}

int DeleteDuplicateRec(Node *head, Node *prev) {
  // case 1: zero node, NULL head meanwhile Termination
  if (NULL == head)
    return 0;
  // case 2:
  Node *new_prev;
  Node *new_head;
  if (NULL != prev && prev->key == head->key) {
    new_prev = prev;
    new_head = head->next;
    new_prev->next = new_head;  // connect
    free(head);
  } else {
    new_prev = head;
    new_head = head->next;
  }
  DeleteDuplicateRec(new_head, new_prev);
}

int ClearNodes(List *list) {
  // case 1: zero node
  if (NULL == list->head)
    return 0;
  // case 2: single node or multiple nodes
  Node *thru = list->head;
  while (NULL != thru) {
    Node *temp = thru;
    thru = thru->next;
    free(temp);
  }
  list->head = NULL;  // freed memory but pointer value does NOT be set NULL
  return 0;
}
