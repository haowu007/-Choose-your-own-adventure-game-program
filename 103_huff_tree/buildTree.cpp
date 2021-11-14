#include "node.h"

Node * buildTree(uint64_t * counts) {
  //WRITE ME!
  priority_queue_t Mypq;
  for (unsigned i = 0; i < 257; i++) {
    if (counts[i] != 0) {
      Mypq.push(new Node(i, counts[i]));
    }
  }
  while (Mypq.size() > 1) {
    Node * left = Mypq.top();
    Mypq.pop();
    Node * right = Mypq.top();
    Mypq.pop();
    Mypq.push(new Node(left, right));
  }

  return Mypq.top();
}
