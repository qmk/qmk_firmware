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

/** \ingroup Group_Common
 *  \defgroup Group_Compiler Compiler
 *  \brief Group_Compiler brief
 *  @{ */

#ifndef _TUSB_COMPILER_H_
#define _TUSB_COMPILER_H_

#define TU_TOKEN(x)           x
#define TU_STRING(x)          #x                  ///< stringify without expand
#define TU_XSTRING(x)         TU_STRING(x)        ///< expand then stringify

#define TU_STRCAT(a, b)       a##b                ///< concat without expand
#define TU_STRCAT3(a, b, c)   a##b##c             ///< concat without expand

#define TU_XSTRCAT(a, b)      TU_STRCAT(a, b)     ///< expand then concat
#define TU_XSTRCAT3(a, b, c)  TU_STRCAT3(a, b, c) ///< expand then concat 3 tokens

#define TU_INCLUDE_PATH(_dir,_file) TU_XSTRING( TU_TOKEN(_dir)TU_TOKEN(_file) )

#if defined __COUNTER__ && __COUNTER__ != __COUNTER__
  #define _TU_COUNTER_ __COUNTER__
#else
  #define _TU_COUNTER_ __LINE__
#endif

// Compile-time Assert
#if defined (__cplusplus) && __cplusplus >= 201103L
  #define TU_VERIFY_STATIC   static_assert
#elif defined (__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
  #define TU_VERIFY_STATIC   _Static_assert
#elif defined(__CCRX__)
  #define TU_VERIFY_STATIC(const_expr, _mess) typedef char TU_XSTRCAT(Line, __LINE__)[(const_expr) ? 1 : 0];
#else
  #define TU_VERIFY_STATIC(const_expr, _mess) enum { TU_XSTRCAT(_verify_static_, _TU_COUNTER_) = 1/(!!(const_expr)) }
#endif

/* --------------------- Fuzzing types -------------------------------------- */
#ifdef _FUZZ
  #define tu_static static __thread
#else
  #define tu_static static
#endif

// for declaration of reserved field, make use of _TU_COUNTER_
#define TU_RESERVED           TU_XSTRCAT(reserved, _TU_COUNTER_)

#define TU_LITTLE_ENDIAN (0x12u)
#define TU_BIG_ENDIAN (0x21u)

/*------------------------------------------------------------------*/
/* Count number of arguments of __VA_ARGS__
 * - reference https://stackoverflow.com/questions/2124339/c-preprocessor-va-args-number-of-arguments
 * - _GET_NTH_ARG() takes args >= N (64) but only expand to Nth one (64th)
 * - _RSEQ_N() is reverse sequential to N to add padding to have
 * Nth position is the same as the number of arguments
 * - ##__VA_ARGS__ is used to deal with 0 paramerter (swallows comma)
 *------------------------------------------------------------------*/
#if !defined(__CCRX__)
#define TU_ARGS_NUM(...)   _TU_NARG(_0, ##__VA_ARGS__, _RSEQ_N())
#else
#define TU_ARGS_NUM(...)   _TU_NARG(_0, __VA_ARGS__, _RSEQ_N())
#endif

#define _TU_NARG(...)      _GET_NTH_ARG(__VA_ARGS__)
#define _GET_NTH_ARG( \
          _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
         _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
         _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
         _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
         _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
         _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
         _61,_62,_63,N,...) N
#define _RSEQ_N() \
         62,61,60,                      \
         59,58,57,56,55,54,53,52,51,50, \
         49,48,47,46,45,44,43,42,41,40, \
         39,38,37,36,35,34,33,32,31,30, \
         29,28,27,26,25,24,23,22,21,20, \
         19,18,17,16,15,14,13,12,11,10, \
         9,8,7,6,5,4,3,2,1,0

// Apply an macro X to each of the arguments with an separated of choice
#define TU_ARGS_APPLY(_X, _s, ...)   TU_XSTRCAT(_TU_ARGS_APPLY_, TU_ARGS_NUM(__VA_ARGS__))(_X, _s, __VA_ARGS__)

