#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#include "action_util.h"
#include "eeconfig.h"
#include "wait.h"

#include "klackygears.h"


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_DVRK] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        XXXXXXX,        XXXXXXX,              XXXXXXX,           XXXXXXX,           XXXXXXX,           XXXXXXX,  XXXXXXX,
        KC_ESC,         KC_QUOT,              TD(TD_COMQUES),    TD(TD_DTEX),       KC_P,              KC_Y,     XXXXXXX,
        KC_LSFT,        KC_A,                 KC_O,              KC_E,              KC_U,              KC_I,
        XXXXXXX, MT(MOD_LGUI,KC_SCLN), MT(MOD_LALT,KC_Q), MT(MOD_LCTL,KC_J), MT(MOD_LSFT,KC_K), KC_X,     XXXXXXX,
        MO(_MDIA),       KC_LGUI,              KC_LALT,           KC_LCTL,           SH_MON,
                                                                XXXXXXX,  XXXXXXX,
                                                                          XXXXXXX,
                                       LT(_SYMB,KC_SPC), LT(_NUMB,KC_BSPC), XXXXXXX,
        // right hand
             XXXXXXX,  XXXXXXX,  XXXXXXX,           XXXXXXX,           XXXXXXX,           XXXXXXX,       XXXXXXX,
             XXXXXXX,  KC_F,     KC_G,              KC_C,              KC_R,              KC_L,          LGUI(KC_L),
                       KC_D,     KC_H,              KC_T,              KC_N,              KC_S,          KC_RSFT,
             XXXXXXX,  KC_B,     MT(MOD_LSFT,KC_M), MT(MOD_LCTL,KC_W), MT(MOD_LALT,KC_V), LT(_MDIA,KC_Z), TD(TD_MCROTOG),
                                 SH_MON,            KC_RCTL,           KC_RALT,           KC_RGUI,       MO(_MDIA),
             XXXXXXX,  XXXXXXX,
             XXXXXXX,
             XXXXXXX,  LT(_NUMB,KC_TAB), LT(_SYMB,KC_ENT)
    ),

[_MDVK] = LAYOUT_ergodox(  // layer
        // left hand
        XXXXXXX,        XXXXXXX,              XXXXXXX,           XXXXXXX,           XXXXXXX,           XXXXXXX, XXXXXXX,
        TD(TD_CAPESC),  KC_QUOT,              TD(TD_COMQUES),    TD(TD_DTEX),       KC_P,              KC_Y,    XXXXXXX,
        KC_LSFT,        KC_A,                 KC_O,              KC_E,              KC_U,              KC_I,
        XXXXXXX, MT(MOD_LCTL,KC_SCLN), MT(MOD_LALT,KC_Q), MT(MOD_LGUI,KC_J), MT(MOD_LSFT,KC_K), KC_X,    XXXXXXX,
        MO(_MDIA),       KC_LCTL,              KC_LALT,           KC_LCMD,           SH_MON,
                                                   XXXXXXX,   XXXXXXX,
                                                              XXXXXXX,
                           LT(_SYMB,KC_SPC), LT(_MNMB,KC_BSPC), XXXXXXX,
        // right hand
             XXXXXXX,  XXXXXXX,                    XXXXXXX,           XXXXXXX,           XXXXXXX,           XXXXXXX,  XXXXXXX,
             XXXXXXX,  KC_F,    KC_G,              KC_C,              KC_R,              KC_L,              LGUI(KC_L),
                       KC_D,    KC_H,              KC_T,              KC_N,              KC_S,              KC_RSFT,
             XXXXXXX,  KC_B,    MT(MOD_LSFT,KC_M), MT(MOD_LGUI,KC_W), MT(MOD_LALT,KC_V), LT(_MDIA,KC_Z),     TD(TD_MCROTOG),
                                SH_MON,            KC_RCMD,           KC_RALT,           KC_RCTL,           MO(_MDIA),
             XXXXXXX, XXXXXXX,
             XXXXXXX,
             XXXXXXX,     LT(_MNMB,KC_TAB), LT(_SYMB,KC_ENT)
    ),

// _SYMBOLS
[_NUMB] = LAYOUT_ergodox(
       // left hand
       KC_TRNS,    KC_TRNS,     KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,      KC_TRNS,
       KC_TRNS,    KC_PGUP,     KC_PGDN,    KC_HOME,     KC_END,      TD(TD_FNDR),  KC_TRNS,
       LCTL(KC_5), KC_LEFT,     KC_UP,      KC_DOWN,     KC_RIGHT,    TD(TD_PTSP),
       KC_TRNS,    TD(TD_ACCW), LCTL(KC_A), TD(TD_CCPY), TD(TD_PSTI), TD(TD_DDEL),  KC_TRNS,
       KC_TRNS,    KC_TRNS,     KC_TRNS,    KC_TRNS,     KC_TRNS,
                                                                      KC_TRNS,      KC_TRNS,
                                                                                    KC_TRNS,
                                                         KC_TRNS,     KC_TRNS,      KC_TRNS,
       // right hand
       KC_TRNS,   KC_TRNS,       KC_TRNS,           KC_TRNS,           KC_TRNS,           KC_TRNS,              KC_TRNS,
       KC_TRNS,   TD(TD_MINPLS), KC_7,              KC_8,              KC_9,              KC_PPLS,              KC_TRNS,
                  TD(TD_DIVMLT), KC_4,              KC_5,              KC_6,              C_S_T(KC_0),          KC_TRNS,
       KC_TRNS,   TD(TD_DOTEQL), KC_1,              MT(MOD_LCTL,KC_2), MT(MOD_LALT,KC_3), MT(MOD_LGUI,KC_0),    KC_TRNS,
                                 KC_0,              KC_TRNS,           KC_TRNS,           KC_TRNS,              KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),

