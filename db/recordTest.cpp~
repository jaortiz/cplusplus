#include <iostream>

#include "record.h"
#include "fraction.h"
#include "utility.h"

using namespace std;

// g++ -std=c++11 -Wall -Werror -O2 -o recordTest recordTest.cpp fraction.cpp
int main() {
   Record<Fraction> test;
   cin >> test;
   cout << test;

   //selected Test
   //cout << "is Selected: " << test.isSelected() << endl;	


   //string test
   //cout << "string test: " << test.matchesQuery("name",NotEqual,"Jingling Xue") << endl;

   //int test
   //cout << "int test: " << test.matchesQuery("retail cost",Equal,42) << endl;

   //Fraction Test
   Fraction fract (121,4);
   cout << fract << endl;
   cout << "Fraction test: " << test.matchesQuery("*",LessThan,fract) << endl;
   return 0;
}
