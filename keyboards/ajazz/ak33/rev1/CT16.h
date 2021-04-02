#ifndef __SN32F240_CT16_H
#define __SN32F240_CT16_H


/*_____ I N C L U D E S ____________________________________________________*/

/*_____ D E F I N I T I O N S ______________________________________________*/
/*
Base Address: 0x4000 0000 (CT16B0)
							0x4000 2000 (CT16B1)
							0x4000 4000 (CT16B2)
*/

/* CT16Bn Timer Control register <CT16Bn_TMRCTRL> (0x00) */
#define	CT16_CEN_DIS 						0			//[0:0] CT16Bn enable bit
#define	CT16_CEN_EN  						1
#define mskCT16_CEN_DIS					(CT16_CEN_DIS<<0)
#define	mskCT16_CEN_EN  				(CT16_CEN_EN<<0)

#define	CT16_CRST 							1			//[1:1] CT16Bn counter reset bit
#define mskCT16_CRST						(CT16_CRST<<1)

																			//[6:4] CT16Bn counting mode selection
#define CT16_CM_EDGE_UP					0			//Edge-aligned Up-counting mode
#define CT16_CM_EDGE_DOWN				1			//Edge-aligned Down-counting mode
#define CT16_CM_CENTER_UP				2			//Center-aligned mode 1. Match interrupt is set during up-counting period
#define CT16_CM_CENTER_DOWN			4			//Center-aligned mode 2. Match interrupt is set during down-counting period
#define CT16_CM_CENTER_BOTH			6			//Center-aligned mode 3. Match interrupt is set during both up and down period.
#define mskCT16_CM_EDGE_UP			(CT16_CM_EDGE_UP<<4)
#define mskCT16_CM_EDGE_DOWN		(CT16_CM_EDGE_DOWN<<4)
#define mskCT16_CM_CENTER_UP		(CT16_CM_CENTER_UP<<4)
#define mskCT16_CM_CENTER_DOWN	(CT16_CM_CENTER_DOWN<<4)
#define mskCT16_CM_CENTER_BOTH	(CT16_CM_CENTER_BOTH<<4)

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
#define	CT16_MR0IE_EN						1		//[0:0] Enable MR0 match interrupt
#define	CT16_MR0IE_DIS					0
#define mskCT16_MR0IE_EN				(CT16_MR0IE_EN<<0)
#define mskCT16_MR0IE_DIS				(CT16_MR0IE_DIS<<0)

#define	CT16_MR0RST_EN					1		//[1:1] Enable reset TC when MR0 matches TC.
#define	CT16_MR0RST_DIS					0
#define mskCT16_MR0RST_EN				(CT16_MR0RST_EN<<1)
#define mskCT16_MR0RST_DIS			(CT16_MR0RST_DIS<<1)

#define	CT16_MR0STOP_EN					1		//[2:2] Enable stop TC and clear CEN when MR0 matches TC.
#define	CT16_MR0STOP_DIS				0
#define mskCT16_MR0STOP_EN			(CT16_MR0STOP_EN<<2)
#define mskCT16_MR0STOP_DIS			(CT16_MR0STOP_DIS<<2)

#define	CT16_MR1IE_EN						1		//[3:3] Enable MR1 match interrupt
#define	CT16_MR1IE_DIS					0
#define mskCT16_MR1IE_EN				(CT16_MR1IE_EN<<3)
#define mskCT16_MR1IE_DIS				(CT16_MR1IE_DIS<<3)

#define	CT16_MR1RST_EN					1		//[4:4] Enable reset TC when MR1 matches TC.
#define	CT16_MR1RST_DIS					0
#define mskCT16_MR1RST_EN				(CT16_MR1RST_EN<<4)
#define mskCT16_MR1RST_DIS			(CT16_MR1RST_DIS<<4)

