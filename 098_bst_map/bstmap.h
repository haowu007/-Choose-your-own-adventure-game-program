#include <algorithm>
#include <cstdlib>
#include <iostream>

#include "map.h"
template<typename K, typename V>
class BstMap : public Map<K, V> {
 public:
  class Node {
   public:
    K key;
    V value;
    Node * left;
    Node * right;

    Node(K key, V value) : key(key), value(value), left(NULL), right(NULL) {}
  };
  Node * root;

 public:
  BstMap<K, V>() : root(NULL) {}

  virtual void add(const K & key, const V & value) {
    Node ** cur = &root;
    while (*cur != NULL) {
      if ((*cur)->key == key) {  //Add a key which already exists, replace its value
        (*cur)->value = value;
      }
      else {  //go deeper to look for the Place for the key to add
        cur = ((*cur)->key > key) ? (&(*cur)->left) : (&(*cur)->right);
      }
    }
    *cur = new Node(key, value);  //add this new Node to the proper place
  }

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * const * cur = &root;
    while (*cur != NULL) {
      if ((*cur)->key == key) {
        return (*cur)->value;
      }
      else {
        cur = ((*cur)->key > key) ? (&(*cur)->left) : (&(*cur)->right);
      }
    }
    throw std::invalid_argument("Key not found!");
  }

  void inorderprint(Node * Root) {
    if (Root == NULL) {
      return;
    }
    std::cout << Root->key << " ";
    inorderprint(Root->left);
    inorderprint(Root->right);
  }

  virtual void remove(const K & key) {
    Node ** cur = &root;
    while (*cur != NULL) {
      if ((*cur)->key == key) {
        if ((*cur)->left == NULL) {
          Node * need_delete = *cur;
          *cur = (*cur)->right;
          delete need_delete;
        }
        else if ((*cur)->right == NULL) {
          Node * need_delete = *cur;
          *cur = (*cur)->left;
          delete need_delete;
        }
        else {                               //the Node we are remoing had two children!
          Node ** replace = &(*cur)->right;  //Go right once
          while ((*replace)->left != NULL) {
            replace = &(*replace)->left;
          }
          //Now found the replacing Node!
          (*cur)->key = (*replace)->key;
          (*cur)->value = (*replace)->value;
          Node * need_delete = *replace;
          *replace =
              (*replace)
                  ->right;  //No matter this is Null or not, we just renew it (So we have removed this replacing Node)
          delete need_delete;
        }
        break;  //The removal was done
      }
      else {
        cur = ((*cur)->key > key) ? (&(*cur)->left) : (&(*cur)->right);
      }
    }
  }
  void copy(Node * rhs_root) {
    if (rhs_root == NULL) {
      return;
    }
    add(rhs_root->key, rhs_root->value);
    copy(rhs_root->left);
    copy(rhs_root->right);
  }

  BstMap<K, V>(const BstMap<K, V> & rhs) : root(NULL) { copy(rhs.root); }

  BstMap<K, V> & operator=(const BstMap<K, V> & rhs) {
    if (this != &rhs) {
      BstMap<K, V> temp(rhs);
      std::swap(temp.root, root);
    }
    return *this;
  }

  void clean(Node * root) {  //post order deletion
    if (root == NULL) {
      return;
    }
    clean(root->left);
    clean(root->right);
    delete root;
  }

  virtual ~BstMap<K, V>() {
    clean(root);

    //we should traverse the tree in resonable order and delete the Nodes!!!
  }
};
