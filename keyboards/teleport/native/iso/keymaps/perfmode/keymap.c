/* Copyright 2023 Moritz Plattner
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

// tested and working
void matrix_io_delay(void) { __asm__ volatile("nop\nnop\nnop\n"); }

enum layers{
    BASE,
    GAME,
    PERF,
    _FN1,
    _FN2
};

/* Create a keycode to toggle RGB without writing to eeprom, important to enable/disable the non-eeprom-stored custom lighting on PERF layer */
enum my_keycodes {
  RGB_TOG_NO = SAFE_RANGE,
  RGB_M_2,
  RGB_M_3,
  RGB_M_4,
  RGB_M_5,
  RGB_M_6,
  RGB_M_7,
  RGB_M_8,
  RGB_M_9,
  RGB_M_0
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case RGB_TOG_NO:
      if (record->event.pressed) {
        rgb_matrix_toggle_noeeprom();
      }
      return false;
    case RGB_M_2:
      if (record->event.pressed) {
        rgb_matrix_mode(RGB_MATRIX_ALPHAS_MODS);
      }
      return false;
    case RGB_M_3:
      if (record->event.pressed) {
        rgb_matrix_mode(RGB_MATRIX_BREATHING);
      }
      return false;
    case RGB_M_4:
      if (record->event.pressed) {
        rgb_matrix_mode(RGB_MATRIX_CYCLE_UP_DOWN);
      }
      return false;
    case RGB_M_5:
      if (record->event.pressed) {
        rgb_matrix_mode(RGB_MATRIX_CYCLE_ALL);
      }
      return false;
    case RGB_M_6:
      if (record->event.pressed) {
        rgb_matrix_mode(RGB_MATRIX_CYCLE_SPIRAL);
      }
      return false;
    case RGB_M_7:
      if (record->event.pressed) {
        rgb_matrix_mode(RGB_MATRIX_TYPING_HEATMAP);
      }
      return false;
    case RGB_M_8:
      if (record->event.pressed) {
        rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE);
      }
      return false;
    case RGB_M_9:
      if (record->event.pressed) {
        rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE);
      }
      return false;
    case RGB_M_0:
      if (record->event.pressed) {
        rgb_matrix_mode(RGB_MATRIX_CUSTOM_SINGLE_COLOR_RAINDROPS);
      }
      return false;
    default:
      return true; // Process all other keycodes normally
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [BASE] = LAYOUT_75_iso(    /* keymap for layer 0 */
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, KC_F13, KC_PSCR,   KC_DEL,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,       KC_BSPC,     KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,                   KC_PGDN,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS,      KC_ENT,      KC_HOME,
        KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(_FN1),KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [GAME] = LAYOUT_75_iso(    /* keymap for layer 1 - GAME disables WIN key and has RGB layer indicators */
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,     KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,     KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,
        KC_TRNS, KC_NO,   KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [PERF] = LAYOUT_75_iso(    /* keymap for layer 2 - PERF has a static LED display to increase matrix scan rates */
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,     KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,     KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,
        KC_TRNS, KC_NO,   KC_TRNS,                            KC_TRNS,                            KC_TRNS, MO(_FN2),KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [_FN1] = LAYOUT_75_iso(    /* keymap for layer 3 */
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_TOG, RGB_VAD, RGB_VAI, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLD, KC_VOLU, KC_MUTE, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, RGB_M_P, RGB_M_2, RGB_M_3, RGB_M_4, RGB_M_5, RGB_M_6, RGB_M_7, RGB_M_8, RGB_M_9, RGB_M_0, KC_TRNS, KC_TRNS,      KC_TRNS,     KC_TRNS,
        RGB_TOG, RGB_VAI, RGB_HUI, RGB_SAI, RGB_SPI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,
        KC_TRNS, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,     KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MAGIC_TOGGLE_NKRO,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, TG(GAME),KC_TRNS,                            TO(PERF),                           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [_FN2] = LAYOUT_75_iso(    /* keymap for layer 4 */
        KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, RGB_TOG_NO,KC_NO, KC_NO,   KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLD, KC_VOLU, KC_MUTE, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS, KC_TRNS,      KC_TRNS,     KC_TRNS,
        RGB_TOG_NO,KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,
        KC_TRNS,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,     KC_TRNS,
        KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,
        KC_TRNS,   KC_NO,   KC_TRNS,                            TG(PERF),                           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
};

/* RGB matrix indicator code
It reads the current matrix color, offsets the hue by 30, 
and sets val to RGB_MATRIX_MAXIMUM_BRIGHTNESS (by default, 255)
This is applied to both caps lock, and other indicator keys for layer 1 */

bool rgb_matrix_indicators_user(void) {
  /* Layer 2 (perf mode on this keymap) is not supposed to have LED refreshes, hence excluded */
  if (!IS_LAYER_ON(2)) {
    HSV hsv_ind = {rgb_matrix_get_hue()+30,255,RGB_MATRIX_MAXIMUM_BRIGHTNESS};
    RGB rgb_ind = hsv_to_rgb(hsv_ind);

    /* Sets Caps to different color as indicator. If RGB mode is rain, and caps indicator is off, the LED will always be off.
    This is to avoid having the LED persist on until the animation randomly refreshes it. */
    if (host_keyboard_led_state().caps_lock) {
      rgb_matrix_set_color(CAPS_LED_INDEX, rgb_ind.r, rgb_ind.g, rgb_ind.b);
    } else if (rgb_matrix_get_mode() == 10) {
      rgb_matrix_set_color(CAPS_LED_INDEX, 0, 0, 0);
    }

    /* Sets W, A, S, D, LGUI to a different color as layer indicator */
    if(IS_LAYER_ON(1)) {
      HSV hsv_ind = {rgb_matrix_get_hue()+30,255,RGB_MATRIX_MAXIMUM_BRIGHTNESS};
      RGB rgb_ind = hsv_to_rgb(hsv_ind);

      rgb_matrix_set_color(W_LED_INDEX, rgb_ind.r, rgb_ind.g, rgb_ind.b);
      rgb_matrix_set_color(A_LED_INDEX, rgb_ind.r, rgb_ind.g, rgb_ind.b);
      rgb_matrix_set_color(S_LED_INDEX, rgb_ind.r, rgb_ind.g, rgb_ind.b);
      rgb_matrix_set_color(D_LED_INDEX, rgb_ind.r, rgb_ind.g, rgb_ind.b);
      rgb_matrix_set_color(WIN_LED_INDEX, rgb_ind.r, rgb_ind.g, rgb_ind.b);
    }
  }
  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  /* Set LEDs to "GAME_MODE" custom animation when entering layer 2 (perf mode), reload matrix from eeprom when exiting */
  if(IS_LAYER_ON_STATE(state, 2)) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_STATIC_GAME_MODE);
  } else {
    rgb_matrix_reload_from_eeprom();
  }
    
  /* If reverting to base layer (no special LED effects) and single color rain is on, set "layer 1" mods back to matrix color to avoid single key persistence */
  if(!IS_LAYER_ON_STATE(state, 2) && !IS_LAYER_ON_STATE(state, 1) && rgb_matrix_get_mode() == 10) {
    HSV hsv_mat = rgb_matrix_get_hsv();
    RGB rgb_mat = hsv_to_rgb(hsv_mat);

    rgb_matrix_set_color(W_LED_INDEX, rgb_mat.r, rgb_mat.g, rgb_mat.b);
    rgb_matrix_set_color(A_LED_INDEX, rgb_mat.r, rgb_mat.g, rgb_mat.b);
    rgb_matrix_set_color(S_LED_INDEX, rgb_mat.r, rgb_mat.g, rgb_mat.b);
    rgb_matrix_set_color(D_LED_INDEX, rgb_mat.r, rgb_mat.g, rgb_mat.b);
    rgb_matrix_set_color(WIN_LED_INDEX, rgb_mat.r, rgb_mat.g, rgb_mat.b);
  }
  return state;
}
