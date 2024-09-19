#include <iostream>
#include <armadillo>
#include "problem2_functions.hpp"
#include "problem3_functions.hpp"
#include "problem4_functions.hpp"
#include "problem5_functions.hpp"

// a)
void jacobi_eigensolver(const arma::mat& A, double eps, arma::vec& eigenvalues, arma::mat& eigenvectors, 
                        const int maxiter, int& iterations, bool& converged){

    /* This function is writing the number of similarity transformations required for matrices with 
    different size N to a table*/

    arma::mat R = arma::eye(A.n_rows, A.n_rows); // Initialize eigenvectors to the identity matrix
    arma::mat A_copy = A;

    iterations = 0;
    converged = false;
    int k;
    int l;

    // Iterate up to the maximum number of iterations or until convergence
    for (iterations = 0; iterations < maxiter; iterations++) {
        double max_offdiag = max_offdiag_symmetric(A_copy, k, l);

        // If the largest off-diagonal element is smaller than eps, set convergance to true
        if (fabs(max_offdiag) < eps) {
            converged = true;
            std::cout << "Size of matrix: " << A.n_rows << "X" << A.n_rows << ", Amount of transformations: " << iterations << std::endl;
            break;
        }
        
        jacobi_rotate(A_copy, R, k, l); //rotate
    }
}


