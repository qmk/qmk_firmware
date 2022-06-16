/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              https://ugfx.io/license.html
 * 
 * Author: pashamray
 * e-mail: pashamray@gmail.com
 * github: https://github.com/pashamray
 * 
 * this driver based on code: 
 *    http://caxapa.ru/thumbs/316734/rdx0154gc.zip
 *    http://leoniv.livejournal.com/124005.html
 *    Author: leoniv
 *    Web site: http://leoniv.livejournal.com
 * 
 */

#ifndef _UC1601s_H
#define _UC1601s_H

// UC1601s Address:
#define UC1601s_ADDR_C    0x70  // control address
#define UC1601s_ADDR_D    0x72  // data address

#define UC1601s_SET_COL_L 0x00  // set column address LSB, CA[3:0]
#define UC1601s_SET_COL_H 0x10  // set column address MSB, CA[7:4]
#define UC1601s_SET_TC    0x24  // set temperature compensation, TC[1:0]
#define UC1601s_SET_POWER 0x28  // set power control, PC[2:0]
#define UC1601s_SET_ADV   0x30  // set advanced program control, APC[R][7:0]
#define UC1601s_SET_SL    0x40  // set scroll line, SL[5:0]
#define UC1601s_SET_PAGE  0xB0  // set page address, PA[3:0]
#define UC1601s_SET_BIAS  0x81  // set Vbias, PM[7:0]
#define UC1601s_SET_PART  0x84  // set partial display control, LC[4]
#define UC1601s_SET_RAMA  0x88  // set RAM address control, AC[2:0]
#define UC1601s_SET_FR    0xA0  // set frame rate, LC[3]
#define UC1601s_SET_PON   0xA4  // set all pixel on, DC[1]
#define UC1601s_SET_INV   0xA6  // set inverse display, DC[0]
#define UC1601s_SET_EN 0xAE  // set display enable, DC[2]
#define UC1601s_SET_MAP   0xC0  // set LCD mapping control, LC[2:1]
#define UC1601s_RESET     0xE2  // system reset
#define UC1601s_NOP       0xE3  // NOP
#define UC1601s_SET_TEST  0xE4  // set test control
#define UC1601s_SET_BR    0xE8  // set LCD bias ratio, BR[1:0]
#define UC1601s_SET_CEN   0xF1  // set COM end, CEN[6:0]
#define UC1601s_SET_DST   0xF2  // set partial display start, DST[6:0]
#define UC1601s_SET_DEN   0xF3  // set partial display end, DEN[6:0]

// TC[1:0]:                         
#define UC1601s_TC0       0x00  // TC[1:0] = 0: temp. coeff.  -0.05%/°C (default)
#define UC1601s_TC1       0x01  // TC[1:0] = 1: temp. coeff.  -0.10%/°C
#define UC1601s_TC2       0x02  // TC[1:0] = 2: temp. coeff.  -0.15%/°C
#define UC1601s_TC3       0x03  // TC[1:0] = 3: temp. coeff.  -0.00%/°C

// PC[2:0]                          
#define UC1601s_15N       0x00  // PC[0] = 0, panel loading < 15 nF (default)
#define UC1601s_24N       0x01  // PC[0] = 1, panel loading 15 - 24 nF
#define UC1601s_EXT_VLCD  0x00  // PC[2:1] = 00, external Vlcd
#define UC1601s_INT_VLCD  0x06  // PC[2:1] = 11, internal Vlcd (x7) (default)

// LC[4:1]:                         
#define UC1601s_MX        0x02  // LC[1] = 1, X mirror
#define UC1601s_MY        0x04  // LC[2] = 1, Y mirror
#define UC1601s_80FPS     0x00  // LC[3] = 0, 80 frames per second (default)
#define UC1601s_100FPS    0x01  // LC[3] = 1, 100 frames per second
#define UC1601s_DIS_PD    0x00  // LC[4] = 0, disable partial display,
                                // mux rate = CEN + 1 (DST, DEN not used)
#define UC1601s_ENA_PD    0x01  // LC[4] = 1, enable partial display,
                                // mux rate = DEN - DST + 1

// AC[2:0]:                         
#define UC1601s_WA        0x01  // AC[0] = 1, wrap around
#define UC1601s_AINC      0x02  // AC[1] = 1, auto increment
#define UC1601s_PID       0x04  // AC[2] = 1, page auto increment direction

// DC[2:0]:                         
#define UC1601s_INVERSE   0x01  // DC[0] = 1, inverse display
#define UC1601s_ALL_ON    0x01  // DC[1] = 1, all pixels on
#define UC1601s_ENABLE    0x01  // DC[2] = 1, enable display

//BR[1:0]:                         
#define UC1601s_BR_6      0x00  // BR[1:0] = 0: bias ratio = 6
#define UC1601s_BR_7      0x01  // BR[1:0] = 1: bias ratio = 7
#define UC1601s_BR_8      0x02  // BR[1:0] = 2: bias ratio = 8
#define UC1601s_BR_9      0x03  // BR[1:0] = 3: bias ratio = 9 (default)

#endif /* _UC1601s_H */
