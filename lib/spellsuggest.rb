raise "This file should never be required. It's here only for documentation purposes."

# module, through which the functionality of spell check and suggestion is possible
module Spell

  # class, that implements spell checking and spell suggestions
  class SpellSuggest

    # load a list of words into the speller
    def load(filename); end

    # check if the given 'word' is spelled correctly
    def correct?(word); end

    # suggest possible corrections to incorrectly spelled 'word'
    def suggest(word); end

  end

end
