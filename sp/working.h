#ifndef SMATRIX_H
#define SMATRIX_H

#include <exception>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <algorithm>
#include <cstddef>
#include <cmath>
#include <cstring>
#include <sstream>

// matrix error class
class MatrixError : public std::exception {
 public:
  MatrixError(const std::string& what_arg) : _what(what_arg) { }
  virtual const char* what() const throw() { return _what.c_str (); }
  virtual ~MatrixError() throw() { }
 private:
  std::string _what;
};


// sparse matrix class
class SMatrix {
 public:
  // public interface
  // *** YOU SHOULD NOT MODIFY THE PUBLIC INTERFACE IN ANY WAY! ***

  // types
  typedef size_t size_type;

  // friends
  friend bool operator==(const SMatrix&, const SMatrix&);
  friend bool operator!=(const SMatrix&, const SMatrix&);
  friend SMatrix operator+(const SMatrix&, const SMatrix&) throw(MatrixError); 
  friend SMatrix operator-(const SMatrix&, const SMatrix&) throw(MatrixError); 
  friend SMatrix operator*(const SMatrix&, const SMatrix&) throw(MatrixError); 
  friend SMatrix transpose(const SMatrix&);
  friend std::ostream& operator<<(std::ostream&, const SMatrix&);
  
  // constructors
  SMatrix(size_type size = 1); // the default constructor
  SMatrix(size_type, size_type);
  SMatrix(std::istream&);
  SMatrix(const SMatrix&);   // copy
  SMatrix(SMatrix&&);        // move
  SMatrix(const std::initializer_list<std::initializer_list<int>>&); // initializer_list

  // operators  
  SMatrix& operator=(const SMatrix&);  // copy 
  SMatrix& operator=(SMatrix&&);       // move
  SMatrix& operator+=(const SMatrix&) throw(MatrixError);
  SMatrix& operator-=(const SMatrix&) throw(MatrixError);
  SMatrix& operator*=(const SMatrix&) throw(MatrixError);
  int operator()(size_type, size_type) const throw(MatrixError);
  
  // operations
  inline size_type rows() const { return m_; };
  inline size_type cols() const { return n_; };
  bool setVal(size_type, size_type, int) throw(MatrixError);

  // `iterator' operations
  void begin() const;
  bool end() const;
  void next() const;
  int value() const;

  // destructor
  ~SMatrix();
  
  // static members  
  static SMatrix identity(size_type);

 private:
  // private data members
   int *vals_;
   size_type *cidx_;
   std::map< size_type, std::pair<size_t, unsigned int> > ridx_;
   
   size_type m_,n_,k_,arrSize_;  //m_ = rows, n_ = columns, k_ = non-zero elements, 
                                    //arrSize_ = size of arrays
   mutable size_type rowPointer_,colPointer_; //fake pointers to iterate the matrix
   
   std::vector<size_type> rowOrder_;   //order of rows stored in vals_ and cidx_
};

#endif
