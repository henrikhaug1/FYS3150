CC = g++-14
IFLAG = -Iinclude

.PHONY: all clean

all: problem2_main problem3_main problem3_test_main

problem2_main:
	$(CC) problem2_main.cpp src/problem2_functions.cpp $(IFLAG) -larmadillo -o problem2_main

problem3_main:
	$(CC) problem3_main.cpp src/problem3_functions.cpp $(IFLAG) -larmadillo -o problem3_main

problem3_test_main:
	$(CC) problem3_test_main.cpp src/problem3_test_functions.cpp $(IFLAG) -larmadillo -o problem3_test_main

run_all: all
	./problem2_main &
	./problem3_main &
	./problem3_test_main &

clean:
	rm -f problem2_main
	rm -f problem3_main
	rm -f problem3_test_main
