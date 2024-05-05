#include "Method.hpp"
#include <vector>
#include <concepts>


class gradient:public Method{

    public:
    // Inheritance of constructor from base class
    using Method::Method;
    typedef std::vector<double> vector;

    template<class T>
    vector solve(const vector &x0, const T &ak_ob);
    // redefinition of operator =, for copy assingment
    gradient& operator=(const gradient& other);
    
};
