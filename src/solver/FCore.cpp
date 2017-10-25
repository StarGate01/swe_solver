/**
 * @file FCore.cpp
 * @brief Implementation of FCore.hpp
 */

#include <cmath>
#include <assert.h>
#include "FCore.hpp"
#include "FCalc.hpp"
#include "FConst.hpp"

using namespace solver;

struct fresult FCore::compute(qvector ql, qvector qr)
{
    //TODO: Treat very small numbers < ZERO_PRECISION
    if(ql.h == 0 && ql.hu == 0 && qr.h == 0 && qr.hu == 0) //Special case, where inputs are zero
    {
        struct vector2 zerovector = {0.0, 0.0}; //Create zero vector
        struct fresult res = {zerovector, zerovector, 0.0, 0.0}; //Create output struct, where all values are zero 
        return res;
    }

    struct fresult res = {0}; //Initialize result struct 

    assert(FCalc::h_func(ql, qr) >= 0); //Assert h_func(ql, qr) is positive

    double lambda_sqrt = sqrt(G_CONST * FCalc::h_func(ql, qr));//Calculate square root in definition of of lambdas
    res.lambda_1 = FCalc::u_func(ql, qr) - lambda_sqrt; //Calculate lambda_1 
    res.lambda_2 = FCalc::u_func(ql, qr) + lambda_sqrt; //Calculate lambda_2 

    struct vector2 r1 = {1, res.lambda_1}; //Create r_1 vector
    struct vector2 r2 = {1, res.lambda_2}; //Create r_2 vector
    
    struct vector2 fqr = FCalc::f_func(qr); //Calculate f(qr)
    struct vector2 fql = FCalc::f_func(ql); //Calculate f(ql)
    
    struct vector2 df = { //Calculate delta f
        fqr.x - fql.x, 
        fqr.y - fql.y
    };

    assert(std::abs(res.lambda_2 - res.lambda_1) > ZERO_PRECISION); //Assert lambda_2 - lambda_1 != 0 (potential division by zero) 

    struct vector2 alpha = {
        (df.x * res.lambda_2 - df.y) / (res.lambda_2 - res.lambda_1), 
        (df.x * res.lambda_1 + df.y) / (res.lambda_2 - res.lambda_1)
    };

    if(res.lambda_1 < 0) //In case lambda_1 is negative, assign AdQ appropriately
    {
        res.adq_negative.x += alpha.x * r1.x;
        res.adq_negative.y += alpha.x * r1.y;
    }
    else if(res.lambda_1 > 0) //In case lambda_1 is positive, assign AdQ appropriately
    {
        res.adq_positive.x += alpha.x * r1.x;
        res.adq_positive.y += alpha.x * r1.y;
    }
 
    if(res.lambda_2 < 0) //In case lambda_2 is negative, assign AdQ appropriately
    {
        res.adq_negative.x += alpha.x * r2.x;
        res.adq_negative.y += alpha.x * r2.y;
    }
    else if(res.lambda_2 > 0) //In case lambda_1 is positive, assign AdQ appropriately
    {
        res.adq_positive.x += alpha.x * r2.x;
        res.adq_positive.y += alpha.x * r2.y;  
    }
             
    if(res.lambda_1 < 0 && res.lambda_2) //Handle special cases
        res.lambda_2 = 0;
    else if(res.lambda_1 > 0 && res.lambda_2 > 0)
        res.lambda_1 = 0;

    return res;
}