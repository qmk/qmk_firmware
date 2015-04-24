/* ----------------------------------------------------------------------    
* Copyright (C) 2010-2013 ARM Limited. All rights reserved.    
*    
* $Date:        17. January 2013
* $Revision: 	V1.4.1
*    
* Project: 	    CMSIS DSP Library    
* Title:		arm_cos_f32.c    
*    
* Description:	Fast cosine calculation for floating-point values.   
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
 * @ingroup groupFastMath    
 */

/**    
 * @defgroup cos Cosine    
 *    
 * Computes the trigonometric cosine function using a combination of table lookup   
 * and cubic interpolation.  There are separate functions for   
 * Q15, Q31, and floating-point data types.   
 * The input to the floating-point version is in radians while the   
 * fixed-point Q15 and Q31 have a scaled input with the range   
 * [0 +0.9999] mapping to [0 2*pi).  The fixed-point range is chosen so that a
 * value of 2*pi wraps around to 0.
 *   
 * The implementation is based on table lookup using 256 values together with cubic interpolation.   
 * The steps used are:   
 *  -# Calculation of the nearest integer table index   
 *  -# Fetch the four table values a, b, c, and d     
 *  -# Compute the fractional portion (fract) of the table index.   
 *  -# Calculation of wa, wb, wc, wd    
 *  -# The final result equals <code>a*wa + b*wb + c*wc + d*wd</code>   
 *   
 * where   
 * <pre>    
 *    a=Table[index-1];    
 *    b=Table[index+0];    
 *    c=Table[index+1];    
 *    d=Table[index+2];    
 * </pre>   
 * and   
 * <pre>    
 *    wa=-(1/6)*fract.^3 + (1/2)*fract.^2 - (1/3)*fract;    
 *    wb=(1/2)*fract.^3 - fract.^2 - (1/2)*fract + 1;    
 *    wc=-(1/2)*fract.^3+(1/2)*fract.^2+fract;    
 *    wd=(1/6)*fract.^3 - (1/6)*fract;    
 * </pre>    
 */

 /**    
 * @addtogroup cos    
 * @{    
 */


/**    
* \par    
* <b>Example code for Generation of Cos Table:</b>
* <pre>
* tableSize = 256;    
* for(n = -1; n < (tableSize + 2); n++)    
* {    
*	cosTable[n+1]= cos(2*pi*n/tableSize);    
* } </pre>    
* where pi value is  3.14159265358979    
*/

