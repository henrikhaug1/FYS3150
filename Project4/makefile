CC = c++-14
FLAGS = -Iinclude -larmadillo
OMPFLAGS = -fopenmp

.PHONY: all clean

all: main main_parallel

main: main.cpp src/IsingModel.cpp
	$(CC) main.cpp src/IsingModel.cpp $(FLAGS) -o main

main_parallel: main_parallel.cpp src/IsingModel_parallel.cpp
	$(CC) main_parallel.cpp src/IsingModel_parallel.cpp $(FLAGS) $(OMPFLAGS) -o main_parallel

run_all: all
	./main &

clean:
	rm -f main
	rm -f main_parallel
	rm -f energy_L20_T1.000000_ordered.txt
	rm -f energy_L20_T1.000000_unordered.txt
	rm -f energy_L20_T2.400000_ordered.txt
	rm -f energy_L20_T2.400000_unordered.txt
	rm -f L40_func_of_temp.txt
	rm -f L60_func_of_temp.txt
	rm -f L80_func_of_temp.txt
	rm -f L100_func_of_temp.txt
	rm -f L2_func_of_temp.txt
