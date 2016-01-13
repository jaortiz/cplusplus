/**
 *Name: Jeremy Ortiz z3461601
 *
 *Sparse Matrix Class
 */
#include "SMatrix.h"

using namespace std;

/**
 *Overloading the output operator to output the matrix to the output stream.
 *Returns a reference to the output stream.
 *
 */
std::ostream& operator<<(std::ostream &os, const SMatrix &m) {

   if(m.rows() != 0 || m.cols() != 0) {      //Ensure empty matrices aren't printed
      os << "(" << m.rows() << "," << m.cols() << "," << m.k_ << ")";    //(m,n,k)
      
      for(auto it = m.ridx_.cbegin();it != m.ridx_.cend();++it) {    //Loop through ridx_
         os << endl; 
         auto nElements = it->second.first + it->second.second; 
         for(auto i = it->second.first;i < nElements;++i) {
            auto row = it->first;
            auto col = m.cidx_[i];
            auto val = m.vals_[i];
            os << "(" << row << "," << col << "," << val;
            if((i + 1) == nElements) {    //For auto-marking purposes
               os << ")";
            } else {
               os << ") ";
            }         
         
         }
      } 
   }
  return os;
}

//CONSTRUCTORS
//------------------------
/**
 *The default constructor for the class, which if not given a size, creates a 1x1 matrix.
 *If a size is given, it delegates its construction to the constructor below.
 *
 */
SMatrix::SMatrix(size_type size) : SMatrix::SMatrix(size,size) { }   


/**
 *Constructor given the number of rows and columns of a matrix.
 *
 */
SMatrix::SMatrix(size_type m, size_type n) {
   m_ = m;     //setting private members
   n_ = n;
   k_ = 0;
   
   double temp = ceil((m*n)/5.0);
   double size = min(temp,1000.0);     //initial array size amortisation
   arrSize_ = size;
   vals_ = new int[arrSize_];          //dynamically allocating vals_ and cidx_ arrays
   cidx_ = new size_type[arrSize_];
}


/**
 *Constructor for a matrix given an intializer list.
 *
 */
SMatrix::SMatrix(const std::initializer_list<std::initializer_list<int>>& init) {

   //finding matrix dimensions
   bool matrixDim = true;
   for(auto it = init.begin(); it != init.end(); ++ it) {      //Looping through first initializer
      int i = 0;                                                  //list
      int col = 0;
      int row = 0;
      int val = 0;
      for(auto inner = it->begin(); inner != it->end(); ++inner) {   //Loop though inner 
         if(i == 0) {                                                // initializer list
            row = *inner;
         } else if(i == 1) {
            col = *inner;
         } else {
            val = *inner;
         }
         ++i;
      }

      if(matrixDim == true) {     //first initialiser list contains dimensions
         matrixDim = false;
         m_ = row;
         n_ = col;
         k_ = 0;
         
         double temp = ceil((row*col)/5.0);
         double size = min(temp,1000.0);     //initial array size amortisation
         arrSize_ = size;
         vals_ = new int[arrSize_];   
         cidx_ = new size_type[arrSize_];    //dynamically allocating vals_ and cidx_ arrays
         
      } else {
         setVal(row,col,val);    //otherwise set the values of the matrix
      }
   }
}

/**
 *Constructor given the input stream (cin).
 *
 */
SMatrix::SMatrix(std::istream& stream) {
   
   bool matrixDim = true;
   string line;
   
   while(getline(stream,line)) {
      replace(line.begin(),line.end(),'(',' ');    //replacing unecessary characters
      replace(line.begin(),line.end(),')',' ');       //with whitespace for use with 
      replace(line.begin(),line.end(),',',' ');          //istringstream
      istringstream iss(line);
      
      int n = 0;
      int i = 1;
      int col = 0;
      int row = 0;
      int val = 0;
      while(iss >> n) {    //getting matrix values from the string and converting to int
         if((i%3) == 1) {     //if true, is a row number
            row = n;
         } else if((i%3) == 2) { //if true, is a column number
            col = n;
         } else if((i%3) == 0) { //if true is a value
            val = n;
            if(matrixDim == true) {    // for the first string which contains the dimensions
               matrixDim = false;
               m_ = row;
               n_ = col;
               k_ = 0;
               
               double temp = ceil((row*col)/5.0);
               double size = min(temp,1000.0);     //initial array size amortisation
               arrSize_ = size;
               vals_ = new int[arrSize_];          //dynamically allocating vals_ and cidx_ arrays
               cidx_ = new size_type[arrSize_];
            } else {
               setVal(row,col,val);    //otherwise set the values of the matrix
            }
         }
         ++i;
      }
   }

}


