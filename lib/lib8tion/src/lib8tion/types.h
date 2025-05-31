#pragma once

#include <stdint.h>
#include "namespace.h"

FASTLED_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////
///
/// @defgroup FractionalTypes Fixed-Point Fractional Types. 
/// Types for storing fractional data. 
///
/// * ::sfract7 should be interpreted as signed 128ths.
/// * ::fract8 should be interpreted as unsigned 256ths.
/// * ::sfract15 should be interpreted as signed 32768ths.
/// * ::fract16 should be interpreted as unsigned 65536ths.
///
/// Example: if a fract8 has the value "64", that should be interpreted
///          as 64/256ths, or one-quarter.
///
/// accumXY types should be interpreted as X bits of integer,
///         and Y bits of fraction.  
/// E.g., ::accum88 has 8 bits of int, 8 bits of fraction
///
/// @{

/// ANSI: unsigned short _Fract. 
/// Range is 0 to 0.99609375 in steps of 0.00390625.  
/// Should be interpreted as unsigned 256ths.
typedef uint8_t   fract8;

/// ANSI: signed short _Fract. 
/// Range is -0.9921875 to 0.9921875 in steps of 0.0078125.  
/// Should be interpreted as signed 128ths.
typedef int8_t    sfract7;

/// ANSI: unsigned _Fract.
/// Range is 0 to 0.99998474121 in steps of 0.00001525878.  
/// Should be interpreted as unsigned 65536ths.
typedef uint16_t  fract16;

/// ANSI: signed _Fract.
/// Range is -0.99996948242 to 0.99996948242 in steps of 0.00003051757.  
/// Should be interpreted as signed 32768ths.
typedef int16_t   sfract15;


typedef uint16_t  accum88;    ///< ANSI: unsigned short _Accum. 8 bits int, 8 bits fraction
typedef int16_t   saccum78;   ///< ANSI: signed   short _Accum. 7 bits int, 8 bits fraction
typedef uint32_t  accum1616;  ///< ANSI: signed         _Accum. 16 bits int, 16 bits fraction
typedef int32_t   saccum1516; ///< ANSI: signed         _Accum. 15 bits int, 16 bits fraction
typedef uint16_t  accum124;   ///< no direct ANSI counterpart. 12 bits int, 4 bits fraction
typedef int32_t   saccum114;  ///< no direct ANSI counterpart. 1 bit int, 14 bits fraction


/// typedef for IEEE754 "binary32" float type internals
/// @see https://en.wikipedia.org/wiki/IEEE_754
typedef union {
    uint32_t i;  ///< raw value, as an integer
    float    f;  ///< raw value, as a float
    struct {
        uint32_t mantissa: 23;  ///< 23-bit mantissa
        uint32_t exponent:  8;  ///< 8-bit exponent
        uint32_t signbit:   1;  ///< sign bit
    };
    struct {
        uint32_t mant7 :  7;  ///< @todo Doc: what is this for?
        uint32_t mant16: 16;  ///< @todo Doc: what is this for?
        uint32_t exp_  :  8;  ///< @todo Doc: what is this for?
        uint32_t sb_   :  1;  ///< @todo Doc: what is this for?
    };
    struct {
        uint32_t mant_lo8 : 8;  ///< @todo Doc: what is this for?
        uint32_t mant_hi16_exp_lo1 : 16;  ///< @todo Doc: what is this for?
        uint32_t sb_exphi7 : 8;  ///< @todo Doc: what is this for?
    };
} IEEE754binary32_t;

/// @} FractionalTypes

FASTLED_NAMESPACE_END
