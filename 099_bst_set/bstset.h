#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "set.h"

template<typename K>
class BstSet : public Set<K> {
 private:
  class Node {
   public:
    K key;
    Node * left;
    Node * right;
    Node() : key(0), left(NULL), right(NULL) {}
    Node(const K & k) : key(k), left(NULL), right(NULL) {}
  };

  Node * root;

 public:
  BstSet() : root(NULL) {}

  //copy constructor
  BstSet(const BstSet & rhs) : root(NULL) { root = copy(rhs.root); }

  //cooy helper
  Node * copy(Node * curr) {
    if (curr == NULL) {
      return NULL;
    }
    Node * root = new Node(curr->key);
    root->left = copy(curr->left);
    root->right = copy(curr->right);
    return root;
  }

  BstSet & operator=(const BstSet & rhs) {
    if (this != &rhs) {
      Node * temp = copy(rhs.root);
      destroy(root);
      root = temp;
    }
    return *this;
  }
  //destroy helper
  void destroy(Node * curr) {
    if (curr != NULL) {
      destroy(curr->left);
      destroy(curr->right);
      delete curr;
      curr = NULL;  //
    }
  }

  virtual ~BstSet() {
    destroy(root);
    //root = NULL;
  }

  virtual void add(const K & key) {
    Node ** curr = &root;
    while (*curr != NULL) {
      //key exists, then replace its value
      if (key == (*curr)->key) {
        return;
      }
      else if (key < (*curr)->key) {
        curr = &((*curr)->left);
      }
      else {
        curr = &((*curr)->right);
      }
    }
    //cannot find the key, then add a nade
    *curr = new Node(key);
  }

  virtual bool contains(const K & key) const {
    Node * curr = root;
    while (curr != NULL) {
      if (key == curr->key) {
        return true;
      }
      else if (key < curr->key) {
        curr = curr->left;
      }
      else {
        curr = curr->right;
      }
    }
    //cannot find the key, then throw
    return false;
  }

  virtual void remove(const K & key) {
    Node ** curr = &root;
    while ((*curr)->key != key) {
      if (key > (*curr)->key) {
        curr = &(*curr)->right;
      }
      else {
        curr = &(*curr)->left;
      }
      if ((*curr) == NULL)
        return;
    }
    if ((*curr)->left == NULL) {
      Node * temp = (*curr)->right;
      delete *curr;
      *curr = temp;
    }
    else if ((*curr)->right == NULL) {
      Node * tem = (*curr)->left;
      delete *curr;
      *curr = tem;
    }
    else {
      Node ** temp2 = &(*curr)->right;
      while ((*temp2)->left != NULL) {
        temp2 = &(*temp2)->left;
      }
      (*curr)->key = (*temp2)->key;
      Node * Temp = (*temp2)->right;
      delete *temp2;
      *temp2 = Temp;
    }
  }
};
