/*
 * File: WordLadder.cpp
 * --------------------
 * Name: Jeremy Ortiz z3461601
 * This file is the starter project for the word ladder problem on Assignment #1.
 */

#include "genlib.h"
#include "lexicon.h"
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void wordLadder(Lexicon& lex, string start, string dest);

int main() {

   string start;   
   cout << "Enter start word (RETURN to quit): ";
   getline(cin,start);     
   if(start.empty()) {     //if empty quit
      exit(0);  
   } 

   string dest;     
   cout << "Enter destination word: ";
   cin >> dest;

	Lexicon lex("EnglishWords.dat");    //creating lexicon based on EnglishWords.dat
   
   transform(start.begin(),start.end(),start.begin(),::tolower);     //converting both inputs to lowercase strings
   transform(dest.begin(),dest.end(),dest.begin(),::tolower);
   
   wordLadder(lex, start, dest); 

	return EXIT_SUCCESS;
}


/**
 *Takes in a reference to a lexicon containing valid words and using the start word as the starting point
 *and the destination as a goal, implements a BFS in order to find the shortest ladder/s.
 *
 *@param lex a reference to the lexicon which contains the valid words in the english dictionary
 *
 *@param start the starting word
 *
 *@param dest the destination word
 */
void wordLadder(Lexicon& lex, string start, string dest) {
   
   queue<vector<string>> queue,foundLadders;     //creating queue for BFS and for storing multiple ladder solutions
   
   vector<string> begin;         //creating initial vector containing the start word
   begin.push_back(start);       
   queue.push(begin);         //adding intial ladder to the queue

   bool found = false;     //boolean value storing whether or not a solution has been found
   Lexicon usedWords;      //Lexicon containing all the words already generated to avoid loops

   int currLadderLength = 0;        //used to store the current ladder length
   int foundLadderLength = 999;     //used to store the shortest ladder length if found. 
   
   int wordLength = start.length(); 
 
   while(!queue.empty()) {

      //dequeue the first element
      vector<string> currLadder = queue.front();
      queue.pop();     
      currLadderLength = currLadder.size();
      
      //check if the popped off element is a ladder
      if(currLadder.back().compare(dest) == 0) {
         foundLadders.push(currLadder);
         foundLadderLength = currLadder.size();    
         found = true;
      } else {
         usedWords.add(currLadder.back());      //if not ladder, add latest hop to used words queue to avoid loops
      }

      if(currLadderLength < foundLadderLength) {   //optimisation to ensure ladders greater than the shortest ladder length are not generated
         string currWord = currLadder.back();
         for(int i = 0; i < wordLength; i++) {
            string newWord = currWord;
            for(char ch = 'a'; ch <= 'z'; ch++) {
               newWord.replace(i,1,1,ch);             //for loop to replace each character in the string via string::replace with letters of the alphabet 
               if(lex.containsWord(newWord)) {        //check if word is valid
                  if(newWord.compare(dest) == 0) {    //check if the destination word has been generated
                     vector<string> newLadder = currLadder;
                     newLadder.push_back(newWord);
                     foundLadderLength = newLadder.size();     //store shortest ladder length
                     queue.push(newLadder);                 //add to queue
                  } else if(!usedWords.containsWord(newWord)) {   //check whether the generated word has been previously used
                     vector<string> newLadder = currLadder;       //if not add to queue
                     newLadder.push_back(newWord);
                     queue.push(newLadder);
                  }
               }
            }
         }
      }
   }
  
   //printing the output/result 
   if(found == true) {
      int ladders = foundLadders.size();
      for(int i = 0; i < ladders; i++) {
         if(i == 0) {
            cout << "Found ladder: ";
         }
         vector<string> print = foundLadders.front();
         foundLadders.pop();
         for(auto it = print.begin(); it != print.end();it++) {
            cout << *it << " ";
         }
         cout << endl;
      }
      
   } else { 
      cout << "No ladder found." << endl;
   }
   
}

