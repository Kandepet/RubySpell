#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <array>

#include "Speller.hpp"
#include "SpellSuggestExt.hpp"

using namespace std;

// Forward declarations
void Init_speller();

extern "C" void Init_spellsuggest() {
  Init_speller();
}

static void speller_delete(SpellChecker* obj) {
  if (obj) delete obj;
}

static VALUE speller_init(VALUE self) {
  //string words = "/usr/share/dict/words";
  //SpellChecker *new_obj = new SpellChecker(words);
  SpellChecker *new_obj = new SpellChecker;
  return Data_Wrap_Struct(cSpellSuggest, 0, speller_delete, new_obj);
}

static VALUE check(VALUE self, VALUE val) {
  SpellChecker *obj;
  Data_Get_Struct(self, SpellChecker, obj);
  char  *word = RSTRING_PTR(val);
  //cout << obj->exists(word);
  if(obj->exists(word))
     return Qtrue;
  else
     return Qfalse;
}

static VALUE load(VALUE self, VALUE val) {
  SpellChecker *obj;
  Data_Get_Struct(self, SpellChecker, obj);
  std::string  words_list_file = RSTRING_PTR(val);
  //cout << obj->exists(word);
  if(obj->load(words_list_file))
     return Qtrue;
  else
     return Qfalse;
}

static VALUE suggest(VALUE self, VALUE val) {
  SpellChecker *obj;
  Data_Get_Struct(self, SpellChecker, obj);
  char  *word = RSTRING_PTR(val);

  typedef pair<string, int> Result;
  typedef vector<Result> ResultsVector;
  ResultsVector results = obj -> suggestions(word);
  VALUE suggestions = rb_ary_new();

  for(ResultsVector::iterator it = results.begin(); it != results.end(); ++it)
     rb_ary_push(suggestions, rb_str_new2(it->first.c_str()));
     //cout << "Result: " << it->first << ", " << it->second << endl;

  return suggestions;
}

typedef VALUE (*rb_method)(...);

void Init_speller() {
  mSpell = rb_define_module("Spell");

  cSpellSuggest = rb_define_class_under(mSpell, "SpellSuggest", rb_cObject);

  rb_define_method(cSpellSuggest, "initialize", (rb_method)speller_init, 0);
  rb_define_singleton_method(cSpellSuggest, "new", (rb_method)speller_init, 0);

  rb_define_method(cSpellSuggest, "load",   (rb_method)load, 1);
  rb_define_method(cSpellSuggest, "correct?",   (rb_method)check, 1);
  rb_define_method(cSpellSuggest, "suggest", (rb_method)suggest, 1);
}