/**
 *Copy constructor that creates a copy of a given matrix using copy semantics, that leaves
 *matrix b unchanged.
 *
 */
SMatrix::SMatrix(const SMatrix& b) {

   m_ = b.m_;  //rows
   n_ = b.n_;  //colmns
   k_ = b.k_;  //number of non zero elements
   arrSize_ = b.arrSize_; //array size;

   vals_ = new int[arrSize_];          //dynamically allocating arrays
   cidx_ = new size_type[arrSize_];
   
   memcpy(vals_,b.vals_,sizeof(int) *arrSize_);  //copying vals_
   memcpy(cidx_,b.cidx_,sizeof(size_type)*arrSize_);  //copying cidx_

   ridx_ = b.ridx_;           //copying ridx_ and rowOrder
   rowOrder_ = b.rowOrder_;

}

/**
 *Move constructor that creates a copy of a given matrix using move semantics, that moves the 
 *contents from b to a, but leaves matrix b in a valid state and sets its size to 0x0.
 */
SMatrix::SMatrix(SMatrix&& b) {
   m_ = b.m_;  //rows
   n_ = b.n_;  //colmns
   k_ = b.k_;  //number of non zero elements
   arrSize_ = b.arrSize_; //array size;

   b.m_ = 0;      //setting b matrix members to 0, leaving it in a valid state
   b.n_ = 0;
   b.k_ = 0;
   b.arrSize_ = 0;

   vals_ = b.vals_;   //pointing to b.vals
   b.vals_ = nullptr;   //b.vals_ now points to null

   cidx_ = b.cidx_;     //pointing to b.cidx_
   b.cidx_ = nullptr;   //b.cidx_ now points to null
   
   ridx_ = b.ridx_;     //copying ridx_
   rowOrder_ = b.rowOrder_;   //copy rowOrder
   
   b.ridx_.clear();   //clearing b.ridx_ contents
   b.rowOrder_.clear();  //clearing b.rowOrder contents   

}


/**
 *SMatrix destructor
 *
 */
SMatrix::~SMatrix() {

   delete [] vals_;     //deallocating vals_
   vals_ = NULL;

   delete [] cidx_;     //deallocating cidx_
   cidx_ = NULL;
   
}

//OPERATORS
//------------------
/**
 *Overloading the () operator, which given a column number and row number, returns the value
 *at that location give they are in the bound of the matrix. If the row and column number
 *is not within the matrix boundaries, a "Matrix bound error" is thrown.
 */
int SMatrix::operator()(size_type i, size_type j) const throw(MatrixError) {
   int val = 0;
   if(i > m_ && j > n_) {     //check whether the row and column is in bounds
      throw MatrixError("Matrix bound error");     //throw bound error
    }
   
   if(ridx_.find(i) != ridx_.cend()) {    //check if the row is in the map
      for(SMatrix::size_type k = 0; k < ridx_.at(i).second; ++k) {   //search through row for col
         if(cidx_[ridx_.at(i).first + k] == j) {      //if column found, set val
            val = vals_[ridx_.at(i).first + k];
         }
      }
   }
   return val;
}


/**
 *Overloading the = operator, in order to use copy assignment for the matrix. Via copy semantics
 *'a' becomes a copy of 'b' and returns a reference to 'a'.
 *
 */
