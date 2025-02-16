# Define SFML directory
SFML_DIR = C:/SFML-2.6.2/

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -I$(SFML_DIR)/include
LDFLAGS = -L$(SFML_DIR)/lib -lsfml-graphics -lsfml-window -lsfml-system

# Source and object files
SRC = src/main.cpp
OBJ = $(SRC:.cpp=.o)

# Define the target executable name (update extension for Windows)
TARGET = bin/dot_smash  # Use .exe on Windows if needed

# Default target
all: $(TARGET)

# Build the target
$(TARGET): $(OBJ)
	$(CXX) -o $(TARGET) $(OBJ) $(LDFLAGS)

# Compile object files
%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@
