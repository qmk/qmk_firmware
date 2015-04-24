/* dbg.h */
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

#ifndef DBG_H_
#define DBG_H_

#ifdef __cplusplus
extern "C" {
#endif


void debug_init(void);
void debug(int level, const char* module, int line, const char* fmt, ...);
void debug_set_newline(const char* newline);
void debug_set_speed(int speed);
void debug_error(const char* module, int line, int ret);
void debug_exact(const char* fmt, ...);

#define DBG_INIT() do{ debug_init(); }while(0)

#define DBG_SET_NEWLINE( x ) do{ debug_set_newline(x); }while(0)

#define DBG_SET_SPEED( x ) do{ debug_set_speed(x); }while(0)

#if __DEBUG__ > 0
#ifndef __MODULE__
#error "__MODULE__ must be defined"
#endif
#endif

#if __DEBUG__ >= 1
#define ERR(...) do{ debug(1, __MODULE__, __LINE__, __VA_ARGS__); }while(0)
#else
#define ERR(...) do{ }while(0)
#endif

#if __DEBUG__ >= 2
#define WARN(...) do{ debug(2, __MODULE__, __LINE__, __VA_ARGS__); }while(0)
#else
#define WARN(...) do{ }while(0)
#endif

#if __DEBUG__ >= 3
#define INFO(...) do{ debug(3, __MODULE__, __LINE__, __VA_ARGS__); }while(0)
#define CHECK(ret) do{ if(ret){ debug_error(__MODULE__, __LINE__, ret); } }while(0)
#else
#define INFO(...) do{ }while(0)
#define CHECK(ret) do{ }while(0)
#endif

#if __DEBUG__ >= 4
#define DBG(...) do{ debug(4, __MODULE__, __LINE__, __VA_ARGS__); }while(0)
#define DBGX(...) do{ debug_exact(__VA_ARGS__); }while(0)
#else
#define DBG(...) do{ }while(0)
#define DBGX(...) do{ }while(0)
#endif

#ifdef __cplusplus
}
#endif

#endif /* DBG_H_ */
