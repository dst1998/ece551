#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>

//YOUR CODE GOES HERE
template<typename T>
class LinkedList {
 public:
  class Node {
   public:
    T data;
    Node * prev;
    Node * next;
    Node(T d) : data(d), next(NULL), prev(NULL){};
    Node(T d, Node * p, Node * n) : data(d), prev(p), next(n){};
  };
  Node * head;
  Node * tail;
  int size;

 public:
  LinkedList() : head(NULL), tail(NULL), size(0) {}
  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(0) {
    if (rhs.size == 0) {
      return;
    }
    Node * old = rhs.head;
    head = new Node(old->data, NULL, NULL);
    Node * curr = head;
    old = old->next;
    while (old != NULL) {
      curr->next = new Node(old->data, curr, NULL);
      curr = curr->next;
      old = old->next;
    }
    tail = curr;
    size = rhs.size;
  }
  LinkedList & operator=(const LinkedList & rhs) {
    if (this != &rhs) {
      LinkedList temp(rhs);
      Node * tem = head;
      head = temp.head;
      temp.head = tem;
      tem = tail;
      tail = temp.tail;
      temp.tail = tem;
      size = temp.size;
    }
    return *this;
  }
  ~LinkedList() {
    Node * curr = head;
    while (head != NULL) {
      head = curr->next;
      delete curr;
      curr = head;
    }
  }
  void addFront(const T & item) {
    if (size == 0) {
      head = new Node(item, NULL, NULL);
      tail = head;
    }
    else {
      Node * curr = new Node(item, NULL, head);
      head->prev = curr;
      head = curr;
    }
    size++;
  }
  void addBack(const T & item) {
    if (size == 0) {
      head = new Node(item, NULL, NULL);
      tail = head;
    }
    else {
      Node * curr = new Node(item, tail, NULL);
      tail->next = curr;
      tail = curr;
    }
    size++;
  }
  bool remove(const T & item) {
    Node * curr = head;
    while (curr != NULL) {
      if (curr->data == item) {
        if (curr == head) {
          if (curr->next == NULL) {
            head = NULL;
            tail = NULL;
          }
          else {
            head = curr->next;
            head->prev = NULL;
          }
        }
        else if (curr == tail) {
          tail = curr->prev;
          tail->next = NULL;
        }
        else {
          curr->prev->next = curr->next;
          curr->next->prev = curr->prev;
        }
        delete curr;
        size--;
        return true;
      }
      curr = curr->next;
    }

    return false;
  }
  T & operator[](int index) {
    try {
      if (index < 0 || index >= size) {
        throw std::exception();
      }
    }
    catch (std::exception & e) {
      std::cerr << "out of range" << std::endl;
    }
    Node * curr = head;
    for (int i = 0; i < index; i++) {
      curr = curr->next;
    }
    return curr->data;
  }
  const T & operator[](int index) const {
    try {
      if (index < 0 || index >= size) {
        throw std::exception();
      }
    }
    catch (std::exception & e) {
      std::cerr << "out of range" << std::endl;
    }
    Node * curr = head;
    for (int i = 0; i < index; i++) {
      curr = curr->next;
    }
    return curr->data;
  }
  int find(const T & item) {
    Node * curr = head;
    for (int i = 0; i < size; i++) {
      if (item == curr->data) {
        return i;
      }
      curr = curr->next;
    }
    return -1;
  }
  int getSize() const { return size; }
  friend void testDefCtor(void);
  friend void testAddFront(void);
  friend void testAddBack(void);
  friend void testRemove(void);
  friend void testRules(void);
};

#endif
