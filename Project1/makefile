CC = g++-14 
IFLAG = -Iinclude

.PHONY: all clean 

all: problem2_main problem7_main problem8_main problem9_main problem10_main

problem2_main: 
	$(CC) problem2_main.cpp src/problem2_functions.cpp $(IFLAG) -larmadillo -o problem2_main

problem7_main: 
	$(CC) problem7_main.cpp src/problem7_functions.cpp -Iinclude -larmadillo -o problem7_main

problem8_main: 
	$(CC) problem8_main.cpp src/problem8_functions.cpp -Iinclude -larmadillo -o problem8_main

problem9_main: 
	$(CC) problem9_main.cpp src/problem9_functions.cpp -Iinclude -larmadillo -o problem9_main

problem10_main: 
	$(CC) problem10_main.cpp src/problem10_functions.cpp -Iinclude -larmadillo -o problem10_main

clean:
	rm -f problem2_main
	rm -f problem7_main
	rm -f problem8_main
	rm -f problem9_main
	rm -f problem10_main