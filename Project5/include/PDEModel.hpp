#ifndef __PDEModel_hpp__
#define __PDEModel_hpp__

#include <iostream>
#include <armadillo>
#include <vector>


class PDEModel
{
    public:
        double dt;
        double dx;
        double dy;
        double x_c;
        double y_c;
        double sigma_x;
        double sigma_y;
        double p_x;
        double p_y;
        


    // Constructor 
    PDEModel(double dt, double dx, double dy, 
               double x_c, double y_c, 
               double sigma_x, double sigma_y, 
               double p_x, double p_y);

    // Initial conditions u_ij^0
    std::vector<arma::cx_vec> initial_state(int M);

    std::vector<arma::cx_vec> normalised_initial_state(std::vector<arma::cx_vec> u);

    // setting initial and boundary conditions
    void set_initial_boundary_conditions(arma::mat hello);

    arma::mat construct_u_matrix();

    arma::vec construct_u_vector();

    int pair_to_single_index(int i, int j, int M);

    std::tuple<arma::sp_cx_mat,arma::sp_cx_mat> construct_A_B(arma::cx_double r, int M, arma::cx_vec& a, arma::cx_vec& b);

    void print_sp_matrix_structure(const arma::sp_cx_mat& A);

    void crank_nicolson(arma::mat A, arma::mat B, arma::vec u);


};

#endif