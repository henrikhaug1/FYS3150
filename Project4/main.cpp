#include <iostream>
#include "IsingModel.hpp"

int main()
{
	IsingModel model = IsingModel();
	model.spins.print();
	return 0;
}