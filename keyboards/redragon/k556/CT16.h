#ifndef __SN32F240B_CT16_H
#define __SN32F240B_CT16_H


/*_____ I N C L U D E S ____________________________________________________*/

/*_____ D E F I N I T I O N S ______________________________________________*/
/*
Base Address: 0x4000 0000 (CT16B0)
							0x4000 2000 (CT16B1)
*/

/* CT16Bn Timer Control register <CT16Bn_TMRCTRL> (0x00) */
#define	CT16_CEN_DIS 						0			//[0:0] CT16Bn enable bit
#define	CT16_CEN_EN  						1
#define mskCT16_CEN_DIS					(CT16_CEN_DIS<<0)
#define	mskCT16_CEN_EN  				(CT16_CEN_EN<<0)

#define	CT16_CRST 							1			//[1:1] CT16Bn counter reset bit
#define mskCT16_CRST						(CT16_CRST<<1)

/* CT16Bn Count Control register <CT16Bn_CNTCTRL> (0x10) */
																//[1:0] Count/Timer Mode selection.
#define	CT16_CTM_TIMER					0			//Timer mode: Every rising PCLK edge.
#define CT16_CTM_CNTER_RISING		1			//Counter mode: TC increments on rising edge of CAP input.
#define CT16_CTM_CNTER_FALLING	2			//Counter mode: TC increments on falling edge of CAP input.
#define CT16_CTM_CNTER_BOTH			3			//Counter mode: TC increments on both edge of CAP input.
#define	mskCT16_CTM_TIMER					(CT16_CTM_TIMER<<0)
#define mskCT16_CTM_CNTER_RISING	(CT16_CTM_CNTER_RISING<<0)
#define mskCT16_CTM_CNTER_FALLING	(CT16_CTM_CNTER_FALLING<<0)
#define mskCT16_CTM_CNTER_BOTH		(CT16_CTM_CNTER_BOTH<<0)

#define	CT16_CIS								0			//[3:2] Count Input Select
#define mskCT16_CIS							(CT16_CIS<<2)

/* CT16Bn Match Control register <CT16Bn_MCTRL> (0x14) */
#define	CT16_MR0IE_EN						1			//[0:0] Enable MR0 match interrupt
#define	CT16_MR0IE_DIS					0
#define mskCT16_MR0IE_EN				(CT16_MR0IE_EN<<0)
#define mskCT16_MR0IE_DIS				(CT16_MR0IE_DIS<<0)

#define	CT16_MR0RST_EN					1			//[1:1] Enable reset TC when MR0 matches TC.
#define	CT16_MR0RST_DIS					0
#define mskCT16_MR0RST_EN				(CT16_MR0RST_EN<<1)
#define mskCT16_MR0RST_DIS			(CT16_MR0RST_DIS<<1)

#define	CT16_MR0STOP_EN					1			//[2:2] Enable stop TC and clear CEN when MR0 matches TC.
#define	CT16_MR0STOP_DIS				0
#define mskCT16_MR0STOP_EN			(CT16_MR0STOP_EN<<2)
#define mskCT16_MR0STOP_DIS			(CT16_MR0STOP_DIS<<2)

#define	CT16_MR1IE_EN						1			//[3:3] Enable MR1 match interrupt
#define	CT16_MR1IE_DIS					0
#define mskCT16_MR1IE_EN				(CT16_MR1IE_EN<<3)
#define mskCT16_MR1IE_DIS				(CT16_MR1IE_DIS<<3)

#define	CT16_MR1RST_EN					1			//[4:4] Enable reset TC when MR1 matches TC.
#define	CT16_MR1RST_DIS					0
#define mskCT16_MR1RST_EN				(CT16_MR1RST_EN<<4)
#define mskCT16_MR1RST_DIS			(CT16_MR1RST_DIS<<4)

#define	CT16_MR1STOP_EN					1			//[5:5] Enable stop TC and clear CEN when MR1 matches TC.
#define	CT16_MR1STOP_DIS				0
#define mskCT16_MR1STOP_EN			(CT16_MR1STOP_EN<<5)
#define mskCT16_MR1STOP_DIS			(CT16_MR1STOP_DIS<<5)

#define	CT16_MR2IE_EN						1			//[6:6] Enable MR2 match interrupt
#define	CT16_MR2IE_DIS					0
#define mskCT16_MR2IE_EN				(CT16_MR2IE_EN<<6)
#define mskCT16_MR2IE_DIS				(CT16_MR2IE_DIS<<6)

#define	CT16_MR2RST_EN					1			//[7:7] Enable reset TC when MR2 matches TC.
#define	CT16_MR2RST_DIS					0
#define mskCT16_MR2RST_EN				(CT16_MR2RST_EN<<7)
#define mskCT16_MR2RST_DIS			(CT16_MR2RST_DIS<<7)

#define	CT16_MR2STOP_EN					1			//[8:8] Enable stop TC and clear CEN when MR2 matches TC.
#define	CT16_MR2STOP_DIS				0
#define mskCT16_MR2STOP_EN			(CT16_MR2STOP_EN<<8)
#define mskCT16_MR2STOP_DIS			(CT16_MR2STOP_DIS<<8)

#define	CT16_MR3IE_EN						1			//[9:9] Enable MR3 match interrupt
#define	CT16_MR3IE_DIS					0
#define mskCT16_MR3IE_EN				(CT16_MR3IE_EN<<9)
#define mskCT16_MR3IE_DIS				(CT16_MR3IE_DIS<<9)

#define	CT16_MR3RST_EN					1			//[10:10] Enable reset TC when MR3 matches TC.
#define	CT16_MR3RST_DIS					0
#define mskCT16_MR3RST_EN				(CT16_MR3RST_EN<<10)
#define mskCT16_MR3RST_DIS			(CT16_MR3RST_DIS<<10)

#define	CT16_MR3STOP_EN					1			//[11:11] Enable stop TC and clear CEN when MR3 matches TC.
#define	CT16_MR3STOP_DIS				0
#define mskCT16_MR3STOP_EN			(CT16_MR3STOP_EN<<11)
#define mskCT16_MR3STOP_DIS			(CT16_MR3STOP_DIS<<11)

#define	CT16_MR4IE_EN						1			//[12:12 Enable MR4 match interrupt
#define	CT16_MR4IE_DIS					0
#define mskCT16_MR4IE_EN				(CT16_MR4IE_EN<<12)
#define mskCT16_MR4IE_DIS				(CT16_MR4IE_DIS<<12)

#define	CT16_MR4RST_EN					1			//[13:13] Enable reset TC when MR4 matches TC.
#define	CT16_MR4RST_DIS					0
#define mskCT16_MR4RST_EN				(CT16_MR4RST_EN<<13)
#define mskCT16_MR4RST_DIS			(CT16_MR4RST_DIS<<13)

#define	CT16_MR4STOP_EN					1			//[14:14] Enable stop TC and clear CEN when MR4 matches TC.
#define	CT16_MR4STOP_DIS				0
#define mskCT16_MR4STOP_EN			(CT16_MR4STOP_EN<<14)
#define mskCT16_MR4STOP_DIS			(CT16_MR4STOP_DIS<<14)

#define	CT16_MR5IE_EN						1			//[15:15] Enable MR5 match interrupt
#define	CT16_MR5IE_DIS					0
#define mskCT16_MR5IE_EN				(CT16_MR5IE_EN<<15)
#define mskCT16_MR5IE_DIS				(CT16_MR5IE_DIS<<15)

#define	CT16_MR5RST_EN					1			//[16:16] Enable reset TC when MR5 matches TC.
#define	CT16_MR5RST_DIS					0
#define mskCT16_MR5RST_EN				(CT16_MR5RST_EN<<16)
#define mskCT16_MR5RST_DIS			(CT16_MR5RST_DIS<<16)

#define	CT16_MR5STOP_EN					1			//[17:17] Enable stop TC and clear CEN when MR5 matches TC.
#define	CT16_MR5STOP_DIS				0
#define mskCT16_MR5STOP_EN			(CT16_MR5STOP_EN<<17)
#define mskCT16_MR5STOP_DIS			(CT16_MR5STOP_DIS<<17)

#define	CT16_MR6IE_EN						1			//[18:18 Enable MR6 match interrupt
#define	CT16_MR6IE_DIS					0
#define mskCT16_MR6IE_EN				(CT16_MR6IE_EN<<18)
#define mskCT16_MR6IE_DIS				(CT16_MR6IE_DIS<<18)

#define	CT16_MR6RST_EN					1			//[19:19] Enable reset TC when MR6 matches TC.
#define	CT16_MR6RST_DIS					0
#define mskCT16_MR6RST_EN				(CT16_MR6RST_EN<<19)
#define mskCT16_MR6RST_DIS			(CT16_MR6RST_DIS<<19)

#define	CT16_MR6STOP_EN					1			//[20:20] Enable stop TC and clear CEN when MR6 matches TC.
#define	CT16_MR6STOP_DIS				0
#define mskCT16_MR6STOP_EN			(CT16_MR6STOP_EN<<20)
#define mskCT16_MR6STOP_DIS			(CT16_MR6STOP_DIS<<20)

#define	CT16_MR7IE_EN						1			//[21:21 Enable MR7 match interrupt
#define	CT16_MR7IE_DIS					0
#define mskCT16_MR7IE_EN				(CT16_MR7IE_EN<<21)
#define mskCT16_MR7IE_DIS				(CT16_MR7IE_DIS<<21)

#define	CT16_MR7RST_EN					1			//[22:22] Enable reset TC when MR7 matches TC.
#define	CT16_MR7RST_DIS					0
#define mskCT16_MR7RST_EN				(CT16_MR7RST_EN<<22)
#define mskCT16_MR7RST_DIS			(CT16_MR7RST_DIS<<22)

#define	CT16_MR7STOP_EN					1			//[23:23] Enable stop TC and clear CEN when MR7 matches TC.
#define	CT16_MR7STOP_DIS				0
#define mskCT16_MR7STOP_EN			(CT16_MR7STOP_EN<<23)
#define mskCT16_MR7STOP_DIS			(CT16_MR7STOP_DIS<<23)

#define	CT16_MR8IE_EN						1			//[24:24 Enable MR8 match interrupt
#define	CT16_MR8IE_DIS					0
#define mskCT16_MR8IE_EN				(CT16_MR8IE_EN<<24)
#define mskCT16_MR8IE_DIS				(CT16_MR8IE_DIS<<24)

#define	CT16_MR8RST_EN					1			//[25:25] Enable reset TC when MR8 matches TC.
#define	CT16_MR8RST_DIS					0
#define mskCT16_MR8RST_EN				(CT16_MR8RST_EN<<25)
#define mskCT16_MR8RST_DIS			(CT16_MR8RST_DIS<<25)

#define	CT16_MR8STOP_EN					1			//[26:26] Enable stop TC and clear CEN when MR8 matches TC.
#define	CT16_MR8STOP_DIS				0
#define mskCT16_MR8STOP_EN			(CT16_MR8STOP_EN<<26)
#define mskCT16_MR8STOP_DIS			(CT16_MR8STOP_DIS<<26)

#define	CT16_MR9IE_EN						1			//[27:27] Enable MR9 match interrupt
#define	CT16_MR9IE_DIS					0
#define mskCT16_MR9IE_EN				(CT16_MR9IE_EN<<27)
#define mskCT16_MR9IE_DIS				(CT16_MR9IE_DIS<<27)

#define	CT16_MR9RST_EN					1			//[28:28] Enable reset TC when MR9 matches TC.
#define	CT16_MR9RST_DIS					0
#define mskCT16_MR9RST_EN				(CT16_MR9RST_EN<<28)
#define mskCT16_MR9RST_DIS			(CT16_MR9RST_DIS<<28)

#define	CT16_MR9STOP_EN					1			//[29:29] Enable stop TC and clear CEN when MR9 matches TC.
#define	CT16_MR9STOP_DIS				0
#define mskCT16_MR9STOP_EN			(CT16_MR9STOP_EN<<29)
#define mskCT16_MR9STOP_DIS			(CT16_MR9STOP_DIS<<29)

