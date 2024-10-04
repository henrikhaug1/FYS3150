#include <iostream>
#include <armadillo>
#include "Particle.hpp"
#include "PenningTrap.hpp"

arma::vec position1 = arma::vec({20, 0, 20});
arma::vec velocity1 = arma::vec({0, 40, 5});
Particle particle = Particle(charge_in=1.0, mass_in=40.078 position_in=position1, velocity_in=velocity1)