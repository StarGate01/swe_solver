/**
 * @file FCore.cpp
 * @brief Implementation file of the F-Wave solver
 */


#include "FCore.hpp"
#include "FCalc.hpp"
#include "FConst.hpp"
#include <cmath>
#include <assert.h>


struct fresult FCore::compute(qvector ql, qvector qr)
{
    //Special case ql=qr={0,0}
    if(ql.h == 0 && ql.hu == 0 && qr.h == 0 && qr.hu == 0)
    {
        struct vector2 zerovector = {0.0, 0.0};
        struct fresult res = {zerovector, zerovector, 0.0, 0.0};
        return res;
    }

    struct fresult res = {0};

    assert(FCalc::h_func(ql, qr) >= 0);        /**< Assert h_func(ql, qr) positive*/

    double lambda_sqrt = sqrt(G_CONST * FCalc::h_func(ql, qr));
    res.lambda_1 = FCalc::u_func(ql, qr) - lambda_sqrt;
    res.lambda_2 = FCalc::u_func(ql, qr) + lambda_sqrt;

    struct vector2 r1 = {1, res.lambda_1};
    struct vector2 r2 = {1, res.lambda_2};
    
    struct vector2 fqr = FCalc::f_func(qr);
    struct vector2 fql = FCalc::f_func(ql);
    
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