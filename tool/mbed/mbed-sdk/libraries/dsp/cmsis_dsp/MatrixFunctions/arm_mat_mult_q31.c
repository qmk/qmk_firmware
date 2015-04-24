/* ----------------------------------------------------------------------    
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.    
*    
* $Date:        17. January 2013 
* $Revision: 	V1.4.1
*    
* Project: 	    CMSIS DSP Library    
* Title:	    arm_mat_mult_q31.c    
*    
* Description:	 Q31 matrix multiplication.    
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
 * @ingroup groupMatrix    
 */

/**    
 * @addtogroup MatrixMult    
 * @{    
 */

/**    
 * @brief Q31 matrix multiplication    
 * @param[in]       *pSrcA points to the first input matrix structure    
 * @param[in]       *pSrcB points to the second input matrix structure    
 * @param[out]      *pDst points to output matrix structure    
 * @return     		The function returns either    
 * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.    
 *    
 * @details    
 * <b>Scaling and Overflow Behavior:</b>    
 *    
 * \par    
 * The function is implemented using an internal 64-bit accumulator.    
 * The accumulator has a 2.62 format and maintains full precision of the intermediate    
 * multiplication results but provides only a single guard bit. There is no saturation    
 * on intermediate additions. Thus, if the accumulator overflows it wraps around and    
 * distorts the result. The input signals should be scaled down to avoid intermediate    
 * overflows. The input is thus scaled down by log2(numColsA) bits    
 * to avoid overflows, as a total of numColsA additions are performed internally.    
 * The 2.62 accumulator is right shifted by 31 bits and saturated to 1.31 format to yield the final result.    
 *    
 * \par    
 * See <code>arm_mat_mult_fast_q31()</code> for a faster but less precise implementation of this function for Cortex-M3 and Cortex-M4.    
 *    
 */

