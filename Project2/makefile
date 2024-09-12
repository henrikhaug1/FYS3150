CC = g++-14
IFLAG = -Iinclude

.PHONY: all clean

all: problem2_main problem7_main problem8_main problem9_main problem10_main

problem2_main:
	$(CC) problem2_main.cpp src/problem2_functions.cpp $(IFLAG) -larmadillo -o problem2_main


run_all: all
	./problem2_main &

clean:
	rm -f problem2_main
