
#include <vector>
#include <cmath>
#include "vector.hpp"


namespace v{

    typedef std::vector<double> vector;
    double calculate_norm(const vector &v) {
        double sumsqr(0);
        for (double i: v){
            sumsqr+=pow(i,2);
        }
        return sqrt(sumsqr);
    }

    vector sum(const vector &v1, const vector &v2){
        int s(std::max(v1.size(),v2.size()));
        vector v3(s,0);
        for (std::size_t i=0; i<s;++i){
            if (v1.size()<=i){
                v3[i]=v2[i];
            }else if(v2.size()<=i){
                v3[i]=v1[i];
            }else{
                v3[i]=v1[i]+v2[i];
            }

        }
        return v3;
    }

    vector substract(const vector &v1, const vector &v2){
        vector tempv(v2.size(),0);
        for (std::size_t i=0; i<v2.size();++i){
            tempv[i]=-v2[i];
        }
        return sum(v1,tempv);
    }

    vector scalar_mult(const vector &v1,const double x){
        vector v(v1.size(),0);
        for (std::size_t i=0; i<v1.size();++i){
            v[i]=(v1[i]*x);
        }
        return v;
    }

}
