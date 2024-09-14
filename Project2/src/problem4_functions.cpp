#include <iostream>
#include <armadillo>
#include <cmath>
#include "problem3_functions.hpp"

void jacobi_rotate(arma::mat& A, arma::mat& R, int k, int l){
	double eps = 10e-8;

	max_offdiag_symmetric(A, k, l); // ?????? we need to extract l and k somehow

	while(fabs(A[k, l] > eps){
		double tow = (A[k, k] - A[l, l]) / (2 * A[l, k]);
		double t;
		double c;
		double s;


		if(tow > 0){
			t = - tow + sqrt(1 + tow * tow);
		}
		if(tow < 0){
			t = - tow - sqrt(1 + tow * tow);
		}

		c = 1/(sqrt(1 + (t * t)));
		s = c * t;
	}
}