#include "Method.hpp"
#include <vector>
#include <concepts>


class gradient:public Method{

    public:
    using Method::Method;
    typedef std::vector<double> vector;
    template<class T>
    vector solve(const vector &x0, const T &ak_ob);
    gradient& operator=(const gradient& other);
    //vector calculate_fin_d(const std::function<double(const vector)> &fun, const vector &x, const double &h);

};
