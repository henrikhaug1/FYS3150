#include <iostream>
#include <armadillo>
#include <string>
#include <iomanip>
#include "problem2_functions.hpp"
#include "problem3_functions.hpp"
#include "problem4_functions.hpp"
#include "problem5_functions.hpp"

int main(){

	//a)
	double eps = 1.0e-8;
	arma::vec eigenvalues;
	arma::mat eigenvectors;
	const int maxiter = 10000;
	int iterations;
	bool converged;
	//arma::vec N = {5, 10, 15, 20, 50, 70};
	arma::vec N = {5, 10, 15};

	int width = 20;

	std::string filename = "N_vs_similarity_transformation.txt";
	std::ofstream ofile;
	ofile.open(filename);
	ofile << std::left << std::setw(width) << "N" << std::setw(width) << "similarity transformation" << std::endl;

	for(int i = 0; i < N.size(); ++i){
		arma::mat A = set_up_A_matrix(N[i]);
		jacobi_eigensolver(A, eps, eigenvalues, eigenvectors, maxiter, iterations, converged);
		A.print("A");
		eigenvalues.print("Eigenvalues");
		eigenvectors.print("Eigenvectors");
		//maxiter.print("maxiter");
		//iterations.print("iterations");
		//converged.print("converged");


		ofile << std::left << std::setw(width) << N[i] << std::setw(width) << iterations << std::endl; //making header for file


	}

	ofile.close();

	//b)
	// Generate random N*N matrix
	arma::mat A_dense = arma::randu<arma::mat>(10, 10);

	// Symmetrize the matrix by reflecting the upper triangle to lower triangle
	A_dense = arma::symmatu(A_dense); 

	jacobi_eigensolver(A_dense, eps, eigenvalues, eigenvectors, maxiter, iterations, converged);

	return 0;
}