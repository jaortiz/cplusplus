#include <algorithm>
#include <iostream>
#include <iterator>

#include "btree.h"

using namespace std;

int main(void) {
   
   btree<int> b(3);
   
   b.insert(2);
   b.insert(5);
   b.insert(7);

   
   b.insert(0);
   b.insert(1);
   
   
   b.insert(3);
   b.insert(4);
   
   
   b.insert(6);
   
   b.insert(8);
   b.insert(9);   
   b.insert(10);
   
   b.insert(11);
   b.insert(12);
   
   /*
   btree<int> b(1);
   b.insert(2);
   b.insert(3);
   b.insert(0);
   */
//-------------------------------------------------------------------------------------------
//COPY/MOVE TESTS
//-------------------------------------------------------------------------------------------
   /*
   cout << "Original tree" << endl;
   
   for(btree<int>::iterator iter = b.begin(); iter != b.end(); ++iter) {
   
    cout << *iter << " ";
   }
   
   cout << endl << endl;
   
   //testing copy
   
   btree<int> c = b;
   
   cout << "Original tree" << endl;
   for(btree<int>::iterator iter = b.begin(); iter != b.end(); ++iter) {
    cout << *iter << " ";
   }
   cout << endl;

   
   cout << "Copied tree" << endl;
   for(btree<int>::iterator iter = c.begin(); iter != c.end(); ++iter) {
    cout << *iter << " ";
   }
   
   cout << endl << endl;
   
   btree<int> d = move(b);
   
   cout << "Moved tree" << endl;
   for(btree<int>::iterator iter = d.begin(); iter != d.end(); ++iter) {
    cout << *iter << " ";
   }
   cout << endl;
   */
   
//-------------------------------------------------------------------------------------
//FIND TEST
//------------------------------------------------------------------------------------
   /*
   auto it = b.find(1);
   if(it != b.end()) {
      cout << "element found" << endl;  
   } else {
      cout << "element not found" << endl;  
   }
   */

//-------------------------------------------------------------------------------------
//REVERSE TEST
//-------------------------------------------------------------------------------------
   /*
   for(auto iter = b.rbegin(); iter != b.rend(); ++iter) {
      cout << *iter << " ";
   }   
   cout << endl;
   */
   /*
   auto it = b.rend();
   --it;
   for(int i = 0; i < 3; ++i) {
      cout << *it << " " ;
      --it;
   }
   cout << endl;
   */

//--------------------------------------------------------------------------------------
//PRE-DECREMENT TEST
//--------------------------------------------------------------------------------------
   /*
   auto it = b.end();
   --it;
   
   while(true) {
      if(it == b.begin()) {
         break;
      } else {
         cout << *it << " ";
      }
      --it;
   }
   
   cout << *it;
   cout << endl;
  */
  
   
//------------------------------------------------------------------------------------
//CONST TEST
//------------------------------------------------------------------------------------
   /*
   for(btree<int>::const_iterator iter = b.cbegin(); iter != b.cend(); ++iter) {
   
    cout << *iter << " ";
   }
   cout << endl;
   */
//------------------------------------------------------------------------------------
//OUTPUT OPERATOR TEST
//------------------------------------------------------------------------------------
   //cout << b << endl;
//-----------------------------------------------------------------------------------
//CHAR TEST
//-------------------------------------------------------------------------------------
   /*
   btree<char> c(4);
   c.insert('G');
   c.insert('M');
   c.insert('P');
   c.insert('X');

   c.insert('B');

   c.insert('N');

   c.insert('R');
   c.insert('S');
   c.insert('T');
   c.insert('W');
   
   c.insert('Z');
   
   c.insert('Q');
   c.insert('U');
   c.insert('V');
   
   for(auto iter = c.begin(); iter != c.end(); ++iter) {
   
    cout << *iter << " ";
   }
   cout << endl;
   cout << c << endl;
   */
   return 0;
}
