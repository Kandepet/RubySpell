$LOAD_PATH << File.expand_path( File.dirname(__FILE__) + '/../ext' )
$LOAD_PATH << File.expand_path( File.dirname(__FILE__) + '/..' )

require 'test/unit'

system("cd #{File.expand_path(File.join(File.dirname(__FILE__), '..'))}; make distclean")

system("cd #{File.expand_path(File.join(File.dirname(__FILE__), '..'))}; ruby ext/extconf.rb")
system("cd #{File.expand_path(File.join(File.dirname(__FILE__), '..'))}; make")

require "spellsuggest"

def assert_array_similarity(expected, actual, message=nil)
  full_message = build_message(message, "<?> expected but was\n<?>.\n", expected, actual)
  assert_block(full_message) { (expected.size ==  actual.size) && (expected - actual == []) }
end
