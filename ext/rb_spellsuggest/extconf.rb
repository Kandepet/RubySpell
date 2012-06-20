require "mkmf"

$CFLAGS = "-D_GNU_SOURCE -Wall -std=c++0x"

have_header("ruby.h")
have_library("stdc++")
create_makefile("spellsuggest")
