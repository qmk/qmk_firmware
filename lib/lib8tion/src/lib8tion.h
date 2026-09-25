#ifndef __INC_LIB8TION_H
#define __INC_LIB8TION_H

#include "lib8tion/types.h"

/// @file lib8tion.h
/// Fast, efficient 8-bit math functions specifically
/// designed for high-performance LED programming. 


#include <stdint.h>

#define LIB8STATIC static inline
#define LIB8STATIC_ALWAYS_INLINE static inline

#if !defined(__AVR__)
#include <string.h>
// for memmove, memcpy, and memset if not defined here
#endif // end of !defined(__AVR__)

#if defined(__arm__)

#if defined(FASTLED_TEENSY3)
// Can use Cortex M4 DSP instructions
#define QADD8_C 0
#define QADD7_C 0
#define QADD8_ARM_DSP_ASM 1
#define QADD7_ARM_DSP_ASM 1
#else
// Generic ARM
#define QADD8_C 1
#define QADD7_C 1
#endif // end of defined(FASTLED_TEENSY3)

#define QSUB8_C 1
#define SCALE8_C 1
#define SCALE16BY8_C 1
#define SCALE16_C 1
#define ABS8_C 1
#define MUL8_C 1
#define QMUL8_C 1
#define ADD8_C 1
#define SUB8_C 1
#define EASE8_C 1
#define AVG8_C 1
#define AVG8R_C 1
#define AVG7_C 1
#define AVG16_C 1
#define AVG16R_C 1
#define AVG15_C 1
#define BLEND8_C 1

// end of #if defined(__arm__)

#elif defined(ARDUINO_ARCH_APOLLO3)

// Default to using the standard C functions for now
#define QADD8_C 1
#define QADD7_C 1
#define QSUB8_C 1
#define SCALE8_C 1
#define SCALE16BY8_C 1
#define SCALE16_C 1
#define ABS8_C 1
#define MUL8_C 1
#define QMUL8_C 1
#define ADD8_C 1
#define SUB8_C 1
#define EASE8_C 1
#define AVG8_C 1
#define AVG8R_C 1
#define AVG7_C 1
#define AVG16_C 1
#define AVG16R_C 1
#define AVG15_C 1
#define BLEND8_C 1

// end of #elif defined(ARDUINO_ARCH_APOLLO3)

#elif defined(__AVR__)

// AVR ATmega and friends Arduino

#define QADD8_C 0
#define QADD7_C 0
#define QSUB8_C 0
#define ABS8_C 0
#define ADD8_C 0
#define SUB8_C 0
#define AVG8_C 0
#define AVG8R_C 0
#define AVG7_C 0
#define AVG16_C 0
#define AVG16R_C 0
#define AVG15_C 0

#define QADD8_AVRASM 1
#define QADD7_AVRASM 1
#define QSUB8_AVRASM 1
#define ABS8_AVRASM 1
#define ADD8_AVRASM 1
#define SUB8_AVRASM 1
#define AVG8_AVRASM 1
#define AVG8R_AVRASM 1
#define AVG7_AVRASM 1
#define AVG16_AVRASM 1
#define AVG16R_AVRASM 1
#define AVG15_AVRASM 1

// Note: these require hardware MUL instruction
//       -- sorry, ATtiny!
#if !defined(LIB8_ATTINY)
#define SCALE8_C 0
#define SCALE16BY8_C 0
#define SCALE16_C 0
#define MUL8_C 0
#define QMUL8_C 0
#define EASE8_C 0
#define BLEND8_C 0
#define SCALE8_AVRASM 1
#define SCALE16BY8_AVRASM 1
#define SCALE16_AVRASM 1
#define MUL8_AVRASM 1
#define QMUL8_AVRASM 1
#define EASE8_AVRASM 1
#define CLEANUP_R1_AVRASM 1
#define BLEND8_AVRASM 1
#else
// On ATtiny, we just use C implementations
#define SCALE8_C 1
#define SCALE16BY8_C 1
#define SCALE16_C 1
#define MUL8_C 1
#define QMUL8_C 1
#define EASE8_C 1
#define BLEND8_C 1
#define SCALE8_AVRASM 0
#define SCALE16BY8_AVRASM 0
#define SCALE16_AVRASM 0
#define MUL8_AVRASM 0
#define QMUL8_AVRASM 0
#define EASE8_AVRASM 0
#define BLEND8_AVRASM 0
#endif // end of !defined(LIB8_ATTINY)

