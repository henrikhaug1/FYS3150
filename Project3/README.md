# FYS3150 Project3

## File organization:
This project is organized inside the Project3 folder in this manner:
- Project3 folder contains all main.cpp files and all .pdf and .txt will be saved here after running programs.
- src folder: includes all the .cpp and .py scripts
- include folder: includes headers


## How to compile and run this project:

- make (to compile all .cpp files)
- make run_all (to run all executable files)
- make example.cpp (to compile specific .cpp file)
- make clean (clean all executables, plots and .txt files)

### Example1: Compiling and running the whole project
- make
- make run_all

### Example2: compiling and running
- make main
- ./main


# Compiling .cpp files without using make:

## main:
    g++-14 main.cpp src/Particle.cpp src/PenningTrap.cpp -Iinclude -larmadillo -o main
