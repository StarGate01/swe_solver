/*

    FCore.cpphpp
    Implementation file for FCore

*/

#include "FCore.hpp"
#include <math.h>

double FCore::h_func(qvector ql, qvector qr)
{
    return .5 * (ql.h + qr.h);
}

double FCore::u_func(qvector ql, qvector qr)
{
    double ul = ql.hu/ql.h;
    double ur = qr.hu/qr.h;
    return (ul*sqrt(ql.h)+ur*sqrt(qr.h))/(sqrt(ql.h)+sqrt(qr.h));
}

struct vector2 FCore::f_func(qvector q)
{
    struct vector2 result = {q.hu, q.hu * q.hu + .5 * G_CONST * q.h * q.h};
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

    struct vector2 alpha = {(df.x*res.lambda_2 - df.y)/(res.lambda_2 - res.lambda_1), (df.x*res.lambda_1 + df.y)/(res.lambda_2 - res.lambda_1)};

    if(res.lambda_1 < 0)
        res.adq_negative += alpha.x * r1
    else if(res.lambda_1 > 0)
        res.adq_positive += alpha.x * r1
    
    if(res.lambda_2 < 0)
        res.adq_negative += alpha.x * r2
    else if(res.lambda_2 > 0)
        res.adq_positive += alpha.x * r2

    if(res.lambda_1 < 0 && res.lambda_2)
        res.lambda_2 = 0;
    else if(res.lambda_1 > 0 && res.lambda2 > 0)
        res.lambda_1 = 0;

    return res;
}