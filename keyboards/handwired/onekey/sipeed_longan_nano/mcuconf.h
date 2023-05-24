/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio
    ChibiOS - Copyright (C) 2021 Stefan Kerkmann

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

#pragma once

#include_next <mcuconf.h>

#undef GD32_ADC_USE_ADC0
#define GD32_ADC_USE_ADC0 TRUE

#undef GD32_I2C_USE_I2C0
#define GD32_I2C_USE_I2C0 TRUE

#undef GD32_PWM_USE_TIM4
#define GD32_PWM_USE_TIM4 TRUE