/* CT16Bn Match Control register 2 <CT16Bn_MCTRL2> (0x18) */
#define	CT16_MR10IE_EN					1			//[0:0] Enable MR10 match interrupt
#define	CT16_MR10IE_DIS					0
#define mskCT16_MR10IE_EN				(CT16_MR10IE_EN<<0)
#define mskCT16_MR10IE_DIS			(CT16_MR10IE_DIS<<0)

#define	CT16_MR10RST_EN					1			//[1:1] Enable reset TC when MR10 matches TC.
#define	CT16_MR10RST_DIS				0
#define mskCT16_MR10RST_EN			(CT16_MR10RST_EN<<1)
#define mskCT16_MR10RST_DIS			(CT16_MR10RST_DIS<<1)

#define	CT16_MR10STOP_EN				1			//[2:2] Enable stop TC and clear CEN when MR10 matches TC.
#define	CT16_MR10STOP_DIS				0
#define mskCT16_MR10STOP_EN			(CT16_MR10STOP_EN<<2)
#define mskCT16_MR10STOP_DIS		(CT16_MR10STOP_DIS<<2)

#define	CT16_MR11IE_EN					1			//[3:3] Enable MR11 match interrupt
#define	CT16_MR11IE_DIS					0
#define mskCT16_MR11IE_EN				(CT16_MR11IE_EN<<3)
#define mskCT16_MR11IE_DIS			(CT16_MR11IE_DIS<<3)

#define	CT16_MR11RST_EN					1			//[4:4] Enable reset TC when MR11 matches TC.
#define	CT16_MR11RST_DIS				0
#define mskCT16_MR11RST_EN			(CT16_MR11RST_EN<<4)
#define mskCT16_MR11RST_DIS			(CT16_MR11RST_DIS<<4)

#define	CT16_MR11STOP_EN				1			//[5:5] Enable stop TC and clear CEN when MR11 matches TC.
#define	CT16_MR11STOP_DIS				0
#define mskCT16_MR11STOP_EN			(CT16_MR11STOP_EN<<5)
#define mskCT16_MR11STOP_DIS		(CT16_MR11STOP_DIS<<5)

#define	CT16_MR12IE_EN					1			//[6:6] Enable MR12 match interrupt
#define	CT16_MR12IE_DIS					0
#define mskCT16_MR12IE_EN				(CT16_MR12IE_EN<<6)
#define mskCT16_MR12IE_DIS			(CT16_MR12IE_DIS<<6)

#define	CT16_MR12RST_EN					1			//[7:7] Enable reset TC when MR12 matches TC.
#define	CT16_MR12RST_DIS				0
#define mskCT16_MR12RST_EN			(CT16_MR12RST_EN<<7)
#define mskCT16_MR12RST_DIS			(CT16_MR12RST_DIS<<7)

#define	CT16_MR12STOP_EN				1			//[8:8] Enable stop TC and clear CEN when MR12 matches TC.
#define	CT16_MR12STOP_DIS				0
#define mskCT16_MR12STOP_EN			(CT16_MR12STOP_EN<<8)
#define mskCT16_MR12STOP_DIS		(CT16_MR12STOP_DIS<<8)

#define	CT16_MR13IE_EN					1			//[9:9] Enable MR13 match interrupt
#define	CT16_MR13IE_DIS					0
#define mskCT16_MR13IE_EN				(CT16_MR13IE_EN<<9)
#define mskCT16_MR13IE_DIS			(CT16_MR13IE_DIS<<9)

#define	CT16_MR13RST_EN					1			//[10:10] Enable reset TC when MR13 matches TC.
#define	CT16_MR13RST_DIS				0
#define mskCT16_MR13RST_EN			(CT16_MR13RST_EN<<10)
#define mskCT16_MR13RST_DIS			(CT16_MR13RST_DIS<<10)

#define	CT16_MR13STOP_EN				1			//[11:11] Enable stop TC and clear CEN when MR13 matches TC.
#define	CT16_MR13STOP_DIS				0
#define mskCT16_MR13STOP_EN			(CT16_MR13STOP_EN<<11)
#define mskCT16_MR13STOP_DIS		(CT16_MR13STOP_DIS<<11)

#define	CT16_MR14IE_EN					1			//[12:12 Enable MR14 match interrupt
#define	CT16_MR14IE_DIS					0
#define mskCT16_MR14IE_EN				(CT16_MR14IE_EN<<12)
#define mskCT16_MR14IE_DIS			(CT16_MR14IE_DIS<<12)

#define	CT16_MR14RST_EN					1			//[13:13] Enable reset TC when MR14 matches TC.
#define	CT16_MR14RST_DIS				0
#define mskCT16_MR14RST_EN			(CT16_MR14RST_EN<<13)
#define mskCT16_MR14RST_DIS			(CT16_MR14RST_DIS<<13)

#define	CT16_MR14STOP_EN				1			//[14:14] Enable stop TC and clear CEN when MR14 matches TC.
#define	CT16_MR14STOP_DIS				0
#define mskCT16_MR14STOP_EN			(CT16_MR14STOP_EN<<14)
#define mskCT16_MR14STOP_DIS		(CT16_MR14STOP_DIS<<14)

#define	CT16_MR15IE_EN					1			//[15:15 Enable MR15 match interrupt
#define	CT16_MR15IE_DIS					0
#define mskCT16_MR15IE_EN				(CT16_MR15IE_EN<<15)
#define mskCT16_MR15IE_DIS			(CT16_MR15IE_DIS<<15)

#define	CT16_MR15RST_EN					1			//[16:16] Enable reset TC when MR15 matches TC.
#define	CT16_MR15RST_DIS				0
#define mskCT16_MR15RST_EN			(CT16_MR15RST_EN<<16)
#define mskCT16_MR15RST_DIS			(CT16_MR15RST_DIS<<16)

#define	CT16_MR15STOP_EN				1			//[17:17] Enable stop TC and clear CEN when MR15 matches TC.
#define	CT16_MR15STOP_DIS				0
#define mskCT16_MR15STOP_EN			(CT16_MR15STOP_EN<<17)
#define mskCT16_MR15STOP_DIS		(CT16_MR15STOP_DIS<<17)

#define	CT16_MR16IE_EN					1			//[18:18 Enable MR16 match interrupt
#define	CT16_MR16IE_DIS					0
#define mskCT16_MR16IE_EN				(CT16_MR16IE_EN<<18)
#define mskCT16_MR16IE_DIS			(CT16_MR16IE_DIS<<18)

#define	CT16_MR16RST_EN					1			//[19:19] Enable reset TC when MR16 matches TC.
#define	CT16_MR16RST_DIS				0
#define mskCT16_MR16RST_EN			(CT16_MR16RST_EN<<19)
#define mskCT16_MR16RST_DIS			(CT16_MR16RST_DIS<<19)

#define	CT16_MR16STOP_EN				1			//[20:20] Enable stop TC and clear CEN when MR16 matches TC.
#define	CT16_MR16STOP_DIS				0
#define mskCT16_MR16STOP_EN			(CT16_MR16STOP_EN<<20)
#define mskCT16_MR16STOP_DIS		(CT16_MR16STOP_DIS<<20)

#define	CT16_MR17IE_EN					1			//[21:21 Enable MR17 match interrupt
#define	CT16_MR17IE_DIS					0
#define mskCT16_MR17IE_EN				(CT16_MR17IE_EN<<21)
#define mskCT16_MR17IE_DIS			(CT16_MR17IE_DIS<<21)

#define	CT16_MR17RST_EN					1			//[22:22] Enable reset TC when MR17 matches TC.
#define	CT16_MR17RST_DIS				0
#define mskCT16_MR17RST_EN			(CT16_MR17RST_EN<<22)
#define mskCT16_MR17RST_DIS			(CT16_MR17RST_DIS<<22)

#define	CT16_MR17STOP_EN				1			//[23:23] Enable stop TC and clear CEN when MR17 matches TC.
#define	CT16_MR17STOP_DIS				0
#define mskCT16_MR17STOP_EN			(CT16_MR17STOP_EN<<23)
#define mskCT16_MR17STOP_DIS			(CT16_MR17STOP_DIS<<23)

#define	CT16_MR18IE_EN					1			//[24:24 Enable MR18 match interrupt
#define	CT16_MR18IE_DIS					0
#define mskCT16_MR18IE_EN				(CT16_MR18IE_EN<<24)
#define mskCT16_MR18IE_DIS				(CT16_MR18IE_DIS<<24)

#define	CT16_MR18RST_EN					1			//[25:25] Enable reset TC when MR18 matches TC.
#define	CT16_MR18RST_DIS				0
#define mskCT16_MR18RST_EN				(CT16_MR18RST_EN<<25)
#define mskCT16_MR18RST_DIS			(CT16_MR18RST_DIS<<25)

#define	CT16_MR18STOP_EN				1			//[26:26] Enable stop TC and clear CEN when MR18 matches TC.
#define	CT16_MR18STOP_DIS				0
#define mskCT16_MR18STOP_EN			(CT16_MR18STOP_EN<<26)
#define mskCT16_MR18STOP_DIS		(CT16_MR18STOP_DIS<<26)

#define	CT16_MR19IE_EN					1			//[27:27] Enable MR19 match interrupt
#define	CT16_MR19IE_DIS					0
#define mskCT16_MR19IE_EN				(CT16_MR19IE_EN<<27)
#define mskCT16_MR19IE_DIS			(CT16_MR19IE_DIS<<27)

#define	CT16_MR19RST_EN					1			//[28:28] Enable reset TC when MR19 matches TC.
#define	CT16_MR19RST_DIS				0
#define mskCT16_MR19RST_EN			(CT16_MR19RST_EN<<28)
#define mskCT16_MR19RST_DIS			(CT16_MR19RST_DIS<<28)

#define	CT16_MR19STOP_EN				1			//[29:29] Enable stop TC and clear CEN when MR19 matches TC.
#define	CT16_MR19STOP_DIS				0
#define mskCT16_MR19STOP_EN			(CT16_MR19STOP_EN<<29)
#define mskCT16_MR19STOP_DIS		(CT16_MR19STOP_DIS<<29)

/* CT16Bn Match Control register 3 <CT16Bn_MCTRL3> (0x1C) */
#define	CT16_MR20IE_EN					1			//[0:0] Enable MR20 match interrupt
#define	CT16_MR20IE_DIS					0
#define mskCT16_MR20IE_EN				(CT16_MR20IE_EN<<0)
#define mskCT16_MR20IE_DIS			(CT16_MR20IE_DIS<<0)

#define	CT16_MR20RST_EN					1			//[1:1] Enable reset TC when MR20 matches TC.
#define	CT16_MR20RST_DIS				0
#define mskCT16_MR20RST_EN			(CT16_MR20RST_EN<<1)
#define mskCT16_MR20RST_DIS			(CT16_MR20RST_DIS<<1)

#define	CT16_MR20STOP_EN				1			//[2:2] Enable stop TC and clear CEN when MR20 matches TC.
#define	CT16_MR20STOP_DIS				0
#define mskCT16_MR20STOP_EN			(CT16_MR20STOP_EN<<2)
#define mskCT16_MR20STOP_DIS		(CT16_MR20STOP_DIS<<2)

#define	CT16_MR21IE_EN					1			//[3:3] Enable MR21 match interrupt
#define	CT16_MR21IE_DIS					0
#define mskCT16_MR21IE_EN				(CT16_MR21IE_EN<<3)
#define mskCT16_MR21IE_DIS			(CT16_MR21IE_DIS<<3)

#define	CT16_MR21RST_EN					1			//[4:4] Enable reset TC when MR21 matches TC.
#define	CT16_MR21RST_DIS				0
#define mskCT16_MR21RST_EN			(CT16_MR21RST_EN<<4)
#define mskCT16_MR21RST_DIS			(CT16_MR21RST_DIS<<4)

#define	CT16_MR21STOP_EN				1			//[5:5] Enable stop TC and clear CEN when MR21 matches TC.
#define	CT16_MR21STOP_DIS				0
#define mskCT16_MR21STOP_EN			(CT16_MR21STOP_EN<<5)
#define mskCT16_MR21STOP_DIS		(CT16_MR21STOP_DIS<<5)

