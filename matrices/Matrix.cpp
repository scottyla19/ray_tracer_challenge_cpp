#include "Matrix.h"
#include <iostream>
#include <cmath>
#include <stdexcept>
#include "../primitives/constants.h"

Matrix::Matrix( int row,  int col) {
        m_rows = row;
        m_cols = col;
        m_data.resize(row*col);
        for (int i = 0; i < row; i++){
            for (int j = 0; j < col; j++){
                if (i == j){
                    m_data[i *row + j] = 1.0;
                }
            }
        }
}

Matrix::Matrix(  int row,  int col, const std::vector<double>& data){
    m_rows = row;
    m_cols = col;
    m_data = data;
}

const double Matrix::operator()( int r,  int c) const{
    return m_data[r*m_rows+ c];
}
double& Matrix::operator()( int r,  int c) {
    return m_data[r*m_rows+ c];
}

bool operator==(const Matrix& a , const Matrix& b){
    for (int i = 0; i < a.m_data.size(); i++){
        if (!floatEqual(a.m_data[i] , b.m_data[i],ABS_EPSILON, 0.001)){
            return false;
        }
    }
    return true;
}

Tuple operator*(const Matrix& a, const Tuple& b){
    Tuple M = Tuple(0.0, 0.0, 0.0, 1.0);
    for (int i = 0; i < a.col_count(); i++){
//        for (int j = 0; j < b.m_cols; j++){
            M.set_index(i, a(i, 0) * b.x() + a(i, 1) * b.y() + a(i, 2) * b.z() + a(i, 3) * b.w()) ;
//        }
    }
    return M;
}

Matrix operator*(const Matrix& a , const Matrix& b){
    Matrix M = Matrix(4,4);
    for (int i = 0; i < a.m_rows; i++){
        for (int j = 0; j < b.m_cols; j++){
            M(i, j) = a(i, 0) * b(0, j) + a(i, 1) * b(1, j) + a(i, 2) * b(2, j) + a(i, 3) * b(3, j) ;
        }
    }
    return M;
}

std::ostream& operator<< (std::ostream& out, const Matrix& matrix){
    out << std::endl;
    for(int i = 0; i < matrix.m_cols;i++){
        for(int j = 0; j < matrix.m_rows; j++){
            out << matrix(i, j) << " ";
        }
        out << std::endl;
    }
}

Matrix Matrix::transpose()const{
    std::vector<double> T_data = m_data;
    for (int r = 0; r < m_rows; r++){
        for (int c = 0; c < m_cols; c++){
            T_data[r*m_rows+ c] = m_data[c*m_rows + r];
        }
    }
    Matrix T = Matrix(m_rows, m_cols, T_data);
    return T;
}

double Matrix::determinant()const{
    double det = 0.0;
    if (m_rows == 2 && m_cols == 2){
        det = m_data[0] * m_data[3] - m_data[1] * m_data[2];
    }else{
        for (int i = 0; i < m_cols; i++){
            det += m_data[i] * cofactor(0, i);
        }
    }
    return det;
}

Matrix Matrix::submatrix(int rm_row, int rm_col)const{
    std::vector<double> sub;
//    sub.resize((m_rows - 1)* ()m_cols - 1));
        for (int r = 0; r < m_rows; r++){
            for (int c = 0; c < m_cols; c++){
                if (!(r == rm_row || c == rm_col)){
                    sub.push_back(m_data[r*m_rows+ c]);
                }
            }
        }
    return Matrix(m_rows - 1 , m_cols - 1, sub);
}

double Matrix::minor(int r, int c){
    Matrix a = submatrix(r, c);
    return a.determinant();
}

double Matrix::cofactor(int r, int c)const{
    Matrix a = submatrix(r, c);
    double det = a.determinant();
    return (r + c) % 2 == 0 ? det : -det;
}

bool Matrix::is_invertible()const{
    return !floatEqual(determinant(), 0.0);
}

Matrix Matrix::inverse()const{
    if (!is_invertible()){
        throw std::runtime_error(std::string("Failed: Non-invertible matrix: "));
    }
    Matrix m = Matrix(m_rows, m_cols);
    for (int row = 0; row < m_rows; row++){
        for (int col = 0; col < m_cols; col++){
            double c = cofactor(row, col);
            m(col, row) = c / determinant();
        }
    }
    return m;
}


