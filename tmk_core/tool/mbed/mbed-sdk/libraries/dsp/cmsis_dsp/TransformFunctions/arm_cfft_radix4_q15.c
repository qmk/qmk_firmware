/* ----------------------------------------------------------------------    
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.    
*    
* $Date:        17. January 2013  
* $Revision: 	V1.4.1  
*    
* Project: 	    CMSIS DSP Library    
* Title:	    arm_cfft_radix4_q15.c    
*    
* Description:	This file has function definition of Radix-4 FFT & IFFT function and    
*				In-place bit reversal using bit reversal table    
*    
* Target Processor: Cortex-M4/Cortex-M3/Cortex-M0
*  
* Redistribution and use in source and binary forms, with or without 
* modification, are permitted provided that the following conditions
* are met:
*   - Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   - Redistributions in binary form must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in
*     the documentation and/or other materials provided with the 
*     distribution.
*   - Neither the name of ARM LIMITED nor the names of its contributors
*     may be used to endorse or promote products derived from this
*     software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.     
* -------------------------------------------------------------------- */

#include "arm_math.h"


void arm_radix4_butterfly_q15(
  q15_t * pSrc16,
  uint32_t fftLen,
  q15_t * pCoef16,
  uint32_t twidCoefModifier);

void arm_radix4_butterfly_inverse_q15(
  q15_t * pSrc16,
  uint32_t fftLen,
  q15_t * pCoef16,
  uint32_t twidCoefModifier);

void arm_bitreversal_q15(
  q15_t * pSrc,
  uint32_t fftLen,
  uint16_t bitRevFactor,
  uint16_t * pBitRevTab);

/**    
 * @ingroup groupTransforms    
 */

/**    
 * @addtogroup ComplexFFT    
 * @{    
 */


/**    
 * @details    
 * @brief Processing function for the Q15 CFFT/CIFFT.   
 * @param[in]      *S    points to an instance of the Q15 CFFT/CIFFT structure.   
 * @param[in, out] *pSrc points to the complex data buffer. Processing occurs in-place.   
 * @return none.   
 *     
 * \par Input and output formats:    
 * \par    
 * Internally input is downscaled by 2 for every stage to avoid saturations inside CFFT/CIFFT process.   
 * Hence the output format is different for different FFT sizes.    
 * The input and output formats for different FFT sizes and number of bits to upscale are mentioned in the tables below for CFFT and CIFFT:   
 * \par   
 * \image html CFFTQ15.gif "Input and Output Formats for Q15 CFFT"    
 * \image html CIFFTQ15.gif "Input and Output Formats for Q15 CIFFT"    
 */

void arm_cfft_radix4_q15(
  const arm_cfft_radix4_instance_q15 * S,
  q15_t * pSrc)
{
  if(S->ifftFlag == 1u)
  {
    /*  Complex IFFT radix-4  */
    arm_radix4_butterfly_inverse_q15(pSrc, S->fftLen, S->pTwiddle,
                                     S->twidCoefModifier);
  }
  else
  {
    /*  Complex FFT radix-4  */
    arm_radix4_butterfly_q15(pSrc, S->fftLen, S->pTwiddle,
                             S->twidCoefModifier);
  }

  if(S->bitReverseFlag == 1u)
  {
    /*  Bit Reversal */
    arm_bitreversal_q15(pSrc, S->fftLen, S->bitRevFactor, S->pBitRevTable);
  }

}

/**    
 * @} end of ComplexFFT group    
 */

/*    
* Radix-4 FFT algorithm used is :    
*    
* Input real and imaginary data:    
* x(n) = xa + j * ya    
* x(n+N/4 ) = xb + j * yb    
* x(n+N/2 ) = xc + j * yc    
* x(n+3N 4) = xd + j * yd    
*    
*    
* Output real and imaginary data:    
* x(4r) = xa'+ j * ya'    
* x(4r+1) = xb'+ j * yb'    
* x(4r+2) = xc'+ j * yc'    
* x(4r+3) = xd'+ j * yd'    
*    
*    
* Twiddle factors for radix-4 FFT:    
* Wn = co1 + j * (- si1)    
* W2n = co2 + j * (- si2)    
* W3n = co3 + j * (- si3)    
    
* The real and imaginary output values for the radix-4 butterfly are    
* xa' = xa + xb + xc + xd    
* ya' = ya + yb + yc + yd    
* xb' = (xa+yb-xc-yd)* co1 + (ya-xb-yc+xd)* (si1)    
* yb' = (ya-xb-yc+xd)* co1 - (xa+yb-xc-yd)* (si1)    
* xc' = (xa-xb+xc-xd)* co2 + (ya-yb+yc-yd)* (si2)    
* yc' = (ya-yb+yc-yd)* co2 - (xa-xb+xc-xd)* (si2)    
* xd' = (xa-yb-xc+yd)* co3 + (ya+xb-yc-xd)* (si3)    
* yd' = (ya+xb-yc-xd)* co3 - (xa-yb-xc+yd)* (si3)    
*    
*/

/**    
 * @brief  Core function for the Q15 CFFT butterfly process.   
 * @param[in, out] *pSrc16          points to the in-place buffer of Q15 data type.   
 * @param[in]      fftLen           length of the FFT.   
 * @param[in]      *pCoef16         points to twiddle coefficient buffer.   
 * @param[in]      twidCoefModifier twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table.   
 * @return none.   
 */

