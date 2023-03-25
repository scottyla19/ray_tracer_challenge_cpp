#pragma once
#include <vector>
#include <ostream>
#include "../primitives/Tuple.h"

class Matrix{
private:
     int m_rows;
     int m_cols;

protected:
    std::vector<double> m_data;

public:
    // Constructors
    Matrix( int row,  int col);
    Matrix( int row,  int col, const  std::vector<double>& data);

    // accessors
    int row_count()const{return m_rows;}
    int col_count()const{return m_cols;}
    const std::vector<double>& get_data(){return m_data;}

    // operator overloads
    friend bool operator==(const Matrix& a , const Matrix& b);
    friend Matrix operator*(const Matrix& a , const Matrix& b);
    friend std::ostream& operator<< (std::ostream& out, const Matrix& matrix);

    const double operator()( int r,  int c)  const;
    double& operator()( int r,  int c)  ;

    // member methods
    Matrix transpose();
    double determinant();
    Matrix submatrix(int rm_row, int rm_col);
    double minor(int r, int c);
    double cofactor(int r, int c);
    bool is_invertible();
    Matrix inverse();

    ~Matrix() = default;
};

Tuple operator*(const Matrix& a, const Tuple& b);
