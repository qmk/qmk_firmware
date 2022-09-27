/* Copyright 2021 Andrzej Ressel (andrzej.ressel@gmail.com)
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



enum custom_keycodes {
  TOP_LEFT = SAFE_RANGE,
  TOP_RIGHT,
  BOTTOM_LEFT,
  BOTTOM_RIGHT,
  TOP_LEFT_SIXTH,
  TOP_CENTRE_SIXTH,
  TOP_RIGHT_SIXTH,
  BOTTOM_LEFT_SIXTH,
  BOTTOM_CENTRE_SIXTH,
  BOTTOM_RIGHT_SIXTH,
  LEFT_THIRD,
  CENTRE_THIRD,
  RIGHT_THIRD,
  PREVIOUS_DISPLAY,
  NEXT_DISPLAY,
  CENTRE,
  MUTE_ZOOM
};

enum combos { 
  TOP_LEFT_SIXTH_TOP_CENTRE_SIXTH_TOP_LEFT,
  TOP_CENTRE_SIXTH_TOP_RIGHT_SIXTH_TOP_RIGHT,
  BOTTOM_LEFT_SIXTH_BOTTOM_CENTRE_SIXTH_BOTTOM_LEFT,
  BOTTOM_CENTRE_SIXTH_BOTTOM_RIGHT_SIXTH_BOTTOM_RIGHT,
  TOP_LEFT_SIXTH_BOTTOM_LEFT_SIXTH_LEFT_THIRD,
  TOP_CENTRE_SIXTH_BOTTOM_CENTRE_SIXTH_CENTRE_THIRD,
  TOP_RIGHT_SIXTH_BOTTOM_RIGHT_SIXTH_RIGHT_THIRD,
  
};

const uint16_t PROGMEM top_left_sixth_top_centre_sixth_top_left[] = { TOP_LEFT_SIXTH, TOP_CENTRE_SIXTH, COMBO_END};
const uint16_t PROGMEM top_centre_sixth_top_right_sixth_top_right[] = { TOP_CENTRE_SIXTH, TOP_RIGHT_SIXTH, COMBO_END};
const uint16_t PROGMEM bottom_left_sixth_bottom_centre_sixth_bottom_left[] = { BOTTOM_LEFT_SIXTH, BOTTOM_CENTRE_SIXTH, COMBO_END};
const uint16_t PROGMEM bottom_centre_sixth_bottom_right_sixth_bottom_right[] = { BOTTOM_CENTRE_SIXTH, BOTTOM_RIGHT_SIXTH, COMBO_END};
const uint16_t PROGMEM top_left_sixth_bottom_left_sixth_left_third[] = { TOP_LEFT_SIXTH, BOTTOM_LEFT_SIXTH, COMBO_END};
const uint16_t PROGMEM top_centre_sixth_bottom_centre_sixth_centre_third[] = { TOP_CENTRE_SIXTH, BOTTOM_CENTRE_SIXTH, COMBO_END};
const uint16_t PROGMEM top_right_sixth_bottom_right_sixth_right_third[] = { TOP_RIGHT_SIXTH, BOTTOM_RIGHT_SIXTH, COMBO_END};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case TOP_LEFT:
        if (record->event.pressed) {
            // Left ctrl, left alt, u
            SEND_STRING(SS_LCTL(SS_LALT("u")));
         } else {
        }
        break;
    case TOP_RIGHT:
        if (record->event.pressed) {
            // Left ctrl, left alt, i
            SEND_STRING(SS_LCTL(SS_LALT("i")));
         } else {
        }
        break;
    case BOTTOM_LEFT:
        if (record->event.pressed) {
            // Left ctrl, left alt, j
            SEND_STRING(SS_LCTL(SS_LALT("j")));
         } else {
        }
        break;
    case BOTTOM_RIGHT:
        if (record->event.pressed) {
            // Left ctrl, left alt, k
            SEND_STRING(SS_LCTL(SS_LALT("k")));
         } else {
        }
        break;
    case TOP_LEFT_SIXTH:
        if (record->event.pressed) {
            // Left ctrl, left alt, 1
            SEND_STRING(SS_LCTL(SS_LALT("1")));
         } else {
        }
        break;
    case TOP_CENTRE_SIXTH:
        if (record->event.pressed) {
            // Left ctrl, left alt, 2
            SEND_STRING(SS_LCTL(SS_LALT("2")));
         } else {
        }
        break;
    case TOP_RIGHT_SIXTH:
        if (record->event.pressed) {
            // Left ctrl, left alt, 3
            SEND_STRING(SS_LCTL(SS_LALT("3")));
         } else {
        }
        break;
    case BOTTOM_LEFT_SIXTH:
        if (record->event.pressed) {
            // Left ctrl, left alt, 4
            SEND_STRING(SS_LCTL(SS_LALT("4")));
         } else {
        }
        break;
    case BOTTOM_CENTRE_SIXTH:
        if (record->event.pressed) {
            // Left ctrl, left alt, 5
            SEND_STRING(SS_LCTL(SS_LALT("5")));
         } else {
        }
        break;
    case BOTTOM_RIGHT_SIXTH:
        if (record->event.pressed) {
            // Left ctrl, left alt, 6
            SEND_STRING(SS_LCTL(SS_LALT("6")));
         } else {
        }
        break;
    case LEFT_THIRD:
        if (record->event.pressed) {
            // Left ctrl, left alt, d
            SEND_STRING(SS_LCTL(SS_LALT("d")));
         } else {
        }
        break;
    case CENTRE_THIRD:
        if (record->event.pressed) {
            // Left ctrl, left alt, f
            SEND_STRING(SS_LCTL(SS_LALT("f")));
         } else {
        }
        break;
    case RIGHT_THIRD:
        if (record->event.pressed) {
            // Left ctrl, left alt, g
            SEND_STRING(SS_LCTL(SS_LALT("g")));
         } else {
        }
        break;
    case PREVIOUS_DISPLAY:
        if (record->event.pressed) {
            // Left GUI (CMD), left ctrl, left alt left arrow
            SEND_STRING(SS_LGUI(SS_LCTL(SS_LALT(SS_TAP(X_LEFT)))));
         } else {
        }
        break;
    case NEXT_DISPLAY:
        if (record->event.pressed) {
            // Left GUI (CMD), left ctrl, left alt, right arrow
            SEND_STRING(SS_LGUI(SS_LCTL(SS_LALT(SS_TAP(X_RIGHT)))));
         } else {
        }
        break;
    case CENTRE:
        if (record->event.pressed) {
            // Left ctrl, left alt, c
            SEND_STRING(SS_LCTL(SS_LALT("c")));
         } else {
        }
        break;
    case MUTE_ZOOM:
        if (record->event.pressed) {
            // Left GUI (CMD), left shift, a
            SEND_STRING(SS_LGUI(SS_LSFT("a")));
         } else {
        }
        break;
    }
    return true;
};

combo_t key_combos[COMBO_COUNT] = {
  [TOP_LEFT_SIXTH_TOP_CENTRE_SIXTH_TOP_LEFT] = COMBO(top_left_sixth_top_centre_sixth_top_left, TOP_LEFT),
  [TOP_CENTRE_SIXTH_TOP_RIGHT_SIXTH_TOP_RIGHT] = COMBO(top_centre_sixth_top_right_sixth_top_right, TOP_RIGHT),
  [BOTTOM_LEFT_SIXTH_BOTTOM_CENTRE_SIXTH_BOTTOM_LEFT] = COMBO(bottom_left_sixth_bottom_centre_sixth_bottom_left, BOTTOM_LEFT),
  [BOTTOM_CENTRE_SIXTH_BOTTOM_RIGHT_SIXTH_BOTTOM_RIGHT] = COMBO(bottom_centre_sixth_bottom_right_sixth_bottom_right, BOTTOM_RIGHT),
  [TOP_LEFT_SIXTH_BOTTOM_LEFT_SIXTH_LEFT_THIRD] = COMBO(top_left_sixth_bottom_left_sixth_left_third, LEFT_THIRD),
  [TOP_CENTRE_SIXTH_BOTTOM_CENTRE_SIXTH_CENTRE_THIRD] = COMBO(top_centre_sixth_bottom_centre_sixth_centre_third, CENTRE_THIRD),
  [TOP_RIGHT_SIXTH_BOTTOM_RIGHT_SIXTH_RIGHT_THIRD] = COMBO(top_right_sixth_bottom_right_sixth_right_third, RIGHT_THIRD),
  
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT(
        TOP_LEFT_SIXTH,     TOP_CENTRE_SIXTH,       TOP_RIGHT_SIXTH,        KC_SCROLL_LOCK,     KC_PAUSE,
        BOTTOM_LEFT_SIXTH,  BOTTOM_CENTRE_SIXTH,    BOTTOM_RIGHT_SIXTH,     KC_KB_VOLUME_DOWN,  KC_KB_VOLUME_UP,
        CENTRE,             PREVIOUS_DISPLAY,       NEXT_DISPLAY,           KC_PENT,            RGB_MOD,
        KC_P1,              KC_P2,                  KC_P3,                  KC_UP,              KC_UP,
        KC_P0,              KC_PDOT,                KC_LEFT,                KC_DOWN,            MUTE_ZOOM
    )
};
