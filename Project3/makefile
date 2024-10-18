CC = g++-14
IFLAG = -Iinclude

.PHONY: all clean

all: main

main: 
	$(CC) main_ny.cpp src/Particle.cpp src/PenningTrap.cpp $(IFLAG) -larmadillo -o main

run_all: all
	./main &

clean:
	rm -f main
	rm -f xyz_analytical.txt
	rm -f xyz_RK4_1.txt
	rm -f xyz_RK4_2.txt
	rm -f xyz_RK4_interactions_1.txt
	rm -f xyz_RK4_interactions_2.txt
	rm -f xyz_FE.txt

