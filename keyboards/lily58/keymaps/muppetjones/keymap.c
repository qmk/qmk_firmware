/* Copyright 2020 Stephen J. Bush
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
#include "muppetjones.h"
#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

#ifdef PROTOCOL_LUFA
#  include "lufa.h"
#  include "split_util.h"
#endif
#ifdef SSD1306OLED
#  include "ssd1306.h"
#endif

/*
 *  qmk compile -kb lily58/rev1 -km muppetjones
 */

// GACS (Lower)
#define HR_LBRC LCTL_T(KC_LBRC)
#define HR_RBRC LSFT_T(KC_RBRC)

extern uint8_t is_master;

/*
enum layer_number {
  _CLMK_DH = 0,
  _QWERTY,
  _MOUSE,
  _LOWER,
  _RAISE,
  _NAV,
  _ADJUST,
};
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off

/* Colemak DH
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | BADJ |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   F  |   P  |   B  |                    |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   G  |-------.    ,-------|   M  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------| Raise |    | Lower |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   D  |   V  |-------|    |-------|   K  |   H  |   ,  |   .  |   /  |Enter |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | Alt  | LGUI |LOWER | /Space  /       \Space \  |RAISE | Ctrl | RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_CLMK_DH] = LAYOUT_wrapper(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    CAPSWRD,                   __BLANK____________________________________, KC_BSPC,
    CAPSWRD, __COLEMAK_MOD_DH_L1________________________,                   __COLEMAK_MOD_DH_R1________________________, KC_BSLS,
    HY_ESC,  __COLEMAK_MOD_DH_L2_W_GACS_________________,                   __COLEMAK_MOD_DH_R2_W_SCAG_________________, KC_QUOT,
    TD_LAYR, __COLEMAK_MOD_DH_L3________________________, HY_ESC,  KC_TAB,  __COLEMAK_MOD_DH_R3________________________, KC_SFTENT,
                                KC_DEL,  KC_DEL,  HY_ESC, LOW_ENT, RAI_SPC, HY_ESC,   RAI_TAB, KC_BSPC
),

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_QWERTY] = LAYOUT_wrapper(
    _______, __BLANK____________________________________,                   __BLANK____________________________________, _______,
    _______, __QWERTY_L1________________________________,                   __QWERTY_R1________________________________, _______,
    _______, __QWERTY_L2________________________________,                   __QWERTY_R2________________________________, _______,
    _______, __QWERTY_L3________________________________, _______, _______, __QWERTY_R3________________________________, _______,
                               _______, _______, _______, _______, _______, _______, _______, _______
),
[_MOUSE] = LAYOUT_wrapper(
    _______, __BLANK____________________________________,                   __BLANK____________________________________, _______,
    _______, __BLANK____________________________________,                   __BLANK____________________________________, _______,
    _______, __BLANK____________________________________,                   __BLANK____________________________________, _______,
    _______, __BLANK____________________________________, _______, _______, __BLANK____________________________________, _______,
                               KC_BTN1, __BLANK____________________________________, _______, KC_BTN2
),

/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   `  |      | Mute | Vol- | Vol+ |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   ~  |      |      |   `  |      |   (  |                    |   )  |   7  |   8  |   9  |   \  | Bksp |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | GUI  | ALT  |   _  |   -  |   {  |-------.    ,-------|   }  |   4  |   5  |   6  |   *  |  `   |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |   +  |   =  |   [  |-------|    |-------|   ]  |   1  |   2  |   3  |   |  |Enter |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |LOWER | /       /       \      \  |   0  |   .  |   =  |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_LOWER] = LAYOUT_wrapper(
    _______, __BLANK____________________________________,                   __BLANK____________________________________, _______,
    _______, __BLANK____________________________________,                   __NUMPAD_R1________________________________, _______,
    _______, __BLANK_W_GACS_____________________________,                   __NUMPAD_R2________________________________, KC_PLUS,
    _______, __BLANK____________________________________, _______, _______, __NUMPAD_R3________________________________, _______,
                               __BLANK____________________________________, KC_0,    KC_DOT,  _______
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |MS_A_0|MS_A_1|MS_A_2|      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |MS_W_U|                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | GUI  | ALT  | CTL  | SFT  |MS_W_D|-------.    ,-------|      | Left | Down |  Up  |Right |      |
 * |------+------+------+------+------+------|MS_W_L |    |MS_W_R |------+------+------+------+------+------|
 * |      | MS_L | MS_D | MS_U | MS_R |      |-------|    |-------|      |MS_W_L|MS_W_D|MS_W_U|MS_W_R|      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      | MS_2 | / MS_1  /       \      \  |RAISE |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 // */

[_RAISE] = LAYOUT_wrapper(
    _______, __BLANK____________________________________,                   __BLANK____________________________________, _______,
    _______, XXXXXXX, XXXXXXX, KC_LPRN, KC_RPRN, XXXXXXX,                   __NAV_R1___________________________________, _______,
    _______, KC_LGUI, KC_LALT, HR_LBRC, HR_RBRC, KC_MINS,                   __NAV_R2___________________________________, _______,
    _______, XXXXXXX, XXXXXXX, KC_LCBR, KC_RCBR, KC_EQL,  _______, _______, __NAV_R3___________________________________, _______,
                               _______, _______, _______, _______, _______, _______, _______, _______
),
[_NAV] = LAYOUT_wrapper(
    _______, __BLANK____________________________________,                   __BLANK____________________________________, _______,
    _______, __BLANK____________________________________,                   __NAV_R1___________________________________, _______,
    _______, __BLANK_W_GACS_____________________________,                   __NAV_R2___________________________________, _______,
    _______, __BLANK____________________________________, _______, _______, __NAV_R3___________________________________, _______,
                               _______, _______, _______, _______, _______, _______, _______, _______
),

/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      | Reset|      |      |      |      |                    | Reset|      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |RGB ON| HUE+ | SAT+ | VAL+ |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      | MODE | HUE- | SAT- | VAL- |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_ADJUST] = LAYOUT_wrapper(
    _______, __BLANK____________________________________,                   __BLANK____________________________________, _______,
    RESET,   _______, _______, _______, _______, _______,                   _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______,
    _______, RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD,                   _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______,
    _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD,_______, _______, _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
                               _______, _______, _______, _______, _______, _______, _______, _______
)

    // clang-format on
};

// Setting ADJUST layer RGB back to default
// void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
//   if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
//     layer_on(layer3);
//   } else {
//     layer_off(layer3);
//   }
// }

// SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk
#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
const char *wpm_state(void);
void        render_bongo_cat(void);
void        set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
    // oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    // oled_write_ln(read_host_led_state(), false);
    // oled_write_ln(read_timelog(), false);
  } else {
    render_bongo_cat();
    oled_set_cursor(0, 6);
    oled_write(wpm_state(), false);
    // oled_write(read_logo(), false);
  }
}
#endif  // OLED_DRIVER_ENABLE

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  // Regular user keycode case statement
  switch (keycode) {
    default:
      return true;
  }

  return true;
}
