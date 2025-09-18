#include QMK_KEYBOARD_H

enum unicode_names {
    BUNNY,
    DOGGY,
    MOUSE,
    RABBIT,
    KITTY
};

const uint32_t PROGMEM unicode_map[] = {
    [BUNNY]  = 0x1F430,  // 🐰
    [DOGGY]  = 0x1F436,  // 🐶
    [MOUSE]  = 0x1F42D,  // 🐭
    [RABBIT] = 0x1F407,  // 🐇
    [KITTY]  = 0x1F408,  // 🐈
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_6x4(
        BL_STEP,      KC_F21,     KC_F22,     KC_F23,
        UM(KITTY),    KC_F17,     KC_F20,     KC_M,
        UM(RABBIT),   KC_F16,     KC_F19,     LCTL(KC_Y),
        UM(MOUSE),    KC_F15,     LCTL(KC_D), LCTL(KC_Y), 
        UM(DOGGY),    KC_F14,     KC_F18,     LCTL(KC_Z),
        UM(BUNNY),    KC_F13,     KC_E,       LCTL(KC_Z)
    ),
};