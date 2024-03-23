#include "Amijo.hpp"
#include <cmath>


double Amijo::calculate_step(const vector &xk, const int iter) const{
        //calculate norm squared
        double ak=a0;
        for (int i=0; i<max_iter;++i){
            vector s{v::scalar_mult(grf(fun,xk,h),a0)};
            double normsq(pow(v::calculate_norm(grf(fun,xk,h)),2));
            if(fun(xk)-fun(v::substract(xk,s))>=(sigma*a0*normsq)){
                break;
            }else{
                ak=ak/2;
            }
        }
        return ak;
}




