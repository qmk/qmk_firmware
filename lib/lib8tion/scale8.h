#ifndef __INC_LIB8TION_SCALE_H
#define __INC_LIB8TION_SCALE_H

///@ingroup lib8tion

///@defgroup Scaling Scaling functions
/// Fast, efficient 8-bit scaling functions specifically
/// designed for high-performance LED programming.
///
/// Because of the AVR(Arduino) and ARM assembly language
/// implementations provided, using these functions often
/// results in smaller and faster code than the equivalent
/// program using plain "C" arithmetic and logic.
///@{

///  scale one byte by a second one, which is treated as
///  the numerator of a fraction whose denominator is 256
///  In other words, it computes i * (scale / 256)
///  4 clocks AVR with MUL, 2 clocks ARM
LIB8STATIC_ALWAYS_INLINE uint8_t scale8( uint8_t i, fract8 scale)
{
#if SCALE8_C == 1
#if (FASTLED_SCALE8_FIXED == 1)
    return (((uint16_t)i) * (1+(uint16_t)(scale))) >> 8;
#else
    return ((uint16_t)i * (uint16_t)(scale) ) >> 8;
#endif
#elif SCALE8_AVRASM == 1
#if defined(LIB8_ATTINY)
#if (FASTLED_SCALE8_FIXED == 1)
    uint8_t work=i;
#else
    uint8_t work=0;
#endif
    uint8_t cnt=0x80;
    asm volatile(
#if (FASTLED_SCALE8_FIXED == 1)
        "  inc %[scale]                 \n\t"
        "  breq DONE_%=                 \n\t"
        "  clr %[work]                  \n\t"
#endif
        "LOOP_%=:                       \n\t"
        /*"  sbrc %[scale], 0             \n\t"
        "  add %[work], %[i]            \n\t"
        "  ror %[work]                  \n\t"
        "  lsr %[scale]                 \n\t"
        "  clc                          \n\t"*/
        "  sbrc %[scale], 0             \n\t"
        "  add %[work], %[i]            \n\t"
        "  ror %[work]                  \n\t"
        "  lsr %[scale]                 \n\t"
        "  lsr %[cnt]                   \n\t"
        "brcc LOOP_%=                   \n\t"
        "DONE_%=:                       \n\t"
        : [work] "+r" (work), [cnt] "+r" (cnt)
        : [scale] "r" (scale), [i] "r" (i)
        :
      );
    return work;
#else
    asm volatile(
#if (FASTLED_SCALE8_FIXED==1)
        // Multiply 8-bit i * 8-bit scale, giving 16-bit r1,r0
        "mul %0, %1          \n\t"
        // Add i to r0, possibly setting the carry flag
        "add r0, %0         \n\t"
        // load the immediate 0 into i (note, this does _not_ touch any flags)
        "ldi %0, 0x00       \n\t"
        // walk and chew gum at the same time
        "adc %0, r1          \n\t"
#else
         /* Multiply 8-bit i * 8-bit scale, giving 16-bit r1,r0 */
         "mul %0, %1          \n\t"
         /* Move the high 8-bits of the product (r1) back to i */
         "mov %0, r1          \n\t"
         /* Restore r1 to "0"; it's expected to always be that */
#endif
         "clr __zero_reg__    \n\t"

         : "+a" (i)      /* writes to i */
         : "a"  (scale)  /* uses scale */
         : "r0", "r1"    /* clobbers r0, r1 */ );

    /* Return the result */
    return i;
#endif
#else
#error "No implementation for scale8 available."
#endif
}


///  The "video" version of scale8 guarantees that the output will
///  be only be zero if one or both of the inputs are zero.  If both
///  inputs are non-zero, the output is guaranteed to be non-zero.
///  This makes for better 'video'/LED dimming, at the cost of
///  several additional cycles.
LIB8STATIC_ALWAYS_INLINE uint8_t scale8_video( uint8_t i, fract8 scale)
{
#if SCALE8_C == 1 || defined(LIB8_ATTINY)
    uint8_t j = (((int)i * (int)scale) >> 8) + ((i&&scale)?1:0);
    // uint8_t nonzeroscale = (scale != 0) ? 1 : 0;
    // uint8_t j = (i == 0) ? 0 : (((int)i * (int)(scale) ) >> 8) + nonzeroscale;
    return j;
#elif SCALE8_AVRASM == 1
    uint8_t j=0;
    asm volatile(
        "  tst %[i]\n\t"
        "  breq L_%=\n\t"
        "  mul %[i], %[scale]\n\t"
        "  mov %[j], r1\n\t"
        "  clr __zero_reg__\n\t"
        "  cpse %[scale], r1\n\t"
        "  subi %[j], 0xFF\n\t"
        "L_%=: \n\t"
        : [j] "+a" (j)
        : [i] "a" (i), [scale] "a" (scale)
        : "r0", "r1");

    return j;
    // uint8_t nonzeroscale = (scale != 0) ? 1 : 0;
    // asm volatile(
    //      "      tst %0           \n"
    //      "      breq L_%=        \n"
    //      "      mul %0, %1       \n"
    //      "      mov %0, r1       \n"
    //      "      add %0, %2       \n"
    //      "      clr __zero_reg__ \n"
    //      "L_%=:                  \n"

    //      : "+a" (i)
    //      : "a" (scale), "a" (nonzeroscale)
    //      : "r0", "r1");

    // // Return the result
    // return i;
#else
#error "No implementation for scale8_video available."
#endif
}


