# FYS3150 Project 4

## File organization
This project is organized inside the Project4 folder in this manner:
- Project4 folder contains all main files needed to run the code for this project, a src folder, an include folder and folders with text files;  txt_burn_in, txt_heavy and txt_histogram.
- src: contains the .cpp files for the class IsingModel, the parallelized version of the class IsingModel, and the .py files needed for plotting in this project. 
- include: contains the headerfile for the .cpp files located in src.
- txt_burn_in: text files for the temperature 1.0 and 2.4 for ordered and unordered intitial state (used for problem 5, finding the burn-in time).
- txt_heavy: text files for energy, magnetizaion, heat capacity and susceptibility for lattice sizes L = [40, 60, 80, 100] (used for problem 8)
- txt_histogram: contains the same types of data as the txt_burn_in folder, but for ajusted equlibrium step (1 000 000 Monte Carlo cycles).

## Compiling and running the whole project 
It is strongly recommended to use provided text files located in txt_burn_in, txt_heavy and txt_histogram for plotting

    make
    make run_all
    python3 src/plotting.py

## Compiling and running the whole project (recommended)
    make main
    ./main
    python3 src/plotting.py

#### Note: parallel part
There is no need to compile and run main_parallel.cpp, the data produced by doing this is computationaly heavy, and already provided in the folder txt_heavy.
There is therefore only necessary to compile and run main.cpp to produce the figures and data for this project.  


## Compiling and running files without using make:
### main.cpp:
    c++-14 main.cpp src/IsingModel.cpp -Iinclude -larmadillo -o main
    ./main

### main_parallel.cpp:
    c++-14 main_parallel.cpp src/IsingModel_parallel.cpp -Iinclude -larmadillo -fopenmp -o main_parallel
    ./main_parallel

### Note 
#### Libraries
To run this code it is necessary to have the Armadillo and OpenMP libraries on your computer.
- Armadillo: for linear algebra operations
- OpenMP: for shared memory parallel programming with threads

#### Compiler
To compile this project, we used the Clang C++ compiler. If it's not available on your system, you can also compile the project using the GNU C++ compiler (g++).

#### Make clean
To remove all executable files, .txt files, and .pdf files, run the following command

    make clean 
