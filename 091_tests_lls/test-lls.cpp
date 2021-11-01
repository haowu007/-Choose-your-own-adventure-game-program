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
    IntList l;
    l.addFront(1);
    assert(l.getSize() == 1);
    assert(l.head != NULL);
    assert(l.head->data == 1);
    assert(l.tail != NULL);
    assert(l.head == l.tail);
    assert(l.head->next == NULL);
    assert(l.head->prev == NULL);

    l.addFront(2);
    assert(l.getSize() == 2);
    assert(l.head != NULL);
    assert(l.tail != NULL);
    assert(l.head != l.tail);
    assert(l.head->data == 2);

    assert(l.tail->data == 1);
    assert(l.head->next != NULL);
    assert(l.head->next->data == 1);
    assert(l.head->prev == NULL);
    assert(l.head->next->next == NULL);
    assert(l.head->next->prev == l.head);
  }
  void testAddBack() {
    // WRITE ME
    IntList l;
    l.addBack(1);
    assert(l.getSize() == 1);
    assert(l.head != NULL);
    assert(l.head->data == 1);
    assert(l.tail != NULL);
    assert(l.head == l.tail);
    assert(l.head->next == NULL);
    assert(l.head->prev == NULL);

    l.addBack(2);
    assert(l.getSize() == 2);
    assert(l.head != NULL);
    assert(l.tail != NULL);
    assert(l.head != l.tail);
    assert(l.head->data == 1);

    assert(l.tail->data == 2);
    assert(l.head->next != NULL);
    assert(l.head->next->data == 2);
    assert(l.head->prev == NULL);
    assert(l.head->next->next == NULL);
    assert(l.head->next->prev == l.head);
    assert(l.tail->prev == l.head);
    assert(l.tail->next == NULL);
  }
  void testConstructor() {
    IntList list1;
    IntList L(list1);
    assert(L.getSize() == 0 && L.head == NULL && L.tail == NULL);
    list1.addFront(1);
    list1.addFront(1);
    list1.addFront(3);
    IntList l(list1);  //Copy constructor used!
    assert(l.head != list1.head && l.tail != list1.tail &&
           l.head->next != list1.head->next);          //deep copy?
    assert(l.getSize() == 3 && list1.getSize() == 3);  //size?
    assert(l.head->data == 3 && l.head->next->data == 1 &&
           l.tail->data == 1);                             //data value?
    assert(l.head->prev == NULL && l.tail->next == NULL);  //Null Pointers?
    assert(l.head->next->next->prev == l.head->next);      //middle pointers?
    assert(l.tail->prev == l.head->next);                  //middle pointers?
    assert(l.head->next->next == l.tail);                  //tail?

    l.addBack(2);  //[3,1,1,2]
    assert(l.getSize() == 4 && l.tail->data == 2 && l.tail->prev->data == 1);
  }

  void testCopyconstructor() {
    IntList list1;
    IntList L(list1);
    assert(L.getSize() == 0 && L.head == NULL && L.tail == NULL);
    list1.addFront(1);
    list1.addFront(1);
    list1.addFront(3);
    IntList l;
    l.addFront(15);
    l.addFront(14);
    l.addBack(999);
    l = list1;  //Copy assignment constructor used!!

    assert(l.head != list1.head && l.tail != list1.tail &&
           l.head->next != list1.head->next);          //deep copy?
    assert(l.getSize() == 3 && list1.getSize() == 3);  //size?
    assert(l.head->data == 3 && l.head->next->data == 1 &&
           l.tail->data == 1);                             //data value?
    assert(l.head->prev == NULL && l.tail->next == NULL);  //Null Pointers?
    assert(l.head->next->next->prev == l.head->next);      //middle pointers?
    assert(l.tail->prev == l.head->next);                  //middle pointers?
    assert(l.head->next->next == l.tail);                  //tail?

    l.addBack(2);  //[3,1,1,2]
    assert(l.getSize() == 4 && l.tail->data == 2 && l.tail->prev->data == 1);
  }
  void testRemove() {
    IntList l3;
    assert(l3.remove(1) == false);
    l3.addFront(111);
    assert(l3.remove(111) == true);
    assert(l3.getSize() == 0 && l3.head == NULL && l3.tail == NULL);
    IntList l;
    l.addFront(3);
    l.addFront(1);
    l.addFront(5);
    l.addFront(1);
    l.addFront(2);

    assert(l.remove(2) == true);  //remove from front?
    assert(l.getSize() == 4 && l.head->data == 1 && l.head->prev == NULL);
    assert(l.head->next->data == 5);

    assert(l.remove(2) == false);  //can't remove again?

    assert(l.remove(3) == true);  //remove from back?
    assert(l.getSize() == 3 & l.tail->data == 1 && l.tail->next == NULL);

    assert(l.remove(1) == true);  //remove first item in duplications?
    assert(l.getSize() == 2 && l.head->data == 5 && l.tail->data == 1);

    IntList l2;
    l2.addBack(11);
    l2.addBack(12);
    l2.addBack(13);

    assert(l2.remove(12) == true);  //remove from middle?
    assert(l2.getSize() == 2 && l2.head->data == 11 && l2.tail->data == 13);
    assert(l2.head->next == l2.tail && l2.tail->prev == l2.head);

    // many more tester methods
  }
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  t.testAddBack();
  t.testConstructor();
  t.testCopyconstructor();
  t.testRemove();
  // write calls to your other test methods here
  return EXIT_SUCCESS;
}