// end of #elif defined(__AVR__)

#else

// Doxygen: ignore these macros
/// @cond

// unspecified architecture, so
// no ASM, everything in C
#define QADD8_C 1
#define QADD7_C 1
#define QSUB8_C 1
#define SCALE8_C 1
#define SCALE16BY8_C 1
#define SCALE16_C 1
#define ABS8_C 1
#define MUL8_C 1
#define QMUL8_C 1
#define ADD8_C 1
#define SUB8_C 1
#define EASE8_C 1
#define AVG8_C 1
#define AVG8R_C 1
#define AVG7_C 1
#define AVG16_C 1
#define AVG16R_C 1
#define AVG15_C 1
#define BLEND8_C 1

/// @endcond

#endif

/// @defgroup lib8tion Fast Math Functions
/// Fast, efficient 8-bit math functions specifically
/// designed for high-performance LED programming. 
///
/// Because of the AVR (Arduino) and ARM assembly language
/// implementations provided, using these functions often
/// results in smaller and faster code than the equivalent
/// program using plain "C" arithmetic and logic.
///
/// Included are:
///
///  - Saturating unsigned 8-bit add and subtract.
///    Instead of wrapping around if an overflow occurs,
///    these routines just 'clamp' the output at a maxumum
///    of 255, or a minimum of 0.  Useful for adding pixel
///    values.  E.g., qadd8( 200, 100) = 255.
///      @code
///      qadd8( i, j) == MIN( (i + j), 0xFF )
///      qsub8( i, j) == MAX( (i - j), 0 )
///      @endcode
///
///  - Saturating signed 8-bit ("7-bit") add.
///      @code
///      qadd7( i, j) == MIN( (i + j), 0x7F)
///      @endcode
///
///  - Scaling (down) of unsigned 8- and 16- bit values.
///    Scaledown value is specified in 1/256ths.
///      @code
///      scale8( i, sc) == (i * sc) / 256
///      scale16by8( i, sc) == (i * sc) / 256
///      @endcode
///
///    Example: scaling a 0-255 value down into a
///    range from 0-99:
///      @code
///      downscaled = scale8( originalnumber, 100);
///      @endcode
///
///    A special version of scale8 is provided for scaling
///    LED brightness values, to make sure that they don't
///    accidentally scale down to total black at low
///    dimming levels, since that would look wrong:
///      @code
///      scale8_video( i, sc) = ((i * sc) / 256) +? 1
///      @endcode
///
///    Example: reducing an LED brightness by a
///    dimming factor:
///      @code
///      new_bright = scale8_video( orig_bright, dimming);
///      @endcode
///
///  - Fast 8- and 16- bit unsigned random numbers.
///    Significantly faster than Arduino random(), but
///    also somewhat less random.  You can add entropy.
///      @code
///      random8()       == random from 0..255
///      random8( n)     == random from 0..(N-1)
///      random8( n, m)  == random from N..(M-1)
///
///      random16()      == random from 0..65535
///      random16( n)    == random from 0..(N-1)
///      random16( n, m) == random from N..(M-1)
///
///      random16_set_seed( k)    ==  seed = k
///      random16_add_entropy( k) ==  seed += k
///      @endcode
///
///  - Absolute value of a signed 8-bit value.
///      @code
///      abs8( i)     == abs( i)
///      @endcode
///
///  - 8-bit math operations which return 8-bit values.
///    These are provided mostly for completeness,
///    not particularly for performance.
///      @code
///      mul8( i, j)  == (i * j) & 0xFF
///      add8( i, j)  == (i + j) & 0xFF
///      sub8( i, j)  == (i - j) & 0xFF
///      @endcode
///
///  - Fast 16-bit approximations of sin and cos.
///    Input angle is a uint16_t from 0-65535.
///    Output is a signed int16_t from -32767 to 32767.
///      @code
///      sin16( x)  == sin( (x/32768.0) * pi) * 32767
///      cos16( x)  == cos( (x/32768.0) * pi) * 32767
///      @endcode
///
///    Accurate to more than 99% in all cases.
///
///  - Fast 8-bit approximations of sin and cos.
///    Input angle is a uint8_t from 0-255.
///    Output is an UNsigned uint8_t from 0 to 255.
///      @code
///      sin8( x)  == (sin( (x/128.0) * pi) * 128) + 128
///      cos8( x)  == (cos( (x/128.0) * pi) * 128) + 128
///      @endcode
///
///    Accurate to within about 2%.
///
///  - Fast 8-bit "easing in/out" function.
///      @code
///      ease8InOutCubic(x) == 3(x^2) - 2(x^3)
///      ease8InOutApprox(x) ==
///        faster, rougher, approximation of cubic easing
///      ease8InOutQuad(x) == quadratic (vs cubic) easing
///      @endcode
///
///  - Cubic, Quadratic, and Triangle wave functions.
///    Input is a uint8_t representing phase withing the wave,
///      similar to how sin8 takes an angle 'theta'.
///    Output is a uint8_t representing the amplitude of
///    the wave at that point.
///      @code
///      cubicwave8( x)
///      quadwave8( x)
///      triwave8( x)
///      @endcode
///
///  - Square root for 16-bit integers.  About three times
///    faster and five times smaller than Arduino's built-in
///    generic 32-bit sqrt routine.
///      @code
///      sqrt16( uint16_t x ) == sqrt( x)
///      @endcode
///
///  - Dimming and brightening functions for 8-bit
///    light values.
///      @code
///      dim8_video( x)  == scale8_video( x, x)
///      dim8_raw( x)    == scale8( x, x)
///      dim8_lin( x)    == (x<128) ? ((x+1)/2) : scale8(x,x)
///      brighten8_video( x) == 255 - dim8_video( 255 - x)
///      brighten8_raw( x) == 255 - dim8_raw( 255 - x)
///      brighten8_lin( x) == 255 - dim8_lin( 255 - x)
///      @endcode
///
///    The dimming functions in particular are suitable
///    for making LED light output appear more 'linear'.
///
///  - Linear interpolation between two values, with the
///    fraction between them expressed as an 8- or 16-bit
///    fixed point fraction (fract8 or fract16).
///      @code
///      lerp8by8(   fromU8, toU8, fract8 )
///      lerp16by8(  fromU16, toU16, fract8 )
///      lerp15by8(  fromS16, toS16, fract8 )
///        == from + (( to - from ) * fract8) / 256)
///      lerp16by16( fromU16, toU16, fract16 )
///        == from + (( to - from ) * fract16) / 65536)
///      map8( in, rangeStart, rangeEnd)
///        == map( in, 0, 255, rangeStart, rangeEnd);
///      @endcode
///
///  - Optimized memmove, memcpy, and memset, that are
///    faster than standard avr-libc 1.8.
///      @code
///      memmove8( dest, src,  bytecount)
///      memcpy8(  dest, src,  bytecount)
///      memset8(  buf, value, bytecount)
///      @endcode
///
///  - Beat generators which return sine or sawtooth
///    waves in a specified number of Beats Per Minute.
///    Sine wave beat generators can specify a low and
///    high range for the output.  Sawtooth wave beat
///    generators always range 0-255 or 0-65535.
///      @code
///      beatsin8( BPM, low8, high8)
///          = (sine(beatphase) * (high8-low8)) + low8
///      beatsin16( BPM, low16, high16)
///          = (sine(beatphase) * (high16-low16)) + low16
///      beatsin88( BPM88, low16, high16)
///          = (sine(beatphase) * (high16-low16)) + low16
///      beat8( BPM)  = 8-bit repeating sawtooth wave
///      beat16( BPM) = 16-bit repeating sawtooth wave
///      beat88( BPM88) = 16-bit repeating sawtooth wave
///      @endcode
///
///    BPM is beats per minute in either simple form
///    e.g. 120, or Q8.8 fixed-point form.
///    BPM88 is beats per minute in ONLY Q8.8 fixed-point
///    form.
///
/// Lib8tion is pronounced like 'libation': lie-BAY-shun
///
/// @{




