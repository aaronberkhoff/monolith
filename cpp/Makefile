# Compiler
CXX = g++

# Compilation flags
CXXFLAGS = -O3 -Wall -std=c++23 -fPIC

# Project root

# Include paths
INCLUDES = -I$(MonoHome)/cpp/include \
           -I/usr/include/eigen3 \
           $(shell python3 -m pybind11 --includes)

# Source files
SRC = src/dynamics.cpp bindings/bindings_dynamics.cpp

# Object files (same name as source but in obj/)
OBJ = $(patsubst %.cpp,obj/%.o,$(SRC))

# Target module
TARGET = dynamics$(shell python3-config --extension-suffix)

PY_FOLDER = $(MonoHome)/python/monolith

# Build rules
all: $(TARGET)
	mv $(TARGET) $(PY_FOLDER)/

# Create object directory if missing
obj/%.o: %.cpp
	@mkdir -p obj/$(dir $*)   # create folder
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Build shared library for Python
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -shared $^ -o $@

# Clean
clean:
	rm -rf obj
	rm -f $(PY_FOLDER)/$(TARGET)
