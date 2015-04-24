/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef MBED_PINNAMES_H
#define MBED_PINNAMES_H

#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    PIN_INPUT,
    PIN_OUTPUT
} PinDirection;

#define PORT_SHIFT  5
#define NO_GPIO     15

// On the LPC43xx the MCU pin name and the GPIO pin name are not the same.
// Encode SCU and GPIO offsets as a pin identifier
#define MBED_PIN(group, num, port, pin)  ((SCU_OFF(group,num) << 16) + GPIO_OFF(port,pin))

// Decode pin identifier into register, port and pin values
#define MBED_SCU_REG(MBED_PIN)   (LPC_SCU_BASE + (MBED_PIN >> 16))
#define MBED_GPIO_REG(MBED_PIN)  (LPC_GPIO_PORT_BASE + 0x2000 + ((MBED_PIN >> (PORT_SHIFT - 2)) & 0x0000003C))
#define MBED_GPIO_PORT(MBED_PIN) ((MBED_PIN >> PORT_SHIFT) & 0x0000000F)
#define MBED_GPIO_PIN(MBED_PIN)  (MBED_PIN & 0x0000001F)

typedef enum {
    // LPC43xx Pin Names
    // All pins defined. Package determines which are available.
    //          LBGA256  TFBGA180 TFBGA100 LQFP208  LQFP144
    // GPIO0    [15:0]   [15:0]   [15:6]   [15:0]   [15:0]
    //                            [4:0]
    // GPIO1    [15:0]   [15:0]   [15:0]   [15:0]   [15:0]
    // GPIO2    [15:0]   [15:0]            [15:0]   [15:0]
    // GPIO3    [15:0]   [15:0]   [7]      [15:0]   [15:0]
    //                            [5:3]
    //                            [1:0]
    // GPIO4    [15:0]   [15:0]            [15:0]   [11]
    // GPIO5    [26:0]   [26:0]   [11:0]   [25:0]   [18]
    //                                              [16:0]
    // GPIO6    [30:0]   [30:28]           [30:20]
    //                   [26:25]           [5:0]
    // GPIO7    [25:0]   [4:0]             [25:23]
    //                                     [21:17]
    //          ---      ---      ---      ---      ---
    // Total    164      117      49       131      83

    // Groups 0x00 - 0x0F : Digital pins
    // * Digital pins support up to 8 functions
    //   Use func=0 for GPIO0-GPIO4, func=4 for GPIO5-GPIO7
    // * High-drive pins default to 4 mA but can support 8, 14, 20 mA
    P0_0  = MBED_PIN(0x00, 0, 0, 0),    // GPIO0[0]
    P0_1  = MBED_PIN(0x00, 1, 0, 1),    // GPIO0[1]

    P1_0  = MBED_PIN(0x01, 0, 0, 4),    // GPIO0[4]
    P1_1  = MBED_PIN(0x01, 1, 0, 8),    // GPIO0[8]
    P1_2  = MBED_PIN(0x01, 2, 0, 9),    // GPIO0[9]
    P1_3  = MBED_PIN(0x01, 3, 0, 10),   // GPIO0[10]
    P1_4  = MBED_PIN(0x01, 4, 0, 11),   // GPIO0[11]
    P1_5  = MBED_PIN(0x01, 5, 1, 8),    // GPIO1[8]
    P1_6  = MBED_PIN(0x01, 6, 1, 9),    // GPIO1[9]
    P1_7  = MBED_PIN(0x01, 7, 1, 0),    // GPIO1[0]
    P1_8  = MBED_PIN(0x01, 8, 1, 1),    // GPIO1[1]
    P1_9  = MBED_PIN(0x01, 9, 1, 2),    // GPIO1[2]
    P1_10 = MBED_PIN(0x01, 10, 1, 3),   // GPIO1[3]
    P1_11 = MBED_PIN(0x01, 11, 1, 4),   // GPIO1[4]
    P1_12 = MBED_PIN(0x01, 12, 1, 5),   // GPIO1[5]
    P1_13 = MBED_PIN(0x01, 13, 1, 6),   // GPIO1[6]
    P1_14 = MBED_PIN(0x01, 14, 1, 7),   // GPIO1[7]
    P1_15 = MBED_PIN(0x01, 15, 0, 2),   // GPIO0[2]
    P1_16 = MBED_PIN(0x01, 16, 0, 3),   // GPIO0[3]
    P1_17 = MBED_PIN(0x01, 17, 0, 12),  // GPIO0[12] high-drive
    P1_18 = MBED_PIN(0x01, 18, 0, 13),  // GPIO0[13]
    P1_19 = MBED_PIN(0x01, 19, NO_GPIO, 0),
    P1_20 = MBED_PIN(0x01, 20, 0, 15),  // GPIO0[15]

    P2_0  = MBED_PIN(0x02, 0, 5, 0),    // GPIO5[0]
    P2_1  = MBED_PIN(0x02, 1, 5, 1),    // GPIO5[1]
    P2_2  = MBED_PIN(0x02, 2, 5, 2),    // GPIO5[2]
    P2_3  = MBED_PIN(0x02, 3, 5, 3),    // GPIO5[3]  high-drive
    P2_4  = MBED_PIN(0x02, 4, 5, 4),    // GPIO5[4]  high-drive
    P2_5  = MBED_PIN(0x02, 5, 5, 5),    // GPIO5[5]  high-drive
    P2_6  = MBED_PIN(0x02, 6, 5, 6),    // GPIO5[6]
    P2_7  = MBED_PIN(0x02, 7, 0, 7),    // GPIO0[7]
    P2_8  = MBED_PIN(0x02, 8, 5, 7),    // GPIO5[7]
    P2_9  = MBED_PIN(0x02, 9, 1, 10),   // GPIO1[10]
    P2_10 = MBED_PIN(0x02, 10, 0, 14),  // GPIO0[14]
    P2_11 = MBED_PIN(0x02, 11, 1, 11),  // GPIO1[11]
    P2_12 = MBED_PIN(0x02, 12, 1, 12),  // GPIO1[12]
    P2_13 = MBED_PIN(0x02, 13, 1, 13),  // GPIO1[13]

    P3_0  = MBED_PIN(0x03, 0, NO_GPIO, 0),
    P3_1  = MBED_PIN(0x03, 1, 5, 8),    // GPIO5[8]
    P3_2  = MBED_PIN(0x03, 2, 5, 9),    // GPIO5[9]
    P3_3  = MBED_PIN(0x03, 3, NO_GPIO, 0),
    P3_4  = MBED_PIN(0x03, 4, 1, 14),   // GPIO1[14]
    P3_5  = MBED_PIN(0x03, 5, 1, 15),   // GPIO1[15]
    P3_6  = MBED_PIN(0x03, 6, 0, 6),    // GPIO0[6]
    P3_7  = MBED_PIN(0x03, 7, 5, 10),   // GPIO5[10]
    P3_8  = MBED_PIN(0x03, 8, 5, 11),   // GPIO5[11]

    P4_0  = MBED_PIN(0x04, 0, 2, 0),    // GPIO2[0]
    P4_1  = MBED_PIN(0x04, 1, 2, 1),    // GPIO2[1]
    P4_2  = MBED_PIN(0x04, 2, 2, 2),    // GPIO2[2]
    P4_3  = MBED_PIN(0x04, 3, 2, 3),    // GPIO2[3]
    P4_4  = MBED_PIN(0x04, 4, 2, 4),    // GPIO2[4]
    P4_5  = MBED_PIN(0x04, 5, 2, 5),    // GPIO2[5]
    P4_6  = MBED_PIN(0x04, 6, 2, 6),    // GPIO2[6]
    P4_7  = MBED_PIN(0x04, 7, NO_GPIO, 0),
    P4_8  = MBED_PIN(0x04, 8, 5, 12),   // GPIO5[12]
    P4_9  = MBED_PIN(0x04, 9, 5, 13),   // GPIO5[13]
    P4_10 = MBED_PIN(0x04, 10, 5, 14),  // GPIO5[14]

    P5_0  = MBED_PIN(0x05, 0, 2, 9),    // GPIO2[9]
    P5_1  = MBED_PIN(0x05, 1, 2, 10),   // GPIO2[10]
    P5_2  = MBED_PIN(0x05, 2, 2, 11),   // GPIO2[11]
    P5_3  = MBED_PIN(0x05, 3, 2, 12),   // GPIO2[12]
    P5_4  = MBED_PIN(0x05, 4, 2, 13),   // GPIO2[13]
    P5_5  = MBED_PIN(0x05, 5, 2, 14),   // GPIO2[14]
    P5_6  = MBED_PIN(0x05, 6, 2, 15),   // GPIO2[15]
    P5_7  = MBED_PIN(0x05, 7, 2, 7),    // GPIO2[7]

    P6_0  = MBED_PIN(0x06, 0, NO_GPIO, 0),
    P6_1  = MBED_PIN(0x06, 1, 3, 0),    // GPIO3[0]
    P6_2  = MBED_PIN(0x06, 2, 3, 1),    // GPIO3[1]
    P6_3  = MBED_PIN(0x06, 3, 3, 2),    // GPIO3[2]
    P6_4  = MBED_PIN(0x06, 4, 3, 3),    // GPIO3[3]
    P6_5  = MBED_PIN(0x06, 5, 3, 4),    // GPIO3[4]
    P6_6  = MBED_PIN(0x06, 6, 0, 5),    // GPIO0[5]
    P6_7  = MBED_PIN(0x06, 7, 5, 15),   // GPIO5[15]
    P6_8  = MBED_PIN(0x06, 8, 5, 16),   // GPIO5[16]
    P6_9  = MBED_PIN(0x06, 9, 3, 5),    // GPIO3[5]
    P6_10 = MBED_PIN(0x06, 10, 3, 6),   // GPIO3[6]
    P6_11 = MBED_PIN(0x06, 11, 3, 7),   // GPIO3[7]
    P6_12 = MBED_PIN(0x06, 12, 2, 8),   // GPIO2[8]

    P7_0  = MBED_PIN(0x07, 0, 3, 8),    // GPIO3[8]
    P7_1  = MBED_PIN(0x07, 1, 3, 9),    // GPIO3[9]
    P7_2  = MBED_PIN(0x07, 2, 3, 10),   // GPIO3[10]
    P7_3  = MBED_PIN(0x07, 3, 3, 11),   // GPIO3[11]
    P7_4  = MBED_PIN(0x07, 4, 3, 12),   // GPIO3[12]
    P7_5  = MBED_PIN(0x07, 5, 3, 13),   // GPIO3[13]
    P7_6  = MBED_PIN(0x07, 6, 3, 14),   // GPIO3[14]
    P7_7  = MBED_PIN(0x07, 7, 3, 15),   // GPIO3[15]

    P8_0  = MBED_PIN(0x08, 8, 4, 0),    // GPIO4[0]  high-drive
    P8_1  = MBED_PIN(0x09, 0, 4, 1),    // GPIO4[1]  high-drive
    P8_2  = MBED_PIN(0x09, 1, 4, 2),    // GPIO4[2]  high-drive
    P8_3  = MBED_PIN(0x09, 2, 4, 3),    // GPIO4[3]
    P8_4  = MBED_PIN(0x08, 4, 4, 4),    // GPIO4[4]
    P8_5  = MBED_PIN(0x08, 5, 4, 5),    // GPIO4[5]
    P8_6  = MBED_PIN(0x08, 6, 4, 6),    // GPIO4[6]
    P8_7  = MBED_PIN(0x08, 7, 4, 7),    // GPIO4[7]
    P8_8  = MBED_PIN(0x08, 8, NO_GPIO, 0),

    P9_0  = MBED_PIN(0x09, 0, 4, 12),   // GPIO4[12]
    P9_1  = MBED_PIN(0x09, 1, 4, 13),   // GPIO4[13]
    P9_2  = MBED_PIN(0x09, 2, 4, 14),   // GPIO4[14]
    P9_3  = MBED_PIN(0x09, 3, 4, 15),   // GPIO4[15]
    P9_4  = MBED_PIN(0x09, 4, 5, 17),   // GPIO5[17]
    P9_5  = MBED_PIN(0x09, 5, 5, 18),   // GPIO5[18]
    P9_6  = MBED_PIN(0x09, 6, 4, 11),   // GPIO4[11]

    PA_0  = MBED_PIN(0x0A, 0, NO_GPIO, 0),
    PA_1  = MBED_PIN(0x0A, 1, 4, 8),    // GPIO4[8]  high-drive
    PA_2  = MBED_PIN(0x0A, 2, 4, 9),    // GPIO4[9]  high-drive
    PA_3  = MBED_PIN(0x0A, 3, 4, 10),   // GPIO4[10] high-drive
    PA_4  = MBED_PIN(0x0A, 4, 5, 19),   // GPIO5[19]

    PB_0   = MBED_PIN(0x0B, 0, 5, 20),  // GPIO5[20]
    PB_1   = MBED_PIN(0x0B, 1, 5, 21),  // GPIO5[21]
    PB_2   = MBED_PIN(0x0B, 2, 5, 22),  // GPIO5[22]
    PB_3   = MBED_PIN(0x0B, 3, 5, 23),  // GPIO5[23]
    PB_4   = MBED_PIN(0x0B, 4, 5, 24),  // GPIO5[24]
    PB_5   = MBED_PIN(0x0B, 5, 5, 25),  // GPIO5[25]
    PB_6   = MBED_PIN(0x0B, 6, 5, 26),  // GPIO5[26]

    PC_0   = MBED_PIN(0x0C, 0, NO_GPIO, 0),
    PC_1   = MBED_PIN(0x0C, 1, 6, 0),   // GPIO6[0]
    PC_2   = MBED_PIN(0x0C, 2, 6, 1),   // GPIO6[1]
    PC_3   = MBED_PIN(0x0C, 3, 6, 2),   // GPIO6[2]
    PC_4   = MBED_PIN(0x0C, 4, 6, 3),   // GPIO6[3]
    PC_5   = MBED_PIN(0x0C, 5, 6, 4),   // GPIO6[4]
    PC_6   = MBED_PIN(0x0C, 6, 6, 5),   // GPIO6[5]
    PC_7   = MBED_PIN(0x0C, 7, 6, 6),   // GPIO6[6]
    PC_8   = MBED_PIN(0x0C, 8, 6, 7),   // GPIO6[7]
    PC_9   = MBED_PIN(0x0C, 9, 6, 8),   // GPIO6[8]
    PC_10  = MBED_PIN(0x0C, 10, 6, 9),  // GPIO6[9]
    PC_11  = MBED_PIN(0x0C, 11, 6, 10), // GPIO6[10]
    PC_12  = MBED_PIN(0x0C, 12, 6, 11), // GPIO6[11]
    PC_13  = MBED_PIN(0x0C, 13, 6, 12), // GPIO6[12]
    PC_14  = MBED_PIN(0x0C, 14, 6, 13), // GPIO6[13]

    PD_0   = MBED_PIN(0x0D, 0, 6, 14),  // GPIO6[14]
    PD_1   = MBED_PIN(0x0D, 1, 6, 15),  // GPIO6[15]
    PD_2   = MBED_PIN(0x0D, 2, 6, 16),  // GPIO6[16]
    PD_3   = MBED_PIN(0x0D, 3, 6, 17),  // GPIO6[17]
    PD_4   = MBED_PIN(0x0D, 4, 6, 18),  // GPIO6[18]
    PD_5   = MBED_PIN(0x0D, 5, 6, 19),  // GPIO6[19]
    PD_6   = MBED_PIN(0x0D, 6, 6, 20),  // GPIO6[20]
    PD_7   = MBED_PIN(0x0D, 7, 6, 21),  // GPIO6[21]
    PD_8   = MBED_PIN(0x0D, 8, 6, 22),  // GPIO6[22]
    PD_9   = MBED_PIN(0x0D, 9, 6, 23),  // GPIO6[23]
    PD_10  = MBED_PIN(0x0D, 10, 6, 24), // GPIO6[24]
    PD_11  = MBED_PIN(0x0D, 11, 6, 25), // GPIO6[25]
    PD_12  = MBED_PIN(0x0D, 12, 6, 26), // GPIO6[26]
    PD_13  = MBED_PIN(0x0D, 13, 6, 27), // GPIO6[27]
    PD_14  = MBED_PIN(0x0D, 14, 6, 28), // GPIO6[28]
    PD_15  = MBED_PIN(0x0D, 15, 6, 29), // GPIO6[29]
    PD_16  = MBED_PIN(0x0D, 16, 6, 30), // GPIO6[30]

    PE_0   = MBED_PIN(0x0E, 0, 7, 0),   // GPIO7[0]
    PE_1   = MBED_PIN(0x0E, 1, 7, 1),   // GPIO7[1]
    PE_2   = MBED_PIN(0x0E, 2, 7, 2),   // GPIO7[2]
    PE_3   = MBED_PIN(0x0E, 3, 7, 3),   // GPIO7[3]
    PE_4   = MBED_PIN(0x0E, 4, 7, 4),   // GPIO7[4]
    PE_5   = MBED_PIN(0x0E, 5, 7, 5),   // GPIO7[5]
    PE_6   = MBED_PIN(0x0E, 6, 7, 6),   // GPIO7[6]
    PE_7   = MBED_PIN(0x0E, 7, 7, 7),   // GPIO7[7]
    PE_8   = MBED_PIN(0x0E, 8, 7, 8),   // GPIO7[8]
    PE_9   = MBED_PIN(0x0E, 9, 7, 9),   // GPIO7[9]
    PE_10  = MBED_PIN(0x0E, 10, 7, 10), // GPIO7[10]
    PE_11  = MBED_PIN(0x0E, 11, 7, 11), // GPIO7[11]
    PE_12  = MBED_PIN(0x0E, 12, 7, 12), // GPIO7[12]
    PE_13  = MBED_PIN(0x0E, 13, 7, 13), // GPIO7[13]
    PE_14  = MBED_PIN(0x0E, 14, 7, 14), // GPIO7[14]
    PE_15  = MBED_PIN(0x0E, 15, 7, 15), // GPIO7[15]

    PF_0   = MBED_PIN(0x0F, 0, NO_GPIO, 0),
    PF_1   = MBED_PIN(0x0F, 1, 7, 16),  // GPIO7[16]
    PF_2   = MBED_PIN(0x0F, 2, 7, 17),  // GPIO7[17]
    PF_3   = MBED_PIN(0x0F, 3, 7, 18),  // GPIO7[18]
    PF_4   = MBED_PIN(0x0F, 4, NO_GPIO, 0),
    PF_5   = MBED_PIN(0x0F, 5, 7, 19),  // GPIO7[19]
    PF_6   = MBED_PIN(0x0F, 6, 7, 20),  // GPIO7[20]
    PF_7   = MBED_PIN(0x0F, 7, 7, 21),  // GPIO7[21]
    PF_8   = MBED_PIN(0x0F, 8, 7, 22),  // GPIO7[22]
    PF_9   = MBED_PIN(0x0F, 9, 7, 23),  // GPIO7[23]
    PF_10  = MBED_PIN(0x0F, 10, 7, 24), // GPIO7[24]
    PF_11  = MBED_PIN(0x0F, 11, 7, 25), // GPIO7[25]

    // GPIO pins from MCU pins
    GPIO0_0 = P0_0,
    GPIO0_1 = P0_1 ,
    GPIO0_2 = P1_15,
    GPIO0_3 = P1_16,
    GPIO0_4 = P1_0,
    GPIO0_5 = P6_6,
    GPIO0_6 = P3_6,
    GPIO0_7 = P2_7,
    GPIO0_8 = P1_1,
    GPIO0_9 = P1_2,
    GPIO0_10 = P1_3,
    GPIO0_11 = P1_4,
    GPIO0_12 = P1_17,
    GPIO0_13 = P1_18,
    GPIO0_14 = P2_10,
    GPIO0_15 = P1_20,

    GPIO1_0 = P1_7,
    GPIO1_1 = P1_8,
    GPIO1_2 = P1_9,
    GPIO1_3 = P1_10,
    GPIO1_4 = P1_11,
    GPIO1_5 = P1_12,
    GPIO1_6 = P1_13,
    GPIO1_7 = P1_14,
    GPIO1_8 = P1_5,
    GPIO1_9 = P1_6,
    GPIO1_10 = P2_9,
    GPIO1_11 = P2_11,
    GPIO1_12 = P2_12,
    GPIO1_13 = P2_13,
    GPIO1_14 = P3_4,
    GPIO1_15 = P3_5,

    GPIO2_0 = P4_0,
    GPIO2_1 = P4_1,
    GPIO2_2 = P4_2,
    GPIO2_3 = P4_3,
    GPIO2_4 = P4_4,
    GPIO2_5 = P4_5,
    GPIO2_6 = P4_6,
    GPIO2_7 = P5_7,
    GPIO2_8 = P6_12,
    GPIO2_9 = P5_0,
    GPIO2_10 = P5_1,
    GPIO2_11 = P5_2,
    GPIO2_12 = P5_3,
    GPIO2_13 = P5_4,
    GPIO2_14 = P5_5,
    GPIO2_15 = P5_6,

    GPIO3_0 = P6_1,
    GPIO3_1 = P6_2,
    GPIO3_2 = P6_3,
    GPIO3_3 = P6_4,
    GPIO3_4 = P6_5,
    GPIO3_5 = P6_9,
    GPIO3_6 = P6_10,
    GPIO3_7 = P6_11,
    GPIO3_8 = P7_0,
    GPIO3_9 = P7_1,
    GPIO3_10 = P7_2,
    GPIO3_11 = P7_3,
    GPIO3_12 = P7_4,
    GPIO3_13 = P7_5,
    GPIO3_14 = P7_6,
    GPIO3_15 = P7_7,

    GPIO4_0 = P8_0,
    GPIO4_1 = P8_1,
    GPIO4_2 = P8_2,
    GPIO4_3 = P8_3,
    GPIO4_4 = P8_4,
    GPIO4_5 = P8_5,
    GPIO4_6 = P8_6,
    GPIO4_7 = P8_7,
    GPIO4_8 = PA_1,
    GPIO4_9 = PA_2,
    GPIO4_10 = PA_3,
    GPIO4_11 = P9_6,
    GPIO4_12 = P9_0,
    GPIO4_13 = P9_1,
    GPIO4_14 = P9_2,
    GPIO4_15 = P9_3,

    GPIO5_0 = P2_0,
    GPIO5_1 = P2_1,
    GPIO5_2 = P2_2,
    GPIO5_3 = P2_3,
    GPIO5_4 = P2_4,
    GPIO5_5 = P2_5,
    GPIO5_6 = P2_6,
    GPIO5_7 = P2_8,
    GPIO5_8 = P3_1,
    GPIO5_9 = P3_2,
    GPIO5_10 = P3_7,
    GPIO5_11 = P3_8,
    GPIO5_12 = P4_8,
    GPIO5_13 = P4_9,
    GPIO5_14 = P4_10,
    GPIO5_15 = P6_7,
    GPIO5_16 = P6_8,
    GPIO5_17 = P9_4,
    GPIO5_18 = P9_5,
    GPIO5_19 = PA_4,
    GPIO5_20 = PB_0,
    GPIO5_21 = PB_1,
    GPIO5_22 = PB_2,
    GPIO5_23 = PB_3,
    GPIO5_24 = PB_4,
    GPIO5_25 = PB_5,
    GPIO5_26 = PB_6,

    GPIO6_0 = PC_1,
    GPIO6_1 = PC_2,
    GPIO6_2 = PC_3,
    GPIO6_3 = PC_4,
    GPIO6_4 = PC_5,
    GPIO6_5 = PC_6,
    GPIO6_6 = PC_7,
    GPIO6_7 = PC_8,
    GPIO6_8 = PC_9,
    GPIO6_9 = PC_10,
    GPIO6_10 = PC_11,
    GPIO6_11 = PC_12,
    GPIO6_12 = PC_13,
    GPIO6_13 = PC_14,
    GPIO6_14 = PD_0,
    GPIO6_15 = PD_1,
    GPIO6_16 = PD_2,
    GPIO6_17 = PD_3,
    GPIO6_18 = PD_4,
    GPIO6_19 = PD_5,
    GPIO6_20 = PD_6,
    GPIO6_21 = PD_7,
    GPIO6_22 = PD_8,
    GPIO6_23 = PD_9,
    GPIO6_24 = PD_10,
    GPIO6_25 = PD_11,
    GPIO6_26 = PD_12,
    GPIO6_27 = PD_13,
    GPIO6_28 = PD_14,
    GPIO6_29 = PD_15,
    GPIO6_30 = PD_16,

    GPIO7_0 = PE_0,
    GPIO7_1 = PE_1,
    GPIO7_2 = PE_2,
    GPIO7_3 = PE_3,
    GPIO7_4 = PE_4,
    GPIO7_5 = PE_5,
    GPIO7_6 = PE_5,
    GPIO7_7 = PE_7,
    GPIO7_8 = PE_8,
    GPIO7_9 = PE_9,
    GPIO7_10 = PE_10,
    GPIO7_11 = PE_11,
    GPIO7_12 = PE_12,
    GPIO7_13 = PE_13,
    GPIO7_14 = PE_14,
    GPIO7_15 = PE_15,
    GPIO7_16 = PF_1,
    GPIO7_17 = PF_2,
    GPIO7_18 = PF_3,
    GPIO7_19 = PF_5,
    GPIO7_20 = PF_6,
    GPIO7_21 = PF_7,
    GPIO7_22 = PF_8,
    GPIO7_23 = PF_9,
    GPIO7_24 = PF_10,
    GPIO7_25 = PF_11,

    // Map mbed pin names to LPC43xx board signals

    // Group 0x18 : CLKn pins
    SFP_CLK0  = MBED_PIN(0x18, 0, 0, 0),
    SFP_CLK1  = MBED_PIN(0x18, 1, 0, 0),
    SFP_CLK2  = MBED_PIN(0x18, 2, 0, 0),
    SFP_CLK3  = MBED_PIN(0x18, 3, 0, 0),

    // Group 0x19 : USB1, I2C0, ADC0, ADC1
    SFP_USB1  = MBED_PIN(0x19, 0, 0, 0),
    SFP_I2C0  = MBED_PIN(0x19, 1, 0, 0),
    SFP_AIO0  = MBED_PIN(0x19, 2, 0, 0), // ADC0 function select register
    SFP_AIO1  = MBED_PIN(0x19, 3, 0, 0), // ADC1 function select register
    SFP_AIO2  = MBED_PIN(0x19, 4, 0, 0), // Analog function select register

    SFP_EMCD  = MBED_PIN(0x1A, 0, 0, 0), // EMC clock delay register

    SFP_INS0  = MBED_PIN(0x1C, 0, 0, 0), // Interrupt select for pin interrupts 0 to 3
    SFP_INS1  = MBED_PIN(0x1C, 1, 0, 0), // Interrupt select for pin interrupts 4 to 7

    // Dedicated pin (no GPIO)
    P_DED = MBED_PIN(0, 0, NO_GPIO, 0),

    // Not connected
    NC = (int)0xFFFFFFFF,

    // ---------- Micromint Bambino 200/200E/210/210E (LQFP144) ----------
    // Base headers - J8, J9, J10 on Bambino 210/210E
    //                n/p = not populated, n/a = not available
    //              210E    210     200E    200
    //              ----    ----    ----    ----
    p15 = P7_4,  // J8-1    J8-1    S4-3    S4-3
    p16 = P7_5,  // J8-2    J8-2    S4-4    S4-4
    p17 = P4_1,  // J8-3    J8-3    S3-4    S3-4
    p18 = P7_7,  // J8-4    J8-4    S4-5    S4-5
    p19 = P4_3,  // J8-5*   J8-5*   S3-4    S3-3
    p20 = P4_4,  // J8-6*   J8-6*   S1-5    S1-5
    p20b = PF_8, // J8-6**  J8-6**  S3-5    S3-5
                 // (*)  if p20 is configured as DAC, ADC is not available for p19
                 // (**) requires JP2 mod

    p21 = P6_5,  // J9-1    J9-1    S2-5    S2-5
    p22 = P6_4,  // J9-2    J9-2    S2=4    S2-4
    p23 = P1_7,  // J9-3    J9-3    S2-3    S2-3
    p24 = P4_0,  // J9-4    J9-4    S3-7    S3-7
    p25 = P6_9,  // J9-5    J9-5    S8-7    n/p
    p26 = P5_5,  // J9-6    J9-6    S3-8    S3-8
    p27 = P5_7,  // J9-7    J9-7    S3-9    S3-9
    p28 = P7_6,  // J9-8    J9-8    S4-6    S4-6

    p29 = P6_12, // J10-1   J10-1   S10-3   n/p
    p30 = P5_0,  // J10-2   J10-2   S1-4    S1-4
    p31 = P4_6,  // J10-3   J10-3   S2-6    S2-6
    p32 = P4_8,  // J10-4   J10-4   S2-7    S2-7
    p33 = P4_9,  // J10-5   J10-5   S2-8    S2-8
    p34 = P4_10, // J10-6   J10-6   S2-9    S2-9
    p37 = P2_3,  // J10-9   J10-9   S4-8    S4-8
    p38 = P2_4,  // J10-10  J10-10  S4-9    S4-9

    // Extended headers - J11, J12, J13, J14 on Bambino 210E
    //              210E    210     200E    200
    //              ----    ----    ----    ----
    p47 = P6_3,  // J11-1   n/p     S7-5    n/p
    p48 = P6_6,  // J11-2   n/p     S6-7    n/p
    p49 = P6_7,  // J11-3   n/p     S6-8    n/p
    p50 = P6_8,  // J11-4   n/p     S6-9    n/p
    p53 = P2_2,  // J11-7   n/p     S7-7    n/p
    p54 = P2_1,  // J11-8   n/p     S7-3    n/p

    p55 = PF_10, // J12-1   n/p     n/a     n/a
    p56 = PF_7,  // J12-2   n/p     n/a     n/a
    p57 = P2_6,  // J12-3   n/p     S8-6    n/p
    p58 = P2_8,  // J12-4   n/p     S8-3    n/p
    p59 = P6_10, // J12-5   n/p     S7-8    n/p
    p60 = P2_9,  // J12-6   n/p     S9-3    n/p

    p61 = P7_3,  // J13-1   n/p     S7-9    n/p
    p62 = P3_2,  // J13-2   n/p     S9-4    n/p
    p63 = P7_2,  // J13-3   n/p     S4-7    S4-7
    p64 = P3_1,  // J13-4   n/p     S9-5    n/p
    p65 = P7_1,  // J13-5   n/p     S9-8    n/p
    p66 = P7_0,  // J13-6   n/p     S9-9    n/p
    p67 = P4_2,  // J13-7   n/p     S4-6    S4-6
    p68 = P4_5,  // J13-8   n/p     S1-3    S1-3

    p69 = P2_13, // J14-1   n/p     S9-7    n/p
    p70 = P2_12, // J14-2   n/p     S9-6    n/p
    p71 = P9_6,  // J14-3   n/p     S6-6    n/p
    p72 = P9_5,  // J14-4   n/p     S7-4    n/p
    p73 = P5_3,  // J14-5   n/p     S6-5    n/p
    p74 = P1_8,  // J14-6   n/p     S6-4    n/p
    p75 = P1_5,  // J14-7   n/p     S10-6   n/p
    p76 = P1_4,  // J14-8   n/p     S10-7   n/p
    p77 = P1_3,  // J14-9   n/p     S10-8   n/p
    p78 = PF_4,  // J14-10  n/p     S10-9   n/p

    // J16 - PMOD-SSP header (not populated, field installable)
    p80 = P1_0,  // J16-1   J16-1   S1-6    S1-6
    p81 = P1_2,  // J16-2   J16-2   S1-7    S1-7
    p82 = P1_1,  // J16-3   J16-3   S1-8    S1-8
    p83 = P3_0,  // J16-4   J16-4   S1-9    S1-9

    // Arduino pins - J8, J9, J10
    //              210E    210     200E    200
    //              ----    ----    ----    ----
    D0  = p21,  // J9-1     J9-1    S2-5    S2-5
    D1  = p22,  // J9-2     J9-2    S2-4    S2-4
    D2  = p23,  // J9-3     J9-3    S2-3    S2-3
    D3  = p24,  // J9-4     J9-4    S3-7    S3-7
    D4  = p25,  // J9-5     J9-5    S8-7    n/p
    D5  = p26,  // J9-6     J9-6    S3-8    S3-8
    D6  = p27,  // J9-7     J9-7    S3-9    S3-9
    D7  = p28,  // J9-8     J9-8    S4-6    S4-6

    D8  = p29,  // J10-1    J10-1   S10-1   n/p
    D9  = p30,  // J10-2    J10-2   S1-4    S1-4
    D10 = p31,  // J10-3    J10-3   S2-6    S2-6
    D11 = p32,  // J10-4    J10-4   S2-7    S2-7
    D12 = p33,  // J10-5    J10-5   S2-8    S2-8
    D13 = p34,  // J10-6    J10-6   S2-9    S2-9
    D16 = p37,  // J10-9    J10-9   S4-8    S4-8
    D17 = p38,  // J10-10   J10-10  S4-9    S4-9

    A0  = p15,  // J8-1     J8-1    S4-3    S4-3
    A1  = p16,  // J8-2     J8-2    S4-4    S4-4
    A2  = p17,  // J8-3     J8-3    S3-4    S3-4
    A3  = p18,  // J8-4     J8-4    S3-4    S3-4
    A4  = p19,  // J8-5*    J8-5*   S3-3    S3-3
    A5  = p20,  // J8-6*    J8-6*   S1-5    S1-5
    A5b = p20b, // J8-6**   J8-6**  S3-5    S3-5
                // (*)  if A5 is configured as DAC, ADC is not available for A4
                // (**) requires JP2 mod

    // Extended Arduino pins - J11, J12, J13, J14
    //             210E     210     200E    200
    //             ----     ----    ----    ----
    D20 = p61,  // J13-1    n/p     S7-9    n/p
    D21 = p62,  // J13-2    n/p     S9-4    n/p
    D22 = p63,  // J13-3    n/p     S4-7    S4-7
    D23 = p64,  // J13-4    n/p     S9-5    n/p
    D24 = p65,  // J13-5    n/p     S9-8    n/p
    D25 = p66,  // J13-6    n/p     S9-9    n/p
    D26 = p67,  // J13-7    n/p     S3-7    S3-7
    D27 = p68,  // J13-8    n/p     S1-3    S1-3

    D30 = p69,  // J14-1    n/p     S9-7    n/p
    D31 = p70,  // J14-2    n/p     S9-6    n/p
    D32 = p71,  // J14-3    n/p     S6-6    n/p
    D33 = p72,  // J14-4    n/p     S7-4    n/p
    D34 = p73,  // J14-5    n/p     S6-5    n/p
    D35 = p74,  // J14-6    n/p     S6-4    n/p
    D36 = p75,  // J14-7    n/p     S10-6   n/p
    D37 = p76,  // J14-8    n/p     S10-7   n/p
    D38 = p77,  // J14-9    n/p     S10-8   n/p
    D39 = p78,  // J14-10   n/p     S10-9   n/p

    D40 = p47,  // J11-1    n/p     S7-5    n/p
    D41 = p48,  // J11-2    n/p     S6-7    n/p
    D42 = p49,  // J11-3    n/p     S6-8    n/p
    D43 = p50,  // J11-4    n/p     S6-9    n/p
    D46 = p53,  // J11-7    n/p     S7-7    n/p
    D47 = p54,  // J11-8    n/p     S7-3    n/p

    D52 = p57,  // J12-3    n/p     S8-6    n/p
    D53 = p58,  // J12-4    n/p     S8-3    n/p
    D54 = p59,  // J12-5    n/p     S7-8    n/p
    D55 = p60,  // J12-6    n/p     S9-3    n/p

    A6  = p55,  // J12-1    n/p     n/a     n/a
    A7  = p56,  // J12-2    n/p     n/a     n/a

    // User interfaces: LEDs, buttons
    //                   210E    210     200E    200
    //                   ----    ----    ----    ----
    LED1 = P6_11,     // 210/210E/200e/200
    LED2 = P2_5,      // 210/210E/200e/200
    LED3 = P6_1,      // 210/210E only   S6-3    n/p
    LED4 = P6_2,      // 210/210E only   S7-6    n/p

    LED_YELLOW = LED1,
    LED_GREEN = LED2,
    LED_RED = LED3,
    LED_BLUE = LED4,

    BTN1 = P2_7,

    // Serial pins - UART, SPI, I2C
    //                   210E    210     200E    200
    //                   ----    ----    ----    ----
    UART0_TX = P6_4,  // J9-2    J9-2    S2-4    S2-4
    UART0_RX = P6_5,  // J9-1    J9-1    S2-5    S2-5
    UART1_TX = P5_6,  // XBEE    n/p     S5-4/XBEE S5-4
    UART1_RX = P1_14, // XBEE    n/p     S5-5/XBEE S5-5
    UART2_TX = P2_10, // MBEDHDK MBEDHDK S10-4   n/p
    UART2_RX = P2_11, // MBEDHDK MBEDHDK S10-5   n/p
    UART3_TX = P2_3,  // J10-9   n/p     S4-8    S4-8
    UART3_RX = P2_4,  // J10-10  n/p     S4-9    S4-9

    COM1_TX = UART0_TX,
    COM1_RX = UART0_RX,
    COM2_TX = UART1_TX,
    COM2_RX = UART1_RX,
    COM3_TX = UART2_TX,
    COM3_RX = UART2_RX,
    COM4_TX = UART3_TX,
    COM4_RX = UART3_RX,

    //                   210E    210     200E    200
    //                   ----    ----    ----    ----
    SPI0_SCK  = P3_0, // J16-4   n/p     S1-9    S1-9
    SPI0_MISO = P1_1, // J16-3   n/p     S1-8    S1-8
    SPI0_MOSI = P1_2, // J16-2   n/p     S1-7    S1-7
    SPI0_SSEL = P1_0, // J16-1   n/p     S1-6    S1-6
    SPI1_SCK  = PF_4, // J14-10  n/p     S10-9   n/p
    SPI1_MISO = P1_3, // J14-9   n/p     S10-8   n/p
    SPI1_MOSI = P1_4, // J14-8   n/p     S10-7   n/p
    SPI1_SSEL = P1_5, // J14-7   n/p     S10-6   n/p

    I2C0_SDA = P_DED, // J15-3   J15-3   S8-8    n/p
    I2C0_SCL = P_DED, // J15-1   J15-1   S8-9    n/p
    I2C1_SDA = P2_3,  // J10-9   J10-9   S4-8    S4-8
    I2C1_SCL = P2_4,  // J10-10  J10-10  S4-9    S4-9

    // Analog pins
    ADC0 = P7_4,      // J8-1     J8-1    S4-3    S4-3
    ADC1 = P7_5,      // J8-2     J8-2    S4-4    S4-4
    ADC2 = P4_1,      // J8-3     J8-3    S3-4    S3-4
    ADC3 = P7_7,      // J8-4     J8-4    S3-4    S3-4
    ADC4 = P4_3,      // J8-5*    J8-5*   S3-3    S3-3
    ADC5 = PF_8,      // J8-6**   J8-6**  S1-5    S1-5
    ADC6 = PF_10,     // J12-1    n/p     n/a     n/a
    ADC7 = PF_7,      // J12-2    n/p     n/a     n/a
    DAC0 = P4_4,      // J8-6*    J8-6*   S3-5    S3-5
                      // (*)  if DAC0 is configured, ADC4 is not available
                      // (**) ADC5 requires JP2 mod

    // USB pins
    //                   210E    210     200E    200
    //                   ----    ----    ----    ----
    USBTX = UART2_TX, // MBEDHDK MBEDHDK S10-4   n/p
    USBRX = UART2_RX, // MBEDHDK MBEDHDK S10-5   n/p

    // PWM pins
    //                   210E    210     200E    200
    //                   ----    ----    ----    ----
    PWM1 = P1_7,      // J9-3    J9-3    S2-3    S2-3
    PWM2 = P7_6,      // J9-8    J9-8    S4-6    S4-6
    PWM3 = P6_12,     // J10-1   J10-1   S10-3   n/p
    PWM4 = P4_6,      // J10-3   J10-3   S2-6    S2-6
    PWM5 = P7_5,      // J8-2    J8-2    S4-4    S4-4
    PWM6 = P4_1,      // J8-3    J8-3    S3-4    S3-4
    PWM7 = P7_7,      // J8-4    J8-4    S4-5    S4-5
    PWM8 = P2_8,      // J12-4   n/p     S8-3    n/p
    PWM9 = P2_9,      // J12-6   n/p     S9-3    n/p
    PWM10 = P7_1,     // J13-5   n/p     S9-8    n/p
    PWM11 = P7_0,     // J13-6   n/p     S9-9    n/p
    PWM12 = P1_5,     // J14-7   n/p     S10-6   n/p

    // ---------- End of Micromint Bambino ----------
} PinName;

typedef enum {
    PullUp = 0,
    PullDown = 3,
    PullNone = 2,
    Repeater = 1,
    OpenDrain = 4,
    PullDefault = PullDown
} PinMode;

#ifdef __cplusplus
}
#endif

#endif
