#include "UpdateRule.hpp"
#include <functional>
#include "vector.hpp"


class Amijo: public UpdateRule{
    const double sigma;
    const int max_iter;
    double h;
    typedef std::vector<double> vector;

    const std::function<double(const vector)> fun;
    std::function<vector(const std::function<double(const vector)> &fun, const vector &x, const double &h)> grf;
    public:
    using UpdateRule::UpdateRule; //Inheritance of constructor
    Amijo(const std::function<double(const vector)> &fun_,
          const std::function<vector(const std::function<double(const vector)> &fun, const vector &x, const double &h)> &grf_,
          const double a0, double h) :UpdateRule(a0),
          fun(fun_), grf(grf_), sigma(0.3), max_iter(1000),h(h){};

    Amijo(const std::function<double(const vector)> &fun_,
          const std::function<vector(const std::function<double(const vector)> &fun, const vector &x, const double &h)> &grf_,
          const double a0) :UpdateRule(a0),fun(fun_), grf(grf_), sigma(0.3), max_iter(1000) {h=0.01;};

    double calculate_step(const vector &xk,int iter) const override;

};
