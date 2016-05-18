HFILES=uniqueptr.hpp
TARGETS=test test2

all: $(TARGETS)

CXX=g++
CXXFLAGS=-std=c++11 -Wall -Wextra -pedantic -g

$(TARGETS): %: %.cpp $(HFILES)
	$(CXX) $(CXXFLAGS) $< -o $@

DIR=$(notdir $(CURDIR))

tar: $(CURDIR).tar.gz

%.tar.gz: $(HFILES) README.txt makefile
	tar czvf $@ -C .. $(addprefix $(DIR)/, $^)

clean:
	-rm $(TARGETS) *.tar.gz 2> /dev/null || true
