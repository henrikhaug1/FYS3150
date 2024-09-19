#include <iostream>
#include <armadillo>
#include <cmath>
#include "problem3_functions.hpp"

//a)
double max_offdiag_symmetric(const arma::mat& A, int& k, int& l){ //Takes in an armadillo matrix with references of two integers. 
// identifies the largest off-diagonal element (in absolute value) in the matrix, 
// under the assumption of a symmetric matrix

    int N = A.n_rows; //Gets the size N of an NxN matrix
    double offDiag = 0.0;
    for (int i = 0; i < N; ++i) {//Loops over all values of N (size of A)
        for (int j = 0; j < N; ++j){ //Again. LÖÖPS over all values in A
            if (i != j){ //Ignores the diagonal
                if (fabs(offDiag) < fabs(A(i, j))){ //Checks if the current offDiagonal value of A is larger than a previous one (absolute values)
                    offDiag = A(i, j); //New largest offDiagonal value found
                    k = i; //The integer references are updated for this value
                    l = j;
                }
            }
        }
    }
// writes the matrix indices for this element to the two integer references
    return offDiag; //Returns the largest off diagonal value with corresponding integer references
}

//b)
void test_max_offdiag_symmetric(){ //Test code with a predefined matrix

    int N = 4; 
    arma::mat A = arma::eye(N, N);

    A(3,0) = 0.5;
    A(2,1) = -0.7;
    A(1,2) = -0.7;
    A(0,3) = 0.5;

    double offDiag_returned = 0.0; //Defining variables 
    int l;
    int k;

    offDiag_returned = max_offdiag_symmetric(A, l, k); 
    std::cout << "Largest off-diagonal value in A: " << offDiag_returned << " (Absolute values) " << std::endl;
    std::cout << "k:" << k << " l:" << l << std::endl;
}