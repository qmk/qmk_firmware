#include QMK_KEYBOARD_H

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

// Defines macros for use with the configurators "Any" key.
#define KC_CSGRA  LCTL(LSFT(LGUI(KC_RGHT)))
#define KC_CSGLA  LCTL(LSFT(LGUI(KC_LEFT)))
#define KC_MAXIM  LCTL(LSFT(LGUI(KC_UP)))
#define KC_MINIM  LCTL(LSFT(LGUI(KC_DOWN)))

// Rotary encoder variables used to hold down Command (GUI) key while cycling through open programs.
bool is_command_tab_active = false;
uint16_t command_tab_timer = 0;

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

// The rotary encoders are programmed manually here, but the other keys can
// use the configurator at https://config.qmk.fm/#/keebio/iris/rev6a/LAYOUT
// Upload two_knob.json, make changes, download json again, run `qmk json2c two_knob.json`
// to regen the keymap. Paste keymap here, reneame keys, `qmk compile` `qmk flash`.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(KC_EQL, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLS, LT(1,KC_DEL), LT(2,KC_A), LCTL_T(KC_S), KC_D, LGUI_T(KC_F), KC_G, KC_H, RGUI_T(KC_J), KC_K, RCTL_T(KC_L), LT(2,KC_SCLN), LT(1,KC_QUOT), KC_LSPO, LALT_T(KC_Z), KC_X, KC_C, KC_V, KC_B, KC_MAXIM, KC_MINIM, KC_N, KC_M, KC_COMM, KC_DOT, RALT_T(KC_SLSH), KC_RSPC, QK_GESC, KC_SPC, KC_BSPC, KC_TAB, KC_ENT, KC_DEL),
  [_LOWER] = LAYOUT(KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_TRNS, KC_EXLM, KC_AT, KC_LCBR, KC_RCBR, KC_PIPE, RGB_TOG, KC_7, KC_8, KC_9, KC_ASTR, KC_F12, KC_TRNS, KC_HASH, KC_DLR, KC_LPRN, KC_RPRN, KC_GRV, RGB_MOD, KC_5, KC_4, KC_6, KC_PPLS, KC_TRNS, KC_TRNS, KC_HASH, KC_DLR, KC_LBRC, KC_RBRC, KC_GRV, KC_TRNS, KC_TRNS, RGB_RMOD, KC_1, KC_2, KC_3, KC_PSLS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P0),
  [_RAISE] = LAYOUT(RGB_TOG, KC_ACL0, KC_ACL1, KC_ACL2, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_MOD, RGB_RMOD, RGB_HUI, RGB_HUD, KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_UP, KC_BTN2, RGB_SAI, RGB_SAD, KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, RGB_VAI, RGB_VAD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_SPI, RGB_SPD, KC_TRNS, KC_TRNS, KC_CSGLA, KC_CSGRA, KC_TRNS, KC_TRNS),
  [_ADJUST] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
  }
  return true;
}

/**
 * Rotary Encoder.
 * 
 * This can't be programmed through configurator. You must do it here.
 * 
 * Advanced guide for rotary coder programming found here:
 * https://docs.splitkb.com/hc/en-us/articles/360010513760-How-can-I-use-a-rotary-encoder-
 */
bool encoder_update_user(uint8_t index, bool clockwise) {
  // index 0 is left encoder. (If you only have one knob, this will be it).
  if (index == 0) {
    // Check which layer is active.
    switch(biton32(layer_state)) {
      // Executes on layer 2 only.
      case 2:
        if (clockwise) {
          // Selects words to the right of the cursor. (Command + Shift + Right Arrow).
          tap_code16(C(S(KC_RGHT)));
        } else {
          // Selects words to the left of the cursor. (Command + Shift + Left Arrow).
          tap_code16(C(S(KC_LEFT)));
        }
        break;
      // Executes on layer 1 only.
      case 1:
        if (clockwise) {
          // Scrolls down. (Mouse Wheel Down).
          tap_code(KC_WH_D);
        } else {
          // Scrolls up. (Mouse Wheel Up).
          tap_code(KC_WH_U);
        }
        break;
      // Executes on all other layers.
      default:
        // Note the use of tap_code16 instead of regular tap_code.
        if (clockwise) {
          // Switch between tabs clockwise. (Control + Tab).
          tap_code16(C(KC_TAB));
        } else {
          // Switch between tabs anticlockwise. (Control + Shift + Tab).
          tap_code16(S(C(KC_TAB)));
        }
        break;
    }
  }
  else if (index == 1) {
    // Check which layer is active.
    switch(biton32(layer_state)) {
      // Executes on layer 2 only.
      case 2:
        if (clockwise) {
          // Selects lines to the right. (Control + Shift + Home).
          tap_code16(C(S(KC_HOME)));
        } else {
          // Selects lines to the left. (Control + Shift + End).
          tap_code16(C(S(KC_END)));
        }
        break;
      // Executes on layer 1 only.
      case 1:
        if (clockwise) {
          // Scrolls right. (Shift + Mouse Wheel Up).
          tap_code16(S(KC_WH_U));
        } else {
          // Scrolls left. (Shift + Mouse Wheel Down).
          tap_code16(S(KC_WH_D));
        }
        break;
      default:
        if (clockwise) {
          // Holds down the Command/Gui key if it's not already down.
          if (!is_command_tab_active) {
            is_command_tab_active = true;
            register_code(KC_LGUI);
          }
          // Checks the timer?
          command_tab_timer = timer_read();
          // Hits tab.
          tap_code16(KC_TAB);
        } else {
          if (!is_command_tab_active) {
            is_command_tab_active = true;
            register_code(KC_LGUI);
          }
          command_tab_timer = timer_read();
          tap_code16(S(KC_TAB));
        }
        break;
    }
  }  
  return false;
}

/**
 * Helper function for rotary encoder.
 * 
 * If the timer has elapsed, the Command/Gui tab will be released.
 * 
 * @see encoder_update_user
 */
void matrix_scan_user(void) {
  // Check if the Command/Gui key is currently pressed programatically.
  if (is_command_tab_active) {
    // Will release Command/Gui for you if you haven't send a tab yet in <x> ms.
    if (timer_elapsed(command_tab_timer) > 1050) {
      // Release Command/Gui key.
      unregister_code(KC_LGUI);
      is_command_tab_active = false;
    }
  }
}

