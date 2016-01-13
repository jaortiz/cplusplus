//try and catch exceptions

try {
   if(i > m_ && j > n_) {
      
      throw MatrixError("Matrix bound error: (");
   }
} catch(MatrixError& e) {
   cout << e.what() << i << "," << j << ") entry of " << m_ << " x " << n_ << "matrix" <<endl;
  
}   
return 1;

