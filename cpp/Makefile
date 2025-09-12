# Compiler
CXX = g++

# Compilation flags
CXXFLAGS = -O3 -Wall -std=c++23 -fPIC

# Include paths
INCLUDES = -I$(MonoHome)/cpp/include \
           -I/usr/include/eigen3 \
           $(shell python3 -m pybind11 --includes)

# Python extension suffix
PY_EXT = $(shell python3-config --extension-suffix)

# Modules
DYNAMICS_SO = $(PY_FOLDER)/dynamics$(PY_EXT)
PLANETS_SO  = $(PY_FOLDER)/planets$(PY_EXT)

# Sources per module
DYNAMICS_SRC = src/dynamics.cpp bindings/bindings_dynamics.cpp
PLANETS_SRC  = src/planets.cpp  bindings/bindings_planets.cpp

# Object files
DYNAMICS_OBJ = $(patsubst %.cpp,obj/%.o,$(DYNAMICS_SRC))
PLANETS_OBJ  = $(patsubst %.cpp,obj/%.o,$(PLANETS_SRC))

# Python package folder
PY_FOLDER = $(MonoHome)/python/monolith

# ---------------- Build rules ----------------
all: $(DYNAMICS_SO) $(PLANETS_SO) stubs

# Compile .cpp -> .o
obj/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Build shared libraries directly in Python package
$(DYNAMICS_SO): $(DYNAMICS_OBJ)
	@mkdir -p $(PY_FOLDER)
	$(CXX) $(CXXFLAGS) -shared $^ -o $@

$(PLANETS_SO): $(PLANETS_OBJ)
	@mkdir -p $(PY_FOLDER)
	$(CXX) $(CXXFLAGS) -shared $^ -o $@

# Conditional stub generation
stubs: $(PY_FOLDER)/dynamics.pyi $(PY_FOLDER)/planets.pyi

$(PY_FOLDER)/dynamics.pyi: $(DYNAMICS_SO)
	@echo "Generating dynamics stubs..."
	pybind11-stubgen monolith.dynamics --output-dir $(PY_FOLDER)/stubs
	@cp $(PY_FOLDER)/stubs/monolith/dynamics.pyi $(PY_FOLDER)/dynamics.pyi
	@rm -rf $(PY_FOLDER)/stubs

$(PY_FOLDER)/planets.pyi: $(PLANETS_SO)
	@echo "Generating planets stubs..."
	pybind11-stubgen monolith.planets --output-dir $(PY_FOLDER)/stubs
	@cp $(PY_FOLDER)/stubs/monolith/planets.pyi $(PY_FOLDER)/planets.pyi
	@rm -rf $(PY_FOLDER)/stubs

# Clean
clean:
	rm -rf obj
	rm -f $(PY_FOLDER)/dynamics*$(PY_EXT) $(PY_FOLDER)/planets*$(PY_EXT)
	rm -f $(PY_FOLDER)/dynamics.pyi $(PY_FOLDER)/planets.pyi