#include "lib8tion/math8.h"
#include "lib8tion/scale8.h"
#include "lib8tion/random8.h"
#include "lib8tion/trig8.h"

///////////////////////////////////////////////////////////////////////







///////////////////////////////////////////////////////////////////////
///
/// @defgroup FloatConversions Float-to-Fixed and Fixed-to-Float Conversions
/// Functions to convert between floating point and fixed point types. 
/// @note Anything involving a "float" on AVR will be slower.
/// @{

/// Conversion from 16-bit fixed point (::sfract15) to IEEE754 32-bit float.
LIB8STATIC float sfract15ToFloat( sfract15 y)
{
    return y / 32768.0;
}

/// Conversion from IEEE754 float in the range (-1,1) to 16-bit fixed point (::sfract15).
/// @note The extremes of one and negative one are NOT representable! The
/// representable range is 0.99996948242 to -0.99996948242, in steps of 0.00003051757.
LIB8STATIC sfract15 floatToSfract15( float f)
{
    return f * 32768.0;
}

/// @} FloatConversions



///////////////////////////////////////////////////////////////////////
///
/// @defgroup FastMemory Fast Memory Functions for AVR
/// Alternatives to memmove, memcpy, and memset that are
/// faster on AVR than standard avr-libc 1.8. 
/// @{

