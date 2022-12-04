CC=g++ -g -Wall -std=c++17

# List of source files
SOURCES=driver.cpp voronoi.cpp lll_algorithm.cpp cvpp.cpp cvp.cpp

# Generate the names of the object files
OBJS=${SOURCES:.cpp=.o}

# Compile the file server and tag this compilation
cvp: ${OBJS} 
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
	rm -f ${OBJS} all *.o

.PHONY: build