SMatrix& SMatrix::operator=(const SMatrix& b) {
   if(this != &b) {
      m_ = b.m_;  //rows
      n_ = b.n_;  //colmns
      k_ = b.k_;  //number of non zero elements
      arrSize_ = b.arrSize_; //array size;
      
      delete [] vals_;           //deallocate previous vals_
      vals_ = new int[arrSize_];   //dynamically allocate new vals_
      delete []cidx_;         //deallocate previous cidx_
      cidx_ = new size_type[arrSize_];    //dynamically allocate new cidx_
      
      memcpy(vals_,b.vals_,sizeof(int) *arrSize_);  //copying vals
      memcpy(cidx_,b.cidx_,sizeof(size_type)*arrSize_);  //copying cidx
      
      ridx_ = b.ridx_;     //copy ridx_
      rowOrder_ = b.rowOrder_;   //copy rowOrder_

   }
   return *this;
}

/**
 *Overloading the = operator, in order to use move assignment for the matrix. Via move semantics
 *the contents of 'b' are moved in to 'a' and 'b' is left in an empty but valid state.
 *Returns a reference to 'a'
 *
 */
SMatrix& SMatrix::operator=(SMatrix&& b) {
   if(this != &b) {
      m_ = b.m_;  //rows
      n_ = b.n_;  //colmns
      k_ = b.k_;  //number of non zero elements
      arrSize_ = b.arrSize_; //array size;

      b.m_ = 0;      //setting b matrix members to 0, leaving it in a valid state
      b.n_ = 0;
      b.k_ = 0;
      b.arrSize_ = 0;

      delete [] vals_;
      vals_ = b.vals_;   //pointing to b.vals
      b.vals_ = nullptr;   //b.vals_ now points to null

      delete [] cidx_;
      cidx_ = b.cidx_;     //pointing to b.cidx_
      b.cidx_ = nullptr;   //b.cidx_ now points to null
      
      ridx_ = b.ridx_;     //copying ridx_
      rowOrder_ = b.rowOrder_;   //copy rowOrder
      
      b.ridx_.clear();   //clearing b.ridx_ contents
      b.rowOrder_.clear();  //clearing b.rowOrder contents   
      

   }
   return *this;
}


/**
 *Overloading the += operator on the precondition the matrices are the same size.
 *Takes advantage of sparse matrix representation by only adding the non-zero elements of b to a
 *since elements not used in addition with a are not changed or touched
 *Returns a reference to 'a'.
 *
 */
SMatrix& SMatrix::operator+=(const SMatrix& b) throw(MatrixError) {
   
   if(cols() != b.cols() || rows() != b.rows()) {  //check the matrices are the same size
      throw MatrixError("Matrix size error");      //if not throw size error
   } 
   
   if(this != &b) {
      for(auto it = b.ridx_.cbegin();it != b.ridx_.cend();++it) {   //Loop through b's rows   
         int row = it->first;                                        
         int nElements = it->second.first + it->second.second;
         for(int pos = it->second.first; pos < nElements; ++pos) {   //Loop through b's columns
            int val = (*this)(row,b.cidx_[pos]) + b.vals_[pos];      //adding b to a.
            setVal(row,b.cidx_[pos],val);               
         }
      }
   }
   return *this;      
}


/**
 *Overloading the += operator on the precondition the matrices are the same size.
 *Takes advantage of sparse matrix representation by only subtracitng the non-zero elements of b 
 *from a, since elements not used in subtraction with b are not changed or touched.
 *Returns a reference to 'a'.
 *
 */
SMatrix& SMatrix::operator-=(const SMatrix& b) throw(MatrixError) {
   
   if(cols() != b.cols() || rows() != b.rows()) {  //check the matrices are the same size
      throw MatrixError("Matrix size error");      //if not throw size error
   } 

   if(this != &b) {
      for(auto it = b.ridx_.cbegin();it != b.ridx_.cend();++it) {      //Loop through b's rows  
         int row = it->first;
         int nElements = it->second.first + it->second.second;
         for(int pos = it->second.first; pos < nElements; ++pos) {      //Loop through b's columns
            int val = (*this)(row,b.cidx_[pos]) - b.vals_[pos];       //subtracting b from a.
            setVal(row,b.cidx_[pos],val);
         }
      }
   }
   return *this;      
}