#if defined(__AVR__) || defined(FASTLED_DOXYGEN)
void * memmove8( void * dst, const void * src, uint16_t num );  ///< Faster alternative to memmove() on AVR
void * memcpy8 ( void * dst, const void * src, uint16_t num )  __attribute__ ((noinline));  ///< Faster alternative to memcpy() on AVR
void * memset8 ( void * ptr, uint8_t value, uint16_t num ) __attribute__ ((noinline)) ;  ///< Faster alternative to memset() on AVR
#else
// on non-AVR platforms, these names just call standard libc.
#define memmove8 memmove
#define memcpy8 memcpy
#define memset8 memset
#endif

/// @} FastMemory


///////////////////////////////////////////////////////////////////////
///
/// @defgroup LinearInterpolation Linear Interpolation
/// Fast linear interpolation functions, such as could be used for Perlin noise, etc.
///
/// A note on the structure of the lerp functions:
/// The cases for b>a and b<=a are handled separately for
/// speed. Without knowing the relative order of a and b,
/// the value (a-b) might be overflow the width of a or b,
/// and have to be promoted to a wider, slower type.
/// To avoid that, we separate the two cases, and are able
/// to do all the math in the same width as the arguments,
/// which is much faster and smaller on AVR.
/// @{

/// Linear interpolation between two unsigned 8-bit values,
/// with 8-bit fraction
LIB8STATIC uint8_t lerp8by8( uint8_t a, uint8_t b, fract8 frac)
{
    uint8_t result;
    if( b > a) {
        uint8_t delta = b - a;
        uint8_t scaled = scale8( delta, frac);
        result = a + scaled;
    } else {
        uint8_t delta = a - b;
        uint8_t scaled = scale8( delta, frac);
        result = a - scaled;
    }
    return result;
}

/// Linear interpolation between two unsigned 16-bit values,
/// with 16-bit fraction
LIB8STATIC uint16_t lerp16by16( uint16_t a, uint16_t b, fract16 frac)
{
    uint16_t result;
    if( b > a ) {
        uint16_t delta = b - a;
        uint16_t scaled = scale16(delta, frac);
        result = a + scaled;
    } else {
        uint16_t delta = a - b;
        uint16_t scaled = scale16( delta, frac);
        result = a - scaled;
    }
    return result;
}

/// Linear interpolation between two unsigned 16-bit values,
/// with 8-bit fraction
LIB8STATIC uint16_t lerp16by8( uint16_t a, uint16_t b, fract8 frac)
{
    uint16_t result;
    if( b > a) {
        uint16_t delta = b - a;
        uint16_t scaled = scale16by8( delta, frac);
        result = a + scaled;
    } else {
        uint16_t delta = a - b;
        uint16_t scaled = scale16by8( delta, frac);
        result = a - scaled;
    }
    return result;
}

/// Linear interpolation between two signed 15-bit values,
/// with 8-bit fraction
LIB8STATIC int16_t lerp15by8( int16_t a, int16_t b, fract8 frac)
{
    int16_t result;
    if( b > a) {
        uint16_t delta = b - a;
        uint16_t scaled = scale16by8( delta, frac);
        result = a + scaled;
    } else {
        uint16_t delta = a - b;
        uint16_t scaled = scale16by8( delta, frac);
        result = a - scaled;
    }
    return result;
}

