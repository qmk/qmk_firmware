/*
    Copyright (C) 2021 essemi

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

#ifndef MCUCONF_H
#define MCUCONF_H

#define ES32_FS026_MCUCONF

/*
 * HAL driver system settings.
 */
//Temporarily not supported.
//System_clock = 72M
//Peripheral_clock1(TIMER,SPI,I2C...) = 72M
//Peripheral_clock2(USB) = 48M

/*
 * PWM driver system settings.
 */
#define ES32_PWM_USE_AD16C4T1 FALSE
#define ES32_PWM_USE_GP32C4T1 FALSE
#define ES32_PWM_USE_GP16C4T1 FALSE
#define ES32_PWM_USE_GP16C4T2 TRUE
#define ES32_PWM_USE_GP16C4T3 FALSE
#define ES32_PWM_USE_GP16C2T1 FALSE
#define ES32_PWM_USE_GP16C2T2 FALSE
#define ES32_PWM_USE_GP16C2T3 FALSE
#define ES32_PWM_USE_GP16C2T4 FALSE
#define ES32_PWM_AD16C4T1_IRQ_PRIORITY 7
#define ES32_PWM_GP32C4T1_IRQ_PRIORITY 7
#define ES32_PWM_GP16C4T1_IRQ_PRIORITY 7
#define ES32_PWM_GP16C4T2_IRQ_PRIORITY 7
#define ES32_PWM_GP16C4T3_IRQ_PRIORITY 7
#define ES32_PWM_GP16C2T1_IRQ_PRIORITY 7
#define ES32_PWM_GP16C2T2_IRQ_PRIORITY 7
#define ES32_PWM_GP16C2T3_IRQ_PRIORITY 7
#define ES32_PWM_GP16C2T4_IRQ_PRIORITY 7

#endif /* MCUCONF_H */
