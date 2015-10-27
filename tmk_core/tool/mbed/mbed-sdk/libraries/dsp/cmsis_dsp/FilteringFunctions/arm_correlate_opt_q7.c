/* ----------------------------------------------------------------------    
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.    
*    
* $Date:        17. January 2013
* $Revision: 	V1.4.1
*    
* Project: 	    CMSIS DSP Library    
* Title:		arm_correlate_opt_q7.c    
*    
* Description:	Correlation of Q7 sequences.  
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
 * @brief Correlation of Q7 sequences.    
 * @param[in] *pSrcA points to the first input sequence.    
 * @param[in] srcALen length of the first input sequence.    
 * @param[in] *pSrcB points to the second input sequence.    
 * @param[in] srcBLen length of the second input sequence.    
 * @param[out] *pDst points to the location where the output result is written.  Length 2 * max(srcALen, srcBLen) - 1.    
 * @param[in]  *pScratch1 points to scratch buffer(of type q15_t) of size max(srcALen, srcBLen) + 2*min(srcALen, srcBLen) - 2.    
 * @param[in]  *pScratch2 points to scratch buffer (of type q15_t) of size min(srcALen, srcBLen).    
 * @return none.    
 *    
 *    
 * \par Restrictions    
 *  If the silicon does not support unaligned memory access enable the macro UNALIGNED_SUPPORT_DISABLE    
 *	In this case input, output, scratch1 and scratch2 buffers should be aligned by 32-bit     
 *        
 * @details    
 * <b>Scaling and Overflow Behavior:</b>    
 *    
 * \par    
 * The function is implemented using a 32-bit internal accumulator.    
 * Both the inputs are represented in 1.7 format and multiplications yield a 2.14 result.    
 * The 2.14 intermediate results are accumulated in a 32-bit accumulator in 18.14 format.    
 * This approach provides 17 guard bits and there is no risk of overflow as long as <code>max(srcALen, srcBLen)<131072</code>.    
 * The 18.14 result is then truncated to 18.7 format by discarding the low 7 bits and saturated to 1.7 format.  
 *  
 * 
 */



