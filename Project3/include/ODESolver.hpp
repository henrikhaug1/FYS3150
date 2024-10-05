#ifndef __ODESolver_hpp__
#define __ODESolver_hpp__


class ODESolver
{
	public:

		// Constructor
		ODESolver();

		// Function to set initial conditions
		void set_initail_conditions();

		// Function to solve the right-hand side function of the ODE
		void solve();

};

class ForwardEuler(ODESolver)
{
	public:

		// Constructor
		ForwardEuler();

		// Function to solve the right-hand side function of the ODE using ForwardEuler implementation
		void solve();

};

class RungeKutta4(ODESolver)
{
	public:

		// Constructor
		RungeKutta4();

		// Function to solve the right-hand side function of the ODE using RungeKutta4 implementation
		void solve();

};

#endif