// Copyright 2026 Mauro DiBenedetto
// Copyright 2026 Antonio SJ Musumeci (@trapexit)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

// Matrix column 10 reads the six DIP switches (rows 0-5) instead of keys.
#define PROFILE_SWITCH_COL 10

// TrackPoint sensitivity at power-on, an index into the nine stock levels (0-8).
#ifndef SHURA_TP_DEFAULT_LEVEL
#    define SHURA_TP_DEFAULT_LEVEL 0
#endif
#if (SHURA_TP_DEFAULT_LEVEL < 0) || (SHURA_TP_DEFAULT_LEVEL > 8)
#    error "SHURA_TP_DEFAULT_LEVEL must be 0 through 8"
#endif

// Raw HID command that restarts into the TEX bootloader. VIA does not use it.
#define SHURA_RAW_IAP 0xF1

// The Cortex-M0+ has no cycle counter; time wait_us() with a hardware timer.
#define WAIT_US_TIMER GPTD_BFTM0

// U3 SPI NOR flash (SPI1, AF5) backing the wear-leveled EEPROM; see wear_leveling_shura.c.
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN C2
#define SPI_MOSI_PIN C3
#define SPI_MISO_PIN B6
#define SPI_SCK_PAL_MODE 5
#define SPI_MOSI_PAL_MODE 5
#define SPI_MISO_PAL_MODE 5
// MISO needs the HT32 input buffer enabled while the pin is muxed to SPI.
#define SPI_MISO_FLAGS (PAL_MODE_ALTERNATE(SPI_MISO_PAL_MODE) | PAL_HT32_MODE_INE)
#define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN B7
#define BACKING_STORE_WRITE_SIZE 8

// The PS/2 driver converts Y to HID coordinates. Rotate both axes for the mounted stick.
#define POINTING_DEVICE_ROTATION_180

// Middle and Fn releases rely on QMK's press-time source-layer cache.
#if defined(STRICT_LAYER_RELEASE) || defined(SEMI_STRICT_LAYER_RELEASE)
#    error "The Shura requires press-time layer releases"
#endif