static const float32_t cosTable[260] = {
  0.999698817729949950f, 1.000000000000000000f, 0.999698817729949950f,
  0.998795449733734130f, 0.997290432453155520f, 0.995184719562530520f,
  0.992479562759399410f, 0.989176511764526370f,
  0.985277652740478520f, 0.980785250663757320f, 0.975702106952667240f,
  0.970031261444091800f, 0.963776051998138430f, 0.956940352916717530f,
  0.949528157711029050f, 0.941544055938720700f,
  0.932992815971374510f, 0.923879504203796390f, 0.914209783077239990f,
  0.903989315032958980f, 0.893224298954010010f, 0.881921291351318360f,
  0.870086967945098880f, 0.857728600502014160f,
  0.844853579998016360f, 0.831469595432281490f, 0.817584812641143800f,
  0.803207516670227050f, 0.788346409797668460f, 0.773010432720184330f,
  0.757208824157714840f, 0.740951120853424070f,
  0.724247097969055180f, 0.707106769084930420f, 0.689540565013885500f,
  0.671558976173400880f, 0.653172850608825680f, 0.634393274784088130f,
  0.615231573581695560f, 0.595699310302734380f,
  0.575808167457580570f, 0.555570244789123540f, 0.534997642040252690f,
  0.514102756977081300f, 0.492898195981979370f, 0.471396744251251220f,
  0.449611335992813110f, 0.427555084228515630f,
  0.405241310596466060f, 0.382683426141738890f, 0.359895050525665280f,
  0.336889863014221190f, 0.313681751489639280f, 0.290284663438797000f,
  0.266712754964828490f, 0.242980182170867920f,
  0.219101235270500180f, 0.195090323686599730f, 0.170961886644363400f,
  0.146730467677116390f, 0.122410677373409270f, 0.098017141222953796f,
  0.073564566671848297f, 0.049067676067352295f,
  0.024541229009628296f, 0.000000000000000061f, -0.024541229009628296f,
  -0.049067676067352295f, -0.073564566671848297f, -0.098017141222953796f,
  -0.122410677373409270f, -0.146730467677116390f,
  -0.170961886644363400f, -0.195090323686599730f, -0.219101235270500180f,
  -0.242980182170867920f, -0.266712754964828490f, -0.290284663438797000f,
  -0.313681751489639280f, -0.336889863014221190f,
  -0.359895050525665280f, -0.382683426141738890f, -0.405241310596466060f,
  -0.427555084228515630f, -0.449611335992813110f, -0.471396744251251220f,
  -0.492898195981979370f, -0.514102756977081300f,
  -0.534997642040252690f, -0.555570244789123540f, -0.575808167457580570f,
  -0.595699310302734380f, -0.615231573581695560f, -0.634393274784088130f,
  -0.653172850608825680f, -0.671558976173400880f,
  -0.689540565013885500f, -0.707106769084930420f, -0.724247097969055180f,
  -0.740951120853424070f, -0.757208824157714840f, -0.773010432720184330f,
  -0.788346409797668460f, -0.803207516670227050f,
  -0.817584812641143800f, -0.831469595432281490f, -0.844853579998016360f,
  -0.857728600502014160f, -0.870086967945098880f, -0.881921291351318360f,
  -0.893224298954010010f, -0.903989315032958980f,
  -0.914209783077239990f, -0.923879504203796390f, -0.932992815971374510f,
  -0.941544055938720700f, -0.949528157711029050f, -0.956940352916717530f,
  -0.963776051998138430f, -0.970031261444091800f,
  -0.975702106952667240f, -0.980785250663757320f, -0.985277652740478520f,
  -0.989176511764526370f, -0.992479562759399410f, -0.995184719562530520f,
  -0.997290432453155520f, -0.998795449733734130f,
  -0.999698817729949950f, -1.000000000000000000f, -0.999698817729949950f,
  -0.998795449733734130f, -0.997290432453155520f, -0.995184719562530520f,
  -0.992479562759399410f, -0.989176511764526370f,
  -0.985277652740478520f, -0.980785250663757320f, -0.975702106952667240f,
  -0.970031261444091800f, -0.963776051998138430f, -0.956940352916717530f,
  -0.949528157711029050f, -0.941544055938720700f,
  -0.932992815971374510f, -0.923879504203796390f, -0.914209783077239990f,
  -0.903989315032958980f, -0.893224298954010010f, -0.881921291351318360f,
  -0.870086967945098880f, -0.857728600502014160f,
  -0.844853579998016360f, -0.831469595432281490f, -0.817584812641143800f,
  -0.803207516670227050f, -0.788346409797668460f, -0.773010432720184330f,
  -0.757208824157714840f, -0.740951120853424070f,
  -0.724247097969055180f, -0.707106769084930420f, -0.689540565013885500f,
  -0.671558976173400880f, -0.653172850608825680f, -0.634393274784088130f,
  -0.615231573581695560f, -0.595699310302734380f,
  -0.575808167457580570f, -0.555570244789123540f, -0.534997642040252690f,
  -0.514102756977081300f, -0.492898195981979370f, -0.471396744251251220f,
  -0.449611335992813110f, -0.427555084228515630f,
  -0.405241310596466060f, -0.382683426141738890f, -0.359895050525665280f,
  -0.336889863014221190f, -0.313681751489639280f, -0.290284663438797000f,
  -0.266712754964828490f, -0.242980182170867920f,
  -0.219101235270500180f, -0.195090323686599730f, -0.170961886644363400f,
  -0.146730467677116390f, -0.122410677373409270f, -0.098017141222953796f,
  -0.073564566671848297f, -0.049067676067352295f,
  -0.024541229009628296f, -0.000000000000000184f, 0.024541229009628296f,
  0.049067676067352295f, 0.073564566671848297f, 0.098017141222953796f,
  0.122410677373409270f, 0.146730467677116390f,
  0.170961886644363400f, 0.195090323686599730f, 0.219101235270500180f,
  0.242980182170867920f, 0.266712754964828490f, 0.290284663438797000f,
  0.313681751489639280f, 0.336889863014221190f,
  0.359895050525665280f, 0.382683426141738890f, 0.405241310596466060f,
  0.427555084228515630f, 0.449611335992813110f, 0.471396744251251220f,
  0.492898195981979370f, 0.514102756977081300f,
  0.534997642040252690f, 0.555570244789123540f, 0.575808167457580570f,
  0.595699310302734380f, 0.615231573581695560f, 0.634393274784088130f,
  0.653172850608825680f, 0.671558976173400880f,
  0.689540565013885500f, 0.707106769084930420f, 0.724247097969055180f,
  0.740951120853424070f, 0.757208824157714840f, 0.773010432720184330f,
  0.788346409797668460f, 0.803207516670227050f,
  0.817584812641143800f, 0.831469595432281490f, 0.844853579998016360f,
  0.857728600502014160f, 0.870086967945098880f, 0.881921291351318360f,
  0.893224298954010010f, 0.903989315032958980f,
  0.914209783077239990f, 0.923879504203796390f, 0.932992815971374510f,
  0.941544055938720700f, 0.949528157711029050f, 0.956940352916717530f,
  0.963776051998138430f, 0.970031261444091800f,
  0.975702106952667240f, 0.980785250663757320f, 0.985277652740478520f,
  0.989176511764526370f, 0.992479562759399410f, 0.995184719562530520f,
  0.997290432453155520f, 0.998795449733734130f,
  0.999698817729949950f, 1.000000000000000000f, 0.999698817729949950f,
  0.998795449733734130f
};

