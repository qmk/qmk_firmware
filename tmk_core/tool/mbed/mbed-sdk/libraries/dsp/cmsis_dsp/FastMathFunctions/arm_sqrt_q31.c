/* ----------------------------------------------------------------------     
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.  
*     
* $Date:        17. January 2013
* $Revision: 	V1.4.1
*     
* Project:      CMSIS DSP Library  
* Title:		arm_sqrt_q31.c     
*     
* Description:	Q31 square root function.    
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
#include "arm_common_tables.h"

/**     
 * @ingroup groupFastMath     
 */

/**     
 * @addtogroup SQRT     
 * @{     
 */

/**    
 * @brief Q31 square root function.    
 * @param[in]   in    input value.  The range of the input value is [0 +1) or 0x00000000 to 0x7FFFFFFF.    
 * @param[out]  *pOut square root of input value.    
 * @return The function returns ARM_MATH_SUCCESS if the input value is positive
 * and ARM_MATH_ARGUMENT_ERROR if the input is negative.  For
 * negative inputs, the function returns *pOut = 0.
 */

arm_status arm_sqrt_q31(
  q31_t in,
  q31_t * pOut)
{
  q31_t number, temp1, bits_val1, var1, signBits1, half;
  float32_t temp_float1;
  union
  {
      q31_t fracval;
      float32_t floatval;
  } tempconv;

  number = in;

  /* If the input is a positive number then compute the signBits. */
  if(number > 0)
  {
    signBits1 = __CLZ(number) - 1;

    /* Shift by the number of signBits1 */
    if((signBits1 % 2) == 0)
    {
      number = number << signBits1;
    }
    else
    {
      number = number << (signBits1 - 1);
    }

    /* Calculate half value of the number */
    half = number >> 1;
    /* Store the number for later use */
    temp1 = number;

    /*Convert to float */
    temp_float1 = number * 4.6566128731e-010f;
    /*Store as integer */
    tempconv.floatval = temp_float1;
    bits_val1 = tempconv.fracval;
    /* Subtract the shifted value from the magic number to give intial guess */
    bits_val1 = 0x5f3759df - (bits_val1 >> 1);  // gives initial guess  
    /* Store as float */
    tempconv.fracval = bits_val1;
    temp_float1 = tempconv.floatval;
    /* Convert to integer format */
    var1 = (q31_t) (temp_float1 * 1073741824);

    /* 1st iteration */
    var1 = ((q31_t) ((q63_t) var1 * (0x30000000 -
                                     ((q31_t)
                                      ((((q31_t)
                                         (((q63_t) var1 * var1) >> 31)) *
                                        (q63_t) half) >> 31))) >> 31)) << 2;
    /* 2nd iteration */
    var1 = ((q31_t) ((q63_t) var1 * (0x30000000 -
                                     ((q31_t)
                                      ((((q31_t)
                                         (((q63_t) var1 * var1) >> 31)) *
                                        (q63_t) half) >> 31))) >> 31)) << 2;
    /* 3rd iteration */
    var1 = ((q31_t) ((q63_t) var1 * (0x30000000 -
                                     ((q31_t)
                                      ((((q31_t)
                                         (((q63_t) var1 * var1) >> 31)) *
                                        (q63_t) half) >> 31))) >> 31)) << 2;

    /* Multiply the inverse square root with the original value */
    var1 = ((q31_t) (((q63_t) temp1 * var1) >> 31)) << 1;

    /* Shift the output down accordingly */
    if((signBits1 % 2) == 0)
    {
      var1 = var1 >> (signBits1 / 2);
    }
    else
    {
      var1 = var1 >> ((signBits1 - 1) / 2);
    }
    *pOut = var1;

    return (ARM_MATH_SUCCESS);
  }
  /* If the number is a negative number then store zero as its square root value */
  else
  {
    *pOut = 0;
    return (ARM_MATH_ARGUMENT_ERROR);
  }
}

/**     
 * @} end of SQRT group     
 */
