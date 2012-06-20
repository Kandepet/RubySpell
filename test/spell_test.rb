require File.expand_path( File.dirname(__FILE__) + '/test_helper.rb' )

class SpellTest < Test::Unit::TestCase

  def test_speller_defined
    assert defined?(Spell), "Spell module should be defined"
    assert defined?(Spell::SpellSuggest), "class Spell::SpellSuggest is supposed to be defined"
  end

  def test_speller_has_constructor
    assert_respond_to Spell::SpellSuggest, :new
  end

  SPELLER_METHODS = [:load, :correct?, :suggest]

  def test_speller_methods
    speller = Spell::SpellSuggest.new
    SPELLER_METHODS.each do |method_name|
      assert_respond_to speller, method_name
    end
  end

  def test_speller_functionality
    speller = Spell::SpellSuggest.new
    loaded = speller.load("/usr/share/dict/words")
    assert_equal true, loaded
    assert_array_similarity ["a5", "aae", "aandr", "abend", "arend", "trend"], speller.suggest("trendz")
  end

end
