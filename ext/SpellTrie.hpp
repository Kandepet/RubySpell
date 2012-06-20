#ifndef __SPELL_TRIE_HPP__
#define __SPELL_TRIE_HPP__

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <array>

class SpellDataAsTrie {

   private:

      //Node structure is used to represent each node
      //of the Trie.
      struct Node {

         // Each node can have utmost 26 children, since there are
         // only 26 alphabets.
         static const int NoOfKeys = 26;

         private:
            // The new C++0X array<> is being used to store the links to all
            // 26 children. We could have just used an array of Node pointers,
            // but I want to make use of the array<>::iterator and expose that
            // as the iterator for Node.
            typedef std::array<Node *, NoOfKeys> NodeArray;
            NodeArray children;

            // For ease, I am storing the actual word at the leaf node.
            std::string word;

            // Does this node represent the leaf for a word?
            // Note: We could as well use just word and check if word == "",
            // but this is faster.
            bool final;

            // Return the child at offset c - 'a'
            Node*& child(char c) {
               return children[tolower(c)-'a'];
            }

         public:

            // Constructor
            Node() : final(false) {
               for(int i = 0;i < NoOfKeys;++i)
                  children[i] = 0;
            }

            // Destructor. Not virtual because Node is not
            // exposed outside SpellDataAsTrie and hence never inherited.
            ~Node() {
               for(int i = 0;i < NoOfKeys;++i)
                  if(children[i])
                     delete children[i];
            }

            // Did we find a word at this node?
            bool foundAWord() { return final; }

            // For ease of use, I am storing the actual word in the node.
            // This effectively doubles the space needed. Can easily refactore
            // this out later.
            const std::string & getWord(void) { return word; }

            // Node Iterators
            //
            // The new C++0X array<> is being used to store the links to all
            // 26 children. We can just use an array of Node pointers, but I
            // wanted to make use of the array<>::iterator and expose that
            // as the iterator for Node.
            typedef NodeArray::iterator iterator;

            iterator begin() { return children.begin(); }

            iterator end() { return children.end(); }

            iterator find(char c) {
               if(children[c - 'a'] != NULL)
                  return begin() + (c - 'a');
               else
                  return end();
            }

            // Outer class is friending the inner struct so it can access the
            // private data & functions.
            friend class SpellDataAsTrie;

      }; // end of struct Node

      // Some useful statistics
      int wordCount; // Total words in the trie

      // Root of the trie.
      Node* root;

   public:

      // Constructor
      SpellDataAsTrie() : wordCount(0), root(NULL) {
         root = new Node;
      }

      // Destructor
      virtual ~SpellDataAsTrie() {
         delete root;
      }

      // Add a new word to the Trie.
      void add(std::string& word);

      // Check if a word is spelled correctly.
      // This is just an auxilliary function as the suggest() function
      // can easily detect if a word is spelled correctly as part of its
      // suggestion generation, but this is faster if we only want to check
      // for misspellings.
      bool exists(std::string word);

      // Read all the words from file into our Trie.
      bool load(const std::string &wordsFile);

      // Trie Iterators
      //
      // Since most of the Trie data is encapsulated in a Node, we forward all
      // iterator functionality to the corresponding Node iterators
      typedef Node::iterator iterator;
      iterator begin() { return root -> begin(); }
      iterator end() { return root -> end(); }
      iterator find(char c) { return root -> find(c); }

};

#endif //__SPELL_TRIE_HPP__