void arm_correlate_opt_q7(
  q7_t * pSrcA,
  uint32_t srcALen,
  q7_t * pSrcB,
  uint32_t srcBLen,
  q7_t * pDst,
  q15_t * pScratch1,
  q15_t * pScratch2)
{
  q7_t *pOut = pDst;                             /* output pointer                */
  q15_t *pScr1 = pScratch1;                      /* Temporary pointer for scratch */
  q15_t *pScr2 = pScratch2;                      /* Temporary pointer for scratch */
  q7_t *pIn1;                                    /* inputA pointer                */
  q7_t *pIn2;                                    /* inputB pointer                */
  q15_t *py;                                     /* Intermediate inputB pointer   */
  q31_t acc0, acc1, acc2, acc3;                  /* Accumulators                  */
  uint32_t j, k = 0u, blkCnt;                    /* loop counter                  */
  int32_t inc = 1;                               /* output pointer increment          */
  uint32_t outBlockSize;                         /* loop counter                  */
  q15_t x4;                                      /* Temporary input variable      */
  uint32_t tapCnt;                               /* loop counter                  */
  q31_t x1, x2, x3, y1;                          /* Temporary input variables     */

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


  /* Copy (srcBLen) samples in scratch buffer */
  k = srcBLen >> 2u;

  /* First part of the processing with loop unrolling copies 4 data points at a time.       
   ** a second loop below copies for the remaining 1 to 3 samples. */
  while(k > 0u)
  {
    /* copy second buffer in reversal manner */
    x4 = (q15_t) * pIn2++;
    *pScr2++ = x4;
    x4 = (q15_t) * pIn2++;
    *pScr2++ = x4;
    x4 = (q15_t) * pIn2++;
    *pScr2++ = x4;
    x4 = (q15_t) * pIn2++;
    *pScr2++ = x4;

    /* Decrement the loop counter */
    k--;
  }

  /* If the count is not a multiple of 4, copy remaining samples here.       
   ** No loop unrolling is used. */
  k = srcBLen % 0x4u;

  while(k > 0u)
  {
    /* copy second buffer in reversal manner for remaining samples */
    x4 = (q15_t) * pIn2++;
    *pScr2++ = x4;

    /* Decrement the loop counter */
    k--;
  }

  /* Fill (srcBLen - 1u) zeros in scratch buffer */
  arm_fill_q15(0, pScr1, (srcBLen - 1u));

  /* Update temporary scratch pointer */
  pScr1 += (srcBLen - 1u);

  /* Copy (srcALen) samples in scratch buffer */
  k = srcALen >> 2u;

  /* First part of the processing with loop unrolling copies 4 data points at a time.       
   ** a second loop below copies for the remaining 1 to 3 samples. */
  while(k > 0u)
  {
    /* copy second buffer in reversal manner */
    x4 = (q15_t) * pIn1++;
    *pScr1++ = x4;
    x4 = (q15_t) * pIn1++;
    *pScr1++ = x4;
    x4 = (q15_t) * pIn1++;
    *pScr1++ = x4;
    x4 = (q15_t) * pIn1++;
    *pScr1++ = x4;

    /* Decrement the loop counter */
    k--;
  }

  /* If the count is not a multiple of 4, copy remaining samples here.       
   ** No loop unrolling is used. */
  k = srcALen % 0x4u;

  while(k > 0u)
  {
    /* copy second buffer in reversal manner for remaining samples */
    x4 = (q15_t) * pIn1++;
    *pScr1++ = x4;

    /* Decrement the loop counter */
    k--;
  }

#ifndef UNALIGNED_SUPPORT_DISABLE

  /* Fill (srcBLen - 1u) zeros at end of scratch buffer */
  arm_fill_q15(0, pScr1, (srcBLen - 1u));

  /* Update pointer */
  pScr1 += (srcBLen - 1u);

#else

/* Apply loop unrolling and do 4 Copies simultaneously. */
  k = (srcBLen - 1u) >> 2u;

  /* First part of the processing with loop unrolling copies 4 data points at a time.       
   ** a second loop below copies for the remaining 1 to 3 samples. */
  while(k > 0u)
  {
    /* copy second buffer in reversal manner */
    *pScr1++ = 0;
    *pScr1++ = 0;
    *pScr1++ = 0;
    *pScr1++ = 0;

    /* Decrement the loop counter */
    k--;
  }

  /* If the count is not a multiple of 4, copy remaining samples here.       
   ** No loop unrolling is used. */
  k = (srcBLen - 1u) % 0x4u;

  while(k > 0u)
  {
    /* copy second buffer in reversal manner for remaining samples */
    *pScr1++ = 0;

    /* Decrement the loop counter */
    k--;
  }

#endif	/*	#ifndef UNALIGNED_SUPPORT_DISABLE	*/

  /* Temporary pointer for second sequence */
  py = pScratch2;

  /* Initialization of pScr2 pointer */
  pScr2 = pScratch2;

  /* Actual correlation process starts here */
  blkCnt = (srcALen + srcBLen - 1u) >> 2;

  while(blkCnt > 0)
  {
    /* Initialze temporary scratch pointer as scratch1 */
    pScr1 = pScratch1;

    /* Clear Accumlators */
    acc0 = 0;
    acc1 = 0;
    acc2 = 0;
    acc3 = 0;

    /* Read two samples from scratch1 buffer */
    x1 = *__SIMD32(pScr1)++;

    /* Read next two samples from scratch1 buffer */
    x2 = *__SIMD32(pScr1)++;

    tapCnt = (srcBLen) >> 2u;

    while(tapCnt > 0u)
    {

      /* Read four samples from smaller buffer */
      y1 = _SIMD32_OFFSET(pScr2);

      /* multiply and accumlate */
      acc0 = __SMLAD(x1, y1, acc0);
      acc2 = __SMLAD(x2, y1, acc2);

      /* pack input data */
#ifndef ARM_MATH_BIG_ENDIAN
      x3 = __PKHBT(x2, x1, 0);
#else
      x3 = __PKHBT(x1, x2, 0);
#endif

      /* multiply and accumlate */
      acc1 = __SMLADX(x3, y1, acc1);

      /* Read next two samples from scratch1 buffer */
      x1 = *__SIMD32(pScr1)++;

      /* pack input data */
#ifndef ARM_MATH_BIG_ENDIAN
      x3 = __PKHBT(x1, x2, 0);
#else
      x3 = __PKHBT(x2, x1, 0);
#endif

      acc3 = __SMLADX(x3, y1, acc3);

      /* Read four samples from smaller buffer */
      y1 = _SIMD32_OFFSET(pScr2 + 2u);

      acc0 = __SMLAD(x2, y1, acc0);

      acc2 = __SMLAD(x1, y1, acc2);

      acc1 = __SMLADX(x3, y1, acc1);

      x2 = *__SIMD32(pScr1)++;

#ifndef ARM_MATH_BIG_ENDIAN
      x3 = __PKHBT(x2, x1, 0);
#else
      x3 = __PKHBT(x1, x2, 0);
#endif

      acc3 = __SMLADX(x3, y1, acc3);

      pScr2 += 4u;


      /* Decrement the loop counter */
      tapCnt--;
    }



    /* Update scratch pointer for remaining samples of smaller length sequence */
    pScr1 -= 4u;


    /* apply same above for remaining samples of smaller length sequence */
    tapCnt = (srcBLen) & 3u;

    while(tapCnt > 0u)
    {

      /* accumlate the results */
      acc0 += (*pScr1++ * *pScr2);
      acc1 += (*pScr1++ * *pScr2);
      acc2 += (*pScr1++ * *pScr2);
      acc3 += (*pScr1++ * *pScr2++);

      pScr1 -= 3u;

      /* Decrement the loop counter */
      tapCnt--;
    }

    blkCnt--;

    /* Store the result in the accumulator in the destination buffer. */
    *pOut = (q7_t) (__SSAT(acc0 >> 7u, 8));
    pOut += inc;
    *pOut = (q7_t) (__SSAT(acc1 >> 7u, 8));
    pOut += inc;
    *pOut = (q7_t) (__SSAT(acc2 >> 7u, 8));
    pOut += inc;
    *pOut = (q7_t) (__SSAT(acc3 >> 7u, 8));
    pOut += inc;

    /* Initialization of inputB pointer */
    pScr2 = py;

    pScratch1 += 4u;

  }


  blkCnt = (srcALen + srcBLen - 1u) & 0x3;

  /* Calculate correlation for remaining samples of Bigger length sequence */
  while(blkCnt > 0)
  {
    /* Initialze temporary scratch pointer as scratch1 */
    pScr1 = pScratch1;

    /* Clear Accumlators */
    acc0 = 0;

    tapCnt = (srcBLen) >> 1u;

    while(tapCnt > 0u)
    {
      acc0 += (*pScr1++ * *pScr2++);
      acc0 += (*pScr1++ * *pScr2++);

      /* Decrement the loop counter */
      tapCnt--;
    }

    tapCnt = (srcBLen) & 1u;

    /* apply same above for remaining samples of smaller length sequence */
    while(tapCnt > 0u)
    {

      /* accumlate the results */
      acc0 += (*pScr1++ * *pScr2++);

      /* Decrement the loop counter */
      tapCnt--;
    }

    blkCnt--;

    /* Store the result in the accumulator in the destination buffer. */
    *pOut = (q7_t) (__SSAT(acc0 >> 7u, 8));

    pOut += inc;

    /* Initialization of inputB pointer */
    pScr2 = py;

    pScratch1 += 1u;

  }

}

/**    
 * @} end of Corr group    
 */
