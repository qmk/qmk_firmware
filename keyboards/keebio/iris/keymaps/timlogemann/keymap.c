#include QMK_KEYBOARD_H

#define _DEFAULT 0
#define _WINDOWS 1
#define _MOD 2
#define _MOUSE 3
#define _NUMPAD 4
#define _MEDIA 5
#define _WINDOWS_MEDIA 6
// #define _G_AC 3

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
#define PRV KC_MEDIA_REWIND
#define W_PRV KC_MEDIA_PREV_TRACK
#define NXT KC_MEDIA_FAST_FORWARD
#define W_NXT KC_MEDIA_NEXT_TRACK

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

// Leader Key Sequences
LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    // SEQ_ONE_KEY(KC_1) {
    //     // Move to Layer 1
    //     layer_move(_DEFAULT);
    // }
    // SEQ_ONE_KEY(KC_2) {
    //     // Move to Layer 2
    //     layer_move(_MOD);
    // }
    // SEQ_ONE_KEY(KC_3) {
    //     // Move to Layer 3
    //     layer_move(_MOUSE);
    // }
    SEQ_TWO_KEYS(KC_D, KC_D) {
        SEND_STRING(SS_LCTL("a") SS_LCTL("c"));
    }
    SEQ_THREE_KEYS(KC_D, KC_D, KC_S) {
      SEND_STRING("https://start.duckduckgo.com\n");
    }
    SEQ_TWO_KEYS(KC_A, KC_S) {
      register_code(KC_LGUI);
      register_code(KC_S);
      unregister_code(KC_S);
      unregister_code(KC_LGUI);
    }
   SEQ_TWO_KEYS(KC_O, KC_S) {
        tap_code16(CG_TOGG);
    }
  }
}

// Combos
// Toggle Game Layers
// const uint16_t PROGMEM G_AC_COMBO[] = {KC_LGUI, KC_GESC, COMBO_END};

// // Create Combo map
// combo_t key_combos[COMBO_COUNT] = {COMBO(G_AC_COMBO, KC_ESC)}; // TO(_G_AC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_DEFAULT] = LAYOUT(
        //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
            KC_ESC,  KC_1,    KC_2,    KC_3,   KC_4,   KC_5,                               KC_6,    KC_7,      KC_8,   KC_9,   KC_0,    KC_BSPC,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
            KC_TAB,   KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,                               KC_Y,    KC_U,      KC_I,   KC_O,   KC_P,    KC_EQUAL,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
            SHFT_CPS, KC_A,    KC_S,    KC_D,   KC_F,   KC_G,                               KC_H,    KC_J,      KC_K,   KC_L,   KC_SCLN, KC_QUOT,
        //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            KC_LCTL, KC_LEAD,    KC_Z,    KC_X,   KC_C,   KC_V,       _,                _,    KC_B,    KC_N,      KC_M,   KC_COMM, MH_DT,  KC_SLSH,
        //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┤        ┤        ├        ┼────┬───┴───┬────┴───┬────┴────────┴────────┴────────┘
                                            L_ALT, KC_LGUI,     LT(_NUMPAD, KC_ENT),    LT(_MEDIA, KC_SPC),      TT(_MOD), R_ALT
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
                                            L_ALT, KC_LCTL,     LT(_NUMPAD, KC_ENT),    LT(_WINDOWS_MEDIA, KC_SPC),      TT(_MOD), R_ALT
                                       //└────────┴────────┘    └────────┘        └────────┘    └───────┴────────┘
        ),

    [_MOD] = LAYOUT(
        //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
            HP_GR,   KC_F1,   KC_F2,    KC_F3,  KC_F4,     _,                                  _,       _,      _,        _,      _,      KC_DEL,
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
            KC_TRNS,    _,      _,       _,       _,       _,                                MS_SU,    MS_B1,   MS_UP,   MS_B2,      _,      _,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
            KC_TRNS,    _,      _,       _,       _,       _,                                MS_SD,    MS_LT,   MS_DN,   MS_RT,      _,      _,
        //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
              _,    KC_LEAD,   KC_TRNS,   _,         _,      _,        _,                _,       _,      MS_SL,    _,      MS_SR,    _,       _,
        //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┤        ┤        ├        ┼────┬───┴───┬────┴───┬────┴────────┴────────┴────────┘
                                            _,      RGB_RMOD,     KC_TRNS,           KC_TRNS,    RGB_MOD,   _
                                       //└────────┴────────┘    └────────┘        └────────┘    └───────┴────────┘
        ),
    [_NUMPAD] = LAYOUT(KC_TRNS,KC_TRNS,KC_KP_7,KC_KP_8,KC_KP_9,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_KP_4,KC_KP_5,KC_KP_6,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_KP_1,KC_KP_2,KC_KP_3,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_KP_0,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS),
    [_MEDIA] = LAYOUT(KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,PRV,PLPS,NXT,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS),
    [_WINDOWS_MEDIA] = LAYOUT(KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,VOLUP,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,VOLDOWN,W_PRV,PLPS,W_NXT,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS)
};
