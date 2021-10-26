#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
class Expression {
 public:
  virtual std::string toString() const = 0;

  virtual ~Expression() {}
};

class NumExpression : public Expression {
 private:
  long number;

 public:
  NumExpression(long num) : number(num) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << number;
    std::string s = ss.str();
    return s;
  }
  virtual ~NumExpression() {}
};

class PlusExpression : public Expression {
 private:
  Expression * left;
  Expression * right;

 public:
  PlusExpression(Expression * lhs, Expression * rhs) : left(lhs), right(rhs) {}
  virtual std::string toString() const {
    std::string ans;
    std::stringstream ss;
    ss << "(";
    ss << left->toString();
    ss << " + ";
    ss << right->toString();
    ss << ")";
    return ans = ss.str();
  }
  virtual ~PlusExpression() {
    delete left;
    delete right;
  }
};
