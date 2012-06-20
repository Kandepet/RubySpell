#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <array>

#include "Speller.hpp"


void SpellChecker::suggestionsWithCost(SpellDataAsTrie::iterator tree, char ch, std::vector<int> last_row,
      const std::string& word, std::vector< std::pair< std::string, int> > &results, int& cost) {
   int sz = last_row.size();

   std::vector<int> current_row(sz);
   current_row[0] = last_row[0] + 1;

   // Calculate the min cost of insertion, deletion, match or substution
   int insert_or_del, replace;
   for (int i = 1; i < sz; ++i) {
      insert_or_del = std::min(current_row[i-1] + 1, last_row[i] + 1);
      replace = (word[i-1] == ch) ? last_row[i-1] : (last_row[i-1] + 1);

      current_row[i] = std::min(insert_or_del, replace);
   }

   // When we find a cost that is less than the min_cost, is because
   // it is the minimum until the current row, so we update
   if ((current_row[sz-1] < cost) && ((*tree)->foundAWord())) {
      cost = current_row[sz-1];
      //cout << "Found: " << (*tree) -> getWord() << " cost: " << cost << endl;
      results.push_back(std::make_pair((*tree) -> getWord(), cost));
   }

   // If there is an element wich is smaller than the current minimum cost,
   //   we can have another cost smaller than the current minimum cost
   if (*std::min_element(current_row.begin(), current_row.end()) < cost) {

      // Insert each alphabet and see if anything gives us a smaller cost.
      std::string node_keys = "abcdefghijklmnopqrstuvwxyz";

      for (std::string::iterator it = node_keys.begin(); it != node_keys.end(); ++it) {
         SpellDataAsTrie::iterator sit = (*tree) -> find((*it));
         if(sit != (*tree) -> end())
            suggestionsWithCost(sit, *it, current_row, word, results, cost);
      }
   }
}

std::vector<std::pair<std::string, int> > SpellChecker::suggestions(std::string word, int maxEdits) {


   typedef std::pair<std::string, int> Result;
   typedef std::vector<Result> ResultsVector;
   ResultsVector results;

   if(!loaded) return ResultsVector();

   std::transform(word.begin(), word.end(), word.begin(), ::tolower);
   word.erase(std::remove_if(word.begin(), word.end(), ::ispunct ), word.end());
   word.erase(std::remove_if(word.begin(), word.end(), ::isdigit ), word.end());
   word.erase(std::remove_if(word.begin(), word.end(), ::iscntrl ), word.end());

   if(!word.length()) return ResultsVector();

   std::cout << "Searching for: " << word << std::endl;

   int sz = word.size();
   int cost = 0xffff;

   std::vector<int> current_row(sz + 1);

   // Naive DP initialization
   for (int i = 0; i < sz; ++i)
      current_row[i] = i;

   current_row[sz] = sz;

   // For each letter in the root map wich matches with a
   //   letter in word, we must call the suggestions
   std::string node_keys = "abcdefghijklmnopqrstuvwxyz";
   std::string temp = word;
   //for (std::string::iterator it = node_keys.begin(); it != node_keys.end(); ++it) {
   //for (int i = 0 ; i < sz; ++i) {
   for (int i = 0 ; i < 26; ++i) {
      //SpellDataAsTrie::iterator curr = data -> find(word[i]);
      SpellDataAsTrie::iterator curr = data -> find(node_keys[i]);
      if (curr != data -> end()) {
         //suggestionsWithCost(curr, word[i], current_row, word, results, cost);
         suggestionsWithCost(curr, node_keys[i], current_row, word, results, cost);
      }
   }
   //}

   for(ResultsVector::iterator it = results.begin(); it != results.end(); ++it)
      std::cout << "Result: " << it->first << ", " << it->second << std::endl;

   /*if(results.back().second <= maxEdits)
     return results.back().first.c_str();
     else
     return "NO SUGGESTION";
     */

   return results;
}

#if 0
int main() {
   std::string words = "/usr/share/dict/words";
   SpellChecker speller(words);

   //cout << speller.exists("sheep") << endl;
   //cout << speller.exists("deepak") << endl;

   //cout << speller.suggestions("sheep") << endl;
   //cout << speller.suggestions("sleeeeeeep") << endl;
   //cout << speller.suggestions("bagage") << endl;

   //return 0;

   /*
      std::string tmp;
      cout << "> ";
      while(!cin.eof()) {
      cin >> tmp;
      cout << speller.suggestions(tmp) << endl;
      cout << "> ";
      }*/

}
#endif

