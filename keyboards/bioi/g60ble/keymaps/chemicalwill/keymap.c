#include QMK_KEYBOARD_H

#define _QWER 0
#define _WORK 1
#define _FN1 2

#define FN1_CAPS LT(_FN1, KC_CAPS)

// Tap Dance enum
enum {
    N9_F9,
    N0_F10,
    MINS_F11,
    EQL_F12
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWER] = LAYOUT_60_ansi(
        QK_GESC,  KC_1,    KC_2,    KC_3,   KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,   KC_BSPC,
        KC_TAB,   KC_Q,    KC_W,    KC_E,   KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,  KC_BSLS,
        FN1_CAPS, KC_A,    KC_S,    KC_D,   KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,           KC_ENT,
        KC_LSFT,           KC_Z,    KC_X,   KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,           KC_RSFT,
        KC_LCTL,  KC_LGUI, KC_LALT,                  KC_SPC,                                      KC_RALT, KC_APP,  MO(_FN1), KC_RCTL
    ),

    [_WORK] = LAYOUT_60_ansi(
        QK_GESC,  KC_1,    KC_2,    KC_3,   KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    TD(N9_F9), TD(N0_F10), TD(MINS_F11), TD(EQL_F12), KC_BSPC,
        KC_TAB,   KC_Q,    KC_W,    KC_E,   KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,      KC_P,       KC_LBRC,      KC_RBRC,     KC_BSLS,
        FN1_CAPS, KC_A,    KC_S,    KC_D,   KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,      KC_SCLN,    KC_QUOT,                   KC_ENT,
        KC_LSFT,           KC_Z,    KC_X,   KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM,   KC_DOT,     KC_SLSH,                   KC_RSFT,
        KC_LCTL,  KC_LGUI, KC_LALT,                  KC_SPC,                                        KC_RALT,    KC_APP,       MO(_FN1),    KC_RCTL
    ),

    [_FN1] = LAYOUT_60_ansi(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,    KC_F12,  KC_DEL,
        _______, _______, KC_PGUP, _______, QK_RBT,  _______, _______, _______, KC_UP,   _______, _______, _______,   _______, _______,
        _______, KC_HOME, KC_PGDN, KC_END,  _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,            _______,
        _______,          _______, _______, _______, _______, QK_BOOT, _______, _______, _______, _______, _______,            _______,
        _______, _______, _______,                   _______,                                     _______, DF(_WORK), _______, DF(_QWER)
    )

};


// Tap Dance tap vs. hold https://docs.qmk.fm/#/feature_tap_dance?id=example-3
typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    tap_dance_action_t *action;

    switch (keycode) {
        case TD(N9_F9):
            action = &tap_dance_actions[TD_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
            break;

        case TD(N0_F10):
            action = &tap_dance_actions[TD_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
            break;

        case TD(MINS_F11):
            action = &tap_dance_actions[TD_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
            break;

        case TD(EQL_F12):
            action = &tap_dance_actions[TD_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
            break;
        }
    return true;
}

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

tap_dance_action_t tap_dance_actions[] = {
    [N9_F9] = ACTION_TAP_DANCE_TAP_HOLD(KC_9, KC_F9),
    [N0_F10] = ACTION_TAP_DANCE_TAP_HOLD(KC_0, KC_F10),
    [MINS_F11] = ACTION_TAP_DANCE_TAP_HOLD(KC_MINS, KC_F11),
    [EQL_F12] = ACTION_TAP_DANCE_TAP_HOLD(KC_EQL, KC_F12)
};
