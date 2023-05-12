#include QMK_KEYBOARD_H
#include "sendstring_uk.h"

// Layers
enum layer_number {
    _QWERTY = 0,
    _GAMING,
    _LOWER,
    _RAISE,
    _ADJUST,
    _ALT
};

// Keycodes
enum my_keycodes {
  KC_QWRT = SAFE_RANGE,
  KC_GAME
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,---------------------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |      -         |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+----------------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |      #         |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+----------------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  | '   /  CTRL    |
 * |------+------+------+------+------+------|  MEH  |    |  MEH  |------+------+------+------+------+----------------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift / CapWord|
 * `-----------------------------------------/       /     \      \---------------------------------------------------'
 *                   | LGUI | LAlt |LOWER | /Space  /       \Enter \  |RAISE |BackSP|Hyper |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '----------------------------'
 */

 [_QWERTY] = LAYOUT(
  KC_ESC,   UK_1,   UK_2,    UK_3,    UK_4,    UK_5,                        UK_6,       UK_7,   UK_8,    UK_9,    UK_0,     UK_MINS,
  KC_TAB,   UK_Q,   UK_W,    UK_E,    UK_R,    UK_T,                        UK_Y,       UK_U,   UK_I,    UK_O,    UK_P,     UK_HASH,
  KC_LCTL,  UK_A,   UK_S,    UK_D,    UK_F,    UK_G,                        UK_H,       UK_J,   UK_K,    UK_L,    UK_SCLN,  RCTL_T(UK_QUOT),
  KC_LSFT,  UK_Z,   UK_X,    UK_C,    UK_V,    UK_B,       KC_MEH, KC_MEH,  UK_N,       UK_M,   UK_COMM, UK_DOT,  UK_SLSH,  KC_RSFT,
                             KC_LGUI, KC_LALT, MO(_LOWER), KC_SPC, KC_ENT,  MO(_RAISE), KC_BSPC, KC_HYPR
),
/* GAMING
 * ,-----------------------------------------.                    ,---------------------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |      -         |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+----------------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |      #         |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+----------------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  | '   /  CTRL    |
 * |------+------+------+------+------+------|   [   |    |  MEH  |------+------+------+------+------+----------------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift / CapWord|
 * `-----------------------------------------/       /     \      \---------------------------------------------------'
 *                   |  ]   | LAlt | _ALT | /Space  /       \Enter \  |QWERTY|BackSP|Hyper |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '----------------------------'
 */
  [_GAMING] = LAYOUT(
  KC_ESC,   UK_1,   UK_2,    UK_3,    UK_4,    UK_5,                      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,    KC_F6,
  KC_TAB,   UK_Q,   UK_W,    UK_E,    UK_R,    UK_T,                      UK_Y,    UK_U,    UK_I,    UK_O,    UK_P,     UK_HASH,
  KC_LCTL,  UK_A,   UK_S,    UK_D,    UK_F,    UK_G,                      UK_H,    UK_J,    UK_K,    UK_L,    UK_SCLN,  RCTL_T(UK_QUOT),
  KC_LSFT,  UK_Z,   UK_X,    UK_C,    UK_V,    UK_B,     UK_LBRC, KC_MEH, UK_N,    UK_M,    UK_COMM, UK_DOT,  UK_SLSH,  KC_RSFT,
                             KC_RBRC, KC_LALT, MO(_ALT), KC_SPC,  KC_ENT, KC_QWRT, KC_BSPC, KC_HYPR
  ),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | Esc  |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  | F9   | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |PageUp| Home | Up   | End  | Mute |                    | Home |PageUp|      | End  |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |PageDn| Left | Down | Right| VolU |-------.    ,-------| Left | Down |  Up  | Right|      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      | VolD |-------|    |-------|      |PageDn|      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI | LAlt |      | /Enter  /       \Enter \  |RAISE | Del  |Hyper |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '----------------------------'
 */

