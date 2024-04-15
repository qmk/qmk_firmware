/*
Copyright 2023 @ Nuphy <https://nuphy.com/>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#include "user_kb.h"
#include "quantum_keycodes.h"

enum custom_keycodes {
    RF_DFU = QK_KB_0,
    LNK_USB,
    LNK_RF,
    LNK_BLE1,
    LNK_BLE2,
    LNK_BLE3,

    MAC_TASK,
    MAC_SEARCH,
    MAC_VOICE,
    MAC_CONSOLE,
    MAC_DND,

    WIN_LOCK,
    DEV_RESET,
    SLEEP_MODE,
    BAT_SHOW,
    RGB_TEST,
    SHIFT_GRV,

    SIDE_VAI,
    SIDE_VAD,
    SIDE_MOD,
    SIDE_HUI,
    SIDE_SPI,
    SIDE_SPD,

    LOGO_VAI,
    LOGO_VAD,
    LOGO_MOD,
    LOGO_HUI,
    LOGO_SPI,
    LOGO_SPD,
    TOG_USB_SLP,
    TOG_CAPS_IND,
    DEBOUNCE_PRESS_INC,
    DEBOUNCE_PRESS_DEC,
    DEBOUNCE_PRESS_SHOW,
    SLEEP_TIMEOUT_INC,
    SLEEP_TIMEOUT_DEC,
    SLEEP_TIMEOUT_SHOW,
    MAC_GLOBE,
    DEBOUNCE_RELEASE_INC,
    DEBOUNCE_RELEASE_DEC,
    DEBOUNCE_RELEASE_SHOW,
};

#define MAC_PRT G(S(KC_3))
#define MAC_PRTA G(S(KC_4))
#define WIN_PRTA G(S(KC_S))

#ifdef VIA_ENABLE

enum via_indicator_value {
    id_usb_sleep_toggle    = 0,
    id_debounce_press      = 1,
    id_debounce_release    = 2,
    id_sleep_timeout       = 3,
    id_caps_indicator_type = 4,
    id_sleep_toggle        = 5,
    // side light controls
    id_side_light_mode       = 10,
    id_side_light_speed      = 11,
    id_side_light_color      = 12,
    id_side_light_brightness = 13,
    // logo light controls
    id_logo_light_mode       = 20,
    id_logo_light_speed      = 21,
    id_logo_light_color      = 22,
    id_logo_light_brightness = 23,
};

// struct to save configs
typedef struct {
    uint8_t              been_initiated;
    bool                 usb_sleep_toggle : 1;
    bool                 sleep_enable : 1;
    uint8_t              debounce_press_ms;
    uint8_t              debounce_release_ms;
    uint8_t              sleep_timeout;
    CAPS_LOCK_INDICATION caps_indication_type;
    // (top) side light config
    uint8_t side_mode;
    uint8_t side_brightness;
    uint8_t side_speed;
    uint8_t side_rgb;
    uint8_t side_color;
    // logo light config
    uint8_t logo_mode;
    uint8_t logo_brightness;
    uint8_t logo_speed;
    uint8_t logo_rgb;
    uint8_t logo_color;
} via_config;

// function declaration
void indicator_config_set_value(uint8_t *data);
void indicator_config_get_value(uint8_t *data);
#endif
extern via_config g_config;
void              via_save_values(void);
