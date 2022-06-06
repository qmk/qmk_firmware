/* Copyright 2022 Guilherme Bermêo (bermeo.dev)
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
extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
// Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

enum layers { _QWERTY, _LOWER, _RAISE, _NUMP };

uint8_t mod_state;


enum my_keycodes {
    RMT = SAFE_RANGE,
    RMS,
    RMIH,
    RMDH,
    RMIS,
    RMDS,
    RMIV,
    RMDV,
    CEDILHA,
    ASPAS,
    AO
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT_planck_mit(
        LCTL_T(KC_F3),   KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_GRAVE,
        LALT_T(KC_TAB),  KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_ENTER,
        LSFT_T(KC_LEFT), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, RGUI_T(KC_RIGHT),
        KC_NO, KC_NO, KC_NO, LGUI_T(KC_DOWN), MO(1), KC_SPC, KC_BSPC, MO(2), RSFT_T(KC_UP), KC_NO, KC_NO
    ),
    [_LOWER] = LAYOUT_planck_mit(
        LCTL_T(KC_F5),  KC_1,    KC_2,    KC_3,  KC_4,     KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_ESCAPE, 
        LALT_T(KC_TAB), KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_ENT,  KC_LBRC, KC_RBRC, KC_BSLS, KC_QUOT, KC_COLON, KC_ENT, 
        LALT(KC_LEFT),  KC_F1,   KC_F2,   KC_C,  KC_V,     KC_BSPC, KC_MINS, KC_EQL,  KC_LT,   KC_GT,   KC_QUESTION, LALT(KC_RIGHT),
        KC_NO, KC_NO, KC_NO, LGUI_T(KC_PAGE_DOWN), KC_NO, KC_SPC, LALT(KC_BSPC), TG(3), RSFT_T(KC_PAGE_UP), KC_NO, KC_NO
    ),
    [_RAISE] = LAYOUT_planck_mit(
        LCTL_T(KC_F4),  KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILDE,
        LALT_T(KC_TAB), AO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_LCBR, KC_RCBR, KC_PIPE,  ASPAS,  KC_COLON, KC_ENT,
        LALT(KC_LEFT), KC_NO, KC_NO, CEDILHA, KC_NO, KC_NO, KC_UNDS, KC_PLUS,  KC_LT,    KC_GT, KC_QUESTION, LALT(KC_RIGHT),
        KC_NO, KC_NO, KC_NO, LGUI_T(KC_END), TG(3), KC_SPC, KC_DEL, KC_NO, RSFT_T(KC_HOME), KC_NO, KC_NO
    ),
    [_NUMP] = LAYOUT_planck_mit(
        RMT,  RMS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_P7,   KC_P8,  KC_P9,  KC_PAST, KC_PSLS,
        KC_NO,  RMIH, RMIS, RGB_VAI, RMIV, KC_NO, KC_NO,  KC_P4,   KC_P5,  KC_P6,  KC_PMNS,  KC_ENT,
        KC_NO,  RMDH, RMDS, RGB_VAD, RMDV, KC_NO, KC_PDOT,  KC_P1,   KC_P2,  KC_P3,  KC_PPLS,   KC_NO,
        RESET, KC_NO, KC_NO, TG(3),    TG(3),   TG(3),     KC_BSPC,  TG(3),   KC_P0, KC_NO, KC_NO
    ),
};

int RGB_current_mode;

void matrix_init_user(void) {
#ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
#endif
}

//Per key lights
void rgb_matrix_indicators_user(void) {
#ifdef RGB_MATRIX_ENABLE
    switch (biton32(layer_state)) {
        case _QWERTY:
            mod_state  = get_mods();
            for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
                if (mod_state & MOD_MASK_SHIFT) {
                    rgb_matrix_set_color(23, 255, 255, 255);
                    rgb_matrix_set_color(i, 255, 150, 0);
                } else if (mod_state & MOD_MASK_GUI || mod_state & MOD_MASK_CTRL) {
                    rgb_matrix_set_color(7, 255, 0, 0);         // ctrl + U white (uncomment for desktop remote)
                    rgb_matrix_set_color(20, 255, 0, 0);        // ctrl + K white (comment for desktop remote)
                    rgb_matrix_set_color(27, 255, 0, 0);        // C key red
                    switch (i) {
                        case 2:                                 // cmd + W white (close tab)
                        case 5:                                  // cmd + T white (new tab)
                        case 13:                                 // cmd + A white (select all)
                        case 14:                                 // cmd + S white (save)
                        case 16:                                 // cmd + F white (find)
                        case 25:                                 // cmd + Z white (undo)
                        case 34:                                 // cmd + / white (comment line)
                            rgb_matrix_set_color(i, 255, 255, 255); // white
                            break;
                    }
                    if (mod_state & MOD_MASK_GUI) {
                        rgb_matrix_set_color(26, 255, 255, 255); // white X key
                        rgb_matrix_set_color(27, 255, 255, 255); // white C key
                        rgb_matrix_set_color(28, 255, 255, 255); // white V key
                    } else {
                    }
                } else if (mod_state & MOD_MASK_ALT) {
                } else {
                    rgb_matrix_set_color(39, 0, 0, 0);          // command key off
                }
            }
            rgb_matrix_set_color(40, 23, 181, 255);             // cyan layer
            rgb_matrix_set_color(43, 255, 33, 0);               // orange layer
            break;

        case _RAISE:
            for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
                switch (i) {
                    case 14 ... 17:                             // SDFG keys off
                    case 25:                                    // Z key off
                    case 26:                                    // X key off
                    case 28:                                    // V key off
                    case 29:                                    // B key off
                        rgb_matrix_set_color(i, 0, 0, 0);       // off
                        break;
                    case 27:                                    // Ç key
                    case 13:                                    // Ã key
                    case 0:                                    // Launch (F4)
                    case 43:                                    // Active layer
                        rgb_matrix_set_color(i, 255, 255, 255); // white
                        break;
                    case 40:                                    // active numpad layer
                        rgb_matrix_set_color(i, 0, 255, 0);     // green
                        break;
                    case 22:                                    // ; shifted key
                    case 32 ... 34:                             // ,./ shifted keys
                        rgb_matrix_set_color(i, 255, 214, 0);   // yellow
                        break;
                    default:
                        rgb_matrix_set_color(i, 255, 33, 0);    // orange
                }
            }
            break;

        case _LOWER:
            for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
                switch (i) {
                    case 11:                                    // ESC key
                    case 29:                                    // Delete key on B
                        rgb_matrix_set_color(i, 255, 0, 0);     // red
                        break;
                    case 25 ... 28:                             // ZXCV keys off
                        rgb_matrix_set_color(i, 0, 0, 0);       // off
                        break;
                    case 0:                                    // Print    
                    case 13 ... 16:                             // ASDF arrow keys
                    case 40:                                    // Active layer
                        rgb_matrix_set_color(i, 255, 255, 255); // white
                        break;
                    case 17:                                     // Enter key on G
                    case 43:                                    // Activate Numpad
                        rgb_matrix_set_color(i, 0, 255, 0);     // green
                        break;
                    case 22:                                    // ; shifted key
                    case 32 ... 34:                             // ,./ shifted keys
                        rgb_matrix_set_color(i, 255, 214, 0);   // yellow
                        break;
                    default:
                        rgb_matrix_set_color(i, 23, 181, 255);  // cyan
                }
            }

            break;

        case _NUMP:
            for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
                switch (i) {
                    case 11:                                    // Numpad /
                    case 22:                                    // Numpad -
                    case 25 ... 28:                             // ZXCV keys
                        rgb_matrix_set_color(i, 255, 0, 0);     // red
                        break;
                    case 1 ... 6:                              // QWERTY keys off
                    case 17 ... 18:                            // GH keys off
                        rgb_matrix_set_color(i, 0, 0, 0);       // off
                        break;
                    case 7 ... 9:                               // Numpad numbers row 1
                    case 19 ... 21:                             // Numpad numbers row 2
                    case 31 ... 33:                             // Numpad numbers row 3
                    case 23:                                    // Enter key
                        rgb_matrix_set_color(i, 255, 255, 255); // white
                        break;
                    case 13:                                    // RGB speed+
                    case 14:                                    // RGB saturation+
                    case 16:                                    // RGB hue+
                    case 34:                                    // Numpad +
                        rgb_matrix_set_color(i, 0, 255, 0);     // green
                        break;
                    case 30:                                    // . numpad key
                        rgb_matrix_set_color(i, 255, 214, 0);   // yellow
                        break;
                }
                rgb_matrix_set_color(40, 23, 181, 255);         // Activate cyan layer
                rgb_matrix_set_color(43, 255, 33, 0);           // Activate orange layer
                rgb_matrix_set_color(10, 0, 33, 255);           // Numpad *
            }
    }
};
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case RMT:
      if (record->event.pressed)
      {rgb_matrix_toggle();
      }
      return false;
    case RMS:
      if (record->event.pressed)
      {rgb_matrix_step();
      }
      return false;
      case RMIH:
      if (record->event.pressed)
      {rgb_matrix_increase_hue();
      }
      return false;
      case RMDH:
      if (record->event.pressed)
      {rgb_matrix_decrease_hue();
      }
      return false;
      case RMIS:
      if (record->event.pressed)
      {rgb_matrix_increase_sat();
      }
      return false;
      case RMDS:
      if (record->event.pressed)
      {rgb_matrix_decrease_sat();
      }
      return false;

      case RMIV:
      if (record->event.pressed)
      {rgb_matrix_increase_val();
      }
      return false;

      case RMDV:
      if (record->event.pressed)
      {rgb_matrix_decrease_val();
      }
      return false;
      case CEDILHA:
        if (record->event.pressed) {
            register_code(KC_QUOT);
            unregister_code(KC_QUOT);
            register_code(KC_C);
            unregister_code(KC_C);
        }
        break;
        return false;

    // ã key
      case AO:
        if (record->event.pressed) {
            register_code(KC_LSFT);
            register_code(KC_GRV);
            unregister_code(KC_LSFT);
            unregister_code(KC_GRV);
            register_code(KC_A);
            unregister_code(KC_A);
        }
        break;
        return false;

    // direct " key
      case ASPAS:
        if (record->event.pressed) {
            register_code(KC_LSFT);
            register_code(KC_QUOT);
            register_code(KC_SPC);
            unregister_code(KC_SPC);
            unregister_code(KC_QUOT);
            unregister_code(KC_LSFT);
        }
        break;
        return false;  
  }
  return true;
}