/**   
 * @brief  Fast approximation to the trigonometric cosine function for floating-point data.   
 * @param[in] x input value in radians.   
 * @return cos(x).   
 */


float32_t arm_cos_f32(
  float32_t x)
{
  float32_t cosVal, fract, in;
  int32_t index;
  uint32_t tableSize = (uint32_t) TABLE_SIZE;
  float32_t wa, wb, wc, wd;
  float32_t a, b, c, d;
  float32_t *tablePtr;
  int32_t n;
  float32_t fractsq, fractby2, fractby6, fractby3, fractsqby2;
  float32_t oneminusfractby2;
  float32_t frby2xfrsq, frby6xfrsq;

  /* input x is in radians */
  /* Scale the input to [0 1] range from [0 2*PI] , divide input by 2*pi */
  in = x * 0.159154943092f;

  /* Calculation of floor value of input */
  n = (int32_t) in;

  /* Make negative values towards -infinity */
  if(x < 0.0f)
  {
    n = n - 1;
  }

  /* Map input value to [0 1] */
  in = in - (float32_t) n;

  /* Calculation of index of the table */
  index = (uint32_t) (tableSize * in);

  /* fractional value calculation */
  fract = ((float32_t) tableSize * in) - (float32_t) index;

  /* Checking min and max index of table */
  if(index < 0)
  {
    index = 0;
  }
  else if(index > 256)
  {
    index = 256;
  }

  /* Initialise table pointer */
  tablePtr = (float32_t *) & cosTable[index];

  /* Read four nearest values of input value from the cos table */
  a = tablePtr[0];
  b = tablePtr[1];
  c = tablePtr[2];
  d = tablePtr[3];

  /* Cubic interpolation process */
  fractsq = fract * fract;
  fractby2 = fract * 0.5f;
  fractby6 = fract * 0.166666667f;
  fractby3 = fract * 0.3333333333333f;
  fractsqby2 = fractsq * 0.5f;
  frby2xfrsq = (fractby2) * fractsq;
  frby6xfrsq = (fractby6) * fractsq;
  oneminusfractby2 = 1.0f - fractby2;
  wb = fractsqby2 - fractby3;
  wc = (fractsqby2 + fract);
  wa = wb - frby6xfrsq;
  wb = frby2xfrsq - fractsq;
  cosVal = wa * a;
  wc = wc - frby2xfrsq;
  wd = (frby6xfrsq) - fractby6;
  wb = wb + oneminusfractby2;

  /* Calculate cos value */
  cosVal = (cosVal + (b * wb)) + ((c * wc) + (d * wd));

  /* Return the output value */
  return (cosVal);

}

/**    
 * @} end of cos group    
 */
