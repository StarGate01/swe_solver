/**
 * @file FStructs.hpp
 * @brief Structures used by the F-Wave solver
 */

#ifndef FSTRUCTS_HPP_
#define FSTRUCTS_HPP_

/**
 * @brief Represents a 2D vector.
 */
struct vector2
{
    double x; /**< The x coordinate */
    double y; /**< The y coordinate */
};

/**
 * @brief Represents a net-update.
 */
struct qvector
{
    double h; /**< The height */
    double hu; /**< The momentum */
};

/**
 * @brief Represents the result of the F-Wave solver.
 */
struct fresult
{
    struct vector2 adq_positive; /**< The positive net-update */
    struct vector2 adq_negative; /**< The negative net-update */
    double lambda_1; /**< The wave speed of the left going wave */
    double lambda_2; /**< The wave speed of the right going wave */
};

#endif /* FSTRUCTS_HPP_ */