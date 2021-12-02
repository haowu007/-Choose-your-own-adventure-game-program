#include <cstdlib>
#include <iostream>
#include <set>
#include <stack>
#include <vector>
class Node {
 public:
  int Node_ID;
  Node * parent;
  std::vector<Node *> children;  //size=0 for leaf nodes
  bool visited;                  //= false when constructed
};

std::set<int> Greedy_post_order_DFS(Node * root) {
  std::set<int> invited_set;
  std::stack<Node *> mystack;
  mystack.push(root);
  while (!mystack.empty()) {
    Node * cur = mystack.top();
    mystack.pop();
    int invite_its_chidren = 1;
    if (cur->visited == true) {
      for (size_t i = 0; i < cur->children.size(); i++) {
        if (cur->children[i]->children.size() != 0) {
          invite_its_chidren = 0;
        }
      }
      if (invite_its_chidren == 1) {
        for (size_t i = 0; i < cur->children.size(); i++) {
          invited_set.insert(cur->children[i]->Node_ID);
        }
        std::vector<Node *>::iterator it;
        for (it = cur->parent->children.begin(); it != cur->parent->children.end();
             ++it) {
          if (*it == cur) {
            cur->parent->children.erase(it);
          }
        }
      }
    }
    else {
      cur->visited = true;
      mystack.push(cur);
      for (size_t i = 0; i < cur->children.size(); i++) {
        mystack.push(cur->children[i]);
      }
    }
  }
  std::cout << "This code has never been tested!\n";
  return invited_set;
}
