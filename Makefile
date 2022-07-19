COMPILER=clang++
COMPILER_FLAGS=-g -Wall -std=c++20
LINKER_FLAGS=$(shell pkg-config --libs --cflags raylib)

SOURCE_DIR=src
OBJECT_DIR=build

SOURCE_FILES=$(shell find $(SOURCE_DIR) -type f -name '*.cpp')
OBJECT_FILES=$(patsubst $(SOURCE_DIR)/%.cpp,$(OBJECT_DIR)/%.o,$(SOURCE_FILES))
HEADER_FILES=$(shell find $(SOURCE_DIR) -type f -name '*.cpp')

BINARY=executable


all: $(BINARY)

$(BINARY): $(OBJECT_FILES)
	$(COMPILER) $(COMPILER_FLAGS) $(OBJECT_FILES) -o $@ $(LINKER_FLAGS)

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(COMPILER) $(COMPILER_FLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJECT_DIR)
	$(RM) $(BINARY)