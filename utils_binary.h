/*
 * utils_binary.h
 *
 *  Created on: 11 Mar 2020
 *      Author: Falk
 */
#include <sys/types.h>
#include <stdlib.h>

#ifndef UTILS_UTILS_BINARY_H_
#define UTILS_UTILS_BINARY_H_

inline
unsigned int del_bits(uint val, uint offset, uint len) {
	uint mask = ~0 << offset;      // ...11110000...
	mask &= ~(~0 << (offset+len)); // ...11110000... & ...01111111... --> ...01110000...
	return val & ~mask;
}

inline
void change_byte_order(uint8_t data[], int len) {
	int last = len-1;
	for(int i = 0; i < (int)(len/2); i++) {
		uint8_t tmp = data[i];
		data[i] = data[last-i];
		data[last-i] = tmp;
	}
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
	for(int i = 0; i <= bytes; i++) {
		int shift = 8*i - offset;
		if(shift > 0) {
			val |= data[index+i] << shift;
		} else {
			val |= data[index+i] >> -shift;
		}
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
		int shift = 8*i - offset;
		if(shift > 0) {
			data[index+i] = val >> shift;
		} else {
			data[index+i] = val << -shift;
		}
	}

	uint8_t lb_mask = ~0 << bits;
	data[index+bytes] &= lb_mask;
	data[index+bytes] |= (val >> (bytes*8 - offset)) & ~lb_mask;
}

#endif /* UTILS_UTILS_BINARY_H_ */
