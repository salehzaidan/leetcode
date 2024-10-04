CXX = clang++-17
CXXFLAGS = -std=c++23 -stdlib=libstdc++ -fsanitize=address -g
LIBS = -lgtest -lgtest_main -lpthread

SRC_DIR = src
BUILD_DIR = build

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
TARGETS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%,$(SRCS))

all: $(TARGETS)

$(BUILD_DIR)/%: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< $(LIBS) -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean