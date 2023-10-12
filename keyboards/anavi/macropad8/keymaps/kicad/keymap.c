 /* Copyright 2020 Leon Anavi <leon@anavi.org>
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

#define _SCH 0
#define _PCB 1
#define _FN 2

#define KC_X0 LT(_FN, KC_ESC)

#ifdef RGBLIGHT_ENABLE
// How long (in ms) to wait between animation steps for the rainbow mode
const uint8_t RGBLED_RAINBOW_MOOD_INTERVALS[] PROGMEM = {60, 30, 15};
// How long (in milliseconds) to wait between animation steps for each of the "Swirling rainbow" animations
const uint8_t RGBLED_RAINBOW_SWIRL_INTERVALS[] PROGMEM = {20, 10, 4};
#endif

/*
 * The keymap contains 2 layers for KiCad hotkeys and a 3rd layer
 * for controlling the backlighting and the underlighting.
 *
 * - Layer for KiCad Schematic hotkeys:
 * m - to move selected component
 * r - to rotate selected component
 * w - to wire components
 * v - to edit component value
 * F1 - zoom in
 * F2 - zoom out
 * F4 - zoom center
 *
 * - Layer for KiCad PCB layout hotkets:
 * m - to move selected component
 * r - to rotate selected component
 * x - to route a new track
 * v - to add a via
 * F1 - zoom in
 * F2 - zoom out
 * F4 - zoom center
 *
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_SCH] = LAYOUT_ortho_2x4(
     KC_M, KC_R, KC_W, KC_V,
     KC_F1, KC_F2, KC_F4, TO(_PCB)
  ),

  [_PCB] = LAYOUT_ortho_2x4(
     KC_M, KC_R, KC_X, KC_V,
     KC_F1, KC_F2, KC_F4, TO(_FN)
  ),

  [_FN] = LAYOUT_ortho_2x4(
     RGB_TOG, RGB_MOD, RGB_M_R, RGB_M_SN,
     BL_TOGG, BL_STEP, BL_BRTG, TO(_SCH)
  )
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
}

bool oled_task_user(void) {
  // Host Keyboard Layer Status
  oled_write_ln_P(PSTR("ANAVI Macro Pad 8"), false);
  oled_write_P(PSTR("Layer: "), false);

  switch (get_highest_layer(layer_state)) {
    case _SCH:
      oled_write_ln_P(PSTR("KiCad Schema"), false);
      break;
    case _PCB:
      oled_write_ln_P(PSTR("KiCad PCB"), false);
      break;
    case _FN:
      oled_write_ln_P(PSTR("FN "), false);
      break;
    default:
      // Or use the write_ln shortcut over adding '\n' to the end of your string
      oled_write_ln_P(PSTR("N/A"), false);
  }

  // Host Keyboard LED Status
  led_t led_state = host_keyboard_led_state();
  oled_write_P(PSTR("Num Lock: "), false);
  oled_write_ln_P(led_state.num_lock ? PSTR("On") : PSTR("Off"), false);
  oled_write_P(PSTR("Caps Lock: "), false);
  oled_write_ln_P(led_state.caps_lock ? PSTR("On") : PSTR("Off"), false);
  oled_write_P(PSTR("Scroll Lock: "), false);
  oled_write_ln_P(led_state.scroll_lock ? PSTR("On") : PSTR("Off"), false);
  oled_write_P(PSTR("Backlit: "), false);
  oled_write_ln_P(is_backlight_enabled() ? PSTR("On") : PSTR("Off"), false);
#ifdef RGBLIGHT_ENABLE
  static char rgbStatusLine1[26] = {0};
  snprintf(rgbStatusLine1, sizeof(rgbStatusLine1), "RGB Mode: %d", rgblight_get_mode());
  oled_write_ln(rgbStatusLine1, false);
  static char rgbStatusLine2[26] = {0};
  snprintf(rgbStatusLine2, sizeof(rgbStatusLine2), "h:%d s:%d v:%d", rgblight_get_hue(), rgblight_get_sat(), rgblight_get_val());
  oled_write_ln(rgbStatusLine2, false);
#endif
    return false;
}
#endif