#define _TU_ARGS_APPLY_1(_X, _s, _a1)                                    _X(_a1)
#define _TU_ARGS_APPLY_2(_X, _s, _a1, _a2)                               _X(_a1) _s _X(_a2)
#define _TU_ARGS_APPLY_3(_X, _s, _a1, _a2, _a3)                          _X(_a1) _s _TU_ARGS_APPLY_2(_X, _s, _a2, _a3)
#define _TU_ARGS_APPLY_4(_X, _s, _a1, _a2, _a3, _a4)                     _X(_a1) _s _TU_ARGS_APPLY_3(_X, _s, _a2, _a3, _a4)
#define _TU_ARGS_APPLY_5(_X, _s, _a1, _a2, _a3, _a4, _a5)                _X(_a1) _s _TU_ARGS_APPLY_4(_X, _s, _a2, _a3, _a4, _a5)
#define _TU_ARGS_APPLY_6(_X, _s, _a1, _a2, _a3, _a4, _a5, _a6)           _X(_a1) _s _TU_ARGS_APPLY_5(_X, _s, _a2, _a3, _a4, _a5, _a6)
#define _TU_ARGS_APPLY_7(_X, _s, _a1, _a2, _a3, _a4, _a5, _a6, _a7)      _X(_a1) _s _TU_ARGS_APPLY_6(_X, _s, _a2, _a3, _a4, _a5, _a6, _a7)
#define _TU_ARGS_APPLY_8(_X, _s, _a1, _a2, _a3, _a4, _a5, _a6, _a7, _a8) _X(_a1) _s _TU_ARGS_APPLY_7(_X, _s, _a2, _a3, _a4, _a5, _a6, _a7, _a8)

//--------------------------------------------------------------------+
// Compiler porting with Attribute and Endian
//--------------------------------------------------------------------+

// TODO refactor since __attribute__ is supported across many compiler
#if defined(__GNUC__)
  #define TU_ATTR_ALIGNED(Bytes)        __attribute__ ((aligned(Bytes)))
  #define TU_ATTR_SECTION(sec_name)     __attribute__ ((section(#sec_name)))
  #define TU_ATTR_PACKED                __attribute__ ((packed))
  #define TU_ATTR_WEAK                  __attribute__ ((weak))
  #define TU_ATTR_ALWAYS_INLINE         __attribute__ ((always_inline))
  #define TU_ATTR_DEPRECATED(mess)      __attribute__ ((deprecated(mess))) // warn if function with this attribute is used
  #define TU_ATTR_UNUSED                __attribute__ ((unused))           // Function/Variable is meant to be possibly unused
  #define TU_ATTR_USED                  __attribute__ ((used))             // Function/Variable is meant to be used

  #define TU_ATTR_PACKED_BEGIN
  #define TU_ATTR_PACKED_END
  #define TU_ATTR_BIT_FIELD_ORDER_BEGIN
  #define TU_ATTR_BIT_FIELD_ORDER_END

  #if __has_attribute(__fallthrough__)
    #define TU_ATTR_FALLTHROUGH         __attribute__((fallthrough))
  #else
    #define TU_ATTR_FALLTHROUGH         do {} while (0)  /* fallthrough */
  #endif

  // Endian conversion use well-known host to network (big endian) naming
  #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    #define TU_BYTE_ORDER TU_LITTLE_ENDIAN
  #else
    #define TU_BYTE_ORDER TU_BIG_ENDIAN
  #endif

  #define TU_BSWAP16(u16) (__builtin_bswap16(u16))
  #define TU_BSWAP32(u32) (__builtin_bswap32(u32))

	#ifndef __ARMCC_VERSION
  // List of obsolete callback function that is renamed and should not be defined.
  // Put it here since only gcc support this pragma
		#pragma GCC poison tud_vendor_control_request_cb
	#endif

#elif defined(__TI_COMPILER_VERSION__)
  #define TU_ATTR_ALIGNED(Bytes)        __attribute__ ((aligned(Bytes)))
  #define TU_ATTR_SECTION(sec_name)     __attribute__ ((section(#sec_name)))
  #define TU_ATTR_PACKED                __attribute__ ((packed))
  #define TU_ATTR_WEAK                  __attribute__ ((weak))
  #define TU_ATTR_ALWAYS_INLINE         __attribute__ ((always_inline))
  #define TU_ATTR_DEPRECATED(mess)      __attribute__ ((deprecated(mess))) // warn if function with this attribute is used
  #define TU_ATTR_UNUSED                __attribute__ ((unused))           // Function/Variable is meant to be possibly unused
  #define TU_ATTR_USED                  __attribute__ ((used))
  #define TU_ATTR_FALLTHROUGH           __attribute__((fallthrough))

  #define TU_ATTR_PACKED_BEGIN
  #define TU_ATTR_PACKED_END
  #define TU_ATTR_BIT_FIELD_ORDER_BEGIN
  #define TU_ATTR_BIT_FIELD_ORDER_END

  // __BYTE_ORDER is defined in the TI ARM compiler, but not MSP430 (which is little endian)
  #if ((__BYTE_ORDER__) == (__ORDER_LITTLE_ENDIAN__)) || defined(__MSP430__)
    #define TU_BYTE_ORDER TU_LITTLE_ENDIAN
  #else
    #define TU_BYTE_ORDER TU_BIG_ENDIAN
  #endif

  #define TU_BSWAP16(u16) (__builtin_bswap16(u16))
  #define TU_BSWAP32(u32) (__builtin_bswap32(u32))

