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
        std::cout << u[p] << std::endl;
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
        std::cout << u_normalised[p] << std::endl;
    }

    return u_normalised;
}

void PDEModel::set_initial_boundary_conditions(arma::mat hello)
{

}

arma::mat PDEModel::construct_u_matrix()
{


}

arma::vec PDEModel::construct_u_vector()
{

}

int pair_to_single_index(int i, int j, int M)
{
    return j * M + i;
}

arma::mat PDEModel::construct_A_B(arma::vec a, arma::vec b, double r, int M)
{
    arma::mat A((M-2) * (M-2), (M-2) * (M-2), arma::fill::zeros);
    arma::mat B((M-2) * (M-2), (M-2) * (M-2), arma::fill::zeros);


    // making first super diag 
    arma::vec A_super = arma::vec((M-2) * (M-2) - 1, arma::fill::value(-r));
    arma::vec A_sub = arma::vec((M-2) * (M-2) - 1, arma::fill::value(-r));

    arma::vec B_super = arma::vec((M-2) * (M-2) - 1, arma::fill::value(r));
    arma::vec B_sub = arma::vec((M-2) * (M-2) - 1, arma::fill::value(r));


    for(int i = 1; i < (M-2) * (M-2) - 1; i++)
    {
        if(i % (M-2) == 0)
        {
            A_super(i-1) = 0;
            A_sub(i-1) = 0;
            B_super(i-1) = 0;
            B_sub(i-1) = 0;
        }
    }

    int idx_r_diag = (M - 2);
    A.diag(0) = a;
    A.diag(idx_r_diag).fill(-r);
    A.diag(-idx_r_diag).fill(-r);
    A.diag(1) = A_super;
    A.diag(-1) = A_sub;

    B.diag(0) = b;
    B.diag(idx_r_diag).fill(r);
    B.diag(-idx_r_diag).fill(r);
    B.diag(1) = B_super;
    B.diag(-1) = B_sub;


    // A.print("A\n");
    // B.print("B\n");


}



void PDEModel::crank_nicolson(arma::mat A, arma::mat B, arma::vec u)
{

}


