#ifndef __SPELLER_HPP__
#define __SPELLER_HPP__

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

#include "SpellTrie.hpp"

// Actual SpellChecker
//
// This class implements the algorithm for determining if
// a given word is spelt correctly and returns suggestions
// if misspelt.
//
// SpellChecker implements the spell checking using edit distance.
//
// The SpellChecker does not depend on the format in which the
// words are stored. We could use a Trie, multi-level hash, even
// a vector. Its interface to the data is via iterators.
//
class SpellChecker {

   // Make use of the Trie data for spell check and  suggestions.
   SpellDataAsTrie *data;

   bool loaded;

   public:

      SpellChecker() : data(NULL), loaded(false) {
         data = new SpellDataAsTrie;
      }

      SpellChecker(std::string &wordsFile) : data(NULL), loaded(false) {
         data = new SpellDataAsTrie;
         data->load(wordsFile);
         loaded = true;
      }

      virtual ~SpellChecker() {
         delete data;
      }

      bool load(std::string &wordsFile) {
         if(data->load(wordsFile)) {
            loaded = true;
         } else {
            loaded = false;
         }

         return loaded;
      }

      bool exists(std::string word) {
         if(!loaded) return false;

         return data -> exists(word);
      }

      void suggestionsWithCost(SpellDataAsTrie::iterator tree, char ch, std::vector<int> last_row,
            const std::string& word, std::vector< std::pair< std::string, int> > &results, int& cost);

      std::vector<std::pair<std::string, int> > suggestions(std::string word, int maxEdits = 3);
};

#endif // __SPELLER_HPP__
