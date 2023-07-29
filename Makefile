# Variables
CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11 -O2 -fsanitize=address -fno-omit-frame-pointer
LDLIBS = -lsndfile -lm -fsanitize=address

# Targets
all: main

main: main.o waveForms.o utilities.o
	$(CXX) -o $@ $^ $(LDLIBS)

main.o: main.cc waveForms.h utilities.h

waveForms.o: waveForms.cc waveForms.h

utilities.o: utilities.cc utilities.h

# Automatic dependency generation
%.d: %.cc
	@$(CXX) $(CXXFLAGS) $< -MM -MT $(@:.d=.o) >$@

include $(wildcard *.d)

# Cleanup
.PHONY: clean
clean:
	rm -f *.o *.d main *~

# Testing
TEST_OUTPUT_FILE = test_output.wav
TEST_WAVEFORM = sine
TEST_DURATION = 1
TEST_FREQUENCIES = 440

.PHONY: test
test: main
	./main $(TEST_OUTPUT_FILE) $(TEST_WAVEFORM) $(TEST_DURATION) $(TEST_FREQUENCIES)
	@echo "Test complete. Check $(TEST_OUTPUT_FILE) for the output."
