/* Copyright 2021 Vincent Santillo (vincentsantillo@gmail.com)
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

// Define Tap Dance Macros
#define TD_CAPS CTL_T(KC_CAPS)  // I forget why I need to do this but I'm doing it anyway, I think it's related to tap dances
#define TD_LS TD(TD_LSCP)  // Left Space Cadet Pro Tap Dance
#define TD_RS TD(TD_RSCP)  // Right Space Cadet Pro Tap Dance
#define TD_QM TD(TD_QUICK_MUTE) // Quick Mute Tap Dance

// Define Layer Macros
#define L_SFN LT(MO(SPACEFN), KC_SPACE) // SpaceFN
#define L_FN1 MO(FN1) // FN1
#define L_WIND TG(WINDOWS) // Toggle Windows layer
#define L_GAME TG(GAME)  // Toggle Game mode

// Keyboard layers
enum dz60rgb_layers {
    BASE,  // Base (intended for Mac)
    WINDOWS, // Windows
    SPACEFN, // SpaceFN layer
    FN1, // FN1
    GAME,  // Gaming Layer (disables SpaceFN, and Windows Key)
    BLANK,  // Blank (Transparent) Layer
    NOOP,  // No operation Layer
};

// Tap dances
enum tap_dances {
    TD_LSCP,
    TD_RSCP,
    TD_QUICK_MUTE,
    TD_QUICK_UNDO,
    TD_QUICK_REDO,
};
