#include "UpdateRule.hpp"

class InverseDecay: public UpdateRule{
    public:
    using UpdateRule::UpdateRule;
    double calculate_step(const std::vector<double> &xk, int k) const override;

};