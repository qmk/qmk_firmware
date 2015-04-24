/* ----------------------------------------------------------------------    
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.    
*    
* $Date:        17. January 2013
* $Revision: 	V1.4.1
*    
* Project: 	    CMSIS DSP Library    
* Title:		arm_correlate_opt_q15.c    
*    
* Description:	Correlation of Q15 sequences.  
*    
* Target Processor: Cortex-M4/Cortex-M3
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

/**    
 * @ingroup groupFilters    
 */

/**    
 * @addtogroup Corr    
 * @{    
 */

/**    
 * @brief Correlation of Q15 sequences.  
 * @param[in] *pSrcA points to the first input sequence.    
 * @param[in] srcALen length of the first input sequence.    
 * @param[in] *pSrcB points to the second input sequence.    
 * @param[in] srcBLen length of the second input sequence.    
 * @param[out] *pDst points to the location where the output result is written.  Length 2 * max(srcALen, srcBLen) - 1.    
 * @param[in]  *pScratch points to scratch buffer of size max(srcALen, srcBLen) + 2*min(srcALen, srcBLen) - 2.    
 * @return none.    
 *    
 * \par Restrictions    
 *  If the silicon does not support unaligned memory access enable the macro UNALIGNED_SUPPORT_DISABLE    
 *	In this case input, output, scratch buffers should be aligned by 32-bit    
 *     
 * @details    
 * <b>Scaling and Overflow Behavior:</b>    
 *    
 * \par    
 * The function is implemented using a 64-bit internal accumulator.    
 * Both inputs are in 1.15 format and multiplications yield a 2.30 result.    
 * The 2.30 intermediate results are accumulated in a 64-bit accumulator in 34.30 format.    
 * This approach provides 33 guard bits and there is no risk of overflow.    
 * The 34.30 result is then truncated to 34.15 format by discarding the low 15 bits and then saturated to 1.15 format.    
 *    
 * \par    
 * Refer to <code>arm_correlate_fast_q15()</code> for a faster but less precise version of this function for Cortex-M3 and Cortex-M4.   
 *  
 * 
 */


