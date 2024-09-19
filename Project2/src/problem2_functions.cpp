#include <iostream>
#include <armadillo>
#include <cmath>

arma::mat set_up_A_matrix(const int N){

    /* This function is taking a constant integer N as argument, 
    setting up a tridiagonal matrix A, and returning A*/

    double n = N + 1.0;
    double h = 1.0 / n;
    long double a = - 1.0 / (h * h);
    long double d = 2.0 / (h * h);

    //Setting up A-matrix
    arma::mat A(N, N);

    for (int i = 0; i < N; ++i) {

        A(i, i) = d;            // Maindiagonal

        if (i > 0) {
            A(i, i - 1) = a;    // Subdiagonal
        }

        if (i < N - 1) {
            A(i, i + 1) = a;    // Superdiagonal
        }
    }
    return A;
}

arma::vec solve_eigval(arma::mat A){

    /* This function is taking an armadillo matrix as argument, using arma:eig_sym to compute the eigenvalues 
    and eigenvectors, and returning an armadillo vector with all the eigenvalues*/

    arma::vec eigenvalues;
    arma::mat eigenvectors;

    arma::eig_sym(eigenvalues, eigenvectors, A);

    return eigenvalues;

}

arma::mat solve_eigvec(arma::mat A){

    /* This function is taking an armadillo matrix as argument, using arma:eig_sym to compute the eigenvalues 
    and eigenvectors, and returning an armadillo vector with all the eigenvalues*/

    arma::vec eigenvalues;
    arma::mat eigenvectors;

    arma::eig_sym(eigenvalues, eigenvectors, A);

    return eigenvectors;

}


void test_eigval_eigvec(arma::vec eigval, arma::mat eigvec){

    /* This test function checks that the eigenvalues and eigenvectors from 
    Armadillo agrees with the analytical result for N=6*/

    int N = eigval.n_rows;
    double n = N + 1.0;
    double h = 1.0 / n;
    long double a = - 1.0 / (h * h);
    long double d = 2.0 / (h * h);
    const double pi = M_PI;

    //Checks that the eigenvalues and eigenvectors agree with the analytical result
    arma::vec lamba(N);
    arma::mat v(N, N);

    for (int j = 1; j < N + 1; ++j){

        lamba(j-1) = d + 2 * a * cos(j * pi / (N + 1));     //Analytical lambda

        arma::vec v_temp(N);                                //Vector for each iteration

        for (int i = 1; i < N + 1; ++i){
            v_temp(i - 1) = (sin(j * i * pi / (N + 1)));    //Analytical eigenvector
        }
        
        arma::vec v_temp_norm = arma::normalise(v_temp);    //Need to normalize the vector
        v.row(j-1) = v_temp_norm.t();                       //Transposing and appending
    }

    //Printing analytical eigenvalues and eigenvectors
    lamba.print("Eigenvalues analytical:");
    std::cout << "\n";
    v.print("Eigenvectors analytical:"); //eigenvec 2 and 6 have the 'wrong' sign but that's okay, c_1 = c_4 = -1 is allowed
    std::cout << "\n";
    
    arma::vec lamba_diff = eigval - lamba;                  //Calculates difference in eigenvalues
    arma::mat v_diff(N, N);                                 //Calculates difference in eigenvectors

    //Finds the signs, ref sign differences in eigenvecs 2 and 6
    arma::mat v_sign = sign(v); 
    arma::mat eigvec_sign = sign(eigvec);

    //Loops over all eigenvectors
    for (int i = 0; i < N; ++i){

        if( v_sign.col(i)[0] == eigvec_sign.col(i)[0] ) {   //Checks if the signs are in agreement
            v_diff.col(i) = v.col(i) - eigvec.col(i);       //If they are; Subtract
        }

        else{
            v_diff.col(i) = v.col(i) + eigvec.col(i);       //If they are not; Double negative
        }
    }

    //Printing the difference between numerical and analytical eigenvalues and eigenvectors
    lamba_diff.print("Difference between numerical and analytical eigenvalues:");
    std::cout << "\n";

    v_diff.print("Difference between numerical and analytical eigenvectors:");

}