/// This version of scale8 does not clean up the R1 register on AVR
/// If you are doing several 'scale8's in a row, use this, and
/// then explicitly call cleanup_R1.
LIB8STATIC_ALWAYS_INLINE uint8_t scale8_LEAVING_R1_DIRTY( uint8_t i, fract8 scale)
{
#if SCALE8_C == 1
#if (FASTLED_SCALE8_FIXED == 1)
    return (((uint16_t)i) * ((uint16_t)(scale)+1)) >> 8;
#else
    return ((int)i * (int)(scale) ) >> 8;
#endif
#elif SCALE8_AVRASM == 1
    asm volatile(
      #if (FASTLED_SCALE8_FIXED==1)
              // Multiply 8-bit i * 8-bit scale, giving 16-bit r1,r0
              "mul %0, %1          \n\t"
              // Add i to r0, possibly setting the carry flag
              "add r0, %0         \n\t"
              // load the immediate 0 into i (note, this does _not_ touch any flags)
              "ldi %0, 0x00       \n\t"
              // walk and chew gum at the same time
              "adc %0, r1          \n\t"
      #else
         /* Multiply 8-bit i * 8-bit scale, giving 16-bit r1,r0 */
         "mul %0, %1    \n\t"
         /* Move the high 8-bits of the product (r1) back to i */
         "mov %0, r1    \n\t"
      #endif
         /* R1 IS LEFT DIRTY HERE; YOU MUST ZERO IT OUT YOURSELF  */
         /* "clr __zero_reg__    \n\t" */

         : "+a" (i)      /* writes to i */
         : "a"  (scale)  /* uses scale */
         : "r0", "r1"    /* clobbers r0, r1 */ );

    // Return the result
    return i;
#else
#error "No implementation for scale8_LEAVING_R1_DIRTY available."
#endif
}


/// This version of scale8_video does not clean up the R1 register on AVR
/// If you are doing several 'scale8_video's in a row, use this, and
/// then explicitly call cleanup_R1.
LIB8STATIC_ALWAYS_INLINE uint8_t scale8_video_LEAVING_R1_DIRTY( uint8_t i, fract8 scale)
{
#if SCALE8_C == 1 || defined(LIB8_ATTINY)
    uint8_t j = (((int)i * (int)scale) >> 8) + ((i&&scale)?1:0);
    // uint8_t nonzeroscale = (scale != 0) ? 1 : 0;
    // uint8_t j = (i == 0) ? 0 : (((int)i * (int)(scale) ) >> 8) + nonzeroscale;
    return j;
#elif SCALE8_AVRASM == 1
    uint8_t j=0;
    asm volatile(
        "  tst %[i]\n\t"
        "  breq L_%=\n\t"
        "  mul %[i], %[scale]\n\t"
        "  mov %[j], r1\n\t"
        "  breq L_%=\n\t"
        "  subi %[j], 0xFF\n\t"
        "L_%=: \n\t"
        : [j] "+a" (j)
        : [i] "a" (i), [scale] "a" (scale)
        : "r0", "r1");

    return j;
    // uint8_t nonzeroscale = (scale != 0) ? 1 : 0;
    // asm volatile(
    //      "      tst %0           \n"
    //      "      breq L_%=        \n"
    //      "      mul %0, %1       \n"
    //      "      mov %0, r1       \n"
    //      "      add %0, %2       \n"
    //      "      clr __zero_reg__ \n"
    //      "L_%=:                  \n"

    //      : "+a" (i)
    //      : "a" (scale), "a" (nonzeroscale)
    //      : "r0", "r1");

    // // Return the result
    // return i;
#else
#error "No implementation for scale8_video_LEAVING_R1_DIRTY available."
#endif
}

/// Clean up the r1 register after a series of *LEAVING_R1_DIRTY calls
LIB8STATIC_ALWAYS_INLINE void cleanup_R1(void)
{
#if CLEANUP_R1_AVRASM == 1
    // Restore r1 to "0"; it's expected to always be that
    asm volatile( "clr __zero_reg__  \n\t" : : : "r1" );
#endif
}


/// scale a 16-bit unsigned value by an 8-bit value,
///         considered as numerator of a fraction whose denominator
///         is 256. In other words, it computes i * (scale / 256)

