#include QMK_KEYBOARD_H

enum layer {
    LAYER_DEFAULT,
    LAYER_FUNCTION,
};

/* Switch to function layer when held. */
#define LY_FUNC MO(LAYER_FUNCTION)

/* Send Ctrl+Alt+L (Cinnamon screen lock shortcut) when pressed. */
#define KY_LOCK LCA(KC_L)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_DEFAULT] = LAYOUT(
        KC_MPLY,  KC_VOLU,  KC_MSTP,
        KC_MPRV,  KC_VOLD,  KC_MNXT,
        KY_LOCK,  KC_MUTE,  LY_FUNC
    ),

    [LAYER_FUNCTION] = LAYOUT(
        EEP_RST,  _______,  RESET,
        _______,  _______,  _______,
        _______,  _______,  _______
    ),
};
