/*
    ChibiOS - Copyright (C) 2020 Codetector <codetector@codetector.cn>

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef BOARD_H
#define BOARD_H
/*
 * Setup for Anne Pro 2 board.
 */

/*
 * Board identifier.
 */
#define ANNEPRO2
#define BOARD_NAME                  "Anne Pro 2"

#define HT32F52342

#define FLASH_SIZE                  (0x10000 - 0x4000)      // 64kB - 16kB

/*
 * I/O
 */
#define LINE_UART_TX                PAL_LINE(IOPORTB,  0)
#define LINE_UART_RX                PAL_LINE(IOPORTB,  1)

#define LINE_BT_UART_TX             PAL_LINE(IOPORTA,  4) // Master TX, BLE RX
#define LINE_BT_UART_RX             PAL_LINE(IOPORTA,  5) // Master RX, BLE TX

// outputs (rows are pulled low)
#define LINE_ROW1                   PAL_LINE(IOPORTB,  5)
#define LINE_ROW2                   PAL_LINE(IOPORTB,  4)
#define LINE_ROW3                   PAL_LINE(IOPORTB,  3)
#define LINE_ROW4                   PAL_LINE(IOPORTB,  2)
#define LINE_ROW5                   PAL_LINE(IOPORTD,  1)

// inputs (columns are sampled)
#define LINE_COL1                   PAL_LINE(IOPORTC,  4)
#define LINE_COL2                   PAL_LINE(IOPORTC,  5)
#define LINE_COL3                   PAL_LINE(IOPORTD,  0)
#define LINE_COL4                   PAL_LINE(IOPORTB, 15)
#define LINE_COL5                   PAL_LINE(IOPORTC, 11)
#define LINE_COL6                   PAL_LINE(IOPORTA, 15)
#define LINE_COL7                   PAL_LINE(IOPORTC, 12)
#define LINE_COL8                   PAL_LINE(IOPORTC, 13)
#define LINE_COL9                   PAL_LINE(IOPORTA,  8)
#define LINE_COL10                  PAL_LINE(IOPORTA, 10)
#define LINE_COL11                  PAL_LINE(IOPORTA, 11)
#define LINE_COL12                  PAL_LINE(IOPORTA, 14)
#define LINE_COL13                  PAL_LINE(IOPORTD,  2)
#define LINE_COL14                  PAL_LINE(IOPORTD,  3)

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
    void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* BOARD_H */
