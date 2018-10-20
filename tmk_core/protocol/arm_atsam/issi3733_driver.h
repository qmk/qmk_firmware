/*
Copyright 2018 Massdrop Inc.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _ISSI3733_DRIVER_H_
#define _ISSI3733_DRIVER_H_

//ISII3733 Registers

#define ISSI3733_CMDR 0xFD                      //Command Register (Write Only)

#define ISSI3733_CMDRWL 0xFE                    //Command Register Write Lock (Read/Write)
#define ISSI3733_CMDRWL_WRITE_DISABLE 0x00      //Lock register
#define ISSI3733_CMDRWL_WRITE_ENABLE_ONCE 0xC5  //Enable one write to register then reset to locked

#define ISSI3733_IMR 0xF0                       //Interrupt Mask Register (Write Only)
#define ISSI3733_IMR_IAC_ON 0x08                //Auto Clear Interrupt Bit - Interrupt auto clear when INTB stay low exceeds 8ms
#define ISSI3733_IMR_IAB_ON 0x04                //Auto Breath Interrupt Bit - Enable auto breath loop finish interrupt
#define ISSI3733_IMR_IS_ON 0x02                 //Dot Short Interrupt Bit - Enable dot short interrupt
#define ISSI3733_IMR_IO_ON 0x01                 //Dot Open Interrupt Bit - Enable dot open interrupt

#define ISSI3733_ISR 0xF1                       //Interrupt Status Register (Read Only)
#define ISSI3733_ISR_ABM3_FINISH 0x10           //Auto Breath Mode 3 Finish Bit - ABM3 finished
#define ISSI3733_ISR_ABM2_FINISH 0x08           //Auto Breath Mode 2 Finish Bit - ABM2 finished
#define ISSI3733_ISR_ABM1_FINISH 0x04           //Auto Breath Mode 1 Finish Bit - ABM1 finished
#define ISSI3733_ISR_SB 0x02                    //Short Bit - Shorted
#define ISSI3733_ISR_OB 0x01                    //Open Bit - Opened

#define ISSI3733_PG0 0x00                       //LED Control Register
#define ISSI3733_PG1 0x01                       //PWM Register
#define ISSI3733_PG2 0x02                       //Auto Breath Mode Register
#define ISSI3733_PG3 0x03                       //Function Register

#define ISSI3733_PG_ONOFF ISSI3733_PG0
#define ISSI3733_PG_OR ISSI3733_PG0
#define ISSI3733_PG_SR ISSI3733_PG0
#define ISSI3733_PG_PWM ISSI3733_PG1
#define ISSI3733_PG_ABM ISSI3733_PG2
#define ISSI3733_PG_FN ISSI3733_PG3

#define ISSI3733_CR 0x00                        //Configuration Register

//PG3: Configuration Register: Synchronize Configuration
#define ISSI3733_CR_SYNC_MASTER 0x40            //Master
#define ISSI3733_CR_SYNC_SLAVE 0x80             //Slave
#define ISSI3733_CR_SYNC_HIGH_IMP 0xC0          //High Impedance

//PG3: Configuration Register: Open/Short Detection Enable Bit
//#define ISSI3733_CR_OSD_DISABLE 0x00          //Disable open/short detection
#define ISSI3733_CR_OSD_ENABLE 0x04             //Enable open/short detection

//PG3: Configuration Register: Auto Breath Enable
//#define ISSI3733_CR_B_EN_PWM 0x00             //PWM Mode Enable
#define ISSI3733_CR_B_EN_AUTO 0x02              //Auto Breath Mode Enable

//PG3: Configuration Register: Software Shutdown Control
//#define ISSI3733_CR_SSD_SHUTDOWN 0x00         //Software shutdown
#define ISSI3733_CR_SSD_NORMAL 0x01             //Normal operation

#define ISSI3733_GCCR 0x01              //Global Current Control Register

//1 Byte, Iout = (GCC / 256) * (840 / Rext)
//TODO: Give user define for Rext

//PG3: Auto Breath Control Register 1
#define ISSI3733_ABCR1_ABM1 0x02        //Auto Breath Control Register 1 of ABM-1
#define ISSI3733_ABCR1_ABM2 0x06        //Auto Breath Control Register 1 of ABM-2
#define ISSI3733_ABCR1_ABM3 0x0A        //Auto Breath Control Register 1 of ABM-3

//Rise time
#define ISSI3733_ABCR1_T1_0021 0x00     //0.21s
#define ISSI3733_ABCR1_T1_0042 0x20     //0.42s
#define ISSI3733_ABCR1_T1_0084 0x40     //0.84s
#define ISSI3733_ABCR1_T1_0168 0x60     //1.68s
#define ISSI3733_ABCR1_T1_0336 0x80     //3.36s
#define ISSI3733_ABCR1_T1_0672 0xA0     //6.72s
#define ISSI3733_ABCR1_T1_1344 0xC0     //13.44s
#define ISSI3733_ABCR1_T1_2688 0xE0     //26.88s

//Max value time
#define ISSI3733_ABCR1_T2_0000 0x00     //0s
#define ISSI3733_ABCR1_T2_0021 0x02     //0.21s
#define ISSI3733_ABCR1_T2_0042 0x04     //0.42s
#define ISSI3733_ABCR1_T2_0084 0x06     //0.84s
#define ISSI3733_ABCR1_T2_0168 0x08     //1.68s
#define ISSI3733_ABCR1_T2_0336 0x0A     //3.36s
#define ISSI3733_ABCR1_T2_0672 0x0C     //6.72s
#define ISSI3733_ABCR1_T2_1344 0x0E     //13.44s
#define ISSI3733_ABCR1_T2_2688 0x10     //26.88s

//PG3: Auto Breath Control Register 2
#define ISSI3733_ABCR2_ABM1 0x03        //Auto Breath Control Register 2 of ABM-1
#define ISSI3733_ABCR2_ABM2 0x07        //Auto Breath Control Register 2 of ABM-2
#define ISSI3733_ABCR2_ABM3 0x0B        //Auto Breath Control Register 2 of ABM-3

//Fall time
#define ISSI3733_ABCR2_T3_0021 0x00     //0.21s
#define ISSI3733_ABCR2_T3_0042 0x20     //0.42s
#define ISSI3733_ABCR2_T3_0084 0x40     //0.84s
#define ISSI3733_ABCR2_T3_0168 0x60     //1.68s
#define ISSI3733_ABCR2_T3_0336 0x80     //3.36s
#define ISSI3733_ABCR2_T3_0672 0xA0     //6.72s
#define ISSI3733_ABCR2_T3_1344 0xC0     //13.44s
#define ISSI3733_ABCR2_T3_2688 0xE0     //26.88s

//Min value time
#define ISSI3733_ABCR2_T4_0000 0x00     //0s
#define ISSI3733_ABCR2_T4_0021 0x02     //0.21s
#define ISSI3733_ABCR2_T4_0042 0x04     //0.42s
#define ISSI3733_ABCR2_T4_0084 0x06     //0.84s
#define ISSI3733_ABCR2_T4_0168 0x08     //1.68s
#define ISSI3733_ABCR2_T4_0336 0x0A     //3.36s
#define ISSI3733_ABCR2_T4_0672 0x0C     //6.72s
#define ISSI3733_ABCR2_T4_1344 0x0E     //13.44s
#define ISSI3733_ABCR2_T4_2688 0x10     //26.88s
#define ISSI3733_ABCR2_T4_5376 0x12     //53.76s
#define ISSI3733_ABCR2_T4_10752 0x14    //107.52s

//PG3: Auto Breath Control Register 3
#define ISSI3733_ABCR3_ABM1 0x04        //Auto Breath Control Register 3 of ABM-1
#define ISSI3733_ABCR3_ABM2 0x08        //Auto Breath Control Register 3 of ABM-2
#define ISSI3733_ABCR3_ABM3 0x0C        //Auto Breath Control Register 3 of ABM-3

#define ISSI3733_ABCR3_LTA_LOOP_ENDLESS 0x00
#define ISSI3733_ABCR3_LTA_LOOP_1 0x01
#define ISSI3733_ABCR3_LTA_LOOP_2 0x02
#define ISSI3733_ABCR3_LTA_LOOP_3 0x03
#define ISSI3733_ABCR3_LTA_LOOP_4 0x04
#define ISSI3733_ABCR3_LTA_LOOP_5 0x05
#define ISSI3733_ABCR3_LTA_LOOP_6 0x06
#define ISSI3733_ABCR3_LTA_LOOP_7 0x07
#define ISSI3733_ABCR3_LTA_LOOP_8 0x08
#define ISSI3733_ABCR3_LTA_LOOP_9 0x09
#define ISSI3733_ABCR3_LTA_LOOP_10 0x0A
#define ISSI3733_ABCR3_LTA_LOOP_11 0x0B
#define ISSI3733_ABCR3_LTA_LOOP_12 0x0C
#define ISSI3733_ABCR3_LTA_LOOP_13 0x0D
#define ISSI3733_ABCR3_LTA_LOOP_14 0x0E
#define ISSI3733_ABCR3_LTA_LOOP_15 0x0F

//Loop Begin
#define ISSI3733_ABCR3_LB_T1 0x00
#define ISSI3733_ABCR3_LB_T2 0x10
#define ISSI3733_ABCR3_LB_T3 0x20
#define ISSI3733_ABCR3_LB_T4 0x30

//Loop End
#define ISSI3733_ABCR3_LE_T3 0x00       //End at Off state
#define ISSI3733_ABCR3_LE_T1 0x40       //End at On State

//PG3: Auto Breath Control Register 4
#define ISSI3733_ABCR4_ABM1 0x05        //Auto Breath Control Register 4 of ABM-1
#define ISSI3733_ABCR4_ABM2 0x09        //Auto Breath Control Register 4 of ABM-2
#define ISSI3733_ABCR4_ABM3 0x0D        //Auto Breath Control Register 4 of ABM-3

#define ISSI3733_ABCR4_LTB_LOOP_ENDLESS 0x00
//Or 8bit loop times

//PG3: Time Update Register
#define ISSI3733_TUR 0x0E
#define ISSI3733_TUR_UPDATE 0x00        //Write to update 02h~0Dh time registers after configuring

//PG3: SWy Pull-Up Resistor Selection Register
#define ISSI3733_SWYR_PUR 0x0F
#define ISSI3733_SWYR_PUR_NONE 0x00     //No pull-up resistor
#define ISSI3733_SWYR_PUR_500 0x01      //0.5k Ohm
#define ISSI3733_SWYR_PUR_1000 0x02     //1.0k Ohm
#define ISSI3733_SWYR_PUR_2000 0x03     //2.0k Ohm
#define ISSI3733_SWYR_PUR_4000 0x04     //4.0k Ohm
#define ISSI3733_SWYR_PUR_8000 0x05     //8.0k Ohm
#define ISSI3733_SWYR_PUR_16000 0x06    //16k Ohm
#define ISSI3733_SWYR_PUR_32000 0x07    //32k Ohm

//PG3: CSx Pull-Down Resistor Selection Register
#define ISSI3733_CSXR_PDR 0x10
#define ISSI3733_CSXR_PDR_NONE 0x00     //No pull-down resistor
#define ISSI3733_CSXR_PDR_500 0x01      //0.5k Ohm
#define ISSI3733_CSXR_PDR_1000 0x02     //1.0k Ohm
#define ISSI3733_CSXR_PDR_2000 0x03     //2.0k Ohm
#define ISSI3733_CSXR_PDR_4000 0x04     //4.0k Ohm
#define ISSI3733_CSXR_PDR_8000 0x05     //8.0k Ohm
#define ISSI3733_CSXR_PDR_16000 0x06    //16k Ohm
#define ISSI3733_CSXR_PDR_32000 0x07    //32k Ohm

//PG3: Reset Register
#define ISSI3733_RR 0x11                //Read to reset all registers to default values

#endif //_ISSI3733_DRIVER_H_