#define	CT16_MR1STOP_EN					1		//[5:5] Enable stop TC and clear CEN when MR1 matches TC.
#define	CT16_MR1STOP_DIS				0
#define mskCT16_MR1STOP_EN			(CT16_MR1STOP_EN<<5)
#define mskCT16_MR1STOP_DIS			(CT16_MR1STOP_DIS<<5)

#define	CT16_MR2IE_EN						1		//[6:6] Enable MR2 match interrupt
#define	CT16_MR2IE_DIS					0
#define mskCT16_MR2IE_EN				(CT16_MR2IE_EN<<6)
#define mskCT16_MR2IE_DIS				(CT16_MR2IE_DIS<<6)

#define	CT16_MR2RST_EN					1		//[7:7] Enable reset TC when MR2 matches TC.
#define	CT16_MR2RST_DIS					0
#define mskCT16_MR2RST_EN				(CT16_MR2RST_EN<<7)
#define mskCT16_MR2RST_DIS			(CT16_MR2RST_DIS<<7)

#define	CT16_MR2STOP_EN					1		//[8:8] Enable stop TC and clear CEN when MR2 matches TC.
#define	CT16_MR2STOP_DIS				0
#define mskCT16_MR2STOP_EN			(CT16_MR2STOP_EN<<8)
#define mskCT16_MR2STOP_DIS			(CT16_MR2STOP_DIS<<8)

#define	CT16_MR3IE_EN						1		//[9:9] Enable MR3 match interrupt
#define	CT16_MR3IE_DIS					0
#define mskCT16_MR3IE_EN				(CT16_MR3IE_EN<<9)
#define mskCT16_MR3IE_DIS				(CT16_MR3IE_DIS<<9)

#define	CT16_MR3RST_EN					1		//[10:10] Enable reset TC when MR3 matches TC.
#define	CT16_MR3RST_DIS					0
#define mskCT16_MR3RST_EN				(CT16_MR3RST_EN<<10)
#define mskCT16_MR3RST_DIS			(CT16_MR3RST_DIS<<10)

#define	CT16_MR3STOP_EN					1		//[11:11] Enable stop TC and clear CEN when MR3 matches TC.
#define	CT16_MR3STOP_DIS				0
#define mskCT16_MR3STOP_EN			(CT16_MR3STOP_EN<<11)
#define mskCT16_MR3STOP_DIS			(CT16_MR3STOP_DIS<<11)

/* CT16Bn Capture Control register <CT16Bn_CAPCTRL> (0x28) */
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

/* CT16Bn External Match register <CT16Bn_EM> (0x30) */
#define	CT16_EM0								1		//[0:0] CT16Bn PWM0 drive state
#define mskCT16_EM0							(CT16_EM0<<0)
#define	CT16_EM1								1		//[1:1] CT16Bn PWM1 drive state
#define mskCT16_EM1							(CT16_EM1<<1)
#define	CT16_EM2								1		//[2:2] CT16Bn PWM2 drive state
#define mskCT16_EM2							(CT16_EM2<<2)


																	//[5:4] CT16Bn PWM0 functionality
#define	CT16_EMC0_DO_NOTHING		0	//Do nothing.
#define	CT16_EMC0_LOW						1	//CT16Bn PWM0 pin is low.
#define	CT16_EMC0_HIGH					2	//CT16Bn PWM0 pin is high.
#define	CT16_EMC0_TOGGLE				3	//Toggle CT16Bn PWM0 pin.
#define mskCT16_EMC0_DO_NOTHING	(CT16_EMC0_LOW<<4)
#define mskCT16_EMC0_LOW				(CT16_EMC0_LOW<<4)
#define mskCT16_EMC0_HIGH				(CT16_EMC0_HIGH<<4)
#define mskCT16_EMC0_TOGGLE			(CT16_EMC0_TOGGLE<<4)

																	//[7:6] CT16Bn PWM1 functionality
