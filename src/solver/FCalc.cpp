/**
 * @file FCalc.cpp
 * @brief Implementation of FCalc.hpp
*/

#include <assert.h>
#include <cmath>
#include "FCalc.hpp"

double FCalc::h_func(qvector ql, qvector qr)
{
    return 0.5 * (ql.h + qr.h);
}

double FCalc::u_func(qvector ql, qvector qr)
{
    assert(ql.h > ZERO_PRECISION && qr.h > ZERO_PRECISION); //Assert h values of ql and qr are positive

    double ul = ql.hu / ql.h;
    double ur = qr.hu / qr.h;
    return (ul * sqrt(ql.h) + ur * sqrt(qr.h)) / (sqrt(ql.h) + sqrt(qr.h));
}

struct vector2 FCalc::f_func(qvector q)
{
    struct vector2 result = {
        q.hu, 
        q.hu * q.hu + 0.5 * G_CONST * q.h * q.h
    };
    return result;
}