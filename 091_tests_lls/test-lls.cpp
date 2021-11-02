#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    // WRITE ME
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
    il.addFront(10);
    assert(il.head->data == 10 && il.head->next == NULL && il.tail->data == 10 &&
           il.tail->next == NULL && il.tail->prev == NULL);
    assert(il.head == il.tail);
    il.addFront(20);
    assert(il.head->data == 20 && il.head->next->data == 10 && il.tail->data == 10 &&
           il.tail->next == NULL && il.tail->prev->data == 20);
    assert(il.head->next == il.tail);
  }
  // many more tester methods
  void testAddBack() {
    IntList il3 = IntList();
    IntList il(il3);
    assert(il.head == NULL && il.tail == NULL && il.getSize() == 0);
    il.addBack(10);
    IntList::Node * n1 = il.tail;
    assert(n1->data == 10 && n1->next == NULL && il.tail->data == 10 &&
           n1->next == NULL && il.tail->prev == NULL);
    assert(il.head == il.tail);
    il.addBack(20);
    IntList::Node * n2 = il.tail;
    assert(n1 == il.head);
    assert(il.head->data == 10 && il.head->next->data == 20 && il.tail->data == 20 &&
           il.tail->next == NULL && n2->prev->data == 10);
    assert(il.head->next == n2);
    il.addBack(30);
    IntList::Node * n3 = il.tail;
    assert(n1 == il.head);
    assert(il.head->data == 10 && il.head->next->data == 20 && n3->data == 30 &&
           n3->next == NULL && n3->prev->data == 20);
    assert(n3->prev == n2);
  }

  void testRules() {
    IntList il1 = IntList();
    IntList il3 = il1;

    il1.addFront(20);
    IntList il = IntList(il1);
    assert(il.head->data == 20 && il.head->next == NULL && il.tail->data == 20 &&
           il.tail->prev == NULL && il.tail == il.head);
    il1.addFront(10);
    il = IntList(il1);
    assert(il.head->data == 10 && il.head->next->data == 20 &&
           il.tail->prev->data == 10 && il.head->next == il.tail &&
           il.tail->prev == il.head);
  }

  void testRemove() {
    IntList il;
    assert(il.head == NULL && il.tail == NULL && il.getSize() == 0);
    il.addBack(20);
    il.addBack(30);
    il.addFront(10);
    assert(il.remove(20));
    IntList::Node * n1 = il.head;
    assert(n1->data == 10 && n1->next->data == 30 && il.tail->data == 30 &&
           n1->next == il.tail && il.tail->prev == n1 && il[0] == 10 && il[1] == 30 &&
           il.getSize() == 2);
    IntList il1 = il;

    assert(il.remove(30));
    assert(!il.remove(100));
    IntList::Node * n2 = il.tail;
    assert(n2 == il.head);
    assert(il.head->next == NULL && il.head->data == 10 && il.tail->data == 10 &&
           il.tail->prev == NULL && il[0] == 10 && il.getSize() == 1);

    assert(il1.remove(10));
    assert(!il1.remove(100));
    IntList::Node * n4 = il1.tail;
    assert(n4 == il1.head);
    assert(il1.head->next == NULL && il1.head->data == 30 && il1.tail->data == 30 &&
           il1.tail->prev == NULL && il1[0] == 30 && il1.getSize() == 1);

    il.remove(10);
    assert(il.head == NULL && il.tail == NULL && il.getSize() == 0);
  }
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  t.testAddBack();
  t.testRules();
  t.testRemove();
  // write calls to your other test methods here
  return EXIT_SUCCESS;
}
