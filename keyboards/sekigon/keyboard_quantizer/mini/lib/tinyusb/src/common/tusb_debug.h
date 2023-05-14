/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2022, Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * This file is part of the TinyUSB stack.
 */

#ifndef _TUSB_DEBUG_H_
#define _TUSB_DEBUG_H_

#ifdef __cplusplus
 extern "C" {
#endif

//--------------------------------------------------------------------+
// Debug
//--------------------------------------------------------------------+

// CFG_TUSB_DEBUG for debugging
// 0 : no debug
// 1 : print error
// 2 : print warning
// 3 : print info
#if CFG_TUSB_DEBUG

// Enum to String for debugging purposes
#if CFG_TUSB_DEBUG >= 2
extern char const* const tu_str_speed[];
extern char const* const tu_str_std_request[];
#endif

void tu_print_mem(void const *buf, uint32_t count, uint8_t indent);

#ifdef CFG_TUSB_DEBUG_PRINTF
  extern int CFG_TUSB_DEBUG_PRINTF(const char *format, ...);
  #define tu_printf    CFG_TUSB_DEBUG_PRINTF
#else
  #define tu_printf    printf
#endif

static inline void tu_print_arr(uint8_t const* buf, uint32_t bufsize)
{
  for(uint32_t i=0; i<bufsize; i++) tu_printf("%02X ", buf[i]);
}

// Log with Level
#define TU_LOG(n, ...)        TU_XSTRCAT(TU_LOG, n)(__VA_ARGS__)
#define TU_LOG_MEM(n, ...)    TU_XSTRCAT3(TU_LOG, n, _MEM)(__VA_ARGS__)
#define TU_LOG_ARR(n, ...)    TU_XSTRCAT3(TU_LOG, n, _ARR)(__VA_ARGS__)
#define TU_LOG_PTR(n, ...)    TU_XSTRCAT3(TU_LOG, n, _PTR)(__VA_ARGS__)
#define TU_LOG_INT(n, ...)    TU_XSTRCAT3(TU_LOG, n, _INT)(__VA_ARGS__)
#define TU_LOG_HEX(n, ...)    TU_XSTRCAT3(TU_LOG, n, _HEX)(__VA_ARGS__)
#define TU_LOG_LOCATION()     tu_printf("%s: %d:\r\n", __PRETTY_FUNCTION__, __LINE__)
#define TU_LOG_FAILED()       tu_printf("%s: %d: Failed\r\n", __PRETTY_FUNCTION__, __LINE__)

// Log Level 1: Error
#define TU_LOG1               tu_printf
#define TU_LOG1_MEM           tu_print_mem
#define TU_LOG1_ARR(_x, _n)   tu_print_arr((uint8_t const*)(_x), _n)
#define TU_LOG1_PTR(_x)       tu_print_arr((uint8_t const*)(_x), sizeof(*(_x)))
#define TU_LOG1_INT(_x)       tu_printf(#_x " = %ld\r\n", (unsigned long) (_x) )
#define TU_LOG1_HEX(_x)       tu_printf(#_x " = %lX\r\n", (unsigned long) (_x) )

// Log Level 2: Warn
#if CFG_TUSB_DEBUG >= 2
  #define TU_LOG2             TU_LOG1
  #define TU_LOG2_MEM         TU_LOG1_MEM
  #define TU_LOG2_ARR         TU_LOG1_ARR
  #define TU_LOG2_PTR         TU_LOG1_PTR
  #define TU_LOG2_INT         TU_LOG1_INT
  #define TU_LOG2_HEX         TU_LOG1_HEX
#endif

// Log Level 3: Info
#if CFG_TUSB_DEBUG >= 3
  #define TU_LOG3             TU_LOG1
  #define TU_LOG3_MEM         TU_LOG1_MEM
  #define TU_LOG3_ARR         TU_LOG1_ARR
  #define TU_LOG3_PTR         TU_LOG1_PTR
  #define TU_LOG3_INT         TU_LOG1_INT
  #define TU_LOG3_HEX         TU_LOG1_HEX
#endif

typedef struct
{
  uint32_t key;
  const char* data;
} tu_lookup_entry_t;

typedef struct
{
  uint16_t count;
  tu_lookup_entry_t const* items;
} tu_lookup_table_t;

static inline const char* tu_lookup_find(tu_lookup_table_t const* p_table, uint32_t key)
{
  tu_static char not_found[11];

  for(uint16_t i=0; i<p_table->count; i++)
  {
    if (p_table->items[i].key == key) return p_table->items[i].data;
  }

  // not found return the key value in hex
  snprintf(not_found, sizeof(not_found), "0x%08lX", (unsigned long) key);

  return not_found;
}

#endif // CFG_TUSB_DEBUG

#ifndef TU_LOG
  #define TU_LOG(n, ...)
  #define TU_LOG_MEM(n, ...)
  #define TU_LOG_PTR(n, ...)
  #define TU_LOG_INT(n, ...)
  #define TU_LOG_HEX(n, ...)
  #define TU_LOG_LOCATION()
  #define TU_LOG_FAILED()
#endif

// TODO replace all TU_LOGn with TU_LOG(n)

#define TU_LOG0(...)
#define TU_LOG0_MEM(...)
#define TU_LOG0_PTR(...)
#define TU_LOG0_INT(...)
#define TU_LOG0_HEX(...)

#ifndef TU_LOG1
  #define TU_LOG1(...)
  #define TU_LOG1_MEM(...)
  #define TU_LOG1_PTR(...)
  #define TU_LOG1_INT(...)
  #define TU_LOG1_HEX(...)
#endif

#ifndef TU_LOG2
  #define TU_LOG2(...)
  #define TU_LOG2_MEM(...)
  #define TU_LOG2_PTR(...)
  #define TU_LOG2_INT(...)
  #define TU_LOG2_HEX(...)
#endif

#ifndef TU_LOG3
  #define TU_LOG3(...)
  #define TU_LOG3_MEM(...)
  #define TU_LOG3_PTR(...)
  #define TU_LOG3_INT(...)
  #define TU_LOG3_HEX(...)
#endif

#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_DEBUG_H_ */
