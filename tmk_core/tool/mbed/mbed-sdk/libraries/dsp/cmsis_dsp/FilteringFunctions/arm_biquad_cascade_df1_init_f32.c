/*-----------------------------------------------------------------------------    
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.    
*    
* $Date:        17. January 2013
* $Revision: 	V1.4.1
*    
* Project: 	    CMSIS DSP Library    
* Title:        arm_biquad_cascade_df1_init_f32.c    
*    
* Description:  floating-point Biquad cascade DirectFormI(DF1) filter initialization function.    
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
* ---------------------------------------------------------------------------*/

#include "arm_math.h"

/**    
 * @ingroup groupFilters    
 */

/**    
 * @addtogroup BiquadCascadeDF1    
 * @{    
 */

/**    
 * @details    
 * @brief  Initialization function for the floating-point Biquad cascade filter.    
 * @param[in,out] *S           points to an instance of the floating-point Biquad cascade structure.    
 * @param[in]     numStages    number of 2nd order stages in the filter.    
 * @param[in]     *pCoeffs     points to the filter coefficients array.    
 * @param[in]     *pState      points to the state array.    
 * @return        none    
 *    
 *    
 * <b>Coefficient and State Ordering:</b>    
 *    
 * \par    
 * The coefficients are stored in the array <code>pCoeffs</code> in the following order:    
 * <pre>    
 *     {b10, b11, b12, a11, a12, b20, b21, b22, a21, a22, ...}    
 * </pre>    
 *    
 * \par    
 * where <code>b1x</code> and <code>a1x</code> are the coefficients for the first stage,    
 * <code>b2x</code> and <code>a2x</code> are the coefficients for the second stage,    
 * and so on.  The <code>pCoeffs</code> array contains a total of <code>5*numStages</code> values.    
 *    
 * \par    
 * The <code>pState</code> is a pointer to state array.    
 * Each Biquad stage has 4 state variables <code>x[n-1], x[n-2], y[n-1],</code> and <code>y[n-2]</code>.    
 * The state variables are arranged in the <code>pState</code> array as:    
 * <pre>    
 *     {x[n-1], x[n-2], y[n-1], y[n-2]}    
 * </pre>    
 * The 4 state variables for stage 1 are first, then the 4 state variables for stage 2, and so on.    
 * The state array has a total length of <code>4*numStages</code> values.    
 * The state variables are updated after each block of data is processed; the coefficients are untouched.    
 *    
 */

void arm_biquad_cascade_df1_init_f32(
  arm_biquad_casd_df1_inst_f32 * S,
  uint8_t numStages,
  float32_t * pCoeffs,
  float32_t * pState)
{
  /* Assign filter stages */
  S->numStages = numStages;

  /* Assign coefficient pointer */
  S->pCoeffs = pCoeffs;

  /* Clear state buffer and size is always 4 * numStages */
  memset(pState, 0, (4u * (uint32_t) numStages) * sizeof(float32_t));

  /* Assign state pointer */
  S->pState = pState;
}

/**    
 * @} end of BiquadCascadeDF1 group    
 */
