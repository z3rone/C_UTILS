/*
 * utils_math.h
 *
 *  Created on: 11 Mar 2020
 *      Author: Falk
 */

#include <math.h>

#ifndef UTILS_UTILS_MATH_H_
#define UTILS_UTILS_MATH_H_

/**
 * @brief Get the absolute value of an integer.
 * @param i Value
 * @return Absolute value
 */
/*__weak inline
unsigned int abs(int i){
	return i<0?i*-1:i;
}*/

/**
 * @brief Linear regression.
 */
inline
int lin_reg(int a, int b, int dx, int x) {
	if(x == 0) return a;
	if(x >= dx) return b;

	int dy = b - a;
	double asc = ((double) dy) / ((double) dx);

	return round(a+(asc*x));
}

/**
 * @brief Iterative modulo function.
 * @param i number
 * @param d divider
 */
inline
int mod_iter(int i, int d) {
	while(i >= d) {
		i -= d;
	}

	return i;
}

inline
int limit_i(int x, int min, int max) {
	if(x < min) return min;
	if(x > max) return max;
	return x;
}

#endif /* UTILS_UTILS_MATH_H_ */
