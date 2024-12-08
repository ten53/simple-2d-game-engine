# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++17 -I"./include/" -I"./libs/lua/" -I"./libs/sol/" -I"./libs/imgui/"
LDFLAGS = -L"./libs/lua/" -llua -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -ldl

# Directories
SRC_DIR = src
BUILD_DIR = build

# Files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))
TARGET = engine

# Build rules
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

