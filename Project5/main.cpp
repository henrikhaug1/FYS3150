#include "PDEModel.hpp"
#include <iostream>
#include <armadillo>
#include <iomanip> // For setting precision

void save_matrix_to_csv(const arma::mat& matrix, const std::string& filename) {
    std::ofstream file(filename);
    for (size_t i = 0; i < matrix.n_rows; ++i) {
        for (size_t j = 0; j < matrix.n_cols; ++j) {
            file << matrix(i, j);
            if (j < matrix.n_cols - 1) {
                file << ","; 
            }
        }
        file << "\n";  
    }
    file.close();
}
void save_vector_to_csv(const arma::vec& vec, const std::string& filename) {
    std::ofstream file(filename);

    // Set precision to 16 decimal places
    file << std::setprecision(16) << std::scientific;

    for (size_t i = 0; i < vec.n_elem; ++i) {
        file << vec[i];
        if (i < vec.n_elem - 1) {
            file << ","; // Use comma as a separator
        }
    }
    file << "\n"; // Add a newline at the end
    file.close();
}

int main()
{
    double dt = 2.5e-5;
    double T = 0.008;
    arma::vec t = arma::regspace(0, dt, T);
    int timesteps = t.n_elem;                   
    double dx = 0.005;
    double dy = 0.005;
    int M = 100;
    double x_c = 0.25;
    double y_c = 0.5;
    double p_x = 200.0;
    double p_y = 0.0;
    double sigma_x = 0.05;
    double sigma_y = 0.05;

    PDEModel model(dt, dx, dy, x_c, y_c, sigma_x, sigma_y, p_x, p_y); //Creating model

    arma::mat V(M-2, M-2, arma::fill::zeros);               //Creating potential
    double v_0 = 1e10;
    int nr_slits = 2;
    double thickness = 0.02;
    double centre = 0.5;
    double middle_wall = 0.05;
    double opening = 0.05;
    model.construct_potential(V, v_0, M, nr_slits, thickness, centre, middle_wall, opening);
    save_matrix_to_csv(V, "Potential.csv");        //Saving the potential for plotting

    auto result = model.construct_A_B(M, dx, dt, V);        //Creating A and B using potential
    arma::sp_cx_mat A = std::get<0>(result);
    arma::sp_cx_mat B = std::get<1>(result);

    arma::cx_vec u = model.initial_state(M);   //Initializing initial state
    u = model.normalised_initial_state(u);     //Normalizes initial state

    arma::cx_mat U((M-2) * (M-2), timesteps);   //Will store all the time iterations of u
    U.col(0) = u;                               //Saving first u
    for (size_t i = 1; i < timesteps; ++i)      //Finding the u of all time steps
    {
        arma::cx_vec u_1 = model.crank_nicolson(A, B, U.col(i-1)); //Finding next u
        U.col(i) = u_1;                                            //Saving the next u
        // std::cout << u_1((M-2) * (M-2) / 2) << std::endl;
        std::cout << i << std::endl;
    }
    arma::cx_mat U_conj = arma::conj(U);
    arma::mat P = arma::real(U_conj % U);       //This P matrix is a 2D one representing a 3D one

    arma::mat U_real = arma::real(U);
    arma::mat U_imag = arma::imag(U);

    save_matrix_to_csv(P, "P.csv");
    save_matrix_to_csv(U_real, "U_Real.csv");
    save_matrix_to_csv(U_imag, "U_imag.csv");

    arma::vec p(timesteps);
    for(size_t i = 0; i < timesteps; ++i){
        p(i) = arma::accu(P.col(i));        //Summing up all the probabilites of each time step
    }
    save_vector_to_csv(p, "Prob_vec.csv");

    //Plotting code to see structure of A or B matrix
    // std::cout << "Shape of Matrices A and B" << std::endl;
    // model.print_sp_matrix_structure(A);
    // model.print_sp_matrix_structure(B);

	return 0;
}