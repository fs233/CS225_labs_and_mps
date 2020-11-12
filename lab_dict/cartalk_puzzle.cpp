/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>
#include <iostream>
#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    /* Your code goes here! */
    ifstream wordsFile(word_list_fname);
    string word;
    if (wordsFile.is_open()) {
        //std::cout<<__LINE__<<std::endl;
        while (getline(wordsFile, word)){
            if(word.length()==5){
                string word_first = word.substr(1, word.length()-1);
                string word_sec = word[0]+word.substr(2, word.length()-2);
                if(d.homophones(word, word_first) && d.homophones(word_first, word_sec)){
                    auto t = std::make_tuple(word, word_first, word_sec);
                    ret.push_back(t);
                }
            }
            
        }
    }
    return ret;
}
