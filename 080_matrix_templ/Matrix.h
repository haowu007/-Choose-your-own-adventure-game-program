#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

//YOUR CODE GOES HERE

template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;

 public:
  Matrix() : numRows(0), numColumns(0), rows(0) {}
  Matrix(int r, int c) : numRows(r), numColumns(c), rows(r) {
    typename std::vector<std::vector<T> >::iterator it;
    for (it = rows.begin(); it != rows.end(); it++) {
      *it = std::vector<T>(c);
    }
  }
  Matrix(const Matrix & rhs) :
      numRows(rhs.numRows),
      numColumns(rhs.numColumns),
      rows(rhs.rows) {}  //std::vector has its own copy constructor

  Matrix & operator=(const Matrix & rhs) {
    if (this != &rhs) {
      rows = rhs.rows;
      numRows = rhs.numRows;
      numColumns = rhs.numColumns;
    }
    return *this;
  }
  int getRows() const { return numRows; }
  int getColumns() const { return numColumns; }
  const std::vector<T> & operator[](int index) const {
    assert(index >= 0 && index < numRows);
    return rows[index];
  }
  std::vector<T> & operator[](int index) {
    assert(index >= 0 && index < numRows);
    return rows[index];
  }

  bool operator==(const Matrix & rhs) const {
    return numRows == rhs.numRows && numColumns == rhs.numColumns && rows == rhs.rows;
  }

  Matrix operator+(const Matrix & rhs) const {
    assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
    Matrix ans(numRows, numColumns);
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        ans.rows[i][j] = rows[i][j] + rhs.rows[i][j];
      }
    }
    return ans;
  }

  template<typename U>
  friend std::ostream & operator<<(std::ostream & s, const Matrix<U> & rhs);
};

template<typename U>
std::ostream & operator<<(std::ostream & s, const Matrix<U> & rhs) {
  s << "[ ";
  for (int i = 0; i < rhs.numRows; i++) {
    for (int j = 0; j < rhs.numColumns; j++) {
      if (j == 0) {
        s << "{";
      }
      s << rhs.rows[i][j];
      if (j < rhs.numColumns - 1) {
        s << ", ";
      }
      if (j == rhs.numColumns - 1) {
        s << "}";
      }
    }
    if (i < rhs.numRows - 1) {
      s << "," << std::endl;
    }
  }
  s << " ]";
  return s;
}
#endif
