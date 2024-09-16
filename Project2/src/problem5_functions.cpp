#include <iostream>
#include <armadillo>
#include "problem2_functions.hpp"
#include "problem3_functions.hpp"
#include "problem4_functions.hpp"
#include "problem5_functions.hpp"

// a) Estimating how the number of required transformations scale with the matrix size N
void jacobi_eigensolver(const arma::mat& A, double eps, arma::vec& eigenvalues, arma::mat& eigenvectors, 
                        const int maxiter, int& iterations, bool& converged){

    arma::vec N = {5, 10, 20, 30};

    for(int i = 0; i < N.size(); ++i){

        arma::mat R = arma::eye(N[i], N[i]); // Initialize eigenvectors to the identity matrix
        arma::mat A_copy = set_up_A_matrix(N[i]); // Work on a copy of A to preserve the original matrix
        
        iterations = 0;
        converged = false;
        int k, l;

        // Iterate up to the maximum number of iterations or until convergence
        for (iterations = 0; iterations < maxiter; iterations++) {
            k, l = 0;
            // Find the indices of the largest off-diagonal element in A
            double max_offdiag = max_offdiag_symmetric(A_copy, k, l);

            // If the largest off-diagonal element is smaller than eps, set convergance to true
            if (fabs(max_offdiag) < eps) {
                converged = true;
                std::cout << "Size of matrix: " << N[i] << "X" << N[i] << ", Amount of transformations: " << iterations << std::endl;
                break;
            }

            jacobi_rotate(A_copy, R, k, l); //rotate
        }
    }
}


