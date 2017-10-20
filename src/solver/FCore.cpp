/*

    FCore.cpphpp
    Implementation file for FCore

*/

#include "FCore.hpp"
#include <math.h>

double h_func(qvector ql, qvector qr)
{
    return .5f * (ql.h + qr.h);
}

double u_func(qvector ql, qvector qr)
{
    double ul = ql.hu/ql.h;
    double ur = qr.hu/qr.h;
    return (ul*sqrt(ql.h)+ur*sqrt(qr.h))/(sqrt(ql.h)+sqrt(qr.h));
}

struct 2vector f_func(qvector q)
{
    return {q.hu, q.hu * q.hu + .5f * G_CONST * q.h * q.h};
}

fresult FCore::compute(qvector ql, qvector qr)
{
    fresult res = {0};
    
    struct fresult res;
    res.lambda_1 = u_func(ql, qr) - sqrt(G_CONST * h_func(ql, qr));
    res.lambda_2 = u_func(ql, qr) + sqrt(G_CONST * h_func(ql, qr));
    
    struct 2vector r1 = {1, lambda_1};
    struct 2vector r2 = {1, lambda_2};
    
    struct 2vector fqr = f_func(qr);
    struct 2vector fql = f_func(ql);
    
    struct 2vector df = {fqr.x - fql.x, fqr.y - fql.y};

    return res;
}