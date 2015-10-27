
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
    {PTC1, RTC_CLKIN, 1},
};

/************ADC***************/
const PinMap PinMap_ADC[] = {
    {PTE20, ADC0_SE0,  0},
    {PTE22, ADC0_SE3,  0},
    {PTE21, ADC0_SE4a, 0},
    {PTE29, ADC0_SE4b, 0},
    {PTE30, ADC0_SE23, 0},
    {PTE23, ADC0_SE7a, 0},
    {PTB0,  ADC0_SE8,  0},
    {PTB1,  ADC0_SE9,  0},
    {PTB2,  ADC0_SE12, 0},
    {PTB3,  ADC0_SE13, 0},
    {PTC0,  ADC0_SE14, 0},
    {PTC1,  ADC0_SE15, 0},
    {PTC2,  ADC0_SE11, 0},
    {PTD1,  ADC0_SE5b, 0},
    {PTD5,  ADC0_SE6b, 0},
    {PTD6,  ADC0_SE7b, 0},
    {NC,    NC,        0}
};

/************DAC***************/
const PinMap PinMap_DAC[] = {
    {PTE30, DAC_0, 0},
    {NC   , NC   , 0}
};

/************I2C***************/
const PinMap PinMap_I2C_SDA[] = {
    {PTE25, I2C_0, 5},
    {PTC9,  I2C_0, 2},
    {PTE0,  I2C_1, 6},
    {PTB1,  I2C_0, 2},
    {PTB3,  I2C_0, 2},
    {PTC11, I2C_1, 2},
    {PTC2,  I2C_1, 2},
    {PTA4,  I2C_1, 2},
    {NC  ,  NC   , 0}
};

const PinMap PinMap_I2C_SCL[] = {
    {PTE24, I2C_0, 5},
    {PTC8,  I2C_0, 2},
    {PTE1,  I2C_1, 6},
    {PTB0,  I2C_0, 2},
    {PTB2,  I2C_0, 2},
    {PTC10, I2C_1, 2},
    {PTC1,  I2C_1, 2},
    {NC  ,  NC,    0}
};

/************UART***************/
const PinMap PinMap_UART_TX[] = {
    {PTC4,  UART_1, 3},
    {PTA2,  UART_0, 2},
    {PTD5,  UART_2, 3},
    {PTD3,  UART_2, 3},
    {PTD7,  UART_0, 3},
    {PTE20, UART_0, 4},
    {PTE22, UART_2, 4},
    {PTE0,  UART_1, 3},
    {NC  ,  NC    , 0}
};

const PinMap PinMap_UART_RX[] = {
    {PTC3,  UART_1, 3},
    {PTA1,  UART_0, 2},
    {PTD4,  UART_2, 3},
    {PTD2,  UART_2, 3},
    {PTD6,  UART_0, 3},
    {PTE23, UART_2, 4},
    {PTE21, UART_0, 4},
    {PTE1,  UART_1, 3},
    {NC  ,  NC    , 0}
};

/************SPI***************/
const PinMap PinMap_SPI_SCLK[] = {
    {PTA15, SPI_0, 2},
    {PTB11, SPI_1, 2},
    {PTC5,  SPI_0, 2},
    {PTD1,  SPI_0, 2},
    {PTD5,  SPI_1, 2},
    {PTE2,  SPI_1, 2},
    {NC  ,  NC   , 0}
};

const PinMap PinMap_SPI_MOSI[] = {
    {PTA16, SPI_0, 2},
    {PTA17, SPI_0, 5},
    {PTB16, SPI_1, 2},
    {PTB17, SPI_1, 5},
    {PTC6,  SPI_0, 2},
    {PTC7,  SPI_0, 5},
    {PTD2,  SPI_0, 2},
    {PTD3,  SPI_0, 5},
    {PTD6,  SPI_1, 2},
    {PTD7,  SPI_1, 5},
    {PTE1,  SPI_1, 2},
    {PTE3,  SPI_1, 5},
    {NC  ,  NC   , 0}
};