#define	CT16_MR22IE_EN					1			//[6:6] Enable MR22 match interrupt
#define	CT16_MR22IE_DIS					0
#define mskCT16_MR22IE_EN				(CT16_MR22IE_EN<<6)
#define mskCT16_MR22IE_DIS			(CT16_MR22IE_DIS<<6)

#define	CT16_MR22RST_EN					1			//[7:7] Enable reset TC when MR22 matches TC.
#define	CT16_MR22RST_DIS				0
#define mskCT16_MR22RST_EN			(CT16_MR22RST_EN<<7)
#define mskCT16_MR22RST_DIS			(CT16_MR22RST_DIS<<7)

#define	CT16_MR22STOP_EN				1			//[8:8] Enable stop TC and clear CEN when MR22 matches TC.
#define	CT16_MR22STOP_DIS				0
#define mskCT16_MR22STOP_EN			(CT16_MR22STOP_EN<<8)
#define mskCT16_MR22STOP_DIS		(CT16_MR22STOP_DIS<<8)

#define	CT16_MR23IE_EN					1			//[9:9] Enable MR23 match interrupt
#define	CT16_MR23IE_DIS					0
#define mskCT16_MR23IE_EN				(CT16_MR23IE_EN<<9)
#define mskCT16_MR23IE_DIS			(CT16_MR23IE_DIS<<9)

#define	CT16_MR23RST_EN					1			//[10:10] Enable reset TC when MR23 matches TC.
#define	CT16_MR23RST_DIS				0
#define mskCT16_MR23RST_EN			(CT16_MR23RST_EN<<10)
#define mskCT16_MR23RST_DIS			(CT16_MR23RST_DIS<<10)

#define	CT16_MR23STOP_EN				1			//[11:11] Enable stop TC and clear CEN when MR23 matches TC.
#define	CT16_MR23STOP_DIS				0
#define mskCT16_MR23STOP_EN			(CT16_MR23STOP_EN<<11)
#define mskCT16_MR23STOP_DIS		(CT16_MR23STOP_DIS<<11)

#define	CT16_MR24IE_EN					1			//[12:12] Enable MR24 match interrupt
#define	CT16_MR24IE_DIS					0
#define mskCT16_MR24IE_EN				(CT16_MR24IE_EN<<12)
#define mskCT16_MR24IE_DIS			(CT16_MR24IE_DIS<<12)

#define	CT16_MR24RST_EN					1			//[13:13] Enable reset TC when MR24 matches TC.
#define	CT16_MR24RST_DIS				0
#define mskCT16_MR24RST_EN			(CT16_MR24RST_EN<<13)
#define mskCT16_MR24RST_DIS			(CT16_MR24RST_DIS<<13)

#define	CT16_MR24STOP_EN				1			//[14:14] Enable stop TC and clear CEN when MR24 matches TC.
#define	CT16_MR24STOP_DIS				0
#define mskCT16_MR24STOP_EN			(CT16_MR24STOP_EN<<14)
#define mskCT16_MR24STOP_DIS		(CT16_MR24STOP_DIS<<14)

/* CT16Bn Capture Control register <CT16Bn_CAPCTRL> (0x80) */
#define	CT16_CAP0RE_EN					1		//[0:0] Enable CAP0 capture on rising edge.
#define	CT16_CAP0RE_DIS					0
#define mskCT16_CAP0RE_EN				(CT16_CAP0RE_EN<<0)
#define mskCT16_CAP0RE_DIS			(CT16_CAP0RE_DIS<<0)

#define	CT16_CAP0FE_EN					1		//[1:1] Enable CAP0 capture on fallng edge.
#define	CT16_CAP0FE_DIS					0
#define mskCT16_CAP0FE_EN				(CT16_CAP0FE_EN<<1)
#define mskCT16_CAP0FE_DIS			(CT16_CAP0FE_DIS<<1)

#define	CT16_CAP0IE_EN					1		//[2:2] Enable CAP0 interrupt.
#define	CT16_CAP0IE_DIS					0
#define mskCT16_CAP0IE_EN				(CT16_CAP0IE_EN<<2)
#define mskCT16_CAP0IE_DIS			(CT16_CAP0IE_DIS<<2)

#define	CT16_CAP0EN_EN					1		//[3:3] Enable CAP0 function.
#define	CT16_CAP0EN_DIS					0
#define mskCT16_CAP0EN_EN				(CT16_CAP0EN_EN<<3)
#define mskCT16_CAP0EN_DIS			(CT16_CAP0EN_DIS<<3)

/* CT16Bn External Match register <CT16Bn_EM> (0x88) */
#define	CT16_EM0								1		//[0:0] CT16Bn PWM0 drive state
#define mskCT16_EM0							(CT16_EM0<<0)
#define	CT16_EM1								1		//[1:1] CT16Bn PWM1 drive state
#define mskCT16_EM1							(CT16_EM1<<1)
#define	CT16_EM2								1		//[2:2] CT16Bn PWM2 drive state
#define mskCT16_EM2							(CT16_EM2<<2)
#define	CT16_EM3								1		//[3:3] CT16Bn PWM3 drive state
#define mskCT16_EM3							(CT16_EM3<<3)
#define	CT16_EM4								1		//[4:4] CT16Bn PWM4 drive state
#define mskCT16_EM4							(CT16_EM4<<4)
#define	CT16_EM5								1		//[5:5] CT16Bn PWM5 drive state
#define mskCT16_EM5							(CT16_EM5<<5)
#define	CT16_EM6								1		//[6:6] CT16Bn PWM6 drive state
#define mskCT16_EM6							(CT16_EM6<<6)
#define	CT16_EM7								1		//[7:7] CT16Bn PWM7 drive state
#define mskCT16_EM7							(CT16_EM7<<7)
#define	CT16_EM8								1		//[8:8] CT16Bn PWM8 drive state
#define mskCT16_EM8							(CT16_EM8<<8)
#define	CT16_EM9								1		//[9:9] CT16Bn PWM9 drive state
#define mskCT16_EM9							(CT16_EM9<<9)
#define	CT16_EM10								1		//[10:10] CT16Bn PWM10 drive state
#define mskCT16_EM10							(CT16_EM0<<10)
#define	CT16_EM11								1		//[11:11] CT16Bn PWM11 drive state
#define mskCT16_EM11							(CT16_EM11<<11)
#define	CT16_EM12								1		//[12:12] CT16Bn PWM12 drive state
#define mskCT16_EM12							(CT16_EM12<<12)
#define	CT16_EM13								1		//[13:13] CT16Bn PWM13 drive state
#define mskCT16_EM13							(CT16_EM13<<13)
#define	CT16_EM14								1		//[14:14] CT16Bn PWM14 drive state
#define mskCT16_EM14							(CT16_EM14<<14)
#define	CT16_EM15								1		//[15:15] CT16Bn PWM15 drive state
#define mskCT16_EM15							(CT16_EM15<<15)
#define	CT16_EM16								1		//[16:16] CT16Bn PWM16 drive state
#define mskCT16_EM16							(CT16_EM16<<16)
#define	CT16_EM17								1		//[17:17] CT16Bn PWM17 drive state
#define mskCT16_EM17							(CT16_EM17<<17)
#define	CT16_EM18								1		//[18:18] CT16Bn PWM18 drive state
#define mskCT16_EM18							(CT16_EM18<<8)
#define	CT16_EM19								1		//[19:19] CT16Bn PWM19 drive state
#define mskCT16_EM19							(CT16_EM19<<9)
#define	CT16_EM20								1		//[20:20] CT16Bn PWM20 drive state
#define mskCT16_EM20							(CT16_EM20<<0)
#define	CT16_EM21								1		//[21:21] CT16Bn PWM21 drive state
#define mskCT16_EM21							(CT16_EM21<<1)
#define	CT16_EM22								1		//[22:22] CT16Bn PWM22 drive state
#define mskCT16_EM22							(CT16_EM22<<2)
#define	CT16_EM23								1		//[23:23] CT16Bn PWM23 drive state
#define mskCT16_EM23							(CT16_EM23<<3)

/* CT16Bn External Match Control register <CT16Bn_EMC> (0x8C) */
																//[1:0]CT16Bn PWM0 functionality
#define	CT16_EMC0_DO_NOTHING		0	//Do nothing.
#define	CT16_EMC0_LOW						1	//CT16Bn PWM0 pin is low.
#define	CT16_EMC0_HIGH					2	//CT16Bn PWM0 pin is high.
#define	CT16_EMC0_TOGGLE				3	//Toggle CT16Bn PWM0 pin.
#define mskCT16_EMC0_DO_NOTHING	(CT16_EMC0_LOW<<0)
#define mskCT16_EMC0_LOW				(CT16_EMC0_LOW<<0)
#define mskCT16_EMC0_HIGH				(CT16_EMC0_HIGH<<0)
#define mskCT16_EMC0_TOGGLE			(CT16_EMC0_TOGGLE<<0)

																//[3:2]CT16Bn PWM1 functionality
#define	CT16_EMC1_DO_NOTHING		0	//Do nothing.
#define	CT16_EMC1_LOW						1	//CT16Bn PWM1 pin is low.
#define	CT16_EMC1_HIGH					2	//CT16Bn PWM1 pin is high.
#define	CT16_EMC1_TOGGLE				3	//Toggle CT16Bn PWM1 pin.
#define mskCT16_EMC1_DO_NOTHING	(CT16_EMC1_LOW<<2)
#define mskCT16_EMC1_LOW				(CT16_EMC1_LOW<<2)
#define mskCT16_EMC1_HIGH				(CT16_EMC1_HIGH<<2)
#define mskCT16_EMC1_TOGGLE			(CT16_EMC1_TOGGLE<<2)

																//[5:4]CT16Bn PWM2 functionality
#define	CT16_EMC2_DO_NOTHING		0	//Do nothing.
#define	CT16_EMC2_LOW						1	//CT16Bn PWM2 pin is low.
#define	CT16_EMC2_HIGH					2	//CT16Bn PWM2 pin is high.
#define	CT16_EMC2_TOGGLE				3	//Toggle CT16Bn PWM2 pin.
#define mskCT16_EMC2_DO_NOTHING	(CT16_EMC2_LOW<<4)
#define mskCT16_EMC2_LOW				(CT16_EMC2_LOW<<4)
#define mskCT16_EMC2_HIGH				(CT16_EMC2_HIGH<<4)
#define mskCT16_EMC2_TOGGLE			(CT16_EMC2_TOGGLE<<4)

																//[7:6]CT16Bn PWM3 functionality
#define	CT16_EMC3_DO_NOTHING		0	//Do nothing.
#define	CT16_EMC3_LOW						1	//CT16Bn PWM3 pin is low.
#define	CT16_EMC3_HIGH					2	//CT16Bn PWM3 pin is high.
#define	CT16_EMC3_TOGGLE				3	//Toggle CT16Bn PWM3 pin.
#define mskCT16_EMC3_DO_NOTHING	(CT16_EMC3_LOW<<6)
#define mskCT16_EMC3_LOW				(CT16_EMC3_LOW<<6)
#define mskCT16_EMC3_HIGH				(CT16_EMC3_HIGH<<6)
#define mskCT16_EMC3_TOGGLE			(CT16_EMC3_TOGGLE<<6)

																//[9:8]CT16Bn PWM4 functionality
#define	CT16_EMC4_DO_NOTHING		0	//Do nothing.
#define	CT16_EMC4_LOW						1	//CT16Bn PWM4 pin is low.
#define	CT16_EMC4_HIGH					2	//CT16Bn PWM4 pin is high.
#define	CT16_EMC4_TOGGLE				3	//Toggle CT16Bn PWM4 pin.
#define mskCT16_EMC4_DO_NOTHING	(CT16_EMC4_LOW<<8)
#define mskCT16_EMC4_LOW				(CT16_EMC4_LOW<<8)
#define mskCT16_EMC4_HIGH				(CT16_EMC4_HIGH<<8)
#define mskCT16_EMC4_TOGGLE			(CT16_EMC4_TOGGLE<<8)

																//[11:10]CT16Bn PWM5 functionality
