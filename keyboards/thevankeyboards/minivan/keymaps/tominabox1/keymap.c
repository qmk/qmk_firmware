#include QMK_KEYBOARD_H

#ifdef BACKLIGHT_ENABLE
#include "backlight.h"
#endif

// Act as Shift on hold and as CapsLock on tap
#define KC_SFT_CPS TD(TD_SFT_CPS)
// Left space on tap, LOWER on hold
#define SPC_LOW LT(_LOWER, KC_ENT)
// Left space on tap, UPPER on hold
#define SPC_UPR LT(_RAISE, KC_SPC)


extern keymap_config_t keymap_config;

enum tv44_layers {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST,
    _FKEY
};

enum {
    KC_EML = 0,
    TD_SFT_CPS,
};

void dance_cln_finished (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code (KC_RSFT);
        register_code (KC_2);
    } else {
        SEND_STRING("tom.campie@gmail.com");
    }
}

void dance_cln_reset (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code (KC_RSFT);
        unregister_code (KC_2);
    } else {
    }
}

//All tap dance functions would go here. Only showing this one.
qk_tap_dance_action_t tap_dance_actions[] = {
    [KC_EML] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_cln_finished, dance_cln_reset),
    [TD_SFT_CPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS)
};


uint16_t get_tapping_term(uint16_t keycode) {
    switch (keycode) {
            //        case KC_SFT_CPS:
            //            return 100;
            //        case SPC_UPR:
            //            return 50;
        case SPC_LOW:
            return 150;
            ////        case TD(KC_EML):
            ////            return 50;
        default:
            return TAPPING_TERM;
    }
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    
    [_BASE] = LAYOUT_arrow(
                           KC_GESC, KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,    KC_BSPC,
                           LCTL_T(KC_TAB),  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT,
                           KC_SFT_CPS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_UP, KC_DOT,   KC_SLSH,
                           KC_LCTL, KC_LGUI, KC_LALT, SPC_LOW,  SPC_UPR,  LT(_FKEY, KC_LEFT), KC_DOWN, KC_RIGHT, MO(_FKEY)
                           ),
    
    [_LOWER] = LAYOUT_arrow(
                            KC_TILD, KC_EXLM, TD(KC_EML),   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
                            KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
                            KC_TRNS,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_PGDN, KC_UP, KC_QUES, KC_SLSH,
                            LCA(KC_DEL),   KC_NO,   KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_END
                            ),

    [_RAISE] = LAYOUT_arrow(
                            KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
                            KC_INS,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
                            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_SLSH, KC_NO,
                            KC_LCTL, KC_LGUI, KC_LALT, SPC_LOW,  SPC_UPR,  KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT
                            ),

    [_ADJUST] = LAYOUT_arrow(
                            RESET,EEP_RST,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                            RGB_M_P,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                            RGB_MOD,   RGB_HUI,   RGB_HUD,   RGB_M_SN,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,
                            RGB_VAD, RGB_TOG, RGB_VAI, KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_NO
                            ),
    
    [_FKEY] = LAYOUT_arrow(
                           KC_NO, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,
                           RGB_M_P,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_F12,   KC_F13,
                           RGB_MOD,   RGB_HUI,   RGB_HUD,   RGB_M_SN,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,
                           RGB_VAD, RGB_TOG, RGB_VAI, KC_NO,   KC_NO,   KC_TRNS,   KC_NO, KC_NO,   KC_TRNS
                           ),
};

uint32_t layer_state_set_user(uint32_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    switch (biton32(state)) {
        case _LOWER:
//            rgblight_sethsv_noeeprom(HSV_BLUE);
            break;
        case _RAISE:
//            rgblight_sethsv_noeeprom(HSV_GREEN);
            break;
        case _ADJUST:
//            rgblight_sethsv_noeeprom(HSV_CYAN);
            break;
        default:
//            rgblight_sethsv_noeeprom(50,140,201);
            break;
    }
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif
    return true;
}
