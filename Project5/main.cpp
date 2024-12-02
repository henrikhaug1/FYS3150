#include "PDEModel.hpp"

#include <iostream>
#include <armadillo>


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

void save_complex_matrix_to_csv(const arma::cx_mat& matrix, const std::string& filename) {
    std::ofstream file(filename);
    for (size_t i = 0; i < matrix.n_rows; ++i) {
        for (size_t j = 0; j < matrix.n_cols; ++j) {
            file << matrix(i, j).real() << "+" << matrix(i, j).imag() << "i";
            if (j < matrix.n_cols - 1) {
                file << ","; 
            }
        }
        file << "\n"; 
    }
    file.close();
}

void save_cube_to_csv(const arma::cube& cube, const std::string& filename) {
    std::ofstream file(filename);
    for (size_t k = 0; k < cube.n_slices; ++k) {
        file << "# Slice " << k << "\n";  
        for (size_t i = 0; i < cube.n_rows; ++i) {
            for (size_t j = 0; j < cube.n_cols; ++j) {
                file << cube(i, j, k);
                if (j < cube.n_cols - 1) {
                    file << ","; 
                }
            }
            file << "\n"; 
        }
        file << "\n"; 
    }
    file.close();
}


int main()
{
    int M = 100;
    double dt = 0.001;//2.5e-5;
    double T = 5 * dt; //0.008
    arma::vec t = arma::regspace(0, dt, T);
    int timesteps = t.n_elem;                   
    double dx = 0.1;
    double dy = 0.1;
    double x_c = 0.25;
    double y_c = 0.5;
    double p_x = 200;
    double p_y = 0;
    double sigma_x = 0.05;
    double sigma_y = 0.05;

    PDEModel model(dt, dx, dy, x_c, y_c, sigma_x, sigma_y, p_x, p_y); //Creating model

    arma::mat V(M-2, M-2, arma::fill::zeros);               //Creating potential
    double v_0 = 1000000;
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
    u = model.normalised_initial_state(u);                  //Normalizes initial state

    arma::cx_mat U((M-2) * (M-2), timesteps);   //Will store all the time iterations of u
    U.col(0) = u;                               //Saving first u
    for (size_t i = 1; i < timesteps; ++i)      //Finding the u of all time steps
    {
        // std::cout << U.col(i) << std::endl;
        arma::cx_vec u_1 = model.crank_nicolson(A, B, U.col(i-1)); //Finding next u
        U.col(i) = u_1;                                            //Saving the next u
        std::cout << i << std::endl;
    }
    
    arma::cx_mat U_conj = arma::conj(U);
    arma::mat P = arma::real(U_conj % U);       //This P matrix is a 2D one representing a 3D one

    save_matrix_to_csv(P, "P.csv");

    // arma::cube P_3D(M-2, M-2, timesteps);       //Converting to 3D
    // for (size_t k = 0; k < timesteps; ++k) {
    //     for (size_t i = 0; i < (M-2); ++i) {
    //         for (size_t j = 0; j < (M-2); ++j) {
    //             size_t flat_index = i * (M-2) + j;
    //             P_3D(i, j, k) = P(flat_index, k);
    //         }
    //     }
    // }
    // std::cout << P_3D << std::endl;
    // save_cube_to_csv(P_3D, "P.csv");

    //Plotting code to see structure of A or B matrix
    // std::cout << "Shape of Matrices A and B" << std::endl;
    // model.print_sp_matrix_structure(A);
    // model.print_sp_matrix_structure(B);

	return 0;
}