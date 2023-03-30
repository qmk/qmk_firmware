/*************************************************************************//**
 * @file     system_RP2040.c
 * @brief    CMSIS-Core(M) Device Peripheral Access Layer Header File for
 *           Device RP2040
 * @version  V1.0.0
 * @date     5. May 2021
 *****************************************************************************/
/*
 * Copyright (c) 2009-2021 Arm Limited. All rights reserved.
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include "RP2040.h"
#include "hardware/clocks.h"

/*---------------------------------------------------------------------------
  System Core Clock Variable
 *---------------------------------------------------------------------------*/
uint32_t SystemCoreClock; /* System Clock Frequency (Core Clock)*/

/*---------------------------------------------------------------------------
  System Core Clock function
 *---------------------------------------------------------------------------*/
void SystemCoreClockUpdate (void)
{
    SystemCoreClock = clock_get_hz(clk_sys);
}

/*---------------------------------------------------------------------------
  System initialization function
 *---------------------------------------------------------------------------*/
void __attribute__((constructor)) SystemInit (void)
{
    SystemCoreClockUpdate();
}