/**
 *Overloading the += operator on the precondition the matrices are the same size.
 *Takes advantage of sparse matrix representation by only multiplying the non-zero elements of a 
 *to b since non-zeroes not already multiplied will become zero.
 *Returns a reference to 'a'.
 *
 */
SMatrix& SMatrix::operator*=(const SMatrix& b) throw(MatrixError) {
   if(cols() != b.rows()) {
      throw MatrixError("Matrix size error");   
   } 

   SMatrix c(rows(),b.cols());    //dimensions of new 'a' matrix 
   
   for(auto it = ridx_.cbegin();it != ridx_.cend();++it) {     //loop through a's rows
      int row = it->first;
      int nElements = it->second.first + it->second.second;
      for(SMatrix::size_type i = 0; i < b.cols(); ++i) {    //loop through b's columns
         int col = i;   
         int val = 0;
         for(int pos = it->second.first; pos < nElements; ++pos) {   //loop through a's columns
            val += vals_[pos] * b(cidx_[pos],i);         //multiply 'a' value to corresponding
         }                                               //'b' value
         if(val != 0) {
            c.setVal(row,col,val);
         }
      }
   }
   
   *this = move(c);     //moving temporary matrix to a
   return *this;
   
}

/**
 *Set value method of SMatrix class, which given a row and column number with the matrix 
 *boundaries, sets the passed value to the given location. 
 *Returns a bool value of whether more memory was allocated.
 *
 */
bool SMatrix::setVal(size_type row, size_type col, int val) throw(MatrixError) {
   bool valSet = false;
   if(row > m_ && col > n_) {
      throw MatrixError("Matrix bound error");  //CHANGE LATER??

   } else {
      if(ridx_.find(row) != ridx_.cend()) {   //row already in ridx
         int nElements = ridx_[row].first + ridx_[row].second;   
         
         //finding insert position
         int pos;
         for(pos = ridx_[row].first;pos < nElements;++pos) {
            if(col <= cidx_[pos]) {  
               break;
            }
         }
      
         //if at near capacity double the size of the arrays 
         if(k_ >= arrSize_) { //arrSize_ - 2) {     
            valSet = true;    //returns true if additional memory must be allocated
            int* tempVal = vals_;
            size_type* tempCidx = cidx_;

            arrSize_ = arrSize_*2;
            vals_ = new int[arrSize_];   
            cidx_ = new size_type[arrSize_];
            for(size_type i = 0;i < k_;++i) {
               vals_[i] = tempVal[i];
               cidx_[i] = tempCidx[i];
            }   
         } 
         
         //check if overriding a non zero
         if(col == cidx_[pos]) {
            if(val == 0) {
               if(ridx_[row].second == 1) {
                  bool start = false;
                  for(auto it = rowOrder_.begin(); it != rowOrder_.end();++it) {
                     if(*it == row) {
                        start = true;
                     } else if(start == true) {
                        --ridx_[*it].first;
                     }
                  }  
                  ridx_.erase(row); 
                  rowOrder_.erase(remove(rowOrder_.begin(),rowOrder_.end(),row),rowOrder_.end());
                  
               } else {
                  //if(ridx[row].first == col) {
                    //ridx[row].first = cidx_[pos+1]          
                  //}
                  --ridx_[row].second;
               }
               //shift everything down 1 in cidx and vals
               --k_;
               for(SMatrix::size_type i = pos; i < k_; ++i) {
                  vals_[i] = vals_[i+1];
                  cidx_[i] = cidx_[i+1];
               }
               vals_[k_+1] = 0;
               cidx_[k_+1] = 0;
               
               //updating ridx
               bool start = false;
               for(auto it = rowOrder_.begin(); it != rowOrder_.end();++it) {
                  if(*it == row) {
                     start = true;
                  } else if(start == true) {
                     --ridx_[*it].first;
                  }
               }
            } else {
               vals_[pos] = val;
            }
         } else {   
            //shifting arrays to make space for new insert
            if(val != 0) {
               for(int i = k_; i > pos;--i) {
                  vals_[i] = vals_[i-1];
                  cidx_[i] = cidx_[i-1];
               }
               vals_[pos] = val;    //inserting new element
               cidx_[pos] = col;
               ++k_;
               ++ridx_[row].second;
               
               //updating ridx
               bool start = false;
               for(auto it = rowOrder_.begin(); it != rowOrder_.end();++it) {
                  if(*it == row) {
                     start = true;
                  } else if(start == true) {
                     ++ridx_[*it].first;
                  }
               }
            }
         }

      } else {
         if(val != 0) {      //avoid creating new entry if it is a non zero element
            if(k_ > arrSize_) {
               valSet = true;    //returns true if additional memory must be allocated
               int* tempVal = vals_;
               size_type* tempCidx = cidx_;

               arrSize_ = arrSize_*2;
               vals_ = new int[arrSize_];   
               cidx_ = new size_type[arrSize_];
               for(size_type i = 0;i < k_;++i) {
                  vals_[i] = tempVal[i];
                  cidx_[i] = tempCidx[i];
               }   
            } else {
               vals_[k_] = val;    //setting val 
               cidx_[k_] = col;    //setting corresponding column        
               pair<size_t, unsigned int> newPair(k_,1);   //new pair to add to ridx
               ridx_[row] = newPair;
               ++k_;
   
               rowOrder_.push_back(row);
            }
         }
     }
   }         
   return valSet; 
}


