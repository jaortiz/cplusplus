/**
 *Name: Jeremy Ortiz z3461601
 *
 * Provides the implementation of the Production class, which
 * is simply a wrapper for the sequence of items (where items are terminals
 * or nonterminals).  It also completes the implementation of the ifstream
 * constructor, which was really the only thing missing from the .h
 */

#include "production.h"

/**
 * Constructor Implementation: Production
 * --------------------------------------
 * Constructor that initializes the Production based
 * on the content of a file.
 */

Production::Production(ifstream& infile)
{
   string str;
   int pos = 0;
   while(infile >> str) {
      if(str.compare(";") == 0) {   //end of production found
         infile.seekg(pos);
         break;
      } else {
         phrases.push_back(str);    //add string to phrase vector
      }      
      pos = infile.tellg();
   }
}
