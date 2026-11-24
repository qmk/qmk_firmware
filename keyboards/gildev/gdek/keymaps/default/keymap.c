#include QMK_KEYBOARD_H

enum gdek_keymap_layers {
    LAYER_BASE = 0,
    LAYER_RED = 1,
    LAYER_BLUE = 2,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┐            ┌───┬───┬───┬───┬───┬───┐
     * │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │            │ 6 │ 7 │ 8 │ 9 │ 0 │ - │
     * ├───┼───┼───┼───┼───┼───┤            ├───┼───┼───┼───┼───┼───┤
     * │Tab│ Q │ W │ E │ R │ T │            │ Y │ U │ I │ O │ P │ [ │
     * ├───┼───┼───┼───┼───┼───┼───┐    ┌───┼───┼───┼───┼───┼───┼───┤
     * │Cap│ A │ S │ D │ F │ G │Vol│    │< >│ H │ J │ K │ L │ ; │ ' │
     * ├───┼───┼───┼───┼───┼───┼───┤    ├───┼───┼───┼───┼───┼───┼───┤
     * │Sft│ Z │ X │ C │ V │ B │M_2│    │Ent│ N │ M │ , │ . │ / │Sft│
     * └───┴───┼───┼───┼───┼───┼───┤    ├───┼───┼───┼───┼───┼───┴───┘
     *         │Ctl│Cmd│Alt│Spc│M_1│    │Bsp│Spc│Alt│Cmd│Ctl│
     *         └───┴───┴───┴───┴───┘    └───┴───┴───┴───┴───┘
     */
    [LAYER_BASE] = LAYOUT(
      KC_GRV,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,                                   KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_MINUS,
      KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,                                   KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_LBRC,
      KC_CAPS,    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       KC_MUTE,        XXXXXXX,    KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOTE,
      KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       MO(2),          KC_ENTER,   KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_RSFT,
                              KC_LCTL,    KC_LGUI,    KC_LALT,    KC_SPC,     MO(1),          KC_BSPC,    KC_SPC,     KC_RALT,    KC_RGUI,    KC_RCTL
    ),
    [LAYER_RED] = LAYOUT(
      KC_ESCAPE,  KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,                                  KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_EQUAL,
      _______,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,                                XXXXXXX,    KC_PGUP,    KC_UP,      KC_PGDN,    XXXXXXX,    KC_RBRC,
      _______,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,        XXXXXXX,    XXXXXXX,    KC_LEFT,    KC_DOWN,    KC_RGHT,    XXXXXXX,    KC_NUHS,
      _______,    KC_NUBS,    LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), XXXXXXX,    XXXXXXX,        _______,    XXXXXXX,    KC_HOME,    KC_INS,     KC_END,     XXXXXXX,    _______,
                              _______,    _______,    _______,    _______,    _______,        KC_DELETE,  _______,    _______,    _______,    _______
    ),
    [LAYER_BLUE] = LAYOUT(
      QK_REBOOT,  KC_F11,     KC_F12,     KC_F13,     KC_F14,     KC_F15,                                 KC_NUM,     KC_P7,      KC_P8,      KC_P9,      KC_PSLS,    QK_REBOOT,
      _______,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,                                XXXXXXX,    KC_P4,      KC_P5,      KC_P6,      KC_PAST,    XXXXXXX,
      _______,    XXXXXXX,    RM_SATU,    RM_SPDU,    RM_NEXT,    XXXXXXX,    RM_TOGG,        XXXXXXX,    XXXXXXX,    KC_P1,      KC_P2,      KC_P3,      KC_PMNS,    XXXXXXX,
      _______,    XXXXXXX,    RM_SATD,    RM_SPDD,    RM_PREV,    XXXXXXX,    _______,        XXXXXXX,    XXXXXXX,    KC_P0,      KC_PDOT,    KC_PENT,    KC_PPLS,    _______,
                              _______,    _______,    _______,    _______,    XXXXXXX,        _______,    _______,    _______,    _______,    _______
    ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    { ENCODER_CCW_CW(KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP), ENCODER_CCW_CW(KC_LEFT, KC_RIGHT) },
    { ENCODER_CCW_CW(KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP), ENCODER_CCW_CW(KC_UP, KC_DOWN) },
    { ENCODER_CCW_CW(QK_RGB_MATRIX_VALUE_DOWN, QK_RGB_MATRIX_VALUE_UP), ENCODER_CCW_CW(QK_RGB_MATRIX_HUE_DOWN, QK_RGB_MATRIX_HUE_UP) },
};
#endif
