#include "IntMatrix.h"

IntMatrix::IntMatrix() : numRows(0), numColumns(0), rows(NULL) {
}
IntMatrix::IntMatrix(int r, int c) : numRows(r), numColumns(c), rows(NULL) {
  rows = new IntArray *[numRows];
  for (int i = 0; i < numRows; i++) {
    rows[i] = new IntArray(numColumns);
  }
}
IntMatrix::IntMatrix(const IntMatrix & rhs) :
    numRows(rhs.numRows),
    numColumns(rhs.numColumns),
    rows(new IntArray *[rhs.numRows]) {
  for (int i = 0; i < numRows; i++) {
    rows[i] = new IntArray(numColumns);
    for (int j = 0; j < numColumns; j++) {
      rows[i]->data[j] = rhs.rows[i]->data[j];
    }
  }
}
IntMatrix::~IntMatrix() {
  for (int i = 0; i < numRows; i++) {
    delete rows[i];
  }
  delete[] rows;
}
IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs) {
    IntArray ** temp_Matrix = new IntArray *[rhs.numRows];
    for (int i = 0; i < rhs.numRows; i++) {
      temp_Matrix[i] = new IntArray(rhs.numColumns);
      for (int j = 0; j < rhs.numColumns; j++) {
        temp_Matrix[i]->data[j] = rhs.rows[i]->data[j];
      }
    }
    for (int i = 0; i < numRows; i++) {
      delete rows[i];
    }
    delete[] rows;
    rows = temp_Matrix;
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
  }
  return *this;
}
int IntMatrix::getRows() const {
  return numRows;
}
int IntMatrix::getColumns() const {
  return numColumns;
}
const IntArray & IntMatrix::operator[](int index) const {
  assert(index >= 0 && index < numRows);
  return *rows[index];
}
IntArray & IntMatrix::operator[](int index) {
  assert(index >= 0 && index < numRows);
  return *rows[index];
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if (this == &rhs) {
    return true;
  }
  if (rhs.numRows != numRows || rhs.numColumns != numColumns) {
    return false;
  }
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numColumns; j++) {
      if (rows[i]->data[j] != rhs.rows[i]->data[j]) {
        return false;
      }
    }
  }
  return true;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
  IntMatrix ans(numRows, numColumns);
  for (int k = 0; k < numRows; k++) {
    for (int j = 0; j < numColumns; j++) {
      ans.rows[k]->data[j] = rows[k]->data[j] + rhs.rows[k]->data[j];
    }
  }
  return ans;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  s << "[ ";
  for (int i = 0; i < rhs.numRows; i++) {
    s << *rhs.rows[i];
    if (i < rhs.numRows - 1) {
      s << "," << std::endl;
    }
  }
  s << " ]";
  return s;
}
