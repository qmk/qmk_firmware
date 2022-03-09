#include QMK_KEYBOARD_H
#include "font.h"
#include "max7219.h"

enum custom_keycodes {
    MSG_CB =  SAFE_RANGE,
    MSG_CS,
    MSG_KMI,
    MSG_QMK,
};

uint8_t custom_message[5][6] = {CHR_M, CHR_y, CHR_SPACE, CHR_2, CHR_CENT};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_all(
        MSG_CB,  MSG_QMK, MSG_KMI, MSG_CS,    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,   KC_F10,  KC_F11,  KC_F12,                    KC_PSCR, KC_SLCK, KC_PAUS, KC_INS,
        KC_PMNS, KC_NLCK, KC_PSLS, KC_PAST,   KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
        KC_PPLS, KC_P7,   KC_P8,   KC_P9,     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_P7,   KC_P8,   KC_P9, KC_PPLS,
                 KC_P4,   KC_P5,   KC_P6,     KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   KC_H,   KC_J,   KC_K,   KC_L,    KC_SCLN, KC_QUOT,       KC_ENT,              KC_P4,   KC_P5,   KC_P6,
        KC_PENT, KC_P1,   KC_P2,   KC_P3,     KC_UP,   KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH,       KC_RSFT,    KC_UP,   KC_P1, KC_P2, KC_P3, KC_PENT,
                 KC_P0,   KC_PDOT,   KC_LEFT, KC_DOWN, KC_RGHT, KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_RALT, KC_RGUI, KC_APP,  KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT, KC_P0, KC_PDOT
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case MSG_CB:
                max7219_led_scrolling=true;
                uint8_t cb_msg[MSG_CLUEBOARD_LEN][6] = MSG_CLUEBOARD;
                max7219_message_sign(cb_msg, MSG_CLUEBOARD_LEN);
                return true;
            case MSG_CS:
                max7219_led_scrolling=false;
                max7219_message_sign(custom_message, 5);
                return true;
            case MSG_KMI:
                max7219_led_scrolling=true;
                uint8_t kmi_msg[MSG_KONAMI_LEN][6] = MSG_KONAMI;
                max7219_message_sign(kmi_msg, MSG_KONAMI_LEN);
                return true;
            case MSG_QMK:
                max7219_led_scrolling=true;
                uint8_t qmk_msg[MSG_QMK_POWERED_LEN][6] = MSG_QMK_POWERED;
                max7219_message_sign(qmk_msg, MSG_QMK_POWERED_LEN);
                return true;
        }
    }
    return true;
};
