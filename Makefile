# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Project files
TARGET = stable_pendulum
SOURCES = stable_pendulum.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(TARGET)

# Linking the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) $(LDLIBS) -o $(TARGET)

# Compiling source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJECTS) $(TARGET)

# Phony targets
.PHONY: all clean
