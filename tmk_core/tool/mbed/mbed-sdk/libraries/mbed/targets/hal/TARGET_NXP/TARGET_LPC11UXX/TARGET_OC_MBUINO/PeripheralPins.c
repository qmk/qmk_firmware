
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

/************ADC***************/
const PinMap PinMap_ADC[] = {
    {P0_11, ADC0_0, 0x02},
    {P0_12, ADC0_1, 0x02},
    {P0_13, ADC0_2, 0x02},
    {P0_14, ADC0_3, 0x02},
    {P0_15, ADC0_4, 0x02},
    {P0_16, ADC0_5, 0x01},
    {P0_22, ADC0_6, 0x01},
    {P0_23, ADC0_7, 0x01},
    {NC   , NC    , 0   }
};

/************I2C***************/
const PinMap PinMap_I2C_SDA[] = {
    {P0_5, I2C_0, 1},
    {NC  , NC   , 0}
};

const PinMap PinMap_I2C_SCL[] = {
    {P0_4, I2C_0, 1},
    {NC  , NC,    0}
};

/************UART***************/
const PinMap PinMap_UART_TX[] = {
    {P0_19, UART_0, 1},
    { NC  , NC    , 0}
};

const PinMap PinMap_UART_RX[] = {
    {P0_18, UART_0, 1},
    {NC   , NC    , 0}
};

/************SPI***************/
const PinMap PinMap_SPI_SCLK[] = {
    {P0_6 , SPI_0, 0x02},
    {P0_10, SPI_0, 0x02},
    {P1_15, SPI_1, 0x03},
    {NC   , NC   , 0}
};

const PinMap PinMap_SPI_MOSI[] = {
    {P0_9 , SPI_0, 0x01},
    {P0_21, SPI_1, 0x02},
    {NC   , NC   , 0}
};

const PinMap PinMap_SPI_MISO[] = {
    {P0_8 , SPI_0, 0x01},
    {P0_22, SPI_1, 0x03},
    {NC   , NC   , 0}
};

const PinMap PinMap_SPI_SSEL[] = {
    {P0_2 , SPI_0, 0x01},
    {P1_19, SPI_1, 0x02},
    {NC   , NC   , 0}
};

/************PWM***************/
const PinMap PinMap_PWM[] = {
    /* CT16B0 */
    {P0_8 , PWM_1, 2},                      /* MR0 */
    {P0_9 , PWM_2, 2},                      /* MR1 */
    {P0_10, PWM_3, 3},                      /* MR2 */
    {P1_15, PWM_3, 2},                      /* MR2 */ // Same channel as P0_10

    /* CT16B1 */
    {P0_21, PWM_4, 1},                      /* MR0 */
    {P0_22, PWM_5, 2},                      /* MR1 */

    /* CT32B0 */
    {P0_18, PWM_6, 2},                      /* MR0 */
    {P0_19, PWM_7, 2},                      /* MR1 */
    {P0_1 , PWM_8, 2},                      /* MR2 */
	{P0_11, PWM_9, 3},                      /* MR3 */

    /* CT32B1 */
    {P0_13, PWM_10, 3},                     /* MR0 */
    {P0_14, PWM_11, 3},                     /* MR1 */
    {P0_15, PWM_12, 3},                     /* MR2 */
	{P0_16, PWM_13, 2},                     /* MR3 */

    {NC, NC, 0}
};
