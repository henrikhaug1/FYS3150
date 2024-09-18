#include <iostream>
#include <armadillo>
#include "problem2_functions.hpp"
#include "problem3_functions.hpp"
#include "problem4_functions.hpp"
#include "problem5_functions.hpp"

// a) Estimating how the number of required transformations scale with the matrix size N
void jacobi_eigensolver(const arma::mat& A, double eps, arma::vec& eigenvalues, arma::mat& eigenvectors, 
                        const int maxiter, int& iterations, bool& converged) {

    arma::mat R = arma::eye(A.n_rows, A.n_rows); // Initialize eigenvectors to the identity matrix
    arma::mat A_copy = A;

    iterations = 0;
    converged = false;
    int k, l;

    // Check initial largest off-diagonal element
    double max_offdiag = max_offdiag_symmetric(A_copy, k, l);
    std::cout << "Initial max off-diagonal element: " << max_offdiag << std::endl;

    // Iterate up to the maximum number of iterations or until convergence
    for (iterations = 0; iterations < maxiter; iterations++) {
        // Find the indices of the largest off-diagonal element in A
        max_offdiag = max_offdiag_symmetric(A_copy, k, l);

        // Print for debugging
        std::cout << "Iteration " << iterations + 1 << ": max off-diagonal element = " << max_offdiag << std::endl;

        // If the largest off-diagonal element is smaller than eps, convergence is achieved
        if (fabs(max_offdiag) < eps) {
            converged = true;
            std::cout << "Size of matrix: " << A.n_rows << "X" << A.n_rows << ", Amount of transformations: " << iterations + 1 << std::endl;
            break;
        }

        // Perform Jacobi rotation
        jacobi_rotate(A_copy, R, k, l);

        // Check the updated matrix
        std::cout << "After rotation, A(" << k << ", " << l << ") = " << A_copy(k, l) << std::endl;
    }

    // If we reach the maximum number of iterations without convergence
    if (!converged) {
        std::cout << "Jacobi method did not converge within the maximum number of iterations." << std::endl;
    }
}