void arm_correlate_opt_q15(
  q15_t * pSrcA,
  uint32_t srcALen,
  q15_t * pSrcB,
  uint32_t srcBLen,
  q15_t * pDst,
  q15_t * pScratch)
{
  q15_t *pIn1;                                   /* inputA pointer               */
  q15_t *pIn2;                                   /* inputB pointer               */
  q63_t acc0, acc1, acc2, acc3;                  /* Accumulators                  */
  q15_t *py;                                     /* Intermediate inputB pointer  */
  q31_t x1, x2, x3;                              /* temporary variables for holding input1 and input2 values */
  uint32_t j, blkCnt, outBlockSize;              /* loop counter                 */
  int32_t inc = 1;                               /* output pointer increment     */
  uint32_t tapCnt;
  q31_t y1, y2;
  q15_t *pScr;                                   /* Intermediate pointers        */
  q15_t *pOut = pDst;                            /* output pointer               */
#ifdef UNALIGNED_SUPPORT_DISABLE

  q15_t a, b;

#endif	/*	#ifndef UNALIGNED_SUPPORT_DISABLE	*/

  /* The algorithm implementation is based on the lengths of the inputs. */
  /* srcB is always made to slide across srcA. */
  /* So srcBLen is always considered as shorter or equal to srcALen */
  /* But CORR(x, y) is reverse of CORR(y, x) */
  /* So, when srcBLen > srcALen, output pointer is made to point to the end of the output buffer */
  /* and the destination pointer modifier, inc is set to -1 */
  /* If srcALen > srcBLen, zero pad has to be done to srcB to make the two inputs of same length */
  /* But to improve the performance,        
   * we include zeroes in the output instead of zero padding either of the the inputs*/
  /* If srcALen > srcBLen,        
   * (srcALen - srcBLen) zeroes has to included in the starting of the output buffer */
  /* If srcALen < srcBLen,        
   * (srcALen - srcBLen) zeroes has to included in the ending of the output buffer */
  if(srcALen >= srcBLen)
  {
    /* Initialization of inputA pointer */
    pIn1 = (pSrcA);

    /* Initialization of inputB pointer */
    pIn2 = (pSrcB);

    /* Number of output samples is calculated */
    outBlockSize = (2u * srcALen) - 1u;

    /* When srcALen > srcBLen, zero padding is done to srcB        
     * to make their lengths equal.        
     * Instead, (outBlockSize - (srcALen + srcBLen - 1))        
     * number of output samples are made zero */
    j = outBlockSize - (srcALen + (srcBLen - 1u));

    /* Updating the pointer position to non zero value */
    pOut += j;

  }
  else
  {
    /* Initialization of inputA pointer */
    pIn1 = (pSrcB);

    /* Initialization of inputB pointer */
    pIn2 = (pSrcA);

    /* srcBLen is always considered as shorter or equal to srcALen */
    j = srcBLen;
    srcBLen = srcALen;
    srcALen = j;

    /* CORR(x, y) = Reverse order(CORR(y, x)) */
    /* Hence set the destination pointer to point to the last output sample */
    pOut = pDst + ((srcALen + srcBLen) - 2u);

    /* Destination address modifier is set to -1 */
    inc = -1;

  }

  pScr = pScratch;

  /* Fill (srcBLen - 1u) zeros in scratch buffer */
  arm_fill_q15(0, pScr, (srcBLen - 1u));

  /* Update temporary scratch pointer */
  pScr += (srcBLen - 1u);

#ifndef UNALIGNED_SUPPORT_DISABLE

  /* Copy (srcALen) samples in scratch buffer */
  arm_copy_q15(pIn1, pScr, srcALen);

  /* Update pointers */
  //pIn1 += srcALen;    
  pScr += srcALen;

#else

  /* Apply loop unrolling and do 4 Copies simultaneously. */
  j = srcALen >> 2u;

  /* First part of the processing with loop unrolling copies 4 data points at a time.       
   ** a second loop below copies for the remaining 1 to 3 samples. */
  while(j > 0u)
  {
    /* copy second buffer in reversal manner */
    *pScr++ = *pIn1++;
    *pScr++ = *pIn1++;
    *pScr++ = *pIn1++;
    *pScr++ = *pIn1++;

    /* Decrement the loop counter */
    j--;
  }

  /* If the count is not a multiple of 4, copy remaining samples here.       
   ** No loop unrolling is used. */
  j = srcALen % 0x4u;

  while(j > 0u)
  {
    /* copy second buffer in reversal manner for remaining samples */
    *pScr++ = *pIn1++;

    /* Decrement the loop counter */
    j--;
  }

#endif	/*	#ifndef UNALIGNED_SUPPORT_DISABLE	*/

#ifndef UNALIGNED_SUPPORT_DISABLE

  /* Fill (srcBLen - 1u) zeros at end of scratch buffer */
  arm_fill_q15(0, pScr, (srcBLen - 1u));

  /* Update pointer */
  pScr += (srcBLen - 1u);

#else

/* Apply loop unrolling and do 4 Copies simultaneously. */
  j = (srcBLen - 1u) >> 2u;

  /* First part of the processing with loop unrolling copies 4 data points at a time.       
   ** a second loop below copies for the remaining 1 to 3 samples. */
  while(j > 0u)
  {
    /* copy second buffer in reversal manner */
    *pScr++ = 0;
    *pScr++ = 0;
    *pScr++ = 0;
    *pScr++ = 0;

    /* Decrement the loop counter */
    j--;
  }

  /* If the count is not a multiple of 4, copy remaining samples here.       
   ** No loop unrolling is used. */
  j = (srcBLen - 1u) % 0x4u;

  while(j > 0u)
  {
    /* copy second buffer in reversal manner for remaining samples */
    *pScr++ = 0;

    /* Decrement the loop counter */
    j--;
  }

#endif	/*	#ifndef UNALIGNED_SUPPORT_DISABLE	*/

  /* Temporary pointer for scratch2 */
  py = pIn2;


  /* Actual correlation process starts here */
  blkCnt = (srcALen + srcBLen - 1u) >> 2;

  while(blkCnt > 0)
  {
    /* Initialze temporary scratch pointer as scratch1 */
    pScr = pScratch;

    /* Clear Accumlators */
    acc0 = 0;
    acc1 = 0;
    acc2 = 0;
    acc3 = 0;

    /* Read four samples from scratch1 buffer */
    x1 = *__SIMD32(pScr)++;

    /* Read next four samples from scratch1 buffer */
    x2 = *__SIMD32(pScr)++;

    tapCnt = (srcBLen) >> 2u;

    while(tapCnt > 0u)
    {

#ifndef UNALIGNED_SUPPORT_DISABLE

      /* Read four samples from smaller buffer */
      y1 = _SIMD32_OFFSET(pIn2);
      y2 = _SIMD32_OFFSET(pIn2 + 2u);

      acc0 = __SMLALD(x1, y1, acc0);

      acc2 = __SMLALD(x2, y1, acc2);

#ifndef ARM_MATH_BIG_ENDIAN
      x3 = __PKHBT(x2, x1, 0);
#else
      x3 = __PKHBT(x1, x2, 0);
#endif

      acc1 = __SMLALDX(x3, y1, acc1);

      x1 = _SIMD32_OFFSET(pScr);

      acc0 = __SMLALD(x2, y2, acc0);

      acc2 = __SMLALD(x1, y2, acc2);

#ifndef ARM_MATH_BIG_ENDIAN
      x3 = __PKHBT(x1, x2, 0);
#else
      x3 = __PKHBT(x2, x1, 0);
#endif

      acc3 = __SMLALDX(x3, y1, acc3);

      acc1 = __SMLALDX(x3, y2, acc1);

      x2 = _SIMD32_OFFSET(pScr + 2u);

#ifndef ARM_MATH_BIG_ENDIAN
      x3 = __PKHBT(x2, x1, 0);
#else
      x3 = __PKHBT(x1, x2, 0);
#endif

      acc3 = __SMLALDX(x3, y2, acc3);

#else	 

      /* Read four samples from smaller buffer */
	  a = *pIn2;
	  b = *(pIn2 + 1);

#ifndef ARM_MATH_BIG_ENDIAN
      y1 = __PKHBT(a, b, 16);
#else
      y1 = __PKHBT(b, a, 16);
#endif
	  
	  a = *(pIn2 + 2);
	  b = *(pIn2 + 3);
#ifndef ARM_MATH_BIG_ENDIAN
      y2 = __PKHBT(a, b, 16);
#else
      y2 = __PKHBT(b, a, 16);
#endif				

      acc0 = __SMLALD(x1, y1, acc0);

      acc2 = __SMLALD(x2, y1, acc2);

#ifndef ARM_MATH_BIG_ENDIAN
      x3 = __PKHBT(x2, x1, 0);
#else
      x3 = __PKHBT(x1, x2, 0);
#endif

      acc1 = __SMLALDX(x3, y1, acc1);

	  a = *pScr;
	  b = *(pScr + 1);

#ifndef ARM_MATH_BIG_ENDIAN
      x1 = __PKHBT(a, b, 16);
#else
      x1 = __PKHBT(b, a, 16);
#endif

      acc0 = __SMLALD(x2, y2, acc0);

      acc2 = __SMLALD(x1, y2, acc2);

#ifndef ARM_MATH_BIG_ENDIAN
      x3 = __PKHBT(x1, x2, 0);
#else
      x3 = __PKHBT(x2, x1, 0);
#endif

      acc3 = __SMLALDX(x3, y1, acc3);

      acc1 = __SMLALDX(x3, y2, acc1);

	  a = *(pScr + 2);
	  b = *(pScr + 3);

#ifndef ARM_MATH_BIG_ENDIAN
      x2 = __PKHBT(a, b, 16);
#else
      x2 = __PKHBT(b, a, 16);
#endif

#ifndef ARM_MATH_BIG_ENDIAN
      x3 = __PKHBT(x2, x1, 0);
#else
      x3 = __PKHBT(x1, x2, 0);
#endif

      acc3 = __SMLALDX(x3, y2, acc3);

#endif	/*	#ifndef UNALIGNED_SUPPORT_DISABLE	*/

      pIn2 += 4u;

      pScr += 4u;


      /* Decrement the loop counter */
      tapCnt--;
    }



    /* Update scratch pointer for remaining samples of smaller length sequence */
    pScr -= 4u;


    /* apply same above for remaining samples of smaller length sequence */
    tapCnt = (srcBLen) & 3u;

    while(tapCnt > 0u)
    {

      /* accumlate the results */
      acc0 += (*pScr++ * *pIn2);
      acc1 += (*pScr++ * *pIn2);
      acc2 += (*pScr++ * *pIn2);
      acc3 += (*pScr++ * *pIn2++);

      pScr -= 3u;

      /* Decrement the loop counter */
      tapCnt--;
    }

    blkCnt--;


    /* Store the results in the accumulators in the destination buffer. */
    *pOut = (__SSAT(acc0 >> 15u, 16));
    pOut += inc;
    *pOut = (__SSAT(acc1 >> 15u, 16));
    pOut += inc;
    *pOut = (__SSAT(acc2 >> 15u, 16));
    pOut += inc;
    *pOut = (__SSAT(acc3 >> 15u, 16));
    pOut += inc;

    /* Initialization of inputB pointer */
    pIn2 = py;

    pScratch += 4u;

  }


  blkCnt = (srcALen + srcBLen - 1u) & 0x3;

  /* Calculate correlation for remaining samples of Bigger length sequence */
  while(blkCnt > 0)
  {
    /* Initialze temporary scratch pointer as scratch1 */
    pScr = pScratch;

    /* Clear Accumlators */
    acc0 = 0;

    tapCnt = (srcBLen) >> 1u;

    while(tapCnt > 0u)
    {

      acc0 += (*pScr++ * *pIn2++);
      acc0 += (*pScr++ * *pIn2++);

      /* Decrement the loop counter */
      tapCnt--;
    }

    tapCnt = (srcBLen) & 1u;

    /* apply same above for remaining samples of smaller length sequence */
    while(tapCnt > 0u)
    {

      /* accumlate the results */
      acc0 += (*pScr++ * *pIn2++);

      /* Decrement the loop counter */
      tapCnt--;
    }

    blkCnt--;

    /* Store the result in the accumulator in the destination buffer. */
    *pOut = (q15_t) (__SSAT((acc0 >> 15), 16));

    pOut += inc;

    /* Initialization of inputB pointer */
    pIn2 = py;

    pScratch += 1u;

  }


}

/**    
 * @} end of Corr group    
 */
