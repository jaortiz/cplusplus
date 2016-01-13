bool SMatrix::setVal(size_type row, size_type col, int val) throw(MatrixError) {
   bool valSet = false;
   if(row > m_ && col > n_) {
      throw MatrixError("Matrix bound error");  //CHANGE LATER??

   } else {
      if(ridx_.find(row) != ridx_.cend()) {   //row already in ridx
         int nElements = ridx_[row].first + ridx_[row].second;   
         //cout << ridx_[row].first << " " << ridx_[row].second << endl;         
         
         //finding insert position
         int pos;
         for(pos = ridx_[row].first;pos < nElements;++pos) {
            if(col < cidx_[pos]) {  
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
            
         //loop to find insert position
         for(int i = k_; i > pos;--i) {
            vals_[i] = vals_[i-1];
            cidx_[i] = cidx_[i-1];
         }
         vals_[pos] = val;    //inserting new element
         cidx_[pos] = col;
         ++k_;
         ++ridx_[row].second;

         //cout << "row: " << row << "num elements" << ridx_[row].second << endl;
         //cout << vals_[0] << " " << vals_[1] << " " << vals_[2] <<endl;
         //cout << cidx_[0] << " " << cidx_[1] << " " << cidx_[2] << endl;
         //cout << ridx_[row].first << " " << ridx_[row].second << endl;
            


      } else {
         if(val != 0) {      //avoid creating new entry if it is a non zero element
            if(k_ > arrSize_) {
               valSet = true;    //returns true if additional memory must be allocated
               //allocate more memory
            } else {
               vals_[k_] = val;    //setting val 
               cidx_[k_] = col;    //setting corresponding column        
               pair<size_t, unsigned int> newPair(k_,1);   //new pair to add to ridx
               ridx_[row] = newPair;
               ++k_;
            }
         }
     }
   }         
   return valSet; 
}

//old * operator
for(SMatrix::size_type i = 0; i < c.rows(); ++i) {
      for(SMatrix::size_type j = 0; j < c.cols(); ++j) {
         int val = 0;
         for(SMatrix::size_type k = 0; k < a.cols(); ++k) {
            val += a(i,k) * b(k,j);
         }
         if(val != 0) {
            c.setVal(i,j,val);
         }
      
      }   
   }   

//kinda working '+' operator
for(auto it = a.ridx_.cbegin();it != a.ridx_.cend();++it) {
      int row = it->first;
      int nElements = it->second.first + it->second.second;
      
      for(int pos = it->second.first; pos < nElements; ++pos) {
         int val = 0;
         val = a.vals_[pos] + b(row,a.cidx_[pos]);
         if(val != 0) {
            c.setVal(row,a.cidx_[pos],val);         
         }   
      } 
   }


