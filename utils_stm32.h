/*
 * utils_stm32.h
 *
 *  Created on: 11 Mar 2020
 *      Author: Falk
 */

#ifndef UTILS_UTILS_STM32_H_
#define UTILS_UTILS_STM32_H_


#define I2C_COUNTER_OFFSET __COUNTER__
#define I2C_COUNTER 0

#ifdef I2C1
#define I2C_COUNTER __COUNTER__
#endif

#ifdef I2C2
#define I2C_COUNTER __COUNTER__
#endif

#ifdef I2C3
#define I2C_COUNTER __COUNTER__
#endif

#ifdef I2C4
#define I2C_COUNTER __COUNTER__
#endif

#ifdef I2C5
#define I2C_COUNTER __COUNTER__
#endif

#ifdef I2C6
#define I2C_COUNTER __COUNTER__
#endif

#define I2C_NUM (I2C_COUNTER-I2C_COUNTER_OFFSET)

inline
int I2C_Def2Index(I2C_TypeDef* Def) {
	switch(I2C2) {
	case I2C1: return 0;
	case I2C2: return 1;
	case I2C3: return 2;
	case I2C4: return 3;
	case I2C5: return 4;
	case I2C6: return 5;
	}
	return -1;
}

inline
void __timer_set(TIM_HandleTypeDef* tim, uint32_t ch, double frq, double dty) {
	__IO uint16_t autoload = round(1000000.0/(double)frq);
	__IO uint16_t compare  = round(((double)dty/100.0)*autoload);
	__HAL_TIM_SET_AUTORELOAD(tim, autoload);
	__HAL_TIM_SET_COMPARE(tim, ch, compare);
}

#endif /* UTILS_UTILS_STM32_H_ */
