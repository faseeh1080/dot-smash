# Define paths
SFML_DIR = c:\SFML-2.6.2
CXX = g++
CXXFLAGS = -std=c++11 -Wall -I$(SFML_DIR)/include
LDFLAGS = -L$(SFML_DIR)/lib -lsfml-graphics -lsfml-window -lsfml-system -mwindows

# Define the target executable name
TARGET = bin/dot_smash

# Define the source files
SRC = src/main.cpp

# Define the object files (from source files)
OBJ = $(SRC:.cpp=.o)

# Default target
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $(TARGET) $(OBJ) $(LDFLAGS)

# Commands to run after compilation.
	del /f /q src\*.o

# Compile the object files
%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@
