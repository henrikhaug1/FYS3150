CC = g++-14 
IFLAG = -Iinclude

.PHONY: all clean 

all: problem2_main problem7_main problem8_main problem9_main problem10_main

problem2: 
	$(CC) problem2_main.cpp src/problem2_functions.cpp $(IFLAG) -larmadillo -o problem2_main

problem7: 
	$(CC) problem7_main.cpp src/problem7_functions.cpp $(IFLAG) -larmadillo -o problem7_main

problem8: 
	$(CC) problem8_main.cpp src/problem8_functions.cpp $(IFLAG) -larmadillo -o problem8_main

problem9: 
	$(CC) problem9_main.cpp src/problem9_functions.cpp $(IFLAG) -larmadillo -o problem9_main

problem10: 
	$(CC) problem10_main.cpp src/problem10_functions.cpp src/problem7_functions.cpp src/problem9_functions.cpp $(IFLAG) -larmadillo -o problem10_main

run_all: all
	./problem2_main &
	./problem7_main &
	./problem8_main &
	./problem9_main	&
	./problem10_main &
	wait

plot: problem2_main problem7_main problem8_main
	python3 problem2_plotting.py problem7_plotting.py problem8_plotting.py

clean:
	rm -f problem2_main
	rm -f problem7_main
	rm -f problem8_main
	rm -f problem9_main
	rm -f problem10_main
	rm -f problem7_v_x_10steps.txt
	rm -f problem7_v_x_100steps.txt
	rm -f problem7_v_x_1000steps.txt
	rm -f problem7_v_x_10000steps.txt
	rm -f problem7_v_x_100000steps.txt
	rm -f h-approx-exact10.txt
	rm -f h-approx-exact100.txt
	rm -f h-approx-exact1000.txt
	rm -f log10_relative_error_h.pdf
	rm -f log10_absolute_error_h.pdf
	rm -f x_and_ux_values_output.txt
	rm -f plot_comparing_exact_numerical.pdf
	rm -f problem2_ux_plot.pdf

