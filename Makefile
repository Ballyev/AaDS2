CXX = g++
CXXFLAGS = -I/usr/include/eigen3 -O3 -Wall -std=c++17
SOURCES = csv_matrix_io.cpp gaussian_solver.cpp main.cpp matrix_generator.cpp solver_tests.cpp
TARGET = linear_solver

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f $(TARGET) *.csv


test: $(TARGET)
	./$(TARGET) --test


format:
	clang-format -i $(SOURCES) linear_solver.h

lint:
	cppcheck $(SOURCES) linear_solver.h

.PHONY: all clean test format lint