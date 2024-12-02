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

arma::cx_vec PDEModel::initial_state(int M)
{
    int side_length = (M-2) * (M-2);    //Initializing a flat 2D matrix
    arma::cx_vec u(side_length);

    arma::cx_double i(0.0, 1.0);

    for (int j = 0; j < M-2; j++)       //Looping over the matrix
    {
        double x_val = 1.0 * j / (M-2);

        for(int k = 0; k < M-2; k++)    
        {
            double y_val = 1.0 * k / (M-2); 

            arma::cx_double exponent = - (x_val - x_c) * (x_val - x_c) / (2 * sigma_x * sigma_x)
                                       - (y_val - y_c) * (y_val - y_c) / (2 * sigma_y * sigma_y)
                                       + i * p_x * x_val + i * p_y * y_val; // We ignore optimizing the flops 
                                                                            // for readability as this part is not looped
            int l = pair_to_single_index(j, k, M-2);
            u(l) = std::exp(exponent); // Assign the complex exponential value
        }
    }
    return u;
}


arma::cx_vec PDEModel::normalised_initial_state(arma::cx_vec u)
{
    int M = u.size();

    arma::cx_vec u_normalised = u / arma::norm(u, 2); // Normalize by L2 norm

    for(int p = 0; p < M; p++)
    {
        p += 1; //std::cout << u_normalised[p] << std::endl;
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

void PDEModel::construct_potential(arma::mat& V, const double v_0, const double M, const int nr_slits, const double thickness, const double centre, const double middle_wall, const double opening)
{
    //Converting from positions to indexes
    int centre_id = (M - 2) * centre;
    int half_width_id = (M - 2) * thickness / 2;
    int middle_wall_id = (M - 2) * middle_wall;
    int half_opening_id = (M - 2) * opening / 2;
    V.cols(centre_id - half_width_id, centre_id + half_width_id).fill(v_0);  //Filling the wall

    if(nr_slits == 0){ //If there are no slits, the wall is complete
        return;
    }

    if(nr_slits % 2 == 0){//If there is an even amount of slits 
        int walls = nr_slits - 1; //Calculate the amount of walls

        for(int i = 0; i < walls; i++){//Leave the innermost wall, and remove the openings above and below accordingly. First upwards
            V.rows(centre_id + middle_wall_id / 2 + i * (2 * half_opening_id + middle_wall_id), centre_id + middle_wall_id / 2 + 2 * half_opening_id + i * (2 * half_opening_id + middle_wall_id)).fill(0);
        }//This is way easier to understand if you draw a sketch!

        for(int i = 0; i < walls; i++){//Then downwards
            V.rows(centre_id - middle_wall_id / 2 - 2 * half_opening_id - i * (2 * half_opening_id + middle_wall_id), centre_id - middle_wall_id / 2 - i * (2 * half_opening_id + middle_wall_id)).fill(0);
        }//This is way easier to understand if you draw a sketch!
    } 
     
    if(nr_slits % 2 == 1){//If there is an odd amount of slits 
        int slits = (nr_slits + 1) / 2; //Calculate the nr. of slits on each side (+ the middle one)
        for(int i = 0; i < slits; i++){//Remove openings accordingly. First upwards
            V.rows(centre_id - half_opening_id + i * (middle_wall_id + 2 * half_opening_id), centre_id + half_opening_id + i * (middle_wall_id + 2 * half_opening_id)).fill(0);
        }
        for(int i = 0; i < slits; i++){//Then downwards
            V.rows(centre_id - half_opening_id - i * (middle_wall_id + 2 * half_opening_id), centre_id + half_opening_id - i * (middle_wall_id + 2 * half_opening_id)).fill(0);
        }  
    } 
}

int PDEModel::pair_to_single_index(int i, int j, int matrix_side_length)
{
    return j * matrix_side_length + i;
}

std::tuple<arma::sp_cx_mat,arma::sp_cx_mat> PDEModel::construct_A_B(const int M, const double dx, const double dt, const arma::mat V)
{
    arma::cx_double r(0., dt / (2 * dx * dx));

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
    int k;
    arma::cx_double i_dt_2(0., dt / 2);
    for (int j = 0; j < (M-2); j++){
        for (int i = 0; i < (M-2); i++){
        k = pair_to_single_index(i, j, M-2);
        A(k,k) = 1. + 4.*r + i_dt_2 * V(j, i);   //a_k  Apparently the indexes need to be transposed to get the correct plot
        B(k,k) = 1. - 4.*r - i_dt_2 * V(j, i);   //b_k

        }
    }
    A.diag(1) = -r_diag_1; 
    A.diag(-1) = -r_diag_1;
    A.diag(M - 2) = -r_diag_2; 
    A.diag(- (M - 2)) = -r_diag_2;

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


arma::cx_vec PDEModel::crank_nicolson(const arma::sp_cx_mat A, const arma::sp_cx_mat B, arma::cx_vec u) //Solves u for one time step 
{
    arma::cx_vec u_1;             //The next time step
    arma::cx_vec b = B * u;       //First matrix multiplying the right side 
    u_1 = arma::spsolve(A, b);    //Then solving for the next time step using a sparse solver
    return u_1;
}


