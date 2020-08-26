#include QMK_KEYBOARD_H

#define _DEFAULT 0
#define _WINDOWS 1
#define _MOD 2
#define _MOUSE 3
#define _NUMPAD 4
#define _MEDIA 5
#define _WINDOWS_MEDIA 6

#define HP_GR HYPR_T(KC_GRAVE)
#define MH_DT MEH_T(KC_DOT)
#define SHFT_CPS LSFT_T(OSM(MOD_LSFT))
#define _ KC_NO


// Tap Dance declarations
enum {
    _7,
    _8,
    _9
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [_7] = ACTION_TAP_DANCE_DOUBLE(KC_7, KC_MEDIA_FAST_FORWARD),
    [_8] = ACTION_TAP_DANCE_DOUBLE(KC_8, KC_MEDIA_PLAY_PAUSE),
    [_9] = ACTION_TAP_DANCE_DOUBLE(KC_9, KC_MEDIA_REWIND)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_DEFAULT] = LAYOUT(
        //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
            KC_ESC,  KC_1,    KC_2,    KC_3,   KC_4,   KC_5,                               KC_6,       TD(_7),   TD(_8),  TD(_9),    KC_0,   KC_BSPC,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
            KC_TAB,   KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,                               KC_Y,    KC_U,      KC_I,   KC_O,   KC_P,    KC_EQUAL,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
            SHFT_CPS, KC_A,    KC_S,    KC_D,   KC_F,   KC_G,                               KC_H,    KC_J,      KC_K,   KC_L,   KC_SCLN, KC_QUOT,
        //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            KC_LCTL, HP_GR,    KC_Z,    KC_X,   KC_C,   KC_V,       _,                _,    KC_B,    KC_N,      KC_M,   KC_COMM, MH_DT,  KC_SLSH,
        //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┤        ┤        ├        ┼────┬───┴───┬────┴───┬────┴────────┴────────┴────────┘
                                            KC_LAPO, KC_LGUI,     LT(_NUMPAD, KC_ENT),  KC_SPC,      TT(_MOD), KC_RAPC
                                       //└────────┴────────┘    └────────┘        └────────┘    └───────┴────────┘
        ),


    [_WINDOWS] = LAYOUT(
        //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
            KC_ESC,  KC_1,    KC_2,    KC_3,   KC_4,   KC_5,                               KC_6,    KC_7,      KC_8,   KC_9,   KC_0,    KC_BSPC,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
            KC_TAB,   KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,                               KC_Y,    KC_U,      KC_I,   KC_O,   KC_P,    KC_EQUAL,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
            SHFT_CPS, KC_A,    KC_S,    KC_D,   KC_F,   KC_G,                               KC_H,    KC_J,      KC_K,   KC_L,   KC_SCLN, KC_QUOT,
        //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            KC_LGUI, KC_LEAD,    KC_Z,    KC_X,   KC_C,   KC_V,       _,                _,    KC_B,    KC_N,      KC_M,   KC_COMM, MH_DT,  KC_SLSH,
        //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┤        ┤        ├        ┼────┬───┴───┬────┴───┬────┴────────┴────────┴────────┘
                                            KC_LAPO, KC_LCTL,     LT(_NUMPAD, KC_ENT),  KC_SPC,      TT(_MOD), KC_RAPC
                                       //└────────┴────────┘    └────────┘        └────────┘    └───────┴────────┘
        ),

    [_MOD] = LAYOUT(
        //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
            KC_GRAVE,   KC_F1,   KC_F2,    KC_F3,  KC_F4,     _,                                  _,       KC_MEDIA_REWIND,    KC_MEDIA_PLAY_PAUSE,    KC_MEDIA_FAST_FORWARD,      _,      KC_DEL,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
            KC_TRNS,  KC_F5,   KC_F6,  KC_F7,  KC_F8,   TT(_MOUSE),                             _,    KC_PGUP,  KC_UP, KC_PGDN,    _,     KC_MINUS,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
            KC_TRNS,   KC_F9,   KC_F10, KC_F11, KC_F12,  _,                                  _,    KC_LEFT, KC_DOWN, KC_RGHT,    _,     KC_PAST,
        //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            KC_TRNS, KC_TRNS,   _,       _,       _,       _,       _,                _,    KC_MINUS, KC_HOME,   _,     KC_END, KC_TRNS, KC_BSLASH,
        //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┤        ┤        ├        ┼────┬───┴───┬────┴───┬────┴────────┴────────┴────────┘
                                LALT_T(KC_LBRC),    KC_TRNS,    KC_TRNS,            KC_TRNS,     KC_TRNS, RALT_T(KC_RBRC)
                                       //└────────┴────────┘    └────────┘        └────────┘    └───────┴────────┘
        ),
    [_MOUSE] = LAYOUT(
        //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
        TO(_DEFAULT),   _,    KC_TRNS,  _,       _,      RGB_TOG,                             _,       _,       _,       _,       _,        _,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
            KC_TRNS,    _,      _,       _,       _,       _,                                KC_MS_WH_UP,    KC_MS_BTN1,   KC_MS_UP,   KC_MS_BTN2,      _,      _,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
            KC_TRNS,    _,      _,       _,       _,       _,                                KC_MS_WH_DOWN,    KC_MS_L,   KC_MS_D,   KC_MS_R,      _,      _,
        //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
              _,    KC_LEAD,   KC_TRNS,   _,         _,      _,        _,                _,       _,      KC_MS_WH_LEFT,    _,      KC_MS_WH_RIGHT,    _,       _,
        //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┤        ┤        ├        ┼────┬───┴───┬────┴───┬────┴────────┴────────┴────────┘
                                            _,      RGB_RMOD,     KC_TRNS,           KC_TRNS,    RGB_MOD,   _
                                       //└────────┴────────┘    └────────┘        └────────┘    └───────┴────────┘
        ),
    [_NUMPAD] = LAYOUT(KC_TRNS,KC_TRNS,KC_KP_7,KC_KP_8,KC_KP_9,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_KP_4,KC_KP_5,KC_KP_6,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_KP_1,KC_KP_2,KC_KP_3,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_KP_0,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS),
    [_MEDIA] = LAYOUT(KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC__VOLUP,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC__VOLDOWN,KC_MEDIA_REWIND,KC_MEDIA_PLAY_PAUSE,KC_MEDIA_FAST_FORWARD,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS),
    [_WINDOWS_MEDIA] = LAYOUT(KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC__VOLUP,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC__VOLDOWN,KC_MEDIA_PREV_TRACK,KC_MEDIA_PLAY_PAUSE,KC_MEDIA_NEXT_TRACK,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS)
};
