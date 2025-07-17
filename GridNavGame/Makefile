CXX = g++
CXXFLAGS = -std=c++11 -Wall

OBJS = main.o textgames.o
TARGET = GridNavGame

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp textgames.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

textgames.o: textgames.cpp textgames.hpp
	$(CXX) $(CXXFLAGS) -c textgames.cpp

clean:
	rm -f $(OBJS) $(TARGET) 