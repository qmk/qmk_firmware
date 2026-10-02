# Copyright 2026 HMC Studio
# SPDX-License-Identifier: GPL-2.0-or-later

# Reserve the final two 1 kB flash pages for the embedded-flash wear-leveling
# backing store. The application is placed after the 16 kB uf2boot bootloader.
MCU_LDSCRIPT = STM32F103xB_uf2boot_wl
