CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

SRC = src/*.cpp
TARGET = run_graph.out

all:
	@$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: all
	@./$(TARGET)
	@rm $(TARGET)

clean:
	@rm $(TARGET)