# # Compiler
# CXX ?= g++-11

# # Compilation flags
# CXXFLAGS = -O3 -Wall -std=c++23 -fPIC
# CXXFLAGS += -Wno-maybe-uninitialized # suppress pybind11 warning

# CXXFLAGS_COV = -O0 -g -fprofile-arcs -ftest-coverage -fPIC # for coverage analysis
# CXXFLAGS_COV += -Wno-maybe-uninitialized # suppress pybind11 warning

# # Include paths
# INCLUDES = -I$(MonoHome)/cpp/include \
#            -I/usr/include/eigen3 \
#            $(shell python3 -m pybind11 --includes)

# # Python extension suffix
# PY_EXT = $(shell python3-config --extension-suffix)
# # Python package folder
# PY_FOLDER = $(MonoHome)/python/monolith

# #cpp
# CPP_FOLDER = $(MonoHome)/cpp

# # Modules
# DYNAMICS_SO = $(PY_FOLDER)/dynamics$(PY_EXT)
# PLANETS_SO  = $(PY_FOLDER)/planets$(PY_EXT)

# # Sources per module
# DYNAMICS_SRC = $(CPP_FOLDER)/src/dynamics.cpp $(CPP_FOLDER)/bindings/bindings_dynamics.cpp
# PLANETS_SRC  = $(CPP_FOLDER)/src/planets.cpp  $(CPP_FOLDER)/bindings/bindings_planets.cpp

# MONOLITH_SRC = $(DYNAMICS_SRC) \
# 			   $(PLANETS_SRC)

# # Object files
# DYNAMICS_OBJ = $(patsubst $(CPP_FOLDER)/%.cpp,$(CPP_FOLDER)/obj/%.o,$(DYNAMICS_SRC))
# PLANETS_OBJ  = $(patsubst $(CPP_FOLDER)/%.cpp,$(CPP_FOLDER)/obj/%.o,$(PLANETS_SRC))

# # ---------------- Build rules ----------------
# # ---------------- Build rules ----------------

# .PHONY: all cov clean stubs

# all: CXXFLAGS := $(CXXFLAGS)
# all: $(DYNAMICS_SO) $(PLANETS_SO) stubs

# cov: clean
# cov: CXXFLAGS := $(CXXFLAGS_COV)
# cov: LDFLAGS += -fprofile-arcs -ftest-coverage
# cov: $(DYNAMICS_SO) $(PLANETS_SO) stubs

# # Compile .cpp -> .o
# $(CPP_FOLDER)/obj/%.o: $(CPP_FOLDER)/%.cpp
# 	@mkdir -p $(dir $@)
# 	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# # Build shared libraries
# $(DYNAMICS_SO): $(DYNAMICS_OBJ)
# 	@mkdir -p $(PY_FOLDER)
# 	$(CXX) $(CXXFLAGS) $(LDFLAGS) -shared $^ -o $@

# $(PLANETS_SO): $(PLANETS_OBJ)
# 	@mkdir -p $(PY_FOLDER)
# 	$(CXX) $(CXXFLAGS) $(LDFLAGS) -shared $^ -o $@

# # Stub generation
# stubs: $(PY_FOLDER)/dynamics.pyi $(PY_FOLDER)/planets.pyi

# $(PY_FOLDER)/dynamics.pyi: $(DYNAMICS_SO)
# 	@echo "Generating dynamics stubs..."
# 	pybind11-stubgen monolith.dynamics --output-dir $(PY_FOLDER)/stubs
# 	@cp $(PY_FOLDER)/stubs/monolith/dynamics.pyi $(PY_FOLDER)/dynamics.pyi
# 	@rm -rf $(PY_FOLDER)/stubs

# $(PY_FOLDER)/planets.pyi: $(PLANETS_SO)
# 	@echo "Generating planets stubs..."
# 	pybind11-stubgen monolith.planets --output-dir $(PY_FOLDER)/stubs
# 	@cp $(PY_FOLDER)/stubs/monolith/planets.pyi $(PY_FOLDER)/planets.pyi
# 	@rm -rf $(PY_FOLDER)/stubs

# # Clean
# clean:
# 	rm -rf $(CPP_FOLDER)/obj
# 	rm -f $(PY_FOLDER)/dynamics*$(PY_EXT) $(PY_FOLDER)/planets*$(PY_EXT)
# 	rm -f $(PY_FOLDER)/dynamics.pyi $(PY_FOLDER)/planets.pyi
# 	rm -rf dist/

#python
PY_FOLDER = $(MonoHome)/python/monolith
PY_EXT = $(shell python3-config --extension-suffix)

#cpp
CPP_FOLDER = $(MonoHome)/cpp

BUILD_DIR := build

.PHONY: all clean stubs stubs_clean cov spice

spice:
	python scripts/make_cspice.py --kernels

all:
	@mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake .. -DCMAKE_BUILD_TYPE=Release -D pybind11_DIR=$(python3 -m pybind11 --cmakedir)
	cmake --build $(BUILD_DIR) --target all -j$(nproc)

# cov:
# 	@mkdir -p $(BUILD_DIR)
# 	cd $(BUILD_DIR) && cmake .. \
# 		-DCOVERAGE=ON \
# 		-DCMAKE_BUILD_TYPE=Debug \
# 		-Dpybind11_DIR=$(PYBIND11_DIR)
# 	cmake --build $(BUILD_DIR) -- -j$$(nproc)
# 	cd $(BUILD_DIR) && ctest || true
# 	# Generate HTML report with gcovr (requires gcovr installed: pip install gcovr)
# 	gcovr -r . --html --html-details -o coverage.html
# 	@echo "Coverage report generated: $(BUILD_DIR)/coverage.html"


clean:
	@rm -rf $(BUILD_DIR)
	rm -f $(PY_FOLDER)/*$(PY_EXT)
	rm -rf dist/

clean_stubs:
	rm -f $(PY_FOLDER)/*.pyi
