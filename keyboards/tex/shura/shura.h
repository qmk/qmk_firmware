// Copyright 2026 Mauro DiBenedetto
// Copyright 2026 Antonio SJ Musumeci (@trapexit)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include "quantum.h"
#include "shura_fn.h"

// Bluetooth connector signals match the schematic for the BLE5 add-on used with the Shinobi:
// USART0 TX/RX (AF6), RESET_N and FROM_MCU (wake).
// BLE5 (nRF52810) runs at 500 kbaud; BLE4 (CC2541) at 115,942 baud.
#define SHURA_BLE_TX_PIN B0
#define SHURA_BLE_RX_PIN B1
#define SHURA_BLE_BAUD 500000
#define SHURA_BLE_AF 6
#define SHURA_BLE_RESET_PIN C1
#define SHURA_BLE_FROM_MCU_PIN D1
#ifdef SHURA_BLE4
#    define SHURA_BLE_TO_MCU_PIN B10
#endif
// Configuration block the stock firmware sends the module at start-up (name "TEX-BLE").
#define SHURA_BLE_CONFIG_BLOCK {0x00, 0x00, 0x10, 0x00, 0xB8, 0x0B, 0x28, 0x00, 0x50, 0x46, 0xA0, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0x54, 0x45, 0x58, 0x2D, 0x42, 0x4C, 0x45, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

#define SHURA_CAPS_LED_PIN C10
// USB power detect, active high; the BLE4 module's TO_MCU also raises this line.
#define SHURA_WAKEUP_PIN B12
#define SHURA_BATTERY_PIN A0
// TrackPoint power switch, active low.
#define SHURA_TP_POWER_PIN C8

// AFIO ESSR selects one port per EXTI line, four bits per line (A=0, B=1).
// Matrix rows PA1..PA8; PB12 wakes on USB, and BLE4 also wakes on PB10.
#define SHURA_MATRIX_WAKE_LINES 0x01FEU
#define SHURA_WAKE_ESSR0 0U
#ifdef SHURA_BLE4
#    define SHURA_WAKE_LINES (SHURA_MATRIX_WAKE_LINES | (1U << 10) | (1U << 12))
#    define SHURA_WAKE_ESSR1 ((1U << 8) | (1U << 16))
#else
#    define SHURA_WAKE_LINES (SHURA_MATRIX_WAKE_LINES | (1U << 12))
#    define SHURA_WAKE_ESSR1 (1U << 16)
#endif

#define TEX_DIP4_FN_SCROLL (1U << 3)
#define TEX_DIP5_REVERSE (1U << 4)

// Signed division truncating toward zero, built on unsigned division: the Cortex-M0+
// has no divide instruction, and this avoids linking libgcc's signed division.
static inline int16_t shura_div(int32_t numerator, uint16_t divisor) {
    uint32_t magnitude = numerator < 0 ? -(uint32_t)numerator : (uint32_t)numerator;
    int32_t  quotient  = (int32_t)(magnitude / divisor);
    return numerator < 0 ? -quotient : quotient;
}

#ifdef BLUETOOTH_ENABLE
bool ble_process_record(uint16_t keycode, keyrecord_t *record);
void ble_housekeeping(void);
bool ble_pairing(void);
void ble_flush_keys(uint8_t settle_ms);
void ble_set_battery(uint8_t percent);
void ble_sleep(void);
void ble_wake(void);
#    ifdef SHURA_BLE4
bool ble4_can_sleep(void);
bool ble4_radio_asleep(void);
#    endif
void    power_init(void);
void    power_task(void);
void    power_pointer_activity(void);
void    power_input(void);
void    power_set_sleep(uint8_t choice, bool announce);
uint8_t battery_percent(void);
void    battery_report(void);
void    type_text(const char *text);
void    type_number(uint16_t number, const char *after);
#else
// Without the Bluetooth add-on board there is no battery: USB power only.
static inline bool ble_process_record(uint16_t keycode, keyrecord_t *record) {
    return true;
}
static inline void ble_housekeeping(void) {}
static inline void power_init(void) {}
static inline void power_task(void) {}
static inline void power_pointer_activity(void) {}
static inline void power_input(void) {}
static inline void power_set_sleep(uint8_t choice, bool announce) {}
static inline void battery_report(void) {}
#endif

void           tp_power_off(void);
void           tp_power_on(void);
void           shura_trackpoint_task(void);
bool           shura_trackpoint_record(uint16_t keycode, bool pressed);
void           shura_trackpoint_scale(report_mouse_t *report);
void           ps2_host_resume(void);
extern uint8_t tp_level;

// DIP switches 1-3 select profile 1-3 when exactly one is on, otherwise profile 0.
void           profile_switch_user(uint8_t profile);
extern uint8_t tex_dip;
