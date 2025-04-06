/* Copyright 2024 keymagichorse
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once
 

#ifdef BLUETOOTH_BHQ
// Its active level is "BHQ_IRQ_AND_INT_LEVEL of bhq.h " 
#   define BHQ_IQR_PIN      A1             // Module operating status
#   define BHQ_INT_PIN       A0             // QMK operating status

#   define UART_DRIVER          SD2
#   define UART_TX_PIN          A2
#   define UART_TX_PAL_MODE     7
#   define UART_RX_PIN          A3
#   define UART_RX_PAL_MODE	    7

// STM32使用到的高速晶振引脚号，做低功耗需要用户配置，每款芯片有可能不一样的
#define LPM_STM32_HSE_PIN_IN     H1  
#define LPM_STM32_HSE_PIN_OUT    H0

#endif

/*************************matrix**************************/
/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 4
/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* key matrix pins */
#define MATRIX_ROW_PINS { NO_PIN, A8, B15, B8, B9, C13 }
                        //  Q7      Q6      Q5     Q4
#define MATRIX_COL_PINS { NO_PIN, NO_PIN, NO_PIN, NO_PIN}

// 列 接到 74HC595 的哪个 Qx
#define COL_TO_74HC595_PINS  { _1_595_Q7, _1_595_Q6, _1_595_Q5, _1_595_Q4}
// 定义列映射到 74HC595 的管脚数量
#define COL_TO_74HC595_PINS_COUNT  4    
// 第几个列开始接到595     
#define COL_TO_74HC595_START_INDEX    0   
// 到第几个列结束到595
#define COL_TO_74HC595_END_INDEX      3  


/* Pin connected to DS of 74HC595 */
#define DS_PIN_74HC595 A4
/* Pin connected to SH_CP of 74HC595 */
#define SHCP_PIN_74HC595 A6
/* Pin connected to ST_CP of 74HC595 */
#define STCP_PIN_74HC595 A5


/*************************matrix**************************/



#define WS2812_BYTE_ORDER       WS2812_BYTE_ORDER_GRB

#define RGBLIGHT_LAYERS
#define RGBLIGHT_LAYER_BLINK
#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
#define RGBLIGHT_LAYERS_RETAIN_VAL
