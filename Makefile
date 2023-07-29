# Variables
CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11 -O2 -fsanitize=address -fno-omit-frame-pointer
LDLIBS = -lsndfile -lm -fsanitize=address

# Targets
all: main

main: main.o waveForms.o
	$(CXX) -o $@ $^ $(LDLIBS)

main.o: main.cc waveForms.h

waveForms.o: waveForms.cc waveForms.h

# Automatic dependency generation
%.d: %.cc
	@$(CXX) $(CXXFLAGS) $< -MM -MT $(@:.d=.o) >$@

include $(wildcard *.d)

# Cleanup
.PHONY: clean
clean:
	rm -f *.o *.d main *~
