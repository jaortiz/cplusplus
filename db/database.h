/**
 *Name: Jeremy Ortiz z3461601
 *
 *Database Class Header
 */

#ifndef DATABASE_H
#define DATABASE_H
#include <algorithm>
#include <iostream>
#include <string>

#include "fraction.h"
#include "utility.h"
#include "record.h"

using namespace std;

template <class value> class Database {

   public:
   Database();
   ~Database();

   int numRecords() const; 
   int numSelected() const;   
   void write(ostream& out, DBScope scope) const;
   void read(istream& in); 
   void deleteRecords(DBScope scope);  
   void selectAll();    
   void deselectAll();  
   void select(DBSelectOperation selOp, const string& attr, DBQueryOperator op, const value& val);

   private:
   vector<Record<value>> records_;
   int numSelected_;
};

#include "database.tem"

#endif
