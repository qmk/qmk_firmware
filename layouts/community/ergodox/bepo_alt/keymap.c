/* Bepo layout for ergodox EZ by Nicolas CARPi (deltablot.com) */
#include QMK_KEYBOARD_H
#include "keymap_bepo.h"
#include "keymap_french.h"

#define BEPO 0  // default layer, for bepo compatible systems
#define FNAV 1  // function / navigation / mouse layer

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: default layer
 *
 * ,--------------------------------------------------.                                  ,--------------------------------------------------.
 * |   $    |   "  |   <  |   >  |   (  |   )  |  @   |                                  |  +   |   -  |   -  |   /  |   *  |   =  |   %    |
 * |--------+------+------+------+------+-------------|                                  |------+------+------+------+------+------+--------|
 * |   TAB  |   B  |E_ACUT|   P  |   O  |E_GRAV|Backsp|                                  |CapsLo|   ^  |   V  |   D  |   L  |   J  |   Z    |
 * |--------+------+------+------+------+------|  ace |                                  |      |------+------+------+------+------+--------|
 * |   W    |   A  |   U  |   I  |   E  |   ,  |------|                                  |------|   C  |   T  |   S  |   R  |   N  |   M    |
 * |--------+------+------+------+------+------|      |                                  | ESCAP------+------+------+------+------+--------|
 * | SHIFT |E_CIRC |  A_GRAV   | Y | X |    .  |  K   |                                  |      |   '  |   Q  |   G  |   H  |   F  | C_CEDIL|
 * `--------+------+------+------+------+-------------,-------------.      ,-------------`-------------+------+------+------+------+--------'
 *   |Ctrl|LSuper|LSuper| LSuper|  LAlt|             | PgUp  | PgDwn|      |BEPO| Delete |             | AltGr| RSuper|RSuper|RCtrl| Enter|
 *   `----------------------------------'      ,------|------|------|      |------+------+------.      `----------------------------------'
 *                                             |      |      |Insert|      |L_Fnav|      |      |
 *                                             | Space|Shift |------|      |------|RShift|Enter |
 *                                             |      |      |Mouse |      |  Fn  |       |      |
 *                                             `--------------------'      `--------------------'
 * df is for temporary stuff and mo is for toggle (momentary)
 * so mouse is to toggle the mouse mode
 */
[BEPO] = LAYOUT_ergodox(

/* Left hand */
BP_DLR,  BP_DQUO,  BP_LDAQ,  BP_RDAQ,  BP_LPRN,  BP_RPRN,  BP_AT,
KC_TAB, BP_B,   BP_EACU,    BP_P,   BP_O,   BP_EGRV, KC_BSPC,
BP_W,   BP_A,   BP_U,   BP_I,   BP_E,   BP_COMM,
KC_LSFT,    BP_ECIR,  BP_AGRV,   BP_Y,   BP_X,   BP_DOT,   BP_K,
KC_LCTL,    KC_LGUI,    KC_LGUI,  KC_LGUI,  KC_LALT,
                            KC_PGUP,  KC_PGDN,
                                KC_INS,
                        KC_SPC,   KC_LSFT,  DF(FNAV),

/* Right hand */
                BP_PLUS, BP_MINS,    BP_MINS, BP_SLSH, BP_ASTR,  BP_EQL, BP_PERC,
        KC_CAPS,  BP_DCIR,  BP_V,   BP_D,   BP_L,   BP_J,   BP_Z,
            BP_C,   BP_T,   BP_S,   BP_R,   BP_N,   BP_M,
        KC_ESC, BP_QUOT,  BP_Q,   BP_G,   BP_H,   BP_F,   BP_CCED,
                KC_ALGR,  KC_RGUI,  KC_RGUI,  KC_RCTL,  KC_ENTER,
DF(BEPO), KC_DEL,
DF(FNAV),
MO(FNAV), KC_RSFT,  KC_ENTER),