#elif defined(__ICCARM__)
  #include <intrinsics.h>
  #define TU_ATTR_ALIGNED(Bytes)        __attribute__ ((aligned(Bytes)))
  #define TU_ATTR_SECTION(sec_name)     __attribute__ ((section(#sec_name)))
  #define TU_ATTR_PACKED                __attribute__ ((packed))
  #define TU_ATTR_WEAK                  __attribute__ ((weak))
  #define TU_ATTR_ALWAYS_INLINE         __attribute__ ((always_inline))
  #define TU_ATTR_DEPRECATED(mess)      __attribute__ ((deprecated(mess))) // warn if function with this attribute is used
  #define TU_ATTR_UNUSED                __attribute__ ((unused))           // Function/Variable is meant to be possibly unused
  #define TU_ATTR_USED                  __attribute__ ((used))             // Function/Variable is meant to be used
  #define TU_ATTR_FALLTHROUGH           __attribute__((fallthrough))

  #define TU_ATTR_PACKED_BEGIN
  #define TU_ATTR_PACKED_END
  #define TU_ATTR_BIT_FIELD_ORDER_BEGIN
  #define TU_ATTR_BIT_FIELD_ORDER_END

  // Endian conversion use well-known host to network (big endian) naming
  #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    #define TU_BYTE_ORDER TU_LITTLE_ENDIAN
  #else
    #define TU_BYTE_ORDER TU_BIG_ENDIAN
  #endif

  #define TU_BSWAP16(u16) (__iar_builtin_REV16(u16))
  #define TU_BSWAP32(u32) (__iar_builtin_REV(u32))

#elif defined(__CCRX__)
  #define TU_ATTR_ALIGNED(Bytes)
  #define TU_ATTR_SECTION(sec_name)
  #define TU_ATTR_PACKED
  #define TU_ATTR_WEAK
  #define TU_ATTR_ALWAYS_INLINE
  #define TU_ATTR_DEPRECATED(mess)
  #define TU_ATTR_UNUSED
  #define TU_ATTR_USED
  #define TU_ATTR_FALLTHROUGH           do {} while (0)  /* fallthrough */

  #define TU_ATTR_PACKED_BEGIN          _Pragma("pack")
  #define TU_ATTR_PACKED_END            _Pragma("packoption")
  #define TU_ATTR_BIT_FIELD_ORDER_BEGIN _Pragma("bit_order right")
  #define TU_ATTR_BIT_FIELD_ORDER_END   _Pragma("bit_order")

  // Endian conversion use well-known host to network (big endian) naming
  #if defined(__LIT)
    #define TU_BYTE_ORDER TU_LITTLE_ENDIAN
  #else
    #define TU_BYTE_ORDER TU_BIG_ENDIAN
  #endif

  #define TU_BSWAP16(u16) ((unsigned short)_builtin_revw((unsigned long)u16))
  #define TU_BSWAP32(u32) (_builtin_revl(u32))

#else 
  #error "Compiler attribute porting is required"
#endif


#if (TU_BYTE_ORDER == TU_LITTLE_ENDIAN)

  #define tu_htons(u16)  (TU_BSWAP16(u16))
  #define tu_ntohs(u16)  (TU_BSWAP16(u16))

  #define tu_htonl(u32)  (TU_BSWAP32(u32))
  #define tu_ntohl(u32)  (TU_BSWAP32(u32))

  #define tu_htole16(u16) (u16)
  #define tu_le16toh(u16) (u16)

  #define tu_htole32(u32) (u32)
  #define tu_le32toh(u32) (u32)

#elif (TU_BYTE_ORDER == TU_BIG_ENDIAN)

  #define tu_htons(u16)  (u16)
  #define tu_ntohs(u16)  (u16)

  #define tu_htonl(u32)  (u32)
  #define tu_ntohl(u32)  (u32)

  #define tu_htole16(u16) (TU_BSWAP16(u16))
  #define tu_le16toh(u16) (TU_BSWAP16(u16))

  #define tu_htole32(u32) (TU_BSWAP32(u32))
  #define tu_le32toh(u32) (TU_BSWAP32(u32))

#else
  #error Byte order is undefined
#endif

#endif /* _TUSB_COMPILER_H_ */

/// @}
