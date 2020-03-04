/*
 * utils.h
 *
 *  Created on: Dec 9, 2019
 *      Author: Falk B. Schimweg
 */

#include <math.h>
#include <sys/types.h>
#include <stdlib.h>

#ifdef UTILS_LWIP
#include "lwip/udp.h"
#include "lwip/ip4_addr.h"
#include "lwip.h"
#endif

#ifdef UTILS_STM32
#include <stm32f3xx_hal.h>
#endif

#ifndef UTILS_H
#define UTILS_H

#ifdef UTILS_MATH
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
#endif

#ifdef UTILS_STM32
inline
void __timer_set(TIM_HandleTypeDef* tim, uint32_t ch, double frq, double dty) {
	__IO uint16_t autoload = round(1000000.0/(double)frq);
	__IO uint16_t compare  = round(((double)dty/100.0)*autoload);
	__HAL_TIM_SET_AUTORELOAD(tim, autoload);
	__HAL_TIM_SET_COMPARE(tim, ch, compare);
}
#endif

#ifdef UTILS_BINARY
inline
unsigned int del_bits(uint val, uint offset, uint len) {
	uint mask = ~0 << offset;      // ...11110000...
	mask &= ~(~0 << (offset+len)); // ...11110000... & ...01111111... --> ...01110000...
	return val & ~mask;
}

/**
 * @brief Extracts bit sequence from byte array.
 * @param data  Byte array
 * @param start Start of bit section
 * @param amt   Number of bits
 * @return Bit sequence
 */
inline
unsigned int get_bits(uint8_t* data, int start, int amt) {
	div_t begin = div(start, 8);
	int index = begin.quot;
	int offset = begin.rem;

	div_t end = div(amt + offset, 8);
	int bytes = end.quot;

	int val = 0;
	for(int i = 0; i < bytes; i++) {
		val |= data[index+i] << (8*i - offset);
	}

	val &= ~(~0 << amt); // Cut off additional bits at the left
	return val;
}

/**
 * @brief Inserts bit sequence from byte array.
 * @param data  Byte array
 * @param val   Bits to insert
 * @param start Start of insert
 * @param amt   Number of bits
 * TODO Testing!
 */
inline
void set_bits(uint8_t* data, unsigned int val, int start, int amt) {
	div_t begin = div(start, 8);
	int index = begin.quot;
	int offset = begin.rem;

	div_t end = div(amt + offset, 8);
	int bytes = end.quot;
	int bits = end.rem;

	data[index] &= ~(~0 << offset);
	data[index] |= (val << offset) & 0xFF;

	for(int i = 1; i < bytes; i++) {
		data[i] = val >> (8*i - offset);
	}

	data[index+bytes] &= ~(~0 << bits);
	data[index+bytes] |= val >> (bytes*8 - offset);
}
#endif

#ifdef UTILS_LWIP
inline void pbuf_next(struct pbuf** p, int* i, int size) {
	(*i)++;
	if((*i) * size > (*p)->len) {
		if((*p)->len < (*p)->tot_len) {
			*p = (*p)->next;
			*i = 0;
		} else {
			*p = NULL;
		}
	}
}
#endif

#ifdef UTILS_STRING
#define STYLE_TEXT_BLACK   ("\033[30m")
#define STYLE_TEXT_RED     ("\033[31m")
#define STYLE_TEXT_GREEN   ("\033[32m")
#define STYLE_TEXT_YELLOW  ("\033[33m")
#define STYLE_TEXT_BLUE    ("\033[34m")
#define STYLE_TEXT_MAGENTA ("\033[35m")
#define STYLE_TEXT_CYAN    ("\033[36m")
#define STYLE_TEXT_WHITE   ("\033[37m")
#define STYLE_TEXT_RGB(r,g,b)("\033[38;2;" r ";" g ";" b "m")
#define STYLE_RESET        ("\033[0m")
#define POOP ("\033[38;5;94m\xF0\x9F\x92\xA9\033[0m")

#define CLS "\033[2J\033[;H"

#define CURSOR_LEFT(i) ("\033["i"D")
#endif

#endif
