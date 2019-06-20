#include QMK_KEYBOARD_H
#include "brandonschlack.h"

extern keymap_config_t keymap_config;

// Layers defined in brandonschlack.h

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Navigation
 * ,-------------.
 * | PTab | NTab |
 * |------+------|
 * | SclL | SclU |
 * |------+------|
 * | SclR | SclD |
 * |------+------|
 * |LstTab|ClsTab|
 * `-------------'
 */
[_NAVI] = LAYOUT( \
    PRV_TAB, NXT_TAB, \
    MC_WH_L, MC_WH_U, \
    MC_WH_R, MC_WH_D, \
    TD(TD_SHLD_LGHT), TD(TD_SHLD_MAGC) \
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
    CMD_TAB, TD(TD_REDR_H), \
    KC_P, KC_K, \
    KC_N, KC_J, \
    TD(TD_SHLD_LGHT), TD(TD_SHLD_MAGC) \
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
    TD(TD_SHLD_LGHT), TD(TD_SHLD_MAGC) \
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
    TD(TD_SHLD_LGHT), TD(TD_SHLD_MAGC) \
),

/* Lights
 * ,-------------.
 * | HUE- | HUE+ |
 * |------+------|
 * | SAT- | SAT+ |
 * |------+------|
 * | VAL- | VAL+ |
 * |------+------|
 * | XXXX | Mode+|
 * `-------------'
 */
[_LIGHT] = LAYOUT( \
    RGB_HUD, RGB_HUI, \
    RGB_SAD, RGB_SAI, \
    RGB_VAD, RGB_VAI, \
    XXXXXXX, RGB_MOD \
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
void keyboard_post_init_keymap(void) {
};

/**
 * Tap Dances
 */
void process_tap_dance_keycode (bool reset, uint8_t toggle_layer) {
    uint16_t keycode = 0;
    switch (toggle_layer) {
        case _LIGHT:
            switch (biton32(layer_state)) {
                case _NAVI:
                    keycode = REO_TAB;
                    break;
                case _REEDER:
                    keycode = KC_L;
                    break;
                case _MEDIA:
                    keycode = KC_SPC;
                    break;
                case _KEYPAD:
                    keycode = KC_P7;
                    break;
            }
            break;
        case _MAGIC:
            switch (biton32(layer_state)) {
                case _NAVI:
                    keycode = CLS_TAB;
                    break;
                case _REEDER:
                    keycode = KC_S;
                    break;
                case _MEDIA:
                    keycode = MC_PLYR;
                    break;
                case _KEYPAD:
                    keycode = KC_P8;
                    break;
            }
            break;
    }
    if (!reset) {
        register_code16(keycode);
    } else {
        unregister_code16(keycode);
    }
}
