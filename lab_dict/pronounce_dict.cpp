/**
 * @file pronounce_dict.cpp
 * Implementation of the PronounceDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "pronounce_dict.h"

#include <iterator>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstring>
#include <algorithm>

using std::string;
using std::map;
using std::vector;
using std::ifstream;
using std::istream;
using std::istream_iterator;
using std::stringstream;

/** 
 * Constructs a PronounceDict from a CMU pronunciation dictionary
 * file. See http://www.speech.cs.cmu.edu/cgi-bin/cmudict .
 * @param pronun_dict_filename Filename of the CMU pronunciation
 * dictionary.
 */
PronounceDict::PronounceDict(const string& pronun_dict_filename)
{
    ifstream pronun_dict_file(pronun_dict_filename);
    string line;
    if(pronun_dict_file.is_open()) {
        while(getline(pronun_dict_file, line)) {
            /* Used to break the line by whitespace. The CMU Dict does this for
             * separating words from their pronunciations. */
            stringstream line_ss(line);
            istream_iterator< string > line_begin(line_ss);
            istream_iterator< string > line_end;
            if(line[0] != '#' && *line_begin != ";;;") {   
                /* Associate the word with the rest of the line
                 * (its pronunciation). */
                dict[*line_begin] = vector< string > (++line_begin, 
                                                      line_end);
            }
        }
    }
    /* If it's not open then... well... just don't do anything for the sake
     * of simplicity. */
}

/** 
 * Constructs a PronounceDict from a CMU std::map mapping the word
 * to a vector of strings which represent the pronunciation.
 * @param pronun_dict Maps a string word to a vector of strings
 * representing its pronunciation.
 */
PronounceDict::PronounceDict(const map< string, vector< string > >& 
                             pronun_dict) : dict(pronun_dict)
{
    /* Nothing to see here. */  
}

/** 
 * Uses the dictionary to determine if the two words are homophones.
 * @param word1 First word to be tested.
 * @param word2 Second word to be tested.
 * @return true if the two words are homophones, false otherwise (or
 * one or both words weren't in the dictionary).
 * Note: The word keys in the dictionary are stored in uppercase.
 */
bool PronounceDict::homophones(const string& word1, const string& word2) const
{
    /* Your code goes here! */
	string w1 = word1;
	string w2 = word2;
	std::transform(w1.begin(),w1.end(),w1.begin(),toupper);
	std::transform(w2.begin(),w2.end(),w2.begin(),toupper);
	auto w11 = dict.find(w1);
	auto w22 = dict.find(w2);
	if(w11==dict.end()||w22==dict.end()){
		//puts("end");
		return false;}
	else if(w11->second.size()!=w22->second.size()){
		//puts("size");
		return false;}
	else{
		//puts("baby");
		for(size_t i = 0; i< w11->second.size();i++){
			if(w11->second[i]!=w22->second[i])
			return false;}
		return true;}}
