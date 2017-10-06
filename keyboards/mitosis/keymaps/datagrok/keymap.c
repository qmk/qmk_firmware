#include "mitosis.h"

// Arrows in a layer in the home position.
// Fn+Arrows = PgUp PgDn Home End, which is intuitive for me
// 
// Since QWERTY and WORKMAN keep angle brackets together, I wanted to place
// other enclosing symbols on the same keys. So, 9 and 0 and [ and ] land there
// in other layers. That informed the numbers placement, which informed the
// function-key placement.
//
// To do:
// - Improve LED indications (may require modding bluetooth firmware):
//   - Is any board nonresponsive (which one?)
//   - Does either board have a low battery?
// - Use "shifted keys" hack to make programming symbols easier to type
// - Add "media" keysyms, Insert, PrintScr, Pause/Break
// - Dynamically toggle QWERTY or other layouts
// - See if the henkans placement is at all useful for Japanese speakers, or
//   abuse different keysyms
// - Overlay a 10key numpad somewhere
// - Mod a speaker onto my receiver and enable tones
// - Mod more indicator LEDs onto my receiver
// - Do something with Num/Caps/Scroll lock?
// - Improve tri-layer behavior

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
        {KC_Q,    KC_D,      KC_R,    KC_W,    KC_B,      KC_J,      KC_F,    KC_U,    KC_P,      KC_SCLN},
        {KC_A,    KC_S,      KC_H,    KC_T,    KC_G,      KC_Y,      KC_N,    KC_E,    KC_O,      KC_I},
        {KC_Z,    KC_X,      KC_M,    KC_C,    KC_V,      KC_K,      KC_L,    KC_COMM, KC_DOT,    KC_SLSH},
        {XXXXXXX, MO(_NUMS), KC_LCTL, KC_LSFT, KC_BSPC,   KC_SPC,    KC_RSFT, KC_RCTL, MO(_NUMS), XXXXXXX},
        {XXXXXXX, KC_LHYP,   KC_LSUP, KC_LMTA, MO(_FUNC), MO(_FUNC), KC_RMTA, KC_RSUP, KC_RHYP,   XXXXXXX}
    },
    [_FUNC] = {
        {KC_ESC,  _______,   KC_UP,   _______, _______, _______, _______, _______, _______,   KC_QUOT},
        {KC_TAB,  KC_LEFT,   KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______,   KC_GRV},
        {_______, _______,   _______, _______, _______, _______, _______, KC_LBRC, KC_RBRC,   KC_BSLS},
        {XXXXXXX, MO(_NMFN), _______, _______, KC_DEL,  KC_ENT,  _______, _______, MO(_NMFN), XXXXXXX},
        {XXXXXXX, _______,   _______, _______, ___M___, ___M___, _______, _______, _______,   XXXXXXX},
    },
    [_NUMS] = {
        {_______, _______, _______, _______, _______,   _______,   KC_1,    KC_2,    KC_3,    KC_4},
        {_______, _______, _______, _______, _______,   _______,   KC_5,    KC_6,    KC_7,    KC_8},
        {_______, _______, _______, _______, _______,   _______,   KC_MINS, KC_9,    KC_0,    KC_EQL},
        {XXXXXXX, ___M___, _______, _______, _______,   _______,   _______, _______, ___M___, XXXXXXX},
        {XXXXXXX, _______, _______, _______, MO(_NMFN), MO(_NMFN), _______, _______, _______, XXXXXXX},
    },
    [_NMFN] = {
        {_______, _______, KC_PGUP, _______, _______, _______, KC_F1,   KC_F2,   KC_F3,   KC_F4},
        {_______, KC_HOME, KC_PGDN, KC_END,  _______, _______, KC_F5,   KC_F6,   KC_F7,   KC_F8},
        {_______, _______, _______, _______, _______, _______, KC_F8,   KC_F9,   KC_F10,  KC_F12},
        {XXXXXXX, ___M___, _______, _______, _______, _______, _______, _______, ___M___, XXXXXXX},
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
