// Copyright 2023 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

///////////////////////////////////////////////////////////////////////////////
// BEGIN: STM32L4xx Wear-leveling ECC fault handling
//
// STM32L4xx have ECC checks for all flash memory access. Whenever there's an
// ECC failure, the MCU raises the NMI interrupt. Whenever we receive such an
// interrupt whilst reading the wear-leveling EEPROM area, we gracefully cater
// for it, signalling the wear-leveling code that a failure has occurred.
///////////////////////////////////////////////////////////////////////////////

#include <ch.h>
#include <chcore.h>

#if defined(QMK_MCU_SERIES_STM32L4XX) && defined(WEAR_LEVELING_EMBEDDED_FLASH)

extern bool backing_store_allow_ecc_errors(void);
extern void backing_store_signal_ecc_error(void);

void NMI_Handler(void) {
#    ifdef FLASH_ECCR_ECCD
    if (FLASH->ECCR & FLASH_ECCR_ECCD) {
        if (backing_store_allow_ecc_errors()) {
            FLASH->ECCR = FLASH_ECCR_ECCD;
            backing_store_signal_ecc_error();
            return;
        }
    }
#    endif // FLASH_ECCR_ECCD

    chSysHalt("NMI");
}

#endif // defined(QMK_MCU_SERIES_STM32L4XX) && defined(WEAR_LEVELING_DRIVER_EMBEDDED_FLASH)

///////////////////////////////////////////////////////////////////////////////
// END: STM32L4xx Wear-leveling ECC fault handling
///////////////////////////////////////////////////////////////////////////////
