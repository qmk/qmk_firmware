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

typedef struct {
    bool is_press_action;
    uint8_t state;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP, // Send two single taps
    TRIPLE_TAP,
    TRIPLE_HOLD
};

// Tap Dance declarations
enum {
    PLAY,
    PREV,
    NEXT
};

uint8_t cur_dance(qk_tap_dance_state_t *state);

// For the x tap dance. Put it here so it can be used in any keymap
void play_finished(qk_tap_dance_state_t *state, void *user_data);
void play_reset(qk_tap_dance_state_t *state, void *user_data);



// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    // [_7] = ACTION_TAP_DANCE_DOUBLE(KC_7, KC_MEDIA_FAST_FORWARD),
    // [_8] = ACTION_TAP_DANCE_DOUBLE(KC_8, KC_MEDIA_PLAY_PAUSE),
    // [_9] = ACTION_TAP_DANCE_DOUBLE(KC_9, KC_MEDIA_REWIND)
    [PLAY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, play_finished, play_reset)
    // [PREV] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished, x_reset)
    // [NEXT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished, x_reset)
};

uint8_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        // DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TRIPLE_TAP;
        else return TRIPLE_HOLD;
    } else return 8; // Magic number. At some point this method will expand to work for more presses
}

// Create an instance of 'tap' for the 'x' tap dance.
static tap playtap_state = {
    .is_press_action = true,
    .state = 0
};

void play_finished(qk_tap_dance_state_t *state, void *user_data) {
    playtap_state.state = cur_dance(state);
    switch (playtap_state.state) {
        case SINGLE_TAP:
        case SINGLE_HOLD: register_code(KC_8); break;

        case DOUBLE_TAP:
        case DOUBLE_HOLD:
            register_code(KC_MEDIA_PLAY_PAUSE);
            break;

        case DOUBLE_SINGLE_TAP: tap_code(KC_8); register_code(KC_8);
            break;
    }
}

void play_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (playtap_state.state) {
        case SINGLE_TAP:
        case SINGLE_HOLD: unregister_code(KC_8);
            break;
        case DOUBLE_TAP:
        case DOUBLE_HOLD: unregister_code(KC_MEDIA_PLAY_PAUSE); break;
        case DOUBLE_SINGLE_TAP:
            unregister_code(KC_8);
            break;

    }
    playtap_state.state = 0;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_DEFAULT] = LAYOUT(
        //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
            KC_ESC,  KC_1,    KC_2,    KC_3,   KC_4,   KC_5,                               KC_6,       KC_7,   KC_8,  KC_9,    KC_0,   KC_BSPC,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
            KC_TAB,   KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,                               KC_Y,    KC_U,      KC_I,   KC_O,   KC_P,    KC_EQUAL,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
            SHFT_CPS, KC_A,    KC_S,    KC_D,   KC_F,   KC_G,                               KC_H,    KC_J,      KC_K,   KC_L,   KC_SCLN, KC_QUOT,
        //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            KC_LCTL, HP_GR,    KC_Z,    KC_X,   KC_C,   KC_V,       _,                _,    KC_B,    KC_N,      KC_M,   KC_COMM, MH_DT,  KC_SLSH,
        //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┤        ┤        ├        ┼────┬───┴───┬────┴───┬────┴────────┴────────┴────────┘
                                            KC_LAPO, KC_LGUI,     LT(_NUMPAD, KC_ENT),  LT(_MEDIA, KC_SPC),   TT(_MOD), KC_RAPC
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
                                            KC_LAPO, KC_LCTL,     LT(_NUMPAD, KC_ENT),  LT(_WINDOWS_MEDIA, KC_SPC),      TT(_MOD), KC_RAPC
                                       //└────────┴────────┘    └────────┘        └────────┘    └───────┴────────┘
        ),

    [_MOD] = LAYOUT(
        //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
            KC_GRAVE,   KC_F1,   KC_F2,    KC_F3,  KC_F4,     _,                                  _,       KC_MEDIA_PREV_TRACK,    KC_MEDIA_PLAY_PAUSE,    KC_MEDIA_NEXT_TRACK,      _,      KC_DEL,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
            KC_TRNS,  KC_F5,   KC_F6,  KC_F7,  KC_F8,   TT(_MOUSE),                          KC_VOLU,    KC_PGUP,  KC_UP, KC_PGDN,    _,     KC_MINUS,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
            KC_TRNS,   KC_F9,   KC_F10, KC_F11, KC_F12,  _,                                  KC_VOLD,    KC_LEFT, KC_DOWN, KC_RGHT,    _,     KC_PAST,
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
