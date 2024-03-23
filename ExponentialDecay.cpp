#include <valarray>
#include <vector>
#include "ExponentialDecay.hpp"


double ExponentialDecay::calculate_step(const std::vector<double> &xk, const int k) const{
    return a0 * std::exp(-mu*k);
}

