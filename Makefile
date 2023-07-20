# Variables
CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11 -O2
LDLIBS = -lsndfile -lm

# Targets
all: main

main: main.o waveForms.o
	$(CXX) -o $@ $^ $(LDLIBS)

main.o: main.cpp waveForms.h

waveForms.o: waveForms.cpp waveForms.h

# Automatic dependency generation
%.d: %.cpp
	@$(CXX) $(CXXFLAGS) $< -MM -MT $(@:.d=.o) >$@

include $(wildcard *.d)

# Cleanup
.PHONY: clean
clean:
	rm -f *.o *.d main *~
