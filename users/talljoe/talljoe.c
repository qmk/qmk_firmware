/* Copyright 2020 Joseph Wasson
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

#include "talljoe.h"

#ifdef ZEAL_RGB
#include "../../../keyboards/wilba_tech/wt_rgb_backlight.h"
#endif

#ifdef VISUALIZER_ENABLE
const char layer_names[32][16] = {
  [_BASE] = "QWERTY",
  [_WORKMAN] = "Workman",
  [_NORMAN] = "Norman",
  [_DVORAK] = "Dvorak",
  [_COLMAK] = "Colmak",
  [_MALTROFF] = "Maltroff",
  [_NORTRON] = "Nortron",
  [_GAME] = "Game",
  [_NAV] = "Navigation",
  [_NUM] = "Numpad",
  [_ADJUST] = "Adjust",
  [_RESET] = "Reset",
};
#endif

__attribute__((weak))
void matrix_scan_keymap(void) {
}

void matrix_scan_user(void) {
  matrix_scan_keymap();

  #ifdef KEYBOARD_gh60
    if (IS_LAYER_ON(_GAME)) {
      gh60_wasd_leds_on();
    } else {
      gh60_wasd_leds_off();
    }
  #endif
}

void matrix_init_user(void) {
  if (!eeconfig_is_enabled()) {
    eeconfig_init();
  }
}

layer_state_t default_layer_state_set_kb(layer_state_t state) {
  // persist changes to default layers
  eeconfig_update_default_layer(state);
  return state;
}

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

#ifdef ZEAL_RGB
extern backlight_config g_config;
#endif
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef ZEAL_RGB
  static uint8_t last_effect;
#endif

#ifdef RGBLIGHT_ENABLE
  static uint32_t savedRgbMode;
  static uint16_t savedHue;
  static uint8_t savedSat;
  static uint8_t savedVal;

  if (keycode == KC_ESC) {
    if (record->event.pressed) {
      savedRgbMode = rgblight_get_mode();
      savedHue = rgblight_get_hue();
      savedSat = rgblight_get_sat();
      savedVal = rgblight_get_val();
      rgblight_mode(1);
      rgblight_setrgb(255, 0, 0);
    } else {
      rgblight_mode(savedRgbMode);
      rgblight_sethsv(savedHue, savedSat, savedVal);
    }
  }
#endif
// If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
  xprintf("KL: row: %u, column: %u, pressed: %u\n", record->event.key.row, record->event.key.col, record->event.pressed);
#endif //CONSOLE_ENABLE

  switch (keycode) {
    case KC_MAKE:  // Compiles the firmware, and adds the flash command based on keyboard bootloader
      if (!record->event.pressed) {
          uint8_t temp_mod = get_mods();
          uint8_t temp_osm = get_oneshot_mods();
          clear_mods(); clear_oneshot_mods();
          SEND_STRING("make " QMK_KEYBOARD ":" QMK_KEYMAP);
#ifndef FLASH_BOOTLOADER
          if ((temp_mod | temp_osm) & MOD_MASK_SHIFT)
#endif
          {
              SEND_STRING(":flash");
          }
          if ((temp_mod | temp_osm) & MOD_MASK_CTRL) {
              SEND_STRING(" -j8 --output-sync");
          }
          tap_code(KC_ENT);
          set_mods(temp_mod);
      }
      return false;
      break;
#ifdef ZEAL_RGB
    case BL_TOGG:
      if (IS_PRESSED(record->event)) {
        if (g_config.effect) {
          last_effect = g_config.effect;
          g_config.effect = 0;
        } else {
          g_config.effect = last_effect;
        }
      }
      return false;
    case EFFECT...EFFECT_END:
      if (IS_PRESSED(record->event)) {
        uint8_t effect = keycode - EFFECT;
        if(effect == g_config.effect)
          effect = 0; // Toggle effect on second press
        g_config.effect = effect;
        backlight_config_save();
      }
      return false;
#endif
  }
  return process_record_keymap(keycode, record);
}
