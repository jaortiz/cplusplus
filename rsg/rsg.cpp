/**
 *Name: Jeremy Ortiz z3461601
 *
 * Provides the implementation of the full RSG application, which
 * relies on the services of the built-in string, ifstream, vector,
 * and map classes as well as the custom Production and Definition
 * classes provided with the assignment.
 */
 
#include <map>
#include <fstream>
#include <cstdlib>
#include "definition.h"
#include "production.h"

using namespace std;

//method protoype
void contextFreeGrammar(map<string, Definition> grammar, string nonTerminal,vector<string>& CFG);

/**
 * Takes a reference to a legitimate infile (one that's been set up
 * to layer over a file) and populates the grammar map with the
 * collection of definitions that are spelled out in the referenced
 * file. 
 *
 * @param infile a valid reference to a flat text file storing the grammar.
 * @param grammar a reference to the STL map, which maps nonterminal strings
 *                to their definitions.
 */

void readGrammar(ifstream& infile, map<string, Definition>& grammar)
{
   string str;
   while(infile >> str) {
      if(str.compare("{") == 0) {      //beginning of definition found
         int pos = infile.tellg();     //store current position
         infile >> str;                //storing definiton name
         infile.seekg(pos);            //return to previous position
         Definition def(infile);       //create new definition from the current file position
         grammar[str] = def;           //add definition to map
      }
   }   
}

/**
 * Takes a const reference to a grammar stored in a map and prints
 * sentences produced by applying the grammar rules. The number of
 * sentences should be as specified by the second parameter.
 *
 * @param grammar a reference to the STL map, which maps nonterminal strings
 *                to their definitions.
 * @param numSentencesNeeded number of sentences to be produced
 */
 
void generateRandomSentences(const map<string, Definition>& grammar, 
				    int numSentencesNeeded)
{
   vector<string> CFG;     //vector to store the context free grammars

   for(int i = 0; i < numSentencesNeeded;i++) {
      CFG.clear();
      contextFreeGrammar(grammar,"<start>",CFG);    //start random sentence generator with "<start>" non-terminal seed

      for(auto it = CFG.begin(); it != CFG.end(); it++) {   //loop through CFG vector and print separated by spaces
         cout << *it << " ";
      }
      cout << endl << endl;
   }
   
}

/**
 *Takes in the grammar map and the non terminal seed and recursively calls itself
 * when a non terminal is found when traversing a random production until all non
 * terminals have been expanded an printed.
 *
 *@param grammar the STL map, which maps nonterminal strings to their definitions.
 * 
 *@param nonTerminal is a non terminal string used for recursive expansion
 *
 *@param CFG a reference to a vector which contains the terminals of a context free grammar
 */
void contextFreeGrammar(map<string, Definition> grammar, string nonTerminal,vector<string>& CFG) {

   if(grammar.find(nonTerminal) == grammar.end()) {   //check whether or not a non terminal is contained in the map
      //cout << "invalid non-terminal" <<endl;
      exit(0);          //if not exit 
   }
      
   Definition def = grammar[nonTerminal];          //creating a copy of the non terminal definiton
   Production prod = def.getRandomProduction();    //creating a copy of a random production from 
                                                      //non terminal definition
   auto itEnd = prod.end();                        //production end iterator

   for(auto it = prod.begin(); it != itEnd; it++) {   //loop through the production
      string terminal = *it;  
      if((terminal.front() == '<') && (terminal.back() == '>')) {    //if true, a non-terminal has been found
         contextFreeGrammar(grammar,terminal,CFG);     //recusive call with the found non-terminal
      } else {
         CFG.push_back(terminal);         //otherwise add the terminal to context free grammar vector
      }
      
   }
}

/**
 * Performs the rudimentary error checking needed to confirm that
 * the client provided a grammar file.  It then continues to
 * open the file, read the grammar into a map<string, Definition>,
 * and then print out the random expansions as required.
 *
 * @param argc the number of tokens making up the command that invoked
 *             the RSG executable.  There must be at least two arguments,
 *             and only the first two are used.
 * @param argv the sequence of tokens making up the command, where each
 *             token is represented as a '\0'-terminated C string.
 */

int main(int argc, char *argv[])
{
  if (argc == 1) {
    cerr << "You need to specify the name of a grammar file." << endl;
    cerr << "Usage: rsg <path to grammar text file>" << endl;
    
    return EXIT_FAILURE;
  }
  
  ifstream grammarFile(argv[1]);
  if (grammarFile.fail()) {
    cerr << "Failed to open the file named \"" << argv[1] << "\". "
            "Check to ensure the file exists." << endl;
    return EXIT_FAILURE;
  }
  
  // things are looking good...
  map<string, Definition> grammar;
  readGrammar(grammarFile, grammar);
  generateRandomSentences(grammar, 3);
  
  return EXIT_SUCCESS;
}
