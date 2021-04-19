/*
 * main.h
 *
 *  Created on: Apr 16, 2021
 *      Author: grantweiss
 */

#ifndef MAIN_H_
#define MAIN_H_

#define STRING_(x)                  #x                   // stringify without expand
#define XSTRING_(x)                 STRING_(x)           // expand then stringify

#define ATTR_OPTIMIZE(n)          __attribute__ ((optimize(XSTRING_(O##n))))
#define __ALWAYS_INLINE 		  __attribute__ ((always_inline))

void error(uint32_t);

#endif /* MAIN_H_ */
