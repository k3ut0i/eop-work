CC = g++
CXXFLAGS = -Wall -Wextra -ggdb -Isrc

TEST_DIR = t
TEST_FILES = $(wildcard $(TEST_DIR)/*.cc)
TESTS = $(TEST_FILES:.cc=)

.PHONY: clean test all

all: $(TESTS)
test:
	prove
clean:
	rm -f *.o *.d $(TESTS)

