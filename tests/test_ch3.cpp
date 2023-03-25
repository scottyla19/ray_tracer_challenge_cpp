#include "doctest.h"
#include <iostream>
#include <typeinfo>
#include <cmath>

#include "../primitives/Matrix.h"
#include "../primitives/constants.h"

TEST_CASE("Constructing a matrix"){
    std::vector<double> data {1.0, 2.0, 3.0, 4.0, 5.5, 6.5, 7.5, 8.5, 9.0, 10.0 , 11.0, 12.0, 13.5,14.5,15.5,16.5};
    Matrix m = Matrix(4,4, data);
    CHECK(floatEqual(m(0,0), 1.0));
    CHECK(floatEqual(m(0,3), 4.0));
    CHECK(floatEqual(m(1,0), 5.5));
    CHECK(floatEqual(m(1,2), 7.5));
    CHECK(floatEqual(m(2,2), 11.0));
    CHECK(floatEqual(m(3,0), 13.5));
    CHECK(floatEqual(m(3,2), 15.5));
}

TEST_CASE("Constructing a 2x2 matrix"){
    std::vector<double> data {-3.0, 5.0, 1.0, -2.0};
    Matrix m = Matrix(2,2, data);
    CHECK(floatEqual(m(0,0), -3.0));
    CHECK(floatEqual(m(0,1), 5.0));
    CHECK(floatEqual(m(1,0), 1.0));
    CHECK(floatEqual(m(1,1), -2.0));
}

TEST_CASE("Constructing a 3x3 matrix"){
    std::vector<double> data {-3.0, 5.0,0.0, 1.0, -2.0, -7.0, 0.0,1.0,1.0};
    Matrix m = Matrix(3,3, data);
    CHECK(floatEqual(m(0,0), -3.0));
    CHECK(floatEqual(m(1,1), -2.0));
    CHECK(floatEqual(m(1,0), 1.0));
    CHECK(floatEqual(m(1,1), -2.0));
    CHECK(floatEqual(m(2,2), 1.0));
}

TEST_CASE("Matrix equality"){
    std::vector<double> data {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 8.0 , 7.0, 6.0, 5.0, 4.0, 3.0, 2.0};
    Matrix a = Matrix(4,4, data);
    Matrix b = Matrix(4,4, data);
    CHECK(a == b);
}

TEST_CASE("Matrix inequality"){
    std::vector<double> data {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 8.0 , 7.0, 6.0, 5.0, 4.0, 3.0, 2.0};
    Matrix a = Matrix(4,4, data);
    std::vector<double> data2 {1.0, 2.0, 3.0, 4.0, 5.5, 6.5, 7.5, 8.5, 9.0, 10.0 , 11.0, 12.0, 13.5,14.5,15.5,16.5};
    Matrix b = Matrix(4,4, data2);
    CHECK(!(a == b));
}

TEST_CASE("Matrix multiplication"){
    std::vector<double> data {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 8.0 , 7.0, 6.0, 5.0, 4.0, 3.0, 2.0};
    Matrix a = Matrix(4,4, data);

    std::vector<double> data2 {-2.0, 1.0, 2.0, 3.0, 3.0, 2.0, 1.0, -1.0, 4.0, 3.0 , 6.0, 5.0, 1.0, 2.0, 7.0, 8.0};
    Matrix b = Matrix(4,4, data2);

    std::vector<double> data3 {20.0, 22.0, 50.0, 48.0, 44.0, 54.0, 114.0, 108.0, 40.0, 58.0 , 110.0, 102.0, 16.0, 26.0, 46.0, 42.0};
    Matrix c = Matrix(4,4, data3);
    CHECK(a * b == c);
}

TEST_CASE("Mutliply matrix by tuple"){
    std::vector<double> data {1.0, 2.0, 3.0, 4.0, 2.0, 4.0, 4.0, 2.0, 8.0, 6.0 , 4.0, 1.0, 0.0, 0.0, 0.0, 1.0};
    Matrix a = Matrix(4,4, data);
    Tuple b = Tuple(1.0, 2.0, 3.0, 1.0);
    Matrix id = Matrix(4, 4);
    CHECK(a * b == Tuple(18.0, 24.0, 33.0, 1.0));
}

