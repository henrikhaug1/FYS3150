#include <iostream>
#include <armadillo>
#include <cmath>

    // sets up the tridiagonal matrix A for N = 6
    // Solves A v = lamba v      using Armadillo’s arma::eig_sym

    // checks that the eigenvalues and eigenvectors from Armadillo agrees with the analytical result for N = 6 
arma::mat set_up_A_matrix(const int N){
    //Defining values
    double n = N + 1.0; //Will divide by n later -> needs to be a float
    double h = 1.0 / n; //Defining h
    long double a = - 1.0 / (h * h); //Defining a
    long double; //Defining d

    //Matrix A
    arma::mat A(N, N); //Defining size of matrix A 
    for (int i = 0; i < N; ++i) {   //Loops over all values of N (size of A)
        A(i, i) = d;  // Main diagonal
        if (i > 0) {
            A(i, i - 1) = a;  // Subdiagonal
        }
        if (i < N - 1) {
            A(i, i + 1) = a;  // Superdiagonal
        }
    }
    return A;
}

arma::vec solve_eigval(arma::mat A){
    //Solving the matrix equation using arma::eig_sym
    arma::vec eigenvalues; //Withdraws the values from arma
    arma::mat eigenvectors;

    arma::eig_sym(eigenvalues, eigenvectors, A); //Calculates the eigenvalues and eigenvectors

    return eigenvalues;

}

arma::mat solve_eigvec(arma::mat A){
    //Solving the matrix equation using arma::eig_sym
    arma::vec eigenvalues; //Withdraws the values from arma
    arma::mat eigenvectors;

    arma::eig_sym(eigenvalues, eigenvectors, A); //Calculates the eigenvalues and eigenvectors

    return eigenvectors;

}


void check_eigval_eigvec(arma::vec eigval, arma::mat eigvec){

    int N = eigval.n_rows;
    double n = N + 1.0; //Will divide by n later -> needs to be a float
    double h = 1.0 / n; //Defining h
    long double a = - 1.0 / (h * h); //Defining a
    long double d = 2.0 / (h * h); //Defining d
    const double pi = M_PI; //Defining pi
    //Checks that the eigenvalues and eigenvectors agree with the analytical result
    arma::vec lamba(N);
    arma::mat v(N, N);

    for (int j = 1; j < N + 1; ++j){  //i between 1 and 6
        lamba(j-1) = d + 2 * a * cos(j * pi / (N + 1)); //ANALytical lambda

        arma::vec v_temp(N); //Vector for each iteration
        for (int i = 1; i < N + 1; ++i){ //j between 1 and 6
            v_temp(i - 1) = (sin(j * i * pi / (N + 1))); //ANALytical eigenvector
        }
        
        arma::vec v_temp_norm = arma::normalise(v_temp); //Need to normalize the vector
        v.row(j-1) = v_temp_norm.t(); //Transposing and appending
    }

    lamba.print("lamba analytical"); //To see analytical eigen val/vec
    v.print("vec analytical"); //eigenvec 2 and 6 have the 'wrong' sign but that's okay, c_1 = c_4 = -1 is allowed
 
    arma::vec lamba_diff = eigval - lamba; //Calculates difference in eigenvalues
    arma::mat v_diff(N, N); //Difference in eigenvectors

    arma::mat v_sign = sign(v); //Finds the signs, ref sign differences in eigenvecs 2 and 6
    arma::mat eigvec_sign = sign(eigvec);

    for (int i = 0; i < N; ++i){  //Loops over all eigenvectors
        if( v_sign.col(i)[0] == eigvec_sign.col(i)[0] ) {  //Checks if the signs are in agreement
            v_diff.col(i) = v.col(i) - eigvec.col(i); //If they are; Subtract
        }
        else{
            v_diff.col(i) = v.col(i) + eigvec.col(i); //If they are'nt; Double negative
        }
    }

    lamba_diff.print("Difference between numerical and analytical eigenvalues");
    v_diff.print("Difference between numerical and analytical eigenvectors");

}
