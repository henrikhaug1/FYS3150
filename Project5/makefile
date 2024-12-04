CC = c++-14
FLAGS = -Iinclude -larmadillo -lsuperlu -lblas -llapack

.PHONY: all clean

all: main

main: main.cpp src/PDEModel.cpp
	$(CC) main.cpp src/PDEModel.cpp $(FLAGS) -o main

run_all: all
	./main &

clean:
	rm -f main
	rm -f Potential_2.csv
	rm -f Prob_vec_2.csv
	rm -f animation.mp4







