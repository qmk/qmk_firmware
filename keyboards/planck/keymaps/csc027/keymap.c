/*
Copyright 2020 Constantine Chen @csc027

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

#include QMK_KEYBOARD_H
#include "csc027.h"

#define LAYOUT_wrapper(...) LAYOUT_ortho_4x12(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QW] = LAYOUT_wrapper(
        _____________________QWERTY_L1_____________________, _____________________QWERTY_R1_____________________,
        _____________________QWERTY_L2_____________________, _____________________QWERTY_R2_____________________,
        _____________________QWERTY_L3_____________________, _____________________QWERTY_R3_____________________,
        _____________________QWERTY_L4_____________________, _____________________QWERTY_R4_____________________
    ),

    [_RS] = LAYOUT_wrapper(
        ______________________RAISE_L1_____________________, ______________________RAISE_R1_____________________,
        ______________________RAISE_L2_____________________, ______________________RAISE_R2_____________________,
        ______________________RAISE_L3_____________________, ______________________RAISE_R3_____________________,
        ______________________RAISE_L4_____________________, ______________________RAISE_R4_____________________
    ),

    [_LW] = LAYOUT_wrapper(
        ______________________LOWER_L1_____________________, ______________________LOWER_R1_____________________,
        ______________________LOWER_L2_____________________, ______________________LOWER_R2_____________________,
        ______________________LOWER_L3_____________________, ______________________LOWER_R3_____________________,
        ______________________LOWER_L4_____________________, ______________________LOWER_R4_____________________
    ),

    [_MS] = LAYOUT_wrapper(
        ______________________MOUSE_L1_____________________, ______________________MOUSE_R1_____________________,
        ______________________MOUSE_L2_____________________, ______________________MOUSE_R2_____________________,
        ______________________MOUSE_L3_____________________, ______________________MOUSE_R3_____________________,
        ______________________MOUSE_L4_____________________, ______________________MOUSE_R4_____________________
    ),

    [_WT] = LAYOUT_wrapper(
        ________________WINDOWS_TERMINAL_L1________________, ________________WINDOWS_TERMINAL_R1________________,
        ________________WINDOWS_TERMINAL_L2________________, ________________WINDOWS_TERMINAL_R2________________,
        ________________WINDOWS_TERMINAL_L3________________, ________________WINDOWS_TERMINAL_R3________________,
        ________________WINDOWS_TERMINAL_L4________________, ________________WINDOWS_TERMINAL_R4________________
    ),

    [_CN] = LAYOUT_wrapper(
        ___________________CONVENIENCE_L1__________________, ___________________CONVENIENCE_R1__________________,
        ___________________CONVENIENCE_L2__________________, ___________________CONVENIENCE_R2__________________,
        ___________________CONVENIENCE_L3__________________, ___________________CONVENIENCE_R3__________________,
        ___________________CONVENIENCE_L4__________________, ___________________CONVENIENCE_R4__________________
    ),

    [_GG] = LAYOUT_wrapper(
        ________________General_Game_4x12_L1_______________, ________________General_Game_4x12_R1_______________,
        ________________General_Game_4x12_L2_______________, ________________General_Game_4x12_R2_______________,
        ________________General_Game_4x12_L3_______________, ________________General_Game_4x12_R3_______________,
        ________________General_Game_4x12_L4_______________, ________________General_Game_4x12_R4_______________
    ),

    [_CS] = LAYOUT_wrapper(
        ___________________CSGO_4x12_L1____________________, ___________________CSGO_4x12_R1____________________,
        ___________________CSGO_4x12_L2____________________, ___________________CSGO_4x12_R2____________________,
        ___________________CSGO_4x12_L3____________________, ___________________CSGO_4x12_R3____________________,
        ___________________CSGO_4x12_L4____________________, ___________________CSGO_4x12_R4____________________
    )
};
