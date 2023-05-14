/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
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

#ifndef _TUSB_COMMON_H_
#define _TUSB_COMMON_H_

#ifdef __cplusplus
 extern "C" {
#endif

//--------------------------------------------------------------------+
// Macros Helper
//--------------------------------------------------------------------+
#define TU_ARRAY_SIZE(_arr)   ( sizeof(_arr) / sizeof(_arr[0]) )
#define TU_MIN(_x, _y)        ( ( (_x) < (_y) ) ? (_x) : (_y) )
#define TU_MAX(_x, _y)        ( ( (_x) > (_y) ) ? (_x) : (_y) )

#define TU_U16(_high, _low)   ((uint16_t) (((_high) << 8) | (_low)))
#define TU_U16_HIGH(_u16)     ((uint8_t) (((_u16) >> 8) & 0x00ff))
#define TU_U16_LOW(_u16)      ((uint8_t) ((_u16)       & 0x00ff))
#define U16_TO_U8S_BE(_u16)   TU_U16_HIGH(_u16), TU_U16_LOW(_u16)
#define U16_TO_U8S_LE(_u16)   TU_U16_LOW(_u16), TU_U16_HIGH(_u16)

#define TU_U32_BYTE3(_u32)    ((uint8_t) ((((uint32_t) _u32) >> 24) & 0x000000ff)) // MSB
#define TU_U32_BYTE2(_u32)    ((uint8_t) ((((uint32_t) _u32) >> 16) & 0x000000ff))
#define TU_U32_BYTE1(_u32)    ((uint8_t) ((((uint32_t) _u32) >>  8) & 0x000000ff))
#define TU_U32_BYTE0(_u32)    ((uint8_t) (((uint32_t)  _u32)        & 0x000000ff)) // LSB

#define U32_TO_U8S_BE(_u32)   TU_U32_BYTE3(_u32), TU_U32_BYTE2(_u32), TU_U32_BYTE1(_u32), TU_U32_BYTE0(_u32)
#define U32_TO_U8S_LE(_u32)   TU_U32_BYTE0(_u32), TU_U32_BYTE1(_u32), TU_U32_BYTE2(_u32), TU_U32_BYTE3(_u32)

#define TU_BIT(n)             (1UL << (n))
#define TU_GENMASK(h, l)      ( (UINT32_MAX << (l)) & (UINT32_MAX >> (31 - (h))) )

//--------------------------------------------------------------------+
// Includes
//--------------------------------------------------------------------+

// Standard Headers
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

// Tinyusb Common Headers
#include "tusb_option.h"
#include "tusb_compiler.h"
#include "tusb_verify.h"
#include "tusb_types.h"
#include "tusb_debug.h"

#include "tusb_timeout.h" // TODO remove

//--------------------------------------------------------------------+
// Optional API implemented by application if needed
// TODO move to a more ovious place/file
//--------------------------------------------------------------------+

// flush data cache
TU_ATTR_WEAK extern void tusb_app_dcache_flush(uintptr_t addr, uint32_t data_size);

// invalidate data cache
TU_ATTR_WEAK extern void tusb_app_dcache_invalidate(uintptr_t addr, uint32_t data_size);

// Optional physical <-> virtual address translation
TU_ATTR_WEAK extern void* tusb_app_virt_to_phys(void *virt_addr);
TU_ATTR_WEAK extern void* tusb_app_phys_to_virt(void *phys_addr);

//--------------------------------------------------------------------+
// Internal Inline Functions
//--------------------------------------------------------------------+

//------------- Mem -------------//
#define tu_memclr(buffer, size)  memset((buffer), 0, (size))
#define tu_varclr(_var)          tu_memclr(_var, sizeof(*(_var)))

//------------- Bytes -------------//
TU_ATTR_ALWAYS_INLINE static inline uint32_t tu_u32(uint8_t b3, uint8_t b2, uint8_t b1, uint8_t b0)
{
  return ( ((uint32_t) b3) << 24) | ( ((uint32_t) b2) << 16) | ( ((uint32_t) b1) << 8) | b0;
}

TU_ATTR_ALWAYS_INLINE static inline uint16_t tu_u16(uint8_t high, uint8_t low)
{
  return (uint16_t) ((((uint16_t) high) << 8) | low);
}

TU_ATTR_ALWAYS_INLINE static inline uint8_t tu_u32_byte3(uint32_t ui32) { return TU_U32_BYTE3(ui32); }
TU_ATTR_ALWAYS_INLINE static inline uint8_t tu_u32_byte2(uint32_t ui32) { return TU_U32_BYTE2(ui32); }
TU_ATTR_ALWAYS_INLINE static inline uint8_t tu_u32_byte1(uint32_t ui32) { return TU_U32_BYTE1(ui32); }
TU_ATTR_ALWAYS_INLINE static inline uint8_t tu_u32_byte0(uint32_t ui32) { return TU_U32_BYTE0(ui32); }

TU_ATTR_ALWAYS_INLINE static inline uint16_t tu_u32_high16(uint32_t ui32) { return (uint16_t) (ui32 >> 16); }
TU_ATTR_ALWAYS_INLINE static inline uint16_t tu_u32_low16 (uint32_t ui32) { return (uint16_t) (ui32 & 0x0000ffffu); }

TU_ATTR_ALWAYS_INLINE static inline uint8_t tu_u16_high(uint16_t ui16) { return TU_U16_HIGH(ui16); }
TU_ATTR_ALWAYS_INLINE static inline uint8_t tu_u16_low (uint16_t ui16) { return TU_U16_LOW(ui16); }

//------------- Bits -------------//
TU_ATTR_ALWAYS_INLINE static inline uint32_t tu_bit_set  (uint32_t value, uint8_t pos) { return value | TU_BIT(pos);                  }
TU_ATTR_ALWAYS_INLINE static inline uint32_t tu_bit_clear(uint32_t value, uint8_t pos) { return value & (~TU_BIT(pos));               }
TU_ATTR_ALWAYS_INLINE static inline bool     tu_bit_test (uint32_t value, uint8_t pos) { return (value & TU_BIT(pos)) ? true : false; }

//------------- Min -------------//
TU_ATTR_ALWAYS_INLINE static inline uint8_t  tu_min8  (uint8_t  x, uint8_t y ) { return (x < y) ? x : y; }
TU_ATTR_ALWAYS_INLINE static inline uint16_t tu_min16 (uint16_t x, uint16_t y) { return (x < y) ? x : y; }
TU_ATTR_ALWAYS_INLINE static inline uint32_t tu_min32 (uint32_t x, uint32_t y) { return (x < y) ? x : y; }

//------------- Max -------------//
TU_ATTR_ALWAYS_INLINE static inline uint8_t  tu_max8  (uint8_t  x, uint8_t y ) { return (x > y) ? x : y; }
TU_ATTR_ALWAYS_INLINE static inline uint16_t tu_max16 (uint16_t x, uint16_t y) { return (x > y) ? x : y; }
TU_ATTR_ALWAYS_INLINE static inline uint32_t tu_max32 (uint32_t x, uint32_t y) { return (x > y) ? x : y; }

//------------- Align -------------//
TU_ATTR_ALWAYS_INLINE static inline uint32_t tu_align(uint32_t value, uint32_t alignment)
{
  return value & ((uint32_t) ~(alignment-1));
}

TU_ATTR_ALWAYS_INLINE static inline uint32_t tu_align16 (uint32_t value) { return (value & 0xFFFFFFF0UL); }
TU_ATTR_ALWAYS_INLINE static inline uint32_t tu_align32 (uint32_t value) { return (value & 0xFFFFFFE0UL); }
TU_ATTR_ALWAYS_INLINE static inline uint32_t tu_align4k (uint32_t value) { return (value & 0xFFFFF000UL); }
TU_ATTR_ALWAYS_INLINE static inline uint32_t tu_offset4k(uint32_t value) { return (value & 0xFFFUL); }

//------------- Mathematics -------------//
TU_ATTR_ALWAYS_INLINE static inline uint32_t tu_div_ceil(uint32_t v, uint32_t d) { return (v + d -1)/d; }

// log2 of a value is its MSB's position
// TODO use clz TODO remove
static inline uint8_t tu_log2(uint32_t value)
{
  uint8_t result = 0;
  while (value >>= 1) { result++; }
  return result;
}

//static inline uint8_t tu_log2(uint32_t value)
//{
//   return sizeof(uint32_t) * CHAR_BIT - __builtin_clz(x) - 1;
//}

static inline bool tu_is_power_of_two(uint32_t value)
{
   return (value != 0) && ((value & (value - 1)) == 0);
}

//------------- Unaligned Access -------------//
#if TUP_ARCH_STRICT_ALIGN

// Rely on compiler to generate correct code for unaligned access
typedef struct { uint16_t val; } TU_ATTR_PACKED tu_unaligned_uint16_t;
typedef struct { uint32_t val; } TU_ATTR_PACKED tu_unaligned_uint32_t;

TU_ATTR_ALWAYS_INLINE static inline uint32_t tu_unaligned_read32(const void* mem)
{
  tu_unaligned_uint32_t const* ua32 = (tu_unaligned_uint32_t const*) mem;
  return ua32->val;
}

TU_ATTR_ALWAYS_INLINE static inline void tu_unaligned_write32(void* mem, uint32_t value)
{
  tu_unaligned_uint32_t* ua32 = (tu_unaligned_uint32_t*) mem;
  ua32->val = value;
}

TU_ATTR_ALWAYS_INLINE static inline uint16_t tu_unaligned_read16(const void* mem)
{
  tu_unaligned_uint16_t const* ua16 = (tu_unaligned_uint16_t const*) mem;
  return ua16->val;
}

TU_ATTR_ALWAYS_INLINE static inline void tu_unaligned_write16(void* mem, uint16_t value)
{
  tu_unaligned_uint16_t* ua16 = (tu_unaligned_uint16_t*) mem;
  ua16->val = value;
}

#elif TUP_MCU_STRICT_ALIGN

// MCU such as LPC_IP3511 Highspeed cannot access unaligned memory on USB_RAM although it is ARM M4.
// We have to manually pick up bytes since tu_unaligned_uint32_t will still generate unaligned code
// NOTE: volatile cast to memory to prevent compiler to optimize and generate unaligned code
// TODO Big Endian may need minor changes
TU_ATTR_ALWAYS_INLINE static inline uint32_t tu_unaligned_read32(const void* mem)
{
  volatile uint8_t const* buf8 = (uint8_t const*) mem;
  return tu_u32(buf8[3], buf8[2], buf8[1], buf8[0]);
}

TU_ATTR_ALWAYS_INLINE static inline void tu_unaligned_write32(void* mem, uint32_t value)
{
  volatile uint8_t* buf8 = (uint8_t*) mem;
  buf8[0] = tu_u32_byte0(value);
  buf8[1] = tu_u32_byte1(value);
  buf8[2] = tu_u32_byte2(value);
  buf8[3] = tu_u32_byte3(value);
}

TU_ATTR_ALWAYS_INLINE static inline uint16_t tu_unaligned_read16(const void* mem)
{
  volatile uint8_t const* buf8 = (uint8_t const*) mem;
  return tu_u16(buf8[1], buf8[0]);
}

TU_ATTR_ALWAYS_INLINE static inline void tu_unaligned_write16(void* mem, uint16_t value)
{
  volatile uint8_t* buf8 = (uint8_t*) mem;
  buf8[0] = tu_u16_low(value);
  buf8[1] = tu_u16_high(value);
}


#else

// MCU that could access unaligned memory natively
TU_ATTR_ALWAYS_INLINE static inline uint32_t tu_unaligned_read32  (const void* mem) { return *((uint32_t const *) mem); }
TU_ATTR_ALWAYS_INLINE static inline uint16_t tu_unaligned_read16  (const void* mem) { return *((uint16_t const *) mem); }

TU_ATTR_ALWAYS_INLINE static inline void     tu_unaligned_write32 (void* mem, uint32_t value ) { *((uint32_t*) mem) = value; }
TU_ATTR_ALWAYS_INLINE static inline void     tu_unaligned_write16 (void* mem, uint16_t value ) { *((uint16_t*) mem) = value; }

#endif

// To be removed
//------------- Binary constant -------------//
#if defined(__GNUC__) && !defined(__CC_ARM)

#define TU_BIN8(x)               ((uint8_t)  (0b##x))
#define TU_BIN16(b1, b2)         ((uint16_t) (0b##b1##b2))
#define TU_BIN32(b1, b2, b3, b4) ((uint32_t) (0b##b1##b2##b3##b4))

#else

//  internal macro of B8, B16, B32
#define _B8__(x) (((x&0x0000000FUL)?1:0) \
                +((x&0x000000F0UL)?2:0) \
                +((x&0x00000F00UL)?4:0) \
                +((x&0x0000F000UL)?8:0) \
                +((x&0x000F0000UL)?16:0) \
                +((x&0x00F00000UL)?32:0) \
                +((x&0x0F000000UL)?64:0) \
                +((x&0xF0000000UL)?128:0))

#define TU_BIN8(d) ((uint8_t) _B8__(0x##d##UL))
#define TU_BIN16(dmsb,dlsb) (((uint16_t)TU_BIN8(dmsb)<<8) + TU_BIN8(dlsb))
#define TU_BIN32(dmsb,db2,db3,dlsb) \
            (((uint32_t)TU_BIN8(dmsb)<<24) \
            + ((uint32_t)TU_BIN8(db2)<<16) \
            + ((uint32_t)TU_BIN8(db3)<<8) \
            + TU_BIN8(dlsb))
#endif

#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_COMMON_H_ */
