CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

TARGET = ../build/thread-guard

SRC = thread-guard.cpp

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