#define	CT16_EMC5_DO_NOTHING		0	//Do nothing.
#define	CT16_EMC5_LOW						1	//CT16Bn PWM5 pin is low.
#define	CT16_EMC5_HIGH					2	//CT16Bn PWM5 pin is high.
#define	CT16_EMC5_TOGGLE				3	//Toggle CT16Bn PWM5 pin.
#define mskCT16_EMC5_DO_NOTHING	(CT16_EMC5_LOW<<10)
#define mskCT16_EMC5_LOW				(CT16_EMC5_LOW<<10)
#define mskCT16_EMC5_HIGH				(CT16_EMC5_HIGH<<10)
#define mskCT16_EMC5_TOGGLE			(CT16_EMC5_TOGGLE<<10)

																//[13:12]CT16Bn PWM6 functionality
#define	CT16_EMC6_DO_NOTHING		0	//Do nothing.
#define	CT16_EMC6_LOW						1	//CT16Bn PWM6 pin is low.
#define	CT16_EMC6_HIGH					2	//CT16Bn PWM6 pin is high.
#define	CT16_EMC6_TOGGLE				3	//Toggle CT16Bn PWM6 pin.
#define mskCT16_EMC6_DO_NOTHING	(CT16_EMC6_LOW<<12)
#define mskCT16_EMC6_LOW				(CT16_EMC6_LOW<<12)
#define mskCT16_EMC6_HIGH				(CT16_EMC6_HIGH<<12)
#define mskCT16_EMC6_TOGGLE			(CT16_EMC6_TOGGLE<<12)

																//[15:14]CT16Bn PWM7 functionality
#define	CT16_EMC7_DO_NOTHING		0	//Do nothing.
#define	CT16_EMC7_LOW						1	//CT16Bn PWM7 pin is low.
#define	CT16_EMC7_HIGH					2	//CT16Bn PWM7 pin is high.
#define	CT16_EMC7_TOGGLE				3	//Toggle CT16Bn PWM7 pin.
#define mskCT16_EMC7_DO_NOTHING	(CT16_EMC7_LOW<<14)
#define mskCT16_EMC7_LOW				(CT16_EMC7_LOW<<14)
#define mskCT16_EMC7_HIGH				(CT16_EMC7_HIGH<<14)
#define mskCT16_EMC7_TOGGLE			(CT16_EMC7_TOGGLE<<14)

																//[17:16]CT16Bn PWM8 functionality
#define	CT16_EMC8_DO_NOTHING		0	//Do nothing.
#define	CT16_EMC8_LOW						1	//CT16Bn PWM8 pin is low.
#define	CT16_EMC8_HIGH					2	//CT16Bn PWM8 pin is high.
#define	CT16_EMC8_TOGGLE				3	//Toggle CT16Bn PWM8 pin.
#define mskCT16_EMC8_DO_NOTHING	(CT16_EMC8_LOW<<16)
#define mskCT16_EMC8_LOW				(CT16_EMC8_LOW<<16)
#define mskCT16_EMC8_HIGH				(CT16_EMC8_HIGH<<16)
#define mskCT16_EMC8_TOGGLE			(CT16_EMC8_TOGGLE<<16)

																//[19:18]CT16Bn PWM9 functionality
#define	CT16_EMC9_DO_NOTHING		0	//Do nothing.
#define	CT16_EMC9_LOW						1	//CT16Bn PWM9 pin is low.
#define	CT16_EMC9_HIGH					2	//CT16Bn PWM9 pin is high.
#define	CT16_EMC9_TOGGLE				3	//Toggle CT16Bn PWM9 pin.
#define mskCT16_EMC9_DO_NOTHING	(CT16_EMC9_LOW<<18)
#define mskCT16_EMC9_LOW				(CT16_EMC9_LOW<<18)
#define mskCT16_EMC9_HIGH				(CT16_EMC9_HIGH<<18)
#define mskCT16_EMC9_TOGGLE			(CT16_EMC9_TOGGLE<<18)

																	//[21:20]CT16Bn PWM10 functionality
#define	CT16_EMC10_DO_NOTHING			0	//Do nothing.
#define	CT16_EMC10_LOW						1	//CT16Bn PWM10 pin is low.
#define	CT16_EMC10_HIGH						2	//CT16Bn PWM10 pin is high.
#define	CT16_EMC10_TOGGLE					3	//Toggle CT16Bn PWM10 pin.
#define mskCT16_EMC10_DO_NOTHING	(CT16_EMC10_LOW<<20)
#define mskCT16_EMC10_LOW					(CT16_EMC10_LOW<<20)
#define mskCT16_EMC10_HIGH				(CT16_EMC10_HIGH<<20)
#define mskCT16_EMC10_TOGGLE			(CT16_EMC10_TOGGLE<<20)

																	//[23:22]CT16Bn PWM11 functionality
#define	CT16_EMC11_DO_NOTHING			0	//Do nothing.
#define	CT16_EMC11_LOW						1	//CT16Bn PWM11 pin is low.
#define	CT16_EMC11_HIGH						2	//CT16Bn PWM11 pin is high.
#define	CT16_EMC11_TOGGLE					3	//Toggle CT16Bn PWM11 pin.
#define mskCT16_EMC11_DO_NOTHING	(CT16_EMC11_LOW<<22)
#define mskCT16_EMC11_LOW					(CT16_EMC11_LOW<<22)
#define mskCT16_EMC11_HIGH				(CT16_EMC11_HIGH<<22)
#define mskCT16_EMC11_TOGGLE			(CT16_EMC11_TOGGLE<<22)

																	//[25:24]CT16Bn PWM12 functionality
#define	CT16_EMC12_DO_NOTHING			0	//Do nothing.
#define	CT16_EMC12_LOW						1	//CT16Bn PWM12 pin is low.
#define	CT16_EMC12_HIGH						2	//CT16Bn PWM12 pin is high.
#define	CT16_EMC12_TOGGLE					3	//Toggle CT16Bn PWM12 pin.
#define mskCT16_EMC12_DO_NOTHING	(CT16_EMC12_LOW<<24)
#define mskCT16_EMC12_LOW					(CT16_EMC12_LOW<<24)
#define mskCT16_EMC12_HIGH				(CT16_EMC12_HIGH<<24)
#define mskCT16_EMC12_TOGGLE			(CT16_EMC12_TOGGLE<<24)

																	//[27:26]CT16Bn PWM13 functionality
#define	CT16_EMC13_DO_NOTHING			0	//Do nothing.
#define	CT16_EMC13_LOW						1	//CT16Bn PWM13 pin is low.
#define	CT16_EMC13_HIGH						2	//CT16Bn PWM13 pin is high.
#define	CT16_EMC13_TOGGLE					3	//Toggle CT16Bn PWM13 pin.
#define mskCT16_EMC13_DO_NOTHING	(CT16_EMC13_LOW<<26)
#define mskCT16_EMC13_LOW					(CT16_EMC13_LOW<<26)
#define mskCT16_EMC13_HIGH				(CT16_EMC13_HIGH<<26)
#define mskCT16_EMC13_TOGGLE			(CT16_EMC13_TOGGLE<<26)

																	//[29:28]CT16Bn PWM14 functionality
#define	CT16_EMC14_DO_NOTHING			0	//Do nothing.
#define	CT16_EMC14_LOW						1	//CT16Bn PWM14 pin is low.
#define	CT16_EMC14_HIGH						2	//CT16Bn PWM14 pin is high.
#define	CT16_EMC14_TOGGLE					3	//Toggle CT16Bn PWM14 pin.
#define mskCT16_EMC14_DO_NOTHING	(CT16_EMC14_LOW<<28)
#define mskCT16_EMC14_LOW					(CT16_EMC14_LOW<<28)
#define mskCT16_EMC14_HIGH				(CT16_EMC14_HIGH<<28)
#define mskCT16_EMC14_TOGGLE			(CT16_EMC14_TOGGLE<<28)

																	//[31:30]CT16Bn PWM15 functionality
#define	CT16_EMC15_DO_NOTHING			0	//Do nothing.
#define	CT16_EMC15_LOW						1	//CT16Bn PWM15 pin is low.
#define	CT16_EMC15_HIGH						2	//CT16Bn PWM15 pin is high.
#define	CT16_EMC15_TOGGLE					3	//Toggle CT16Bn PWM15 pin.
#define mskCT16_EMC15_DO_NOTHING	(CT16_EMC15_LOW<<30)
#define mskCT16_EMC15_LOW					(CT16_EMC15_LOW<<30)
#define mskCT16_EMC15_HIGH				(CT16_EMC15_HIGH<<30)
#define mskCT16_EMC15_TOGGLE			(CT16_EMC15_TOGGLE<<30)

/* CT16Bn External Match Control register2 <CT16Bn_EMC> (0x90) */
																	//[1:0]CT16Bn PWM16 functionality
#define	CT16_EMC16_DO_NOTHING			0	//Do nothing.
#define	CT16_EMC16_LOW						1	//CT16Bn PWM16 pin is low.
#define	CT16_EMC16_HIGH						2	//CT16Bn PWM16 pin is high.
#define	CT16_EMC16_TOGGLE					3	//Toggle CT16Bn PWM16 pin.
#define mskCT16_EMC16_DO_NOTHING	(CT16_EMC16_LOW<<0)
#define mskCT16_EMC16_LOW					(CT16_EMC16_LOW<<0)
#define mskCT16_EMC16_HIGH				(CT16_EMC16_HIGH<<0)
#define mskCT16_EMC16_TOGGLE			(CT16_EMC16_TOGGLE<<0)

																	//[3:2]CT16Bn PWM17 functionality
#define	CT16_EMC17_DO_NOTHING			0	//Do nothing.
#define	CT16_EMC17_LOW						1	//CT16Bn PWM17 pin is low.
#define	CT16_EMC17_HIGH						2	//CT16Bn PWM17 pin is high.
#define	CT16_EMC17_TOGGLE					3	//Toggle CT16Bn PWM17 pin.
#define mskCT16_EMC17_DO_NOTHING	(CT16_EMC17_LOW<<2)
#define mskCT16_EMC17_LOW					(CT16_EMC17_LOW<<2)
#define mskCT16_EMC17_HIGH				(CT16_EMC17_HIGH<<2)
#define mskCT16_EMC17_TOGGLE			(CT16_EMC17_TOGGLE<<2)

																	//[5:4]CT16Bn PWM18 functionality
#define	CT16_EMC18_DO_NOTHING			0	//Do nothing.
#define	CT16_EMC18_LOW						1	//CT16Bn PWM18 pin is low.
#define	CT16_EMC18_HIGH						2	//CT16Bn PWM18 pin is high.
#define	CT16_EMC18_TOGGLE					3	//Toggle CT16Bn PWM18 pin.
#define mskCT16_EMC18_DO_NOTHING	(CT16_EMC18_LOW<<4)
#define mskCT16_EMC18_LOW					(CT16_EMC18_LOW<<4)
#define mskCT16_EMC18_HIGH				(CT16_EMC18_HIGH<<4)
#define mskCT16_EMC18_TOGGLE			(CT16_EMC18_TOGGLE<<4)

																	//[7:6]CT16Bn PWM19 functionality
#define	CT16_EMC19_DO_NOTHING			0	//Do nothing.
#define	CT16_EMC19_LOW						1	//CT16Bn PWM19 pin is low.
#define	CT16_EMC19_HIGH						2	//CT16Bn PWM19 pin is high.
#define	CT16_EMC19_TOGGLE					3	//Toggle CT16Bn PWM19 pin.
#define mskCT16_EMC19_DO_NOTHING	(CT16_EMC19_LOW<<6)
#define mskCT16_EMC19_LOW					(CT16_EMC19_LOW<<6)
#define mskCT16_EMC19_HIGH				(CT16_EMC19_HIGH<<6)
#define mskCT16_EMC19_TOGGLE			(CT16_EMC19_TOGGLE<<6)

																	//[9:8]CT16Bn PWM20 functionality
