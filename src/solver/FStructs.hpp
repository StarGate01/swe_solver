/**
 * @file FStructs.hpp
 * @brief Structures used by the F-Wave solver
 */

#ifndef FSTRUCTS_HPP_
#define FSTRUCTS_HPP_

namespace solver
{

    /**
     * @brief Represents a 2D vector.
     */
    struct vector2
    {
        double x1; /**< The x1 or h coordinate */
        double x2; /**< The x2 or hu coordinate */

        /**
         * @brief Adds a vector to this vector
         */
        vector2 add(const vector2 b) { return {x1 + b.x1, x2 + b.x2}; };

        /**
         * @brief Substracts a vector from this vector
         */
        vector2 substract(const vector2 b) { return {x1 - b.x1, x2 - b.x2}; };

        /**
         * @brief Multiplies this vector with a scalar
         */
        vector2 multiply(double b) { return {x1 * b, x2 * b}; };

         /**
         * @brief Divides this vector with a scalar
         */
        vector2 divide(double b) { return {x1 / b, x2 / b}; };

    };

    /**
     * @brief Represents the result of the F-Wave solver.
     */
    struct fresult
    {
        double lambda_1; /**< The wave speed of the left going wave */
        double lambda_2; /**< The wave speed of the right going wave */
        vector2 adq_positive; /**< The positive net-update */
        vector2 adq_negative; /**< The negative net-update */
    };

};

#endif /* FSTRUCTS_HPP_ */