arm_status arm_mat_mult_q31(
  const arm_matrix_instance_q31 * pSrcA,
  const arm_matrix_instance_q31 * pSrcB,
  arm_matrix_instance_q31 * pDst)
{
  q31_t *pIn1 = pSrcA->pData;                    /* input data matrix pointer A */
  q31_t *pIn2 = pSrcB->pData;                    /* input data matrix pointer B */
  q31_t *pInA = pSrcA->pData;                    /* input data matrix pointer A */
  q31_t *pOut = pDst->pData;                     /* output data matrix pointer */
  q31_t *px;                                     /* Temporary output data matrix pointer */
  q63_t sum;                                     /* Accumulator */
  uint16_t numRowsA = pSrcA->numRows;            /* number of rows of input matrix A    */
  uint16_t numColsB = pSrcB->numCols;            /* number of columns of input matrix B */
  uint16_t numColsA = pSrcA->numCols;            /* number of columns of input matrix A */

#ifndef ARM_MATH_CM0_FAMILY

  /* Run the below code for Cortex-M4 and Cortex-M3 */

  uint16_t col, i = 0u, j, row = numRowsA, colCnt;      /* loop counters */
  arm_status status;                             /* status of matrix multiplication */
  q31_t a0, a1, a2, a3, b0, b1, b2, b3;

#ifdef ARM_MATH_MATRIX_CHECK


  /* Check for matrix mismatch condition */
  if((pSrcA->numCols != pSrcB->numRows) ||
     (pSrcA->numRows != pDst->numRows) || (pSrcB->numCols != pDst->numCols))
  {
    /* Set status as ARM_MATH_SIZE_MISMATCH */
    status = ARM_MATH_SIZE_MISMATCH;
  }
  else
#endif /*    #ifdef ARM_MATH_MATRIX_CHECK    */

  {
    /* The following loop performs the dot-product of each row in pSrcA with each column in pSrcB */
    /* row loop */
    do
    {
      /* Output pointer is set to starting address of the row being processed */
      px = pOut + i;

      /* For every row wise process, the column loop counter is to be initiated */
      col = numColsB;

      /* For every row wise process, the pIn2 pointer is set    
       ** to the starting address of the pSrcB data */
      pIn2 = pSrcB->pData;

      j = 0u;

      /* column loop */
      do
      {
        /* Set the variable sum, that acts as accumulator, to zero */
        sum = 0;

        /* Initiate the pointer pIn1 to point to the starting address of pInA */
        pIn1 = pInA;

        /* Apply loop unrolling and compute 4 MACs simultaneously. */
        colCnt = numColsA >> 2;


        /* matrix multiplication */
        while(colCnt > 0u)
        {
          /* c(m,n) = a(1,1)*b(1,1) + a(1,2) * b(2,1) + .... + a(m,p)*b(p,n) */
          /* Perform the multiply-accumulates */
          b0 = *pIn2;
          pIn2 += numColsB;

          a0 = *pIn1++;
          a1 = *pIn1++;

          b1 = *pIn2;
          pIn2 += numColsB;
          b2 = *pIn2;
          pIn2 += numColsB;

          sum += (q63_t) a0 *b0;
          sum += (q63_t) a1 *b1;

          a2 = *pIn1++;
          a3 = *pIn1++;

          b3 = *pIn2;
          pIn2 += numColsB;

          sum += (q63_t) a2 *b2;
          sum += (q63_t) a3 *b3;

          /* Decrement the loop counter */
          colCnt--;
        }

        /* If the columns of pSrcA is not a multiple of 4, compute any remaining output samples here.    
         ** No loop unrolling is used. */
        colCnt = numColsA % 0x4u;

        while(colCnt > 0u)
        {
          /* c(m,n) = a(1,1)*b(1,1) + a(1,2) * b(2,1) + .... + a(m,p)*b(p,n) */
          /* Perform the multiply-accumulates */
          sum += (q63_t) * pIn1++ * *pIn2;
          pIn2 += numColsB;

          /* Decrement the loop counter */
          colCnt--;
        }

        /* Convert the result from 2.62 to 1.31 format and store in destination buffer */
        *px++ = (q31_t) (sum >> 31);

        /* Update the pointer pIn2 to point to the  starting address of the next column */
        j++;
        pIn2 = (pSrcB->pData) + j;

        /* Decrement the column loop counter */
        col--;

      } while(col > 0u);

#else

  /* Run the below code for Cortex-M0 */

  q31_t *pInB = pSrcB->pData;                    /* input data matrix pointer B */
  uint16_t col, i = 0u, row = numRowsA, colCnt;  /* loop counters */
  arm_status status;                             /* status of matrix multiplication */


#ifdef ARM_MATH_MATRIX_CHECK

  /* Check for matrix mismatch condition */
  if((pSrcA->numCols != pSrcB->numRows) ||
     (pSrcA->numRows != pDst->numRows) || (pSrcB->numCols != pDst->numCols))
  {
    /* Set status as ARM_MATH_SIZE_MISMATCH */
    status = ARM_MATH_SIZE_MISMATCH;
  }
  else
#endif /*    #ifdef ARM_MATH_MATRIX_CHECK    */

  {
    /* The following loop performs the dot-product of each row in pSrcA with each column in pSrcB */
    /* row loop */
    do
    {
      /* Output pointer is set to starting address of the row being processed */
      px = pOut + i;

      /* For every row wise process, the column loop counter is to be initiated */
      col = numColsB;

      /* For every row wise process, the pIn2 pointer is set          
       ** to the starting address of the pSrcB data */
      pIn2 = pSrcB->pData;

      /* column loop */
      do
      {
        /* Set the variable sum, that acts as accumulator, to zero */
        sum = 0;

        /* Initiate the pointer pIn1 to point to the starting address of pInA */
        pIn1 = pInA;

        /* Matrix A columns number of MAC operations are to be performed */
        colCnt = numColsA;

        /* matrix multiplication */
        while(colCnt > 0u)
        {
          /* c(m,n) = a(1,1)*b(1,1) + a(1,2) * b(2,1) + .... + a(m,p)*b(p,n) */
          /* Perform the multiply-accumulates */
          sum += (q63_t) * pIn1++ * *pIn2;
          pIn2 += numColsB;

          /* Decrement the loop counter */
          colCnt--;
        }

        /* Convert the result from 2.62 to 1.31 format and store in destination buffer */
        *px++ = (q31_t) (sum >> 31);

        /* Decrement the column loop counter */
        col--;

        /* Update the pointer pIn2 to point to the  starting address of the next column */
        pIn2 = pInB + (numColsB - col);

      } while(col > 0u);

#endif

      /* Update the pointer pInA to point to the  starting address of the next row */
      i = i + numColsB;
      pInA = pInA + numColsA;

      /* Decrement the row loop counter */
      row--;

    } while(row > 0u);

    /* set status as ARM_MATH_SUCCESS */
    status = ARM_MATH_SUCCESS;
  }
  /* Return to application */
  return (status);
}

/**    
 * @} end of MatrixMult group    
 */
