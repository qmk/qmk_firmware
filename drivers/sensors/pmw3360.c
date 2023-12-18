// Copyright 2022 Stefan Kerkmann (KarlK90)
// Copyright 2022 Ulrich Spörlein (@uqs)
// Copyright 2021 Alabastard (@Alabastard-64)
// Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// Copyright 2019 Sunjun Kim
// Copyright 2020 Ploopy Corporation
// SPDX-License-Identifier: GPL-2.0-or-later

#include "pmw33xx_common.h"
#include "progmem.h"

uint16_t pmw33xx_get_cpi(uint8_t sensor) {
    if (sensor >= pmw33xx_number_of_sensors) {
        return 0;
    }

    uint8_t cpival = pmw33xx_read(sensor, REG_Config1);
    return (uint16_t)((cpival + 1) & 0xFF) * PMW33XX_CPI_STEP;
}

void pmw33xx_set_cpi(uint8_t sensor, uint16_t cpi) {
    if (sensor >= pmw33xx_number_of_sensors) {
        return;
    }

    uint8_t cpival = CONSTRAIN((cpi / PMW33XX_CPI_STEP), (PMW33XX_CPI_MIN / PMW33XX_CPI_STEP), (PMW33XX_CPI_MAX / PMW33XX_CPI_STEP)) - 1U;
    pmw33xx_write(sensor, REG_Config1, cpival);
}

// PID, Inverse PID, SROM version
const uint8_t pmw33xx_firmware_signature[3] PROGMEM = {0x42, 0xBD, 0x04};

