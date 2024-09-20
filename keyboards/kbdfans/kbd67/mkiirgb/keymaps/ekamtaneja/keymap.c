#include QMK_KEYBOARD_H
#include <stdint.h>

#define _DEF 0
#define _GAM 1
#define _ENG 2
#define _FN 3
#define _NUM 4

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_HOLD,
    TD_DOUBLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum {
    FN_NUM,
};

td_state_t cur_dance(tap_dance_state_t *state);

void fn_finished(tap_dance_state_t *state, void *user_data);
void fn_reset(tap_dance_state_t *state, void *user_data);

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _NUM:
            rgb_matrix_mode(RGB_MATRIX_JELLYBEAN_RAINDROPS);
            break;
        case _FN:
            rgb_matrix_mode(RGB_MATRIX_PIXEL_FRACTAL);
            break;
        case _ENG:
            rgb_matrix_mode(RGB_MATRIX_RIVERFLOW);
            break;
        case _GAM:
            rgb_matrix_mode(RGB_MATRIX_TYPING_HEATMAP);
            break;
        case _DEF:
            rgb_matrix_mode(RGB_MATRIX_CYCLE_ALL);
            break;
        default:
            rgb_matrix_mode(RGB_MATRIX_CYCLE_ALL);
            break;
    }
    return state;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_DEF] = LAYOUT_65_ansi_blocker( /* Base */
		QK_GESC,    KC_1,    KC_2,          KC_3,          KC_4,          KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_TRNS,
		KC_TAB,     KC_Q,    KC_W,          KC_E,          KC_R,          KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_TRNS,
		TD(FN_NUM), KC_A,    KC_S,          KC_D,          KC_F,          KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  DF(_ENG),
		KC_LSFT,    KC_Z,    KC_X,          KC_C,          KC_V,          KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   TG(_GAM),
		KC_LCTL,    KC_LGUI, KC_LALT,                                     KC_SPC,                    KC_CAPS,          KC_RALT, KC_LEFT,          KC_DOWN, KC_RIGHT
	),
	[_GAM] = LAYOUT_65_ansi_blocker( /* 5xFN */
		KC_ESC,     KC_TRNS, KC_TRNS,       KC_TRNS,       KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS,    KC_TRNS, KC_TRNS,       KC_TRNS,       KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		TD(FN_NUM), KC_TRNS, KC_TRNS,       KC_TRNS,       KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,
		KC_TRNS,    KC_TRNS, KC_TRNS,       KC_TRNS,       KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, TG(_GAM),
		KC_TRNS,    KC_TRNS, KC_TRNS,                                     KC_SPC,                    KC_TRNS,          KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS
	),
    [_ENG] = LAYOUT_65_ansi_blocker( /* Engrammer */
		QK_GESC,    KC_1,    KC_2,          KC_3,          KC_4,          KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_LBRC, KC_RBRC, KC_BSPC, KC_TRNS,
		KC_TAB,     KC_B,    KC_Y,          KC_O,          KC_U,          KC_QUOT, KC_SCLN, KC_L,    KC_D,    KC_W,    KC_V,    KC_Z,    KC_EQL,  KC_BSLS, KC_TRNS,
		TD(FN_NUM), KC_C,    KC_I,          KC_E,          KC_A,          KC_COMM, KC_DOT,  KC_H,    KC_T,    KC_S,    KC_N,    KC_Q,             KC_ENT,  DF(_DEF),
		KC_LSFT,    KC_G,    KC_X,          KC_J,          KC_K,          KC_MINS, KC_SLSH, KC_R,    KC_M,    KC_F,    KC_P,    KC_RSFT,          KC_UP,   TG(_GAM),
		KC_LCTL,    KC_LGUI, KC_LALT,                                     KC_SPC,                    KC_CAPS,          KC_RALT, KC_LEFT,          KC_DOWN, KC_RIGHT
	),
	[_FN] = LAYOUT_65_ansi_blocker( /* FN */
		KC_NO,      KC_F1,   KC_F2,         KC_F3,         KC_F4,         KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_PSCR,
		KC_NO,      KC_NO,   KC_NO,         KC_WBAK,       KC_WFWD,       KC_NO,   KC_NO,   KC_PGDN, KC_UP,   KC_PGUP, KC_INS,  KC_SCRL, KC_PAUS, QK_BOOT, KC_PAUS,
		KC_NO,      KC_NO,   OSM(MOD_LALT), OSM(MOD_LSFT), OSM(MOD_LCTL), KC_NO,   KC_NO,   KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL,  KC_NO,            EE_CLR,  KC_PGDN,
		KC_NO,      KC_NO,   KC_NO,         RGB_TOG,       RGB_MOD,       RGB_SPI, RGB_HUI, RGB_SAI, RGB_VAI, KC_NO,   KC_NO,   KC_NO,            KC_VOLU, KC_MUTE,
		KC_NO,      KC_NO,   KC_NO,                                       KC_NO,                     KC_NO,            KC_NO,   KC_MPRV,          KC_VOLD, KC_MNXT
	),
    [_NUM] = LAYOUT_65_ansi_blocker( /* FN */
		KC_NO,      KC_NO,   KC_NO,         KC_NO,         KC_NO,         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_BSPC, KC_NO,
		KC_NO,      KC_NO,   KC_NO,         KC_NO,         KC_NO,         KC_NO,   KC_TAB,  KC_P7,   KC_P8,   KC_P9,   KC_PPLS, KC_PAST, KC_NO,   KC_NO,   KC_NO,
		KC_NO,      KC_NO,   KC_NO,         KC_NO,         KC_NO,         KC_NO,   KC_NO,   KC_P4,   KC_P5,   KC_P6,   KC_PMNS, KC_PSLS,          KC_ENT,  KC_NO,
		KC_NO,      KC_NO,   KC_NO,         KC_NO,         KC_NO,         KC_NO,   KC_NO,   KC_P1,   KC_P2,   KC_P3,   KC_PDOT, KC_RSFT,          KC_NO,   KC_NO,
		KC_NO,      KC_NO,   KC_NO,                                       KC_P0,                     KC_NO,            KC_NO,   KC_NO,            KC_NO,   KC_NO
	),
};

// Determine the current tap dance state
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count < 2) {
        if (state->pressed) return TD_SINGLE_HOLD;
        else return TD_UNKNOWN;
    } else if (state->count >= 2) {
        if(state->pressed) return TD_DOUBLE_HOLD;
        else return TD_UNKNOWN;
    }
    else return TD_UNKNOWN;
}

// Initialize tap structure associated with example tap dance key
static td_tap_t fn_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void fn_finished(tap_dance_state_t *state, void *user_data) {
    fn_tap_state.state = cur_dance(state);
    switch (fn_tap_state.state) {
        case TD_SINGLE_HOLD:
            layer_on(_FN);
            break;
        case TD_DOUBLE_HOLD:
            layer_on(_NUM);
            break;
        default:
            break;
    }
}

void fn_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (fn_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(_FN);
    } else if (fn_tap_state.state == TD_DOUBLE_HOLD) {
        layer_off(_NUM);
    }
    fn_tap_state.state = TD_NONE;
}

// Associate our tap dance key with its functionality
tap_dance_action_t tap_dance_actions[] = {
    [FN_NUM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, fn_finished, fn_reset)
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
            return 275;
        default:
            return TAPPING_TERM;
    }
}
