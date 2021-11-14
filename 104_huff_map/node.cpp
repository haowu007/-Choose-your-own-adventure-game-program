#include "node.h"
void Node::buildMap(BitString b, std::map<unsigned, BitString> & theMap) {
  if (sym != NO_SYM) {
    assert(left == NULL && right == NULL);
    theMap[sym] = b;
    return;
  }
  BitString leftstr = b.plusZero();
  BitString rightstr = b.plusOne();
  left->buildMap(leftstr, theMap);
  right->buildMap(rightstr, theMap);

  //WRITE ME!
}
