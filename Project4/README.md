# FYS3150 Project3

## File organization:
This project is organized inside the Project4 folder in this manner:
- Project4 folder contains all main files needed to run the code for this project, a src folder, a include folder and a txt_files folder.
- src: contains the .cpp files for the class IsingModel, and the parallelized version of the class IsingModel, and the .py files needed for plotting in this project. 
- include: contains the headerfile for the .cpp files located in src.

## Compiling and running the whole project 
- However it is strongly recommended to use provided text files located in txt_files for plotting instead of making your own by running main_parallel.cpp

- make
- make run_all
- python3 src/plotting.py

## Compiling and running the whole project (recommended)
- make main
- ./main
- python3 src/plotting.py

#### Note: parallel part
There is no need to compile and run main_parallel.cpp, the data produced by doing this is computationaly heavy, and already provided in the folder txt_files.
There is therefore only necessary to compile and run main.cpp to get produce the figures.  


## Compiling and running files without using make:
### main.cpp:
    c++-14 main.cpp src/IsingModel.cpp src/IsingModel.cpp -Iinclude -larmadillo -o main
    ./main

### main_parallel.cpp:
    c++-14 main_parallel.cpp src/IsingModel_parallel.cpp -Iinclude -larmadillo -fopenmp -o main_parallel
    ./main_parallel

### Note 
#### Libraries
To run this code it is necessary to have the Armadillo (for linear algebra operations) and OpenMP (for shared memory parallel programming with threads) libraries on your computer.
- Armadillo: for linear algebra operations
- OpenMP: for shared memory parallel programming with threads

#### Compiler
To compile this project, we used the Clang C++ compiler. If it's not available on your system, you can also compile the project using the GNU C++ compiler (g++).
