/* Copyright 2020 elmo-space<mail@elmo.space>
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
#include "rgblite.h"

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FUNC,
};

// set your keycodes here
#define layer1_left  KC_PAUS
#define layer1_right KC_MPLY
#define layer2_left  KC_MPRV
#define layer2_right KC_MNXT


enum custom_keycodes {
  LEFT1 = SAFE_RANGE,
  RIGHT1,
  LEFT2,
  RIGHT2
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    LEFT1,  RIGHT1
  ),
  [_FUNC] = LAYOUT(
    LEFT2,  RIGHT2
  )
};

static bool key1_down = false;
static bool key2_down = false;
static char layer_switched = 0; // this prevents the individual keys getting triggered after a layerchange

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode)
    {
    case LEFT1:
        if (record->event.pressed)
        {
            if (key2_down)
            {
                layer_on(1);
                layer_switched = 2;
                return false;
                break;
            }
            key1_down = true;
        }
        else {
            if (layer_switched > 0) {
                --layer_switched;
                key1_down = false;
            }
            else {
                tap_code(layer1_left);
                key1_down = false;
            }
        }
        return false;
        break;
    case RIGHT1:
        if (record->event.pressed)
        {
            if (key1_down)
            {
                layer_on(1);
                layer_switched = 2;
                return false;
                break;
            }
            key2_down = true;
        }
        else {
            if (layer_switched > 0) {
                --layer_switched;
                key2_down = false;
            }
            else {
                tap_code(layer1_right);
                key2_down = false;
            }
        }
        return false;
        break;
    case LEFT2:
        if (record->event.pressed)
        {
            if (key2_down)
            {
                layer_off(1);
                layer_switched = 2;
                return false;
                break;
            }
            key1_down = true;
        }
        else {
            if (layer_switched > 0) {
                --layer_switched;
                key1_down = false;
            }
            else {
                tap_code(layer2_left);
                key1_down = false;
            }
        }
        return false;
        break;
    case RIGHT2:
        if (record->event.pressed)
        {
            if (key1_down)
            {
                layer_off(1);
                layer_switched = 2;
                return false;
                break;
            }
            key2_down = true;
        }
        else {
            if (layer_switched > 0) {
                --layer_switched;
                key2_down = false;
            }
            else {
                tap_code(layer2_right);
                key2_down = false;
            }
        }
        return false;
        break;
    }
    return true;
};

// layer colors
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _FUNC:
        rgblight_setrgb_red();
        break;
    default: //  for any other layers, or the default layer
        rgblight_setrgb_green();
        break;
    }
  return state;
}

// default color
void keyboard_post_init_user(void) {
    rgblight_setrgb_green();
}
