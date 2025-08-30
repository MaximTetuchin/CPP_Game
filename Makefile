CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I./source -I./gtests
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
GTEST_LDFLAGS = -lgtest -pthread

BUILD_DIR = build
SRC_DIR = source
TEST_DIR = gtests

TARGET = CPP_Game
TEST_TARGET = $(BUILD_DIR)/test_runner

MAIN_SRC = main.cpp
PROJECT_SRC = $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/**/*.cpp)
PROJECT_OBJ = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(PROJECT_SRC))
MAIN_OBJ = $(BUILD_DIR)/$(MAIN_SRC:.cpp=.o)

TEST_SRC = \
    $(TEST_DIR)/test_gtest.cpp \
    $(TEST_DIR)/funcs.cpp \
    $(PROJECT_SRC)  # <-- добавляем все исходники проекта для тестов

TEST_OBJ = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(TEST_SRC))

.PHONY: all clean test prj

all: prj test

prj: $(TARGET)

test: $(TEST_TARGET)
	@echo "Running tests..."
	./$(TEST_TARGET)

# Собираем основной проект
$(TARGET): $(PROJECT_OBJ) $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Собираем тесты (линкер видит все cpp проекта)
$(TEST_TARGET): $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(GTEST_LDFLAGS)

# Общий шаблон для сборки объектов
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(TEST_TARGET)
