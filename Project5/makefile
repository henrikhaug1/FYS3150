CC = c++-14
FLAGS = -Iinclude -larmadillo

.PHONY: all clean

all: main

main: main.cpp src/PDEModel.cpp
	$(CC) main.cpp src/PDEModel.cpp $(FLAGS) -o main

run_all: all
	./main &

clean:
	rm -f main
	rm -f Potential.csv
	rm -f Prob_vec.csv
	rm -f U_imag.csv
	rm -f U_Real.csv
	rm -f P.csv







