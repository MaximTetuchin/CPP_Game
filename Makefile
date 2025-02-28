CXX = g++
CXXFLAGS = -std=c++17 -Werror -Wpedantic -Wall
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
GTEST_LDFLAGS = -lgtest -lgtest_main -pthread

SRC_DIR = source
TEST_DIR = gtests
BUILD_DIR = build

SRC_FILES = $(SRC_DIR)/simple_pic.cpp
SRC_OBJ = $(BUILD_DIR)/simple_pic.o
TEST_FILES = $(TEST_DIR)/test_gtest.cpp
TEST_OBJ = $(BUILD_DIR)/test_gtest.o
SIMPLE_FUNC_OBJ = $(BUILD_DIR)/simple_func.o

EXE = $(BUILD_DIR)/simple_pic
TEST_EXE = $(BUILD_DIR)/test_gtest

$(shell mkdir -p $(BUILD_DIR))

all: $(EXE)

$(EXE): $(SRC_OBJ) $(SIMPLE_FUNC_OBJ)
	$(CXX) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/simple_pic.o: $(SRC_DIR)/simple_pic.cpp $(SRC_DIR)/simple_func.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/simple_func.o: $(SRC_DIR)/simple_func.cpp $(SRC_DIR)/simple_func.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TEST_EXE)
	./$(TEST_EXE)

$(TEST_EXE): $(TEST_OBJ) $(BUILD_DIR)/simple_func.o
	$(CXX) $^ -o $@ $(LDFLAGS) $(GTEST_LDFLAGS)

$(BUILD_DIR)/test_gtest.o: $(TEST_FILES)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)/*