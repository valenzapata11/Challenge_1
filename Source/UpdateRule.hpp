
#ifndef Included_UpdateRule_H
#define Included_UpdateRule_H
#include <vector>

class UpdateRule{
    protected:
    double a0;
    const double mu;
    public:
    UpdateRule(double a0, const double mu):a0(a0),mu(mu){}; 
    explicit UpdateRule(double a0):a0(a0),mu(0.01){};//Set constructors

    virtual double calculate_step(const std::vector<double> &xk, int k) const =0;

};
#endif
