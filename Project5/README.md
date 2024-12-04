# FYS3150 Project 5

## File organization
This project is organized inside the Project4 folder in this manner:
- Project5 folder contains a main file needed to run the code for this project, a src folder, an include folder and a folder with csv files; pre_computed.
- src: contains the .cpp file for the class PDEModel, and the .py files needed for plotting in this project. 
- include: contains the headerfile for the .cpp file located in src.
- pre_computed: csv files ...

## Compiling and running the whole project (with SuperLu)
If you have the correct verison of SuperLu on your computer, you can compile, run and produce simulations and animations as following 

    make
    make run_all
    python3 src/Plotting.py


## Compiling and running the whole project (without SuperLu)
If the correct version of SuperLu isn´t availible on your system, you can simply use the pre computed csv files stored in the folder pre_computer by only running the python file for plotting and simulations

    python3 src/Plotting.py


### Note 
#### Libraries
To run this code it is necessary to have the Armadillo and OpenMP libraries on your computer.
- Armadillo: for linear algebra operations
- SuperLu: for the direct solution of large, sparse, nonsymmetric systems of linear equations. 

#### Compiler
To compile this project, we used the Clang C++ compiler. If it's not available on your system, you can also compile the project using the GNU C++ compiler (g++).

#### Make clean
To remove all executable files, .csv files, .pdf files and .mp4 files, run the following command

    make clean 
