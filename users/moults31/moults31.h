/* Copyright 2021 moults31
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

#include QMK_KEYBOARD_H

#include "vscode.h"
#include "obs.h"
#include "gdb.h"

bool moults31_tap_custom_code(uint16_t keycode);

enum custom_keycodes {
    // VSCode keycodes
    M_VSC_TERMFOCUS = SAFE_RANGE,
    M_VSC_SIDEBARFOCUS,
    M_VSC_SIDEBARCLOSE,
    M_VSC_DBGCNSLFOCUS,
    M_VSC_EDGRPNXT,
    M_VSC_EDGRPPRV,
    M_VSC_MVEDTRNXTGRP,
    M_VSC_MVEDTRPRVGRP,
    M_VSC_VIEWSIZEINC,
    M_VSC_VIEWSIZEDEC,
    M_VSC_FILECLOSE,
    M_VSC_FILENXT,
    M_VSC_FILEPRV,
    // GDB keycodes (for vscode debugger)
    M_GDB_PLAY,
    M_GDB_PAUSE,
    M_GDB_STEPOVER,
    M_GDB_STEPIN,
    M_GDB_STEPOUT,
    M_GDB_RESTART,
    M_GDB_STOP,
    // MS Teams keycodes
    M_MST_CODEBLOCK,
    // OBS keycodes
    M_OBS_BRB,
    M_OBS_GAME,
    M_OBS_JSTCHT,
    M_OBS_DSKT_MUTE,
    M_OBS_DSKT_UNMUTE,
    M_OBS_VOICE_MUTE,
    M_OBS_VOICE_UNMUTE,
    M_OBS_MOOSIC_MUTE,
    M_OBS_MOOSIC_UNMUTE,
};
