#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
 private:
  class Node {
   public:
    K key;
    V value;
    Node * left;
    Node * right;
    Node() : key(0), value(0), left(NULL), right(NULL) {}
    Node(const K & k, const V & v) : key(k), value(v), left(NULL), right(NULL) {}
  };

  Node * root;

 public:
  BstMap() : root(NULL) {}

  //copy constructor
  BstMap(const BstMap & rhs) : root(NULL) { root = copy(rhs.root); }

  //cooy helper
  Node * copy(Node * curr) {
    if (curr == NULL) {
      return NULL;
    }
    Node * root = new Node(curr->key, curr->value);
    root->left = copy(curr->left);
    root->right = copy(curr->right);
    return root;
  }

  BstMap & operator=(const BstMap & rhs) {
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

  virtual ~BstMap() {
    destroy(root);
    //root = NULL;
  }

  virtual void add(const K & key, const V & value) {
    Node ** curr = &root;
    while (*curr != NULL) {
      //key exists, then replace its value
      if (key == (*curr)->key) {
        (*curr)->value = value;
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
    *curr = new Node(key, value);
  }

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * curr = root;
    while (curr != NULL) {
      if (key == curr->key) {
        return curr->value;
      }
      else if (key < curr->key) {
        curr = curr->left;
      }
      else {
        curr = curr->right;
      }
    }
    //cannot find the key, then throw
    throw std::invalid_argument("Cannot find the key!\n");
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
      (*curr)->value = (*temp2)->value;
      Node * Temp = (*temp2)->right;
      delete *temp2;
      *temp2 = Temp;
    }
  }
};
