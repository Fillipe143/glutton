.SILENT:

CXX = gcc
CXXFLAGS = -lSDL2

SRCS = src/*.c
TARGET = bin/glutton

build:
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

run: build
	./$(TARGET)
