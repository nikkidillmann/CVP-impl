CC=g++ -g -Wall -std=c++17

# List of source files
SOURCES=src/lll_algorithm.cpp src/vector_ops.cpp test_lll.cpp 

# Generate the names of the object files
OBJS=lll_algorithm.o vector_ops.o test_lll.o

# Compile the file server and tag this compilation
all: ${OBJS} 
	${CC} -o $@ $^ 

test: ${TESTS}
	${CC} -o $@ $^


# Generic rules for compiling a source file to an object file
%.o: %.cpp
	${CC} -c $<
%.o: %.cc
	${CC} -c $<

build:
	mkdir -p build && cd build && cmake .. && make

clean:
	rm -f ${OBJS} all

.PHONY: build

