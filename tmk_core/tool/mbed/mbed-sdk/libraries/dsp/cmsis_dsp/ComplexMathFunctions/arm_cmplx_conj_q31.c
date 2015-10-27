/* ----------------------------------------------------------------------    
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.    
*    
* $Date:        17. January 2013
* $Revision: 	V1.4.1
*    
* Project: 	    CMSIS DSP Library    
* Title:		arm_cmplx_conj_q31.c    
*    
* Description:	Q31 complex conjugate.    
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
* ---------------------------------------------------------------------------- */
#include "arm_math.h"

/**        
 * @ingroup groupCmplxMath        
 */

/**        
 * @addtogroup cmplx_conj        
 * @{        
 */

/**        
 * @brief  Q31 complex conjugate.        
 * @param  *pSrc points to the input vector        
 * @param  *pDst points to the output vector        
 * @param  numSamples number of complex samples in each vector        
 * @return none.        
 *        
 * <b>Scaling and Overflow Behavior:</b>        
 * \par        
 * The function uses saturating arithmetic.        
 * The Q31 value -1 (0x80000000) will be saturated to the maximum allowable positive value 0x7FFFFFFF.        
 */

void arm_cmplx_conj_q31(
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t numSamples)
{
  uint32_t blkCnt;                               /* loop counter */
  q31_t in;                                      /* Input value */

#ifndef ARM_MATH_CM0_FAMILY

  /* Run the below code for Cortex-M4 and Cortex-M3 */
  q31_t inR1, inR2, inR3, inR4;                  /* Temporary real variables */
  q31_t inI1, inI2, inI3, inI4;                  /* Temporary imaginary variables */

  /*loop Unrolling */
  blkCnt = numSamples >> 2u;

  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.        
   ** a second loop below computes the remaining 1 to 3 samples. */
  while(blkCnt > 0u)
  {
    /* C[0]+jC[1] = A[0]+ j (-1) A[1] */
    /* Calculate Complex Conjugate and then store the results in the destination buffer. */
    /* Saturated to 0x7fffffff if the input is -1(0x80000000) */
    /* read real input sample */
    inR1 = pSrc[0];
    /* store real input sample */
    pDst[0] = inR1;

    /* read imaginary input sample */
    inI1 = pSrc[1];

    /* read real input sample */
    inR2 = pSrc[2];
    /* store real input sample */
    pDst[2] = inR2;

    /* read imaginary input sample */
    inI2 = pSrc[3];

    /* negate imaginary input sample */
    inI1 = __QSUB(0, inI1);

    /* read real input sample */
    inR3 = pSrc[4];
    /* store real input sample */
    pDst[4] = inR3;

    /* read imaginary input sample */
    inI3 = pSrc[5];

    /* negate imaginary input sample */
    inI2 = __QSUB(0, inI2);

    /* read real input sample */
    inR4 = pSrc[6];
    /* store real input sample */
    pDst[6] = inR4;

    /* negate imaginary input sample */
    inI3 = __QSUB(0, inI3);

    /* store imaginary input sample */
    inI4 = pSrc[7];

    /* store imaginary input samples */
    pDst[1] = inI1;

    /* negate imaginary input sample */
    inI4 = __QSUB(0, inI4);

    /* store imaginary input samples */
    pDst[3] = inI2;

    /* increment source pointer by 8 to proecess next samples */
    pSrc += 8u;

    /* store imaginary input samples */
    pDst[5] = inI3;
    pDst[7] = inI4;

    /* increment destination pointer by 8 to process next samples */
    pDst += 8u;

    /* Decrement the loop counter */
    blkCnt--;
  }

  /* If the numSamples is not a multiple of 4, compute any remaining output samples here.        
   ** No loop unrolling is used. */
  blkCnt = numSamples % 0x4u;

#else

  /* Run the below code for Cortex-M0 */
  blkCnt = numSamples;


#endif /* #ifndef ARM_MATH_CM0_FAMILY */

  while(blkCnt > 0u)
  {
    /* C[0]+jC[1] = A[0]+ j (-1) A[1] */
    /* Calculate Complex Conjugate and then store the results in the destination buffer. */
    /* Saturated to 0x7fffffff if the input is -1(0x80000000) */
    *pDst++ = *pSrc++;
    in = *pSrc++;
    *pDst++ = (in == INT32_MIN) ? INT32_MAX : -in;

    /* Decrement the loop counter */
    blkCnt--;
  }
}

/**        
 * @} end of cmplx_conj group        
 */
