/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "quantum.h"
#include "oled_driver.h"

void oled_driver_render_logo(void);
bool process_record_user_oled(uint16_t keycode, keyrecord_t *record);
extern uint32_t oled_timer;

#ifdef OLED_DISPLAY_128X64
#    define OLED_RENDER_KEYLOGGER "Keylogger: "

#    define OLED_RENDER_LAYOUT_NAME    "Layout: "
#    define OLED_RENDER_LAYOUT_QWERTY  "Qwerty"
#    define OLED_RENDER_LAYOUT_COLEMAK "Colemak"
#    define OLED_RENDER_LAYOUT_DVORAK  "Dvorak"
#    define OLED_RENDER_LAYOUT_WORKMAN "Workman"
#    define OLED_RENDER_LAYOUT_NORMAN  "Norman"
#    define OLED_RENDER_LAYOUT_MALTRON "Matron"
#    define OLED_RENDER_LAYOUT_EUCALYN "Eucalyn"
#    define OLED_RENDER_LAYOUT_CARPLAX "Carplax"

#    define OLED_RENDER_LAYER_NAME   "Layer:"
#    define OLED_RENDER_LAYER_LOWER  "Lower"
#    define OLED_RENDER_LAYER_RAISE  "Raise"
#    define OLED_RENDER_LAYER_ADJUST "Adjust"
#    define OLED_RENDER_LAYER_MODS   "Mods"

#    define OLED_RENDER_LOCK_NAME "Lock: "
#    define OLED_RENDER_LOCK_NUML "NUML"
#    define OLED_RENDER_LOCK_CAPS "CAPS"
#    define OLED_RENDER_LOCK_SCLK "SCLK"

#    define OLED_RENDER_MODS_NAME "Mods:"
#    define OLED_RENDER_MODS_SFT  "Sft"
#    define OLED_RENDER_MODS_CTL  "Ctl"
#    define OLED_RENDER_MODS_ALT  "Alt"
#    define OLED_RENDER_MODS_GUI  "GUI"

#    define OLED_RENDER_BOOTMAGIC_NAME  "Boot  "
#    define OLED_RENDER_BOOTMAGIC_NKRO  "NKRO"
#    define OLED_RENDER_BOOTMAGIC_NOGUI "nGUI"
#    define OLED_RENDER_BOOTMAGIC_GRV   "GRV"
#    define OLED_RENDER_BOOTMAGIC_CAPS  "CAPS"

#    define OLED_RENDER_USER_NAME "USER:"
#    define OLED_RENDER_USER_ANIM "Anim"
#    define OLED_RENDER_USER_LAYR "Layr"
#    define OLED_RENDER_USER_NUKE "Nuke"

#    define OLED_RENDER_WPM_COUNTER "WPM: "
#else
#    define OLED_RENDER_KEYLOGGER "KLogr"

#    define OLED_RENDER_LAYOUT_NAME    "Lyout"
#    define OLED_RENDER_LAYOUT_QWERTY  " QRTY"
#    define OLED_RENDER_LAYOUT_COLEMAK " COLE"
#    define OLED_RENDER_LAYOUT_DVORAK  " DVRK"
#    define OLED_RENDER_LAYOUT_WORKMAN " WKMN"
#    define OLED_RENDER_LAYOUT_NORMAN  " NORM"
#    define OLED_RENDER_LAYOUT_MALTRON " MLTN"
#    define OLED_RENDER_LAYOUT_EUCALYN " ECLN"
#    define OLED_RENDER_LAYOUT_CARPLAX " CRPX"

#    define OLED_RENDER_LAYER_NAME   "LAYER"
#    define OLED_RENDER_LAYER_LOWER  "Lower"
#    define OLED_RENDER_LAYER_RAISE  "Raise"
#    define OLED_RENDER_LAYER_ADJUST "Adjst"
#    define OLED_RENDER_LAYER_MODS   " Mods"

#    define OLED_RENDER_LOCK_NAME "Lock:"
#    define OLED_RENDER_LOCK_NUML "NumL"
#    define OLED_RENDER_LOCK_CAPS "CapL"
#    define OLED_RENDER_LOCK_SCLK "ScrL"

#    define OLED_RENDER_MODS_NAME "Mods: "
#    define OLED_RENDER_MODS_SFT  "Shft"
#    define OLED_RENDER_MODS_CTL  "Ctrl"
#    define OLED_RENDER_MODS_ALT  "Alt\n"
#    define OLED_RENDER_MODS_GUI  "GUI\n"

#    define OLED_RENDER_BOOTMAGIC_NAME  "BTMGK"
#    define OLED_RENDER_BOOTMAGIC_NKRO  "NKRO"
#    define OLED_RENDER_BOOTMAGIC_NOGUI "nGUI"
#    define OLED_RENDER_BOOTMAGIC_GRV   "GRV"
#    define OLED_RENDER_BOOTMAGIC_CAPS  "CAPS"

#    define OLED_RENDER_USER_NAME "USER:"
#    define OLED_RENDER_USER_ANIM "Anim"
#    define OLED_RENDER_USER_LAYR "Layr"
#    define OLED_RENDER_USER_NUKE "Nuke"

#    define OLED_RENDER_WPM_COUNTER "WPM: "

#endif
