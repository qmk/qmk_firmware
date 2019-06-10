#include QMK_KEYBOARD_H
#include "brandonschlack.h"

extern keymap_config_t keymap_config;

enum launchpad_layers {
    _NAVI,
    _REEDER,
    _MEDIA,
    _KEYPAD
};

enum launchpad_keycodes {
    TG_NAVI = KEYMAP_SAFE_RANGE,
    TG_REDR,
    TG_MEDA,
    TG_KYPD
};

enum launchpad_dances {
    TD_LGHT = 0,
    TD_MAGC,
    TD_CMTB
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Navigation
 * ,-------------.
 * | PTab | NTab |
 * |------+------|
 * | Left |  Up  |
 * |------+------|
 * | Rght |  Dn  |
 * |------+------|
 * | PgUp | PgDn |
 * `-------------'
 */
[_NAVI] = LAYOUT( \
    S(G(KC_LBRC)), S(G(KC_RBRC)), \
    KC_P, KC_K, \
    KC_N, KC_J, \
    TD(TD_LGHT), TD(TD_MAGC) \
),

/* Reeder
 * ,-------------.
 * |CMDTAB|  H   |
 * |------+------|
 * |   P  |  K   |
 * |------+------|
 * |   N  |  J   |
 * |------+------|
 * |   L  |  S   |
 * `-------------'
 */
[_REEDER] = LAYOUT( \
    TD(TD_CMTB), KC_H, \
    KC_P, KC_K, \
    KC_N, KC_J, \
    TD(TD_LGHT), TD(TD_MAGC) \
),

/* Media
 * ,-------------.
 * | Mute | PlPs |
 * |------+------|
 * | VolU | TrkN |
 * |------+------|
 * | VolD | TrkP |
 * |------+------|
 * | Spc  | Plyr |
 * `-------------'
 */
[_MEDIA] = LAYOUT( \
    KC_MUTE, KC_MPLY, \
    KC_VOLU, KC_MFFD, \
    KC_VOLD, KC_MRWD, \
    TD(TD_LGHT), TD(TD_MAGC) \
),

/* Keypad
 * ,-------------.
 * |   1  |  2   |
 * |------+------|
 * |   3  |  4   |
 * |------+------|
 * |   5  |  6   |
 * |------+------|
 * |   7  |  8   |
 * `-------------'
 */
[_KEYPAD] = LAYOUT( \
    KC_P1,     KC_P2, \
    KC_P3,     KC_P4, \
    KC_P5,     KC_P6, \
    TD(TD_LGHT), TD(TD_MAGC) \
),

/* Lights
 * ,-------------.
 * | Mode-| Mode+|
 * |------+------|
 * | HUE- | HUE+ |
 * |------+------|
 * | SAT- | SAT+ |
 * |------+------|
 * | Magc |RGBTOG|
 * `-------------'
 */
[_LIGHT] = LAYOUT( \
    RGB_RMOD, RGB_MOD, \
    RGB_HUD,  RGB_HUI, \
    RGB_SAD,  RGB_SAI, \
    TG(_MAGIC), RGB_TOG \
),

/* Magic
 * ,-------------.
 * | Make | Rset |
 * |------+------|
 * | Navi | Redr |
 * |------+------|
 * | Meda | Kypd |
 * |------+------|
 * | Lght | XXXX |
 * `-------------'
 */
[_MAGIC] = LAYOUT( \
    KC_MAKE, RESET, \
    TG_NAVI, TG_REDR, \
    TG_MEDA, TG_KYPD, \
    TG(_LIGHT), XXXXXXX \
)

};

void matrix_init_user(void) {

}

// Runs once after keyboard initializes
void keyboard_post_init_user(void) {
    rgblight_sethsv(HSV_LSR_PURPLE);
};


bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TG_NAVI:
            if (!record->event.pressed) {
                layer_move(_NAVI);
            }
            break;
        case TG_REDR:
            if (!record->event.pressed) {
                layer_move(_REEDER);
            }
            break;
        case TG_MEDA:
            if (!record->event.pressed) {
                layer_move(_MEDIA);
            }
            break;
        case TG_KYPD:
            if (!record->event.pressed) {
                layer_move(_KEYPAD);
            }
            break;
    }
    return true;
}

uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
    case _REEDER:
        rgblight_sethsv_noeeprom(HSV_LSR_PINK);
        break;
    case _MEDIA:
        rgblight_sethsv_noeeprom(HSV_LSR_BLUE);
        break;
    case _KEYPAD:
        rgblight_sethsv_noeeprom(HSV_LSR_CYAN);
        break;
    case _MAGIC:
        rgblight_sethsv_noeeprom(HSV_GREEN);
        break;
    default: //  for any other layers, or the default layer
        rgblight_sethsv_noeeprom(HSV_LSR_PURPLE);
        break;
    }
  return state;
}

/**
 * Tap Dances
 */
void dance_light_layer_finished (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        layer_on(_LIGHT);
    } else {
        switch (biton32(layer_state)) {
            case _NAVI:
                register_code(KC_PGDN);
                break;
            case _REEDER:
                register_code(KC_L);
                break;
            case _MEDIA:
                register_code(KC_SPC);
                break;
            case _KEYPAD:
                register_code(KC_P7);
                break;
        }
    }
}
void dance_light_layer_reset (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
    } else {
        switch (biton32(layer_state)) {
            case _NAVI:
                unregister_code(KC_PGDN);
                break;
            case _REEDER:
                unregister_code(KC_L);
                break;
            case _MEDIA:
                unregister_code(KC_SPC);
                break;
            case _KEYPAD:
                unregister_code(KC_P7);
                break;
        }
    }
}

void dance_magic_layer_finished (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        layer_on(_MAGIC);
    } else {
        switch (biton32(layer_state)) {
            case _NAVI:
                register_code(KC_PGUP);
                break;
            case _REEDER:
                register_code(KC_S);
                break;
            case _MEDIA:
                register_code16(G(KC_F8));
                break;
            case _KEYPAD:
                register_code(KC_P8);
                break;
        }
    }
}
void dance_magic_layer_reset (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
    } else {
        switch (biton32(layer_state)) {
            case _NAVI:
                register_code(KC_PGUP);
                break;
            case _REEDER:
                unregister_code(KC_S);
                break;
            case _MEDIA:
                unregister_code16(G(KC_F8));
                break;
            case _KEYPAD:
                unregister_code(KC_P8);
                break;
        }
    }
}

void dance_command_tab_finished (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        register_code(KC_R);
    } else {
        switch (biton32(layer_state)) {
            case _REEDER:
                register_code16(G(KC_TAB));
                break;
        }
    }
}
void dance_command_tab_reset (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        unregister_code(KC_R);
    } else {
        switch (biton32(layer_state)) {
            case _REEDER:
                unregister_code16(G(KC_TAB));
                break;
        }
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_LGHT] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_light_layer_finished, dance_light_layer_reset),
    [TD_MAGC] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_magic_layer_finished, dance_magic_layer_reset),
    [TD_CMTB] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_command_tab_finished, dance_command_tab_reset)
};
