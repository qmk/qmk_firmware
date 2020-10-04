#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern uint8_t is_master;

enum layer_number {
  _QWERTY = 0,
  _NUM_FUN,
  _NAV_SYM,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LCTRL |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI | NAV  | /Space  /       \Enter \  |  NUM |BackSP| RGUI |
 *                   |      |      | SYM  |/       /         \      \ |  FUN |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT( \
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV, \
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS, \
  KC_LSFT,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LCTRL, KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT, \
                        KC_LALT, KC_LGUI, TG(_NUM_FUN), KC_SPC, KC_ENT, TG(_NAV_SYM), KC_BSPC, KC_RGUI \
),
/* NUM_FUN
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |   (  |                    |   )  |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   1  |   2  |   3  |   4  |   5  |-------.    ,-------|   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|   =   |    |   =   |------+------+------+------+------+------|
 * |      |      |   +  |   -  |   *  |   /  |-------|    |-------|   %  |   ^  |   &  |   |  |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |QWERTY| /Space  /       \Enter \  |  NAV |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |  SYM |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_NUM_FUN] = LAYOUT( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, \
  _______, _______, _______, _______, _______, KC_LEFT_PAREN,             KC_RIGHT_PAREN, _______, _______, _______, _______, _______, \
  _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______, \
  _______, _______, KC_PLUS, KC_MINUS, KC_ASTERISK, KC_SLASH, KC_EQUAL, KC_EQUAL, KC_PERCENT, KC_CIRCUMFLEX, KC_AMPERSAND, KC_PIPE, _______, _______, \
                         _______, _______, TG(_QWERTY), _______, _______, TG(_NAV_SYM), _______, _______\
),
/* NAV_SYM
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   !  |   @  |   #  |   $  |   %  |                    |   ^  |   &  |   *  |   (  |   )  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |  Up  |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | Left | Down | Right|      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |      |      |      |      |   ;  |   '  |-------|    |-------|   ,  |   .  |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI | NUM  | /Space  /       \Enter \  |QWERTY |BackSP| RGUI |
 *                   |      |      | FUN  |/       /         \      \ |       |      |      |
 *                   `----------------------------'           '------''--------------------'
 */	
[_NAV_SYM] = LAYOUT( \
  KC_GRV, KC_EXCLAIM, KC_AT, KC_HASH, KC_DOLLAR, KC_PERCENT,                KC_CIRCUMFLEX, KC_AMPERSAND, KC_ASTERISK, KC_LEFT_PAREN, KC_RIGHT_PAREN, KC_MINUS, \
  _______, _______, KC_UP, _______, _______, _______,                     _______, _______, _______, _______, _______, _______, \
  _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______ , _______,                 XXXXXXX, _______, _______, _______, _______, XXXXXXX, \
  _______, _______, _______, _______,  KC_SCOLON, KC_QUOTE, _______,  _______, KC_COMMA, KC_DOT, _______, _______, _______, _______,\
                             _______, _______, TG(_NUM_FUN),  _______, _______,  TG(_QWERTY), _______, _______ \
),
};

// Setting ADJUST layer RGB back to default
//void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
//  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
//    layer_on(layer3);
//  } else {
//    layer_off(layer3);
//  }
///}

//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk
#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

void oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_keylogs(), false);
  } else {
    oled_write(read_logo(), false);
  }
}
#endif // OLED_DRIVER_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  return true;
}