/// Linear interpolation between two signed 15-bit values,
/// with 8-bit fraction
LIB8STATIC int16_t lerp15by16( int16_t a, int16_t b, fract16 frac)
{
    int16_t result;
    if( b > a) {
        uint16_t delta = b - a;
        uint16_t scaled = scale16( delta, frac);
        result = a + scaled;
    } else {
        uint16_t delta = a - b;
        uint16_t scaled = scale16( delta, frac);
        result = a - scaled;
    }
    return result;
}

/// Map from one full-range 8-bit value into a narrower
/// range of 8-bit values, possibly a range of hues.
///
/// E.g. map `myValue` into a hue in the range blue..purple..pink..red
///   @code
///   hue = map8( myValue, HUE_BLUE, HUE_RED);
///   @endcode
///
/// Combines nicely with the waveform functions (like sin8(), etc)
/// to produce continuous hue gradients back and forth:
///   @code
///   hue = map8( sin8( myValue), HUE_BLUE, HUE_RED);
///   @endcode
///
/// Mathematically simiar to lerp8by8(), but arguments are more
/// like Arduino's "map"; this function is similar to
///   @code
///   map( in, 0, 255, rangeStart, rangeEnd)
///   @endcode
///
/// but faster and specifically designed for 8-bit values.
LIB8STATIC uint8_t map8( uint8_t in, uint8_t rangeStart, uint8_t rangeEnd)
{
    uint8_t rangeWidth = rangeEnd - rangeStart;
    uint8_t out = scale8( in, rangeWidth);
    out += rangeStart;
    return out;
}

/// @} LinearInterpolation


///////////////////////////////////////////////////////////////////////
///
/// @defgroup Easing Easing Functions 
/// Specify the rate of change of a parameter over time.
/// @see http://easings.net
/// @{

/// 8-bit quadratic ease-in / ease-out function. 
/// Takes around 13 cycles on AVR.
#if (EASE8_C == 1) || defined(FASTLED_DOXYGEN)
LIB8STATIC uint8_t ease8InOutQuad( uint8_t i)
{
    uint8_t j = i;
    if( j & 0x80 ) {
        j = 255 - j;
    }
    uint8_t jj  = scale8(  j, j);
    uint8_t jj2 = jj << 1;
    if( i & 0x80 ) {
        jj2 = 255 - jj2;
    }
    return jj2;
}

#elif EASE8_AVRASM == 1
// This AVR asm version of ease8InOutQuad preserves one more
// low-bit of precision than the C version, and is also slightly
// smaller and faster.
LIB8STATIC uint8_t ease8InOutQuad(uint8_t val) {
    uint8_t j=val;
    asm volatile (
      "sbrc %[val], 7 \n"
      "com %[j]       \n"
      "mul %[j], %[j] \n"
      "add r0, %[j]   \n"
      "ldi %[j], 0    \n"
      "adc %[j], r1   \n"
      "lsl r0         \n" // carry = high bit of low byte of mul product
      "rol %[j]       \n" // j = (j * 2) + carry // preserve add'l bit of precision
      "sbrc %[val], 7 \n"
      "com %[j]       \n"
      "clr __zero_reg__   \n"
      : [j] "+&a" (j)
      : [val] "a" (val)
      : "r0", "r1"
      );
    return j;
}

#else
#error "No implementation for ease8InOutQuad available."
#endif

/// 16-bit quadratic ease-in / ease-out function. 
/// C implementation at this point.
LIB8STATIC uint16_t ease16InOutQuad( uint16_t i)
{
    uint16_t j = i;
    if( j & 0x8000 ) {
        j = 65535 - j;
    }
    uint16_t jj  = scale16( j, j);
    uint16_t jj2 = jj << 1;
    if( i & 0x8000 ) {
        jj2 = 65535 - jj2;
    }
    return jj2;
}


/// 8-bit cubic ease-in / ease-out function. 
/// Takes around 18 cycles on AVR.
LIB8STATIC fract8 ease8InOutCubic( fract8 i)
{
    uint8_t ii  = scale8_LEAVING_R1_DIRTY(  i, i);
    uint8_t iii = scale8_LEAVING_R1_DIRTY( ii, i);

    uint16_t r1 = (3 * (uint16_t)(ii)) - ( 2 * (uint16_t)(iii));

    /* the code generated for the above *'s automatically
       cleans up R1, so there's no need to explicitily call
       cleanup_R1(); */

    uint8_t result = r1;

    // if we got "256", return 255:
    if( r1 & 0x100 ) {
        result = 255;
    }
    return result;
}


