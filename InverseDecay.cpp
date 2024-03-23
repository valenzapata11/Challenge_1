#include <vector>
#include "InverseDecay.hpp"

double InverseDecay::calculate_step(const std::vector<double> &x0,const int k) const{
    return a0/(1+(mu*k));

}