#define	CT16_EMC20_DO_NOTHING			0	//Do nothing.
#define	CT16_EMC20_LOW						1	//CT16Bn PWM20 pin is low.
#define	CT16_EMC20_HIGH						2	//CT16Bn PWM20 pin is high.
#define	CT16_EMC20_TOGGLE					3	//Toggle CT16Bn PWM20 pin.
#define mskCT16_EMC20_DO_NOTHING	(CT16_EMC20_LOW<<8)
#define mskCT16_EMC20_LOW					(CT16_EMC20_LOW<<8)
#define mskCT16_EMC20_HIGH				(CT16_EMC20_HIGH<<8)
#define mskCT16_EMC20_TOGGLE			(CT16_EMC20_TOGGLE<<8)

																	//[11:10]CT16Bn PWM21 functionality
#define	CT16_EMC21_DO_NOTHING			0	//Do nothing.
#define	CT16_EMC21_LOW						1	//CT16Bn PWM21 pin is low.
#define	CT16_EMC21_HIGH						2	//CT16Bn PWM21 pin is high.
#define	CT16_EMC21_TOGGLE					3	//Toggle CT16Bn PWM21 pin.
#define mskCT16_EMC21_DO_NOTHING	(CT16_EMC21_LOW<<10)
#define mskCT16_EMC21_LOW					(CT16_EMC21_LOW<<10)
#define mskCT16_EMC21_HIGH				(CT16_EMC21_HIGH<<10)
#define mskCT16_EMC21_TOGGLE			(CT16_EMC21_TOGGLE<<10)

																	//[13:12]CT16Bn PWM22 functionality
#define	CT16_EMC22_DO_NOTHING			0	//Do nothing.
#define	CT16_EMC22_LOW						1	//CT16Bn PWM22 pin is low.
#define	CT16_EMC22_HIGH						2	//CT16Bn PWM22 pin is high.
#define	CT16_EMC22_TOGGLE					3	//Toggle CT16Bn PWM22 pin.
#define mskCT16_EMC22_DO_NOTHING	(CT16_EMC22_LOW<<12)
#define mskCT16_EMC22_LOW					(CT16_EMC22_LOW<<12)
#define mskCT16_EMC22_HIGH				(CT16_EMC22_HIGH<<12)
#define mskCT16_EMC22_TOGGLE			(CT16_EMC22_TOGGLE<<12)

																	//[15:14]CT16Bn PWM23	functionality
#define	CT16_EMC23_DO_NOTHING			0	//Do nothing.
#define	CT16_EMC23_LOW						1	//CT16Bn PWM23 pin is low.
#define	CT16_EMC23_HIGH						2	//CT16Bn PWM23 pin is high.
#define	CT16_EMC23_TOGGLE					3	//Toggle CT16Bn PWM23 pin.
#define mskCT16_EMC23_DO_NOTHING	(CT16_EMC23_LOW<<14)
#define mskCT16_EMC23_LOW					(CT16_EMC23_LOW<<14)
#define mskCT16_EMC23_HIGH				(CT16_EMC23_HIGH<<14)
#define mskCT16_EMC23_TOGGLE			(CT16_EMC23_TOGGLE<<14)

/* CT16Bn PWM Control register <CT16Bn_PWMCTRL> (0x94) */
																	//[1:0] CT16Bn PWM0 output mode.
#define	CT16_PWM0MODE_1						0	// PWM mode 1.
#define	CT16_PWM0MODE_2						1 // PWM mode 2.
#define	CT16_PWM0MODE_FORCE_0			2 // Force 0.
#define	CT16_PWM0MODE_FORCE_1			3 // Force 1.
#define mskCT16_PWM0MODE_1				(CT16_PWM0MODE_1<<0)
#define mskCT16_PWM0MODE_2				(CT16_PWM0MODE_2<<0)
#define mskCT16_PWM0MODE_FORCE_0	(CT16_PWM0MODE_FORCE_0<<0)
#define mskCT16_PWM0MODE_FORCE_1	(CT16_PWM0MODE_FORCE_1<<0)

																	//[3:2] CT16Bn PWM1 output mode.
#define	CT16_PWM1MODE_1						0	// PWM mode 1.
#define	CT16_PWM1MODE_2						1 // PWM mode 2.
#define	CT16_PWM1MODE_FORCE_0			2 // Force 0.
#define	CT16_PWM1MODE_FORCE_1			3 // Force 1.
#define mskCT16_PWM1MODE_1				(CT16_PWM1MODE_1<<2)
#define mskCT16_PWM1MODE_2				(CT16_PWM1MODE_2<<2)
#define mskCT16_PWM1MODE_FORCE_0	(CT16_PWM1MODE_FORCE_0<<2)
#define mskCT16_PWM1MODE_FORCE_1	(CT16_PWM1MODE_FORCE_1<<2)

																	//[5:4] CT16Bn PWM2 output mode.
#define	CT16_PWM2MODE_1						0	// PWM mode 1.
#define	CT16_PWM2MODE_2						1 // PWM mode 2.
#define	CT16_PWM2MODE_FORCE_0			2 // Force 0.
#define	CT16_PWM2MODE_FORCE_1			3 // Force 1.
#define mskCT16_PWM2MODE_1				(CT16_PWM2MODE_1<<4)
#define mskCT16_PWM2MODE_2				(CT16_PWM2MODE_2<<4)
#define mskCT16_PWM2MODE_FORCE_0	(CT16_PWM2MODE_FORCE_0<<4)
#define mskCT16_PWM2MODE_FORCE_1	(CT16_PWM2MODE_FORCE_1<<4)

																	//[7:6] CT16Bn PWM3 output mode.
#define	CT16_PWM3MODE_1						0	// PWM mode 1.
#define	CT16_PWM3MODE_2						1 // PWM mode 2.
#define	CT16_PWM3MODE_FORCE_0			2 // Force 0.
#define	CT16_PWM3MODE_FORCE_1			3 // Force 1.
#define mskCT16_PWM3MODE_1				(CT16_PWM3MODE_1<<6)
#define mskCT16_PWM3MODE_2				(CT16_PWM3MODE_2<<6)
#define mskCT16_PWM3MODE_FORCE_0	(CT16_PWM3MODE_FORCE_0<<6)
#define mskCT16_PWM3MODE_FORCE_1	(CT16_PWM3MODE_FORCE_1<<6)

																	//[9:8] CT16Bn PWM4 output mode.
#define	CT16_PWM4MODE_1						0	// PWM mode 1.
#define	CT16_PWM4MODE_2						1 // PWM mode 2.
#define	CT16_PWM4MODE_FORCE_0			2 // Force 0.
#define	CT16_PWM4MODE_FORCE_1			3 // Force 1.
#define mskCT16_PWM4MODE_1				(CT16_PWM4MODE_1<<8)
#define mskCT16_PWM4MODE_2				(CT16_PWM4MODE_2<<8)
#define mskCT16_PWM4MODE_FORCE_0	(CT16_PWM4MODE_FORCE_0<<8)
#define mskCT16_PWM4MODE_FORCE_1	(CT16_PWM4MODE_FORCE_1<<8)

																	//[11:10] CT16Bn PWM5 output mode.
#define	CT16_PWM5MODE_1					0	// PWM mode 1.
#define	CT16_PWM5MODE_2					1 // PWM mode 2.
#define	CT16_PWM5MODE_FORCE_0		2 // Force 0.
#define	CT16_PWM5MODE_FORCE_1		3 // Force 1.
#define mskCT16_PWM5MODE_1				(CT16_PWM5MODE_1<<10)
#define mskCT16_PWM5MODE_2				(CT16_PWM5MODE_2<<10)
#define mskCT16_PWM5MODE_FORCE_0	(CT16_PWM5MODE_FORCE_0<<10)
#define mskCT16_PWM5MODE_FORCE_1	(CT16_PWM5MODE_FORCE_1<<10)

																	//[13:12] CT16Bn PWM6 output mode.
#define	CT16_PWM6MODE_1					0	// PWM mode 1.
#define	CT16_PWM6MODE_2					1 // PWM mode 2.
#define	CT16_PWM6MODE_FORCE_0		2 // Force 0.
#define	CT16_PWM6MODE_FORCE_1		3 // Force 1.
#define mskCT16_PWM6MODE_1				(CT16_PWM6MODE_1<<12)
#define mskCT16_PWM6MODE_2				(CT16_PWM6MODE_2<<12)
#define mskCT16_PWM6MODE_FORCE_0	(CT16_PWM6MODE_FORCE_0<<12)
#define mskCT16_PWM6MODE_FORCE_1	(CT16_PWM6MODE_FORCE_1<<12)

																	//[15:14] CT16Bn PWM7 output mode.
#define	CT16_PWM7MODE_1						0	// PWM mode 1.
#define	CT16_PWM7MODE_2						1 // PWM mode 2.
#define	CT16_PWM7MODE_FORCE_0			2 // Force 0.
#define	CT16_PWM7MODE_FORCE_1			3 // Force 1.
#define mskCT16_PWM7MODE_1				(CT16_PWM7MODE_1<<14)
#define mskCT16_PWM7MODE_2				(CT16_PWM7MODE_2<<14)
#define mskCT16_PWM7MODE_FORCE_0	(CT16_PWM7MODE_FORCE_0<<14)
#define mskCT16_PWM7MODE_FORCE_1	(CT16_PWM7MODE_FORCE_1<<14)

																	//[17:16] CT16Bn PWM8 output mode.
#define	CT16_PWM8MODE_1						0	// PWM mode 1.
#define	CT16_PWM8MODE_2						1 // PWM mode 2.
#define	CT16_PWM8MODE_FORCE_0			2 // Force 0.
#define	CT16_PWM8MODE_FORCE_1			3 // Force 1.
#define mskCT16_PWM8MODE_1				(CT16_PWM8MODE_1<<16)
#define mskCT16_PWM8MODE_2				(CT16_PWM8MODE_2<<16)
#define mskCT16_PWM8MODE_FORCE_0	(CT16_PWM8MODE_FORCE_0<<16)
#define mskCT16_PWM8MODE_FORCE_1	(CT16_PWM8MODE_FORCE_1<<16)

																	//[19:18] CT16Bn PWM9 output mode.
#define	CT16_PWM9MODE_1						0	// PWM mode 1.
#define	CT16_PWM9MODE_2						1 // PWM mode 2.
#define	CT16_PWM9MODE_FORCE_0			2 // Force 0.
#define	CT16_PWM9MODE_FORCE_1			3 // Force 1.
#define mskCT16_PWM9MODE_1				(CT16_PWM9MODE_1<<18)
#define mskCT16_PWM9MODE_2				(CT16_PWM9MODE_2<<18)
#define mskCT16_PWM9MODE_FORCE_0	(CT16_PWM9MODE_FORCE_0<<18)
#define mskCT16_PWM9MODE_FORCE_1	(CT16_PWM9MODE_FORCE_1<<18)

																	//[21:20] CT16Bn PWM10 output mode.
#define	CT16_PWM10MODE_1						0	// PWM mode 1.
#define	CT16_PWM10MODE_2						1 // PWM mode 2.
#define	CT16_PWM10MODE_FORCE_0			2 // Force 0.
#define	CT16_PWM10MODE_FORCE_1			3 // Force 1.
#define mskCT16_PWM10MODE_1				(CT16_PWM10MODE_1<<20)
#define mskCT16_PWM10MODE_2				(CT16_PWM10MODE_2<<20)
#define mskCT16_PWM10MODE_FORCE_0	(CT16_PWM10MODE_FORCE_0<<20)
#define mskCT16_PWM10MODE_FORCE_1	(CT16_PWM10MODE_FORCE_1<<20)

																	//[23:22] CT16Bn PWM11 output mode.
#define	CT16_PWM11MODE_1						0	// PWM mode 1.
#define	CT16_PWM11MODE_2						1 // PWM mode 2.
#define	CT16_PWM11MODE_FORCE_0			2 // Force 0.
#define	CT16_PWM11MODE_FORCE_1			3 // Force 1.
#define mskCT16_PWM11MODE_1				(CT16_PWM11MODE_1<<22)
#define mskCT16_PWM11MODE_2				(CT16_PWM11MODE_2<<22)
#define mskCT16_PWM11MODE_FORCE_0	(CT16_PWM11MODE_FORCE_0<<22)
#define mskCT16_PWM11MODE_FORCE_1	(CT16_PWM11MODE_FORCE_1<<22)

																	//[25:24] CT16Bn PWM12 output mode.
