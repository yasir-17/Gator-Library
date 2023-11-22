CXX = g++
CXXFLAGS = -std=c++17 -Wall
TARGET = gatorLibrary 
SRCS = main.cpp GatorLibrary.cpp RedBlackTree.cpp ReservationHeap.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)
	@echo Compilation successful

$(TARGET): $(OBJS)
	@$(CXX) $(CXXFLAGS) -o $@ $^ 2> NUL
	@del /Q $(OBJS)  # Remove object files after building the executable on Windows

%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@ 2> NUL

run: $(TARGET)
	./$(TARGET)

clean:
	@del /Q $(TARGET)   
