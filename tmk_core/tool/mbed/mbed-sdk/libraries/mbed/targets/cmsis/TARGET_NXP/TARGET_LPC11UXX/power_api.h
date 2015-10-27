/****************************************************************************
 *   $Id:: power_api.h 6249 2011-01-25 19:23:47Z usb01267                   $
 *   Project: NXP LPC11Uxx software example  
 *
 *   Description:
 *     Power API Header File for NXP LPC11Uxx Device Series 
 *
 ****************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
****************************************************************************/
#ifndef __LPC11UXX_POWER_API_H__
#define __LPC11UXX_POWER_API_H__

#ifdef __cplusplus
 extern "C" {
#endif 

#define PWRROMD_PRESENT

typedef	struct _PWRD {
  void (*set_pll)(unsigned int cmd[], unsigned int resp[]);
  void (*set_power)(unsigned int cmd[], unsigned int resp[]);
}  PWRD;

typedef	struct _ROM {
#ifdef USBROMD_PRESENT
   const USB * pUSBD;
#else
   const unsigned p_usbd;
#endif /* USBROMD_PRESENT */
   const unsigned p_clib;
   const unsigned p_cand;
#ifdef PWRROMD_PRESENT
   const PWRD * pPWRD;
#else
   const unsigned p_pwrd;
#endif /* PWRROMD_PRESENT */
   const unsigned p_dev1;
   const unsigned p_dev2;
   const unsigned p_dev3;
   const unsigned p_dev4; 
}  ROM;

//PLL setup related definitions
#define	CPU_FREQ_EQU  		0       //main PLL freq must be equal to the specified 
#define	CPU_FREQ_LTE		1       //main PLL freq must be less than or equal the specified
#define	CPU_FREQ_GTE		2       //main PLL freq must be greater than or equal the specified
#define	CPU_FREQ_APPROX		3       //main PLL freq must be as close as possible the specified

#define	PLL_CMD_SUCCESS		0       //PLL setup successfully found
#define	PLL_INVALID_FREQ	1       //specified freq out of range (either input or output)
#define	PLL_INVALID_MODE	2       //invalid mode (see above for valid) specified
#define	PLL_FREQ_NOT_FOUND	3       //specified freq not found under specified conditions
#define	PLL_NOT_LOCKED		4       //PLL not locked => no changes to the PLL setup

//power setup elated definitions
#define	PARAM_DEFAULT			0   //default power settings (voltage regulator, flash interface)
#define	PARAM_CPU_PERFORMANCE	1   //setup for maximum CPU performance (higher current, more computation)
#define	PARAM_EFFICIENCY		2   //balanced setting (power vs CPU performance)
#define	PARAM_LOW_CURRENT		3   //lowest active current, lowest CPU performance

#define	PARAM_CMD_SUCCESS		0   //power setting successfully found
#define	PARAM_INVALID_FREQ		1   //specified freq out of range (=0 or > 50 MHz)
#define	PARAM_INVALID_MODE		2   //specified mode not valid (see above for valid)

#define MAX_CLOCK_KHZ_PARAM                50000

#ifdef __cplusplus
}
#endif

#endif  /* __LPC11UXX_POWER_API_H__ */

