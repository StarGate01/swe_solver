/**
 * @file FCore.cpp
 * @brief Implementation file of the F-Wave solver
 */


#include "FCore.hpp"
//#include <math.h>
#include <cmath>
#include <assert.h>

double FCore::h_func(qvector ql, qvector qr)
{
    return 0.5 * (ql.h + qr.h);
}

double FCore::u_func(qvector ql, qvector qr)
{
    assert(ql.h > ZERO_PRECISION && qr.h > ZERO_PRECISION);     /**< Assert h values are positive */

    double ul = ql.hu / ql.h;
    double ur = qr.hu / qr.h;
    return (ul * sqrt(ql.h) + ur * sqrt(qr.h)) / (sqrt(ql.h) + sqrt(qr.h));
}

struct vector2 FCore::f_func(qvector q)
{
    struct vector2 result = {
        q.hu, 
        q.hu * q.hu + 0.5 * G_CONST * q.h * q.h
    };
    return result;
}

struct fresult FCore::compute(qvector ql, qvector qr)
{
    struct fresult res = {0};

    assert(h_func(ql, qr) > ZERO_PRECISION);        /**< Assert h_func(ql, qr) positive*/

    double lambda_sqrt = sqrt(G_CONST * h_func(ql, qr));
    res.lambda_1 = u_func(ql, qr) - lambda_sqrt;
    res.lambda_2 = u_func(ql, qr) + lambda_sqrt;

    struct vector2 r1 = {1, res.lambda_1};
    struct vector2 r2 = {1, res.lambda_2};
    
    struct vector2 fqr = f_func(qr);
    struct vector2 fql = f_func(ql);
    
    struct vector2 df = {
        fqr.x - fql.x, 
        fqr.y - fql.y
    };

    assert(std::abs(res.lambda_2 - res.lambda_1) > ZERO_PRECISION); /**< Assert lambda_2 - lambda_1 != 0 (potential devision by zero) */

    struct vector2 alpha = {
        (df.x * res.lambda_2 - df.y) / (res.lambda_2 - res.lambda_1), 
        (df.x * res.lambda_1 + df.y) / (res.lambda_2 - res.lambda_1)
    };

    if(res.lambda_1 < 0)
    {
        res.adq_negative.x += alpha.x * r1.x;
        res.adq_negative.y += alpha.x * r1.y;
    }
    else if(res.lambda_1 > 0)
    {
        res.adq_positive.x += alpha.x * r1.x;
        res.adq_positive.y += alpha.x * r1.y;
    }
 
    if(res.lambda_2 < 0)
    {
        res.adq_negative.x += alpha.x * r2.x;
        res.adq_negative.y += alpha.x * r2.y;
    }
    else if(res.lambda_2 > 0)
    {
        res.adq_positive.x += alpha.x * r2.x;
        res.adq_positive.y += alpha.x * r2.y;  
    }
             
    if(res.lambda_1 < 0 && res.lambda_2)
        res.lambda_2 = 0;
    else if(res.lambda_1 > 0 && res.lambda_2 > 0)
        res.lambda_1 = 0;

    return res;
}