#include QMK_KEYBOARD_H

#define _1L 0
#define _2L 1
#define _3L 2
#define _G_AC 3

#define HP_GR HYPR_T(KC_GRAVE)
#define MH_DT MEH_T(KC_DOT)
#define SHFT_CPS LSFT_T(OSM(MOD_LSFT))
#define SHFT_QT RSFT_T(KC_QUOT)
#define L_ALT KC_LAPO
#define R_ALT KC_RAPC
#define CTL_OSL MT(MOD_LCTL, OSL(_2L))
#define TAB_DANCE LT(2, KC_TAB)
#define _ KC_NO

#define VOLDOWN KC__VOLDOWN
#define VOLUP KC__VOLUP
#define PLPS KC_MEDIA_PLAY_PAUSE
#define FWD KC_MEDIA_FAST_FORWARD
#define RWD KC_MEDIA_REWIND

// Mouse keys
#define MS_UP KC_MS_UP
#define MS_DN KC_MS_D
#define MS_LT KC_MS_L
#define MS_RT KC_MS_R
#define MS_B1 KC_MS_BTN1
#define MS_B2 KC_MS_BTN2
#define MS_B3 KC_MS_BTN3
#define MS_B4 KC_MS_BTN4
#define MS_B5 KC_MS_BTN5
#define MS_SU KC_MS_WH_UP
#define MS_SD KC_MS_WH_DOWN
#define MS_SL KC_MS_WH_LEFT
#define MS_SR KC_MS_WH_RIGHT


// Combos
// Toggle Game Layers
const uint16_t PROGMEM test_combo[] = {KC_LGUI, KC_GESC, KC_ENT, COMBO_END};

// Create Combo map
combo_t key_combos[COMBO_COUNT] = {COMBO(test_combo, TO(_G_AC))};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_1L] = LAYOUT(
        //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
            KC_GESC,  KC_1,    KC_2,    KC_3,   KC_4,   KC_5,                               KC_6,    KC_7,      KC_8,   KC_9,   KC_0,    KC_BSPC,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
            KC_TAB,   KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,                               KC_Y,    KC_U,      KC_I,   KC_O,   KC_P,    KC_EQUAL,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
            SHFT_CPS, KC_A,    KC_S,    KC_D,   KC_F,   KC_G,                               KC_H,    KC_J,      KC_K,   KC_L,   KC_SCLN, KC_QUOT,
        //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            CTL_OSL, HP_GR,    KC_Z,    KC_X,   KC_C,   KC_V,       _,                _,    KC_B,    KC_N,      KC_M,   KC_COMM, MH_DT,  KC_SLSH,
        //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┤        ┤        ├        ┼────┬───┴───┬────┴───┬────┴────────┴────────┴────────┘
                                            L_ALT, KC_LGUI,     KC_ENT,          KC_SPC,      TT(_2L), R_ALT
                                       //└────────┴────────┘    └────────┘        └────────┘    └───────┴────────┘
        ),

    [_2L] = LAYOUT(
        //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
            KC_GESC, KC_F1,    KC_F2, KC_F3,    KC_F4,  KC_F5,                                 KC_F6,   KC_F7,  KC_F8,  KC_F9,  KC_F10,   KC_DEL,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
            KC_TRNS,  KC_F11, KC_F12,  VOLUP,    _,    TO(_3L),                               _,    KC_PGUP,   KC_UP, KC_PGDN,    _,     KC_MINUS,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
            KC_TRNS,  _,       RWD,     PLPS,    FWD,      _,                                  _,    KC_LEFT, KC_DOWN, KC_RGHT,    _,     KC_PAST,
        //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            KC_TRNS, KC_TRNS,   _,    VOLDOWN,    _,      +KC_PLUS, _,                _,    KC_MINUS, KC_HOME, _,       KC_END, KC_TRNS, KC_BSLASH,
        //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┤        ┤        ├        ┼────┬───┴───┬────┴───┬────┴────────┴────────┴────────┘
                                LALT_T(KC_LBRC),    KC_TRNS,    KC_TRNS,            KC_TRNS,     KC_TRNS, RALT_T(KC_RBRC)
                                       //└────────┴────────┘    └────────┘        └────────┘    └───────┴────────┘
        ),
    [_3L] = LAYOUT(
        //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
            TO(_1L), KC_1,    KC_2,     KC_3,   _,          _,                                  _,       _,      _,      _,          _,      _,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
            KC_TRNS, KC_4,      KC_5,   KC_6,   _,          _,                              MS_SU,      MS_SL, MS_UP,   MS_SR,      _,      _,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
            KC_TRNS, KC_7,      KC_8,   KC_9,   _,          _,                              MS_SD,      MS_LT, MS_DN,   MS_RT,      _,      _,
        //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
              _,    KC_MINUS,   KC_0,   KC_PLUS, _,         _,      _,                  _,  _,          MS_B1, MS_B2,   MS_B3,  MS_B4,      _,
        //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┤        ┤        ├        ┼────┬───┴───┬────┴───┬────┴────────┴────────┴────────┘
                                            _,        _,          KC_TRNS,              _,          _,      _
                                       //└────────┴────────┘    └────────┘        └────────┘    └───────┴────────┘
        ),

    [_G_AC] = LAYOUT(
        //┌────────┬────────┬────────┬────────┬────────┬────────┐
            KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,  KC_GRAVE,                            _, _, _, _, _, _,
        //├────────┼────────┼────────┼────────┼────────┼────────┤
            KC_T,     KC_G,    KC_Q,    KC_W,    KC_E,    KC_R,                              _, _, _, _, _, _,
        //├────────┼────────┼────────┼────────┼────────┼────────┤
              _,       _,      KC_A,    KC_S,    KC_D,     _,                              _, _, _, _, _, _,
        //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐
              KC_M,    KC_Z,   KC_X,    KC_C,     KC_X,     KC_V,      _,                  _, _, _, _, _, _, _,
        //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┤        ┤
                                            KC_F,     KC_SPACE,     KC_SHIFT,              TO(_1L), _, _
                                       //└────────┴────────┘    └────────┘
    ),

};
