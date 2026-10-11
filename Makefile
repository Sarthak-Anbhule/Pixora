CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iinclude

SRCDIR = src
TESTDIR = tests
INCDIR = include
BINDIR = bin

TARGET = $(BINDIR)/pixora_demo
TEST_TARGET = $(BINDIR)/test_graph

all: $(TARGET)

$(BINDIR):
	mkdir -p $(BINDIR)

$(TARGET): $(SRCDIR)/Graph.cpp $(SRCDIR)/main.cpp | $(BINDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(TEST_TARGET): $(SRCDIR)/Graph.cpp $(TESTDIR)/test_graph.cpp | $(BINDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

test: $(TEST_TARGET)
	@echo "Running Pixora Graph unit tests..."
	@./$(TEST_TARGET)

run: $(TARGET)
	@./$(TARGET)

clean:
	rm -rf $(BINDIR)

.PHONY: all test run clean
