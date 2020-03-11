/*
 * utils_string.h
 *
 *  Created on: 11 Mar 2020
 *      Author: Falk
 */

#ifndef UTILS_UTILS_STRING_H_
#define UTILS_UTILS_STRING_H_

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

#endif /* UTILS_UTILS_STRING_H_ */
