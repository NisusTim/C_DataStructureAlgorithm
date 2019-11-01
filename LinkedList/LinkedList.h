class LinkedList;

class ListNode {
 public:
  ListNode():key(0), next(NULL){};
  ListNode(int k):key(k), next(NULL){};
 private:
  int key;
  ListNode *next;
  ListNode *prev;  // always NULL for singly linked
 friend class LinkedList;
};

class LinkedList {
 public:
  LinkedList():head(NULL){};
  // queries
  void PrintList();
  ListNode *Search(int k);                // returns a pointer to the with key = k
  ListNode *Maximum(ListNode *node);      // returns a pointer to the largest key
  ListNode *Minimum(ListNode *node);      // returns a pointer to the smallest key
  ListNode *Successor(ListNode *node);    // returns a pointer to next larger element
  ListNode *Predecessor(ListNode *node);  // returns a pointer to next smaller element
  // modifying operations
  void PushFront(int k);  // insert head
  void PushBack(int k);   // insert tail
  void Delete(int k);
  void DeleteNode(ListNode *node);
  void Clear();
  void Reverse();
 private:
  int size;
  ListNode *head;
}
