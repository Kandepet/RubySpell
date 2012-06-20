require './spellsuggest'
require 'pp'

ss = Spell::SpellSuggest.new

loaded = ss.load("/usr/share/dict2/words")

if loaded
   if ss.correct?("spell")
      puts "'spell' is spelled correctly"
   else
      puts "'spell' is spelled incorrectly"
   end

   if ss.correct?("kandepet")
      puts "'kandepet' is spelled correctly"
   else
      puts "'kandepet' is spelled incorrectly"
   end

   pp ss.suggest("spel");
end
