#include <vector>
#include <cmath>
#ifndef Included_vector_H
#define Included_vector_H

namespace v{

    typedef std::vector<double> vector;
    double calculate_norm(const vector &v);

    vector sum(const vector &v1, const vector &v2);

    vector substract(const vector &v1, const vector &v2);

    vector scalar_mult(const vector &v1,double x);
}
#endif