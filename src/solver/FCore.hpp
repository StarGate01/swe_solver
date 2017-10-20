/*

    FCore.hpp
    Header file for FCore

*/

#ifndef FCORE_HPP_
#define FCORE_HPP_

#include "FStructs.hpp"

#define G_CONST 9.81f

class FCore
{

public:
    static struct fresult compute(qvector ql, qvector qr);


private:
    static double h_func(qvector ql, qvector qr);
    static double u_func(qvector ql, qvector qr);
    static struct vector2 f_func(qvector q);

};


#endif /* FCORE_HPP_ */