const PinMap PinMap_SPI_MISO[] = {
    {PTA16, SPI_0, 5},
    {PTA17, SPI_0, 2},
    {PTB16, SPI_1, 5},
    {PTB17, SPI_1, 2},
    {PTC6,  SPI_0, 5},
    {PTC7,  SPI_0, 2},
    {PTD2,  SPI_0, 5},
    {PTD3,  SPI_0, 2},
    {PTD6,  SPI_1, 5},
    {PTD7,  SPI_1, 2},
    {PTE1,  SPI_1, 5},
    {PTE3,  SPI_1, 2},
    {NC   , NC   , 0}
};

const PinMap PinMap_SPI_SSEL[] = {
    {PTA14, SPI_0, 2},
    {PTB10, SPI_1, 2},
    {PTC4,  SPI_0, 2},
    {PTD0,  SPI_0, 2},
    {PTD4,  SPI_1, 2},
    {PTE4,  SPI_1, 2},
    {NC  ,  NC   , 0}
};

/************PWM***************/
const PinMap PinMap_PWM[] = {
    {PTA0,  PWM_6,  3}, // PTA0 , TPM0 CH5    
    {PTA1,  PWM_9 , 3}, // PTA1 , TPM2 CH0
    {PTA2,  PWM_10, 3}, // PTA2 , TPM2 CH1
    {PTA3,  PWM_1,  3}, // PTA3 , TPM0 CH0
    {PTA4,  PWM_2 , 3}, // PTA4 , TPM0 CH1
    {PTA5,  PWM_3 , 3}, // PTA5 , TPM0 CH2
    {PTA12, PWM_7 , 3}, // PTA12, TPM1 CH0
    {PTA13, PWM_8 , 3}, // PTA13, TPM1 CH1  
    
    {PTB0,  PWM_7,  3}, // PTB0 , TPM1 CH0
    {PTB1,  PWM_8,  3}, // PTB1 , TPM1 CH1
    {PTB2,  PWM_9,  3}, // PTB2 , TPM2 CH0
    {PTB3,  PWM_10, 3}, // PTB3 , TPM2 CH1
    {PTB18, PWM_9,  3}, // PTB18, TPM2 CH0
    {PTB19, PWM_10, 3}, // PTB18, TPM2 CH1

    {PTC1,  PWM_1,  4}, // PTC1 , TPM0 CH0
    {PTC2,  PWM_2,  4}, // PTC2 , TPM0 CH1
    {PTC3,  PWM_3,  4}, // PTC3 , TPM0 CH2
    {PTC4,  PWM_4,  4}, // PTC4 , TPM0 CH3
    {PTC8,  PWM_5 , 3}, // PTC8 , TPM0 CH4
    {PTC9,  PWM_6 , 3}, // PTC9 , TPM0 CH5    
    
    {PTD0,  PWM_1 , 4}, // PTD0 , TPM0 CH0
    {PTD1,  PWM_2 , 4}, // PTD0 , TPM0 CH1
    {PTD2,  PWM_3 , 4}, // PTD2 , TPM0 CH2
    {PTD3,  PWM_4 , 4}, // PTD3 , TPM0 CH3    
    {PTD4,  PWM_5 , 4}, // PTD4 , TPM0 CH4
    {PTD5,  PWM_6 , 4}, // PTD5 , TPM0 CH5

    {PTE20, PWM_7,  3}, // PTE20, TPM1 CH0
    {PTE21, PWM_8,  3}, // PTE21, TPM1 CH1
    {PTE22, PWM_9,  3}, // PTE22, TPM2 CH0
    {PTE23, PWM_10, 3}, // PTE23, TPM2 CH1
    {PTE24, PWM_1,  3}, // PTE24, TPM0 CH0
    {PTE25, PWM_2,  3}, // PTE25, TPM0 CH1
    {PTE26, PWM_6,  3}, // PTE26, TPM0 CH5
    {PTE29, PWM_3,  3}, // PTE29, TPM0 CH2
    {PTE30, PWM_4,  3}, // PTE30, TPM0 CH3
    {PTE31, PWM_5,  3}, // PTE31, TPM0 CH4
    {NC   , NC,     0}
};