// _SYMBOLS
[_MNMB] = LAYOUT_ergodox(
       // left hand
       KC_TRNS,    KC_TRNS,     KC_TRNS,    KC_TRNS,       KC_TRNS,        KC_TRNS,  KC_TRNS,
       KC_TRNS,    KC_PGUP,     KC_PGDN,    KC_HOME,       KC_END,         KC_TRNS,  KC_TRNS,
       KC_TRNS,    KC_LEFT,     KC_UP,      KC_DOWN,       KC_RIGHT,       KC_TRNS,
       KC_TRNS,    KC_TRNS,     LGUI(KC_A), TD(TD_MCCCPY), TD(TD_MCPSTIN), KC_TRNS,  KC_TRNS,
       KC_TRNS,    KC_TRNS,     KC_TRNS,    KC_TRNS,       KC_TRNS,
                                                                      KC_TRNS,      KC_TRNS,
                                                                                    KC_TRNS,
                                                         KC_TRNS,     KC_TRNS,      KC_TRNS,
       // right hand
       KC_TRNS,   KC_TRNS,       KC_TRNS,           KC_TRNS,           KC_TRNS,           KC_TRNS,              KC_TRNS,
       KC_TRNS,   TD(TD_MINPLS), KC_7,              KC_8,              KC_9,              KC_PPLS,              KC_TRNS,
                  TD(TD_DIVMLT), KC_4,              KC_5,              KC_6,              C_S_T(KC_0),          KC_TRNS,
       KC_TRNS,   TD(TD_DOTEQL), KC_1,              MT(MOD_LGUI,KC_2), MT(MOD_LALT,KC_3), MT(MOD_LCTL,KC_0),    KC_TRNS,
                                 KC_0,              KC_TRNS,           KC_TRNS,           KC_TRNS,              KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),

// MEDIA AND MOUSE
[_MDIA] = LAYOUT_ergodox(
       XXXXXXX, XXXXXXX,  XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
       XXXXXXX, KC_PGUP,  KC_PGDOWN, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
       XXXXXXX, KC_MS_L,  KC_MS_U,   KC_MS_D, KC_MS_R, KC_TRNS,
       XXXXXXX, KC_TRNS,  KC_WH_U,   KC_WH_D, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS,
                                                       KC_BTN3, KC_TRNS,
                                                                KC_TRNS,
                                              KC_BTN1, KC_BTN2, KC_TRNS,
    // right hand
       XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
       XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                 XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, KC_TRNS, XXXXXXX,
       XXXXXXX,  XXXXXXX, KC_ACL0, KC_ACL1, KC_ACL2, KC_TRNS, XXXXXXX,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_WBAK
),
//Keymap 4: FN & Punctuation
[_SYMB] = LAYOUT_ergodox(
       KC_TRNS,   KC_TRNS,      KC_TRNS,   KC_TRNS,              KC_TRNS,      KC_TRNS, KC_TRNS,
       KC_CIRC,   KC_BSLS,      KC_AT,     KC_HASH,              KC_DLR,       KC_PERC, KC_TRNS,
       KC_TRNS,   KC_PLUS,      KC_MINS,   KC_ASTR,              KC_SLSH,      KC_EQL,
       KC_TRNS,   KC_LBRC,      KC_RBRC,   KC_LPRN,              KC_RPRN,      KC_AMPR, KC_TRNS,
       KC_TRNS,   KC_TRNS,      KC_TRNS,   KC_TRNS,              KC_TRNS,
                                                        KC_TRNS,  KC_TRNS,
                                                                  KC_TRNS,
                                                 KC_TRNS, KC_DEL, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,            KC_TRNS,            KC_TRNS,            KC_TRNS,
       KC_TRNS,  TO(_MDVK), KC_F9,              KC_F10,             KC_F11,             KC_F12,             KC_TRNS,
                 TO(_DVRK), KC_F5,              KC_F6,              KC_F7,              KC_F8,              KC_TRNS,
       KC_TRNS,  KC_TRNS,  KC_F1,              KC_F2,              KC_F3,              KC_F4,              KC_TRNS,
                           KC_TRNS,            KC_TRNS,            KC_TRNS,            KC_TRNS,            KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_CAPS
),

};


