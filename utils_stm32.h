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

#define DEV_ID_BASE_F0 ((uint32_t*)0x1FFFF7AC)
#define DEV_ID_BASE_F1 ((uint32_t*)0x1FFFF7E8)
#define DEV_ID_BASE_F2 ((uint32_t*)0x1FFF7A10)
#define DEV_ID_BASE_F3 ((uint32_t*)0x1FFFF7AC)
#define DEV_ID_BASE_F4 ((uint32_t*)0x1FFF7A10)
#define DEV_ID_BASE_F7 ((uint32_t*)0x1FF0F420)

inline
uint32_t get_DevID_32(uint32_t* base) {
	uint32_t id = 0;
	for(int i = 0; i < 3; i++) {
		id ^= base[i];
	}
	return id;
}

inline
uint16_t get_DevID_16(uint32_t* base) {
	uint32_t id32 = get_DevID_32(base);
	uint16_t id16 = 0;
	for(int shift = 0; shift < 32; shift += 16) {
		id16 ^= (id32 >> shift) & 0xFFFF;
	}
	return id16;
}

inline
uint8_t get_DevID_8(uint32_t* base) {
	uint16_t id16 = get_DevID_16(base);
	uint8_t id8 = 0;
	for(int shift = 0; shift < 16; shift += 8) {
		id8 ^= (id16 >> shift) & 0xFF;
	}
	return id8;
}

inline
uint8_t get_DevID_4(uint32_t* base) {
	uint32_t id8 = get_DevID_8(base);
	uint16_t id4 = 0;
	for(int shift = 0; shift < 8; shift += 4) {
		id4 ^= (id8 >> shift) & 0xF;
	}
	return id4;
}

#endif /* UTILS_UTILS_STM32_H_ */
