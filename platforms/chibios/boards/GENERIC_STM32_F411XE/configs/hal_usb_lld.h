// Copyright 2026 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include_next <hal_usb_lld.h>

// Workaround for A9 on STM32F4 not working. This is a temporary workaround until upstream is fixed.
#if defined(BOARD_OTG_NOVBUSSENS)
#    undef usb_lld_connect_bus
#    define usb_lld_connect_bus(usbp) ((usbp)->otg->GCCFG |= GCCFG_NOVBUSSENS)

#    undef usb_lld_disconnect_bus
#    define usb_lld_disconnect_bus(usbp) ((usbp)->otg->GCCFG &= ~GCCFG_NOVBUSSENS)
#endif
