
/* mbed Microcontroller Library
 * Copyright (c) 2006-2015 ARM Limited
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

/************ADC***************/
const PinMap PinMap_ADC[] = {
    {PTC2, ADC0_SE4b, 0},
    {PTD1, ADC0_SE5b, 0},
    {PTD5, ADC0_SE6b, 0},
    {PTD6, ADC0_SE7b, 0},
    {PTB0, ADC0_SE8,  0},
    {PTB1, ADC0_SE9,  0},
    {PTB2, ADC0_SE12, 0},
    {PTB3, ADC0_SE13, 0},
    {PTC0, ADC0_SE14, 0},
    {PTC1, ADC0_SE15, 0},
    {NC,   NC,        0}
};

/************I2C***************/
const PinMap PinMap_I2C_SDA[] = {
    {PTB1,  I2C_0, 2},
    {PTB3,  I2C_0, 2},
    {NC  ,  NC   , 0}
};

const PinMap PinMap_I2C_SCL[] = {
    {PTB0,  I2C_0, 2},
    {PTB2,  I2C_0, 2},
    {NC  ,  NC,    0}
};

/************UART***************/
const PinMap PinMap_UART_TX[] = {
    {PTB17, UART_0, 3},
    {PTC4 , UART_1, 3},
    {PTD3 , UART_2, 3},
    {PTD7 , UART_0, 3},
    {PTE0 , UART_1, 3},
    {NC   , NC    , 0}
};

const PinMap PinMap_UART_RX[] = {
    {PTB16, UART_0, 3},
    {PTC3 , UART_1, 3},
    {PTD2 , UART_2, 3},
    {PTD6 , UART_0, 3},
    {PTE1 , UART_1, 3},
    {NC   , NC    , 0}
};

/************SPI***************/
const PinMap PinMap_SPI_SCLK[] = {
    {PTC5, SPI_0, 2},
    {PTD1, SPI_0, 2},
    {NC  , NC   , 0}
};

const PinMap PinMap_SPI_MOSI[] = {
    {PTD2, SPI_0, 2},
    {PTC6, SPI_0, 2},
    {NC  , NC   , 0}
};

const PinMap PinMap_SPI_MISO[] = {
    {PTD3, SPI_0, 2},
    {PTC7, SPI_0, 2},
    {NC  , NC   , 0}
};

const PinMap PinMap_SPI_SSEL[] = {
    {PTD0, SPI_0, 2},
    {PTC4, SPI_0, 2},
    {NC  , NC   , 0}
};

/************PWM***************/
const PinMap PinMap_PWM[] = {
    // LEDs
    {LED_RED  , PWM_3 , 4}, // PTC3, FTM0 CH2
    {LED_GREEN, PWM_5,  4}, // PTD4, FTM0 CH4
    {LED_BLUE , PWM_8 , 3}, // PTA2, FTM0 CH7

    // Arduino digital pinout
    {D3,  PWM_5 , 4}, // PTD4, FTM0 CH4
    {D5,  PWM_7 , 3}, // PTA1, FTM0 CH6
    {D6,  PWM_3 , 4}, // PTC3, FTM0 CH2
    {D9,  PWM_6 , 4}, // PTD5, FTM0 CH6
    {D10, PWM_2 , 4}, // PTC2, FTM0 CH1

    {PTA0,  PWM_6 , 3}, // PTA0, FTM0 CH5
    {PTA3,  PWM_1 , 3}, // PTA3, FTM0 CH0
    {PTA4,  PWM_2 , 3}, // PTA4, FTM0 CH1
    {PTA5,  PWM_3 , 3}, // PTA5, FTM0 CH2
    {PTA12, PWM_9 , 3}, // PTA12, FTM1 CH0
    {PTA13, PWM_10, 3}, // PTA13, FTM1 CH1
    {PTB0,  PWM_9 , 3}, // PTB0, FTM1 CH0
    {PTB1,  PWM_10, 3}, // PTB1, FTM1 CH1
    {PTC1,  PWM_1 , 4}, // PTC1, FTM0 CH0
    {PTD4,  PWM_4 , 4}, // PTD4, FTM0 CH3
    {PTD6,  PWM_7 , 4}, // PTD6, FTM0 CH6
    {PTD7,  PWM_8 , 4}, // PTD7, FTM0 CH7

    {NC , NC    , 0}
};