#define	CT16_EMC1_DO_NOTHING		0	//Do nothing.
#define	CT16_EMC1_LOW						1	//CT16Bn PWM1 pin is low.
#define	CT16_EMC1_HIGH					2	//CT16Bn PWM1 pin is high.
#define	CT16_EMC1_TOGGLE				3	//Toggle CT16Bn PWM1 pin.
#define mskCT16_EMC1_DO_NOTHING	(CT16_EMC1_LOW<<6)
#define mskCT16_EMC1_LOW				(CT16_EMC1_LOW<<6)
#define mskCT16_EMC1_HIGH				(CT16_EMC1_HIGH<<6)
#define mskCT16_EMC1_TOGGLE			(CT16_EMC1_TOGGLE<<6)

																	//[9:8] CT16Bn PWM2 functionality
#define	CT16_EMC2_DO_NOTHING		0	//Do nothing.
#define	CT16_EMC2_LOW						1	//CT16Bn PWM2 pin is low.
#define	CT16_EMC2_HIGH					2	//CT16Bn PWM2 pin is high.
#define	CT16_EMC2_TOGGLE				3	//Toggle CT16Bn PWM2 pin.
#define mskCT16_EMC2_DO_NOTHING	(CT16_EMC2_LOW<<8)
#define mskCT16_EMC2_LOW				(CT16_EMC2_LOW<<8)
#define mskCT16_EMC2_HIGH				(CT16_EMC2_HIGH<<8)
#define mskCT16_EMC2_TOGGLE			(CT16_EMC2_TOGGLE<<8)


/* CT16Bn PWM Control register <CT16Bn_PWMCTRL> (0x34) */
																//[0:0] CT16Bn PWM0 enable.
#define	CT16_PWM0EN_EN					1	// CT16Bn PWM0 is enabled for PWM mode.
#define	CT16_PWM0EN_EM0					0 // CT16Bn PWM0 is controlled by EM0.
#define mskCT16_PWM0EN_EN				(CT16_PWM0EN_EN<<0)
#define mskCT16_PWM0EN_EM0			(CT16_PWM0EN_EM0<<0)

																//[1:1] CT16Bn PWM1 enable.
#define	CT16_PWM1EN_EN					1	// CT16Bn PWM1 is enabled for PWM mode.
#define	CT16_PWM1EN_EM1					0 // CT16Bn PWM1 is controlled by EM1.
#define mskCT16_PWM1EN_EN				(CT16_PWM1EN_EN<<1)
#define mskCT16_PWM1EN_EM1			(CT16_PWM1EN_EM1<<1)

																//[2:2] CT16Bn PWM2 enable.
#define	CT16_PWM2EN_EN					1	// CT16Bn PWM2 is enabled for PWM mode.
#define	CT16_PWM2EN_EM2					0 // CT16Bn PWM2 is controlled by EM2.
#define mskCT16_PWM2EN_EN				(CT16_PWM2EN_EN<<2)
#define mskCT16_PWM2EN_EM2			(CT16_PWM2EN_EM2<<2)

																	//[5:4] CT16Bn PWM0 output mode.
#define	CT16_PWM0MODE_1					0	// PWM mode 1.
#define	CT16_PWM0MODE_2					1 // PWM mode 2.
#define	CT16_PWM0MODE_FORCE_0		2 // Force 0.
#define	CT16_PWM0MODE_FORCE_1		3 // Force 1.
#define mskCT16_PWM0MODE_1			(CT16_PWM0MODE_1<<4)
#define mskCT16_PWM0MODE_2			(CT16_PWM0MODE_2<<4)
#define mskCT16_PWM0MODE_FORCE_0	(CT16_PWM0MODE_FORCE_0<<4)
#define mskCT16_PWM0MODE_FORCE_1	(CT16_PWM0MODE_FORCE_1<<4)

																	//[7:6] CT16Bn PWM1 output mode.
