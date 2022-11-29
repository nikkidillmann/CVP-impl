CC=g++ -g -Wall -std=c++17

# List of source files
SOURCES=lll_algorithm.cpp vector_ops.cpp test_lll.cpp 

# Generate the names of the object files
OBJS=${SOURCES:.cpp=.o}

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

