/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of "StringTriples" (a typedef'd std::tuple, see top of 
 * cartalk_puzzle.h). Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector< StringTriple > cartalk_puzzle(PronounceDict d,
                                      const string& word_list_fname)
{
    /* Your code goes here! */
	vector<StringTriple> a;
		ifstream b(word_list_fname);
		string word;
		if(b.is_open()){
			while(getline(b,word)){
				if(word.size()>=2){
					string s1=word;
					string s2=word;
					s1.erase(s1.begin());
					s2.erase(s2.begin()+1);
					if(d.homophones(word,s1)&&d.homophones(word,s2)){
						StringTriple s(word,s1,s2);
						a.push_back(s);}}}}
	return a;}
