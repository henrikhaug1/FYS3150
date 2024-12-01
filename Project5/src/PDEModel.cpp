#include "PDEModel.hpp"

#include <iomanip>
#include <iostream>
#include <vector>

PDEModel::PDEModel(double dt_in, double dx_in, double dy_in, 
                   double x_c_in, double y_c_in, 
                   double sigma_x_in, double sigma_y_in, 
                   double p_x_in, double p_y_in)
{
    dt = dt_in;

    dx = dx_in;
    dy = dy_in;
    x_c = x_c_in;
    y_c = y_c_in;
    sigma_x = sigma_x_in;
    sigma_y = sigma_y_in;
    p_x = p_x_in;
    p_y = p_y_in;


}

std::vector<arma::cx_vec> PDEModel::initial_state(int M)
{
    std::vector<arma::cx_vec> u(M, arma::cx_vec(M, arma::fill::zeros));

    arma::vec x = arma::regspace(0, dx, M - 1); 
    arma::vec y = arma::regspace(0, dy, M - 1);


    std::complex<double> i(0, 1);


    for (int j = 0; j < M; ++j) 
    {
        arma::cx_vec u_element(M, arma::fill::zeros);
        double x_val = x[j];

        for(int k = 0; k < M; k++)
        {

            
            double y_val = y[k];

            std::complex<double> exponent = - (x_val - x_c) * (x_val - x_c) / (2 * sigma_x * sigma_x)
                                            - (y_val - y_c) * (y_val - y_c) / (2 * sigma_y * sigma_y)
                                            - i * p_x * x_val
                                            + i * p_y * y_val;

            u_element[k] = std::exp(exponent); // Assign the complex exponential value
        }

        u[j] = u_element;

    }

    for(int p = 0; p < M; p++)
    {
        p += 1;//std::cout << u[p] << std::endl;
    }

    return u;
}


std::vector<arma::cx_vec> PDEModel::normalised_initial_state(std::vector<arma::cx_vec> u)
{
    int M = u.size();
    std::vector<arma::cx_vec> u_normalised(M);

    for(int i = 0; i < M; i++)
    {
        u_normalised[i] = arma::normalise(u[i]);
    }


    for(int p = 0; p < M; p++)
    {
        p += 1;//std::cout << u_normalised[p] << std::endl;
    }

    return u_normalised;
}

void PDEModel::set_initial_boundary_conditions(arma::mat hello)
{

}

arma::mat PDEModel::construct_u_matrix()
{

    return 0;
}

arma::vec PDEModel::construct_u_vector()
{
    return 0;
}

int pair_to_single_index(int i, int j, int M)
{
    return j * M + i;
}

std::tuple<arma::sp_cx_mat,arma::sp_cx_mat> PDEModel::construct_A_B(arma::cx_double r, int M, arma::cx_vec& a, arma::cx_vec& b)
{
    int side_length = (M - 2) * (M - 2);
    arma::sp_cx_mat A(side_length, side_length);
    arma::sp_cx_mat B(side_length, side_length);

    // making diagonals
    arma::cx_vec r_diag_1(side_length - 1,   arma::fill::value(r));
    arma::cx_vec r_diag_2(side_length - (M - 2), arma::fill::value(r));

    //Removing Each M-2th diagonal 
    for(int i = 1; i < (M-2) * (M-2) - 1; i++)
    {
        if(i % (M-2) == 0)
        {
            r_diag_1(i-1) = 0;
        }
    }

    A.diag(0) = a;
    A.diag(1) = -r_diag_1; 
    A.diag(-1) = -r_diag_1;
    A.diag(M - 2) = -r_diag_2; 
    A.diag(- (M - 2)) = -r_diag_2;

    B.diag(0) = b;
    B.diag(1) = r_diag_1; 
    B.diag(-1) = r_diag_1;
    B.diag(M - 2) = r_diag_2; 
    B.diag(- (M - 2)) = r_diag_2;


    return std::make_tuple(A,B);
}

// A function that prints the structure of a sparse matrix to screen. Copy pasted from task.
void PDEModel::print_sp_matrix_structure(const arma::sp_cx_mat& A)
{
    using namespace std;
    using namespace arma;

    // Declare a C-style 2D array of strings.
    string S[A.n_rows][A.n_cols];  

    // Initialise all the strings to " ".
    for (int i =0; i < A.n_rows; i++)
    {
        for (int j = 0; j < A.n_cols; j++)
        {
            S[i][j] = " ";
        }
    }

    // Next, we want to set the string to a dot at each non-zero element.
    // To do this we use the special loop iterator from the sp_cx_mat class
    // to help us loop over only the non-zero matrix elements.
    sp_cx_mat::const_iterator it     = A.begin();
    sp_cx_mat::const_iterator it_end = A.end();

    int nnz = 0;
    for(it; it != it_end; ++it)
    {
        S[it.row()][it.col()] = "•";
        nnz++;
    }

    // Finally, print the matrix to screen.
    cout << endl;
    for (int i =0; i < A.n_rows; i++)
    {
        cout << "| ";
        for (int j = 0; j < A.n_cols; j++)
        {
            cout << S[i][j] << " ";
        }
        cout <<  "|\n";
    }

    cout << endl;
    cout << "matrix size: " << A.n_rows << "x" << A.n_cols << endl;
    cout << "non-zero elements: " << nnz << endl ;
    cout << endl;
}


void PDEModel::crank_nicolson(arma::mat A, arma::mat B, arma::vec u)
{

}


