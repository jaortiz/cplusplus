/**
 *Name: Jeremy Ortiz z3461601
 *
 * Provides the implementation of
 * the Definition class, which is really
 * nothing more than an ordered pair: a nonterminal
 * attached to a string.
 */ 
 
#include "definition.h"
#include "random.h"

/**
 * Constructor: Definition
 * -----------------------
 * Constructs an instance of a Definition object
 * based on the content of the specified file.
 */

Definition::Definition(ifstream& infile)
{
   //create productions of definitons and store in the definiton object
   string str;
   int pos = 0;
   while(infile >> str) {
      if(str.compare(";") == 0) {      //end of production found
         pos = infile.tellg();         //remeber current position
         infile >> str;
         if(str.compare("}") == 0) {   //check for end of definition
            break;
         } else {
            infile.seekg(pos);         //return to previous position
            Production prod(infile);   //create the new production
            possibleExpansions.push_back(prod); //add production to possible expansions vector
         }
      } else {
         Production prod(infile);         //create new production
         possibleExpansions.push_back(prod);    //add production to possible expansions vector
      }
   }
}

/**
 * Method: getRandomProduction
 * ---------------------------
 * Returns a const reference to one of the
 * embedded Productions.
 */

const Production& Definition::getRandomProduction() const
{
   static RandomGenerator rand;     //declaring static to ensure the random seed is the same for the entire runtime
   int random = rand.getRandomInteger(0, possibleExpansions.size()-1);  //get random number based on no. of possible expansions
   return possibleExpansions[random];     //return random production
}
