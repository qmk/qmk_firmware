/* Copyright 2021 Aaron VerDow
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

#include QMK_KEYBOARD_H

// Layer declarations
enum {
    DEF_LAYER,
    MOD_LAYER,
};

// Tap Dance declarations
enum {
    TD_CAR,
    TD_PRINT,
    TD_CAM_UP,
    TD_CAM_DN
};

void camera_number(uint16_t tens, uint16_t ones) {
/* Switch to a specific camera number
 *
 * I haven't been able to find official docs for this.
 *
 * To determine the number click the dropdown in UI and 
 * count from the top.  The list can change with updates.
 *
 * Shift must be held between both * presses or the combo
 * won't be recognized.
 */

    register_code16(KC_LSFT);
    tap_code(KC_8);
    tap_code(KC_8);
    unregister_code16(KC_LSFT);
    tap_code(tens);
    tap_code(ones);
    tap_code(KC_ENT);
}

void cam_up(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:                     
            tap_code(KC_C);             // tap once for next cam
            break;
        case 2:                     
            camera_number(KC_2,KC_0); // tap twice for reverse chase cam
            break;
    }
}

void cam_down(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:                     
            tap_code16(LSFT(KC_C));     // tap once for prev cam
            break;
        case 2:                     
            camera_number(KC_1,KC_8); // tap twice for chase cam
            break;
    }
}

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_CAR] = ACTION_TAP_DANCE_DOUBLE(
        LSFT(KC_V),                 // tap once for prev car
        LCTL(KC_V)                  // tap twice for my car
    ),
    [TD_PRINT] = ACTION_TAP_DANCE_DOUBLE(
        LCTL(LALT(LSFT(KC_S))),     // tap once for iRacing screenshot (must be enabled in options)
        LGUI(KC_PSCR)               // tap twice for Windows print screen and save to file
    ),
    [TD_CAM_UP] = ACTION_TAP_DANCE_FN(cam_up),
    [TD_CAM_DN] = ACTION_TAP_DANCE_FN(cam_down)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [DEF_LAYER] = LAYOUT_ortho_6x4( /* Base */

    TD(TD_CAM_UP),  // next cam, double tap for reverse chase cam
    KC_V,           // next car
    LSFT(KC_P3),    // next lap
    LCTL(KC_P3),    // next inc

    TD(TD_CAM_DN),  // prev cam, double tap for chase cam
    TD(TD_CAR),     // prev car, double tap for my car
    LSFT(KC_P1),    // prev lap
    LCTL(KC_P1),    // prev inc

    LSFT(KC_P4),    // rewind
    KC_P5,          // play/pause
    LSFT(KC_P6),    // fast forward
    KC_P8,          // slow mo

    KC_P4,          // prev frame
    KC_W,           // up
    KC_P6,          // next frame
    TD(TD_PRINT),   // print screen

    KC_A,           // left
    KC_S,           // down
    KC_D,           // right
    LALT(KC_K),     // toggle click and drag ui elements (in car)

    KC_LCTL,        // ctrl 
    KC_LALT,        // alt
    LCTL(KC_F12),   // camera tool
    LT(MOD_LAYER, KC_SPACE)        // press once for UI, hold for MOD layer
  ),

  [MOD_LAYER] = LAYOUT_ortho_6x4( /* Base */

    KC_B,           // next sub cam
    KC_PGUP,        // next driver cam
    LCTL(KC_P6),    // next session
    KC_P7,          // start

    LSFT(KC_B),     // prev sub cam
    KC_PGDOWN,      // prev driver cam
    LCTL(KC_P4),    // prev session
    KC_P1,          // end

    KC_RBRC,        // FOV up
    KC_EQL,         // step factor up 
    _______,
    _______,

    KC_LBRC,        // FOV down
    KC_MINS,        // step factor down
    _______,
    _______,

    _______,
    _______,
    _______,
    _______,

    _______,
    LALT(KC_M),     // cycle aim
    RALT(KC_ENTER), // fullscreen (unreliable)
    _______
  ),
};
