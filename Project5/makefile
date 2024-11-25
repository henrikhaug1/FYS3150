CC = c++-14
FLAGS = -Iinclude -larmadillo
OMPFLAGS = -fopenmp

.PHONY: all clean

all: main

main: main.cpp src/PDEModel.cpp
	$(CC) main.cpp src/PDEModel.cpp $(FLAGS) -o main

run_all: all
	./main &

clean:
	rm -f main