#include "SpellTrie.hpp"

using namespace std;

// Add a new word to the Trie.
void SpellDataAsTrie::add(string& word) {

   //Make sure we have a word with atleast a character.
   if(!word.length()) return;

   // Keep track of number of words in the trie
   ++ wordCount;

   // Transform word to lowercase and remove punctuations.
   std::transform(word.begin(), word.end(), word.begin(), ::tolower);
   word.erase(remove_if(word.begin(), word.end(), ::ispunct ), word.end());

   // Make sure we have a word with atleast a character
   // after all the transformations
   if(!word.length()) return;

   // Start from the root. Add the new word one character at a time,
   // traversing the Trie until either the word is found, or we find
   // a path in the tree when new characters are to be added.
   Node* curr = root;
   for(unsigned int i = 0;i < word.length();++i) {

      char& c = word[i];

      if(!isalpha(c)) continue;

      // Didn't find a character.
      // Create a new node in the Trie.
      if(!curr->child(c))
         curr->child(c) = new Node;

      curr = curr->child(c);
   }

   // Mark the final node and store the complete word in it for
   // easier access.
   curr->final = true;
   curr->word = word;
}

// Check if a word is spelled correctly.
// This is just an auxilliary function as the suggest() function
// can easily detect if a word is spelled correctly as part of its
// suggestion generation, but this is faster if we only want to check
// for misspellings.
bool SpellDataAsTrie::exists(string word) {

   // Transform word to lowercase and remove punctuations.
   std::transform(word.begin(), word.end(), word.begin(), ::tolower);
   word.erase(remove_if(word.begin(), word.end(), ::ispunct ), word.end());

   // Start from the root and travel down until you find all characters
   // in the given word & we end in a final node, or we found a misspellet
   // word.

   Node* curr = root;
   for(unsigned int i = 0;i < word.size();++i) {
      char& c = word[i];
      if(!isalpha(c)) continue;
      if(!curr->child(c)) return false;
      curr = curr->child(c);
   }
   return curr->final;
}

// Read all the words from file into our Trie.
bool SpellDataAsTrie::load(const string &wordsFile) {

   cout << "indexing dictionary : " << wordsFile << " ... ";

   ifstream dict(wordsFile.c_str());
   if(dict.good()) {
      string tmp;
      while(!dict.eof()) {
         dict >> tmp;
         add(tmp);
      }

      cout << " done. Added " << wordCount << " words." << endl;
      return true;

   } else {
      cout << " error. Check file." << endl;
      return false;
   }
}

