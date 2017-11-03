#include "mitosis.h"

enum mitosis_layers
{
    _WORKMAN,
    _FUNC,
    _NUMS,
    _NMFN
};

// Fillers to make layering more clear
#define XXXXXXX KC_NO   // No-op (no key in this location on Mitosis' fake matrix)
#define _______ KC_TRNS // Transparent, because I haven't decided a mapping yet
#define ___M___ KC_TRNS // Transparent, as required by modifier key on another layer
#define KC_LMTA KC_LALT // For fun, name the mods like the space cadet keyboard does
#define KC_RMTA KC_RALT // META
#define KC_LSUP KC_LGUI // SUPER
#define KC_RSUP KC_RGUI // 
#define KC_RHYP KC_INT4 // HYPER (actually muhenkan 無変換 and henkan 変換)
#define KC_LHYP KC_INT5 // or NFER/XFER.

// I didn't want to mess about with new keymappings and custom logic etc. to
// enable tri-state layers like mitosis default does. This layout accomplishes
// it with a small quirk that triggering both layers then releasing one
// out-of-order will leave the tri-state triggered. Which doesn't bother me.

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_WORKMAN] = {
        {KC_Q,    KC_D,    KC_R,    KC_W,      KC_B,      KC_J,      KC_F,      KC_U,    KC_P,    KC_SCLN},
        {KC_A,    KC_S,    KC_H,    KC_T,      KC_G,      KC_Y,      KC_N,      KC_E,    KC_O,    KC_I},
        {KC_Z,    KC_X,    KC_M,    KC_C,      KC_V,      KC_K,      KC_L,      KC_COMM, KC_DOT,  KC_SLSH},
        {XXXXXXX, KC_LSUP, KC_LCTL, MO(_NUMS), KC_BSPC,   KC_SPC,    MO(_NUMS), KC_RCTL, KC_RSUP, XXXXXXX},
        {XXXXXXX, KC_LHYP, KC_LMTA, KC_LSFT,   MO(_FUNC), MO(_FUNC), KC_RSFT,   KC_RMTA, KC_RHYP, XXXXXXX}
    },
    [_FUNC] = {
        {KC_ESC,  _______, KC_UP,   _______,   _______, _______, _______,   _______, _______, KC_QUOT},
        {KC_TAB,  KC_LEFT, KC_DOWN, KC_RGHT,   _______, _______, _______,   _______, _______, KC_GRV},
        {_______, _______, _______, _______,   _______, _______, _______,   KC_LBRC, KC_RBRC, KC_BSLS},
        {XXXXXXX, _______, _______, MO(_NMFN), KC_DEL,  KC_ENT,  MO(_NMFN), _______, _______, XXXXXXX},
        {XXXXXXX, _______, _______, _______,   ___M___, ___M___, _______,   _______, _______, XXXXXXX},
    },
    [_NUMS] = {
        {_______, _______, _______, _______, _______,   _______,   KC_1,    KC_2,    KC_3,    KC_4},
        {_______, _______, _______, _______, _______,   _______,   KC_5,    KC_6,    KC_7,    KC_8},
        {_______, _______, _______, _______, _______,   _______,   KC_MINS, KC_9,    KC_0,    KC_EQL},
        {XXXXXXX, _______, _______, ___M___, _______,   _______,   ___M___, _______, _______, XXXXXXX},
        {XXXXXXX, _______, _______, _______, MO(_NMFN), MO(_NMFN), _______, _______, _______, XXXXXXX},
    },
    [_NMFN] = {
        {_______, _______, KC_PGUP, _______, _______, _______, KC_F1,   KC_F2,   KC_F3,   KC_F4},
        {_______, KC_HOME, KC_PGDN, KC_END,  _______, _______, KC_F5,   KC_F6,   KC_F7,   KC_F8},
        {_______, _______, _______, _______, _______, _______, KC_F8,   KC_F9,   KC_F10,  KC_F12},
        {XXXXXXX, _______, _______, ___M___, _______, _______, ___M___, _______, _______, XXXXXXX},
        {XXXXXXX, _______, _______, _______, ___M___, ___M___, _______, _______, _______, XXXXXXX},
    },
};

void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);

    switch (layer) {
        case _WORKMAN:
            red_led_off;
            grn_led_off;
            break;
        case _FUNC:
            red_led_off;
            grn_led_on;
            break;
        case _NUMS:
            red_led_on;
            grn_led_off;
            break;
        case _NMFN:
            red_led_on;
            grn_led_on;
            break;
        default:
            break;
    }
};
