#include QMK_KEYBOARD_H

#define _MAIN 0
#define _FN 1

#define KC_X0 LT(_FN, KC_ESC)

#ifdef RGBLIGHT_ENABLE
// How long (in ms) to wait between animation steps for the rainbow mode
const uint8_t RGBLED_RAINBOW_MOOD_INTERVALS[] PROGMEM = {60, 30, 15};
// How long (in milliseconds) to wait between animation steps for each of the "Swirling rainbow" animations
const uint8_t RGBLED_RAINBOW_SWIRL_INTERVALS[] PROGMEM = {20, 10, 4};
#endif

/**
 * Kodi shortcuts:
 *
 * ESC - Previous menu OR Home screen
 * Enter - Select
 * X - Stop
 * Arrows to move
 *
 * For details have a look at:
 * https://kodi.wiki/view/Keyboard_controls
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_MAIN] = LAYOUT_ortho_2x4(
     KC_ESC, KC_UP, KC_ENTER, KC_X,
     KC_LEFT, KC_DOWN, KC_RIGHT, MO(_FN)
  ),

  [_FN] = LAYOUT_ortho_2x4(
     RGB_TOG, RGB_MOD, RGB_M_R, RGB_M_SN,
     BL_TOGG, BL_STEP, BL_BRTG, _______
  )
};

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
}

void oled_task_user(void) {
  // Host Keyboard Layer Status
  oled_write_ln_P(PSTR("ANAVI Macro Pad 8"), false);
  oled_write_P(PSTR("Active layer: "), false);

  switch (get_highest_layer(layer_state)) {
    case _MAIN:
      oled_write_ln_P(PSTR("Kodi"), false);
      break;
    case _FN:
      oled_write_ln_P(PSTR("FN"), false);
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
}
#endif