#define	CT16_PWM12MODE_1						0	// PWM mode 1.
#define	CT16_PWM12MODE_2						1 // PWM mode 2.
#define	CT16_PWM12MODE_FORCE_0			2 // Force 0.
#define	CT16_PWM12MODE_FORCE_1			3 // Force 1.
#define mskCT16_PWM12MODE_1				(CT16_PWM12MODE_1<<24)
#define mskCT16_PWM12MODE_2				(CT16_PWM12MODE_2<<24)
#define mskCT16_PWM12MODE_FORCE_0	(CT16_PWM12MODE_FORCE_0<<24)
#define mskCT16_PWM12MODE_FORCE_1	(CT16_PWM12MODE_FORCE_1<<24)

																	//[27:26] CT16Bn PWM13 output mode.
#define	CT16_PWM13MODE_1						0	// PWM mode 1.
#define	CT16_PWM13MODE_2						1 // PWM mode 2.
#define	CT16_PWM13MODE_FORCE_0			2 // Force 0.
#define	CT16_PWM13MODE_FORCE_1			3 // Force 1.
#define mskCT16_PWM13MODE_1				(CT16_PWM13MODE_1<<26)
#define mskCT16_PWM13MODE_2				(CT16_PWM13MODE_2<<26)
#define mskCT16_PWM13MODE_FORCE_0	(CT16_PWM13MODE_FORCE_0<<26)
#define mskCT16_PWM13MODE_FORCE_1	(CT16_PWM13MODE_FORCE_1<<26)

																	//[29:28] CT16Bn PWM14 output mode.
#define	CT16_PWM14MODE_1						0	// PWM mode 1.
#define	CT16_PWM14MODE_2						1 // PWM mode 2.
#define	CT16_PWM14MODE_FORCE_0			2 // Force 0.
#define	CT16_PWM14MODE_FORCE_1			3 // Force 1.
#define mskCT16_PWM14MODE_1				(CT16_PWM14MODE_1<<28)
#define mskCT16_PWM14MODE_2				(CT16_PWM14MODE_2<<28)
#define mskCT16_PWM14MODE_FORCE_0	(CT16_PWM14MODE_FORCE_0<<28)
#define mskCT16_PWM14MODE_FORCE_1	(CT16_PWM14MODE_FORCE_1<<28)

																	//[31:30] CT16Bn PWM15 output mode.
#define	CT16_PWM15MODE_1						0	// PWM mode 1.
#define	CT16_PWM15MODE_2						1 // PWM mode 2.
#define	CT16_PWM15MODE_FORCE_0			2 // Force 0.
#define	CT16_PWM15MODE_FORCE_1			3 // Force 1.
#define mskCT16_PWM15MODE_1				(CT16_PWM15MODE_1<<30)
#define mskCT16_PWM15MODE_2				(CT16_PWM15MODE_2<<30)
#define mskCT16_PWM15MODE_FORCE_0	(CT16_PWM15MODE_FORCE_0<<30)
#define mskCT16_PWM15MODE_FORCE_1	(CT16_PWM15MODE_FORCE_1<<30)

/* CT16Bn PWM Control register <CT16Bn_PWMCTRL> (0x98) */
																	//[1:0] CT16Bn PWM16 output mode.
#define	CT16_PWM16MODE_1						0	// PWM mode 1.
#define	CT16_PWM16MODE_2						1 // PWM mode 2.
#define	CT16_PWM16MODE_FORCE_0			2 // Force 0.
#define	CT16_PWM16MODE_FORCE_1			3 // Force 1.
#define mskCT16_PWM16MODE_1				(CT16_PWM16MODE_1<<0)
#define mskCT16_PWM16MODE_2				(CT16_PWM16MODE_2<<0)
#define mskCT16_PWM16MODE_FORCE_0	(CT16_PWM16MODE_FORCE_0<<0)
#define mskCT16_PWM16MODE_FORCE_1	(CT16_PWM16MODE_FORCE_1<<0)

																	//[3:2] CT16Bn PWM17 output mode.
#define	CT16_PWM17MODE_1						0	// PWM mode 1.
#define	CT16_PWM17MODE_2						1 // PWM mode 2.
#define	CT16_PWM17MODE_FORCE_0			2 // Force 0.
#define	CT16_PWM17MODE_FORCE_1			3 // Force 1.
#define mskCT16_PWM17MODE_1				(CT16_PWM17MODE_1<<2)
#define mskCT16_PWM17MODE_2				(CT16_PWM17MODE_2<<2)
#define mskCT16_PWM17MODE_FORCE_0	(CT16_PWM17MODE_FORCE_0<<2)
#define mskCT16_PWM17MODE_FORCE_1	(CT16_PWM17MODE_FORCE_1<<2)

																	//[5:4] CT16Bn PWM18 output mode.
#define	CT16_PWM18MODE_1						0	// PWM mode 1.
#define	CT16_PWM18MODE_2						1 // PWM mode 2.
#define	CT16_PWM18MODE_FORCE_0			2 // Force 0.
#define	CT16_PWM18MODE_FORCE_1			3 // Force 1.
#define mskCT16_PWM18MODE_1				(CT16_PWM18MODE_1<<4)
#define mskCT16_PWM18MODE_2				(CT16_PWM18MODE_2<<4)
#define mskCT16_PWM18MODE_FORCE_0	(CT16_PWM18MODE_FORCE_0<<4)
#define mskCT16_PWM18MODE_FORCE_1	(CT16_PWM18MODE_FORCE_1<<4)

																	//[7:6] CT16Bn PWM19 output mode.
#define	CT16_PWM19MODE_1						0	// PWM mode 1.
#define	CT16_PWM19MODE_2						1 // PWM mode 2.
#define	CT16_PWM19MODE_FORCE_0			2 // Force 0.
#define	CT16_PWM19MODE_FORCE_1			3 // Force 1.
#define mskCT16_PWM19MODE_1				(CT16_PWM19MODE_1<<6)
#define mskCT16_PWM19MODE_2				(CT16_PWM19MODE_2<<6)
#define mskCT16_PWM19MODE_FORCE_0	(CT16_PWM19MODE_FORCE_0<<6)
#define mskCT16_PWM19MODE_FORCE_1	(CT16_PWM19MODE_FORCE_1<<6)

																	//[9:8] CT16Bn PWM20 output mode.
#define	CT16_PWM20MODE_1						0	// PWM mode 1.
#define	CT16_PWM20MODE_2						1 // PWM mode 2.
#define	CT16_PWM20MODE_FORCE_0			2 // Force 0.
#define	CT16_PWM20MODE_FORCE_1			3 // Force 1.
#define mskCT16_PWM20MODE_1				(CT16_PWM20MODE_1<<8)
#define mskCT16_PWM20MODE_2				(CT16_PWM20MODE_2<<8)
#define mskCT16_PWM20MODE_FORCE_0	(CT16_PWM20MODE_FORCE_0<<8)
#define mskCT16_PWM20MODE_FORCE_1	(CT16_PWM20MODE_FORCE_1<<8)

																	//[11:10] CT16Bn PWM21 output mode.
#define	CT16_PWM21MODE_1					0	// PWM mode 1.
#define	CT16_PWM21MODE_2					1 // PWM mode 2.
#define	CT16_PWM21MODE_FORCE_0		2 // Force 0.
#define	CT16_PWM21MODE_FORCE_1		3 // Force 1.
#define mskCT16_PWM21MODE_1				(CT16_PWM21MODE_1<<10)
#define mskCT16_PWM21MODE_2				(CT16_PWM21MODE_2<<10)
#define mskCT16_PWM21MODE_FORCE_0	(CT16_PWM21MODE_FORCE_0<<10)
#define mskCT16_PWM21MODE_FORCE_1	(CT16_PWM21MODE_FORCE_1<<10)

																	//[13:12] CT16Bn PWM22 output mode.
#define	CT16_PWM22MODE_1					0	// PWM mode 1.
#define	CT16_PWM22MODE_2					1 // PWM mode 2.
#define	CT16_PWM22MODE_FORCE_0		2 // Force 0.
#define	CT16_PWM22MODE_FORCE_1		3 // Force 1.
#define mskCT16_PWM22MODE_1				(CT16_PWM22MODE_1<<12)
#define mskCT16_PWM22MODE_2				(CT16_PWM22MODE_2<<12)
#define mskCT16_PWM22MODE_FORCE_0	(CT16_PWM22MODE_FORCE_0<<12)
#define mskCT16_PWM22MODE_FORCE_1	(CT16_PWM22MODE_FORCE_1<<12)

																	//[15:14] CT16Bn PWM23 output mode.
#define	CT16_PWM23MODE_1					0	// PWM mode 1.
#define	CT16_PWM23MODE_2					1 // PWM mode 2.
#define	CT16_PWM23MODE_FORCE_0		2 // Force 0.
#define	CT16_PWM23MODE_FORCE_1		3 // Force 1.
#define mskCT16_PWM23MODE_1				(CT16_PWM23MODE_1<<14)
#define mskCT16_PWM23MODE_2				(CT16_PWM23MODE_2<<14)
#define mskCT16_PWM23MODE_FORCE_0	(CT16_PWM23MODE_FORCE_0<<14)
#define mskCT16_PWM23MODE_FORCE_1	(CT16_PWM23MODE_FORCE_1<<14)

/* CT16Bn PWM Enable register <CT16Bn_PWMENB> (0x9C) */
																	//[0:0] CT16Bn PWM0 enable.
#define	CT16_PWM0EN_EN						1	// CT16Bn PWM0 is enabled for PWM mode.
#define	CT16_PWM0EN_EM0						0 // CT16Bn PWM0 is controlled by EM0.
#define mskCT16_PWM0EN_EN					(CT16_PWM0EN_EN<<0)
#define mskCT16_PWM0EN_EM0				(CT16_PWM0EN_EM0<<0)

																	//[1:1] CT16Bn PWM1 enable.
#define	CT16_PWM1EN_EN						1	// CT16Bn PWM1 is enabled for PWM mode.
#define	CT16_PWM1EN_EM1						0 // CT16Bn PWM1 is controlled by EM1.
#define mskCT16_PWM1EN_EN					(CT16_PWM1EN_EN<<1)
#define mskCT16_PWM1EN_EM1				(CT16_PWM1EN_EM1<<1)

																	//[2:2] CT16Bn PWM2 enable.
#define	CT16_PWM2EN_EN						1	// CT16Bn PWM2 is enabled for PWM mode.
#define	CT16_PWM2EN_EM2						0 // CT16Bn PWM2 is controlled by EM2.
#define mskCT16_PWM2EN_EN					(CT16_PWM2EN_EN<<2)
#define mskCT16_PWM2EN_EM2				(CT16_PWM2EN_EM2<<2)

																	//[3:3] CT16Bn PWM3 enable.
#define	CT16_PWM3EN_EN						1	// CT16Bn PWM3 is enabled for PWM mode.
#define	CT16_PWM3EN_EM3						0 // CT16Bn PWM3 is controlled by EM3.
#define mskCT16_PWM3EN_EN					(CT16_PWM3EN_EN<<3)
#define mskCT16_PWM3EN_EM3				(CT16_PWM3EN_EM3<<3)

																	//[4:4] CT16Bn PWM4 enable.
#define	CT16_PWM4EN_EN						1	// CT16Bn PWM4 is enabled for PWM mode.
#define	CT16_PWM4EN_EM4						0 // CT16Bn PWM4 is controlled by EM4.
#define mskCT16_PWM4EN_EN					(CT16_PWM4EN_EN<<4)
#define mskCT16_PWM4EN_EM4				(CT16_PWM4EN_EM4<<4)

																	//[5:5] CT16Bn PWM5 enable.
