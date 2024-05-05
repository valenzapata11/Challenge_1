//
// Created by valen on 02-May-24.
//

#ifndef CHALLENGE_2_MATRIX_H
#define CHALLENGE_2_MATRIX_H

#endif //CHALLENGE_2_MATRIX_H

#include <vector>
#include <map>
#include <array>
#include <string>
#include <iostream>
#include <cassert>
#include <fstream>


namespace algebra
{   //Comparator for the map depending of storage order
    struct Comp{
        explicit Comp(bool row): row(row){};
        Comp(): row(true){};

        bool operator()(std::array<std::size_t,2> lhs, std::array<std::size_t,2> rhs) const
        {
            if(row){
                //if storage order is row, the vector of keys will be read lexicographically
                return std::lexicographical_compare(lhs.cbegin(), lhs.cend(), rhs.cbegin(),rhs.cend());
            }else{
                //if storage order is column, the vector of keys will be read lexicographically but in reverse order
                return std::lexicographical_compare(lhs.rbegin(), lhs.rend(), rhs.rbegin(),rhs.rend());
            }

        }
    private:
        bool row;
    };

    template <class T, int So>
    class Matrix final {

    public:
        using sparse_t = std::map<std::array<std::size_t,2>,T,Comp> ;
        using k_arr = std::array<std::size_t,2>;
        using comp_v= std::vector<T>;


        //Constructor
        Matrix(size_t r, size_t c, int resize_m):
        n_rows(r), n_cols(c),nz(r*c), compressed(false), s_order(So){
             //Depending of the storage order the map will be initialized differently
          if (s_order==1){
              sparse_t n(Comp(false));
              map=n;
              inner.reserve(n_cols);
              outer.reserve(n_rows);
          }else{
              sparse_t n(Comp(true));
              map=n;
              inner.reserve(n_rows);
              outer.reserve(n_cols);
          }

        }
        // Default constructor for matrix that later will be filled with info of a file
        Matrix():
                n_rows(0), n_cols(0),nz(0), compressed(false), s_order(So){
            if (s_order==1){
                sparse_t n(Comp(false));
                map=n;
            }else{
                sparse_t n(Comp(true));
                map=n;
            }

        }

        //Methods

        //Matrix compression
        void compress(){
            compressed=true;
            //Extraction of number of rows or columns
            size_t first_rc=map.cbegin()->first[s_order];
            size_t last_rc=std::prev(map.cend(),1)->first[s_order];

            inner.push_back(0);
            //Loop through each row or column
            for(size_t i=first_rc; i<=last_rc;i++){
                k_arr l,u;
                l[s_order]=i;
                l[abs(s_order-1)]=0;
                u[s_order]=i+1;
                u[abs(s_order-1)]=0;
                //l{i,0}, u{i+1,0};
                //row/column extraction with upper and lower bound
                auto up_bound=map.lower_bound(u);
                auto l_bound=map.lower_bound(l);

                //update inner vector
                size_t num=std::distance(l_bound,up_bound);
                inner.push_back(inner.back()+num);

                //addition of values and column/row indexes for each element of the row/column
                for(auto j=l_bound;j!=up_bound;j++){
                    outer.push_back(j->first[abs(s_order-1)]);
                    values.push_back(j->second);
                }
            }
            //deletion of information
            map.clear();

        }


        comp_v get_values(){return values;};

        std::vector<size_t> get_inner(){return inner;};

        std::vector<size_t> get_outer(){return outer;};


        //matrix conversion to sparse matrix
        void uncompress(){
            size_t i_n{inner[0]};
            //Transverse the inner vector to construct the map
            for (auto i = inner.begin();i !=inner.cend()-1;i++){
                for (auto j=*i;j<(*std::next(i));j++){
                    k_arr a;
                    a[s_order]=i_n;
                    a[abs(s_order-1)]=outer[j];
                    map[a]=values[j];
                }
                i_n++;
            }
            inner.clear();
            outer.clear();
            values.clear();
            compressed=false;

        };

        //Verification if it is compressed
        bool is_compressed(){
            return compressed;
        };

        T &
        operator()(size_t i,size_t j) {
            //if compressed change value
            if (compressed) {
                //if the storage order is column wise, i and j are switched to access the correct inner vector
                if(s_order!=0){
                    std::swap(i, j);
                }

                T* ptr= nullptr;

                size_t start = inner[i];
                size_t finish = inner[i + 1];
                for (size_t j_l=start;j_l<finish; j_l++){
                    if(outer[j_l]==j){
                        ptr= &values[j_l];
                    }
                }
                //if the pair of subscripts wasn't found give error
                if ((ptr== nullptr)){
                    throw std::runtime_error("Values cannot be added to compressed matrices");
                }
                return *ptr;
            }
            else
            {
                //if uncompressed only add
                k_arr a{i,j};
                return map[a];
            }

        }

        T
        operator()(size_t i, size_t j) const
        {
            //if not value return 0

            if (compressed) {

                //if the storage order is column wise, i and j are switched to access the correct inner vector
                if(s_order!=0){
                    std::swap(i, j);
                }

                size_t start = inner[i];
                size_t finish = inner[i + 1];

                for (size_t j_l = start; j_l <= finish; j_l++) {
                    if (outer[j_l] == j) {
                        return values[j_l];
                    }
                }
                return static_cast<T &> (0);


            } else {
                k_arr k{i, j};
                if (map.find(k) == map.end()) {
                    return static_cast<T &> (0);
                } else {
                    return map[k];
                }

            }
        }

