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
    $(TEST_DIR)/funcs.cpp

# Исключаем main.cpp из исходников для тестов
PROJECT_SRC_WITHOUT_MAIN = $(filter-out $(MAIN_SRC), $(PROJECT_SRC))
PROJECT_OBJ_WITHOUT_MAIN = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(PROJECT_SRC_WITHOUT_MAIN))
TEST_OBJ = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(TEST_SRC))

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(PROJECT_OBJ) $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

test: $(TEST_TARGET)
	@echo "Running tests..."
	@if [ -z "$$DISPLAY" ]; then \
		echo "No DISPLAY found, using xvfb-run..."; \
		xvfb-run --auto-servernum --server-args="-screen 0 1024x768x24" ./$(TEST_TARGET); \
	else \
		./$(TEST_TARGET); \
	fi

# Собираем тесты (используем объектные файлы проекта без main.o)
$(TEST_TARGET): $(TEST_OBJ) $(PROJECT_OBJ_WITHOUT_MAIN)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(GTEST_LDFLAGS)

# Общий шаблон для сборки объектов
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(TEST_TARGET)