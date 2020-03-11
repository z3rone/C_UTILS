/*
 * utils_stm32.h
 *
 *  Created on: 11 Mar 2020
 *      Author: Falk
 */

#include <main.h>
#include <math.h>

#ifndef UTILS_UTILS_STM32_H_
#define UTILS_UTILS_STM32_H_

inline
void __timer_set(TIM_HandleTypeDef* tim, uint32_t ch, double frq, double dty) {
	__IO uint16_t autoload = round(1000000.0/(double)frq);
	__IO uint16_t compare  = round(((double)dty/100.0)*autoload);
	__HAL_TIM_SET_AUTORELOAD(tim, autoload);
	__HAL_TIM_SET_COMPARE(tim, ch, compare);
}

#endif /* UTILS_UTILS_STM32_H_ */
