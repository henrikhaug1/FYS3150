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