TEST_CASE("identity matrix multiplication"){
    std::vector<double> data {0.0, 1.0, 2.0, 4.0, 1.0, 2.0, 4.0, 8.0, 2.0, 3.0 , 8.0, 16.0, 4.0, 8.0, 16.0, 32.0};
    Matrix a = Matrix(4,4, data);
    Matrix id = Matrix(4, 4);
    CHECK(a * id == a);
}

TEST_CASE("identity matrix tuple multiplication"){
    Tuple b = Tuple(1.0, 2.0, 3.0, 1.0);
    Matrix id = Matrix(4, 4);
    CHECK( id * b == b);
}

TEST_CASE("transpose matrix"){
    std::vector<double> data {0.0, 9.0, 3.0, 0.0, 9.0, 8.0, 0.0, 8.0, 1.0, 8.0 , 5.0, 3.0, 0.0, 0.0, 5.0, 8.0};
    Matrix a = Matrix(4,4, data);
    std::vector<double> data2 {0.0, 9.0, 1.0, 0.0, 9.0, 8.0, 8.0, 0.0, 3.0, 0.0 , 5.0, 5.0, 0.0, 8.0, 3.0, 8.0};
    Matrix exp = Matrix(4, 4, data2);
    CHECK(a.transpose() == exp);
}

TEST_CASE("calculating determinant of 2x2"){
    std::vector<double> data { 1.0, 5.0, -3.0, 2.0};
    Matrix a  = Matrix(2,2,data );
    CHECK(a.determinant() == 17.0);
}

TEST_CASE("Submatrix 3x3"){
    std::vector<double> data {1.0, 5.0, 0.0,
                             -3.0, 2.0, 7.0,
                              0.0, 6.0, -3.0};
    Matrix a = Matrix(3, 3, data);
    std::vector<double> data2 { -3.0, 2.0,
                                0.0, 6.0};
    Matrix exp  = Matrix(2,2,data2 );
    CHECK(a.submatrix(0,2) == exp);
}

TEST_CASE("Submatrix 4x4"){
    std::vector<double> data {-6.0, 1.0, 1.0, 6.0,
                             -8.0, 5.0, 8.0, 6.0,
                              -1.0, 0.0, 8.0, 2.0,
                              -7.0, 1.0, -1.0, 1.0};
    Matrix a = Matrix(4, 4, data);
    std::vector<double> data2 { -6.0, 1.0, 6.0,
                                -8.0, 8.0, 6.0,
                                -7.0, -1.0, 1.0};
    Matrix exp  = Matrix(3,3,data2 );
    CHECK(a.submatrix(2,1) == exp);
}

TEST_CASE("calculating minor of 3x3"){
    std::vector<double> data {3.0, 5.0, 0.0,
                             2.0, -1.0, -7.0,
                              6.0, -1.0, 5.0};
    Matrix a = Matrix(3, 3, data);
    Matrix b = a.submatrix(1,0);
    CHECK(b.determinant() == 25.0);
    CHECK(a.minor(1,0) == 25);
}

TEST_CASE("calculating cofactor of 3x3"){
    std::vector<double> data {3.0, 5.0, 0.0,
                             2.0, -1.0, -7.0,
                              6.0, -1.0, 5.0};
    Matrix a = Matrix(3, 3, data);

    CHECK(a.minor(0,0) == -12);
    CHECK(a.minor(1,0) == 25);
    CHECK(a.cofactor(0,0) == -12);
    CHECK(a.cofactor(1,0) == -25);

}


TEST_CASE("calculating determinant of 3x3"){
    std::vector<double> data {1.0, 2.0, 6.0,
                              -5.0, 8.0, -4.0,
                              2.0, 6.0, 4.0};
    Matrix a = Matrix(3, 3, data);

    CHECK(a.cofactor(0,0) == 56);
    CHECK(a.cofactor(0,1) == 12);
    CHECK(a.cofactor(0,2) == -46);
    CHECK(a.determinant() == -196);
}

TEST_CASE("calculating determinant of 4x4"){
    std::vector<double> data {-2.0, -8.0, 3.0, 5.0,
                              -3.0, 1.0, 7.0, 3.0,
                              1.0, 2.0, -9.0, 6.0,
                              -6.0, 7.0, 7.0, -9.0};
    Matrix a = Matrix(4, 4, data);

    CHECK(a.cofactor(0,0) == 690);
    CHECK(a.cofactor(0,1) == 447);
    CHECK(a.cofactor(0,2) == 210);
    CHECK(a.cofactor(0,3) == 51);
    CHECK(a.determinant() == -4071);
}

