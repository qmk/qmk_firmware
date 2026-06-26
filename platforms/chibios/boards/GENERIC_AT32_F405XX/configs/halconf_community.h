/*
    ChibiOS - Copyright (C) 2014 Uladzimir Pylinsky aka barthess
    ChibiOS - Copyright (C) 2023..2025 HorrorTroll
    ChibiOS - Copyright (C) 2023..2025 Zhaqian

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

#ifndef HALCONF_COMMUNITY_H
#define HALCONF_COMMUNITY_H

#if !defined(HAL_USE_COMMUNITY) || defined(__DOXYGEN__)
#define HAL_USE_COMMUNITY           TRUE
#endif

#if !defined(HAL_USE_FSMC) || defined(__DOXYGEN__)
#define HAL_USE_FSMC                FALSE
#endif

#if !defined(HAL_USE_NAND) || defined(__DOXYGEN__)
#define HAL_USE_NAND                FALSE
#endif

#if !defined(HAL_USE_ONEWIRE) || defined(__DOXYGEN__)
#define HAL_USE_ONEWIRE             FALSE
#endif

#if !defined(HAL_USE_EICU) || defined(__DOXYGEN__)
#define HAL_USE_EICU                FALSE
#endif

#if !defined(HAL_USE_CRC) || defined(__DOXYGEN__)
#define HAL_USE_CRC                 FALSE
#endif

#if !defined(HAL_USE_RNG) || defined(__DOXYGEN__)
#define HAL_USE_RNG                 FALSE
#endif

#if !defined(HAL_USE_EEPROM) || defined(__DOXYGEN__)
#define HAL_USE_EEPROM              FALSE
#endif

#if !defined(HAL_USE_TIMCAP) || defined(__DOXYGEN__)
#define HAL_USE_TIMCAP              FALSE
#endif

#if !defined(HAL_USE_COMP) || defined(__DOXYGEN__)
#define HAL_USE_COMP                FALSE
#endif

#if !defined(HAL_USE_OPAMP) || defined(__DOXYGEN__)
#define HAL_USE_OPAMP               FALSE
#endif

#if !defined(HAL_USE_QEI) || defined(__DOXYGEN__)
#define HAL_USE_QEI                 FALSE
#endif

#if !defined(HAL_USE_USBH) || defined(__DOXYGEN__)
#define HAL_USE_USBH                FALSE
#endif

#if !defined(HAL_USE_USB_MSD) || defined(__DOXYGEN__)
#define HAL_USE_USB_MSD             FALSE
#endif

#define NAND_USE_MUTUAL_EXCLUSION   TRUE
#define ONEWIRE_USE_STRONG_PULLUP   FALSE
#define ONEWIRE_USE_SEARCH_ROM      TRUE

#if !defined(QEI_USE_OVERFLOW_DISCARD) || defined(__DOXYGEN__)
#define QEI_USE_OVERFLOW_DISCARD    FALSE
#endif

#if !defined(QEI_USE_OVERFLOW_MINMAX) || defined(__DOXYGEN__)
#define QEI_USE_OVERFLOW_MINMAX     FALSE
#endif

#define EEPROM_USE_EE24XX           FALSE
#define EEPROM_USE_EE25XX           FALSE

#endif /* HALCONF_COMMUNITY_H */
