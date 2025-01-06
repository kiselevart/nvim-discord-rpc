CXX = clang++
CXXFLAGS = -I./cpp

LIB_DIR = lib
CPP_DIR = cpp
SRC_DIR = src
OBJ_DIR = obj

# Find all source files from both directories
CPP_SRC = $(wildcard $(CPP_DIR)/*.cpp)
SRC_SRC = $(wildcard $(SRC_DIR)/*.cpp)

# Generate object files paths
CPP_OBJ = $(CPP_SRC:$(CPP_DIR)/%.cpp=$(OBJ_DIR)/%.o)
SRC_OBJ = $(SRC_SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Combine all object files
OBJ = $(CPP_OBJ) $(SRC_OBJ)

EXEC = discord-rpc

.PHONY: all clean debug

all: $(EXEC)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(EXEC): $(OBJ)
	$(CXX) -v $^ $(LIB_DIR)/discord_game_sdk.dylib -Wl,-rpath,@executable_path/$(LIB_DIR) -o $@

# Rule for compiling cpp directory files
$(OBJ_DIR)/%.o: $(CPP_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# Rule for compiling src directory files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

-include $(OBJ:%.o=%.d)

clean:
	rm -rf $(OBJ_DIR) $(EXEC)

debug:
	@echo "CPP source files:"
	@echo $(CPP_SRC)
	@echo "SRC source files:"
	@echo $(SRC_SRC)
	@echo "Object files:"
	@echo $(OBJ)
