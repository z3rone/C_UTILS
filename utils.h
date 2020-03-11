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
#include <main.h>
#endif

#ifndef UTILS_H
#define UTILS_H

#ifdef UTILS_MATH
#include "./utils_math.h"
#endif

#ifdef UTILS_STM32
#include "./utils_stm32.h"
#endif

#ifdef UTILS_BINARY
#include "./utils_binary.h"
#endif

#ifdef UTILS_LWIP
#include "./utils_lwip.h"
#endif

#ifdef UTILS_STRING
#include "./utils_string.h"
#endif

#endif
