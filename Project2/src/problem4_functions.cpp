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

    //Step 2) finding k and l 
    double offDiag = max_offdiag_symmetric(A, k, l);

    double a_kl = A(k, l); //Initial, needed to start the while loop

    //Step 3)
    while(fabs(a_kl) > eps){
        a_kl = A(k, l);  //First and continuing a_xx
        double a_ll = A(l, l);  //When continued, will get the a_xx_mp1 calculated in step 3.3
        double a_kk = A(k, k);

        //Step 3.1)
        double tau = (a_ll - a_kk) / (2 * a_kl);  
        
        //Step 3.2)
        double t_theta;

        if(tau > 0){ //Choose the solution that gives the smallest tθ. Step 3.2)
            double t_theta = 1 / (tau + sqrt(1 + tau * tau));
        } 

        else if(tau < 0){
            double t_theta = 1 / (tau - sqrt(1 + tau * tau));
        } 
        
        //Step 3.3
        double c_theta = 1 / sqrt(1 + t_theta * t_theta);
        double s_theta = c_theta * t_theta;

        
        double a_kk_mp1;
        a_kk_mp1 = a_kk * (c_theta * c_theta) - ( 2 * a_kl * (c_theta * s_theta) ) + a_ll * (s_theta * s_theta);  //Calculating next a_xx
        A(k, k) = a_kk_mp1; //Updating A

        double a_ll_mp1;
        a_ll_mp1 = a_ll * (c_theta * c_theta) + ( 2 * a_kl * (c_theta * s_theta) ) + a_kk * (s_theta * s_theta);  //Repeat
        A(l, l) = a_ll_mp1;

        double a_kl_mp1;
        a_kl_mp1 = 0.0;
        A(k, l) = a_kl_mp1;

        double a_lk_mp1;
        a_lk_mp1 = 0.0;
        A(l, k) = a_lk_mp1;

        // Updating all other elements where i!=k and i!=l
        for (int i = 0; i < row; ++i){


            if(i != k and i != l){

                double a_ik = A(i, k);
                double a_il = A(i, l);

                //A[i][k]
                double a_ik_mp1;
                a_ik_mp1 = (a_ik * c_theta) - (a_il * s_theta);
                A(i, k) = a_ik_mp1;

                //A[k][i]
                double a_ki_mp1;
                a_ki_mp1 = a_ik_mp1;
                A(k, i) = a_ki_mp1;

                //A[i][l]
                double a_il_mp1;
                a_il_mp1 = (a_il * c_theta) + (a_ik * s_theta);
                A(i, l) = a_il_mp1;

                //A[l][i]
                double a_li_mp1;
                a_li_mp1 = a_il_mp1;
                A(l, i) = a_li_mp1;
            }

            //Step 3.4
            double r_ik = R(i, k);
            double r_il = R(i, l);

            //R[i][k]
            double r_ik_mp1;
            r_ik_mp1 = (r_ik * c_theta) - (r_il * s_theta);
            R(i, k) = r_ik_mp1;

            //R[i][l]
            double r_il_mp1;
            r_il_mp1 = (r_il * c_theta) + (r_ik * s_theta);
            R(i, l) = r_il_mp1;
        }

        //Step 3.5
        double offDiag = max_offdiag_symmetric(A, k, l); 
    }
}



void test_jacobi_rotate(){

    int N = 6;
    arma::mat A = set_up_A_matrix(N);
    arma::mat R = arma::eye(N, N);
    int k = 0;
    int l = 0;

    jacobi_rotate(A, R, k, l);
    std::cout << "A-matrix with eigenvalues along the diagonal" << std::endl;
    A.print();

    std::cout << "R-matrix with eigenvectors as columns" << std::endl;
    R.print();


    //Analytical solution
    std::cout << "Calling test_jacobi_rotate() to compare with analytical results " << std::endl;
    arma::mat analytical_eigvec = solve_eigvec(A);
    arma::vec analytical_eigval = solve_eigval(A);

    analytic_eigval.print();
    analytic_eigvec.print();

}