void arm_radix4_butterfly_q15(
  q15_t * pSrc16,
  uint32_t fftLen,
  q15_t * pCoef16,
  uint32_t twidCoefModifier)
{

#ifndef ARM_MATH_CM0_FAMILY

  /* Run the below code for Cortex-M4 and Cortex-M3 */

  q31_t R, S, T, U;
  q31_t C1, C2, C3, out1, out2;
  uint32_t n1, n2, ic, i0, i1, i2, i3, j, k;
  q15_t in;

  q15_t *ptr1;



  q31_t xaya, xbyb, xcyc, xdyd;

  /* Total process is divided into three stages */

  /* process first stage, middle stages, & last stage */

  /*  Initializations for the first stage */
  n2 = fftLen;
  n1 = n2;

  /* n2 = fftLen/4 */
  n2 >>= 2u;

  /* Index for twiddle coefficient */
  ic = 0u;

  /* Index for input read and output write */
  i0 = 0u;
  j = n2;

  /* Input is in 1.15(q15) format */

  /*  start of first stage process */
  do
  {
    /*  Butterfly implementation */

    /*  index calculation for the input as, */
    /*  pSrc16[i0 + 0], pSrc16[i0 + fftLen/4], pSrc16[i0 + fftLen/2], pSrc16[i0 + 3fftLen/4] */
    i1 = i0 + n2;
    i2 = i1 + n2;
    i3 = i2 + n2;

    /*  Reading i0, i0+fftLen/2 inputs */
    /* Read ya (real), xa(imag) input */
    T = _SIMD32_OFFSET(pSrc16 + (2u * i0));
    in = ((int16_t) (T & 0xFFFF)) >> 2;
    T = ((T >> 2) & 0xFFFF0000) | (in & 0xFFFF);

    /* Read yc (real), xc(imag) input */
    S = _SIMD32_OFFSET(pSrc16 + (2u * i2));
    in = ((int16_t) (S & 0xFFFF)) >> 2;
    S = ((S >> 2) & 0xFFFF0000) | (in & 0xFFFF);

    /* R = packed((ya + yc), (xa + xc) ) */
    R = __QADD16(T, S);

    /* S = packed((ya - yc), (xa - xc) ) */
    S = __QSUB16(T, S);

    /*  Reading i0+fftLen/4 , i0+3fftLen/4 inputs */
    /* Read yb (real), xb(imag) input */
    T = _SIMD32_OFFSET(pSrc16 + (2u * i1));
    in = ((int16_t) (T & 0xFFFF)) >> 2;
    T = ((T >> 2) & 0xFFFF0000) | (in & 0xFFFF);

    /* Read yd (real), xd(imag) input */
    U = _SIMD32_OFFSET(pSrc16 + (2u * i3));
    in = ((int16_t) (U & 0xFFFF)) >> 2;
    U = ((U >> 2) & 0xFFFF0000) | (in & 0xFFFF);

    /* T = packed((yb + yd), (xb + xd) ) */
    T = __QADD16(T, U);

    /*  writing the butterfly processed i0 sample */
    /* xa' = xa + xb + xc + xd */
    /* ya' = ya + yb + yc + yd */
    _SIMD32_OFFSET(pSrc16 + (2u * i0)) = __SHADD16(R, T);

    /* R = packed((ya + yc) - (yb + yd), (xa + xc)- (xb + xd)) */
    R = __QSUB16(R, T);

    /* co2 & si2 are read from SIMD Coefficient pointer */
    C2 = _SIMD32_OFFSET(pCoef16 + (4u * ic));

#ifndef ARM_MATH_BIG_ENDIAN

    /* xc' = (xa-xb+xc-xd)* co2 + (ya-yb+yc-yd)* (si2) */
    out1 = __SMUAD(C2, R) >> 16u;
    /* yc' = (ya-yb+yc-yd)* co2 - (xa-xb+xc-xd)* (si2) */
    out2 = __SMUSDX(C2, R);

#else

    /* xc' = (ya-yb+yc-yd)* co2 - (xa-xb+xc-xd)* (si2) */
    out1 = __SMUSDX(R, C2) >> 16u;
    /* yc' = (xa-xb+xc-xd)* co2 + (ya-yb+yc-yd)* (si2) */
    out2 = __SMUAD(C2, R);

#endif /*      #ifndef ARM_MATH_BIG_ENDIAN     */

    /*  Reading i0+fftLen/4 */
    /* T = packed(yb, xb) */
    T = _SIMD32_OFFSET(pSrc16 + (2u * i1));
    in = ((int16_t) (T & 0xFFFF)) >> 2;
    T = ((T >> 2) & 0xFFFF0000) | (in & 0xFFFF);

    /* writing the butterfly processed i0 + fftLen/4 sample */
    /* writing output(xc', yc') in little endian format */
    _SIMD32_OFFSET(pSrc16 + (2u * i1)) =
      (q31_t) ((out2) & 0xFFFF0000) | (out1 & 0x0000FFFF);

    /*  Butterfly calculations */
    /* U = packed(yd, xd) */
    U = _SIMD32_OFFSET(pSrc16 + (2u * i3));
    in = ((int16_t) (U & 0xFFFF)) >> 2;
    U = ((U >> 2) & 0xFFFF0000) | (in & 0xFFFF);

    /* T = packed(yb-yd, xb-xd) */
    T = __QSUB16(T, U);

#ifndef ARM_MATH_BIG_ENDIAN

    /* R = packed((ya-yc) + (xb- xd) , (xa-xc) - (yb-yd)) */
    R = __QASX(S, T);
    /* S = packed((ya-yc) - (xb- xd),  (xa-xc) + (yb-yd)) */
    S = __QSAX(S, T);

#else

    /* R = packed((ya-yc) + (xb- xd) , (xa-xc) - (yb-yd)) */
    R = __QSAX(S, T);
    /* S = packed((ya-yc) - (xb- xd),  (xa-xc) + (yb-yd)) */
    S = __QASX(S, T);

#endif /*      #ifndef ARM_MATH_BIG_ENDIAN     */

    /* co1 & si1 are read from SIMD Coefficient pointer */
    C1 = _SIMD32_OFFSET(pCoef16 + (2u * ic));
    /*  Butterfly process for the i0+fftLen/2 sample */

#ifndef ARM_MATH_BIG_ENDIAN

    /* xb' = (xa+yb-xc-yd)* co1 + (ya-xb-yc+xd)* (si1) */
    out1 = __SMUAD(C1, S) >> 16u;
    /* yb' = (ya-xb-yc+xd)* co1 - (xa+yb-xc-yd)* (si1) */
    out2 = __SMUSDX(C1, S);

#else

    /* xb' = (ya-xb-yc+xd)* co1 - (xa+yb-xc-yd)* (si1) */
    out1 = __SMUSDX(S, C1) >> 16u;
    /* yb' = (xa+yb-xc-yd)* co1 + (ya-xb-yc+xd)* (si1) */
    out2 = __SMUAD(C1, S);

#endif /*      #ifndef ARM_MATH_BIG_ENDIAN     */

    /* writing output(xb', yb') in little endian format */
    _SIMD32_OFFSET(pSrc16 + (2u * i2)) =
      ((out2) & 0xFFFF0000) | ((out1) & 0x0000FFFF);


    /* co3 & si3 are read from SIMD Coefficient pointer */
    C3 = _SIMD32_OFFSET(pCoef16 + (6u * ic));
    /*  Butterfly process for the i0+3fftLen/4 sample */

#ifndef ARM_MATH_BIG_ENDIAN

    /* xd' = (xa-yb-xc+yd)* co3 + (ya+xb-yc-xd)* (si3) */
    out1 = __SMUAD(C3, R) >> 16u;
    /* yd' = (ya+xb-yc-xd)* co3 - (xa-yb-xc+yd)* (si3) */
    out2 = __SMUSDX(C3, R);

#else

    /* xd' = (ya+xb-yc-xd)* co3 - (xa-yb-xc+yd)* (si3) */
    out1 = __SMUSDX(R, C3) >> 16u;
    /* yd' = (xa-yb-xc+yd)* co3 + (ya+xb-yc-xd)* (si3) */
    out2 = __SMUAD(C3, R);

#endif /*      #ifndef ARM_MATH_BIG_ENDIAN     */

    /* writing output(xd', yd') in little endian format */
    _SIMD32_OFFSET(pSrc16 + (2u * i3)) =
      ((out2) & 0xFFFF0000) | (out1 & 0x0000FFFF);

    /*  Twiddle coefficients index modifier */
    ic = ic + twidCoefModifier;

    /*  Updating input index */
    i0 = i0 + 1u;

  } while(--j);
  /* data is in 4.11(q11) format */

  /* end of first stage process */


  /* start of middle stage process */

  /*  Twiddle coefficients index modifier */
  twidCoefModifier <<= 2u;

  /*  Calculation of Middle stage */
  for (k = fftLen / 4u; k > 4u; k >>= 2u)
  {
    /*  Initializations for the middle stage */
    n1 = n2;
    n2 >>= 2u;
    ic = 0u;

    for (j = 0u; j <= (n2 - 1u); j++)
    {
      /*  index calculation for the coefficients */
      C1 = _SIMD32_OFFSET(pCoef16 + (2u * ic));
      C2 = _SIMD32_OFFSET(pCoef16 + (4u * ic));
      C3 = _SIMD32_OFFSET(pCoef16 + (6u * ic));

      /*  Twiddle coefficients index modifier */
      ic = ic + twidCoefModifier;

      /*  Butterfly implementation */
      for (i0 = j; i0 < fftLen; i0 += n1)
      {
        /*  index calculation for the input as, */
        /*  pSrc16[i0 + 0], pSrc16[i0 + fftLen/4], pSrc16[i0 + fftLen/2], pSrc16[i0 + 3fftLen/4] */
        i1 = i0 + n2;
        i2 = i1 + n2;
        i3 = i2 + n2;

        /*  Reading i0, i0+fftLen/2 inputs */
        /* Read ya (real), xa(imag) input */
        T = _SIMD32_OFFSET(pSrc16 + (2u * i0));

        /* Read yc (real), xc(imag) input */
        S = _SIMD32_OFFSET(pSrc16 + (2u * i2));

        /* R = packed( (ya + yc), (xa + xc)) */
        R = __QADD16(T, S);

        /* S = packed((ya - yc), (xa - xc)) */
        S = __QSUB16(T, S);

        /*  Reading i0+fftLen/4 , i0+3fftLen/4 inputs */
        /* Read yb (real), xb(imag) input */
        T = _SIMD32_OFFSET(pSrc16 + (2u * i1));

        /* Read yd (real), xd(imag) input */
        U = _SIMD32_OFFSET(pSrc16 + (2u * i3));

        /* T = packed( (yb + yd), (xb + xd)) */
        T = __QADD16(T, U);

        /*  writing the butterfly processed i0 sample */

        /* xa' = xa + xb + xc + xd */
        /* ya' = ya + yb + yc + yd */
        out1 = __SHADD16(R, T);
        in = ((int16_t) (out1 & 0xFFFF)) >> 1;
        out1 = ((out1 >> 1) & 0xFFFF0000) | (in & 0xFFFF);
        _SIMD32_OFFSET(pSrc16 + (2u * i0)) = out1;

        /* R = packed( (ya + yc) - (yb + yd), (xa + xc) - (xb + xd)) */
        R = __SHSUB16(R, T);

#ifndef ARM_MATH_BIG_ENDIAN

        /* (ya-yb+yc-yd)* (si2) + (xa-xb+xc-xd)* co2 */
        out1 = __SMUAD(C2, R) >> 16u;

        /* (ya-yb+yc-yd)* co2 - (xa-xb+xc-xd)* (si2) */
        out2 = __SMUSDX(C2, R);

#else

        /* (ya-yb+yc-yd)* co2 - (xa-xb+xc-xd)* (si2) */
        out1 = __SMUSDX(R, C2) >> 16u;

        /* (ya-yb+yc-yd)* (si2) + (xa-xb+xc-xd)* co2 */
        out2 = __SMUAD(C2, R);

#endif /*      #ifndef ARM_MATH_BIG_ENDIAN     */

        /*  Reading i0+3fftLen/4 */
        /* Read yb (real), xb(imag) input */
        T = _SIMD32_OFFSET(pSrc16 + (2u * i1));

        /*  writing the butterfly processed i0 + fftLen/4 sample */
        /* xc' = (xa-xb+xc-xd)* co2 + (ya-yb+yc-yd)* (si2) */
        /* yc' = (ya-yb+yc-yd)* co2 - (xa-xb+xc-xd)* (si2) */
        _SIMD32_OFFSET(pSrc16 + (2u * i1)) =
          ((out2) & 0xFFFF0000) | (out1 & 0x0000FFFF);

        /*  Butterfly calculations */

        /* Read yd (real), xd(imag) input */
        U = _SIMD32_OFFSET(pSrc16 + (2u * i3));

        /* T = packed(yb-yd, xb-xd) */
        T = __QSUB16(T, U);

#ifndef ARM_MATH_BIG_ENDIAN

        /* R = packed((ya-yc) + (xb- xd) , (xa-xc) - (yb-yd)) */
        R = __SHASX(S, T);

        /* S = packed((ya-yc) - (xb- xd),  (xa-xc) + (yb-yd)) */
        S = __SHSAX(S, T);


        /*  Butterfly process for the i0+fftLen/2 sample */
        out1 = __SMUAD(C1, S) >> 16u;
        out2 = __SMUSDX(C1, S);

#else

        /* R = packed((ya-yc) + (xb- xd) , (xa-xc) - (yb-yd)) */
        R = __SHSAX(S, T);

        /* S = packed((ya-yc) - (xb- xd),  (xa-xc) + (yb-yd)) */
        S = __SHASX(S, T);


        /*  Butterfly process for the i0+fftLen/2 sample */
        out1 = __SMUSDX(S, C1) >> 16u;
        out2 = __SMUAD(C1, S);

#endif /*      #ifndef ARM_MATH_BIG_ENDIAN     */

        /* xb' = (xa+yb-xc-yd)* co1 + (ya-xb-yc+xd)* (si1) */
        /* yb' = (ya-xb-yc+xd)* co1 - (xa+yb-xc-yd)* (si1) */
        _SIMD32_OFFSET(pSrc16 + (2u * i2)) =
          ((out2) & 0xFFFF0000) | (out1 & 0x0000FFFF);

        /*  Butterfly process for the i0+3fftLen/4 sample */

#ifndef ARM_MATH_BIG_ENDIAN

        out1 = __SMUAD(C3, R) >> 16u;
        out2 = __SMUSDX(C3, R);

#else

        out1 = __SMUSDX(R, C3) >> 16u;
        out2 = __SMUAD(C3, R);

#endif /*      #ifndef ARM_MATH_BIG_ENDIAN     */

        /* xd' = (xa-yb-xc+yd)* co3 + (ya+xb-yc-xd)* (si3) */
        /* yd' = (ya+xb-yc-xd)* co3 - (xa-yb-xc+yd)* (si3) */
        _SIMD32_OFFSET(pSrc16 + (2u * i3)) =
          ((out2) & 0xFFFF0000) | (out1 & 0x0000FFFF);
      }
    }
    /*  Twiddle coefficients index modifier */
    twidCoefModifier <<= 2u;
  }
  /* end of middle stage process */


  /* data is in 10.6(q6) format for the 1024 point */
  /* data is in 8.8(q8) format for the 256 point */
  /* data is in 6.10(q10) format for the 64 point */
  /* data is in 4.12(q12) format for the 16 point */

  /*  Initializations for the last stage */
  j = fftLen >> 2;

  ptr1 = &pSrc16[0];

  /* start of last stage process */

  /*  Butterfly implementation */
  do
  {
    /* Read xa (real), ya(imag) input */
    xaya = *__SIMD32(ptr1)++;

    /* Read xb (real), yb(imag) input */
    xbyb = *__SIMD32(ptr1)++;

    /* Read xc (real), yc(imag) input */
    xcyc = *__SIMD32(ptr1)++;

    /* Read xd (real), yd(imag) input */
    xdyd = *__SIMD32(ptr1)++;

    /* R = packed((ya + yc), (xa + xc)) */
    R = __QADD16(xaya, xcyc);

    /* T = packed((yb + yd), (xb + xd)) */
    T = __QADD16(xbyb, xdyd);

    /* pointer updation for writing */
    ptr1 = ptr1 - 8u;


    /* xa' = xa + xb + xc + xd */
    /* ya' = ya + yb + yc + yd */
    *__SIMD32(ptr1)++ = __SHADD16(R, T);

    /* T = packed((yb + yd), (xb + xd)) */
    T = __QADD16(xbyb, xdyd);

    /* xc' = (xa-xb+xc-xd) */
    /* yc' = (ya-yb+yc-yd) */
    *__SIMD32(ptr1)++ = __SHSUB16(R, T);

    /* S = packed((ya - yc), (xa - xc)) */
    S = __QSUB16(xaya, xcyc);

    /* Read yd (real), xd(imag) input */
    /* T = packed( (yb - yd), (xb - xd))  */
    U = __QSUB16(xbyb, xdyd);

#ifndef ARM_MATH_BIG_ENDIAN

    /* xb' = (xa+yb-xc-yd) */
    /* yb' = (ya-xb-yc+xd) */
    *__SIMD32(ptr1)++ = __SHSAX(S, U);


    /* xd' = (xa-yb-xc+yd) */
    /* yd' = (ya+xb-yc-xd) */
    *__SIMD32(ptr1)++ = __SHASX(S, U);

#else

    /* xb' = (xa+yb-xc-yd) */
    /* yb' = (ya-xb-yc+xd) */
    *__SIMD32(ptr1)++ = __SHASX(S, U);


    /* xd' = (xa-yb-xc+yd) */
    /* yd' = (ya+xb-yc-xd) */
    *__SIMD32(ptr1)++ = __SHSAX(S, U);

#endif /*      #ifndef ARM_MATH_BIG_ENDIAN     */

  } while(--j);

  /* end of last stage process */

  /* output is in 11.5(q5) format for the 1024 point */
  /* output is in 9.7(q7) format for the 256 point   */
  /* output is in 7.9(q9) format for the 64 point  */
  /* output is in 5.11(q11) format for the 16 point  */


#else

  /* Run the below code for Cortex-M0 */

  q15_t R0, R1, S0, S1, T0, T1, U0, U1;
  q15_t Co1, Si1, Co2, Si2, Co3, Si3, out1, out2;
  uint32_t n1, n2, ic, i0, i1, i2, i3, j, k;

  /* Total process is divided into three stages */

  /* process first stage, middle stages, & last stage */

  /*  Initializations for the first stage */
  n2 = fftLen;
  n1 = n2;

  /* n2 = fftLen/4 */
  n2 >>= 2u;

  /* Index for twiddle coefficient */
  ic = 0u;

  /* Index for input read and output write */
  i0 = 0u;
  j = n2;

  /* Input is in 1.15(q15) format */

  /*  start of first stage process */
  do
  {
    /*  Butterfly implementation */

    /*  index calculation for the input as, */
    /*  pSrc16[i0 + 0], pSrc16[i0 + fftLen/4], pSrc16[i0 + fftLen/2], pSrc16[i0 + 3fftLen/4] */
    i1 = i0 + n2;
    i2 = i1 + n2;
    i3 = i2 + n2;

    /*  Reading i0, i0+fftLen/2 inputs */

    /* input is down scale by 4 to avoid overflow */
    /* Read ya (real), xa(imag) input */
    T0 = pSrc16[i0 * 2u] >> 2u;
    T1 = pSrc16[(i0 * 2u) + 1u] >> 2u;

    /* input is down scale by 4 to avoid overflow */
    /* Read yc (real), xc(imag) input */
    S0 = pSrc16[i2 * 2u] >> 2u;
    S1 = pSrc16[(i2 * 2u) + 1u] >> 2u;

    /* R0 = (ya + yc) */
    R0 = __SSAT(T0 + S0, 16u);
    /* R1 = (xa + xc) */
    R1 = __SSAT(T1 + S1, 16u);

    /* S0 = (ya - yc) */
    S0 = __SSAT(T0 - S0, 16);
    /* S1 = (xa - xc) */
    S1 = __SSAT(T1 - S1, 16);

    /*  Reading i0+fftLen/4 , i0+3fftLen/4 inputs */
    /* input is down scale by 4 to avoid overflow */
    /* Read yb (real), xb(imag) input */
    T0 = pSrc16[i1 * 2u] >> 2u;
    T1 = pSrc16[(i1 * 2u) + 1u] >> 2u;

    /* input is down scale by 4 to avoid overflow */
    /* Read yd (real), xd(imag) input */
    U0 = pSrc16[i3 * 2u] >> 2u;
    U1 = pSrc16[(i3 * 2u) + 1] >> 2u;

    /* T0 = (yb + yd) */
    T0 = __SSAT(T0 + U0, 16u);
    /* T1 = (xb + xd) */
    T1 = __SSAT(T1 + U1, 16u);

    /*  writing the butterfly processed i0 sample */
    /* ya' = ya + yb + yc + yd */
    /* xa' = xa + xb + xc + xd */
    pSrc16[i0 * 2u] = (R0 >> 1u) + (T0 >> 1u);
    pSrc16[(i0 * 2u) + 1u] = (R1 >> 1u) + (T1 >> 1u);

    /* R0 = (ya + yc) - (yb + yd) */
    /* R1 = (xa + xc) - (xb + xd) */
    R0 = __SSAT(R0 - T0, 16u);
    R1 = __SSAT(R1 - T1, 16u);

    /* co2 & si2 are read from Coefficient pointer */
    Co2 = pCoef16[2u * ic * 2u];
    Si2 = pCoef16[(2u * ic * 2u) + 1];

    /* xc' = (xa-xb+xc-xd)* co2 + (ya-yb+yc-yd)* (si2) */
    out1 = (short) ((Co2 * R0 + Si2 * R1) >> 16u);
    /* yc' = (ya-yb+yc-yd)* co2 - (xa-xb+xc-xd)* (si2) */
    out2 = (short) ((-Si2 * R0 + Co2 * R1) >> 16u);

    /*  Reading i0+fftLen/4 */
    /* input is down scale by 4 to avoid overflow */
    /* T0 = yb, T1 =  xb */
    T0 = pSrc16[i1 * 2u] >> 2;
    T1 = pSrc16[(i1 * 2u) + 1] >> 2;

    /* writing the butterfly processed i0 + fftLen/4 sample */
    /* writing output(xc', yc') in little endian format */
    pSrc16[i1 * 2u] = out1;
    pSrc16[(i1 * 2u) + 1] = out2;

    /*  Butterfly calculations */
    /* input is down scale by 4 to avoid overflow */
    /* U0 = yd, U1 = xd */
    U0 = pSrc16[i3 * 2u] >> 2;
    U1 = pSrc16[(i3 * 2u) + 1] >> 2;
    /* T0 = yb-yd */
    T0 = __SSAT(T0 - U0, 16);
    /* T1 = xb-xd */
    T1 = __SSAT(T1 - U1, 16);

    /* R1 = (ya-yc) + (xb- xd),  R0 = (xa-xc) - (yb-yd)) */
    R0 = (short) __SSAT((q31_t) (S0 - T1), 16);
    R1 = (short) __SSAT((q31_t) (S1 + T0), 16);

    /* S1 = (ya-yc) - (xb- xd), S0 = (xa-xc) + (yb-yd)) */
    S0 = (short) __SSAT(((q31_t) S0 + T1), 16u);
    S1 = (short) __SSAT(((q31_t) S1 - T0), 16u);

    /* co1 & si1 are read from Coefficient pointer */
    Co1 = pCoef16[ic * 2u];
    Si1 = pCoef16[(ic * 2u) + 1];
    /*  Butterfly process for the i0+fftLen/2 sample */
    /* xb' = (xa+yb-xc-yd)* co1 + (ya-xb-yc+xd)* (si1) */
    out1 = (short) ((Si1 * S1 + Co1 * S0) >> 16);
    /* yb' = (ya-xb-yc+xd)* co1 - (xa+yb-xc-yd)* (si1) */
    out2 = (short) ((-Si1 * S0 + Co1 * S1) >> 16);

    /* writing output(xb', yb') in little endian format */
    pSrc16[i2 * 2u] = out1;
    pSrc16[(i2 * 2u) + 1] = out2;

    /* Co3 & si3 are read from Coefficient pointer */
    Co3 = pCoef16[3u * (ic * 2u)];
    Si3 = pCoef16[(3u * (ic * 2u)) + 1];
    /*  Butterfly process for the i0+3fftLen/4 sample */
    /* xd' = (xa-yb-xc+yd)* Co3 + (ya+xb-yc-xd)* (si3) */
    out1 = (short) ((Si3 * R1 + Co3 * R0) >> 16u);
    /* yd' = (ya+xb-yc-xd)* Co3 - (xa-yb-xc+yd)* (si3) */
    out2 = (short) ((-Si3 * R0 + Co3 * R1) >> 16u);
    /* writing output(xd', yd') in little endian format */
    pSrc16[i3 * 2u] = out1;
    pSrc16[(i3 * 2u) + 1] = out2;

    /*  Twiddle coefficients index modifier */
    ic = ic + twidCoefModifier;

    /*  Updating input index */
    i0 = i0 + 1u;

  } while(--j);
  /* data is in 4.11(q11) format */

  /* end of first stage process */


  /* start of middle stage process */

  /*  Twiddle coefficients index modifier */
  twidCoefModifier <<= 2u;

  /*  Calculation of Middle stage */
  for (k = fftLen / 4u; k > 4u; k >>= 2u)
  {
    /*  Initializations for the middle stage */
    n1 = n2;
    n2 >>= 2u;
    ic = 0u;

    for (j = 0u; j <= (n2 - 1u); j++)
    {
      /*  index calculation for the coefficients */
      Co1 = pCoef16[ic * 2u];
      Si1 = pCoef16[(ic * 2u) + 1u];
      Co2 = pCoef16[2u * (ic * 2u)];
      Si2 = pCoef16[(2u * (ic * 2u)) + 1u];
      Co3 = pCoef16[3u * (ic * 2u)];
      Si3 = pCoef16[(3u * (ic * 2u)) + 1u];

      /*  Twiddle coefficients index modifier */
      ic = ic + twidCoefModifier;

      /*  Butterfly implementation */
      for (i0 = j; i0 < fftLen; i0 += n1)
      {
        /*  index calculation for the input as, */
        /*  pSrc16[i0 + 0], pSrc16[i0 + fftLen/4], pSrc16[i0 + fftLen/2], pSrc16[i0 + 3fftLen/4] */
        i1 = i0 + n2;
        i2 = i1 + n2;
        i3 = i2 + n2;

        /*  Reading i0, i0+fftLen/2 inputs */
        /* Read ya (real), xa(imag) input */
        T0 = pSrc16[i0 * 2u];
        T1 = pSrc16[(i0 * 2u) + 1u];

        /* Read yc (real), xc(imag) input */
        S0 = pSrc16[i2 * 2u];
        S1 = pSrc16[(i2 * 2u) + 1u];

        /* R0 = (ya + yc), R1 = (xa + xc) */
        R0 = __SSAT(T0 + S0, 16);
        R1 = __SSAT(T1 + S1, 16);

        /* S0 = (ya - yc), S1 =(xa - xc) */
        S0 = __SSAT(T0 - S0, 16);
        S1 = __SSAT(T1 - S1, 16);

        /*  Reading i0+fftLen/4 , i0+3fftLen/4 inputs */
        /* Read yb (real), xb(imag) input */
        T0 = pSrc16[i1 * 2u];
        T1 = pSrc16[(i1 * 2u) + 1u];

        /* Read yd (real), xd(imag) input */
        U0 = pSrc16[i3 * 2u];
        U1 = pSrc16[(i3 * 2u) + 1u];


        /* T0 = (yb + yd), T1 = (xb + xd) */
        T0 = __SSAT(T0 + U0, 16);
        T1 = __SSAT(T1 + U1, 16);

        /*  writing the butterfly processed i0 sample */

        /* xa' = xa + xb + xc + xd */
        /* ya' = ya + yb + yc + yd */
        out1 = ((R0 >> 1u) + (T0 >> 1u)) >> 1u;
        out2 = ((R1 >> 1u) + (T1 >> 1u)) >> 1u;

        pSrc16[i0 * 2u] = out1;
        pSrc16[(2u * i0) + 1u] = out2;

        /* R0 = (ya + yc) - (yb + yd), R1 = (xa + xc) - (xb + xd) */
        R0 = (R0 >> 1u) - (T0 >> 1u);
        R1 = (R1 >> 1u) - (T1 >> 1u);

        /* (ya-yb+yc-yd)* (si2) + (xa-xb+xc-xd)* co2 */
        out1 = (short) ((Co2 * R0 + Si2 * R1) >> 16u);

        /* (ya-yb+yc-yd)* co2 - (xa-xb+xc-xd)* (si2) */
        out2 = (short) ((-Si2 * R0 + Co2 * R1) >> 16u);

        /*  Reading i0+3fftLen/4 */
        /* Read yb (real), xb(imag) input */
        T0 = pSrc16[i1 * 2u];
        T1 = pSrc16[(i1 * 2u) + 1u];

        /*  writing the butterfly processed i0 + fftLen/4 sample */
        /* xc' = (xa-xb+xc-xd)* co2 + (ya-yb+yc-yd)* (si2) */
        /* yc' = (ya-yb+yc-yd)* co2 - (xa-xb+xc-xd)* (si2) */
        pSrc16[i1 * 2u] = out1;
        pSrc16[(i1 * 2u) + 1u] = out2;

        /*  Butterfly calculations */

        /* Read yd (real), xd(imag) input */
        U0 = pSrc16[i3 * 2u];
        U1 = pSrc16[(i3 * 2u) + 1u];

        /* T0 = yb-yd, T1 = xb-xd */
        T0 = __SSAT(T0 - U0, 16);
        T1 = __SSAT(T1 - U1, 16);

        /* R0 = (ya-yc) + (xb- xd), R1 = (xa-xc) - (yb-yd)) */
        R0 = (S0 >> 1u) - (T1 >> 1u);
        R1 = (S1 >> 1u) + (T0 >> 1u);

        /* S0 = (ya-yc) - (xb- xd), S1 = (xa-xc) + (yb-yd)) */
        S0 = (S0 >> 1u) + (T1 >> 1u);
        S1 = (S1 >> 1u) - (T0 >> 1u);

        /*  Butterfly process for the i0+fftLen/2 sample */
        out1 = (short) ((Co1 * S0 + Si1 * S1) >> 16u);

        out2 = (short) ((-Si1 * S0 + Co1 * S1) >> 16u);

        /* xb' = (xa+yb-xc-yd)* co1 + (ya-xb-yc+xd)* (si1) */
        /* yb' = (ya-xb-yc+xd)* co1 - (xa+yb-xc-yd)* (si1) */
        pSrc16[i2 * 2u] = out1;
        pSrc16[(i2 * 2u) + 1u] = out2;

        /*  Butterfly process for the i0+3fftLen/4 sample */
        out1 = (short) ((Si3 * R1 + Co3 * R0) >> 16u);

        out2 = (short) ((-Si3 * R0 + Co3 * R1) >> 16u);
        /* xd' = (xa-yb-xc+yd)* Co3 + (ya+xb-yc-xd)* (si3) */
        /* yd' = (ya+xb-yc-xd)* Co3 - (xa-yb-xc+yd)* (si3) */
        pSrc16[i3 * 2u] = out1;
        pSrc16[(i3 * 2u) + 1u] = out2;
      }
    }
    /*  Twiddle coefficients index modifier */
    twidCoefModifier <<= 2u;
  }
  /* end of middle stage process */


  /* data is in 10.6(q6) format for the 1024 point */
  /* data is in 8.8(q8) format for the 256 point */
  /* data is in 6.10(q10) format for the 64 point */
  /* data is in 4.12(q12) format for the 16 point */

  /*  Initializations for the last stage */
  n1 = n2;
  n2 >>= 2u;

  /* start of last stage process */

  /*  Butterfly implementation */
  for (i0 = 0u; i0 <= (fftLen - n1); i0 += n1)
  {
    /*  index calculation for the input as, */
    /*  pSrc16[i0 + 0], pSrc16[i0 + fftLen/4], pSrc16[i0 + fftLen/2], pSrc16[i0 + 3fftLen/4] */
    i1 = i0 + n2;
    i2 = i1 + n2;
    i3 = i2 + n2;

    /*  Reading i0, i0+fftLen/2 inputs */
    /* Read ya (real), xa(imag) input */
    T0 = pSrc16[i0 * 2u];
    T1 = pSrc16[(i0 * 2u) + 1u];

    /* Read yc (real), xc(imag) input */
    S0 = pSrc16[i2 * 2u];
    S1 = pSrc16[(i2 * 2u) + 1u];

    /* R0 = (ya + yc), R1 = (xa + xc) */
    R0 = __SSAT(T0 + S0, 16u);
    R1 = __SSAT(T1 + S1, 16u);

    /* S0 = (ya - yc), S1 = (xa - xc) */
    S0 = __SSAT(T0 - S0, 16u);
    S1 = __SSAT(T1 - S1, 16u);

    /*  Reading i0+fftLen/4 , i0+3fftLen/4 inputs */
    /* Read yb (real), xb(imag) input */
    T0 = pSrc16[i1 * 2u];
    T1 = pSrc16[(i1 * 2u) + 1u];
    /* Read yd (real), xd(imag) input */
    U0 = pSrc16[i3 * 2u];
    U1 = pSrc16[(i3 * 2u) + 1u];

    /* T0 = (yb + yd), T1 = (xb + xd)) */
    T0 = __SSAT(T0 + U0, 16u);
    T1 = __SSAT(T1 + U1, 16u);

    /*  writing the butterfly processed i0 sample */
    /* xa' = xa + xb + xc + xd */
    /* ya' = ya + yb + yc + yd */
    pSrc16[i0 * 2u] = (R0 >> 1u) + (T0 >> 1u);
    pSrc16[(i0 * 2u) + 1u] = (R1 >> 1u) + (T1 >> 1u);

    /* R0 = (ya + yc) - (yb + yd), R1 = (xa + xc) - (xb + xd) */
    R0 = (R0 >> 1u) - (T0 >> 1u);
    R1 = (R1 >> 1u) - (T1 >> 1u);
    /* Read yb (real), xb(imag) input */
    T0 = pSrc16[i1 * 2u];
    T1 = pSrc16[(i1 * 2u) + 1u];

    /*  writing the butterfly processed i0 + fftLen/4 sample */
    /* xc' = (xa-xb+xc-xd) */
    /* yc' = (ya-yb+yc-yd) */
    pSrc16[i1 * 2u] = R0;
    pSrc16[(i1 * 2u) + 1u] = R1;

    /* Read yd (real), xd(imag) input */
    U0 = pSrc16[i3 * 2u];
    U1 = pSrc16[(i3 * 2u) + 1u];
    /* T0 = (yb - yd), T1 = (xb - xd)  */
    T0 = __SSAT(T0 - U0, 16u);
    T1 = __SSAT(T1 - U1, 16u);

    /*  writing the butterfly processed i0 + fftLen/2 sample */
    /* xb' = (xa+yb-xc-yd) */
    /* yb' = (ya-xb-yc+xd) */
    pSrc16[i2 * 2u] = (S0 >> 1u) + (T1 >> 1u);
    pSrc16[(i2 * 2u) + 1u] = (S1 >> 1u) - (T0 >> 1u);

    /*  writing the butterfly processed i0 + 3fftLen/4 sample */
    /* xd' = (xa-yb-xc+yd) */
    /* yd' = (ya+xb-yc-xd) */
    pSrc16[i3 * 2u] = (S0 >> 1u) - (T1 >> 1u);
    pSrc16[(i3 * 2u) + 1u] = (S1 >> 1u) + (T0 >> 1u);

  }

  /* end of last stage process */

  /* output is in 11.5(q5) format for the 1024 point */
  /* output is in 9.7(q7) format for the 256 point   */
  /* output is in 7.9(q9) format for the 64 point  */
  /* output is in 5.11(q11) format for the 16 point  */

#endif /* #ifndef ARM_MATH_CM0_FAMILY */

}


