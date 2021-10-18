#include "IntArray.h"

#include <assert.h>

#include <ostream>

IntArray::IntArray() : data(NULL), numElements(0) {
}
IntArray::IntArray(int n) : data(new int[n]), numElements(n) {
}

IntArray::IntArray(const IntArray & rhs) :
    data(new int[rhs.numElements]),
    numElements(rhs.numElements) {
  for (int j = 0; j < numElements; j++) {
    data[j] = rhs.data[j];
  }
}
IntArray::~IntArray() {
  delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  if (&rhs != this) {
    int * temp = new int[rhs.numElements];
    for (int p = 0; p < rhs.numElements; p++) {
      temp[p] = rhs.data[p];
    }
    delete[] data;
    data = temp;
    numElements = rhs.numElements;
  }
  return *this;
}
const int & IntArray::operator[](int index) const {
  assert(index >= 0 && index <= numElements - 1);
  return data[index];
}
int & IntArray::operator[](int index) {
  assert(index >= 0 && index <= numElements - 1);
  return data[index];
}

int IntArray::size() const {
  return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
  if (numElements != rhs.numElements) {
    return false;
  }
  for (int y = 0; y < numElements; y++) {
    if (data[y] != rhs.data[y]) {
      return false;
    }
  }
  return true;
}

bool IntArray::operator!=(const IntArray & rhs) const {
  if (numElements == rhs.numElements) {
    return false;
  }
  for (int y = 0; y < numElements; y++) {
    if (data[y] == rhs.data[y]) {
      return false;
    }
  }
  return true;
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  s << "{";
  for (int u = 0; u < rhs.numElements; u++) {
    if (u >= 1) {
      s << " ";
    }
    s << rhs.data[u];
    if (u < rhs.numElements - 1) {
      s << ",";
    }
  }
  s << "}";
  return s;
}
