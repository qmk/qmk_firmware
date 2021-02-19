#include QMK_KEYBOARD_H
#include <stdio.h>

char wpm_str[10];

#define GRAVE_MODS  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT)|MOD_BIT(KC_LGUI)|MOD_BIT(KC_RGUI)|MOD_BIT(KC_LALT)|MOD_BIT(KC_RALT))

#define _BL 0
#define _FL 1 // lower
#define _CL 2 // raise



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * _BL
 * ,-----------------------------------------.            ,-------------------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |            |       |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------|            |   D   |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |            |   I   |   Y  |   U  |   I  |   O  |   P  |  \|  |
 * |------+------+------+------+------+------|            |   S   |------+------+------+------+------+------|
 * |LShift|   A  |   S  |   D  |   F  |   G  |-------.    |   P   |   H  |   J  |   K  |   L  |  :;  |  "'  |
 * |------+------+------+------+------+------| Knob  |    |       |------+------+------+------+------+------|
 * | LCTR |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |  ,<  |  .>  |  /?  |  Ent |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt |  DEL |Lower | / Space /       \ BKSP \  |Raise |  +=  |  {[  |  ]}  |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[_BL] = LAYOUT( \
  KC_ESC,    KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                          KC_6,    KC_7,    KC_8,    KC_9,   KC_0,    KC_MINS, \
  KC_TAB,    KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                          KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,    KC_BSLS, \
  KC_LSFT,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,   XXXXXXX,      XXXXXXX, KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT, \
  KC_LCTL,   KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,   KC_SPC,       KC_BSPC, KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_ENT, \
                              KC_LGUI, KC_LALT, KC_DEL, MO(_FL),      MO(_CL), KC_EQL,  KC_LBRC, KC_RBRC \
),
/*
 *
 * ,-----------------------------------------.            ,-------------------------------------------------.
 * | Reset|  F1  |  F2  |  F3  |  F4  |  F5  |            |       |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|            |   D   |------+------+------+------+------+------|
 * |      |      |      | Mute | PrtSc|      |            |   I   |      |      |      |      |      | F12  |
 * |------+------+------+------+------+------|            |   S   |------+------+------+------+------+------|
 * | Caps |      | Prev | P/P  | Next |      |-------.    |   P   | Left | Down |  Up  | Right|      |  '   |
 * |------+------+------+------+------+------|  Knob |    |       |------+------+------+------+------+------|
 * |      |      | BrDo |      | BrUp |      |-------|    |-------|      | Home | Ins  | End  |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt |      |LOWER | /Space  /       \BackSc\  |RAISE |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
*/

[_FL] = LAYOUT( \
  RESET,    KC_F1,    KC_F2,    KC_F3,     KC_F4,    KC_F5,                          KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11, \
  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC__MUTE,  KC_PSCR,  XXXXXXX,                        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, \
  KC_CAPS,  XXXXXXX,  KC_MPRV,  KC_MPLY,   KC_MNXT,  XXXXXXX, XXXXXXX,     XXXXXXX,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  XXXXXXX,  KC_QUOT, \
  XXXXXXX,  XXXXXXX,  KC_BRID,  XXXXXXX,   KC_BRIU,  XXXXXXX, KC_SPC,      KC_BSPC,  XXXXXXX,  KC_HOME,  KC_INS,   KC_END,   XXXXXXX,  XXXXXXX, \
                                KC_LGUI,   KC_LALT,  XXXXXXX, MO(_FL),     MO(_CL),  XXXXXXX,  XXXXXXX,  XXXXXXX \
),
/*
 *
 * ,-----------------------------------------.            ,-------------------------------------------------.
 * |      |      |      |      |      |      |            |       |      |      | Slash|  *   | Back |      |
 * |------+------+------+------+------+------|            |   D   |------+------+------+------+------+------|
 * |      |      |      |      |      |      |            |   I   |      |  7   |  8   |  9   |  -   |      |
 * |------+------+------+------+------+------|            |   S   |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    |   P   |      |  4   |  5   |  6   |  +   |      |
 * |------+------+------+------+------+------|  Knob |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |  1   |  2   |  3   |Enter |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt |      |LOWER | /Space  /       \BackSc\  |RAISE |  0   | space|  .   |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'-----------
 *
*/

[_CM] = LAYOUT( \
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                       XXXXXXX,  XXXXXXX,  KC_PSLS,  KC_PAST,  KC_BSPC,  XXXXXXX, \
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                       XXXXXXX,  KC_P7,    KC_P8,    KC_P9,    KC_PMNS,  XXXXXXX, \
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX,  KC_P4,    KC_P5,    KC_P6,    KC_PLUS,  XXXXXXX, \
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, KC_SPC,      KC_BSPC, XXXXXXX,  KC_P1,    KC_P2,    KC_P3,    KC_PENT,  XXXXXXX, \
                                KC_LGUI,  KC_LALT,  XXXXXXX, MO(_FL),     MO(_CL), KC_P0,    KC_P0,    KC_PDOT \
)
};

const rgblight_segment_t PROGMEM _BL[] = RGBLIGHT_LAYER_SEGMENTS(
    {0,57, HSV_WHITE}
);
const rgblight_segment_t PROGMEM _FL[] = RGBLIGHT_LAYER_SEGMENTS(
    {0,57, HSV_GREEN}
);
const rgblight_segment_t PROGMEM _CL[] = RGBLIGHT_LAYER_SEGMENTS(
    {0,57, HSV_RED}
);
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    _BL,
    _FL,
    _CL
);

void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers
}


#ifdef OLED_DRIVER_ENABLE

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0
    };

    oled_write_P(qmk_logo, false);
}


oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

void oled_task_user(void) {
    render_logo();
    oled_ser_cursor(0,6);
    sprintf(wpm_str, "WPM: %03d", get_current_wpm());
    oled_write(wpm_str, false);
}


#endif







bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}

#ifdef ENCODER_ENABLE

void encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        tap_code(KC_VOLU);
    } else {
        tap_code(KC_VOLD);
    }
}

#endif
