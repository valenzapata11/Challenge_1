#include <iostream>
#include "matrix.hpp"
#include <chrono>
using namespace std::chrono;

int main() {

    //Main file for testing namespace Matrix

    //Creation of matrix and adding values

    //Matrix A is stored Column Wise (1)
    algebra::Matrix<double,1> A(4,4,0);
    //Matrix B is stored Row Wise (1)
    algebra::Matrix<double,0> B(4,4,0);

    //Fill matrices A B with operator()
    unsigned int n=4;
    for (unsigned int i = 0; i < n; ++i)
    {
        if (i > 0){A(i,i - 1)=-1;B(i,i - 1)=-1;}
        if (i < n - 1){A(i,i + 1) = -1;B(i,i + 1) = -1;}
        if(i!=1){A(i,i) = 4;B(i,i) = 4;}
    }
    A(0,3)=1;
    B(0,3)=1;

    //Matrix C is created empty for later reading from file
    algebra::Matrix<double,0> C; //row wise storage
    std::string filename("lnsp_131.mtx");
    //Fill matrix with info for file
    C.read(filename);
    algebra::Matrix<double,1> D; //column wise storage
    //Fill matrix with info for file
    D.read(filename);

    //Test Compression

    A.compress();

    B.compress();

    C.compress();

    D.compress();

    //Printing of compressed vectors
    std::cout <<"Matrix A Compressed"<<std::endl;
    std::cout << A <<std::endl << std::endl;
    std::cout <<"Matrix B Compressed"<<std::endl;
    std::cout << B <<std::endl << std::endl;
    //std::cout <<"Matrix C Compressed"<<std::endl;
    //std::cout << C <<std::endl << std::endl;

    //Test const () operator
    A(3,3)=6; //Value replacement
    B(3,3)=6; //Value replacement
    //A(3,0)=3; //Error because values cannot be added


    std::cout <<"Matrix A Compressed"<<std::endl;
    std::cout << A <<std::endl << std::endl;
    std::cout <<"Matrix B Compressed"<<std::endl;
    std::cout << B <<std::endl << std::endl;

    //Matrix Vector Multiplication in compressed state:
    //Create vectors to multiply
    std::vector<double> x_C(C.size(),1);
    std::vector<double> x_D(D.size(),1);



    //Start timing to test efficiency
    auto start= high_resolution_clock::now();
    //Multiplication in compressed state
    std::vector<double> e= C * x_C;
    auto stop = high_resolution_clock::now();
    auto t1 = duration_cast<nanoseconds>(stop - start).count();

    //Start timing to test efficiency
    start= high_resolution_clock::now();
    //Multiplication in compressed state
    std::vector<double> d= D * x_D;
    stop = high_resolution_clock::now();
    auto t2 = duration_cast<nanoseconds>(stop - start).count();



    //Test Uncompression
    A.uncompress();
    B.uncompress();
    C.uncompress();
    D.uncompress();


    //Vector Matrix Multiplication in Uncompressed State

    //Multiplication in uncompressed state
    start= high_resolution_clock::now();
    e= C * x_C;
    stop = high_resolution_clock::now();
    //print_vector(e);
    auto t3 = duration_cast<nanoseconds>(stop - start).count();

    start= high_resolution_clock::now();
    d= D * x_D;
    stop = high_resolution_clock::now();
    //print_vector(d);
    auto t4 = duration_cast<nanoseconds>(stop - start).count();


    std::cout<<"Efficiency Comparison in ns: "<<std::endl;
    std::cout<<"               R. Sto      C. Sto "<<std::endl;
    std::cout<<"Compressed     "<<t1<<"        "<<t2<<std::endl;
    std::cout<<"Uncompressed  "<<t3<<"        "<<t4<<std::endl;



}

