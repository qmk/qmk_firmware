#include QMK_KEYBOARD_H

enum my_layers {
    // Base QWERTY
    QWERTY = 0,
    // Keypad layer
    KEYPAD = 1,
    // Program layer
    _PROGRAM = 2,
};

enum my_leds {
    // Originally used by LED_COMPOSE_PIN
    LED_KEYPAD = LINE_PIN24,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [QWERTY] = LAYOUT(
        // Left Hand
        KC_ESC  ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F6   ,KC_F7   ,KC_F8   ,
        KC_EQL  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,
        KC_TAB  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,
        KC_CAPS ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,
        KC_LSFT ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,
                 KC_GRV  ,KC_INS  ,KC_LEFT ,KC_RGHT ,
        // Left Thumb
                 KC_LCTL ,KC_LALT ,
                          KC_HOME ,
        KC_BSPC ,KC_DEL  ,KC_END  ,
        // Right Hand
        KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,KC_PSCR ,KC_SCRL ,KC_PAUS ,TT(KEYPAD),MO(_PROGRAM),
        KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_MINS ,
        KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_BSLS ,
        KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_QUOT ,
        KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_RSFT ,
                 KC_UP   ,KC_DOWN ,KC_LBRC ,KC_RBRC ,
        // Right Thumb
        KC_LGUI ,RALT_T(KC_APP),
        KC_PGUP ,
        KC_PGDN ,KC_ENTER,KC_SPC
    ),

    [KEYPAD] = LAYOUT(
        // Left Hand
        _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
        _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
        _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
        _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
        _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
                 _______ ,KC_INS  , KC_LEFT, KC_RGHT,
        // Left Thumb
                 _______ ,_______ ,
                          _______ ,
        _______ ,_______ ,_______ ,

        // Right Hand
        _______ ,_______ ,_______ ,_______ ,KC_AUDIO_MUTE,KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,_______,_______,
        _______ ,KC_NUM  ,KC_PEQL ,KC_PSLS ,KC_PAST ,_______ ,
        _______ ,KC_P7   ,KC_P8   ,KC_P9   ,KC_PMNS ,_______ ,
        _______ ,KC_P4   ,KC_P5   ,KC_P6   ,KC_PPLS ,_______ ,
        _______ ,KC_P1   ,KC_P2   ,KC_P3   ,KC_PENT ,_______ ,
                 KC_UP   ,KC_DOWN ,KC_PDOT ,KC_PENT ,
        // Right Thumb
        _______ ,_______ ,
        _______ ,
        _______ ,KC_PENT ,KC_P0
    ),

    [_PROGRAM] = LAYOUT(
        // Left Hand
        _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
        _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
        _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
        _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
        _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
                 _______ ,_______ ,_______ ,_______ ,
        // Left Thumb
                 _______ ,_______ ,
                          _______ ,
        _______ ,_______ ,_______ ,

        // Right Hand
        QK_BOOT ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
        _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
        _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
        _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
        _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
                 _______ ,_______ ,_______ ,_______ ,
        // Right Thumb
        _______ ,_______ ,
        _______ ,
        _______ ,_______ ,_______
    ),
};

void keyboard_pre_init_user(void) {
  // Set our LED pins as output.
  setPinOutput(LED_KEYPAD);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    writePin(LED_KEYPAD, !layer_state_cmp(state, KEYPAD));
    return state;
}
