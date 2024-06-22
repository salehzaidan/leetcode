SOLUTION_FILENAME := solution.cpp
PROBLEMS_DIR := problems
BUILD_DIR := build

SOURCES := $(wildcard $(PROBLEMS_DIR)/*/$(SOLUTION_FILENAME))
EXECUTABLES := $(patsubst $(PROBLEMS_DIR)/%/$(SOLUTION_FILENAME),$(BUILD_DIR)/%,$(SOURCES))

CXX := g++
CXXFLAGS := -std=c++20 -g -I./include -fsanitize=address
LDLIBS := -lgtest -lgtest_main

all: $(EXECUTABLES)

$(BUILD_DIR)/%: $(PROBLEMS_DIR)/%/$(SOLUTION_FILENAME)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDLIBS)

test: $(EXECUTABLES)
	@for exe in $(EXECUTABLES); do \
		echo "Running $$exe"; \
		./$$exe; \
		echo ""; \
	done

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all test clean
