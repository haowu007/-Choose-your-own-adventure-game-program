#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <algorithm>
#include <cstdlib>
#include <exception>
#include <iostream>

//YOUR CODE GOES HERE

class invalid_index : public std::exception {};

template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    Node(const T & d) : data(d), next(NULL), prev(NULL) {}
    Node(const T & d, Node * n, Node * p) : data(d), next(n), prev(p) {}
  };
  Node * head;
  Node * tail;
  int size;

 public:
  void addFront(const T & item) {
    Node * oldhead = head;
    head = new Node(item, oldhead, NULL);
    size++;
    if (size == 1) {  //we just made the first node!
      tail = head;
    }
    else {
      head->next->prev = head;
    }
  }
  void addBack(const T & item) {
    Node * oldtail = tail;
    tail = new Node(item, NULL, oldtail);

    ++size;
    if (size == 1) {  //we just made the first node!
      head = tail;
    }
    else {
      oldtail->next = tail;
    }
  }
  bool remove(const T & item) {
    Node ** current = &head;
    while (*current != NULL) {
      if (item != (*current)->data) {  //item not found yet
        current = &(*current)->next;
      }
      else {
        Node * deleting = *current;
        if (deleting != tail) {
          deleting->next->prev = deleting->prev;
        }
        else {
          tail = deleting->prev;
        }
        *current = deleting->next;
        delete deleting;
        --size;
        return true;
      }
    }
    return false;  // item not found!
  }

  T & operator[](int index) {
    if (index + 1 > size) {
      throw invalid_index();
    }
    else {
      Node * current = head;
      while (index > 0) {
        --index;
        current = current->next;
      }
      return current->data;
    }
  }

  const T & operator[](int index) const {
    if (index + 1 > size) {
      throw invalid_index();
    }

    else {
      Node * current = head;
      while (index > 0) {
        --index;
        current = current->next;
      }
      return current->data;
    }
  }

  int find(const T & item) const {
    int index = 0;
    Node * current = head;
    while (current != NULL) {
      if (current->data != item) {
        current = current->next;
        index++;
      }
      else {
        return index;
      }
    }
    return -1;  //did not find the item!
  }

  LinkedList() : head(NULL), tail(NULL), size(0) {}

  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(0) {
    Node * current = rhs.head;
    while (current != NULL) {
      addBack(current->data);
      current = current->next;
    }
  }

  LinkedList & operator=(const LinkedList & rhs) {
    if (this != &rhs) {
      LinkedList temp(rhs);

      Node * deleting;
      while (tail != NULL) {
        deleting = tail;
        tail = tail->prev;
        delete deleting;
      }
      // Now we have properly deallocted the space before the copy happens
      std::swap(head, temp.head);
      std::swap(tail, temp.tail);
      std::swap(size, temp.size);
    }

    return *this;
  }
  ~LinkedList() {
    Node * deleting;
    while (tail != NULL) {
      deleting = tail;
      tail = tail->prev;
      delete deleting;
    }  // Now we have properly d
  }

  int getSize() const { return size; }
  friend class Tester;
};

#endif
