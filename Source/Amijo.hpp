#include "UpdateRule.hpp"
#include <functional>
#include "vector.hpp"


class Amijo: public UpdateRule{
   //class members
    const double sigma;
    const int max_iter;
    double h;
    typedef std::vector<double> vector;

    const std::function<double(const vector)> fun;
    std::function<vector(const std::function<double(const vector)> &fun, const vector &x, const double &h)> grf;
    public:
    using UpdateRule::UpdateRule; //Inheritance of constructor
    // class constructors
    //@todo the order of the variables in the initializer list should coincide with the order in the function declaration otherwise you 
    //have warnings. Don't you have seen the compiler warnings?
    Amijo(const std::function<double(const vector)> &fun_,
          const std::function<vector(const std::function<double(const vector)> &fun, const vector &x, const double &h)> &grf_,
          const double a0, double h) :UpdateRule(a0),
          fun(fun_), grf(grf_), sigma(0.3), max_iter(1000),h(h){};
//@todo If you want to give defaults  it is simpler initializing in class the member variables than use the constructor.
// For instance you could have defined  
// const int max_iter=1000;
// and simplify the constructor

//@todo If you create type aliases you make the code more readeable. For instance you could have defined
// using vector=std::vector<double>;
// and use vector instead of std::vector<double> in the code.

    Amijo(const std::function<double(const vector)> &fun_,
          const std::function<vector(const std::function<double(const vector)> &fun, const vector &x, const double &h)> &grf_,
          const double a0) :UpdateRule(a0),fun(fun_), grf(grf_), sigma(0.3), max_iter(1000) {h=0.01;};

    double calculate_step(const vector &xk,int iter) const override;

};
