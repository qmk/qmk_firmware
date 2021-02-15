#include "64key.h"
#include <keymap_colemak.h>
#include <sendstring_colemak.h>

enum layer_names {
    _QWERTY,   // OS-side Colemak. Default.
    _COLEMAK,  // Keyboard-side Colemak. Portability, emergency.
    _GAMING,   // Navigation clusters (only) change hands.
    _NUMERIC   // Numbers, function keys, special characters, mouse.
};

enum taps {
    PNX,  // Play/pause; next track.
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [PNX] = ACTION_TAP_DANCE_DOUBLE(KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK),
};

// Shorthand:
#define LAYER_N MO(_NUMERIC)
#define LAYER_C TG(_COLEMAK)
#define LAYER_G TG(_GAMING)
#define PASTE LSFT(KC_INS)  // Terminal-compatible paste.
#define SLQ RALT(KC_9)  // Single left-side quotation mark (in Colemak).
#define SRQ RALT(KC_0)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_64key(
                      KC_LSPO, KC_MINS, KC_EQL,
                      KC_LCPO, KC_LGUI, KC_HAEN, KC_ENT,
                               KC_LAPO, KC_SPC,  SLQ,

                      CM_W,    CM_F,    CM_P,    CM_G,
    KC_TAB,  CM_Q,    CM_R,    CM_S,    CM_T,    CM_D,
    KC_BSPC, CM_A,    CM_X,    CM_C,    CM_V,    CM_B,
    KC_DEL,  CM_Z,    KC_HOME, KC_PGUP, KC_END,
                               KC_PGDN,

             KC_VOLD, KC_VOLU, KC_RSPC,
    KC_MUTE, TD(PNX), LAYER_N, KC_RCPC,
    SRQ,     KC_ESC,  KC_RAPC,

    CM_J,    CM_L,    CM_U,    CM_Y,
    CM_H,    CM_N,    CM_E,    CM_I,    CM_SCLN, KC_BSLS,
    CM_K,    CM_M,    KC_COMM, KC_DOT,  CM_O,    KC_QUOT,
             KC_LEFT, KC_UP,   KC_RGHT, KC_SLSH, KC_GRV,
                      KC_DOWN
),

[_COLEMAK] = LAYOUT_64key(
                      _______, _______, _______,
                      _______, _______, _______, _______,
                               _______, _______, _______,

                      KC_W,    KC_F,    KC_P,    KC_G,
    _______, KC_Q,    KC_R,    KC_S,    KC_T,    KC_D,
    _______, KC_A,    KC_X,    KC_C,    KC_V,    KC_B,
    _______, KC_Z,    _______, _______, _______,
                               _______,

             _______, _______, _______,
    _______, _______, _______, _______,
    _______, _______, _______,

    KC_J,    KC_L,    KC_U,    KC_Y,
    KC_H,    KC_N,    KC_E,    KC_I,    KC_SCLN, _______,
    KC_K,    KC_M,    _______, _______, KC_O,    _______,
             _______, _______, _______, _______, _______,
                      _______
),

[_GAMING] = LAYOUT_64key(
                      _______, _______, _______,
                      _______, _______, _______, _______,
                               _______, _______, _______,

                      _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,
    _______, _______, KC_LEFT, KC_UP,   KC_RGHT,
                               KC_DOWN,

             _______, _______, _______,
    _______, _______, _______, _______,
    _______, _______, _______,

    _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,
             KC_HOME, KC_PGUP, KC_END,  _______, _______,
                      KC_PGDN
),

[_NUMERIC] = LAYOUT_64key(
                      _______, _______, _______,
                      _______, _______, LAYER_C, _______,
                               _______, _______, _______,

                      KC_F2,   KC_F3,   KC_F4,   KC_F5,
    KC_F12,  KC_F1,   KC_2,    KC_3,    KC_4,    KC_5,
    _______, KC_1,    KC_AT,   KC_HASH, KC_DLR,  KC_PERC,
    KC_INS,  KC_EXLM, KC_BTN1, KC_BTN3, KC_BTN2,
                               LAYER_G,

             KC_ACL1, KC_ACL2, _______,
    KC_ACL0, _______, _______, _______,
    KC_SLEP, _______, _______,

    KC_F6,   KC_F7,   KC_F8,   KC_F9,
    KC_6,    KC_7,    KC_8,    KC_9,    KC_F10,  KC_F11,
    KC_CIRC, KC_AMPR, KC_ASTR, KC_APP,  KC_0,    PASTE,
             KC_MS_L, KC_MS_U, KC_MS_R, KC_PSCR, RESET,
                      KC_MS_D
)
};