//FRIENDS
//-----------------------
/**
 *Overloading the '==' operator.
 *Returns a bool value whether the matrices are equal 
 *
 */
bool operator==(const SMatrix& a, const SMatrix& b) {
   bool equal = true;
   if(a.rows() != b.rows() || a.cols() != b.cols()) {    //If the matrices do not have the 
      equal = false;                                      //same dimensions                   
   } else {
      b.begin();
      for(a.begin(); !a.end(); a.next()) {      //compare all the values of a to b
         if(a.value() != b.value()) {
            equal = false;
         }
         b.next();
      }     
   }
   return equal;   
}


/**
 *Overloading the '!=' operator.
 *Returns a bool value whether the matrices are not equal 
 *
 */
bool operator!=(const SMatrix& a, const SMatrix& b) {
   bool notEqual = false;
   if(a.rows() != b.rows() || a.cols() != b.cols()) {    //If the matrices have different 
      notEqual = true;                                      //dimensions            
   } else {
      b.begin();
      for(a.begin(); !a.end() && !notEqual; a.next()) {  //Compare all values of a to b until
         if(a.value() != b.value()) {                       //not matching values are          
            notEqual = true;                                   //found
         }
         b.next();
      }    
   } 
   return notEqual;   
}


/**
 *Overloading the '*' operator. Only works when matrix a's columns are equal to matrix b's 
 *rows, otherwise there is a size error.
 *Returns a new matrix equal to a * b
 *
 */
SMatrix operator*(const SMatrix& a, const SMatrix& b) throw(MatrixError) {
   if(a.cols() != b.rows()) {    //Check whether a's columns are equal to b's rows
      throw MatrixError("Matrix size error");      //if not throw size error
   } 
   
   SMatrix c(a.rows(),b.cols());    //dimensions of new matrix 
   
   for(auto it = a.ridx_.cbegin();it != a.ridx_.cend();++it) {    //Loop through a's rows
      int row = it->first;
      int nElements = it->second.first + it->second.second;
      for(SMatrix::size_type i = 0; i < b.cols(); ++i) {    //Loop through b's columns
         int col = i;   
         int val = 0;
         for(int pos = it->second.first; pos < nElements; ++pos) {   //Loop through a's columns
            val += a.vals_[pos] * b(a.cidx_[pos],i);      //adding the multiplications to 
         }                                                  //val
         if(val != 0) {
            c.setVal(row,col,val);
         }

      }
   }

   return c;
}


/**
 *Overloading the '+' operator. Only works when both matrices have equal dimensions
 *Returns a new matrix equal to a + b
 *
 */
