/*
Copyright 2023 NuPhy & jincao1

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#define EXTI_PORT_R0             EXTI_PortSourceGPIOC
#define EXTI_PORT_R1             EXTI_PortSourceGPIOC
#define EXTI_PORT_R2             EXTI_PortSourceGPIOA
#define EXTI_PORT_R3             EXTI_PortSourceGPIOA
#define EXTI_PORT_R4             EXTI_PortSourceGPIOA
#define EXTI_PORT_R5             EXTI_PortSourceGPIOA

#define EXTI_PIN_R0              14  // C14
#define EXTI_PIN_R1              15  // C15
#define EXTI_PIN_R2              0   // A0
#define EXTI_PIN_R3              1   // A1
#define EXTI_PIN_R4              2   // A2
#define EXTI_PIN_R5              3   // A3

#define EXTI_PORT_C0             EXTI_PortSourceGPIOA  // A4
#define EXTI_PORT_C1             EXTI_PortSourceGPIOA  // A5
#define EXTI_PORT_C2             EXTI_PortSourceGPIOA  // A6
#define EXTI_PORT_C3             EXTI_PortSourceGPIOB  // B9
#define EXTI_PORT_C4             EXTI_PortSourceGPIOB  // B0
#define EXTI_PORT_C5             EXTI_PortSourceGPIOB  // B1
#define EXTI_PORT_C6             EXTI_PortSourceGPIOB  // B10
#define EXTI_PORT_C7             EXTI_PortSourceGPIOB  // B11
#define EXTI_PORT_C8             EXTI_PortSourceGPIOB  // B12
#define EXTI_PORT_C9             EXTI_PortSourceGPIOB  // B13
#define EXTI_PORT_C10            EXTI_PortSourceGPIOB  // B14
#define EXTI_PORT_C11            EXTI_PortSourceGPIOB  // B15
#define EXTI_PORT_C12            EXTI_PortSourceGPIOA  // A8
#define EXTI_PORT_C13            EXTI_PortSourceGPIOA  // A9
#define EXTI_PORT_C14            EXTI_PortSourceGPIOA  // A10
#define EXTI_PORT_C15            EXTI_PortSourceGPIOA  // A15
#define EXTI_PORT_C16            EXTI_PortSourceGPIOB  // B3

#define EXTI_PIN_C0              4   // A4
#define EXTI_PIN_C1              5   // A5
#define EXTI_PIN_C2              6   // A6
#define EXTI_PIN_C3              9   // B9
#define EXTI_PIN_C4              0   // B0
#define EXTI_PIN_C5              1   // B1
#define EXTI_PIN_C6              10  // B10
#define EXTI_PIN_C7              11  // B11
#define EXTI_PIN_C8              12  // B12
#define EXTI_PIN_C9              13  // B13
#define EXTI_PIN_C10             14  // B14
#define EXTI_PIN_C11             15  // B15
#define EXTI_PIN_C12             8   // A8
#define EXTI_PIN_C13             9   // A9
#define EXTI_PIN_C14             10  // A10
#define EXTI_PIN_C15             15  // A15
#define EXTI_PIN_C16             3   // B3

void enter_light_sleep(void);
void exit_light_sleep(void);
void enter_deep_sleep(void);
void exit_deep_sleep(void);

void pwr_rgb_led_off(void);
void pwr_rgb_led_on(void);
void pwr_side_led_off(void);
void pwr_side_led_on(void);

bool is_rgb_led_on(void);
bool is_side_led_on(void);

void led_pwr_sleep_handle(void);
void led_pwr_wake_handle(void);
