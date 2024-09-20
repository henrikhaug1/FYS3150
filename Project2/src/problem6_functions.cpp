#include <iostream>
#include <armadillo>
#include "problem2_functions.hpp"
#include "problem3_functions.hpp"
#include "problem4_functions.hpp"
#include "problem5_functions.hpp"
#include "problem6_functions.hpp"


void compare_write_to_file(){

	const int N = 10;
	double eps = 1.0e-8;
	arma::vec eigenvalues;
	arma::mat eigenvectors;
	const int maxiter = 10000;
	int iterations;
	bool converged;
	int width = 20;


	arma::mat A = set_up_A_matrix(N);

	jacobi_eigensolver(A, eps, eigenvalues, eigenvectors, maxiter, iterations, converged);



	eigenvalues.print("Eigenvalues:");
    eigenvectors.print("Eigenvectors:");

    // Write eigenvalues to a file
    eigenvalues.save("eigenvalues.txt", arma::raw_ascii);

    // Write eigenvectors to a file
    eigenvectors.save("eigenvectors.txt", arma::raw_ascii);

    // Optionally, print a message to the console indicating that the files were saved
    std::cout << "Eigenvalues and eigenvectors saved to files 'eigenvalues.txt' and 'eigenvectors.txt'." << std::endl;

}
