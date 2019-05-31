#include QMK_KEYBOARD_H
#include "brandonschlack.h"

extern keymap_config_t keymap_config;

enum launchpad_layers {
    _MEDIA,
    _KEYPAD
};

enum bdn9_keycodes {
    TG_MEDA = KEYMAP_SAFE_RANGE,
    TG_KYPD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Media
 * ,-------------.
 * | Mute | PlPs |
 * |------+------|
 * | VolU | TrkN |
 * |------+------|
 * | VolD | TrkP |
 * |------+------|
 * |      | Plyr |
 * `-------------'
 */
[_MEDIA] = LAYOUT( \
    KC_MUTE, KC_MPLY, \
    KC_VOLU, KC_MFFD, \
    KC_VOLD, KC_MRWD, \
    MO(_MAGIC), MC_PLYR \
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
    LT(_MAGIC, KC_P7), KC_P8  \
),

/* Magic
 * ,-------------.
 * | Flsh | Rset |
 * |------+------|
 * | Mdia | Kypd |
 * |------+------|
 * | XXXX | XXXX |
 * |------+------|
 * |      | XXXX |
 * `-------------'
 */
[_MAGIC] = LAYOUT( \
    KC_FLSH, RESET, \
    TG_MEDA, TG_KYPD, \
    XXXXXXX, XXXXXXX, \
    _______, XXXXXXX \
)

};

void matrix_init_user(void) {

}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
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