LIB8STATIC_ALWAYS_INLINE uint16_t scale16by8( uint16_t i, fract8 scale )
{
#if SCALE16BY8_C == 1
    uint16_t result;
#if FASTLED_SCALE8_FIXED == 1
    result = (i * (1+((uint16_t)scale))) >> 8;
#else
    result = (i * scale) / 256;
#endif
    return result;
#elif SCALE16BY8_AVRASM == 1
#if FASTLED_SCALE8_FIXED == 1
    uint16_t result = 0;
    asm volatile(
                 // result.A = HighByte( (i.A x scale) + i.A )
                 "  mul %A[i], %[scale]                 \n\t"
                 "  add r0, %A[i]                       \n\t"
            //   "  adc r1, [zero]                      \n\t"
            //   "  mov %A[result], r1                  \n\t"
                 "  adc %A[result], r1                  \n\t"

                 // result.A-B += i.B x scale
                 "  mul %B[i], %[scale]                 \n\t"
                 "  add %A[result], r0                  \n\t"
                 "  adc %B[result], r1                  \n\t"

                 // cleanup r1
                 "  clr __zero_reg__                    \n\t"

                 // result.A-B += i.B
                 "  add %A[result], %B[i]               \n\t"
                 "  adc %B[result], __zero_reg__        \n\t"

                 : [result] "+r" (result)
                 : [i] "r" (i), [scale] "r" (scale)
                 : "r0", "r1"
                 );
    return result;
#else
    uint16_t result = 0;
    asm volatile(
         // result.A = HighByte(i.A x j )
         "  mul %A[i], %[scale]                 \n\t"
         "  mov %A[result], r1                  \n\t"
         //"  clr %B[result]                      \n\t"

         // result.A-B += i.B x j
         "  mul %B[i], %[scale]                 \n\t"
         "  add %A[result], r0                  \n\t"
         "  adc %B[result], r1                  \n\t"

         // cleanup r1
         "  clr __zero_reg__                    \n\t"

         : [result] "+r" (result)
         : [i] "r" (i), [scale] "r" (scale)
         : "r0", "r1"
         );
    return result;
#endif
#else
    #error "No implementation for scale16by8 available."
#endif
}

/// scale a 16-bit unsigned value by a 16-bit value,
///         considered as numerator of a fraction whose denominator
///         is 65536. In other words, it computes i * (scale / 65536)