/* Keymap 1: function / navigation / mouse layer
 *
 * ,--------------------------------------------------.                                  ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                                  | F7   |  F8  |  F9  |  F10  |  F11  |  F12 |  F12 |
 * |--------+------+------+------+------+-------------|                                  |------+------+------+------+------+------+--------|
 * |        | Next |LClick|  Up  |RClick| WhUp |Backspace|                               |      | PgUp | Home |  Up  |  End |  F11 |        |
 * |--------+------+------+------+------+------|      |                                  |      |------+------+------+------+------+--------|
 * |        | Prev | Left | Down | Right|WhDown|------|                                  |------| Left | Down | Up  | Right |  F12 |        |
 * |--------+------+------+------+------+------| VolUp|                                  |      |------+------+------+------+------+--------|
 * |  Shift  | Undo |  Cut | Copy | Paste|      |      |                                 |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------,-------------.      ,-------------`-------------+------+------+------+------+--------'
 *   |  ctrl  | super  | super | alt    |      |        Home | End  |      |      |      |      |      | Alt  |      |      |Ctrl  |      |
 *   `----------------------------------'      ,------|------|------|      |------+------+------.      `----------------------------------'
 *                                             |      |      |      |      |      |      |      |
 *                                             |      |      |------|      |------|      |      |
 *                                             |      |      |      |      |      |      |      |
 *                                             `--------------------'      `--------------------'
 */
[FNAV] = LAYOUT_ergodox(

/* Left hand */
KC_NO,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,
KC_NO,    KC_MS_BTN5, KC_MS_BTN1, KC_MS_UP, KC_MS_BTN2, KC_MS_WH_UP,  KC_BSPC,
KC_NO,    KC_MS_BTN4, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT,  KC_MS_WH_DOWN,
KC_LSFT,    KC_UNDO,  KC_CUT,   KC_COPY,  KC_PASTE, KC_NO,    KC_VOLD,
KC_LCTL,    KC_INS,   KC_LGUI,  KC_LGUI,  KC_LALT,
                            KC_HOME,  KC_END,
                                KC_TRNS,
                        KC_NO,    KC_TRNS,  KC_TRNS,

/* Right hand */
        KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_F12,
        KC_NO,    KC_PGUP,  KC_HOME,  KC_UP,    KC_END,   KC_F11,   KC_NO,
            KC_LEFT,  KC_DOWN,  KC_UP,  KC_RIGHT, KC_F12,   KC_NO,
        KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
                KC_RALT,  KC_TRNS,  KC_TRNS,  KC_RCTL,    KC_NO,
KC_TRNS,  KC_TRNS,
KC_TRNS,
KC_TRNS,  KC_TRNS,  KC_NO),
};

/* helper function to switch on of the right LED ON/OFF */
static void indicate_using_led(const uint8_t led, const bool enabled) {
  if (enabled) {
    ergodox_right_led_on(led);
  } else {
    ergodox_right_led_off(led);
  }
}

/* Runs constantly in the background, in a loop */
void matrix_scan_user(void) {

  /* red led for shift */
  if (keyboard_report->mods & MOD_BIT(KC_LSFT) ||
    ((get_oneshot_mods() & MOD_BIT(KC_LSFT)) && !has_oneshot_mods_timed_out())) {
    indicate_using_led(1, true);
  } else {
    indicate_using_led(1, false);
  }

  /* green led for alt */
  if (keyboard_report->mods & MOD_BIT(KC_LALT) ||
    ((get_oneshot_mods() & MOD_BIT(KC_LALT)) && !has_oneshot_mods_timed_out())) {
    indicate_using_led(2, true);
  } else {
    indicate_using_led(2, false);
  }

  /* blue led for function mode */
  if (IS_LAYER_ON(FNAV)) {
    indicate_using_led(3, true);
  } else {
    indicate_using_led(3, false);
  }
};
