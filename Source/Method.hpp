#include <functional>
#include <vector>
#include <concepts>


class Method{

    typedef std::vector<double> vector;

protected:

    std::function<double(const vector)> fun;
    std::function<vector(const std::function<double(const vector)> &fun, const vector &x, const double &h)> grf;
    double epsilon_r;
    double epsilon_s;
    double a0;
    int max_iter;
    double h;


public:
    
    Method(const std::function<double(const vector)> &fun_,
            const std::function<vector(const std::function<double(const vector)> &fun, const vector &x, const double &h)> &grf_,
            const double epsilon_r,
            const double epsilon_s,
            double a0, 
            const int max_iter):
            fun(fun_),grf(grf_),epsilon_r(epsilon_r),
            epsilon_s(epsilon_s),a0(a0), max_iter(max_iter), h(0.1){};

    void set_h(double &h_i){h=h_i;}



};
