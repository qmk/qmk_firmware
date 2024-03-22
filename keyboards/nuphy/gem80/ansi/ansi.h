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

#include "quantum.h"

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
};

#define MAC_PRT G(S(KC_3))
#define MAC_PRTA G(S(KC_4))
#define WIN_PRTA G(S(KC_S))