/**    
 * @brief  Core function for the Q15 CIFFT butterfly process.   
 * @param[in, out] *pSrc16          points to the in-place buffer of Q15 data type.   
 * @param[in]      fftLen           length of the FFT.   
 * @param[in]      *pCoef16         points to twiddle coefficient buffer.   
 * @param[in]      twidCoefModifier twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table.   
 * @return none.   
 */

/*    
* Radix-4 IFFT algorithm used is :    
*    
* CIFFT uses same twiddle coefficients as CFFT function    
*  x[k] = x[n] + (j)k * x[n + fftLen/4] + (-1)k * x[n+fftLen/2] + (-j)k * x[n+3*fftLen/4]    
*    
*    
* IFFT is implemented with following changes in equations from FFT    
*    
* Input real and imaginary data:    
* x(n) = xa + j * ya    
* x(n+N/4 ) = xb + j * yb    
* x(n+N/2 ) = xc + j * yc    
* x(n+3N 4) = xd + j * yd    
*    
*    
* Output real and imaginary data:    
* x(4r) = xa'+ j * ya'    
* x(4r+1) = xb'+ j * yb'    
* x(4r+2) = xc'+ j * yc'    
* x(4r+3) = xd'+ j * yd'    
*    
*    
* Twiddle factors for radix-4 IFFT:    
* Wn = co1 + j * (si1)    
* W2n = co2 + j * (si2)    
* W3n = co3 + j * (si3)    
    
* The real and imaginary output values for the radix-4 butterfly are    
* xa' = xa + xb + xc + xd    
* ya' = ya + yb + yc + yd    
* xb' = (xa-yb-xc+yd)* co1 - (ya+xb-yc-xd)* (si1)    
* yb' = (ya+xb-yc-xd)* co1 + (xa-yb-xc+yd)* (si1)    
* xc' = (xa-xb+xc-xd)* co2 - (ya-yb+yc-yd)* (si2)    
* yc' = (ya-yb+yc-yd)* co2 + (xa-xb+xc-xd)* (si2)    
* xd' = (xa+yb-xc-yd)* co3 - (ya-xb-yc+xd)* (si3)    
* yd' = (ya-xb-yc+xd)* co3 + (xa+yb-xc-yd)* (si3)    
*    
*/

