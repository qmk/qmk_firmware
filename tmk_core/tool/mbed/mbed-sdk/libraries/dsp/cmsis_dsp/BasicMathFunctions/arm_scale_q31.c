/* ----------------------------------------------------------------------    
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.    
*    
* $Date:        17. January 2013
* $Revision: 	V1.4.1
*    
* Project: 	    CMSIS DSP Library    
* Title:		arm_scale_q31.c    
*    
* Description:	Multiplies a Q31 vector by a scalar.    
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

/**       
 * @ingroup groupMath       
 */

/**       
 * @addtogroup scale       
 * @{       
 */

/**       
 * @brief Multiplies a Q31 vector by a scalar.       
 * @param[in]       *pSrc points to the input vector       
 * @param[in]       scaleFract fractional portion of the scale value       
 * @param[in]       shift number of bits to shift the result by       
 * @param[out]      *pDst points to the output vector       
 * @param[in]       blockSize number of samples in the vector       
 * @return none.       
 *       
 * <b>Scaling and Overflow Behavior:</b>       
 * \par       
 * The input data <code>*pSrc</code> and <code>scaleFract</code> are in 1.31 format.       
 * These are multiplied to yield a 2.62 intermediate result and this is shifted with saturation to 1.31 format.       
 */

void arm_scale_q31(
  q31_t * pSrc,
  q31_t scaleFract,
  int8_t shift,
  q31_t * pDst,
  uint32_t blockSize)
{
  int8_t kShift = shift + 1;                     /* Shift to apply after scaling */
  int8_t sign = (kShift & 0x80);
  uint32_t blkCnt;                               /* loop counter */
  q31_t in, out;

#ifndef ARM_MATH_CM0_FAMILY

/* Run the below code for Cortex-M4 and Cortex-M3 */

  q31_t in1, in2, in3, in4;                      /* temporary input variables */
  q31_t out1, out2, out3, out4;                  /* temporary output variabels */


  /*loop Unrolling */
  blkCnt = blockSize >> 2u;

  if(sign == 0u)
  {
    /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.       
     ** a second loop below computes the remaining 1 to 3 samples. */
    while(blkCnt > 0u)
    {
      /* read four inputs from source */
      in1 = *pSrc;
      in2 = *(pSrc + 1);
      in3 = *(pSrc + 2);
      in4 = *(pSrc + 3);

      /* multiply input with scaler value */
      in1 = ((q63_t) in1 * scaleFract) >> 32;
      in2 = ((q63_t) in2 * scaleFract) >> 32;
      in3 = ((q63_t) in3 * scaleFract) >> 32;
      in4 = ((q63_t) in4 * scaleFract) >> 32;

      /* apply shifting */
      out1 = in1 << kShift;
      out2 = in2 << kShift;

      /* saturate the results. */
      if(in1 != (out1 >> kShift))
        out1 = 0x7FFFFFFF ^ (in1 >> 31);

      if(in2 != (out2 >> kShift))
        out2 = 0x7FFFFFFF ^ (in2 >> 31);

      out3 = in3 << kShift;
      out4 = in4 << kShift;

      *pDst = out1;
      *(pDst + 1) = out2;

      if(in3 != (out3 >> kShift))
        out3 = 0x7FFFFFFF ^ (in3 >> 31);

      if(in4 != (out4 >> kShift))
        out4 = 0x7FFFFFFF ^ (in4 >> 31);

      /* Store result destination */
      *(pDst + 2) = out3;
      *(pDst + 3) = out4;

      /* Update pointers to process next sampels */
      pSrc += 4u;
      pDst += 4u;

      /* Decrement the loop counter */
      blkCnt--;
    }

  }
  else
  {
    /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.       
     ** a second loop below computes the remaining 1 to 3 samples. */
    while(blkCnt > 0u)
    {
      /* read four inputs from source */
      in1 = *pSrc;
      in2 = *(pSrc + 1);
      in3 = *(pSrc + 2);
      in4 = *(pSrc + 3);

      /* multiply input with scaler value */
      in1 = ((q63_t) in1 * scaleFract) >> 32;
      in2 = ((q63_t) in2 * scaleFract) >> 32;
      in3 = ((q63_t) in3 * scaleFract) >> 32;
      in4 = ((q63_t) in4 * scaleFract) >> 32;

      /* apply shifting */
      out1 = in1 >> -kShift;
      out2 = in2 >> -kShift;

      out3 = in3 >> -kShift;
      out4 = in4 >> -kShift;

      /* Store result destination */
      *pDst = out1;
      *(pDst + 1) = out2;

      *(pDst + 2) = out3;
      *(pDst + 3) = out4;

      /* Update pointers to process next sampels */
      pSrc += 4u;
      pDst += 4u;

      /* Decrement the loop counter */
      blkCnt--;
    }
  }
  /* If the blockSize is not a multiple of 4, compute any remaining output samples here.       
   ** No loop unrolling is used. */
  blkCnt = blockSize % 0x4u;

#else

  /* Run the below code for Cortex-M0 */

  /* Initialize blkCnt with number of samples */
  blkCnt = blockSize;

#endif /* #ifndef ARM_MATH_CM0_FAMILY */

  if(sign == 0)
  {
	  while(blkCnt > 0u)
	  {
		/* C = A * scale */
		/* Scale the input and then store the result in the destination buffer. */
		in = *pSrc++;
		in = ((q63_t) in * scaleFract) >> 32;

		out = in << kShift;
		
		if(in != (out >> kShift))
			out = 0x7FFFFFFF ^ (in >> 31);

		*pDst++ = out;

		/* Decrement the loop counter */
		blkCnt--;
	  }
  }
  else
  {
	  while(blkCnt > 0u)
	  {
		/* C = A * scale */
		/* Scale the input and then store the result in the destination buffer. */
		in = *pSrc++;
		in = ((q63_t) in * scaleFract) >> 32;

		out = in >> -kShift;

		*pDst++ = out;

		/* Decrement the loop counter */
		blkCnt--;
	  }
  
  }
}

/**       
 * @} end of scale group       
 */
