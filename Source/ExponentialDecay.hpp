#include "UpdateRule.hpp"

class ExponentialDecay: public UpdateRule{
    public:
    using UpdateRule::UpdateRule;
    double calculate_step(const std::vector<double> &xk, int k) const override;

};