        //Matrix Size
        size_t size(){
            if (compressed){
                return inner.size();
            }else{
                size_t last_rc=std::prev(map.cend(),1)->first[s_order];
                return last_rc;
            }

        }

        //Stream Operator
        //template <class U>
        friend std::ostream &
        operator<<(std::ostream &stream, Matrix<T,So> &M){
            if (M.compressed){
                std::vector<T> val = M.values;
                std::vector<size_t> col_ind=M.outer;
                std::vector<size_t> row_ptr=M.inner;

                stream << "Compressed Matrix Vectors = " << std::endl;

                stream << "Values: [" ;
                for (auto i : val)
                    stream << i << " ";
                stream << "] " ;
                stream<< std::endl;

                stream << "Outer: [ " ;
                for (auto i : col_ind)
                    stream << i << " ";
                stream << "] " ;
                stream << std::endl;

                stream << "Inner: [ " ;
                for (auto i : row_ptr)
                    stream << i << " ";
                stream << "] " ;
                stream << std::endl << std::endl;

            }else{
                stream << "Matrix = {";
                for (const auto &[j, val]: M.map) {
                    stream << "[" << j[0] << "," << j[1] << "] = " << val << std::endl;
                }
                stream << "};" << std::endl;
            }

            return stream;
        };


        //Matrix vector product
        friend std::vector<T>
        operator*(Matrix<T,So> &M, const std::vector<T> &x){
            std::vector<T> result(x.size(), 0);
            if (M.compressed){
                if(M.s_order==0){
                    size_t row(0);
                    //for each row
                    for (auto i = M.inner.begin();i !=M.inner.cend()-1;i++){
                        //for each column value
                        T s_p(0);
                        for (auto j=*i;j<(*std::next(i));j++){
                            s_p+=x[M.outer[j]]*M.values[j];
                        }
                        result[row]=s_p;
                        row++;
                    }
                }else{
                    //column order
                    size_t column(0);
                    //for each column
                    for (auto i = M.inner.begin();i !=M.inner.cend()-1;i++){
                        //for each row value
                        for (auto j=*i;j<(*std::next(i));j++){
                            result[M.outer[j]]+=x[column]*M.values[j];
                        }
                        column++;
                    }

                }
            } else
            {
                size_t first_rc=M.map.cbegin()->first[M.s_order];
                size_t last_rc=std::prev(M.map.cend(),1)->first[M.s_order];
                //for each row
                size_t column(0);

                for(size_t i=first_rc; i<=last_rc;i++) {
                    k_arr l, u;
                    l[M.s_order]=i;
                    l[abs(M.s_order-1)]=0;
                    u[M.s_order]=i+1;
                    u[abs(M.s_order-1)]=0;
                    //column row extraction with upper and lower bound
                    auto up_bound = M.map.lower_bound(u);
                    auto l_bound = M.map.lower_bound(l);

                    if (M.s_order==0){
                        //initialization of sum
                        T s_p(0);
                        //addition of values and column indexes for each element of the row
                        for (auto j = l_bound; j != up_bound; j++) {
                            size_t column_idx =j->first[1];
                            s_p += (j->second) * x[column_idx];
                        }
                        result[i]=s_p;
                    }

                    else{
                        //column order
                        for (auto j = l_bound; j != up_bound; j++) {
                            size_t column_idx(j->first[0]);
                            result[column_idx]+=x[column]*(j->second);
                        }
                        column++;
                    }


                }

            }
            return result;
        };

        friend Matrix<T,So>
        operator*(Matrix<T,So> &M, const Matrix<T,So> &x){
            //Matrix Matrix mult only for single vector matrices
            if (x.is_compressed()){
                std::vector<T> x1(x.values);
                return M*x1;
            }else{
                M.compress();
                std::vector<T> x1(x.values);
                M.uncompress();
                return M*x1;

            }


        };



        //Read a matrix
        void read (const std::string &filename){

            std::ifstream file(filename);

            if(!file) {
                std::cout << "Cannot open file.\n";}

            //Ignore comment headers
            while (file.peek() == '%'){file.ignore(2048, '\n');}

            //state parameters
            size_t r, c, val;
            file>> r >> c >> val;
            n_rows=r;
            n_cols=c;
            nz=val;

            //reserve memory for compressed vectors
            if(s_order==0){
                inner.reserve(n_rows);
                outer.reserve(n_cols);
            }else{
                inner.reserve(n_cols);
                outer.reserve(n_rows);
            }
            values.reserve(nz);
            //read line by line
            for(size_t l=0;l<nz;l++){
                size_t row, col;
                double v;
                file >> row>> col >>v;
                //fill the matrix
                (*this)(row-1,col-1)=v;
            }

            file.close();

            std::cout<<"Matrix loaded successfully"<< std::endl;

        };


    private:
        size_t n_rows, n_cols,nz;
        bool compressed;
        sparse_t map;
        comp_v values;
        int s_order;
        std::vector<size_t> outer;
        std::vector<size_t> inner;


    };


}
template <class T>
void print_vector(std::vector<T> x){
    std::cout<<"Result Matrix * v: [";
    for(auto &item:x) {
        std::cout << item<< " ";
    }
    std::cout<<"]"<<std::endl;
}
