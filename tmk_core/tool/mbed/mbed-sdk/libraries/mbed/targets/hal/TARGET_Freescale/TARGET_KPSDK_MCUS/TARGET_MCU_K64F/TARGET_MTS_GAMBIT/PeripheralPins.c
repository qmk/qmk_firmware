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
 
#include "PeripheralPins.h"

/************RTC***************/
const PinMap PinMap_RTC[] = {
    {NC, OSC32KCLK, 0},
};

/************I2C***************/
const PinMap PinMap_I2C_SDA[] = {
    {PTE25, I2C_0, 5},
    {PTB1 , I2C_0, 2},
    {PTB3 , I2C_0, 2},
    {PTC11, I2C_1, 2},
    {PTD3 , I2C_0, 7},
    {PTE0 , I2C_1, 6},
    {NC   , NC   , 0}
};

const PinMap PinMap_I2C_SCL[] = {
    {PTE24, I2C_0, 5},
    {PTB0 , I2C_0, 2},
    {PTB2 , I2C_0, 2},
    {PTC10, I2C_1, 2},
    {PTD2 , I2C_0, 7},
    {PTE1 , I2C_1, 6},
    {NC   , NC   , 0}
};

/************UART***************/
const PinMap PinMap_UART_TX[] = {
    {PTB17, UART_0, 3},
    {PTC17, UART_3, 3},
    {PTD7 , UART_0, 3},
    {PTD3 , UART_2, 3},
    {PTB11, UART_3, 3},
    {PTA14, UART_0, 3},
    {PTE4 , UART_3, 3},
    {PTE8 , UART_5, 3},
    {NC  ,  NC    , 0}
};

const PinMap PinMap_UART_RX[] = {
    {PTB16, UART_0, 3},
    {PTE5 , UART_3, 3},
    {PTA15, UART_0, 3},
    {PTC16, UART_3, 3},
    {PTB10, UART_3, 3},
    {PTD2 , UART_2, 3},
    {PTC6 , UART_0, 3},
    {PTE9 , UART_5, 3},
    {NC  ,  NC    , 0}
};

/************SPI***************/
const PinMap PinMap_SPI_SCLK[] = {
    {PTD1 , SPI_0, 2},
    {PTE2 , SPI_1, 2},
    {PTA15, SPI_0, 2},
    {PTB11, SPI_1, 2},
    {PTC5 , SPI_0, 2},
    {PTD5 , SPI_1, 7},
    {NC   , NC   , 0}
};

const PinMap PinMap_SPI_MOSI[] = {
    {PTD2 , SPI_0, 2},
    {PTE1 , SPI_1, 2},
    {PTE3 , SPI_1, 7},
    {PTA16, SPI_0, 2},
    {PTB16, SPI_1, 2},
    {PTC6 , SPI_0, 2},
    {PTD6 , SPI_1, 7},
    {NC   , NC   , 0}
};

const PinMap PinMap_SPI_MISO[] = {
    {PTD3 , SPI_0, 2},
    {PTE1 , SPI_1, 7},
    {PTE3 , SPI_1, 2},
    {PTA17, SPI_0, 2},
    {PTB17, SPI_1, 2},
    {PTC7 , SPI_0, 2},
    {PTD7 , SPI_1, 7},
    {NC   , NC   , 0}
};

const PinMap PinMap_SPI_SSEL[] = {
    {PTD0 , SPI_0, 2},
    {PTE4 , SPI_1, 2},
    {PTA14, SPI_0, 2},
    {PTB10, SPI_1, 2},
    {PTC4 , SPI_0, 2},
    {PTD4 , SPI_1, 7},
    {NC   , NC   , 0}
};