/// Fast, rough 8-bit ease-in/ease-out function. 
/// Shaped approximately like ease8InOutCubic(),
/// it's never off by more than a couple of percent
/// from the actual cubic S-curve, and it executes
/// more than twice as fast.  Use when the cycles
/// are more important than visual smoothness.
/// Asm version takes around 7 cycles on AVR.
#if (EASE8_C == 1) || defined(FASTLED_DOXYGEN)
LIB8STATIC fract8 ease8InOutApprox( fract8 i)
{
    if( i < 64) {
        // start with slope 0.5
        i /= 2;
    } else if( i > (255 - 64)) {
        // end with slope 0.5
        i = 255 - i;
        i /= 2;
        i = 255 - i;
    } else {
        // in the middle, use slope 192/128 = 1.5
        i -= 64;
        i += (i / 2);
        i += 32;
    }

    return i;
}

#elif EASE8_AVRASM == 1
LIB8STATIC uint8_t ease8InOutApprox( fract8 i)
{
    // takes around 7 cycles on AVR
    asm volatile (
        "  subi %[i], 64         \n\t"
        "  cpi  %[i], 128        \n\t"
        "  brcc Lshift_%=        \n\t"

        // middle case
        "  mov __tmp_reg__, %[i] \n\t"
        "  lsr __tmp_reg__       \n\t"
        "  add %[i], __tmp_reg__ \n\t"
        "  subi %[i], 224        \n\t"
        "  rjmp Ldone_%=         \n\t"

        // start or end case
        "Lshift_%=:              \n\t"
        "  lsr %[i]              \n\t"
        "  subi %[i], 96         \n\t"

        "Ldone_%=:               \n\t"

        : [i] "+a" (i)
        :
        : "r0"
        );
    return i;
}
#else
#error "No implementation for ease8 available."
#endif

/// @} Easing


///////////////////////////////////////////////////////////////////////
///
/// @defgroup WaveformGenerators Waveform Generators
/// General purpose wave generator functions.
///
/// @{


/// Triangle wave generator. 
/// Useful for turning a one-byte ever-increasing value into a
/// one-byte value that oscillates up and down.
///   @code
///           input         output
///           0..127        0..254 (positive slope)
///           128..255      254..0 (negative slope)
///   @endcode
///
/// On AVR this function takes just three cycles.
///
LIB8STATIC uint8_t triwave8(uint8_t in)
{
    if( in & 0x80) {
        in = 255 - in;
    }
    uint8_t out = in << 1;
    return out;
}

/// Quadratic waveform generator. Spends just a little
/// more time at the limits than "sine" does. 
///
/// S-shaped wave generator (like "sine"). Useful 
/// for turning a one-byte "counter" value into a
/// one-byte oscillating value that moves smoothly up and down,
/// with an "acceleration" and "deceleration" curve.
///
/// This is even faster than "sin8()", and has
/// a slightly different curve shape.
LIB8STATIC uint8_t quadwave8(uint8_t in)
{
    return ease8InOutQuad( triwave8( in));
}

/// Cubic waveform generator. Spends visibly more time
/// at the limits than "sine" does. 
/// @copydetails quadwave8()
LIB8STATIC uint8_t cubicwave8(uint8_t in)
{
    return ease8InOutCubic( triwave8( in));
}


/// Square wave generator.
/// Useful for turning a one-byte ever-increasing value
/// into a one-byte value that is either 0 or 255.
/// The width of the output "pulse" is determined by
/// the pulsewidth argument:
///   @code
///   if pulsewidth is 255, output is always 255.
///   if pulsewidth < 255, then
///     if input < pulsewidth  then output is 255
///     if input >= pulsewidth then output is 0
///   @endcode
///
/// The output looking like:
///
///   @code
///     255   +--pulsewidth--+
///      .    |              |
///      0    0              +--------(256-pulsewidth)--------
///   @endcode
///
/// @param in input value
/// @param pulsewidth width of the output pulse
/// @returns square wave output
LIB8STATIC uint8_t squarewave8( uint8_t in, uint8_t pulsewidth)
{
    if( in < pulsewidth || (pulsewidth == 255)) {
        return 255;
    } else {
        return 0;
    }
}

/// @} WaveformGenerators

#endif
