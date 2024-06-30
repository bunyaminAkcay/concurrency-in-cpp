CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

TARGET = ../build/hello-concurrency

SRC = hello-concurrency-world.cpp

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
