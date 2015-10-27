/* fwk.h */
/* Copyright (C) 2012 mbed.org, MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef FWK_H_
#define FWK_H_

#include "config.h"

#include "string.h"
//using namespace std;

#include "stdint.h"
typedef unsigned int size_t;

#ifndef __cplusplus
//boolean type compatibility
typedef byte bool;
#define true 1
#define false 0
#endif

#ifndef NULL
#define NULL ((void*)0)
#endif

#define CR '\x0D'
#define LF '\x0A'
#define GD '\x3E'
#define BRK '\x1A'

//Custom utility classes
#include "IOStream.h"
//#include "String.h"

//Error codes
#include "errors.h"

//Debug
#include "dbg.h"

//Utility macros
#define MIN(x,y) (((x)<(y))?(x):(y))
#define MAX(x,y) (((x)>(y))?(x):(y))

#endif /* FWK_H_ */