SMatrix operator+(const SMatrix& a, const SMatrix& b) throw(MatrixError) {
   if(a.cols() != b.cols() || a.rows() != b.rows()) { //Check whether or not dimensions are equal
      throw MatrixError("Matrix size error");      //if not throw size error
   } 
   
   SMatrix c(a.rows(),a.cols());       //dimensions of new matrix
   
   b.begin();
   for(a.begin(); !a.end(); a.next()) {      //Loop through all values of a and b, and add 
      int val = a.value() + b.value();          //together
      c.setVal(a.rowPointer_,a.colPointer_,val);      //add new addition to new matrix
      b.next();
   
   }
   return c;  
}


/**
 *Overloading the '-' operator. Only works when both matrices have equal dimensions
 *Returns a new matrix equal to a - b
 *
 */
SMatrix operator-(const SMatrix& a, const SMatrix& b) throw(MatrixError) {
   if(a.cols() != b.cols() || a.rows() != b.rows()) { //Check whether or not dimensions are equal
      throw MatrixError("Matrix size error");         //if not throw size error
   } 
   
   SMatrix c(a.rows(),a.cols());    //dimensions of new matrix
   
   b.begin();
   for(a.begin(); !a.end(); a.next()) {      //Loop through all values of a and b, and subtract 
      int val = a.value() - b.value();
      c.setVal(a.rowPointer_,a.colPointer_,val);   //add new subtraction to new matrix
      b.next();
   
   }
   return c;  
}

/**
 *Transpose method, that transposes a matrix.
 *Returns a new matrix equal to the transpose of a.
 */
SMatrix transpose(const SMatrix& a) {

   SMatrix c(a.rows(),a.cols());
   
   for(auto it = a.ridx_.cbegin();it != a.ridx_.cend();++it) { //Loop through a's rows
      int row = it->first;
      int nElements = it->second.first + it->second.second;
      for(int pos = it->second.first; pos < nElements; ++pos) {   //Loop through a's columns
         c.setVal(a.cidx_[pos],row,a.vals_[pos]);     //add value to new matrix                  
      }                                               //with rows and columns swapped
   }
   return c;
}


//'Iterators'
//-----------------------

/**
 *Begin member function which provides a fake iterator to the beginning to the matrix.
 *
 */
void SMatrix::begin() const {
   rowPointer_ = 0;     //fake iterator which tracks the row number
   colPointer_ = 0;     //fake iterator which tracks the column number
}

/**
 *Begin member function which provides a fake iterator to the end to the matrix.
 *Returns a bool value whether or not the end of a matrix has been reached
 *
 */
bool SMatrix::end() const {
   bool end = false;
   if(rowPointer_ == m_ || colPointer_ == n_) { //check if the 'pointer' has reached the end
      end = true;                               //of the matrix
   } 
   
   return end;
}

/**
 *Next member function which provides a fake iterator increment, by incrementing the row
 *and column 'pointers'.
 *
 */
void SMatrix::next() const {
   if(colPointer_ == (n_ - 1)) {    //if the end of a column, move to the next row
      colPointer_ = 0;              //and go back to column 0.
      ++rowPointer_;
   } else {
      ++colPointer_;    //otherwise incremenet the column 'pointer'
   }
}


/**
 *Value member function which provides a fake iterator to the matrix value, by searching through
 *the sparse matrix implementation to see if the 'pointer' points to a non zero.  
 *Returns the value if found in the sparse matrix representation otherwise a zero.
 *
 */
int SMatrix::value() const {
   int val = 0;
   
   if(ridx_.find(rowPointer_) != ridx_.cend()) {
      for(SMatrix::size_type i = 0; i < ridx_.at(rowPointer_).second; ++i) {  //search current 
         if(cidx_[ridx_.at(rowPointer_).first + i] == colPointer_) {    //'iterator' row for
            val = vals_[ridx_.at(rowPointer_).first + i];               //current column
         }
      }
   }
   return val;
}


/**
 *Constructs the nxn identity matrix where the diagonals of a matrix are equal
 *to 1 and given n > 0.
 *Returns the constructed nxn identity matrix.
 */
SMatrix SMatrix::identity(size_type n) {
   SMatrix a(n,n);
   for(size_type i = 0; i < n; i++) {
      a.setVal(i,i,1);     //set diagonals to 1

   }
   return a;
}


