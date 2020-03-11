/*
 * utils_lwip.h
 *
 *  Created on: 11 Mar 2020
 *      Author: Falk
 */

#ifndef UTILS_UTILS_LWIP_H_
#define UTILS_UTILS_LWIP_H_

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

#endif /* UTILS_UTILS_LWIP_H_ */
