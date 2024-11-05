CC = c++-14
IFLAG = -Iinclude

.PHONY: all clean

all: main

main: main.cpp src/IsingModel.cpp
	$(CC) main.cpp src/IsingModel.cpp $(IFLAG) -larmadillo -o main

run_all: all
	./main &


clean:
	rm -f main
	rm -f energy_L20_T1.000000_ordered.txt
	rm -f energy_L20_T1.000000_unordered.txt
	rm -f energy_L20_T2.400000_ordered.txt
	rm -f energy_L20_T2.400000_unordered.txt

