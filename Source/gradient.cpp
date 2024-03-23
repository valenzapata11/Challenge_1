#include <valarray>
#include "gradient.hpp"
#include "InverseDecay.hpp"
#include "Amijo.hpp"
#include "vector.hpp"
#include "ExponentialDecay.hpp"
#include <iostream>
#include <concepts>


typedef std::vector<double> vector;
template<class T>
vector gradient::solve(const vector &x, const T &ak_ob){
    vector x0=x;
    int i=0;
    for(int iter=0; iter< max_iter;++iter)
    {
        double ak{ak_ob.calculate_step(x0,iter)};

        vector mult{v::scalar_mult(grf(fun,x0,h),ak)};
        vector x1(v::substract(x0, mult));

        double norm(v::calculate_norm(v::substract(x1,x0)));
        if(norm<epsilon_s){break;}
        double error{std::abs(fun(x1)-fun(x0))};
        if(error<epsilon_r){break;}
        i++;
        x0=x1;

    }
    std::cout<<i<<std::endl;
    return x0;
};

gradient &gradient::operator=(const gradient& other) {
    fun = other.fun;
    grf=other.grf;
    epsilon_r=other.epsilon_r;
    epsilon_s=other.epsilon_s;
    a0=other.a0;
    max_iter=other.max_iter;
    h= other.h;

    return *this;
}

template vector gradient::solve(const vector &x, const Amijo &ak_ob);
template vector gradient::solve(const vector &x, const InverseDecay &ak_ob);
template vector gradient::solve(const vector &x, const ExponentialDecay &ak_ob);


