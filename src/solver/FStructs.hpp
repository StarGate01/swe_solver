/*

    FStructs.hpp
    Header file for FStructs

*/

#ifndef FSTRUCTS_HPP_
#define FSTRUCTS_HPP_


struct qvector
{
    double h;
    double hu;
};

struct fresult
{
    double adq_positive;
    double adq_negative;
    double lambda_l;
    double lambda_r;
};

#endif /* FSTRUCTS_HPP_ */