void arm_radix4_butterfly_inverse_q15(
  q15_t * pSrc16,
  uint32_t fftLen,
  q15_t * pCoef16,
  uint32_t twidCoefModifier)
{

#ifndef ARM_MATH_CM0_FAMILY

  /* Run the below code for Cortex-M4 and Cortex-M3 */

  q31_t R, S, T, U;
  q31_t C1, C2, C3, out1, out2;
  uint32_t n1, n2, ic, i0, i1, i2, i3, j, k;
  q15_t in;

  q15_t *ptr1;



  q31_t xaya, xbyb, xcyc, xdyd;

  /* Total process is divided into three stages */

  /* process first stage, middle stages, & last stage */

  /*  Initializations for the first stage */
  n2 = fftLen;
  n1 = n2;

  /* n2 = fftLen/4 */
  n2 >>= 2u;

  /* Index for twiddle coefficient */
  ic = 0u;

  /* Index for input read and output write */
  i0 = 0u;
  j = n2;

  /* Input is in 1.15(q15) format */

  /*  start of first stage process */
  do
  {
    /*  Butterfly implementation */

    /*  index calculation for the input as, */
    /*  pSrc16[i0 + 0], pSrc16[i0 + fftLen/4], pSrc16[i0 + fftLen/2], pSrc16[i0 + 3fftLen/4] */
    i1 = i0 + n2;
    i2 = i1 + n2;
    i3 = i2 + n2;

    /*  Reading i0, i0+fftLen/2 inputs */
    /* Read ya (real), xa(imag) input */
    T = _SIMD32_OFFSET(pSrc16 + (2u * i0));
    in = ((int16_t) (T & 0xFFFF)) >> 2;
    T = ((T >> 2) & 0xFFFF0000) | (in & 0xFFFF);

    /* Read yc (real), xc(imag) input */
    S = _SIMD32_OFFSET(pSrc16 + (2u * i2));
    in = ((int16_t) (S & 0xFFFF)) >> 2;
    S = ((S >> 2) & 0xFFFF0000) | (in & 0xFFFF);

    /* R = packed((ya + yc), (xa + xc) ) */
    R = __QADD16(T, S);

    /* S = packed((ya - yc), (xa - xc) ) */
    S = __QSUB16(T, S);

    /*  Reading i0+fftLen/4 , i0+3fftLen/4 inputs */
    /* Read yb (real), xb(imag) input */
    T = _SIMD32_OFFSET(pSrc16 + (2u * i1));
    in = ((int16_t) (T & 0xFFFF)) >> 2;
    T = ((T >> 2) & 0xFFFF0000) | (in & 0xFFFF);

    /* Read yd (real), xd(imag) input */
    U = _SIMD32_OFFSET(pSrc16 + (2u * i3));
    in = ((int16_t) (U & 0xFFFF)) >> 2;
    U = ((U >> 2) & 0xFFFF0000) | (in & 0xFFFF);

    /* T = packed((yb + yd), (xb + xd) ) */
    T = __QADD16(T, U);

    /*  writing the butterfly processed i0 sample */
    /* xa' = xa + xb + xc + xd */
    /* ya' = ya + yb + yc + yd */
    _SIMD32_OFFSET(pSrc16 + (2u * i0)) = __SHADD16(R, T);

    /* R = packed((ya + yc) - (yb + yd), (xa + xc)- (xb + xd)) */
    R = __QSUB16(R, T);

    /* co2 & si2 are read from SIMD Coefficient pointer */
    C2 = _SIMD32_OFFSET(pCoef16 + (4u * ic));

#ifndef ARM_MATH_BIG_ENDIAN

    /* xc' = (xa-xb+xc-xd)* co2 + (ya-yb+yc-yd)* (si2) */
    out1 = __SMUSD(C2, R) >> 16u;
    /* yc' = (ya-yb+yc-yd)* co2 - (xa-xb+xc-xd)* (si2) */
    out2 = __SMUADX(C2, R);

#else

    /* xc' = (ya-yb+yc-yd)* co2 - (xa-xb+xc-xd)* (si2) */
    out1 = __SMUADX(C2, R) >> 16u;
    /* yc' = (xa-xb+xc-xd)* co2 + (ya-yb+yc-yd)* (si2) */
    out2 = __SMUSD(__QSUB16(0, C2), R);

#endif /*      #ifndef ARM_MATH_BIG_ENDIAN     */

    /*  Reading i0+fftLen/4 */
    /* T = packed(yb, xb) */
    T = _SIMD32_OFFSET(pSrc16 + (2u * i1));
    in = ((int16_t) (T & 0xFFFF)) >> 2;
    T = ((T >> 2) & 0xFFFF0000) | (in & 0xFFFF);

    /* writing the butterfly processed i0 + fftLen/4 sample */
    /* writing output(xc', yc') in little endian format */
    _SIMD32_OFFSET(pSrc16 + (2u * i1)) =
      (q31_t) ((out2) & 0xFFFF0000) | (out1 & 0x0000FFFF);

    /*  Butterfly calculations */
    /* U = packed(yd, xd) */
    U = _SIMD32_OFFSET(pSrc16 + (2u * i3));
    in = ((int16_t) (U & 0xFFFF)) >> 2;
    U = ((U >> 2) & 0xFFFF0000) | (in & 0xFFFF);

    /* T = packed(yb-yd, xb-xd) */
    T = __QSUB16(T, U);

#ifndef ARM_MATH_BIG_ENDIAN

    /* R = packed((ya-yc) + (xb- xd) , (xa-xc) - (yb-yd)) */
    R = __QSAX(S, T);
    /* S = packed((ya-yc) + (xb- xd),  (xa-xc) - (yb-yd)) */
    S = __QASX(S, T);

#else

    /* R = packed((ya-yc) + (xb- xd) , (xa-xc) - (yb-yd)) */
    R = __QASX(S, T);
    /* S = packed((ya-yc) - (xb- xd),  (xa-xc) + (yb-yd)) */
    S = __QSAX(S, T);

#endif /*      #ifndef ARM_MATH_BIG_ENDIAN     */

    /* co1 & si1 are read from SIMD Coefficient pointer */
    C1 = _SIMD32_OFFSET(pCoef16 + (2u * ic));
    /*  Butterfly process for the i0+fftLen/2 sample */

#ifndef ARM_MATH_BIG_ENDIAN

    /* xb' = (xa+yb-xc-yd)* co1 + (ya-xb-yc+xd)* (si1) */
    out1 = __SMUSD(C1, S) >> 16u;
    /* yb' = (ya-xb-yc+xd)* co1 - (xa+yb-xc-yd)* (si1) */
    out2 = __SMUADX(C1, S);

#else

    /* xb' = (ya-xb-yc+xd)* co1 - (xa+yb-xc-yd)* (si1) */
    out1 = __SMUADX(C1, S) >> 16u;
    /* yb' = (xa+yb-xc-yd)* co1 + (ya-xb-yc+xd)* (si1) */
    out2 = __SMUSD(__QSUB16(0, C1), S);

#endif /*      #ifndef ARM_MATH_BIG_ENDIAN     */

    /* writing output(xb', yb') in little endian format */
    _SIMD32_OFFSET(pSrc16 + (2u * i2)) =
      ((out2) & 0xFFFF0000) | ((out1) & 0x0000FFFF);


    /* co3 & si3 are read from SIMD Coefficient pointer */
    C3 = _SIMD32_OFFSET(pCoef16 + (6u * ic));
    /*  Butterfly process for the i0+3fftLen/4 sample */

#ifndef ARM_MATH_BIG_ENDIAN

    /* xd' = (xa-yb-xc+yd)* co3 + (ya+xb-yc-xd)* (si3) */
    out1 = __SMUSD(C3, R) >> 16u;
    /* yd' = (ya+xb-yc-xd)* co3 - (xa-yb-xc+yd)* (si3) */
    out2 = __SMUADX(C3, R);

#else

    /* xd' = (ya+xb-yc-xd)* co3 - (xa-yb-xc+yd)* (si3) */
    out1 = __SMUADX(C3, R) >> 16u;
    /* yd' = (xa-yb-xc+yd)* co3 + (ya+xb-yc-xd)* (si3) */
    out2 = __SMUSD(__QSUB16(0, C3), R);

#endif /*      #ifndef ARM_MATH_BIG_ENDIAN     */

    /* writing output(xd', yd') in little endian format */
    _SIMD32_OFFSET(pSrc16 + (2u * i3)) =
      ((out2) & 0xFFFF0000) | (out1 & 0x0000FFFF);

    /*  Twiddle coefficients index modifier */
    ic = ic + twidCoefModifier;

    /*  Updating input index */
    i0 = i0 + 1u;

  } while(--j);
  /* data is in 4.11(q11) format */

  /* end of first stage process */


  /* start of middle stage process */

  /*  Twiddle coefficients index modifier */
  twidCoefModifier <<= 2u;

  /*  Calculation of Middle stage */
  for (k = fftLen / 4u; k > 4u; k >>= 2u)
  {
    /*  Initializations for the middle stage */
    n1 = n2;
    n2 >>= 2u;
    ic = 0u;

    for (j = 0u; j <= (n2 - 1u); j++)
    {
      /*  index calculation for the coefficients */
      C1 = _SIMD32_OFFSET(pCoef16 + (2u * ic));
      C2 = _SIMD32_OFFSET(pCoef16 + (4u * ic));
      C3 = _SIMD32_OFFSET(pCoef16 + (6u * ic));

      /*  Twiddle coefficients index modifier */
      ic = ic + twidCoefModifier;

      /*  Butterfly implementation */
      for (i0 = j; i0 < fftLen; i0 += n1)
      {
        /*  index calculation for the input as, */
        /*  pSrc16[i0 + 0], pSrc16[i0 + fftLen/4], pSrc16[i0 + fftLen/2], pSrc16[i0 + 3fftLen/4] */
        i1 = i0 + n2;
        i2 = i1 + n2;
        i3 = i2 + n2;

        /*  Reading i0, i0+fftLen/2 inputs */
        /* Read ya (real), xa(imag) input */
        T = _SIMD32_OFFSET(pSrc16 + (2u * i0));

        /* Read yc (real), xc(imag) input */
        S = _SIMD32_OFFSET(pSrc16 + (2u * i2));

        /* R = packed( (ya + yc), (xa + xc)) */
        R = __QADD16(T, S);

        /* S = packed((ya - yc), (xa - xc)) */
        S = __QSUB16(T, S);

        /*  Reading i0+fftLen/4 , i0+3fftLen/4 inputs */
        /* Read yb (real), xb(imag) input */
        T = _SIMD32_OFFSET(pSrc16 + (2u * i1));

        /* Read yd (real), xd(imag) input */
        U = _SIMD32_OFFSET(pSrc16 + (2u * i3));

        /* T = packed( (yb + yd), (xb + xd)) */
        T = __QADD16(T, U);

        /*  writing the butterfly processed i0 sample */

        /* xa' = xa + xb + xc + xd */
        /* ya' = ya + yb + yc + yd */
        out1 = __SHADD16(R, T);
        in = ((int16_t) (out1 & 0xFFFF)) >> 1;
        out1 = ((out1 >> 1) & 0xFFFF0000) | (in & 0xFFFF);
        _SIMD32_OFFSET(pSrc16 + (2u * i0)) = out1;

        /* R = packed( (ya + yc) - (yb + yd), (xa + xc) - (xb + xd)) */
        R = __SHSUB16(R, T);

#ifndef ARM_MATH_BIG_ENDIAN

        /* (ya-yb+yc-yd)* (si2) + (xa-xb+xc-xd)* co2 */
        out1 = __SMUSD(C2, R) >> 16u;

        /* (ya-yb+yc-yd)* co2 - (xa-xb+xc-xd)* (si2) */
        out2 = __SMUADX(C2, R);

#else

        /* (ya-yb+yc-yd)* co2 - (xa-xb+xc-xd)* (si2) */
        out1 = __SMUADX(R, C2) >> 16u;

        /* (ya-yb+yc-yd)* (si2) + (xa-xb+xc-xd)* co2 */
        out2 = __SMUSD(__QSUB16(0, C2), R);

#endif /*      #ifndef ARM_MATH_BIG_ENDIAN     */

        /*  Reading i0+3fftLen/4 */
        /* Read yb (real), xb(imag) input */
        T = _SIMD32_OFFSET(pSrc16 + (2u * i1));

        /*  writing the butterfly processed i0 + fftLen/4 sample */
        /* xc' = (xa-xb+xc-xd)* co2 + (ya-yb+yc-yd)* (si2) */
        /* yc' = (ya-yb+yc-yd)* co2 - (xa-xb+xc-xd)* (si2) */
        _SIMD32_OFFSET(pSrc16 + (2u * i1)) =
          ((out2) & 0xFFFF0000) | (out1 & 0x0000FFFF);

        /*  Butterfly calculations */

        /* Read yd (real), xd(imag) input */
        U = _SIMD32_OFFSET(pSrc16 + (2u * i3));

        /* T = packed(yb-yd, xb-xd) */
        T = __QSUB16(T, U);

#ifndef ARM_MATH_BIG_ENDIAN

        /* R = packed((ya-yc) + (xb- xd) , (xa-xc) - (yb-yd)) */
        R = __SHSAX(S, T);

        /* S = packed((ya-yc) - (xb- xd),  (xa-xc) + (yb-yd)) */
        S = __SHASX(S, T);


        /*  Butterfly process for the i0+fftLen/2 sample */
        out1 = __SMUSD(C1, S) >> 16u;
        out2 = __SMUADX(C1, S);

#else

        /* R = packed((ya-yc) + (xb- xd) , (xa-xc) - (yb-yd)) */
        R = __SHASX(S, T);

        /* S = packed((ya-yc) - (xb- xd),  (xa-xc) + (yb-yd)) */
        S = __SHSAX(S, T);


        /*  Butterfly process for the i0+fftLen/2 sample */
        out1 = __SMUADX(S, C1) >> 16u;
        out2 = __SMUSD(__QSUB16(0, C1), S);

#endif /*      #ifndef ARM_MATH_BIG_ENDIAN     */

        /* xb' = (xa+yb-xc-yd)* co1 + (ya-xb-yc+xd)* (si1) */
        /* yb' = (ya-xb-yc+xd)* co1 - (xa+yb-xc-yd)* (si1) */
        _SIMD32_OFFSET(pSrc16 + (2u * i2)) =
          ((out2) & 0xFFFF0000) | (out1 & 0x0000FFFF);

        /*  Butterfly process for the i0+3fftLen/4 sample */

#ifndef ARM_MATH_BIG_ENDIAN

        out1 = __SMUSD(C3, R) >> 16u;
        out2 = __SMUADX(C3, R);

#else

        out1 = __SMUADX(C3, R) >> 16u;
        out2 = __SMUSD(__QSUB16(0, C3), R);

#endif /*      #ifndef ARM_MATH_BIG_ENDIAN     */

        /* xd' = (xa-yb-xc+yd)* co3 + (ya+xb-yc-xd)* (si3) */
        /* yd' = (ya+xb-yc-xd)* co3 - (xa-yb-xc+yd)* (si3) */
        _SIMD32_OFFSET(pSrc16 + (2u * i3)) =
          ((out2) & 0xFFFF0000) | (out1 & 0x0000FFFF);
      }
    }
    /*  Twiddle coefficients index modifier */
    twidCoefModifier <<= 2u;
  }
  /* end of middle stage process */

  /* data is in 10.6(q6) format for the 1024 point */
  /* data is in 8.8(q8) format for the 256 point */
  /* data is in 6.10(q10) format for the 64 point */
  /* data is in 4.12(q12) format for the 16 point */

  /*  Initializations for the last stage */
  j = fftLen >> 2;

  ptr1 = &pSrc16[0];

  /* start of last stage process */

  /*  Butterfly implementation */
  do
  {
    /* Read xa (real), ya(imag) input */
    xaya = *__SIMD32(ptr1)++;

    /* Read xb (real), yb(imag) input */
    xbyb = *__SIMD32(ptr1)++;

    /* Read xc (real), yc(imag) input */
    xcyc = *__SIMD32(ptr1)++;

    /* Read xd (real), yd(imag) input */
    xdyd = *__SIMD32(ptr1)++;

    /* R = packed((ya + yc), (xa + xc)) */
    R = __QADD16(xaya, xcyc);

    /* T = packed((yb + yd), (xb + xd)) */
    T = __QADD16(xbyb, xdyd);

    /* pointer updation for writing */
    ptr1 = ptr1 - 8u;


    /* xa' = xa + xb + xc + xd */
    /* ya' = ya + yb + yc + yd */
    *__SIMD32(ptr1)++ = __SHADD16(R, T);

    /* T = packed((yb + yd), (xb + xd)) */
    T = __QADD16(xbyb, xdyd);

    /* xc' = (xa-xb+xc-xd) */
    /* yc' = (ya-yb+yc-yd) */
    *__SIMD32(ptr1)++ = __SHSUB16(R, T);

    /* S = packed((ya - yc), (xa - xc)) */
    S = __QSUB16(xaya, xcyc);

    /* Read yd (real), xd(imag) input */
    /* T = packed( (yb - yd), (xb - xd))  */
    U = __QSUB16(xbyb, xdyd);

#ifndef ARM_MATH_BIG_ENDIAN

    /* xb' = (xa+yb-xc-yd) */
    /* yb' = (ya-xb-yc+xd) */
    *__SIMD32(ptr1)++ = __SHASX(S, U);


    /* xd' = (xa-yb-xc+yd) */
    /* yd' = (ya+xb-yc-xd) */
    *__SIMD32(ptr1)++ = __SHSAX(S, U);

#else

    /* xb' = (xa+yb-xc-yd) */
    /* yb' = (ya-xb-yc+xd) */
    *__SIMD32(ptr1)++ = __SHSAX(S, U);


    /* xd' = (xa-yb-xc+yd) */
    /* yd' = (ya+xb-yc-xd) */
    *__SIMD32(ptr1)++ = __SHASX(S, U);


#endif /*      #ifndef ARM_MATH_BIG_ENDIAN     */

  } while(--j);

  /* end of last stage  process */

  /* output is in 11.5(q5) format for the 1024 point */
  /* output is in 9.7(q7) format for the 256 point   */
  /* output is in 7.9(q9) format for the 64 point  */
  /* output is in 5.11(q11) format for the 16 point  */


#else

  /* Run the below code for Cortex-M0 */

  q15_t R0, R1, S0, S1, T0, T1, U0, U1;
  q15_t Co1, Si1, Co2, Si2, Co3, Si3, out1, out2;
  uint32_t n1, n2, ic, i0, i1, i2, i3, j, k;

  /* Total process is divided into three stages */

  /* process first stage, middle stages, & last stage */

  /*  Initializations for the first stage */
  n2 = fftLen;
  n1 = n2;

  /* n2 = fftLen/4 */
  n2 >>= 2u;

  /* Index for twiddle coefficient */
  ic = 0u;

  /* Index for input read and output write */
  i0 = 0u;

  j = n2;

  /* Input is in 1.15(q15) format */

  /*  Start of first stage process */
  do
  {
    /*  Butterfly implementation */

    /*  index calculation for the input as, */
    /*  pSrc16[i0 + 0], pSrc16[i0 + fftLen/4], pSrc16[i0 + fftLen/2], pSrc16[i0 + 3fftLen/4] */
    i1 = i0 + n2;
    i2 = i1 + n2;
    i3 = i2 + n2;

    /*  Reading i0, i0+fftLen/2 inputs */
    /* input is down scale by 4 to avoid overflow */
    /* Read ya (real), xa(imag) input */
    T0 = pSrc16[i0 * 2u] >> 2u;
    T1 = pSrc16[(i0 * 2u) + 1u] >> 2u;
    /* input is down scale by 4 to avoid overflow */
    /* Read yc (real), xc(imag) input */
    S0 = pSrc16[i2 * 2u] >> 2u;
    S1 = pSrc16[(i2 * 2u) + 1u] >> 2u;

    /* R0 = (ya + yc), R1 = (xa + xc) */
    R0 = __SSAT(T0 + S0, 16u);
    R1 = __SSAT(T1 + S1, 16u);
    /* S0 = (ya - yc), S1 = (xa - xc) */
    S0 = __SSAT(T0 - S0, 16u);
    S1 = __SSAT(T1 - S1, 16u);

    /*  Reading i0+fftLen/4 , i0+3fftLen/4 inputs */
    /* input is down scale by 4 to avoid overflow */
    /* Read yb (real), xb(imag) input */
    T0 = pSrc16[i1 * 2u] >> 2u;
    T1 = pSrc16[(i1 * 2u) + 1u] >> 2u;
    /* Read yd (real), xd(imag) input */
    /* input is down scale by 4 to avoid overflow */
    U0 = pSrc16[i3 * 2u] >> 2u;
    U1 = pSrc16[(i3 * 2u) + 1u] >> 2u;

    /* T0 = (yb + yd), T1 = (xb + xd) */
    T0 = __SSAT(T0 + U0, 16u);
    T1 = __SSAT(T1 + U1, 16u);

    /*  writing the butterfly processed i0 sample */
    /* xa' = xa + xb + xc + xd */
    /* ya' = ya + yb + yc + yd */
    pSrc16[i0 * 2u] = (R0 >> 1u) + (T0 >> 1u);
    pSrc16[(i0 * 2u) + 1u] = (R1 >> 1u) + (T1 >> 1u);

    /* R0 = (ya + yc) - (yb + yd), R1 = (xa + xc)- (xb + xd) */
    R0 = __SSAT(R0 - T0, 16u);
    R1 = __SSAT(R1 - T1, 16u);
    /* co2 & si2 are read from Coefficient pointer */
    Co2 = pCoef16[2u * ic * 2u];
    Si2 = pCoef16[(2u * ic * 2u) + 1u];
    /* xc' = (xa-xb+xc-xd)* co2 - (ya-yb+yc-yd)* (si2) */
    out1 = (short) ((Co2 * R0 - Si2 * R1) >> 16u);
    /* yc' = (ya-yb+yc-yd)* co2 + (xa-xb+xc-xd)* (si2) */
    out2 = (short) ((Si2 * R0 + Co2 * R1) >> 16u);

    /*  Reading i0+fftLen/4 */
    /* input is down scale by 4 to avoid overflow */
    /* T0 = yb, T1 = xb */
    T0 = pSrc16[i1 * 2u] >> 2u;
    T1 = pSrc16[(i1 * 2u) + 1u] >> 2u;

    /* writing the butterfly processed i0 + fftLen/4 sample */
    /* writing output(xc', yc') in little endian format */
    pSrc16[i1 * 2u] = out1;
    pSrc16[(i1 * 2u) + 1u] = out2;

    /*  Butterfly calculations */
    /* input is down scale by 4 to avoid overflow */
    /* U0 = yd, U1 = xd) */
    U0 = pSrc16[i3 * 2u] >> 2u;
    U1 = pSrc16[(i3 * 2u) + 1u] >> 2u;

    /* T0 = yb-yd, T1 = xb-xd) */
    T0 = __SSAT(T0 - U0, 16u);
    T1 = __SSAT(T1 - U1, 16u);
    /* R0 = (ya-yc) - (xb- xd) , R1 = (xa-xc) + (yb-yd) */
    R0 = (short) __SSAT((q31_t) (S0 + T1), 16);
    R1 = (short) __SSAT((q31_t) (S1 - T0), 16);
    /* S = (ya-yc) + (xb- xd), S1 = (xa-xc) - (yb-yd) */
    S0 = (short) __SSAT((q31_t) (S0 - T1), 16);
    S1 = (short) __SSAT((q31_t) (S1 + T0), 16);

    /* co1 & si1 are read from Coefficient pointer */
    Co1 = pCoef16[ic * 2u];
    Si1 = pCoef16[(ic * 2u) + 1u];
    /*  Butterfly process for the i0+fftLen/2 sample */
    /* xb' = (xa-yb-xc+yd)* co1 - (ya+xb-yc-xd)* (si1) */
    out1 = (short) ((Co1 * S0 - Si1 * S1) >> 16u);
    /* yb' = (ya+xb-yc-xd)* co1 + (xa-yb-xc+yd)* (si1) */
    out2 = (short) ((Si1 * S0 + Co1 * S1) >> 16u);
    /* writing output(xb', yb') in little endian format */
    pSrc16[i2 * 2u] = out1;
    pSrc16[(i2 * 2u) + 1u] = out2;

    /* Co3 & si3 are read from Coefficient pointer */
    Co3 = pCoef16[3u * ic * 2u];
    Si3 = pCoef16[(3u * ic * 2u) + 1u];
    /*  Butterfly process for the i0+3fftLen/4 sample */
    /* xd' = (xa+yb-xc-yd)* Co3 - (ya-xb-yc+xd)* (si3) */
    out1 = (short) ((Co3 * R0 - Si3 * R1) >> 16u);
    /* yd' = (ya-xb-yc+xd)* Co3 + (xa+yb-xc-yd)* (si3) */
    out2 = (short) ((Si3 * R0 + Co3 * R1) >> 16u);
    /* writing output(xd', yd') in little endian format */
    pSrc16[i3 * 2u] = out1;
    pSrc16[(i3 * 2u) + 1u] = out2;

    /*  Twiddle coefficients index modifier */
    ic = ic + twidCoefModifier;

    /*  Updating input index */
    i0 = i0 + 1u;

  } while(--j);

  /*  End of first stage process */

  /* data is in 4.11(q11) format */


  /*  Start of Middle stage process */

  /*  Twiddle coefficients index modifier */
  twidCoefModifier <<= 2u;

  /*  Calculation of Middle stage */
  for (k = fftLen / 4u; k > 4u; k >>= 2u)
  {
    /*  Initializations for the middle stage */
    n1 = n2;
    n2 >>= 2u;
    ic = 0u;

    for (j = 0u; j <= (n2 - 1u); j++)
    {
      /*  index calculation for the coefficients */
      Co1 = pCoef16[ic * 2u];
      Si1 = pCoef16[(ic * 2u) + 1u];
      Co2 = pCoef16[2u * ic * 2u];
      Si2 = pCoef16[2u * ic * 2u + 1u];
      Co3 = pCoef16[3u * ic * 2u];
      Si3 = pCoef16[(3u * ic * 2u) + 1u];

      /*  Twiddle coefficients index modifier */
      ic = ic + twidCoefModifier;

      /*  Butterfly implementation */
      for (i0 = j; i0 < fftLen; i0 += n1)
      {
        /*  index calculation for the input as, */
        /*  pSrc16[i0 + 0], pSrc16[i0 + fftLen/4], pSrc16[i0 + fftLen/2], pSrc16[i0 + 3fftLen/4] */
        i1 = i0 + n2;
        i2 = i1 + n2;
        i3 = i2 + n2;

        /*  Reading i0, i0+fftLen/2 inputs */
        /* Read ya (real), xa(imag) input */
        T0 = pSrc16[i0 * 2u];
        T1 = pSrc16[(i0 * 2u) + 1u];

        /* Read yc (real), xc(imag) input */
        S0 = pSrc16[i2 * 2u];
        S1 = pSrc16[(i2 * 2u) + 1u];


        /* R0 = (ya + yc), R1 = (xa + xc) */
        R0 = __SSAT(T0 + S0, 16u);
        R1 = __SSAT(T1 + S1, 16u);
        /* S0 = (ya - yc), S1 = (xa - xc) */
        S0 = __SSAT(T0 - S0, 16u);
        S1 = __SSAT(T1 - S1, 16u);

        /*  Reading i0+fftLen/4 , i0+3fftLen/4 inputs */
        /* Read yb (real), xb(imag) input */
        T0 = pSrc16[i1 * 2u];
        T1 = pSrc16[(i1 * 2u) + 1u];

        /* Read yd (real), xd(imag) input */
        U0 = pSrc16[i3 * 2u];
        U1 = pSrc16[(i3 * 2u) + 1u];

        /* T0 = (yb + yd), T1 = (xb + xd) */
        T0 = __SSAT(T0 + U0, 16u);
        T1 = __SSAT(T1 + U1, 16u);

        /*  writing the butterfly processed i0 sample */
        /* xa' = xa + xb + xc + xd */
        /* ya' = ya + yb + yc + yd */
        pSrc16[i0 * 2u] = ((R0 >> 1u) + (T0 >> 1u)) >> 1u;
        pSrc16[(i0 * 2u) + 1u] = ((R1 >> 1u) + (T1 >> 1u)) >> 1u;

        /* R0 = (ya + yc) - (yb + yd), R1 = (xa + xc) - (xb + xd) */
        R0 = (R0 >> 1u) - (T0 >> 1u);
        R1 = (R1 >> 1u) - (T1 >> 1u);

        /* (ya-yb+yc-yd)* (si2) - (xa-xb+xc-xd)* co2 */
        out1 = (short) ((Co2 * R0 - Si2 * R1) >> 16);
        /* (ya-yb+yc-yd)* co2 + (xa-xb+xc-xd)* (si2) */
        out2 = (short) ((Si2 * R0 + Co2 * R1) >> 16);

        /*  Reading i0+3fftLen/4 */
        /* Read yb (real), xb(imag) input */
        T0 = pSrc16[i1 * 2u];
        T1 = pSrc16[(i1 * 2u) + 1u];

        /*  writing the butterfly processed i0 + fftLen/4 sample */
        /* xc' = (xa-xb+xc-xd)* co2 - (ya-yb+yc-yd)* (si2) */
        /* yc' = (ya-yb+yc-yd)* co2 + (xa-xb+xc-xd)* (si2) */
        pSrc16[i1 * 2u] = out1;
        pSrc16[(i1 * 2u) + 1u] = out2;

        /*  Butterfly calculations */
        /* Read yd (real), xd(imag) input */
        U0 = pSrc16[i3 * 2u];
        U1 = pSrc16[(i3 * 2u) + 1u];

        /* T0 = yb-yd, T1 = xb-xd) */
        T0 = __SSAT(T0 - U0, 16u);
        T1 = __SSAT(T1 - U1, 16u);

        /* R0 = (ya-yc) - (xb- xd) , R1 = (xa-xc) + (yb-yd) */
        R0 = (S0 >> 1u) + (T1 >> 1u);
        R1 = (S1 >> 1u) - (T0 >> 1u);

        /* S1 = (ya-yc) + (xb- xd), S1 = (xa-xc) - (yb-yd) */
        S0 = (S0 >> 1u) - (T1 >> 1u);
        S1 = (S1 >> 1u) + (T0 >> 1u);

        /*  Butterfly process for the i0+fftLen/2 sample */
        out1 = (short) ((Co1 * S0 - Si1 * S1) >> 16u);
        out2 = (short) ((Si1 * S0 + Co1 * S1) >> 16u);
        /* xb' = (xa-yb-xc+yd)* co1 - (ya+xb-yc-xd)* (si1) */
        /* yb' = (ya+xb-yc-xd)* co1 + (xa-yb-xc+yd)* (si1) */
        pSrc16[i2 * 2u] = out1;
        pSrc16[(i2 * 2u) + 1u] = out2;

        /*  Butterfly process for the i0+3fftLen/4 sample */
        out1 = (short) ((Co3 * R0 - Si3 * R1) >> 16u);

        out2 = (short) ((Si3 * R0 + Co3 * R1) >> 16u);
        /* xd' = (xa+yb-xc-yd)* Co3 - (ya-xb-yc+xd)* (si3) */
        /* yd' = (ya-xb-yc+xd)* Co3 + (xa+yb-xc-yd)* (si3) */
        pSrc16[i3 * 2u] = out1;
        pSrc16[(i3 * 2u) + 1u] = out2;


      }
    }
    /*  Twiddle coefficients index modifier */
    twidCoefModifier <<= 2u;
  }
  /*  End of Middle stages process */


  /* data is in 10.6(q6) format for the 1024 point */
  /* data is in 8.8(q8) format for the 256 point   */
  /* data is in 6.10(q10) format for the 64 point  */
  /* data is in 4.12(q12) format for the 16 point  */

  /* start of last stage process */


  /*  Initializations for the last stage */
  n1 = n2;
  n2 >>= 2u;

  /*  Butterfly implementation */
  for (i0 = 0u; i0 <= (fftLen - n1); i0 += n1)
  {
    /*  index calculation for the input as, */
    /*  pSrc16[i0 + 0], pSrc16[i0 + fftLen/4], pSrc16[i0 + fftLen/2], pSrc16[i0 + 3fftLen/4] */
    i1 = i0 + n2;
    i2 = i1 + n2;
    i3 = i2 + n2;

    /*  Reading i0, i0+fftLen/2 inputs */
    /* Read ya (real), xa(imag) input */
    T0 = pSrc16[i0 * 2u];
    T1 = pSrc16[(i0 * 2u) + 1u];
    /* Read yc (real), xc(imag) input */
    S0 = pSrc16[i2 * 2u];
    S1 = pSrc16[(i2 * 2u) + 1u];

    /* R0 = (ya + yc), R1 = (xa + xc) */
    R0 = __SSAT(T0 + S0, 16u);
    R1 = __SSAT(T1 + S1, 16u);
    /* S0 = (ya - yc), S1 = (xa - xc) */
    S0 = __SSAT(T0 - S0, 16u);
    S1 = __SSAT(T1 - S1, 16u);

    /*  Reading i0+fftLen/4 , i0+3fftLen/4 inputs */
    /* Read yb (real), xb(imag) input */
    T0 = pSrc16[i1 * 2u];
    T1 = pSrc16[(i1 * 2u) + 1u];
    /* Read yd (real), xd(imag) input */
    U0 = pSrc16[i3 * 2u];
    U1 = pSrc16[(i3 * 2u) + 1u];

    /* T0 = (yb + yd), T1 = (xb + xd) */
    T0 = __SSAT(T0 + U0, 16u);
    T1 = __SSAT(T1 + U1, 16u);

    /*  writing the butterfly processed i0 sample */
    /* xa' = xa + xb + xc + xd */
    /* ya' = ya + yb + yc + yd */
    pSrc16[i0 * 2u] = (R0 >> 1u) + (T0 >> 1u);
    pSrc16[(i0 * 2u) + 1u] = (R1 >> 1u) + (T1 >> 1u);

    /* R0 = (ya + yc) - (yb + yd), R1 = (xa + xc) - (xb + xd) */
    R0 = (R0 >> 1u) - (T0 >> 1u);
    R1 = (R1 >> 1u) - (T1 >> 1u);

    /* Read yb (real), xb(imag) input */
    T0 = pSrc16[i1 * 2u];
    T1 = pSrc16[(i1 * 2u) + 1u];

    /*  writing the butterfly processed i0 + fftLen/4 sample */
    /* xc' = (xa-xb+xc-xd) */
    /* yc' = (ya-yb+yc-yd) */
    pSrc16[i1 * 2u] = R0;
    pSrc16[(i1 * 2u) + 1u] = R1;

    /* Read yd (real), xd(imag) input */
    U0 = pSrc16[i3 * 2u];
    U1 = pSrc16[(i3 * 2u) + 1u];
    /* T0 = (yb - yd), T1 = (xb - xd) */
    T0 = __SSAT(T0 - U0, 16u);
    T1 = __SSAT(T1 - U1, 16u);

    /*  writing the butterfly processed i0 + fftLen/2 sample */
    /* xb' = (xa-yb-xc+yd) */
    /* yb' = (ya+xb-yc-xd) */
    pSrc16[i2 * 2u] = (S0 >> 1u) - (T1 >> 1u);
    pSrc16[(i2 * 2u) + 1u] = (S1 >> 1u) + (T0 >> 1u);


    /*  writing the butterfly processed i0 + 3fftLen/4 sample */
    /* xd' = (xa+yb-xc-yd) */
    /* yd' = (ya-xb-yc+xd) */
    pSrc16[i3 * 2u] = (S0 >> 1u) + (T1 >> 1u);
    pSrc16[(i3 * 2u) + 1u] = (S1 >> 1u) - (T0 >> 1u);
  }
  /* end of last stage  process */

  /* output is in 11.5(q5) format for the 1024 point */
  /* output is in 9.7(q7) format for the 256 point   */
  /* output is in 7.9(q9) format for the 64 point  */
  /* output is in 5.11(q11) format for the 16 point  */

#endif /* #ifndef ARM_MATH_CM0_FAMILY */

}
