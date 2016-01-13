/**
 *Btree iterator class, const and non-const versions
 *
 *By Jeremy Ortiz (z3461601)
 */
#ifndef BTREE_ITERATOR_H
#define BTREE_ITERATOR_H

#include <iterator>

/**
 * You MUST implement the btree iterators as (an) external class(es) in this file.
 * Failure to do so will result in a total mark of 0 for this deliverable.
 **/

// iterator related interface stuff here; would be nice if you called your
// iterator class btree_iterator (and possibly const_btree_iterator)

using namespace std;

template <typename T> class btree;
template <typename T> class btree_iterator;
template <typename T> class const_btree_iterator;

template <typename T> class btree_iterator {
   
   public:

   friend class const_btree_iterator<T>;

   //iterator traits
   typedef ptrdiff_t             difference_type;
   typedef forward_iterator_tag  iterator_category;
   typedef T                     value_type;
   typedef T*                    pointer;
   typedef T&                    reference;

   reference operator*() const;
   pointer operator->() const { return &(operator*()); }
   
   //pre-fix
   //increment and return
   btree_iterator& operator++();
   btree_iterator& operator--();

   //post-fix
   //return then increment i.e. create temp to return and increment curr
   btree_iterator operator++(int);
   btree_iterator operator--(int);

   //comparison between btree_iterators
   bool operator==(const btree_iterator& other) const;
   bool operator!=(const btree_iterator& other) const { return !operator==(other); }

   //comparison between btree_iterator and const_btree_iterator
   bool operator==(const const_btree_iterator<T>& other) const;
   bool operator!=(const const_btree_iterator<T>& other) const { return !operator==(other); }
      
   //iterator constructor
   btree_iterator(typename btree<T>::Node *pointee = nullptr, int elementPos = 0) : pointee_(pointee), elemPos_(elementPos) {}
   
   private:
      typename btree<T>::Node *pointee_;

      //element position within the node
      int elemPos_;

      typename btree<T>::Node *tempPointee_;
      int tempElemPos_;
};

template <typename T> class const_btree_iterator {
   
   public:

   friend class btree_iterator<T>;   
   
   //iterator traits
   typedef ptrdiff_t             difference_type;
   typedef forward_iterator_tag  iterator_category;
   typedef T                     value_type;
   typedef const T*                    pointer;
   typedef const T&                    reference;

   reference operator*() const;
   pointer operator->() const { return &(operator*()); }
   
   //pre-fix
   //increment and return
   const_btree_iterator& operator++();
   const_btree_iterator& operator--();

   //post-fix
   //return then increment i.e. create temp to return and increment curr
   const_btree_iterator operator++(int);
   const_btree_iterator operator--(int);

   //comparison between const_btree_iterators
   bool operator==(const const_btree_iterator& other) const;
   bool operator!=(const const_btree_iterator& other) const { return !operator==(other); }

   //comparison between const_btree_iterator and btree_iterator
   bool operator==(const btree_iterator<T>& other) const;
   bool operator!=(const btree_iterator<T>& other) const { return !operator==(other); }

   //const iterator constructor
   const_btree_iterator(typename btree<T>::Node *pointee = nullptr, int elementPos = 0) : pointee_(pointee), elemPos_(elementPos) {}
   
   //convert btree_iterator to const_btree_iterator
   const_btree_iterator(const btree_iterator<T>& other) : pointee_(other.pointee_), elemPos_(other.elemPos_) {}
   
   private:
      typename btree<T>::Node *pointee_;
      //element position within the node
      int elemPos_;

      typename btree<T>::Node *tempPointee_;
      int tempElemPos_;
};



#include "btree_iterator.tem"

#endif
