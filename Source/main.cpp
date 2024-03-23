#include "gradient.hpp"
#include <cmath>
#include <iostream>
#include "ExponentialDecay.hpp"
#include "Amijo.hpp"
#include "InverseDecay.hpp"



typedef std::vector<double> vector;

//definition of function to mimize

double fun(const vector &x)
{
    double x1{x[0]};
    double x2{x[1]};
    return (x1*x2)+4*pow(x1,4)+pow(x2,2)+3*x1;
}

// derivative of f
vector dfun(const std::function<double(const vector)> &fun,const vector &x, const double &h)
{
    double x1{x[0]};
    double x2{x[1]};
    double dx1=x2+16*pow(x1,3)+3;
    double dx2=x1+2*x2;
    return std::vector<double> {dx1,dx2};
}

// Calculation of gradient trough finite differences
vector fin_diff(const std::function<double(const vector)> &fun, const vector &x, const double &h){
    vector result(x.size(),0);

    for (std::size_t i=0; i<x.size();++i){
        vector temp1=x;
        vector temp2=x;

        temp1[i]=x[i]+h;
        temp2[i]=x[i]-h;

        result[i]=(fun(temp1)-fun(temp2))/(2*h);
    };

    return result;
};

// Definition of Main function
int main(int argc, char **argv)
{
  // Definition of Parameters 
  const unsigned int max_it = 1000;
  const double tol_r = 1e-6;
  const double tol_s = 1e-6;
  double a0=0.01;
  std::vector<double> x0{0,0};

  // Asking the user for the prefered methods
  // Selection method for gradient
  std::string met;
  std::cout<<"Indicate the desired method to calculate the gradient: \n (Default: Exact Gradient)"<<std::endl;
  std::cout<<"1. Finite differences Approximation \n2. Exact Gradient"<<std::endl;
  std::cin>>met;

  //Selection update rule

  std::string x;
  std::cout<<"Indicate the update rule for ak: \n (Default: ExponentialDecay)"<<std::endl;
  std::cout<<"1. Amijo Rule\n2. InverseDecay\n3. ExponentialDecay"<<std::endl;
  std::cin>>x;

  //Instance of class gradient depending of the selection made
  gradient problem{fun,dfun,tol_r, tol_s,a0,max_it};

  if (met=="1"){
      problem = gradient{fun, fin_diff,tol_r, tol_s,a0,max_it};
  };

  //Instance of class for definition of updating rule
  // Each updating rule has its own class

  vector sol;
  
  if (x=="1"){
    Amijo ak_ob = Amijo(fun,dfun,a0);
    sol=(problem.solve(x0, ak_ob)); // call solve method to find minimum
  }else if(x=="2"){
    InverseDecay ak_ob= InverseDecay(a0);
    sol=problem.solve(x0, ak_ob); // call solve method to find minimum
  }
  else{
    ExponentialDecay ak_ob(a0);
    sol=(problem.solve(x0, ak_ob)); // call solve method to find minimum
    }

  // Print result
  std::cout << "x =    " << std::endl;
  for(auto i:sol) {
      std::cout << i << std::endl;
  }
  return 0;
}