#define	CT16_PWM1MODE_1					0	// PWM mode 1.
#define	CT16_PWM1MODE_2					1 // PWM mode 2.
#define	CT16_PWM1MODE_FORCE_0		2 // Force 0.
#define	CT16_PWM1MODE_FORCE_1		3 // Force 1.
#define mskCT16_PWM1MODE_1			(CT16_PWM1MODE_1<<6)
#define mskCT16_PWM1MODE_2			(CT16_PWM1MODE_2<<6)
#define mskCT16_PWM1MODE_FORCE_0	(CT16_PWM1MODE_FORCE_0<<6)
#define mskCT16_PWM1MODE_FORCE_1	(CT16_PWM1MODE_FORCE_1<<6)

																	//[9:8] CT16Bn PWM2 output mode.
#define	CT16_PWM2MODE_1					0	// PWM mode 1.
#define	CT16_PWM2MODE_2					1 // PWM mode 2.
#define	CT16_PWM2MODE_FORCE_0		2 // Force 0.
#define	CT16_PWM2MODE_FORCE_1		3 // Force 1.
#define mskCT16_PWM2MODE_1			(CT16_PWM2MODE_1<<8)
#define mskCT16_PWM2MODE_2			(CT16_PWM2MODE_2<<8)
#define mskCT16_PWM2MODE_FORCE_0	(CT16_PWM2MODE_FORCE_0<<8)
#define mskCT16_PWM2MODE_FORCE_1	(CT16_PWM2MODE_FORCE_1<<8)

																	//[20:20] CT16Bn PWM0 IO selection.
#define	CT16_PWM0IOEN_EN				1	// PWM 0 pin acts as match output.
#define	CT16_PWM0IOEN_DIS				0	// PWM 0 pin acts as GPIO.
#define mskCT16_PWM0IOEN_EN			(CT16_PWM0IOEN_EN<<20)
#define mskCT16_PWM0IOEN_DIS		(CT16_PWM0IOEN_DIS<<20)

																	//[21:21] CT16Bn PWM1 IO selection.
#define	CT16_PWM1IOEN_EN				1	// PWM 1 pin acts as match output.
#define	CT16_PWM1IOEN_DIS				0	// PWM 1 pin acts as GPIO.
#define mskCT16_PWM1IOEN_EN			(CT16_PWM1IOEN_EN<<21)
#define mskCT16_PWM1IOEN_DIS		(CT16_PWM1IOEN_DIS<<21)

																	//[22:22] CT16Bn PWM2 IO selection.
#define	CT16_PWM2IOEN_EN				1	// PWM 2 pin acts as match output.
#define	CT16_PWM2IOEN_DIS				0	// PWM 2 pin acts as GPIO.
#define mskCT16_PWM2IOEN_EN			(CT16_PWM2IOEN_EN<<22)
#define mskCT16_PWM2IOEN_DIS		(CT16_PWM2IOEN_DIS<<22)


/* CT16Bn Timer Raw Interrupt Status register <CT16Bn_RIS> (0x38) */
/* CT16Bn Timer Interrupt Clear register <CT16Bn_IC> (0x3C) */
/* The bitmask usage of iwCT16Bn_IrqEvent is the same with CT16Bn_RIS*/
#define mskCT16_MR0IF						(0x1<<0) //[0:0] Interrupt flag for match channel 0
#define mskCT16_MR0IC						mskCT16_MR0IF
#define mskCT16_MR1IF						(0x1<<1) //[1:1] Interrupt flag for match channel 1
#define mskCT16_MR1IC						mskCT16_MR1IF
#define mskCT16_MR2IF						(0x1<<2) //[2:2] Interrupt flag for match channel 2
#define mskCT16_MR2IC						mskCT16_MR2IF
#define mskCT16_MR3IF						(0x1<<3) //[3:3] Interrupt flag for match channel 3
#define mskCT16_MR3IC						mskCT16_MR3IF
#define mskCT16_CAP0IF					(0x1<<4) //[4:4] Interrupt flag for capture channel 0
#define mskCT16_CAP0IC					mskCT16_CAP0IF

/*_____ M A C R O S ________________________________________________________*/


/*_____ D E C L A R A T I O N S ____________________________________________*/

#endif	/*__SN32F240_CT16_H*/

