#include QMK_KEYBOARD_H

enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |  P8  |  P4  |  P5  |  P6  | TG_A |                    | INS  | DEL  | HOME | END  | PGUP | PGDN |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------| LOCK  |    | Mute  |------+------+------+------+------+------|
 * |LCTRL |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI | LAlt |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT(
  KC_ESC,  KC_P8,  KC_P4,   KC_P5,   KC_P6,TG(_ADJUST),                 KC_INS,  KC_DEL, KC_HOME,  KC_END,  KC_PGUP,   KC_PGDN,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
  KC_LSFT,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LCTL,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, QK_LOCK,   KC_MUTE, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
                        KC_LGUI, KC_LALT, MO(_LOWER), KC_SPC, KC_ENT  , MO(_RAISE), KC_BSPC, KC_RGUI
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |   6  |   7  |   8  |   9  |   0  |                    | F19  | F20  | F21  | F22  | F23  | F24  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   1  |   2  |   3  |   4  |   5  |                    | F13  | F14  | F15  | F16  | F17  | F18  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |   ~  |
 * |------+------+------+------+------+------| LOCK  |    | Mute  |------+------+------+------+------+------|
 * |      |   6  |   7  |   8  |   9  |   0  |-------|    |-------|      |   _  |   +  |   {  |   }  |   |  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI | LAlt |LOWER | /Space  /       \Enter \  |RAISE | Del  | RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_LOWER] = LAYOUT(
  _______ ,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                     KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,
  _______,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                     KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,
  KC_GRV, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                    KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD,
  _______ ,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  _______, _______, XXXXXXX, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
                             _______, _______, _______, _______, _______,  _______, KC_DEL , _______
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    | Prev | Play | Next | Mute | VolD | VolU |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | SCLK |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |-------.    ,-------| Left | Down |  Up  |Right |      | CAPS |
 * |------+------+------+------+------+------| LOCK  |    | Mute  |------+------+------+------+------+------|
 * |  F7  |  F8  |  F9  | F10  | F11  | F12  |-------|    |-------|   +  |   -  |   =  |   [  |   ]  |   \  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI | LAlt |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_RAISE] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                     KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU,
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_SCRL,
  KC_F1,  KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,                       KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, KC_CAPS,
  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,   _______, _______,  KC_PLUS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
                             _______, _______, _______,  _______, _______,  _______, _______, _______
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |  P7  |  P8  |  P9  |  P/  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |  P4  |  P5  |  P6  |  P*  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |  P1  |  P2  |  P3  |  P-  |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |  P0  |  P.  |  PE  |  P+  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI | LAlt |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ADJUST] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, KC_KP_7, KC_KP_8, KC_KP_9, KC_PSLS,
  _______, _______, _______, _______, _______, _______,                   _______, _______, KC_KP_4, KC_KP_5, KC_KP_6, KC_PAST,
  _______, _______, _______, _______, _______, _______,                   _______, _______, KC_KP_1, KC_KP_2, KC_KP_3, KC_PMNS,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_KP_0, KC_PDOT, KC_PENT, KC_PPLS,
                             _______, _______, _______, _______, _______,  _______, _______, _______
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code_delay(KC_WH_D, 5);
        } else {
            tap_code_delay(KC_WH_U, 5);
        }
    } else {
        if (!clockwise) {
            tap_code_delay(KC_VOLU, 5);
        } else {
            tap_code_delay(KC_VOLD, 5);
        }
    }

    return false;
}

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

    oled_rotation_t oled_init_user(oled_rotation_t rotation) {
      if (!is_keyboard_master())
        return OLED_ROTATION_270;  // flips the display 180 degrees if offhand
      return rotation;
    }

    // When you add source files to SRC in rules.mk, you can use functions.
    const char *read_layer_state(void);
    const char *read_logo(void);
    void set_keylog(uint16_t keycode, keyrecord_t *record);
    const char *read_keylog(void);
    const char *read_keylogs(void);

    // const char *read_mode_icon(bool swap);
    // const char *read_host_led_state(void);
    // void set_timelog(void);
    // const char *read_timelog(void);

    static const char shnob_img[] PROGMEM = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x03, 0x01, 0xf1, 0xf9, 0xf9, 0x39, 0x19, 0x19, 0x19,
        0x19, 0x19, 0x19, 0x39, 0xf9, 0xf9, 0xf1, 0x01, 0x03, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x07, 0x0f, 0x1f, 0x3c, 0x78, 0x70, 0x70,
        0x70, 0x70, 0xf0, 0xe0, 0xc1, 0x83, 0x03, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x7e, 0xfe, 0xfc, 0xe0, 0xc0, 0xc0, 0xc0,
        0xc0, 0xc0, 0xc0, 0xe1, 0xff, 0xff, 0x7f, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x06, 0x00, 0xe0, 0xf0, 0xf0, 0x70, 0x30, 0x00, 0x00,
        0x00, 0x00, 0x30, 0x70, 0xf0, 0xf0, 0xe0, 0x00, 0x06, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xf0, 0xe0, 0xe0, 0xe0,
        0xe0, 0xe0, 0xe0, 0xf0, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xc1, 0x80, 0x00, 0x00,
        0x00, 0x00, 0x80, 0xc1, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x0c, 0x00, 0xc0, 0xe1, 0xe1, 0xc1, 0x81, 0x00, 0x00,
        0x00, 0x00, 0x61, 0xe1, 0xe1, 0xe1, 0xc0, 0x00, 0x0c, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0x0f, 0x3f, 0xfe, 0xf8,
        0xe0, 0x80, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x03,
        0x0f, 0x3f, 0xfe, 0xf8, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x18, 0x00, 0x81, 0xc3, 0xc3, 0xc3, 0xc3, 0xc0, 0xc0,
        0xc0, 0xc0, 0xc0, 0xc1, 0xc3, 0xc3, 0x81, 0x00, 0x18, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x30, 0x00, 0x03, 0x87, 0x87, 0x87, 0x86, 0x86, 0x86,
        0x86, 0x86, 0x86, 0x87, 0x87, 0x07, 0x03, 0x00, 0x30, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0x01, 0x01, 0x01, 0x01,
        0x01, 0x01, 0x01, 0x83, 0xff, 0xff, 0xfe, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0x07, 0x07, 0x07, 0x07,
        0x07, 0x07, 0x07, 0x0f, 0xff, 0xfd, 0xf8, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x60, 0x40, 0x47, 0x4f, 0x4f, 0x4c, 0x4c, 0x4c, 0x4c,
        0x4c, 0x4c, 0x4c, 0x4e, 0x4f, 0x47, 0x43, 0x40, 0x60, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

bool oled_task_user(void) {
      if (is_keyboard_master()) {
        // If you want to change the display of OLED, you need to change here
        oled_write_ln(read_layer_state(), false);
        oled_write_ln(read_keylog(), false);
        oled_write_ln(read_keylogs(), false);
        //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
        //oled_write_ln(read_host_led_state(), false);
        //oled_write_ln(read_timelog(), false);
      } else {
        //oled_write(read_logo(), false);
        oled_write_raw_P(shnob_img, sizeof(shnob_img));
      }
        return false;
    }
#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    #ifdef OLED_ENABLE
        set_keylog(keycode, record);
    #endif
        // set_timelog();
  }
  return true;
}
