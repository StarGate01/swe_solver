/*

    FStructs.hpp
    Header file for FStructs

*/

#ifndef FSTRUCTS_HPP_
#define FSTRUCTS_HPP_

struct vector2
{
    double x;
    double y;
};

struct qvector
{
    double h;
    double hu;
};

struct fresult
{
    double adq_positive;
    double adq_negative;
    double lambda_1;
    double lambda_2;
};

#endif /* FSTRUCTS_HPP_ */