TEST_CASE("Invertible matrix invertibiility"){
    std::vector<double> data {6.0, 4.0, 4.0, 4.0,
                              5.0, 5.0, 7.0, 6.0,
                              4.0, -9.0, 3.0, -7.0,
                              9.0, 1.0, 7.0, -6.0};
    Matrix a = Matrix(4, 4, data);
    CHECK(a.determinant() == -2120);
    CHECK(a.is_invertible());
}

TEST_CASE("Non-Invertible matrix invertibiility"){
    std::vector<double> data {-4.0, 2.0, -2.0, -3.0,
                              9.0, 6.0, 2.0, 6.0,
                              0.0, -5.0, 1.0, -5.0,
                              0.0, 0.0, 0.0, 0.0};
    Matrix a = Matrix(4, 4, data);
    CHECK(a.determinant() == 0);
    CHECK(!a.is_invertible());
}

TEST_CASE("Calculating the inverse of a matrix"){
    std::vector<double> data {-5.0, 2.0, 6.0, -8.0,
                              1.0, -5.0, 1.0, 8.0,
                              7.0, 7.0, -6.0, -7.0,
                              1.0, -3.0, 7.0, 4.0};
    Matrix a = Matrix(4, 4, data);
    Matrix b = a.inverse();
    CHECK(a.determinant() == 532);
    CHECK(a.cofactor(2,3) == -160);
    CHECK(b(3,2) == -160.0 / 532);
    CHECK(a.cofactor(3,2) == 105);
    CHECK(b(2,3) == 105.0 / 532);

    std::vector<double> data2 {
        0.21805 ,  0.45113  , 0.24060 , -0.04511 ,
       -0.80827 , -1.45677 , -0.44361 ,  0.52068 ,
       -0.07895 , -0.22368 , -0.05263 ,  0.19737 ,
       -0.52256 , -0.81391 , -0.30075 ,  0.30639 };
    Matrix exp = Matrix(4, 4, data2);
    CHECK(b == exp);
}

TEST_CASE("Calculating the inverse of another matrix"){
    std::vector<double> data {8.0, -5.0, 9.0, 2.0,
                              7.0, 5.0, 6.0, 1.0,
                              -6.0, 0.0, 9.0, 6.0,
                              -3.0, 0.0, -9.0, -4.0};
    Matrix a = Matrix(4, 4, data);
    Matrix b = a.inverse();

    std::vector<double> data2 {
        -0.15385 , -0.15385 , -0.28205 , -0.53846 ,
        -0.07692 ,  0.12308 ,  0.02564 ,  0.03077 ,
        0.35897 ,  0.35897 ,  0.43590 ,  0.92308 ,
        -0.69231 , -0.69231 , -0.76923 , -1.92308 };
    Matrix exp = Matrix(4, 4, data2);
    CHECK(b == exp);
}

TEST_CASE("Calculating the inverse of a third matrix"){
    std::vector<double> data {9.0, 3.0, 0.0, 9.0,
                              -5.0, -2.0, -6.0, -3.0,
                              -4.0, 9.0, 6.0, 4.0,
                              -7.0, 6.0, 6.0, 2.0};
    Matrix a = Matrix(4, 4, data);
    Matrix b = a.inverse();

    std::vector<double> data2 {
        -0.04074 , -0.07777 ,  0.14444 , -0.22222 ,
        -0.07778 ,  0.03333 ,  0.36667 , -0.33333 ,
        -0.02901 , -0.14630 , -0.10926 ,  0.12963 ,
        0.17778 ,  0.06667 , -0.26667 ,  0.33333  };
    Matrix exp = Matrix(4, 4, data2);
    CHECK(b == exp);
}

TEST_CASE("Multiply product by its inverse"){
    std::vector<double> data {3.0, -9.0, 7.0, 3.0,
                              3.0, -8.0, 2.0, -9.0,
                              -4.0, 4.0, 4.0, 1.0,
                              -6.0, 5.0, -1.0, 1.0};
    Matrix a = Matrix(4, 4, data);
    std::vector<double> data2 {8.0, 2.0, 2.0, 2.0,
                               3.0, -1.0, 7.0, 0.0,
                               7.0, 0.0, 5.0, 4.0,
                               6.0, -2.0, 0.0, 5.0};
    Matrix b = Matrix(4, 4, data);
    Matrix c = a *b;
    CHECK(c * b.inverse() == a);
}
