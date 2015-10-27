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

/************ADC***************/
const PinMap PinMap_ADC[] = {
    {PTC2,  ADC0_SE4b, 0},
    {PTC8,  ADC1_SE4b, 0},
    {PTC9,  ADC1_SE5b, 0},
    {PTD1,  ADC0_SE5b, 0},
    {PTC10, ADC1_SE6b, 0},
    {PTD5,  ADC0_SE6b, 0},
    {PTC11, ADC1_SE7b, 0},
    {PTD6,  ADC0_SE7b, 0},
    {PTB0 , ADC0_SE8 , 0},
    {PTB1 , ADC0_SE9 , 0},
    {PTB2 , ADC0_SE12, 0},
    {PTB3 , ADC0_SE13, 0},
    {PTC0 , ADC0_SE14, 0},
    {PTB10, ADC1_SE14, 0},
    {PTB11, ADC1_SE15, 0},
    {PTC1 , ADC0_SE15, 0},
    {PTA17, ADC1_SE17, 0},
    //{PTE24, ADC0_SE17, 0}, //I2C pull up
    //{PTE25, ADC0_SE18, 0}, //I2C pull up
    {NC   , NC       , 0}
};

/************DAC***************/
const PinMap PinMap_DAC[] = {
    {DAC0_OUT, DAC_0, 0},
    {NC      , NC   , 0}
};

/************I2C***************/
const PinMap PinMap_I2C_SDA[] = {
    {PTB1 , I2C_0 , 2},
    {PTB3 , I2C_0 , 2},
    {PTC11, I2C_1 , 2},
    {PTD3 , I2C_0 , 7},
    {PTD9 , I2C_0 , 2},
    {PTE0 , I2C_1 , 6},
    {PTE25, I2C_0 , 5},
    {NC   , NC   , 0}
};

const PinMap PinMap_I2C_SCL[] = {
    {PTB0 , I2C_0 , 2},
    {PTB2 , I2C_0 , 2},
    {PTC10, I2C_1 , 2},
    {PTD2 , I2C_0 , 7},
    {PTD8 , I2C_0 , 2},
    {PTE1 , I2C_1 , 6},
    {PTE24, I2C_0 , 5},
    {NC   , NC   , 0}
};

/************UART***************/
const PinMap PinMap_UART_TX[] = {
    {PTA2 , UART_0, 2},
    {PTA14, UART_0, 3},
    {PTB17, UART_0, 3},
    {PTD7 , UART_0, 3},
    {PTC4 , UART_1, 3},
    {PTE0 , UART_1, 3},
    {PTD3 , UART_2, 3},
    {NC   ,  NC   , 0}
};

const PinMap PinMap_UART_RX[] = {
    {PTA1 , UART_0, 2},
    {PTA15, UART_0, 3},
    {PTB16, UART_0, 3},
    {PTD6 , UART_0, 3},
    {PTC3 , UART_1, 3},
    {PTE1 , UART_1, 3},
    {PTD2 , UART_2, 3},
    {NC   ,  NC    , 0}
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

/************PWM***************/
const PinMap PinMap_PWM[] = {
    {PTA0 , PWM_05, 3},
    {PTA1 , PWM_06, 3},
    {PTA2 , PWM_07, 3},
    {PTA3 , PWM_00, 3},
    {PTA4 , PWM_01, 3},
    {PTA5 , PWM_02, 3},
    {PTA10, PWM_20, 3},
    {PTA11, PWM_21, 3},
    {PTA12, PWM_10, 3},
    {PTA13, PWM_11, 3},
    
    {PTB0 , PWM_10, 3},
    {PTB1 , PWM_11, 3},
    {PTB18, PWM_20, 3},
    {PTB19, PWM_21, 3},
    
    {PTC1 , PWM_00, 4},
    {PTC2 , PWM_01, 4},
    {PTC3 , PWM_02, 4},
    {PTC4 , PWM_03, 4},
    {PTC5 , PWM_02, 7},
    
    {PTD0 , PWM_30, 4},
    {PTD1 , PWM_31, 4},
    {PTD2 , PWM_32, 4},
    {PTD3 , PWM_33, 4},
    {PTD4 , PWM_04, 4},
    {PTD5 , PWM_05, 4},
    {PTD6 , PWM_06, 4},
    {PTD7 , PWM_07, 4},
    
    {PTE5 , PWM_30, 6},
    {PTE6 , PWM_31, 6},
    {NC   ,  NC   , 0}
};