LIB8STATIC uint16_t scale16( uint16_t i, fract16 scale )
{
  #if SCALE16_C == 1
    uint16_t result;
#if FASTLED_SCALE8_FIXED == 1
    result = ((uint32_t)(i) * (1+(uint32_t)(scale))) / 65536;
#else
    result = ((uint32_t)(i) * (uint32_t)(scale)) / 65536;
#endif
    return result;
#elif SCALE16_AVRASM == 1
#if FASTLED_SCALE8_FIXED == 1
    // implemented sort of like
    //   result = ((i * scale) + i ) / 65536
    //
    // why not like this, you may ask?
    //   result = (i * (scale+1)) / 65536
    // the answer is that if scale is 65535, then scale+1
    // will be zero, which is not what we want.
    uint32_t result;
    asm volatile(
                 // result.A-B  = i.A x scale.A
                 "  mul %A[i], %A[scale]                 \n\t"
                 //  save results...
                 // basic idea:
                 //"  mov %A[result], r0                 \n\t"
                 //"  mov %B[result], r1                 \n\t"
                 // which can be written as...
                 "  movw %A[result], r0                   \n\t"
                 // Because we're going to add i.A-B to
                 // result.A-D, we DO need to keep both
                 // the r0 and r1 portions of the product
                 // UNlike in the 'unfixed scale8' version.
                 // So the movw here is needed.
                 : [result] "=r" (result)
                 : [i] "r" (i),
                 [scale] "r" (scale)
                 : "r0", "r1"
                 );

    asm volatile(
                 // result.C-D  = i.B x scale.B
                 "  mul %B[i], %B[scale]                 \n\t"
                 //"  mov %C[result], r0                 \n\t"
                 //"  mov %D[result], r1                 \n\t"
                 "  movw %C[result], r0                   \n\t"
                 : [result] "+r" (result)
                 : [i] "r" (i),
                 [scale] "r" (scale)
                 : "r0", "r1"
                 );

    const uint8_t  zero = 0;
    asm volatile(
                 // result.B-D += i.B x scale.A
                 "  mul %B[i], %A[scale]                 \n\t"

                 "  add %B[result], r0                   \n\t"
                 "  adc %C[result], r1                   \n\t"
                 "  adc %D[result], %[zero]              \n\t"

                 // result.B-D += i.A x scale.B
                 "  mul %A[i], %B[scale]                 \n\t"

                 "  add %B[result], r0                   \n\t"
                 "  adc %C[result], r1                   \n\t"
                 "  adc %D[result], %[zero]              \n\t"

                 // cleanup r1
                 "  clr r1                               \n\t"

                 : [result] "+r" (result)
                 : [i] "r" (i),
                 [scale] "r" (scale),
                 [zero] "r" (zero)
                 : "r0", "r1"
                 );

    asm volatile(
                 // result.A-D += i.A-B
                 "  add %A[result], %A[i]                \n\t"
                 "  adc %B[result], %B[i]                \n\t"
                 "  adc %C[result], %[zero]              \n\t"
                 "  adc %D[result], %[zero]              \n\t"
                 : [result] "+r" (result)
                 : [i] "r" (i),
                 [zero] "r" (zero)
                 );

    result = result >> 16;
    return result;
#else
    uint32_t result;
    asm volatile(
                 // result.A-B  = i.A x scale.A
                 "  mul %A[i], %A[scale]                 \n\t"
                 //  save results...
                 // basic idea:
                 //"  mov %A[result], r0                 \n\t"
                 //"  mov %B[result], r1                 \n\t"
                 // which can be written as...
                 "  movw %A[result], r0                   \n\t"
                 // We actually don't need to do anything with r0,
                 // as result.A is never used again here, so we
                 // could just move the high byte, but movw is
                 // one clock cycle, just like mov, so might as
                 // well, in case we want to use this code for
                 // a generic 16x16 multiply somewhere.

                 : [result] "=r" (result)
                 : [i] "r" (i),
                   [scale] "r" (scale)
                 : "r0", "r1"
                 );

    asm volatile(
                 // result.C-D  = i.B x scale.B
                 "  mul %B[i], %B[scale]                 \n\t"
                 //"  mov %C[result], r0                 \n\t"
                 //"  mov %D[result], r1                 \n\t"
                 "  movw %C[result], r0                   \n\t"
                 : [result] "+r" (result)
                 : [i] "r" (i),
                   [scale] "r" (scale)
                 : "r0", "r1"
                 );

    const uint8_t  zero = 0;
    asm volatile(
                 // result.B-D += i.B x scale.A
                 "  mul %B[i], %A[scale]                 \n\t"

                 "  add %B[result], r0                   \n\t"
                 "  adc %C[result], r1                   \n\t"
                 "  adc %D[result], %[zero]              \n\t"

                 // result.B-D += i.A x scale.B
                 "  mul %A[i], %B[scale]                 \n\t"

                 "  add %B[result], r0                   \n\t"
                 "  adc %C[result], r1                   \n\t"
                 "  adc %D[result], %[zero]              \n\t"

                 // cleanup r1
                 "  clr r1                               \n\t"

                 : [result] "+r" (result)
                 : [i] "r" (i),
                   [scale] "r" (scale),
                   [zero] "r" (zero)
                 : "r0", "r1"
                 );

    result = result >> 16;
    return result;
#endif
#else
    #error "No implementation for scale16 available."
#endif
}
///@}

///@defgroup Dimming Dimming and brightening functions
///
/// Dimming and brightening functions
///
/// The eye does not respond in a linear way to light.
/// High speed PWM'd LEDs at 50% duty cycle appear far
/// brighter then the 'half as bright' you might expect.
///
/// If you want your midpoint brightness leve (128) to
/// appear half as bright as 'full' brightness (255), you
/// have to apply a 'dimming function'.
///@{

/// Adjust a scaling value for dimming
LIB8STATIC uint8_t dim8_raw( uint8_t x)
{
    return scale8( x, x);
}

/// Adjust a scaling value for dimming for video (value will never go below 1)
LIB8STATIC uint8_t dim8_video( uint8_t x)
{
    return scale8_video( x, x);
}

/// Linear version of the dimming function that halves for values < 128
LIB8STATIC uint8_t dim8_lin( uint8_t x )
{
    if( x & 0x80 ) {
        x = scale8( x, x);
    } else {
        x += 1;
        x /= 2;
    }
    return x;
}

/// inverse of the dimming function, brighten a value
LIB8STATIC uint8_t brighten8_raw( uint8_t x)
{
    uint8_t ix = 255 - x;
    return 255 - scale8( ix, ix);
}

/// inverse of the dimming function, brighten a value
LIB8STATIC uint8_t brighten8_video( uint8_t x)
{
    uint8_t ix = 255 - x;
    return 255 - scale8_video( ix, ix);
}

/// inverse of the dimming function, brighten a value
LIB8STATIC uint8_t brighten8_lin( uint8_t x )
{
    uint8_t ix = 255 - x;
    if( ix & 0x80 ) {
        ix = scale8( ix, ix);
    } else {
        ix += 1;
        ix /= 2;
    }
    return 255 - ix;
}

///@}
#endif
