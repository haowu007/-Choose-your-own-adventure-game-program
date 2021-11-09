#include <algorithm>
#include <cstdlib>
#include <iostream>

#include "set.h"
template<typename T>
class BstSet : public Set<T> {
 public:
  class Node {
   public:
    T val;
    Node * left;
    Node * right;

    Node(T value) : val(value), left(NULL), right(NULL) {}
  };
  Node * root;

 public:
  BstSet<T>() : root(NULL) {}

  virtual void add(const T & value) {
    Node ** cur = &root;
    while (*cur != NULL) {
      if ((*cur)->val == value) {  //Add a key which already exists, do nothing
        return;
      }
      else {  //go deeper to look for the Place for the place to add
        cur = ((*cur)->val > value) ? (&(*cur)->left) : (&(*cur)->right);
      }
    }
    *cur = new Node(value);  //add this new Node to the proper place
  }

  virtual bool contains(const T & value) const {
    Node * const * cur = &root;
    while (*cur != NULL) {
      if ((*cur)->val == value) {
        return true;
      }
      else {
        cur = ((*cur)->val > value) ? (&(*cur)->left) : (&(*cur)->right);
      }
    }
    return false;
  }

  void inorderprint(Node * Root) {
    if (Root == NULL) {
      return;
    }
    std::cout << Root->val << " ";
    inorderprint(Root->left);
    inorderprint(Root->right);
  }

  virtual void remove(const T & value) {
    Node ** cur = &root;
    while (*cur != NULL) {
      if ((*cur)->val == value) {
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
          (*cur)->val = (*replace)->val;

          Node * need_delete = *replace;
          *replace =
              (*replace)
                  ->right;  //No matter this is Null or not, we just renew it (So we have removed this replacing Node)
          delete need_delete;
        }
        break;  //The removal was done
      }
      else {
        cur = ((*cur)->val > value) ? (&(*cur)->left) : (&(*cur)->right);
      }
    }
  }
  void copy(Node * rhs_root) {
    if (rhs_root == NULL) {
      return;
    }
    add(rhs_root->val);
    copy(rhs_root->left);
    copy(rhs_root->right);
  }

  BstSet<T>(const BstSet<T> & rhs) : root(NULL) { copy(rhs.root); }

  BstSet<T> & operator=(const BstSet<T> & rhs) {
    if (this != &rhs) {
      BstSet<T> temp(rhs);
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

  virtual ~BstSet<T>() {
    clean(root);

    //we should traverse the tree in resonable order and delete the Nodes!!!
  }
};
