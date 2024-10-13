CC = g++-14
IFLAG = -Iinclude

.PHONY: all clean

all: main

main: 
	$(CC) main.cpp src/Particle.cpp src/PenningTrap.cpp $(IFLAG) -larmadillo -o main

run_all: all
	./main &

clean:
	rm -f main
	rm -f specific_analytical_z.txt
	rm -f specific_analytical_xy.txt
