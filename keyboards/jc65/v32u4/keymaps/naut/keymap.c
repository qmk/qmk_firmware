#include QMK_KEYBOARD_H

/*
// Define Macros
#define M_PRTS  M(0)
#define M_PRTA  M(1)
#define M_PRTSC M(2)
#define M_PRTAC M(3)
#define M_MSSN  M(4)
#define M_APPS  M(5)
#define M_SPOT  M(6)
#define M_LEFT  M(7)
#define M_RGHT  M(8)
#define RGB_WHT M(9)
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // base layer
    [0] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,  KC_INS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_BSPC, KC_DEL,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,                   KC_ENT,  KC_PGUP,
        KC_LSFT, KC_NO,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_PGDN,
        MO(1),   KC_LALT, KC_LGUI,          KC_SPC,  KC_SPC,  KC_SPC,                             KC_RGUI, KC_NO,   KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT),

    // fn1 Layer
    [1] = LAYOUT(
        KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS, KC_TRNS, KC_TRNS,
        KC_CAPS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_VOLU, KC_MPLY,
        KC_TRNS, MO(2),   KC_TRNS,          TO(3),   TO(3),   TO(3),                              KC_TRNS, KC_TRNS, KC_TRNS, KC_MRWD, KC_VOLD, KC_MFFD),

    // fn2 led layer
    [2] = LAYOUT(
        KC_TRNS, RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_VAD, RGB_VAI, KC_TRNS, KC_TRNS, RGB_M_P,
        KC_TRNS, BL_TOGG, KC_TRNS, RGB_SAD, RGB_SAI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, BL_DEC,  BL_INC,           KC_TRNS, RGB_M_R,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, RGB_M_G,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, RGB_M_SW,
        KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,),

    // fn3 button mash layer
    [3] = LAYOUT(
        TO(0),   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                     KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,            KC_NO,   KC_NO,   KC_NO,                              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO),
};

/*
// The Macros
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    if (record->event.pressed) {
        switch(id) {
            case 0:
                return MACRO(D(LGUI), D(LSFT), T(3), U(LSFT), U(LGUI), END);                   // Mac print screen
            case 1:
                return MACRO(D(LGUI), D(LSFT), T(4), U(LSFT), U(LGUI), END);                   // Mac print area
            case 2:
                return MACRO(D(LCTL), D(LSFT), D(LGUI), T(3), D(LCTL), D(LSFT), D(LGUI), END); // Mac print screen to clipboard
            case 3:
                return MACRO(D(LCTL), D(LSFT), D(LGUI), T(4), D(LCTL), D(LSFT), D(LGUI), END); // Mac print area to clipboard
            case 4:
                return MACRO(D(LCTL), T(UP), U(LCTL), END);                                    // Mac mission control
            case 5:
                return MACRO(D(LCTL), T(DOWN), U(LCTL), END);                                  // Mac app windows
            case 6:
                return MACRO(D(LGUI), T(SPC), U(LGUI), END);                                   // Mac spotlight search
            case 7:
                return MACRO(D(LCTL), T(LEFT), U(LCTL), END);                                  // Mac mission left
            case 8:
                return MACRO(D(LCTL), T(RGHT), U(LCTL), END);                                  // Mac mission right
            case 9:
                rgblight_setrgb(0xff, 0xff, 0xff);                                             // White rgb shortcut
                break;
        }
    }
    return MACRO_NONE;
};
*/
