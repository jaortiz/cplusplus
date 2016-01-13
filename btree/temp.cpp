//overloading pre-increment
template <typename T>
btree_iterator<T>& btree_iterator<T>::operator++() {
   
   
   if(pointee_->hasChildAt(elemPos_ + 1)) {   //check if node element has a child to its right
      pointee_ = pointee_->getChild(elemPos_ + 1); //move to right node
      elemPos_ = 0; //point to the first element in a node

      //go as far left as you can
      while(pointee_->hasChildAt(0)) {      
         pointee_ = pointee_->getChild(0);
      }
      
   } else if(elemPos_ < pointee_->size() - 1) { //otherwise move to next element in node
      ++elemPos_;
   } else if(pointee_->hasParent() && elemPos_ == pointee_->size() - 1) {
      tempElemPos_ = pointee_->getParentPos();  //using temporary pointer to check if we are
      tempPointee_ = pointee_->getParent();     //at the end
      
      
      while(tempPointee_->hasParent() && tempElemPos_ == tempPointee_->size()) { //transverse up 
         tempElemPos_ = tempPointee_->getParentPos();       
         tempPointee_ = tempPointee_->getParent();
      }

      //if reach root node and at the last element of the node
      if(!tempPointee_->hasParent() && tempElemPos_ == tempPointee_->size()) {   
         ++elemPos_;                                        
      } else {
         elemPos_ = pointee_->getParentPos();   //move back to parent position in node
         pointee_ = pointee_->getParent();   //move up a node to parent node
      }
   //case for no children on last node
   } else if(!pointee_->hasParent() && elemPos_ == pointee_->size() - 1) { 
      ++elemPos_;
   } 
   
   return *this;
}
//----------------------------------------------------------------------------------------
/*
   if(elemPos_ < pointee_->size()) {
      ++elemPos_;
   } else if(elemPos_ == pointee_->size()) {  //may or may not need this check
      pointee_ = pointee_->getParent();
      elemPos = 0;
   }
   */
   
   
   if(pointee_->hasChildAt(elemPos_ + 1)) {   //check if node element has a child to its right
      pointee_ = pointee_->getChild(elemPos_ + 1); //move to right node
      elemPos_ = 0; //point to the first element in a node

      //go as far left as you can
      while(pointee_->hasChildAt(0)) {      
         pointee_ = pointee_->getChild(0);
      }
      
   } else if(elemPos_ < pointee_->size()-1) {  //otherwise move to next element in node if can
      ++elemPos_;
   } else if(elemPos_ == pointee_->size() - 1) { //if at the end of a node
      if(pointee_->hasParent()) {      //if not already at root i.e. end is at root
         tempPointee_ = pointee_->getParent();
         tempElemPos_ = pointee_->getParentPos();
         
         while(tempPointee_->hasParent() && tempElemPos_ == tempPointee_->size()) {
            tempPointee_ = tempPointee_->getParent();
            tempElemPos_ = tempPointee_->getParentPos();
            
         }

         if(!tempPointee_->hasParent() && tempElemPos_ == tempPointee_->size()) {
            ++elemPos_;
         } else {
            pointee_ = pointee_->getParent();   //move up a node to parent node
            elemPos_ = pointee_->getParentPos();   //move back to parent position in node
         }
      } else {
         ++elemPos_;
      }
   }

//-----------------------------------------------------------------------------