#define	CT16_PWM5EN_EN						1	// CT16Bn PWM5 is enabled for PWM mode.
#define	CT16_PWM5EN_EM5						0 // CT16Bn PWM5 is controlled by EM5.
#define mskCT16_PWM5EN_EN					(CT16_PWM5EN_EN<<5)
#define mskCT16_PWM5EN_EM5				(CT16_PWM5EN_EM5<<5)

																	//[6:6] CT16Bn PWM6 enable.
#define	CT16_PWM6EN_EN						1	// CT16Bn PWM6 is enabled for PWM mode.
#define	CT16_PWM6EN_EM6						0 // CT16Bn PWM6 is controlled by EM6.
#define mskCT16_PWM6EN_EN					(CT16_PWM6EN_EN<<6)
#define mskCT16_PWM6EN_EM6				(CT16_PWM6EN_EM6<<6)

																	//[7:7] CT16Bn PWM7 enable.
#define	CT16_PWM7EN_EN						1	// CT16Bn PWM7 is enabled for PWM mode.
#define	CT16_PWM7EN_EM7						0 // CT16Bn PWM7 is controlled by EM7.
#define mskCT16_PWM7EN_EN					(CT16_PWM7EN_EN<<7)
#define mskCT16_PWM7EN_EM7				(CT16_PWM7EN_EM7<<7)

																	//[8:8] CT16Bn PWM8 enable.
#define	CT16_PWM8EN_EN						1	// CT16Bn PWM8 is enabled for PWM mode.
#define	CT16_PWM8EN_EM8						0 // CT16Bn PWM8 is controlled by EM8.
#define mskCT16_PWM8EN_EN					(CT16_PWM8EN_EN<<8)
#define mskCT16_PWM8EN_EM8				(CT16_PWM8EN_EM8<<8)

																	//[9:9] CT16Bn PWM9 enable.
#define	CT16_PWM9EN_EN						1	// CT16Bn PWM9 is enabled for PWM mode.
#define	CT16_PWM9EN_EM9						0 // CT16Bn PWM9 is controlled by EM9.
#define mskCT16_PWM9EN_EN					(CT16_PWM9EN_EN<<9)
#define mskCT16_PWM9EN_EM9				(CT16_PWM9EN_EM9<<9)

																	//[10:10] CT16Bn PWM10 enable.
#define	CT16_PWM10EN_EN						1	// CT16Bn PWM10 is enabled for PWM mode.
#define	CT16_PWM10EN_EM10					0 // CT16Bn PWM10 is controlled by EM10.
#define mskCT16_PWM10EN_EN				(CT16_PWM10EN_EN<<10)
#define mskCT16_PWM10EN_EM10			(CT16_PWM10EN_EM10<<10)

																	//[11:11] CT16Bn PWM11 enable.
#define	CT16_PWM11EN_EN						1	// CT16Bn PWM11 is enabled for PWM mode.
#define	CT16_PWM11EN_EM11					0 // CT16Bn PWM11 is controlled by EM11.
#define mskCT16_PWM11EN_EN				(CT16_PWM11EN_EN<<11)
#define mskCT16_PWM11EN_EM11			(CT16_PWM11EN_EM11<<11)

																	//[12:12] CT16Bn PWM12 enable.
#define	CT16_PWM12EN_EN						1	// CT16Bn PWM12 is enabled for PWM mode.
#define	CT16_PWM12EN_EM12					0 // CT16Bn PWM12 is controlled by EM12.
#define mskCT16_PWM12EN_EN				(CT16_PWM12EN_EN<<12)
#define mskCT16_PWM12EN_EM12			(CT16_PWM12EN_EM12<<12)

																	//[13:13] CT16Bn PWM13 enable.
#define	CT16_PWM13EN_EN						1	// CT16Bn PWM13 is enabled for PWM mode.
#define	CT16_PWM13EN_EM13					0 // CT16Bn PWM13 is controlled by EM13.
#define mskCT16_PWM13EN_EN				(CT16_PWM13EN_EN<<13)
#define mskCT16_PWM13EN_EM13			(CT16_PWM13EN_EM13<<13)

																	//[14:14] CT16Bn PWM14 enable.
#define	CT16_PWM14EN_EN						1	// CT16Bn PWM14 is enabled for PWM mode.
#define	CT16_PWM14EN_EM14					0 // CT16Bn PWM14 is controlled by EM14.
#define mskCT16_PWM14EN_EN				(CT16_PWM14EN_EN<<14)
#define mskCT16_PWM14EN_EM14			(CT16_PWM14EN_EM14<<14)

																	//[15:15] CT16Bn PWM15 enable.
#define	CT16_PWM15EN_EN						1	// CT16Bn PWM15 is enabled for PWM mode.
#define	CT16_PWM15EN_EM15					0 // CT16Bn PWM15 is controlled by EM15.
#define mskCT16_PWM15EN_EN				(CT16_PWM15EN_EN<<15)
#define mskCT16_PWM15EN_EM15			(CT16_PWM15EN_EM15<<15)

																	//[16:16] CT16Bn PWM16 enable.
#define	CT16_PWM16EN_EN						1	// CT16Bn PWM16 is enabled for PWM mode.
#define	CT16_PWM16EN_EM16					0 // CT16Bn PWM16 is controlled by EM16.
#define mskCT16_PWM16EN_EN				(CT16_PWM16EN_EN<<16)
#define mskCT16_PWM16EN_EM16			(CT16_PWM16EN_EM16<<16)

																	//[17:17] CT16Bn PWM17 enable.
#define	CT16_PWM17EN_EN						1	// CT16Bn PWM17 is enabled for PWM mode.
#define	CT16_PWM17EN_EM17					0 // CT16Bn PWM17 is controlled by EM17.
#define mskCT16_PWM17EN_EN				(CT16_PWM17EN_EN<<17)
#define mskCT16_PWM17EN_EM17			(CT16_PWM17EN_EM17<<17)

																	//[18:18] CT16Bn PWM18 enable.
#define	CT16_PWM18EN_EN						1	// CT16Bn PWM18 is enabled for PWM mode.
#define	CT16_PWM18EN_EM18					0 // CT16Bn PWM18 is controlled by EM18.
#define mskCT16_PWM18EN_EN				(CT16_PWM18EN_EN<<18)
#define mskCT16_PWM18EN_EM18			(CT16_PWM18EN_EM18<<18)

																	//[19:19] CT16Bn PWM19 enable.
#define	CT16_PWM19EN_EN						1	// CT16Bn PWM19 is enabled for PWM mode.
#define	CT16_PWM19EN_EM19					0 // CT16Bn PWM19 is controlled by EM19.
#define mskCT16_PWM19EN_EN				(CT16_PWM19EN_EN<<19)
#define mskCT16_PWM19EN_EM19			(CT16_PWM19EN_EM19<<19)

																	//[20:20] CT16Bn PWM20 enable.
#define	CT16_PWM20EN_EN						1	// CT16Bn PWM20 is enabled for PWM mode.
#define	CT16_PWM20EN_EM20					0 // CT16Bn PWM20 is controlled by EM20.
#define mskCT16_PWM20EN_EN				(CT16_PWM20EN_EN<<20)
#define mskCT16_PWM20EN_EM20			(CT16_PWM20EN_EM20<<20)

																	//[21:21] CT16Bn PWM21 enable.
#define	CT16_PWM21EN_EN						1	// CT16Bn PWM21 is enabled for PWM mode.
#define	CT16_PWM21EN_EM21					0 // CT16Bn PWM21 is controlled by EM21.
#define mskCT16_PWM21EN_EN				(CT16_PWM21EN_EN<<21)
#define mskCT16_PWM21EN_EM21			(CT16_PWM21EN_EM21<<21)

																	//[22:22] CT16Bn PWM22 enable.
#define	CT16_PWM22EN_EN						1	// CT16Bn PWM22 is enabled for PWM mode.
#define	CT16_PWM22EN_EM22					0 // CT16Bn PWM22 is controlled by EM22.
#define mskCT16_PWM22EN_EN				(CT16_PWM22EN_EN<<22)
#define mskCT16_PWM22EN_EM22			(CT16_PWM22EN_EM2<<22)

																	//[23:23] CT16Bn PWM23 enable.
#define	CT16_PWM23EN_EN						1	// CT16Bn PWM23 is enabled for PWM mode.
#define	CT16_PWM23EN_EM23					0 // CT16Bn PWM23 is controlled by EM23.
#define mskCT16_PWM23EN_EN				(CT16_PWM23EN_EN<<23)
#define mskCT16_PWM23EN_EM23			(CT16_PWM23EN_EM3<<23)

/* CT16Bn PWM IO Enable register <CT16Bn_PWMIOENB> (0xA0) */
																	//[0:0] CT16Bn PWM0 IO selection.
#define	CT16_PWM0IOEN_EN					1	// PWM0 pin acts as match output.
#define	CT16_PWM0IOEN_DIS					0	// PWM0 pin acts as GPIO.
#define mskCT16_PWM0IOEN_EN				(CT16_PWM0IOEN_EN<<0)
#define mskCT16_PWM0IOEN_DIS			(CT16_PWM0IOEN_DIS<<0)

																	//[1:1] CT16Bn PWM1 IO selection.
#define	CT16_PWM1IOEN_EN					1	// PWM1 pin acts as match output.
#define	CT16_PWM1IOEN_DIS					0	// PWM1 pin acts as GPIO.
#define mskCT16_PWM1IOEN_EN				(CT16_PWM1IOEN_EN<<1)
#define mskCT16_PWM1IOEN_DIS			(CT16_PWM1IOEN_DIS<<1)

																	//[2:2] CT16Bn PWM2 IO selection.
#define	CT16_PWM2IOEN_EN					1	// PWM2 pin acts as match output.
#define	CT16_PWM2IOEN_DIS					0	// PWM2 pin acts as GPIO.
#define mskCT16_PWM2IOEN_EN				(CT16_PWM2IOEN_EN<<2)
#define mskCT16_PWM2IOEN_DIS			(CT16_PWM2IOEN_DIS<<2)

																	//[3:3] CT16Bn PWM3 IO selection.
#define	CT16_PWM3IOEN_EN					1	// PWM3 pin acts as match output.
#define	CT16_PWM3IOEN_DIS					0	// PWM3 pin acts as GPIO.
#define mskCT16_PWM3IOEN_EN				(CT16_PWM3IOEN_EN<<3)
#define mskCT16_PWM3IOEN_DIS			(CT16_PWM3IOEN_DIS<<3)

																	//[4:4] CT16Bn PWM4 IO selection.
#define	CT16_PWM4IOEN_EN					1	// PWM4 pin acts as match output.
#define	CT16_PWM4IOEN_DIS					0	// PWM4 pin acts as GPIO.
#define mskCT16_PWM4IOEN_EN				(CT16_PWM4IOEN_EN<<4)
#define mskCT16_PWM4IOEN_DIS			(CT16_PWM4IOEN_DIS<<4)

																	//[5:5] CT16Bn PWM5 IO selection.
#define	CT16_PWM5IOEN_EN					1	// PWM5 pin acts as match output.
#define	CT16_PWM5IOEN_DIS					0	// PWM5 pin acts as GPIO.
#define mskCT16_PWM5IOEN_EN				(CT16_PWM5IOEN_EN<<5)
#define mskCT16_PWM5IOEN_DIS			(CT16_PWM5IOEN_DIS<<5)

																	//[6:6] CT16Bn PWM6 IO selection.
#define	CT16_PWM6IOEN_EN					1	// PWM6 pin acts as match output.
#define	CT16_PWM6IOEN_DIS					0	// PWM6 pin acts as GPIO.
#define mskCT16_PWM6IOEN_EN				(CT16_PWM6IOEN_EN<<6)
#define mskCT16_PWM6IOEN_DIS			(CT16_PWM6IOEN_DIS<<6)

																	//[7:7] CT16Bn PWM7 IO selection.
#define	CT16_PWM7IOEN_EN					1	// PWM7 pin acts as match output.
#define	CT16_PWM7IOEN_DIS					0	// PWM7 pin acts as GPIO.
#define mskCT16_PWM7IOEN_EN				(CT16_PWM7IOEN_EN<<7)
#define mskCT16_PWM7IOEN_DIS			(CT16_PWM7IOEN_DIS<<7)

																	//[8:8] CT16Bn PWM8 IO selection.
