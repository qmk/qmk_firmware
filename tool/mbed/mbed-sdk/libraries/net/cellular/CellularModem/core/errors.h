/* errors.h */
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
 
#ifndef ERRORS_H_
#define ERRORS_H_

/** \page Network-related errors */

#define OK 0 //No error

#define NET_FULL 1 //>All available resources are already used
#define NET_EMPTY 2 //>No resource
#define NET_NOTFOUND 3 //>Element cannot be found
#define NET_INVALID 4 //>Invalid
#define NET_CONTEXT 5 //>Called in a wrong context (eg during an interrupt)
#define NET_TIMEOUT 6 //>Timeout
#define NET_UNKNOWN 7 //>Unknown error
#define NET_OVERFLOW 8 //>Overflow
#define NET_PROCESSING 9 //>Command is processing
#define NET_INTERRUPTED 10 //>Current operation has been interrupted
#define NET_MOREINFO 11 //>More info on this error can be retrieved elsewhere (eg in a parameter passed as ptr)
#define NET_ABORT 12 //>Current operation must be aborted
#define NET_DIFF 13 //>Items that should match are different
#define NET_AUTH 14 //>Authentication failed
#define NET_PROTOCOL 15 //>Protocol error
#define NET_OOM 16 //>Out of memory
#define NET_CONN 17 //>Connection error
#define NET_CLOSED 18 //>Connection was closed by remote end
#define NET_TOOSMALL 19 //>Buffer is too small

#endif /* ERRORS_H_ */
