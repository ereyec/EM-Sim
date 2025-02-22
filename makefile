#Run mingw32-make in cmd

# Compiler
CXX := g++

# Directories
INCLUDE := -I./include
LIBDIR  := -L./lib

# Compiler Flags 
CXXFLAGS := -std=c++17

# Source Files

SRC := ./include/glad.c \
            ./em-sim/main.cpp \

# Libraries
LIBS := -l:libglfw3.a -lopengl32 -lgdi32 -luser32

# Output
OUT := program.exe

# Build rule
all:
	$(CXX) $(INCLUDE) $(LIBDIR) $(SRC) $(LIBS) -o $(OUT)

# Clean rule
clean:
	rm -f $(OUT)
