CC = g++-14
IFLAG = -Iinclude

.PHONY: all clean

all: main

problem2_main:
	$(CC) main.cpp src/Particle.cpp src/PenningTrap.cpp -Iinclude -larmadillo -o main

run_all: all
	./main &

clean:
	rm -f main
