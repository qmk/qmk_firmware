// Copyright 2023 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

///////////////////////////////////////////////////////////////////////////////
// BEGIN: STM32 EFL Wear-leveling ECC fault handling
//
// Some STM32s have ECC checks for all flash memory access. Whenever there's an
// ECC failure, the MCU raises the NMI interrupt. Whenever we receive such an
// interrupt whilst reading the wear-leveling EEPROM area, we gracefully cater
// for it, signalling the wear-leveling code that a failure has occurred.
///////////////////////////////////////////////////////////////////////////////

#include <ch.h>
#include <chcore.h>

#ifdef WEAR_LEVELING_EMBEDDED_FLASH
#    ifdef QMK_MCU_SERIES_STM32L4XX
#        define ECC_ERRORS_TRIGGER_NMI_INTERRUPT
#        define ECC_CHECK_REGISTER FLASH->ECCR
#        define ECC_CHECK_FLAG FLASH_ECCR_ECCD
#    endif // QMK_MCU_SERIES_STM32L4XX
#endif     // WEAR_LEVELING_EMBEDDED_FLASH

#ifdef ECC_ERRORS_TRIGGER_NMI_INTERRUPT

extern bool backing_store_allow_ecc_errors(void);
extern void backing_store_signal_ecc_error(void);

void NMI_Handler(void) {
    if ((ECC_CHECK_REGISTER) & (ECC_CHECK_FLAG)) {
        if (backing_store_allow_ecc_errors()) {
            (ECC_CHECK_REGISTER) = (ECC_CHECK_FLAG);
            backing_store_signal_ecc_error();
            return;
        }
    }

    chSysHalt("NMI");
}

#endif // ECC_ERRORS_TRIGGER_NMI_INTERRUPT

///////////////////////////////////////////////////////////////////////////////
// END: STM32 EFL Wear-leveling ECC fault handling
///////////////////////////////////////////////////////////////////////////////
