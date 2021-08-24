#include QMK_KEYBOARD_H

enum bfo900_layers { _OSX, _OSXMACROS, _WINDOWS, _WINDOWSMACROS, _GAMING, _SYMBOLS };
enum bfo9000_keycodes { JIGGLER = SAFE_RANGE, ALT_TAB };

// jiggler items
bool            mouse_jiggle_mode = true;
static uint32_t jiggle_timer      = 0;

// super alt tab items
bool     is_alt_tab_active = false;
uint16_t alt_tab_timer     = 0;
uint16_t alt_tab_modifier  = KC_LGUI;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_OSX] = LAYOUT(
        KC_ESC,       A(KC_P0),       KC_ESC,  KC_F1,        KC_F2,        KC_F3,        KC_F4,        KC_F5,          KC_WH_U,              KC_VOLU,      KC_F6,        KC_F7,        KC_F8,        KC_F9,        KC_F10,                 KC_F11,   KC_F12,  KC_DEL,
        A(KC_PPLS),   A(KC_PMNS),     KC_GRV,  KC_1,         KC_2,         KC_3,         KC_4,         KC_5,           KC_WH_D,              KC_VOLD,      KC_6,         KC_7,         KC_8,         KC_9,         KC_0,                   _______,  _______, KC_BSPC,
        _______,      _______,        KC_TAB,  KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,           _______,              KC_EQL,       KC_Y,         KC_U,         KC_I,         KC_O,         KC_P,                   _______,  _______, _______,
        DM_PLY1,      DM_PLY2,        KC_ESC,  LCTL_T(KC_A), LGUI_T(KC_S), LSFT_T(KC_D), LOPT_T(KC_F), KC_G,           KC_BSPC,              KC_MINS,      KC_H,         LOPT_T(KC_J), LSFT_T(KC_K), LGUI_T(KC_L), LCTL_T(KC_SCLN),        KC_QUOT,  KC_ENT,  KC_NO,
        TO(_WINDOWS), TO(_GAMING),    KC_LSFT, KC_Z,         KC_X,         KC_C,         KC_V,         KC_B,           ALT_TAB,              KC_B,         KC_N,         KC_M,         KC_COMM,      KC_DOT,       KC_SLSH,                KC_RSFT,  KC_UP,   A(KC_P0),
        TO(_OSX),     MO(_OSXMACROS), KC_LCTL, LCTL(KC_B),   KC_LCTL,      KC_LALT,      KC_LGUI,      KC_SPC,  MO(_OSXMACROS),              MO(_SYMBOLS), KC_MRWD,      KC_MPLY,      KC_MFFD,      JIGGLER,      LCTL(LSFT(LGUI(KC_4))), KC_LEFT,  KC_DOWN, KC_RGHT
    ),
    [_OSXMACROS] = LAYOUT(
        G(C(KC_Q)), _______, _______, _______,  _______,  _______,  _______,  _______,        _______,                                _______, _______,    _______,  _______,     _______,  _______, _______, _______, _______,
        _______,    _______, _______, _______,  _______,  _______,  _______,  _______,        _______,                                _______, _______,    _______,  _______,     _______,  _______, _______, _______, _______,
        DM_REC1,    DM_REC2, _______, _______,  _______,  A(KC_P6), A(KC_P7), A(KC_P3),       _______,                                KC_VOLU, _______,    _______,  _______,     _______,  _______, _______, _______, _______,
        DM_RSTP,    DM_RSTP, _______, A(KC_P9), A(KC_P1), _______,  A(KC_P5), A(KC_KP_ENTER), KC_DEL,                                 KC_VOLD, KC_LEFT,    KC_DOWN,  KC_UP,       KC_RIGHT, _______, _______, _______, _______,
        _______,    _______, _______, _______,  _______,  A(KC_P8), A(KC_P4), _______,        _______,                                _______, _______,    A(KC_P2), _______,     _______,  _______, _______, _______, _______,
        _______,    _______, _______, _______,  _______,  _______,  _______,  _______,        _______,                                _______, G(KC_LEFT), _______,  G(KC_RIGHT), _______,  _______, _______, _______, _______
    ),
    [_SYMBOLS] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______,                 _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5), _______,                 _______, S(KC_6), S(KC_7), S(KC_8), S(KC_9), S(KC_0), _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______,                 KC_EQL,  _______, KC_LBRC, KC_RBRC, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______,                 KC_MINS, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______,                 KC_BSLS, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______,                 _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_WINDOWS] = LAYOUT(
        KC_ESC,  KC_9,               _______, _______,      _______,      _______,      _______,      _______, _______,               _______,      _______, _______, _______, _______, _______, _______, _______, _______,
        KC_7,    KC_8,               _______, _______,      _______,      _______,      _______,      _______, _______,               _______,      _______, _______, _______, _______, _______, _______, _______, _______,
        KC_5,    KC_6,               _______, _______,      _______,      _______,      _______,      _______, _______,               _______,      _______, _______, _______, _______, _______, _______, _______, _______,
        KC_3,    KC_4,               _______, LCTL_T(KC_A), LGUI_T(KC_S), LSFT_T(KC_D), LOPT_T(KC_F), _______, _______,               _______,      _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______,            _______, _______,      _______,      _______,      _______,      _______, ALT_TAB,               _______,      _______, _______, _______, _______, _______, _______, _______, _______,
        _______, MO(_WINDOWSMACROS), KC_LCTL, KC_LCTL,      KC_LALT,      KC_LGUI,      KC_LCTL,      KC_SPC,  MO(_WINDOWSMACROS),    MO(_SYMBOLS), KC_MRWD, KC_MPLY, KC_MFFD, KC_WSCH, KC_PSCR, _______, _______, _______
    ),
    [_WINDOWSMACROS] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______,                                              _______, _______, _______, _______, _______,  _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______,                                              _______, _______, _______, _______, _______,  _______, _______, _______, _______,
        DM_REC1, DM_REC2, _______, _______, _______, _______, _______, _______, _______,                                              _______, _______, _______, _______, _______,  _______, _______, _______, _______,
        DM_RSTP, DM_RSTP, _______, _______, _______, _______, _______, _______, KC_DEL,                                               _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______,                                              _______, _______, _______, _______, _______,  _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______,                                              _______, KC_VOLD, _______, KC_VOLU, _______,  _______, _______, _______, _______
    ),
    [_GAMING] = LAYOUT(
        KC_ESC,  KC_9,               _______, _______, _______, _______, _______, _______,  KC_VOLU,                                  _______,      _______, _______, _______, _______, _______, _______, _______, _______,
        KC_7,    KC_8,               _______, _______, _______, _______, _______, _______,  KC_VOLD,                                  _______,      _______, _______, _______, _______, _______, _______, _______, _______,
        ALT_TAB, +KC_6,               _______, _______, _______, _______, _______, _______, A(KC_P0),                                 _______,      _______, _______, _______, _______, _______, _______, _______, _______,
        KC_3,    KC_4,               KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,     KC_BSPC,                                  _______,      _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______,            _______, _______, _______, _______, _______, _______,  LSFT(KC_SPC),                             _______,      _______, _______, _______, _______, _______, _______, _______, _______,
        _______, MO(_WINDOWSMACROS), KC_LCTL, KC_LCTL, KC_LCTL, KC_LALT, KC_SPC,  KC_SPC,   KC_SPC,                                   MO(_SYMBOLS), KC_MRWD, KC_MPLY, KC_MFFD, KC_WSCH, KC_PSCR, _______, _______, _______
    )
};

// fancy macro shit is going in here
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case JIGGLER:
            if (record->event.pressed) {
                mouse_jiggle_mode ^= true;
            }
            return false;
        case ALT_TAB:
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;

                    register_code(alt_tab_modifier);
                }
                alt_tab_timer = timer_read();
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            return false;
        default:
            return true;  // Process all other keycodes normally
    }
}

void matrix_scan_user(void) {
    if (timer_elapsed32(jiggle_timer) > 3000) {  // 3 seconds
        jiggle_timer = timer_read32();           // resets timer
        if (mouse_jiggle_mode) {
            tap_code(KC_MS_U);
            tap_code(KC_MS_D);
        }  // tap if enabled
    }
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 500) {
            unregister_code(alt_tab_modifier);
            is_alt_tab_active = false;
        }
    }
}

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//     if (!process_record_dynamic_macro(keycode, record)) {
//         return false;
//     }
//     return true;
// }

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _OSX:
            alt_tab_modifier  = KC_LGUI;
            mouse_jiggle_mode = true;
            break;
        default:  //  for any other layers, or the default layer
            alt_tab_modifier  = KC_LALT;
            mouse_jiggle_mode = false;
            break;
    }
    return state;
}
