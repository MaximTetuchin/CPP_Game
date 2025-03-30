CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I./source -I./gtests
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
GTEST_LDFLAGS = -lgtest -pthread

BUILD_DIR = build
SRC_DIR = source
TEST_DIR = gtests

TARGET = CPP_Game
TEST_TARGET = $(BUILD_DIR)/test_runner

# Основной проект
MAIN_SRC = main.cpp
PROJECT_SRC = $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/**/*.cpp)
PROJECT_OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/$(SRC_DIR)/%.o, $(PROJECT_SRC))
MAIN_OBJ = $(BUILD_DIR)/$(MAIN_SRC:.cpp=.o)

# Тесты
TEST_SRC = \
    $(TEST_DIR)/test_gtest.cpp \
    $(TEST_DIR)/simple_func.cpp

TEST_OBJ = $(patsubst $(TEST_DIR)/%.cpp, $(BUILD_DIR)/$(TEST_DIR)/%.o, $(TEST_SRC))

.PHONY: all clean test prj

prj: $(TARGET)
test: $(TEST_TARGET)
	@echo "Running tests..."
	./$(TEST_TARGET)

$(TARGET): $(PROJECT_OBJ) $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(TEST_TARGET): $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(GTEST_LDFLAGS)

# Правила компиляции
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/$(TEST_DIR)/%.o: $(TEST_DIR)/%.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(TEST_TARGET)