[_LOWER] = LAYOUT(
  KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,                      KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  KC_TRNS, KC_PGUP, KC_TRNS, KC_UP,   KC_TRNS,  KC_VOLU,                    KC_HOME, KC_PGUP, KC_TRNS, KC_END,  KC_TRNS, KC_TRNS,
  KC_TRNS, KC_PGDN, KC_LEFT, KC_DOWN, KC_RIGHT, KC_VOLD,                    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS, KC_TRNS,
  KC_CAPS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_MUTE,  KC_BSPC, KC_TRNS, KC_TRNS, KC_PGDN, KC_TRNS, KC_TRNS, KC_TRNS, KC_CAPS,
                             KC_TRNS, KC_TRNS,  KC_TRNS,  KC_ENT,  KC_TRNS, KC_TRNS, KC_DEL,  KC_TRNS
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  !   |  "   |  £   |  $   |  %   |                    |  ^   |  &   |  *   |  '   |  ?   |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  |   |  {   |  [   |  (   |  <   |-------.    ,-------|  >   |  )   |  ]   |  }   |  :   |  @   |
 * |------+------+------+------+------+------|   `   |    |   `   |------+------+------+------+------+------|
 * |      |  \   |      |  ~   |  -   |  =   |-------|    |-------|  =   |  +   |  _   |      |  €   |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI | LAlt |      | /Space  /       \Enter \  |      |BackSP|Hyper |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '----------------------------'
 */

[_RAISE] = LAYOUT(
  KC_TRNS, KC_TRNS,       KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, RSFT(UK_1),    RSFT(UK_2), RSFT(UK_3), RSFT(UK_4), RSFT(UK_5),                UK_CIRC, UK_AMPR, UK_ASTR, UK_QUOT, KC_QUES, KC_TRNS,
  KC_TRNS, RSFT(UK_BSLS), UK_LCBR,    UK_LBRC,    UK_LPRN,    UK_LABK,                   UK_RABK, UK_RPRN, UK_RBRC, UK_RCBR, UK_COLN, UK_AT,
  KC_TRNS, UK_BSLS,       KC_TRNS,    UK_TILD,    UK_MINS,    UK_EQL,  UK_GRV,  UK_GRV,  UK_EQL,  UK_PLUS, UK_UNDS, KC_TRNS, UK_EURO, KC_TRNS,
                                      KC_TRNS,     KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSPC, KC_TRNS
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------| GAME  |    | GAME  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI | LAlt |LOWER | /Space  /       \Enter \  |RAISE |BackSP|Hyper |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ADJUST] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_GAME, KC_GAME, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                             _______, _______, _______, _______, _______, _______, _______, _______
),
/* ALT
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  6   |  7   |  8   |  9   |  0   |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |  Y   |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |  H   |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|   #   |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |  N   |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '-------'--------------------'
 */
  [_ALT] = LAYOUT(
  KC_TRNS,  UK_6,    UK_7,    UK_8,    UK_9,    UK_0,                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, UK_Y,                      KC_VOLU, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, UK_H,                      KC_VOLD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, UK_N,    UK_HASH, KC_TRNS, KC_MUTE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
                     KC_LGUI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  )
};

// Layers
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
// End Layers

// OLED
//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;  // flips the main display 180 degrees
    }
    else {
        return OLED_ROTATION_180;  // flips the offhand display 180 degrees
    }
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_default(void);
const char *read_layer_level(void);
const char *read_host_led(void);
const char *read_logo(void);
//const char *read_layer_state(void);
//void set_keylog(uint16_t keycode, keyrecord_t *record);
//const char *read_keylog(void);
//const char *read_keylogs(void);
//const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
//void set_timelog(void);
//const char *read_timelog(void);

bool oled_task_user(void) {
    if(is_keyboard_master()) {
        // If you want to change the display of OLED, you need to change here
        oled_write_ln(read_layer_default(), false);
        oled_write_ln(read_layer_level(), false);
        oled_write_ln(read_host_led(), false);
        //oled_write_ln(read_layer_state(), false);
        //oled_write_ln(read_keylog(), false);
        //oled_write_ln(read_keylogs(), false);
        //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
        //oled_write_ln(read_host_led_state(), false);
        //oled_write_ln(read_timelog(), false);
    }
    else {
        oled_write(read_logo(), false);
    }
    return false;
}
#endif // OLED_ENABLE
// End OLED

// Keycodes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_QWRT:
            if (record->event.pressed) {
            // Set default and change layer to _QWERTY
                set_single_persistent_default_layer(_QWERTY);
            }
            return false; // Skip all further processing of this key
        case KC_GAME:
            if (record->event.pressed) {
            // Set default and change layer to _GAMING
                set_single_persistent_default_layer(_GAMING);
            }
            return false; // Skip all further processing of this key
        default:
            return true; // Process all other keycodes normally
    }
}
// End Keycodes
