#include <iostream>
#include <armadillo>
#include <cmath>
#include "problem2_functions.hpp"
#include "problem3_functions.hpp"
#include "problem4_functions.hpp"

// a) Implementing Jacobi’s rotation algorithm
void jacobi_rotate(arma::mat& A, arma::mat& R, int k, int l){

    //Step 1)
    double eps = 1.0e-8; //Tolerance
    arma::mat A_1 = A; 
    arma::mat R_1 = R;
    int row = A.n_rows;
    int col = A.n_cols;

    //Step 2)

    double offDiag = max_offdiag_symmetric(A, k, l); 

    double a_kl = A(k, l); //Initial, needed to start the while loop

    //Step 3)
    while(fabs(a_kl) > eps){
        a_kl = A(k, l);  //First and continuing a_xx
        double a_ll = A(l, l);  //When continued, will get the a_xx_mp1 calculated in step 3.3
        double a_kk = A(k, k);
        double tau = (a_ll - a_kk) / (2 * a_kl);  //Step 3.1)
        double t_theta = 0.0;

        if(tau > 0){//Choose the solution that gives the smallest tθ. Step 3.2)
            double t_theta = 1 / (tau + sqrt(1 + tau * tau));
        } 

        else if(tau < 0){
            double t_theta = 1 / (tau - sqrt(1 + tau * tau));
        } 
        
        double c_theta = 1 / sqrt(1 + t_theta * t_theta);  //Equations from task.
        double s_theta = c_theta * t_theta;

        //Step 3.3
        double a_kk_mp1 = a_kk * c_theta * c_theta - 2 * a_kl * c_theta * s_theta + a_ll * s_theta * s_theta;  //Calculating next a_xx
        A(k, k) = a_kk_mp1; //Updating A
        double a_ll_mp1 = a_ll * c_theta * c_theta - 2 * a_kl * c_theta * s_theta + a_ll * s_theta * s_theta;  //Repeat
        A(l, l) = a_ll_mp1;
        double a_kl_mp1 = 0.0;
        A(k, l) = a_kl_mp1;
        double a_lk_mp1 = 0.0;
        A(l, k) = a_lk_mp1;

        for (int i = 0; i < row; ++i) {//Loops over all rows
            if(i != k and i != l){

                double a_ik = A(i, k);
                double a_il = A(i, l);
                double a_ik_mp1 = a_ik * c_theta - a_il * s_theta;

                A(i, k) = a_ik_mp1;
                double a_ki_mp1 = a_ik_mp1;

                A(k, i) = a_ki_mp1;
                double a_il_mp1 = a_il * c_theta + a_ik * s_theta;

                A(i, l) = a_il_mp1;
                double a_li_mp1 = a_il_mp1;

                A(l, i) = a_li_mp1;
            }

            //Step 3.4
            double r_ik = R(i, k);
            double r_il = R(i, l);
            double r_ik_mp1 = r_ik * c_theta - r_il * s_theta;

            R(i, k) = r_ik_mp1;
            double r_il_mp1 = r_il * c_theta + r_ik * s_theta;

            R(i, l) = r_il_mp1;
        }

        double offDiag = max_offdiag_symmetric(A, k, l); //Step 3.5
    }
}

void jacobi_test(){

    arma::mat A = arma::eye(4,4);

    A(3,0) = 0.5;
    A(2,1) = -0.7;
    A(1,2) = -0.7;
    A(0,3) = 0.5;

    std::cout << "Initial A = " << A << std::endl;

    int row = A.n_rows;
    int col = A.n_cols;

    arma::mat R = arma::eye(row, col);  //Identity matrix the size of A

    int k = 0;
    int l = 0;
    jacobi_rotate(A, R, k, l);

    std::cout << "End A = " << A << std::endl;
    std::cout << "End R = " << R << std::endl;
}

void jacobi_eigensolver(const arma::mat& A, double eps, arma::vec& eigenvalues, arma::mat& eigenvectors, 
                        const int maxiter, int& iterations, bool& converged){
    
    int N = A.n_rows; //Size of matrix

    //Seting up the tridiagonal matrix
    arma::mat A = set_up_A_matrix(N); 

    //Identity matrix the size of A
    arma::mat R = arma::eye(N, N);  

    int k = 0;
    int l = 0;

    //Runs jacobi_rotate until max off-diagonal element < eps
    jacobi_rotate(A, R, k, l); 
}
