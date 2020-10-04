/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(tail_->next);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  while(head_ != NULL){
    ListNode* nhead = head_ ->next;
    delete head_;
    head_ = nhead;
  }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  if(length_ == 0){
    head_ = newNode;
    tail_ = newNode;
  }else{
    head_ ->prev = newNode;
    newNode ->next = head_;
    head_ = newNode;
  }
  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newBack = new ListNode(ndata);
  if(length_ == 0){
    head_ = newBack;
    tail_ = newBack;
  }else{
    newBack ->prev = tail_; 
    tail_ ->next = newBack;
    tail_ = newBack;
  }
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */

template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  if(start == NULL){
    return NULL;
  } 
  if(splitPoint==0){
    return start;
  }
  ListNode * curr = start;
  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }
  
  if (curr != NULL) {
      curr->prev->next = NULL;
      curr->prev = NULL;
      return curr;
  }
  return NULL;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  if(length_ < 3){
    return;
  }
  ListNode* curr_past1;
  ListNode* curr_past2;
  ListNode* curr_past3;
  ListNode* curr_next;
  ListNode* curr = head_;
  int count = 0;
  while(count < length_){
    if((count+1)%3==0){
      if(count == 2){
        curr_past1 = curr->prev;
        curr_past2 = curr_past1 -> prev;
        curr_next = curr -> next;
        curr_past2 -> prev = curr;
        curr -> next = curr_past2;
        curr_past2->next = curr_next;
        curr_next->prev = curr_past2;
        curr_past1->prev = NULL;
        head_ = curr_past1;
        curr = curr_past2;
      }else{
        curr_past1 = curr->prev;
        curr_past2 = curr_past1 -> prev;
        curr_past3 = curr_past2 -> prev;
        if(curr->next !=NULL){
          curr_next = curr->next;
          curr_past1->prev = curr_past3;
          curr_past3->next = curr_past1;
          curr_past2->prev = curr;
          curr->next = curr_past2;
          curr_past2->next = curr_next;
          curr_next -> prev = curr_past2;
          curr = curr_past2;
        }else{
          curr_past1->prev = curr_past3;
          curr_past3->next = curr_past1;
          curr_past2->prev = curr;
          curr -> next = curr_past2;
          curr_past2 -> next = NULL;
          tail_ = curr_past2;
          curr = curr_past2;
        }  
      }
    }
    curr = curr -> next;
    count++;
    }
  }
  /*if(length_ == 3){
    ListNode* second = curr -> next;
    ListNode* last = second -> next;
    curr -> prev = last;
    last -> next = curr;
    second->prev = NULL;
    curr -> next = NULL;
    head_ = second;
    tail_ = curr;
    return;
  }
  for (int i = 0; i<length_-(length_%3)-; i++) {
    ListNode* firstprev = curr -> prev;
    ListNode* lastnext = curr -> next -> next -> next;
    ListNode* second = curr -> next;
    ListNode* last = curr -> next -> next;
    if(i%3==0){
      curr -> prev = last;
      last -> next = curr;
      curr -> next = lastnext;
      if(i==0){
        head_ = second;
        lastnext -> prev = curr;
      }else if(length_-i == 3){
        tail_ = curr;
        firstprev -> next = second;
      }else{
        firstprev -> next = second;
        lastnext -> prev = curr;
      }
    } 
    curr = curr->next;
  }*/


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  if(head_ == nullptr || tail_ == nullptr) return;
  if(startPoint == endPoint) return;
  ListNode* currstart = startPoint;
  ListNode* endnext = endPoint->next;
  ListNode* startprev = startPoint -> prev;
  ListNode* curr = startPoint->next; 
  ListNode* temp = NULL;
  while(curr != endPoint){
    temp = curr->next;
    curr->next = curr->prev;
    curr->prev = temp;
    curr = temp;
  }
  endPoint -> next = endPoint -> prev;
  endPoint -> prev = startprev;
  startPoint -> prev = startPoint -> next;
  startPoint -> next = endnext;

  if(startprev == NULL){
    head_ = endPoint;
  } else {
    startprev->next = endPoint;
  }
  if(endnext == NULL) {
    tail_ = startPoint;
  } else {
    endnext->prev = startPoint;
  }
  startPoint = endPoint;
  endPoint = currstart; 
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  int len = this->size();
  ListNode* cur = head_;
  ListNode* startpoint = head_;
  if(len%n == 0){
    int i = 0;
    for(cur = head_; cur != NULL ; cur=cur->next){
      if((i+1)%n==0){
        reverse(startpoint, cur);
        startpoint = cur->next;
      }
      i++;
    }
  }else{
    int i = 0;
    for(cur = head_; cur != NULL ; cur=cur->next){
      if((i+1)%n==0){
        reverse(startpoint, cur);
        startpoint = cur->next;
      }
      if(cur->next == NULL){
        reverse(startpoint, cur);
      }
      i++;
   }
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  ListNode* first_cur = first;
  ListNode* second_cur = second;
  ListNode* cur = NULL;
  ListNode* toreturn = NULL;
  if(first == NULL && second == NULL){
    return NULL;
  }
  if(first == NULL){
    return second;
  }
  if(second == NULL){
    return first;
  }
  if(first_cur->data < second_cur->data){
    cur = first;
    first_cur = first_cur->next;
    toreturn = first;
    }else{
    cur = second;
    second_cur = second_cur->next;
    toreturn = second;
  }
    while(first_cur!=NULL && second_cur!=NULL){
      if(second_cur->data < first_cur->data){
        cur->next = second_cur;
        second_cur->prev = cur;
        cur = second_cur;
        second_cur = second_cur->next;
      }else{
        cur->next = first_cur;
        first_cur->prev = cur;
        cur = first_cur;
        first_cur = first_cur->next;
      }
   }
    if(first_cur==NULL){
      cur->next = second_cur;
    }
    if(second_cur==NULL){
      cur->next = first_cur;
    }
    return toreturn;
  }


/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if(start == NULL||start->next == NULL){
    return start;
  }
  ListNode* left = start;
  ListNode* right = split(start, chainLength / 2);
  return merge(mergesort(left, chainLength/2), mergesort(right, chainLength-chainLength/2));
}