#define	CT16_PWM8IOEN_EN					1	// PWM8 pin acts as match output.
#define	CT16_PWM8IOEN_DIS					0	// PWM8 pin acts as GPIO.
#define mskCT16_PWM8IOEN_EN				(CT16_PWM8IOEN_EN<<8)
#define mskCT16_PWM8IOEN_DIS			(CT16_PWM8IOEN_DIS<<8)

																	//[9:9] CT16Bn PWM9 IO selection.
#define	CT16_PWM9IOEN_EN					1	// PWM9 pin acts as match output.
#define	CT16_PWM9IOEN_DIS					0	// PWM9 pin acts as GPIO.
#define mskCT16_PWM9IOEN_EN				(CT16_PWM9IOEN_EN<<9)
#define mskCT16_PWM9IOEN_DIS			(CT16_PWM9IOEN_DIS<<9)

																	//[10:10] CT16Bn PWM10 IO selection.
#define	CT16_PWM10IOEN_EN					1	// PWM10 pin acts as match output.
#define	CT16_PWM10IOEN_DIS				0	// PWM10 pin acts as GPIO.
#define mskCT16_PWM10IOEN_EN			(CT16_PWM10IOEN_EN<<10)
#define mskCT16_PWM10IOEN_DIS			(CT16_PWM10IOEN_DIS<<10)

																	//[11:11] CT16Bn PWM11 IO selection.
#define	CT16_PWM11IOEN_EN					1	// PWM11 pin acts as match output.
#define	CT16_PWM11IOEN_DIS				0	// PWM11 pin acts as GPIO.
#define mskCT16_PWM11IOEN_EN			(CT16_PWM11IOEN_EN<<11)
#define mskCT16_PWM11IOEN_DIS			(CT16_PWM11IOEN_DIS<<11)

																	//[12:12] CT16Bn PWM12 IO selection.
#define	CT16_PWM12IOEN_EN					1	// PWM12 pin acts as match output.
#define	CT16_PWM12IOEN_DIS				0	// PWM12 pin acts as GPIO.
#define mskCT16_PWM12IOEN_EN			(CT16_PWM12IOEN_EN<<12)
#define mskCT16_PWM12IOEN_DIS			(CT16_PWM12IOEN_DIS<<12)

																	//[13:13] CT16Bn PWM13 IO selection.
#define	CT16_PWM13IOEN_EN					1	// PWM13 pin acts as match output.
#define	CT16_PWM13IOEN_DIS				0	// PWM13 pin acts as GPIO.
#define mskCT16_PWM13IOEN_EN			(CT16_PWM13IOEN_EN<<13)
#define mskCT16_PWM13IOEN_DIS			(CT16_PWM13IOEN_DIS<<13)

																	//[14:14] CT16Bn PWM14 IO selection.
#define	CT16_PWM14IOEN_EN					1	// PWM14 pin acts as match output.
#define	CT16_PWM14IOEN_DIS				0	// PWM14 pin acts as GPIO.
#define mskCT16_PWM14IOEN_EN			(CT16_PWM14IOEN_EN<<14)
#define mskCT16_PWM14IOEN_DIS			(CT16_PWM14IOEN_DIS<<14)

																	//[15:15] CT16Bn PWM15 IO selection.
#define	CT16_PWM15IOEN_EN					1	// PWM15 pin acts as match output.
#define	CT16_PWM15IOEN_DIS				0	// PWM15 pin acts as GPIO.
#define mskCT16_PWM15IOEN_EN			(CT16_PWM15IOEN_EN<<15)
#define mskCT16_PWM15IOEN_DIS			(CT16_PWM15IOEN_DIS<<15)

																	//[16:16] CT16Bn PWM16 IO selection.
#define	CT16_PWM16IOEN_EN					1	// PWM16 pin acts as match output.
#define	CT16_PWM16IOEN_DIS				0	// PWM16 pin acts as GPIO.
#define mskCT16_PWM16IOEN_EN			(CT16_PWM16IOEN_EN<<16)
#define mskCT16_PWM16IOEN_DIS			(CT16_PWM16IOEN_DIS<<16)

																	//[17:17] CT16Bn PWM17 IO selection.
#define	CT16_PWM17IOEN_EN					1	// PWM17 pin acts as match output.
#define	CT16_PWM17IOEN_DIS				0	// PWM17 pin acts as GPIO.
#define mskCT16_PWM17IOEN_EN			(CT16_PWM17IOEN_EN<<17)
#define mskCT16_PWM17IOEN_DIS			(CT16_PWM17IOEN_DIS<<17)

																	//[18:18] CT16Bn PWM18 IO selection.
#define	CT16_PWM18IOEN_EN					1	// PWM18 pin acts as match output.
#define	CT16_PWM18IOEN_DIS				0	// PWM18 pin acts as GPIO.
#define mskCT16_PWM18IOEN_EN			(CT16_PWM18IOEN_EN<<18)
#define mskCT16_PWM18IOEN_DIS			(CT16_PWM18IOEN_DIS<<18)

																	//[19:19] CT16Bn PWM19 IO selection.
#define	CT16_PWM19IOEN_EN					1	// PWM19 pin acts as match output.
#define	CT16_PWM19IOEN_DIS				0	// PWM19 pin acts as GPIO.
#define mskCT16_PWM19IOEN_EN			(CT16_PWM19IOEN_EN<<19)
#define mskCT16_PWM19IOEN_DIS			(CT16_PWM19IOEN_DIS<<19)

																	//[20:20] CT16Bn PWM20 IO selection.
#define	CT16_PWM20IOEN_EN					1	// PWM20 pin acts as match output.
#define	CT16_PWM20IOEN_DIS				0	// PWM20 pin acts as GPIO.
#define mskCT16_PWM20IOEN_EN			(CT16_PWM20IOEN_EN<<20)
#define mskCT16_PWM20IOEN_DIS			(CT16_PWM20IOEN_DIS<<20)

																	//[21:21] CT16Bn PWM21 IO selection.
#define	CT16_PWM21IOEN_EN					1	// PWM21 pin acts as match output.
#define	CT16_PWM21IOEN_DIS				0	// PWM21 pin acts as GPIO.
#define mskCT16_PWM21IOEN_EN			(CT16_PWM21IOEN_EN<<21)
#define mskCT16_PWM21IOEN_DIS			(CT16_PWM21IOEN_DIS<<21)

																	//[22:22] CT16Bn PWM22 IO selection.
#define	CT16_PWM22IOEN_EN					1	// PWM22 pin acts as match output.
#define	CT16_PWM22IOEN_DIS				0	// PWM22 pin acts as GPIO.
#define mskCT16_PWM22IOEN_EN			(CT16_PWM22IOEN_EN<<22)
#define mskCT16_PWM22IOEN_DIS			(CT16_PWM22IOEN_DIS<<22)

																	//[23:23] CT16Bn PWM23 IO selection.
#define	CT16_PWM23IOEN_EN					1	// PWM23 pin acts as match output.
#define	CT16_PWM23IOEN_DIS				0	// PWM23 pin acts as GPIO.
#define mskCT16_PWM23IOEN_EN			(CT16_PWM23IOEN_EN<<23)
#define mskCT16_PWM23IOEN_DIS			(CT16_PWM23IOEN_DIS<<23)


/* CT16Bn Timer Raw Interrupt Status register <CT16Bn_RIS> (0xA4) */
/* CT16Bn Timer Interrupt Clear register <CT16Bn_IC> (0xA8) */
/* The bitmask usage of iwCT16Bn_IrqEvent is the same with CT16Bn_RIS*/
#define mskCT16_MR0IF						(0x1<<0) //[0:0] Interrupt flag for match channel 0
#define mskCT16_MR0IC						mskCT16_MR0IF
#define mskCT16_MR1IF						(0x1<<1) //[1:1] Interrupt flag for match channel 1
#define mskCT16_MR1IC						mskCT16_MR1IF
#define mskCT16_MR2IF						(0x1<<2) //[2:2] Interrupt flag for match channel 2
#define mskCT16_MR2IC						mskCT16_MR2IF
#define mskCT16_MR3IF						(0x1<<3) //[3:3] Interrupt flag for match channel 3
#define mskCT16_MR3IC						mskCT16_MR3IF
#define mskCT16_MR4IF						(0x1<<4) //[4:4] Interrupt flag for match channel 4
#define mskCT16_MR4IC						mskCT16_MR4IF
#define mskCT16_MR5IF						(0x1<<5) //[5:5] Interrupt flag for match channel 5
#define mskCT16_MR5IC						mskCT16_MR5IF
#define mskCT16_MR6IF						(0x1<<6) //[6:6] Interrupt flag for match channel 6
#define mskCT16_MR6IC						mskCT16_MR6IF
#define mskCT16_MR7IF						(0x1<<7) //[7:7] Interrupt flag for match channel 7
#define mskCT16_MR7IC						mskCT16_MR7IF
#define mskCT16_MR8IF						(0x1<<8) //[8:8] Interrupt flag for match channel 8
#define mskCT16_MR8IC						mskCT16_MR8IF
#define mskCT16_MR9IF						(0x1<<9) //[9:9] Interrupt flag for match channel 9
#define mskCT16_MR9IC						mskCT16_MR9IF
#define mskCT16_MR10IF					(0x1<<10) //[10:10] Interrupt flag for match channel 10
#define mskCT16_MR10IC					mskCT16_MR10IF
#define mskCT16_MR11IF					(0x1<<11) //[11:11] Interrupt flag for match channel 11
#define mskCT16_MR11IC					mskCT16_MR11IF
#define mskCT16_MR12IF					(0x1<<12) //[12:12] Interrupt flag for match channel 12
#define mskCT16_MR12IC					mskCT16_MR12IF
#define mskCT16_MR13IF					(0x1<<13) //[13:13] Interrupt flag for match channel 13
#define mskCT16_MR13IC					mskCT16_MR13IF
#define mskCT16_MR14IF					(0x1<<14) //[14:14] Interrupt flag for match channel 14
#define mskCT16_MR14IC					mskCT16_MR14IF
#define mskCT16_MR15IF					(0x1<<15) //[15:15] Interrupt flag for match channel 15
#define mskCT16_MR15IC					mskCT16_MR15IF
#define mskCT16_MR16IF					(0x1<<16) //[16:16] Interrupt flag for match channel 16
#define mskCT16_MR16IC					mskCT16_MR16IF
#define mskCT16_MR17IF					(0x1<<17) //[17:17] Interrupt flag for match channel 17
#define mskCT16_MR17IC					mskCT16_MR17IF
#define mskCT16_MR18IF					(0x1<<18) //[18:18] Interrupt flag for match channel 18
#define mskCT16_MR18IC					mskCT16_MR18IF
#define mskCT16_MR19IF					(0x1<<19) //[19:19] Interrupt flag for match channel 19
#define mskCT16_MR19IC					mskCT16_MR19IF
#define mskCT16_MR20IF					(0x1<<20) //[20:20] Interrupt flag for match channel 20
#define mskCT16_MR20IC					mskCT16_MR20IF
#define mskCT16_MR21IF					(0x1<<21) //[21:21] Interrupt flag for match channel 21
#define mskCT16_MR21IC					mskCT16_MR21IF
#define mskCT16_MR22IF					(0x1<<22) //[22:22] Interrupt flag for match channel 22
#define mskCT16_MR22IC					mskCT16_MR22IF
#define mskCT16_MR23IF					(0x1<<23) //[23:23] Interrupt flag for match channel 23
#define mskCT16_MR23IC					mskCT16_MR23IF
#define mskCT16_MR24IF					(0x1<<24) //[24:24] Interrupt flag for match channel 24
#define mskCT16_MR24IC					mskCT16_MR24IF
#define mskCT16_CAP0IF					(0x1<<25) //[25:25] Interrupt flag for capture channel 25
#define mskCT16_CAP0IC					mskCT16_CAP0IF
/*_____ M A C R O S ________________________________________________________*/

#endif //*__SN32F240B_CT16_H