// Firmware Blob for PMW3360
// clang-format off
const uint8_t pmw33xx_firmware_data[PMW33XX_FIRMWARE_LENGTH] PROGMEM = {
    0x01, 0x04, 0x8E, 0x96, 0x6E, 0x77, 0x3E, 0xFE, 0x7E, 0x5F, 0x1D, 0xB8, 0xF2, 0x66, 0x4E, 0xFF,
    0x5D, 0x19, 0xB0, 0xC2, 0x04, 0x69, 0x54, 0x2A, 0xD6, 0x2E, 0xBF, 0xDD, 0x19, 0xB0, 0xC3, 0xE5,
    0x29, 0xB1, 0xE0, 0x23, 0xA5, 0xA9, 0xB1, 0xC1, 0x00, 0x82, 0x67, 0x4C, 0x1A, 0x97, 0x8D, 0x79,
    0x51, 0x20, 0xC7, 0x06, 0x8E, 0x7C, 0x7C, 0x7A, 0x76, 0x4F, 0xFD, 0x59, 0x30, 0xE2, 0x46, 0x0E,
    0x9E, 0xBE, 0xDF, 0x1D, 0x99, 0x91, 0xA0, 0xA5, 0xA1, 0xA9, 0xD0, 0x22, 0xC6, 0xEF, 0x5C, 0x1B,
    0x95, 0x89, 0x90, 0xA2, 0xA7, 0xCC, 0xFB, 0x55, 0x28, 0xB3, 0xE4, 0x4A, 0xF7, 0x6C, 0x3B, 0xF4,
    0x6A, 0x56, 0x2E, 0xDE, 0x1F, 0x9D, 0xB8, 0xD3, 0x05, 0x88, 0x92, 0xA6, 0xCE, 0x1E, 0xBE, 0xDF,
    0x1D, 0x99, 0xB0, 0xE2, 0x46, 0xEF, 0x5C, 0x07, 0x11, 0x5D, 0x98, 0x0B, 0x9D, 0x94, 0x97, 0xEE,
    0x4E, 0x45, 0x33, 0x6B, 0x44, 0xC7, 0x29, 0x56, 0x27, 0x30, 0xC6, 0xA7, 0xD5, 0xF2, 0x56, 0xDF,
    0xB4, 0x38, 0x62, 0xCB, 0xA0, 0xB6, 0xE3, 0x0F, 0x84, 0x06, 0x24, 0x05, 0x65, 0x6F, 0x76, 0x89,
    0xB5, 0x77, 0x41, 0x27, 0x82, 0x66, 0x65, 0x82, 0xCC, 0xD5, 0xE6, 0x20, 0xD5, 0x27, 0x17, 0xC5,
    0xF8, 0x03, 0x23, 0x7C, 0x5F, 0x64, 0xA5, 0x1D, 0xC1, 0xD6, 0x36, 0xCB, 0x4C, 0xD4, 0xDB, 0x66,
    0xD7, 0x8B, 0xB1, 0x99, 0x7E, 0x6F, 0x4C, 0x36, 0x40, 0x06, 0xD6, 0xEB, 0xD7, 0xA2, 0xE4, 0xF4,
    0x95, 0x51, 0x5A, 0x54, 0x96, 0xD5, 0x53, 0x44, 0xD7, 0x8C, 0xE0, 0xB9, 0x40, 0x68, 0xD2, 0x18,
    0xE9, 0xDD, 0x9A, 0x23, 0x92, 0x48, 0xEE, 0x7F, 0x43, 0xAF, 0xEA, 0x77, 0x38, 0x84, 0x8C, 0x0A,
    0x72, 0xAF, 0x69, 0xF8, 0xDD, 0xF1, 0x24, 0x83, 0xA3, 0xF8, 0x4A, 0xBF, 0xF5, 0x94, 0x13, 0xDB,
    0xBB, 0xD8, 0xB4, 0xB3, 0xA0, 0xFB, 0x45, 0x50, 0x60, 0x30, 0x59, 0x12, 0x31, 0x71, 0xA2, 0xD3,
    0x13, 0xE7, 0xFA, 0xE7, 0xCE, 0x0F, 0x63, 0x15, 0x0B, 0x6B, 0x94, 0xBB, 0x37, 0x83, 0x26, 0x05,
    0x9D, 0xFB, 0x46, 0x92, 0xFC, 0x0A, 0x15, 0xD1, 0x0D, 0x73, 0x92, 0xD6, 0x8C, 0x1B, 0x8C, 0xB8,
    0x55, 0x8A, 0xCE, 0xBD, 0xFE, 0x8E, 0xFC, 0xED, 0x09, 0x12, 0x83, 0x91, 0x82, 0x51, 0x31, 0x23,
    0xFB, 0xB4, 0x0C, 0x76, 0xAD, 0x7C, 0xD9, 0xB4, 0x4B, 0xB2, 0x67, 0x14, 0x09, 0x9C, 0x7F, 0x0C,
    0x18, 0xBA, 0x3B, 0xD6, 0x8E, 0x14, 0x2A, 0xE4, 0x1B, 0x52, 0x9F, 0x2B, 0x7D, 0xE1, 0xFB, 0x6A,
    0x33, 0x02, 0xFA, 0xAC, 0x5A, 0xF2, 0x3E, 0x88, 0x7E, 0xAE, 0xD1, 0xF3, 0x78, 0xE8, 0x05, 0xD1,
    0xE3, 0xDC, 0x21, 0xF6, 0xE1, 0x9A, 0xBD, 0x17, 0x0E, 0xD9, 0x46, 0x9B, 0x88, 0x03, 0xEA, 0xF6,
    0x66, 0xBE, 0x0E, 0x1B, 0x50, 0x49, 0x96, 0x40, 0x97, 0xF1, 0xF1, 0xE4, 0x80, 0xA6, 0x6E, 0xE8,
    0x77, 0x34, 0xBF, 0x29, 0x40, 0x44, 0xC2, 0xFF, 0x4E, 0x98, 0xD3, 0x9C, 0xA3, 0x32, 0x2B, 0x76,
    0x51, 0x04, 0x09, 0xE7, 0xA9, 0xD1, 0xA6, 0x32, 0xB1, 0x23, 0x53, 0xE2, 0x47, 0xAB, 0xD6, 0xF5,
    0x69, 0x5C, 0x3E, 0x5F, 0xFA, 0xAE, 0x45, 0x20, 0xE5, 0xD2, 0x44, 0xFF, 0x39, 0x32, 0x6D, 0xFD,
    0x27, 0x57, 0x5C, 0xFD, 0xF0, 0xDE, 0xC1, 0xB5, 0x99, 0xE5, 0xF5, 0x1C, 0x77, 0x01, 0x75, 0xC5,
    0x6D, 0x58, 0x92, 0xF2, 0xB2, 0x47, 0x00, 0x01, 0x26, 0x96, 0x7A, 0x30, 0xFF, 0xB7, 0xF0, 0xEF,
    0x77, 0xC1, 0x8A, 0x5D, 0xDC, 0xC0, 0xD1, 0x29, 0x30, 0x1E, 0x77, 0x38, 0x7A, 0x94, 0xF1, 0xB8,
    0x7A, 0x7E, 0xEF, 0xA4, 0xD1, 0xAC, 0x31, 0x4A, 0xF2, 0x5D, 0x64, 0x3D, 0xB2, 0xE2, 0xF0, 0x08,
    0x99, 0xFC, 0x70, 0xEE, 0x24, 0xA7, 0x7E, 0xEE, 0x1E, 0x20, 0x69, 0x7D, 0x44, 0xBF, 0x87, 0x42,
    0xDF, 0x88, 0x3B, 0x0C, 0xDA, 0x42, 0xC9, 0x04, 0xF9, 0x45, 0x50, 0xFC, 0x83, 0x8F, 0x11, 0x6A,
    0x72, 0xBC, 0x99, 0x95, 0xF0, 0xAC, 0x3D, 0xA7, 0x3B, 0xCD, 0x1C, 0xE2, 0x88, 0x79, 0x37, 0x11,
    0x5F, 0x39, 0x89, 0x95, 0x0A, 0x16, 0x84, 0x7A, 0xF6, 0x8A, 0xA4, 0x28, 0xE4, 0xED, 0x83, 0x80,
    0x3B, 0xB1, 0x23, 0xA5, 0x03, 0x10, 0xF4, 0x66, 0xEA, 0xBB, 0x0C, 0x0F, 0xC5, 0xEC, 0x6C, 0x69,
    0xC5, 0xD3, 0x24, 0xAB, 0xD4, 0x2A, 0xB7, 0x99, 0x88, 0x76, 0x08, 0xA0, 0xA8, 0x95, 0x7C, 0xD8,
    0x38, 0x6D, 0xCD, 0x59, 0x02, 0x51, 0x4B, 0xF1, 0xB5, 0x2B, 0x50, 0xE3, 0xB6, 0xBD, 0xD0, 0x72,
    0xCF, 0x9E, 0xFD, 0x6E, 0xBB, 0x44, 0xC8, 0x24, 0x8A, 0x77, 0x18, 0x8A, 0x13, 0x06, 0xEF, 0x97,
    0x7D, 0xFA, 0x81, 0xF0, 0x31, 0xE6, 0xFA, 0x77, 0xED, 0x31, 0x06, 0x31, 0x5B, 0x54, 0x8A, 0x9F,
    0x30, 0x68, 0xDB, 0xE2, 0x40, 0xF8, 0x4E, 0x73, 0xFA, 0xAB, 0x74, 0x8B, 0x10, 0x58, 0x13, 0xDC,
    0xD2, 0xE6, 0x78, 0xD1, 0x32, 0x2E, 0x8A, 0x9F, 0x2C, 0x58, 0x06, 0x48, 0x27, 0xC5, 0xA9, 0x5E,
    0x81, 0x47, 0x89, 0x46, 0x21, 0x91, 0x03, 0x70, 0xA4, 0x3E, 0x88, 0x9C, 0xDA, 0x33, 0x0A, 0xCE,
    0xBC, 0x8B, 0x8E, 0xCF, 0x9F, 0xD3, 0x71, 0x80, 0x43, 0xCF, 0x6B, 0xA9, 0x51, 0x83, 0x76, 0x30,
    0x82, 0xC5, 0x6A, 0x85, 0x39, 0x11, 0x50, 0x1A, 0x82, 0xDC, 0x1E, 0x1C, 0xD5, 0x7D, 0xA9, 0x71,
    0x99, 0x33, 0x47, 0x19, 0x97, 0xB3, 0x5A, 0xB1, 0xDF, 0xED, 0xA4, 0xF2, 0xE6, 0x26, 0x84, 0xA2,
    0x28, 0x9A, 0x9E, 0xDF, 0xA6, 0x6A, 0xF4, 0xD6, 0xFC, 0x2E, 0x5B, 0x9D, 0x1A, 0x2A, 0x27, 0x68,
    0xFB, 0xC1, 0x83, 0x21, 0x4B, 0x90, 0xE0, 0x36, 0xDD, 0x5B, 0x31, 0x42, 0x55, 0xA0, 0x13, 0xF7,
    0xD0, 0x89, 0x53, 0x71, 0x99, 0x57, 0x09, 0x29, 0xC5, 0xF3, 0x21, 0xF8, 0x37, 0x2F, 0x40, 0xF3,
    0xD4, 0xAF, 0x16, 0x08, 0x36, 0x02, 0xFC, 0x77, 0xC5, 0x8B, 0x04, 0x90, 0x56, 0xB9, 0xC9, 0x67,
    0x9A, 0x99, 0xE8, 0x00, 0xD3, 0x86, 0xFF, 0x97, 0x2D, 0x08, 0xE9, 0xB7, 0xB3, 0x91, 0xBC, 0xDF,
    0x45, 0xC6, 0xED, 0x0F, 0x8C, 0x4C, 0x1E, 0xE6, 0x5B, 0x6E, 0x38, 0x30, 0xE4, 0xAA, 0xE3, 0x95,
    0xDE, 0xB9, 0xE4, 0x9A, 0xF5, 0xB2, 0x55, 0x9A, 0x87, 0x9B, 0xF6, 0x6A, 0xB2, 0xF2, 0x77, 0x9A,
    0x31, 0xF4, 0x7A, 0x31, 0xD1, 0x1D, 0x04, 0xC0, 0x7C, 0x32, 0xA2, 0x9E, 0x9A, 0xF5, 0x62, 0xF8,
    0x27, 0x8D, 0xBF, 0x51, 0xFF, 0xD3, 0xDF, 0x64, 0x37, 0x3F, 0x2A, 0x6F, 0x76, 0x3A, 0x7D, 0x77,
    0x06, 0x9E, 0x77, 0x7F, 0x5E, 0xEB, 0x32, 0x51, 0xF9, 0x16, 0x66, 0x9A, 0x09, 0xF3, 0xB0, 0x08,
    0xA4, 0x70, 0x96, 0x46, 0x30, 0xFF, 0xDA, 0x4F, 0xE9, 0x1B, 0xED, 0x8D, 0xF8, 0x74, 0x1F, 0x31,
    0x92, 0xB3, 0x73, 0x17, 0x36, 0xDB, 0x91, 0x30, 0xD6, 0x88, 0x55, 0x6B, 0x34, 0x77, 0x87, 0x7A,
    0xE7, 0xEE, 0x06, 0xC6, 0x1C, 0x8C, 0x19, 0x0C, 0x48, 0x46, 0x23, 0x5E, 0x9C, 0x07, 0x5C, 0xBF,
    0xB4, 0x7E, 0xD6, 0x4F, 0x74, 0x9C, 0xE2, 0xC5, 0x50, 0x8B, 0xC5, 0x8B, 0x15, 0x90, 0x60, 0x62,
    0x57, 0x29, 0xD0, 0x13, 0x43, 0xA1, 0x80, 0x88, 0x91, 0x00, 0x44, 0xC7, 0x4D, 0x19, 0x86, 0xCC,
    0x2F, 0x2A, 0x75, 0x5A, 0xFC, 0xEB, 0x97, 0x2A, 0x70, 0xE3, 0x78, 0xD8, 0x91, 0xB0, 0x4F, 0x99,
    0x07, 0xA3, 0x95, 0xEA, 0x24, 0x21, 0xD5, 0xDE, 0x51, 0x20, 0x93, 0x27, 0x0A, 0x30, 0x73, 0xA8,
    0xFF, 0x8A, 0x97, 0xE9, 0xA7, 0x6A, 0x8E, 0x0D, 0xE8, 0xF0, 0xDF, 0xEC, 0xEA, 0xB4, 0x6C, 0x1D,
    0x39, 0x2A, 0x62, 0x2D, 0x3D, 0x5A, 0x8B, 0x65, 0xF8, 0x90, 0x05, 0x2E, 0x7E, 0x91, 0x2C, 0x78,
    0xEF, 0x8E, 0x7A, 0xC1, 0x2F, 0xAC, 0x78, 0xEE, 0xAF, 0x28, 0x45, 0x06, 0x4C, 0x26, 0xAF, 0x3B,
    0xA2, 0xDB, 0xA3, 0x93, 0x06, 0xB5, 0x3C, 0xA5, 0xD8, 0xEE, 0x8F, 0xAF, 0x25, 0xCC, 0x3F, 0x85,
    0x68, 0x48, 0xA9, 0x62, 0xCC, 0x97, 0x8F, 0x7F, 0x2A, 0xEA, 0xE0, 0x15, 0x0A, 0xAD, 0x62, 0x07,
    0xBD, 0x45, 0xF8, 0x41, 0xD8, 0x36, 0xCB, 0x4C, 0xDB, 0x6E, 0xE6, 0x3A, 0xE7, 0xDA, 0x15, 0xE9,
    0x29, 0x1E, 0x12, 0x10, 0xA0, 0x14, 0x2C, 0x0E, 0x3D, 0xF4, 0xBF, 0x39, 0x41, 0x92, 0x75, 0x0B,
    0x25, 0x7B, 0xA3, 0xCE, 0x39, 0x9C, 0x15, 0x64, 0xC8, 0xFA, 0x3D, 0xEF, 0x73, 0x27, 0xFE, 0x26,
    0x2E, 0xCE, 0xDA, 0x6E, 0xFD, 0x71, 0x8E, 0xDD, 0xFE, 0x76, 0xEE, 0xDC, 0x12, 0x5C, 0x02, 0xC5,
    0x3A, 0x4E, 0x4E, 0x4F, 0xBF, 0xCA, 0x40, 0x15, 0xC7, 0x6E, 0x8D, 0x41, 0xF1, 0x10, 0xE0, 0x4F,
    0x7E, 0x97, 0x7F, 0x1C, 0xAE, 0x47, 0x8E, 0x6B, 0xB1, 0x25, 0x31, 0xB0, 0x73, 0xC7, 0x1B, 0x97,
    0x79, 0xF9, 0x80, 0xD3, 0x66, 0x22, 0x30, 0x07, 0x74, 0x1E, 0xE4, 0xD0, 0x80, 0x21, 0xD6, 0xEE,
    0x6B, 0x6C, 0x4F, 0xBF, 0xF5, 0xB7, 0xD9, 0x09, 0x87, 0x2F, 0xA9, 0x14, 0xBE, 0x27, 0xD9, 0x72,
    0x50, 0x01, 0xD4, 0x13, 0x73, 0xA6, 0xA7, 0x51, 0x02, 0x75, 0x25, 0xE1, 0xB3, 0x45, 0x34, 0x7D,
    0xA8, 0x8E, 0xEB, 0xF3, 0x16, 0x49, 0xCB, 0x4F, 0x8C, 0xA1, 0xB9, 0x36, 0x85, 0x39, 0x75, 0x5D,
    0x08, 0x00, 0xAE, 0xEB, 0xF6, 0xEA, 0xD7, 0x13, 0x3A, 0x21, 0x5A, 0x5F, 0x30, 0x84, 0x52, 0x26,
    0x95, 0xC9, 0x14, 0xF2, 0x57, 0x55, 0x6B, 0xB1, 0x10, 0xC2, 0xE1, 0xBD, 0x3B, 0x51, 0xC0, 0xB7,
    0x55, 0x4C, 0x71, 0x12, 0x26, 0xC7, 0x0D, 0xF9, 0x51, 0xA4, 0x38, 0x02, 0x05, 0x7F, 0xB8, 0xF1,
    0x72, 0x4B, 0xBF, 0x71, 0x89, 0x14, 0xF3, 0x77, 0x38, 0xD9, 0x71, 0x24, 0xF3, 0x00, 0x11, 0xA1,
    0xD8, 0xD4, 0x69, 0x27, 0x08, 0x37, 0x35, 0xC9, 0x11, 0x9D, 0x90, 0x1C, 0x0E, 0xE7, 0x1C, 0xFF,
    0x2D, 0x1E, 0xE8, 0x92, 0xE1, 0x18, 0x10, 0x95, 0x7C, 0xE0, 0x80, 0xF4, 0x96, 0x43, 0x21, 0xF9,
    0x75, 0x21, 0x64, 0x38, 0xDD, 0x9F, 0x1E, 0x95, 0x16, 0xDA, 0x56, 0x1D, 0x4F, 0x9A, 0x53, 0xB2,
    0xE2, 0xE4, 0x18, 0xCB, 0x6B, 0x1A, 0x65, 0xEB, 0x56, 0xC6, 0x3B, 0xE5, 0xFE, 0xD8, 0x26, 0x3F,
    0x3A, 0x84, 0x59, 0x72, 0x66, 0xA2, 0xF3, 0x75, 0xFF, 0xFB, 0x60, 0xB3, 0x22, 0xAD, 0x3F, 0x2D,
    0x6B, 0xF9, 0xEB, 0xEA, 0x05, 0x7C, 0xD8, 0x8F, 0x6D, 0x2C, 0x98, 0x9E, 0x2B, 0x93, 0xF1, 0x5E,
    0x46, 0xF0, 0x87, 0x49, 0x29, 0x73, 0x68, 0xD7, 0x7F, 0xF9, 0xF0, 0xE5, 0x7D, 0xDB, 0x1D, 0x75,
    0x19, 0xF3, 0xC4, 0x58, 0x9B, 0x17, 0x88, 0xA8, 0x92, 0xE0, 0xBE, 0xBD, 0x8B, 0x1D, 0x8D, 0x9F,
    0x56, 0x76, 0xAD, 0xAF, 0x29, 0xE2, 0xD9, 0xD5, 0x52, 0xF6, 0xB5, 0x56, 0x35, 0x57, 0x3A, 0xC8,
    0xE1, 0x56, 0x43, 0x19, 0x94, 0xD3, 0x04, 0x9B, 0x6D, 0x35, 0xD8, 0x0B, 0x5F, 0x4D, 0x19, 0x8E,
    0xEC, 0xFA, 0x64, 0x91, 0x0A, 0x72, 0x20, 0x2B, 0xBC, 0x1A, 0x4A, 0xFE, 0x8B, 0xFD, 0xBB, 0xED,
    0x1B, 0x23, 0xEA, 0xAD, 0x72, 0x82, 0xA1, 0x29, 0x99, 0x71, 0xBD, 0xF0, 0x95, 0xC1, 0x03, 0xDD,
    0x7B, 0xC2, 0xB2, 0x3C, 0x28, 0x54, 0xD3, 0x68, 0xA4, 0x72, 0xC8, 0x66, 0x96, 0xE0, 0xD1, 0xD8,
    0x7F, 0xF8, 0xD1, 0x26, 0x2B, 0xF7, 0xAD, 0xBA, 0x55, 0xCA, 0x15, 0xB9, 0x32, 0xC3, 0xE5, 0x88,
    0x97, 0x8E, 0x5C, 0xFB, 0x92, 0x25, 0x8B, 0xBF, 0xA2, 0x45, 0x55, 0x7A, 0xA7, 0x6F, 0x8B, 0x57,
    0x5B, 0xCF, 0x0E, 0xCB, 0x1D, 0xFB, 0x20, 0x82, 0x77, 0xA8, 0x8C, 0xCC, 0x16, 0xCE, 0x1D, 0xFA,
    0xDE, 0xCC, 0x0B, 0x62, 0xFE, 0xCC, 0xE1, 0xB7, 0xF0, 0xC3, 0x81, 0x64, 0x73, 0x40, 0xA0, 0xC2,
    0x4D, 0x89, 0x11, 0x75, 0x33, 0x55, 0x33, 0x8D, 0xE8, 0x4A, 0xFD, 0xEA, 0x6E, 0x30, 0x0B, 0xD7,
    0x31, 0x2C, 0xDE, 0x47, 0xE3, 0xBF, 0xF8, 0x55, 0x42, 0xE2, 0x7F, 0x59, 0xE5, 0x17, 0xEF, 0x99,
    0x34, 0x69, 0x91, 0xB1, 0x23, 0x8E, 0x20, 0x87, 0x2D, 0xA8, 0xFE, 0xD5, 0x8A, 0xF3, 0x84, 0x3A,
    0xF0, 0x37, 0xE4, 0x09, 0x00, 0x54, 0xEE, 0x67, 0x49, 0x93, 0xE4, 0x81, 0x70, 0xE3, 0x90, 0x4D,
    0xEF, 0xFE, 0x41, 0xB7, 0x99, 0x7B, 0xC1, 0x83, 0xBA, 0x62, 0x12, 0x6F, 0x7D, 0xDE, 0x6B, 0xAF,
    0xDA, 0x16, 0xF9, 0x55, 0x51, 0xEE, 0xA6, 0x0C, 0x2B, 0x02, 0xA3, 0xFD, 0x8D, 0xFB, 0x30, 0x17,
    0xE4, 0x6F, 0xDF, 0x36, 0x71, 0xC4, 0xCA, 0x87, 0x25, 0x48, 0xB0, 0x47, 0xEC, 0xEA, 0xB4, 0xBF,
    0xA5, 0x4D, 0x9B, 0x9F, 0x02, 0x93, 0xC4, 0xE3, 0xE4, 0xE8, 0x42, 0x2D, 0x68, 0x81, 0x15, 0x0A,
    0xEB, 0x84, 0x5B, 0xD6, 0xA8, 0x74, 0xFB, 0x7D, 0x1D, 0xCB, 0x2C, 0xDA, 0x46, 0x2A, 0x76, 0x62,
    0xCE, 0xBC, 0x5C, 0x9E, 0x8B, 0xE7, 0xCF, 0xBE, 0x78, 0xF5, 0x7C, 0xEB, 0xB3, 0x3A, 0x9C, 0xAA,
    0x6F, 0xCC, 0x72, 0xD1, 0x59, 0xF2, 0x11, 0x23, 0xD6, 0x3F, 0x48, 0xD1, 0xB7, 0xCE, 0xB0, 0xBF,
    0xCB, 0xEA, 0x80, 0xDE, 0x57, 0xD4, 0x5E, 0x97, 0x2F, 0x75, 0xD1, 0x50, 0x8E, 0x80, 0x2C, 0x66,
    0x79, 0xBF, 0x72, 0x4B, 0xBD, 0x8A, 0x81, 0x6C, 0xD3, 0xE1, 0x01, 0xDC, 0xD2, 0x15, 0x26, 0xC5,
    0x36, 0xDA, 0x2C, 0x1A, 0xC0, 0x27, 0x94, 0xED, 0xB7, 0x9B, 0x85, 0x0B, 0x5E, 0x80, 0x97, 0xC5,
    0xEC, 0x4F, 0xEC, 0x88, 0x5D, 0x50, 0x07, 0x35, 0x47, 0xDC, 0x0B, 0x3B, 0x3D, 0xDD, 0x60, 0xAF,
    0xA8, 0x5D, 0x81, 0x38, 0x24, 0x25, 0x5D, 0x5C, 0x15, 0xD1, 0xDE, 0xB3, 0xAB, 0xEC, 0x05, 0x69,
    0xEF, 0x83, 0xED, 0x57, 0x54, 0xB8, 0x64, 0x64, 0x11, 0x16, 0x32, 0x69, 0xDA, 0x9F, 0x2D, 0x7F,
    0x36, 0xBB, 0x44, 0x5A, 0x34, 0xE8, 0x7F, 0xBF, 0x03, 0xEB, 0x00, 0x7F, 0x59, 0x68, 0x22, 0x79,
    0xCF, 0x73, 0x6C, 0x2C, 0x29, 0xA7, 0xA1, 0x5F, 0x38, 0xA1, 0x1D, 0xF0, 0x20, 0x53, 0xE0, 0x1A,
    0x63, 0x14, 0x58, 0x71, 0x10, 0xAA, 0x08, 0x0C, 0x3E, 0x16, 0x1A, 0x60, 0x22, 0x82, 0x7F, 0xBA,
    0xA4, 0x43, 0xA0, 0xD0, 0xAC, 0x1B, 0xD5, 0x6B, 0x64, 0xB5, 0x14, 0x93, 0x31, 0x9E, 0x53, 0x50,
    0xD0, 0x57, 0x66, 0xEE, 0x5A, 0x4F, 0xFB, 0x03, 0x2A, 0x69, 0x58, 0x76, 0xF1, 0x83, 0xF7, 0x4E,
    0xBA, 0x8C, 0x42, 0x06, 0x60, 0x5D, 0x6D, 0xCE, 0x60, 0x88, 0xAE, 0xA4, 0xC3, 0xF1, 0x03, 0xA5,
    0x4B, 0x98, 0xA1, 0xFF, 0x67, 0xE1, 0xAC, 0xA2, 0xB8, 0x62, 0xD7, 0x6F, 0xA0, 0x31, 0xB4, 0xD2,
    0x77, 0xAF, 0x21, 0x10, 0x06, 0xC6, 0x9A, 0xFF, 0x1D, 0x09, 0x17, 0x0E, 0x5F, 0xF1, 0xAA, 0x54,
    0x34, 0x4B, 0x45, 0x8A, 0x87, 0x63, 0xA6, 0xDC, 0xF9, 0x24, 0x30, 0x67, 0xC6, 0xB2, 0xD6, 0x61,
    0x33, 0x69, 0xEE, 0x50, 0x61, 0x57, 0x28, 0xE7, 0x7E, 0xEE, 0xEC, 0x3A, 0x5A, 0x73, 0x4E, 0xA8,
    0x8D, 0xE4, 0x18, 0xEA, 0xEC, 0x41, 0x64, 0xC8, 0xE2, 0xE8, 0x66, 0xB6, 0x2D, 0xB6, 0xFB, 0x6A,
    0x6C, 0x16, 0xB3, 0xDD, 0x46, 0x43, 0xB9, 0x73, 0x00, 0x6A, 0x71, 0xED, 0x4E, 0x9D, 0x25, 0x1A,
    0xC3, 0x3C, 0x4A, 0x95, 0x15, 0x99, 0x35, 0x81, 0x14, 0x02, 0xD6, 0x98, 0x9B, 0xEC, 0xD8, 0x23,
    0x3B, 0x84, 0x29, 0xAF, 0x0C, 0x99, 0x83, 0xA6, 0x9A, 0x34, 0x4F, 0xFA, 0xE8, 0xD0, 0x3C, 0x4B,
    0xD0, 0xFB, 0xB6, 0x68, 0xB8, 0x9E, 0x8F, 0xCD, 0xF7, 0x60, 0x2D, 0x7A, 0x22, 0xE5, 0x7D, 0xAB,
    0x65, 0x1B, 0x95, 0xA7, 0xA8, 0x7F, 0xB6, 0x77, 0x47, 0x7B, 0x5F, 0x8B, 0x12, 0x72, 0xD0, 0xD4,
    0x91, 0xEF, 0xDE, 0x19, 0x50, 0x3C, 0xA7, 0x8B, 0xC4, 0xA9, 0xB3, 0x23, 0xCB, 0x76, 0xE6, 0x81,
    0xF0, 0xC1, 0x04, 0x8F, 0xA3, 0xB8, 0x54, 0x5B, 0x97, 0xAC, 0x19, 0xFF, 0x3F, 0x55, 0x27, 0x2F,
    0xE0, 0x1D, 0x42, 0x9B, 0x57, 0xFC, 0x4B, 0x4E, 0x0F, 0xCE, 0x98, 0xA9, 0x43, 0x57, 0x03, 0xBD,
    0xE7, 0xC8, 0x94, 0xDF, 0x6E, 0x36, 0x73, 0x32, 0xB4, 0xEF, 0x2E, 0x85, 0x7A, 0x6E, 0xFC, 0x6C,
    0x18, 0x82, 0x75, 0x35, 0x90, 0x07, 0xF3, 0xE4, 0x9F, 0x3E, 0xDC, 0x68, 0xF3, 0xB5, 0xF3, 0x19,
    0x80, 0x92, 0x06, 0x99, 0xA2, 0xE8, 0x6F, 0xFF, 0x2E, 0x7F, 0xAE, 0x42, 0xA4, 0x5F, 0xFB, 0xD4,
    0x0E, 0x81, 0x2B, 0xC3, 0x04, 0xFF, 0x2B, 0xB3, 0x74, 0x4E, 0x36, 0x5B, 0x9C, 0x15, 0x00, 0xC6,
    0x47, 0x2B, 0xE8, 0x8B, 0x3D, 0xF1, 0x9C, 0x03, 0x9A, 0x58, 0x7F, 0x9B, 0x9C, 0xBF, 0x85, 0x49,
    0x79, 0x35, 0x2E, 0x56, 0x7B, 0x41, 0x14, 0x39, 0x47, 0x83, 0x26, 0xAA, 0x07, 0x89, 0x98, 0x11,
    0x1B, 0x86, 0xE7, 0x73, 0x7A, 0xD8, 0x7D, 0x78, 0x61, 0x53, 0xE9, 0x79, 0xF5, 0x36, 0x8D, 0x44,
    0x92, 0x84, 0xF9, 0x13, 0x50, 0x58, 0x3B, 0xA4, 0x6A, 0x36, 0x65, 0x49, 0x8E, 0x3C, 0x0E, 0xF1,
    0x6F, 0xD2, 0x84, 0xC4, 0x7E, 0x8E, 0x3F, 0x39, 0xAE, 0x7C, 0x84, 0xF1, 0x63, 0x37, 0x8E, 0x3C,
    0xCC, 0x3E, 0x44, 0x81, 0x45, 0xF1, 0x4B, 0xB9, 0xED, 0x6B, 0x36, 0x5D, 0xBB, 0x20, 0x60, 0x1A,
    0x0F, 0xA3, 0xAA, 0x55, 0x77, 0x3A, 0xA9, 0xAE, 0x37, 0x4D, 0xBA, 0xB8, 0x86, 0x6B, 0xBC, 0x08,
    0x50, 0xF6, 0xCC, 0xA4, 0xBD, 0x1D, 0x40, 0x72, 0xA5, 0x86, 0xFA, 0xE2, 0x10, 0xAE, 0x3D, 0x58,
    0x4B, 0x97, 0xF3, 0x43, 0x74, 0xA9, 0x9E, 0xEB, 0x21, 0xB7, 0x01, 0xA4, 0x86, 0x93, 0x97, 0xEE,
    0x2F, 0x4F, 0x3B, 0x86, 0xA1, 0x41, 0x6F, 0x41, 0x26, 0x90, 0x78, 0x5C, 0x7F, 0x30, 0x38, 0x4B,
    0x3F, 0xAA, 0xEC, 0xED, 0x5C, 0x6F, 0x0E, 0xAD, 0x43, 0x87, 0xFD, 0x93, 0x35, 0xE6, 0x01, 0xEF,
    0x41, 0x26, 0x90, 0x99, 0x9E, 0xFB, 0x19, 0x5B, 0xAD, 0xD2, 0x91, 0x8A, 0xE0, 0x46, 0xAF, 0x65,
    0xFA, 0x4F, 0x84, 0xC1, 0xA1, 0x2D, 0xCF, 0x45, 0x8B, 0xD3, 0x85, 0x50, 0x55, 0x7C, 0xF9, 0x67,
    0x88, 0xD4, 0x4E, 0xE9, 0xD7, 0x6B, 0x61, 0x54, 0xA1, 0xA4, 0xA6, 0xA2, 0xC2, 0xBF, 0x30, 0x9C,
    0x40, 0x9F, 0x5F, 0xD7, 0x69, 0x2B, 0x24, 0x82, 0x5E, 0xD9, 0xD6, 0xA7, 0x12, 0x54, 0x1A, 0xF7,
    0x55, 0x9F, 0x76, 0x50, 0xA9, 0x95, 0x84, 0xE6, 0x6B, 0x6D, 0xB5, 0x96, 0x54, 0xD6, 0xCD, 0xB3,
    0xA1, 0x9B, 0x46, 0xA7, 0x94, 0x4D, 0xC4, 0x94, 0xB4, 0x98, 0xE3, 0xE1, 0xE2, 0x34, 0xD5, 0x33,
    0x16, 0x07, 0x54, 0xCD, 0xB7, 0x77, 0x53, 0xDB, 0x4F, 0x4D, 0x46, 0x9D, 0xE9, 0xD4, 0x9C, 0x8A,
    0x36, 0xB6, 0xB8, 0x38, 0x26, 0x6C, 0x0E, 0xFF, 0x9C, 0x1B, 0x43, 0x8B, 0x80, 0xCC, 0xB9, 0x3D,
    0xDA, 0xC7, 0xF1, 0x8A, 0xF2, 0x6D, 0xB8, 0xD7, 0x74, 0x2F, 0x7E, 0x1E, 0xB7, 0xD3, 0x4A, 0xB4,
    0xAC, 0xFC, 0x79, 0x48, 0x6C, 0xBC, 0x96, 0xB6, 0x94, 0x46, 0x57, 0x2D, 0xB0, 0xA3, 0xFC, 0x1E,
    0xB9, 0x52, 0x60, 0x85, 0x2D, 0x41, 0xD0, 0x43, 0x01, 0x1E, 0x1C, 0xD5, 0x7D, 0xFC, 0xF3, 0x96,
    0x0D, 0xC7, 0xCB, 0x2A, 0x29, 0x9A, 0x93, 0xDD, 0x88, 0x2D, 0x37, 0x5D, 0xAA, 0xFB, 0x49, 0x68,
    0xA0, 0x9C, 0x50, 0x86, 0x7F, 0x68, 0x56, 0x57, 0xF9, 0x79, 0x18, 0x39, 0xD4, 0xE0, 0x01, 0x84,
    0x33, 0x61, 0xCA, 0xA5, 0xD2, 0xD6, 0xE4, 0xC9, 0x8A, 0x4A, 0x23, 0x44, 0x4E, 0xBC, 0xF0, 0xDC,
    0x24, 0xA1, 0xA0, 0xC4, 0xE2, 0x07, 0x3C, 0x10, 0xC4, 0xB5, 0x25, 0x4B, 0x65, 0x63, 0xF4, 0x80,
    0xE7, 0xCF, 0x61, 0xB1, 0x71, 0x82, 0x21, 0x87, 0x2C, 0xF5, 0x91, 0x00, 0x32, 0x0C, 0xEC, 0xA9,
    0xB5, 0x9A, 0x74, 0x85, 0xE3, 0x36, 0x8F, 0x76, 0x4F, 0x9C, 0x6D, 0xCE, 0xBC, 0xAD, 0x0A, 0x4B,
    0xED, 0x76, 0x04, 0xCB, 0xC3, 0xB9, 0x33, 0x9E, 0x01, 0x93, 0x96, 0x69, 0x7D, 0xC5, 0xA2, 0x45,
    0x79, 0x9B, 0x04, 0x5C, 0x84, 0x09, 0xED, 0x88, 0x43, 0xC7, 0xAB, 0x93, 0x14, 0x26, 0xA1, 0x40,
    0xB5, 0xCE, 0x4E, 0xBF, 0x2A, 0x42, 0x85, 0x3E, 0x2C, 0x3B, 0x54, 0xE8, 0x12, 0x1F, 0x0E, 0x97,
    0x59, 0xB2, 0x27, 0x89, 0xFA, 0xF2, 0xDF, 0x8E, 0x68, 0x59, 0xDC, 0x06, 0xBC, 0xB6, 0x85, 0x0D,
    0x06, 0x22, 0xEC, 0xB1, 0xCB, 0xE5, 0x04, 0xE6, 0x3D, 0xB3, 0xB0, 0x41, 0x73, 0x08, 0x3F, 0x3C,
    0x58, 0x86, 0x63, 0xEB, 0x50, 0xEE, 0x1D, 0x2C, 0x37, 0x74, 0xA9, 0xD3, 0x18, 0xA3, 0x47, 0x6E,
    0x93, 0x54, 0xAD, 0x0A, 0x5D, 0xB8, 0x2A, 0x55, 0x5D, 0x78, 0xF6, 0xEE, 0xBE, 0x8E, 0x3C, 0x76,
    0x69, 0xB9, 0x40, 0xC2, 0x34, 0xEC, 0x2A, 0xB9, 0xED, 0x7E, 0x20, 0xE4, 0x8D, 0x00, 0x38, 0xC7,
    0xE6, 0x8F, 0x44, 0xA8, 0x86, 0xCE, 0xEB, 0x2A, 0xE9, 0x90, 0xF1, 0x4C, 0xDF, 0x32, 0xFB, 0x73,
    0x1B, 0x6D, 0x92, 0x1E, 0x95, 0xFE, 0xB4, 0xDB, 0x65, 0xDF, 0x4D, 0x23, 0x54, 0x89, 0x48, 0xBF,
    0x4A, 0x2E, 0x70, 0xD6, 0xD7, 0x62, 0xB4, 0x33, 0x29, 0xB1, 0x3A, 0x33, 0x4C, 0x23, 0x6D, 0xA6,
    0x76, 0xA5, 0x21, 0x63, 0x48, 0xE6, 0x90, 0x5D, 0xED, 0x90, 0x95, 0x0B, 0x7A, 0x84, 0xBE, 0xB8,
    0x0D, 0x5E, 0x63, 0x0C, 0x62, 0x26, 0x4C, 0x14, 0x5A, 0xB3, 0xAC, 0x23, 0xA4, 0x74, 0xA7, 0x6F,
    0x33, 0x30, 0x05, 0x60, 0x01, 0x42, 0xA0, 0x28, 0xB7, 0xEE, 0x19, 0x38, 0xF1, 0x64, 0x80, 0x82,
    0x43, 0xE1, 0x41, 0x27, 0x1F, 0x1F, 0x90, 0x54, 0x7A, 0xD5, 0x23, 0x2E, 0xD1, 0x3D, 0xCB, 0x28,
    0xBA, 0x58, 0x7F, 0xDC, 0x7C, 0x91, 0x24, 0xE9, 0x28, 0x51, 0x83, 0x6E, 0xC5, 0x56, 0x21, 0x42,
    0xED, 0xA0, 0x56, 0x22, 0xA1, 0x40, 0x80, 0x6B, 0xA8, 0xF7, 0x94, 0xCA, 0x13, 0x6B, 0x0C, 0x39,
    0xD9, 0xFD, 0xE9, 0xF3, 0x6F, 0xA6, 0x9E, 0xFC, 0x70, 0x8A, 0xB3, 0xBC, 0x59, 0x3C, 0x1E, 0x1D,
    0x6C, 0xF9, 0x7C, 0xAF, 0xF9, 0x88, 0x71, 0x95, 0xEB, 0x57, 0x00, 0xBD, 0x9F, 0x8C, 0x4F, 0xE1,
    0x24, 0x83, 0xC5, 0x22, 0xEA, 0xFD, 0xD3, 0x0C, 0xE2, 0x17, 0x18, 0x7C, 0x6A, 0x4C, 0xDE, 0x77,
    0xB4, 0x53, 0x9B, 0x4C, 0x81, 0xCD, 0x23, 0x60, 0xAA, 0x0E, 0x25, 0x73, 0x9C, 0x02, 0x79, 0x32,
    0x30, 0xDF, 0x74, 0xDF, 0x75, 0x19, 0xF4, 0xA5, 0x14, 0x5C, 0xF7, 0x7A, 0xA8, 0xA5, 0x91, 0x84,
    0x7C, 0x60, 0x03, 0x06, 0x3B, 0xCD, 0x50, 0xB6, 0x27, 0x9C, 0xFE, 0xB1, 0xDD, 0xCC, 0xD3, 0xB0,
    0x59, 0x24, 0xB2, 0xCA, 0xE2, 0x1C, 0x81, 0x22, 0x9D, 0x07, 0x8F, 0x8E, 0xB9, 0xBE, 0x4E, 0xFA,
    0xFC, 0x39, 0x65, 0xBA, 0xBF, 0x9D, 0x12, 0x37, 0x5E, 0x97, 0x7E, 0xF3, 0x89, 0xF5, 0x5D, 0xF5,
    0xE3, 0x09, 0x8C, 0x62, 0xB5, 0x20, 0x9D, 0x0C, 0x53, 0x8A, 0x68, 0x1B, 0xD2, 0x8F, 0x75, 0x17,
    0x5D, 0xD4, 0xE5, 0xDA, 0x75, 0x62, 0x19, 0x14, 0x6A, 0x26, 0x2D, 0xEB, 0xF8, 0xAF, 0x37, 0xF0,
    0x6C, 0xA4, 0x55, 0xB1, 0xBC, 0xE2, 0x33, 0xC0, 0x9A, 0xCA, 0xB0, 0x11, 0x49, 0x4F, 0x68, 0x9B,
    0x3B, 0x6B, 0x3C, 0xCC, 0x13, 0xF6, 0xC7, 0x85, 0x61, 0x68, 0x42, 0xAE, 0xBB, 0xDD, 0xCD, 0x45,
    0x16, 0x29, 0x1D, 0xEA, 0xDB, 0xC8, 0x03, 0x94, 0x3C, 0xEE, 0x4F, 0x82, 0x11, 0xC3, 0xEC, 0x28,
    0xBD, 0x97, 0x05, 0x99, 0xDE, 0xD7, 0xBB, 0x5E, 0x22, 0x1F, 0xD4, 0xEB, 0x64, 0xD9, 0x92, 0xD9,
    0x85, 0xB7, 0x6A, 0x05, 0x6A, 0xE4, 0x24, 0x41, 0xF1, 0xCD, 0xF0, 0xD8, 0x3F, 0xF8, 0x9E, 0x0E,
    0xCD, 0x0B, 0x7A, 0x70, 0x6B, 0x5A, 0x75, 0x0A, 0x6A, 0x33, 0x88, 0xEC, 0x17, 0x75, 0x08, 0x70,
    0x10, 0x2F, 0x24, 0xCF, 0xC4, 0xE9, 0x42, 0x00, 0x61, 0x94, 0xCA, 0x1F, 0x3A, 0x76, 0x06, 0xFA,
    0xD2, 0x48, 0x81, 0xF0, 0x77, 0x60, 0x03, 0x45, 0xD9, 0x61, 0xF4, 0xA4, 0x6F, 0x3D, 0xD9, 0x30,
    0xC3, 0x04, 0x6B, 0x54, 0x2A, 0xB7, 0xEC, 0x3B, 0xF4, 0x4B, 0xF5, 0x68, 0x52, 0x26, 0xCE, 0xFF,
    0x5D, 0x19, 0x91, 0xA0, 0xA3, 0xA5, 0xA9, 0xB1, 0xE0, 0x23, 0xC4, 0x0A, 0x77, 0x4D, 0xF9, 0x51,
    0x20, 0xA3, 0xA5, 0xA9, 0xB1, 0xC1, 0x00, 0x82, 0x86, 0x8E, 0x7F, 0x5D, 0x19, 0x91, 0xA0, 0xA3,
    0xC4, 0xEB, 0x54, 0x0B, 0x75, 0x68, 0x52, 0x07, 0x8C, 0x9A, 0x97, 0x8D, 0x79, 0x70, 0x62, 0x46,
    0xEF, 0x5C, 0x1B, 0x95, 0x89, 0x71, 0x41, 0xE1, 0x21, 0xA1, 0xA1, 0xA1, 0xC0, 0x02, 0x67, 0x4C,
    0x1A, 0xB6, 0xCF, 0xFD, 0x78, 0x53, 0x24, 0xAB, 0xB5, 0xC9, 0xF1, 0x60, 0x23, 0xA5, 0xC8, 0x12,
    0x87, 0x6D, 0x58, 0x13, 0x85, 0x88, 0x92, 0x87, 0x6D, 0x58, 0x32, 0xC7, 0x0C, 0x9A, 0x97, 0xAC,
    0xDA, 0x36, 0xEE, 0x5E, 0x3E, 0xDF, 0x1D, 0xB8, 0xF2, 0x66, 0x2F, 0xBD, 0xF8, 0x72, 0x47, 0xED,
    0x58, 0x13, 0x85, 0x88, 0x92, 0x87, 0x8C, 0x7B, 0x55, 0x09, 0x90, 0xA2, 0xC6, 0xEF, 0x3D, 0xF8,
    0x53, 0x24, 0xAB, 0xD4, 0x2A, 0xB7, 0xEC, 0x5A, 0x36, 0xEE, 0x5E, 0x3E, 0xDF, 0x3C, 0xFA, 0x76,
    0x4F, 0xFD, 0x59, 0x30, 0xE2, 0x46, 0xEF, 0x3D, 0xF8, 0x53, 0x05, 0x69, 0x31, 0xC1, 0x00, 0x82,
    0x86, 0x8E, 0x7F, 0x5D, 0x19, 0xB0, 0xE2, 0x27, 0xCC, 0xFB, 0x74, 0x4B, 0x14, 0x8B, 0x94, 0x8B,
    0x75, 0x68, 0x33, 0xC5, 0x08, 0x92, 0x87, 0x8C, 0x9A, 0xB6, 0xCF, 0x1C, 0xBA, 0xD7, 0x0D, 0x98,
    0xB2, 0xE6, 0x2F, 0xDC, 0x1B, 0x95, 0x89, 0x71, 0x60, 0x23, 0xC4, 0x0A, 0x96, 0x8F, 0x9C, 0xBA,
    0xF6, 0x6E, 0x3F, 0xFC, 0x5B, 0x15, 0xA8, 0xD2, 0x26, 0xAF, 0xBD, 0xF8, 0x72, 0x66, 0x2F, 0xDC,
    0x1B, 0xB4, 0xCB, 0x14, 0x8B, 0x94, 0xAA, 0xB7, 0xCD, 0xF9, 0x51, 0x01, 0x80, 0x82, 0x86, 0x6F,
    0x3D, 0xD9, 0x30, 0xE2, 0x27, 0xCC, 0xFB, 0x74, 0x4B, 0x14, 0xAA, 0xB7, 0xCD, 0xF9, 0x70, 0x43,
    0x04, 0x6B, 0x35, 0xC9, 0xF1, 0x60, 0x23, 0xA5, 0xC8, 0xF3, 0x45, 0x08, 0x92, 0x87, 0x6D, 0x58,
    0x32, 0xE6, 0x2F, 0xBD, 0xF8, 0x72, 0x66, 0x4E, 0x1E, 0xBE, 0xFE, 0x7E, 0x7E, 0x7E, 0x5F, 0x1D,
    0x99, 0x91, 0xA0, 0xA3, 0xC4, 0x0A, 0x77, 0x4D, 0x18, 0x93, 0xA4, 0xAB, 0xD4, 0x0B, 0x75, 0x49,
    0x10, 0xA2, 0xC6, 0xEF, 0x3D, 0xF8, 0x53, 0x24, 0xAB, 0xB5, 0xE8, 0x33, 0xE4, 0x4A, 0x16, 0xAE,
    0xDE, 0x1F, 0xBC, 0xDB, 0x15, 0xA8, 0xB3, 0xC5, 0x08, 0x73, 0x45, 0xE9, 0x31, 0xC1, 0xE1, 0x21,
    0xA1, 0xA1, 0xA1, 0xC0, 0x02, 0x86, 0x6F, 0x5C, 0x3A, 0xD7, 0x0D, 0x98, 0x93, 0xA4, 0xCA, 0x16,
    0xAE, 0xDE, 0x1F, 0x9D, 0x99, 0xB0, 0xE2, 0x46, 0xEF, 0x3D, 0xF8, 0x72, 0x47, 0x0C, 0x9A, 0xB6,
    0xCF, 0xFD, 0x59, 0x11, 0xA0, 0xA3, 0xA5, 0xC8, 0xF3, 0x45, 0x08, 0x92, 0x87, 0x6D, 0x39, 0xF0,
    0x43, 0x04, 0x8A, 0x96, 0xAE, 0xDE, 0x3E, 0xDF, 0x1D, 0x99, 0x91, 0xA0, 0xC2, 0x06, 0x6F, 0x3D,
    0xF8, 0x72, 0x47, 0x0C, 0x9A, 0x97, 0x8D, 0x98, 0x93, 0x85, 0x88, 0x73, 0x45, 0xE9, 0x31, 0xE0,
    0x23, 0xA5, 0xA9, 0xD0, 0x03, 0x84, 0x8A, 0x96, 0xAE, 0xDE, 0x1F, 0xBC, 0xDB, 0x15, 0xA8, 0xD2,
    0x26, 0xCE, 0xFF, 0x5D, 0x19, 0x91, 0x81, 0x80, 0x82, 0x67, 0x2D, 0xD8, 0x13, 0xA4, 0xAB, 0xD4,
    0x0B, 0x94, 0xAA, 0xB7, 0xCD, 0xF9, 0x51, 0x20, 0xA3, 0xA5, 0xC8, 0xF3, 0x45, 0xE9, 0x50, 0x22,
    0xC6, 0xEF, 0x5C, 0x3A, 0xD7, 0x0D, 0x98, 0x93, 0x85, 0x88, 0x73, 0x64, 0x4A, 0xF7, 0x4D, 0xF9,
    0x51, 0x20, 0xA3, 0xC4, 0x0A, 0x96, 0xAE, 0xDE, 0x3E, 0xFE, 0x7E, 0x7E, 0x7E, 0x5F, 0x3C, 0xFA,
    0x76, 0x4F, 0xFD, 0x78, 0x72, 0x66, 0x2F, 0xBD, 0xD9, 0x30, 0xC3, 0xE5, 0x48, 0x12, 0x87, 0x8C,
    0x7B, 0x55, 0x28, 0xD2, 0x07, 0x8C, 0x9A, 0x97, 0xAC, 0xDA, 0x17, 0x8D, 0x79, 0x51, 0x20, 0xA3,
    0xC4, 0xEB, 0x54, 0x0B, 0x94, 0x8B, 0x94, 0xAA, 0xD6, 0x2E, 0xBF, 0xFC, 0x5B, 0x15, 0xA8, 0xD2,
    0x26, 0xAF, 0xDC, 0x1B, 0xB4, 0xEA, 0x37, 0xEC, 0x3B, 0xF4, 0x6A, 0x37, 0xCD, 0x18, 0x93, 0x85,
    0x69, 0x31, 0xC1, 0xE1, 0x40, 0xE3, 0x25, 0xC8, 0x12, 0x87, 0x8C, 0x9A, 0xB6, 0xCF, 0xFD, 0x59,
    0x11, 0xA0, 0xC2, 0x06, 0x8E, 0x7F, 0x5D, 0x38, 0xF2, 0x47, 0x0C, 0x7B, 0x74, 0x6A, 0x37, 0xEC,
    0x5A, 0x36, 0xEE, 0x3F, 0xFC, 0x7A, 0x76, 0x4F, 0x1C, 0x9B, 0x95, 0x89, 0x71, 0x41, 0x00, 0x63,
    0x44, 0xEB, 0x54, 0x2A, 0xD6, 0x0F, 0x9C, 0xBA, 0xD7, 0x0D, 0x98, 0x93, 0x85, 0x69, 0x31, 0xC1,
    0x00, 0x82, 0x86, 0x8E, 0x9E, 0xBE, 0xDF, 0x3C, 0xFA, 0x57, 0x2C, 0xDA, 0x36, 0xEE, 0x3F, 0xFC,
    0x5B, 0x15, 0x89, 0x71, 0x41, 0x00, 0x82, 0x86, 0x8E, 0x7F, 0x5D, 0x38, 0xF2, 0x47, 0xED, 0x58,
    0x13, 0xA4, 0xCA, 0xF7, 0x4D, 0xF9, 0x51, 0x01, 0x80, 0x63, 0x44, 0xEB, 0x54, 0x2A, 0xD6, 0x2E,
    0xBF, 0xDD, 0x19, 0x91, 0xA0, 0xA3, 0xA5, 0xA9, 0xB1, 0xE0, 0x42, 0x06, 0x8E, 0x7F, 0x5D, 0x19,
    0x91, 0xA0, 0xA3, 0xC4, 0x0A, 0x96, 0x8F, 0x7D, 0x78, 0x72, 0x47, 0x0C, 0x7B, 0x74, 0x6A, 0x56,
    0x2E, 0xDE, 0x1F, 0xBC, 0xFA, 0x57, 0x0D, 0x79, 0x51, 0x01, 0x61, 0x21, 0xA1, 0xC0, 0xE3, 0x25,
    0xA9, 0xB1, 0xC1, 0xE1, 0x40, 0x02, 0x67, 0x4C, 0x1A, 0x97, 0x8D, 0x98, 0x93, 0xA4, 0xAB, 0xD4,
    0x2A, 0xD6, 0x0F, 0x9C, 0x9B, 0xB4, 0xCB, 0x14, 0xAA, 0xB7, 0xCD, 0xF9, 0x51, 0x20, 0xA3, 0xC4,
    0xEB, 0x35, 0xC9, 0xF1, 0x60, 0x42, 0x06, 0x8E, 0x7F, 0x7C, 0x7A, 0x76, 0x6E, 0x3F, 0xFC, 0x7A,
    0x76, 0x6E, 0x5E, 0x3E, 0xFE, 0x7E, 0x5F, 0x3C, 0xDB, 0x15, 0x89, 0x71, 0x41, 0xE1, 0x21, 0xC0,
    0xE3, 0x44, 0xEB, 0x54, 0x2A, 0xB7, 0xCD, 0xF9, 0x70, 0x62, 0x27, 0xAD, 0xD8, 0x32, 0xC7, 0x0C,
    0x7B, 0x74, 0x4B, 0x14, 0xAA, 0xB7, 0xEC, 0x3B, 0xD5, 0x28, 0xD2, 0x07, 0x6D, 0x39, 0xD1, 0x20,
    0xC2, 0xE7, 0x4C, 0x1A, 0x97, 0x8D, 0x98, 0xB2, 0xC7, 0x0C, 0x59, 0x28, 0xF3, 0x9B
};
