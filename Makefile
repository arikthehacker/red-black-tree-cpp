CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# List of object files
OBJS = main.o \
       main_helpers.o \
       race.o \
       red_black_tree.o

TARGET = program3

# Special color variables
RESET  = \033[0m
GREEN  = \033[1;32m
BLUE   = \033[1;34m
PURPLE = \033[1;35m
YELLOW = \033[1;33m

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo ""
	@echo -e "$(BLUE)Linking $(TARGET) ...$(RESET)"
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
	@echo -e "$(GREEN)Build complete! Run ./$(TARGET) to start.$(RESET)"
	@echo ""

# Compile main.cpp
main.o: main.cpp race.h
	@echo -e "$(PURPLE)Compiling Main: $@$(RESET)"
	$(CXX) $(CXXFLAGS) -c main.cpp

# Compile mainhelpers.cpp
main_helpers.o: main_helpers.cpp race.h
	@echo -e "$(PURPLE)Compiling MainHelpers: $@$(RESET)"
	$(CXX) $(CXXFLAGS) -c main_helpers.cpp

# Compile race.cpp
race.o: race.cpp race.h
	@echo -e "$(PURPLE)Compiling Race: $@$(RESET)"
	$(CXX) $(CXXFLAGS) -c race.cpp

# Compile tree.cpp
red_black_tree.o: red_black_tree.cpp race.h
	@echo -e "$(PURPLE)Compiling Tree: $@$(RESET)"
	$(CXX) $(CXXFLAGS) -c red_black_tree.cpp

# Clean up
clean:
	@echo -e "$(YELLOW)Cleaning up object files and $(TARGET) ...$(RESET)"
	rm -f $(OBJS) $(TARGET)
	@echo -e "$(GREEN)Clean complete.$(RESET)"

run: $(TARGET)
	./$(TARGET) < sample-input.txt

test:
	./test.sh

.PHONY: all clean run test
