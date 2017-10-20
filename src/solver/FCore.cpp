/*

    FCore.cpphpp
    Implementation file for FCore

*/

#include "FCore.hpp"
#include <math.h>

double FCore::h_func(qvector ql, qvector qr)
{
    return .5f * (ql.h + qr.h);
}

double FCore::u_func(qvector ql, qvector qr)
{
    double ul = ql.hu/ql.h;
    double ur = qr.hu/qr.h;
    return (ul*sqrt(ql.h)+ur*sqrt(qr.h))/(sqrt(ql.h)+sqrt(qr.h));
}

struct vector2 FCore::f_func(qvector q)
{
    struct vector2 result = {q.hu, q.hu * q.hu + .5f * G_CONST * q.h * q.h};
    return result;
}

struct fresult FCore::compute(qvector ql, qvector qr)
{
    struct fresult res = {0};

    res.lambda_1 = u_func(ql, qr) - sqrt(G_CONST * h_func(ql, qr));
    res.lambda_2 = u_func(ql, qr) + sqrt(G_CONST * h_func(ql, qr));
    
    struct vector2 r1 = {1, res.lambda_1};
    struct vector2 r2 = {1, res.lambda_2};
    
    struct vector2 fqr = f_func(qr);
    struct vector2 fql = f_func(ql);
    
    struct vector2 df = {fqr.x - fql.x, fqr.y - fql.y};

    return res;
}