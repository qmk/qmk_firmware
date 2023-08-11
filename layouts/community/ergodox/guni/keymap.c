#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_EQL  ,  KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_LBRC,
	MT(MOD_LCTL, KC_TAB) ,  KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,   KC_HOME,
        LT(1, KC_CAPS) ,  KC_A,    KC_S,   KC_D,   KC_F,   KC_G,
        KC_LSFT ,  KC_Z,    KC_X,   KC_C,   KC_V,   KC_B,   KC_PGUP,
        KC_LGUI , KC_GRV,KC_LEFT,KC_RGHT,KC_LALT,
                                          KC_NO , KC_NO  ,
                                               KC_NO  ,
                                     KC_BSPC,KC_DEL ,TO(3),
        // right hand
             KC_RBRC , KC_6,   KC_7 ,  KC_8,   KC_9,   KC_0,   KC_MINS,
             KC_END  , KC_Y,   KC_U ,  KC_I,   KC_O,   KC_P,   MT(MOD_RCTL, KC_BSLS),
             KC_H    , KC_J,   KC_K ,  KC_L,   KC_SCLN,LT(1, KC_QUOT),
             KC_PGDN , KC_N,   KC_M ,  KC_COMM,KC_DOT, KC_SLSH,MT(MOD_RSFT, KC_ESC),
             KC_RALT , KC_DOWN,KC_UP,  KC_NO  ,KC_RGUI,
        KC_NO  , KC_NO,
        KC_NO  ,
        MT(MOD_RSFT, KC_ESC),KC_ENT ,KC_SPC 
    ),

    LAYOUT_ergodox(  // layer 1 : function and symbol keys
        // left hand
        KC_TRNS,KC_F1, KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F11,
        KC_TRNS,KC_AT,KC_UNDS ,KC_LBRC,KC_RBRC,KC_CIRC ,KC_TRNS,
        KC_TRNS,KC_BSLS,KC_SLSH,KC_LCBR ,KC_RCBR ,KC_ASTR,
        KC_TRNS,KC_HASH ,KC_DLR ,KC_PIPE ,KC_TILD ,KC_GRV ,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                           KC_TRNS,
                                 KC_TRNS,KC_TRNS,TO(0),
        // right hand
             KC_F12, KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_TRNS,
             KC_TRNS,KC_EXLM,LSFT(KC_COMM),LSFT(KC_DOT),KC_EQL,KC_AMPR, KC_TRNS,
             LSFT(KC_SLSH),KC_LPRN,KC_RPRN,KC_MINS,LSFT(KC_SCLN),KC_TRNS,
             KC_TRNS,KC_PLUS,LSFT(KC_5),LSFT(KC_QUOT),KC_QUOT,KC_SCLN,KC_TRNS,
                       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,
        KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS
    ),

    LAYOUT_ergodox(  // layer 2: navigation 
        // left hand
        KC_NO,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_PGUP,KC_HOME,KC_UP ,KC_END,KC_NO ,KC_TRNS,
        KC_TRNS,KC_PGDN,KC_LEFT,KC_DOWN,KC_RGHT,KC_NO,
        KC_TRNS,KC_NO,  KC_NO,  KC_NO,  KC_NO,KC_NO,KC_NO,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                      KC_TRNS,KC_TRNS,
                                           KC_TRNS,
                                 KC_TRNS,KC_TRNS,TO(0) ,
        // right hand
             KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
             KC_TRNS ,KC_TRNS,  KC_HOME,  KC_TRNS,  KC_TRNS, KC_END ,KC_TRNS,
                  KC_NO,  KC_LEFT,  KC_UP,   KC_DOWN, KC_RGHT,KC_TRNS,
             KC_TRNS,KC_TRNS,  KC_HOME,  KC_UP,  KC_END, KC_PGUP,KC_TRNS,
                       KC_LEFT,  KC_DOWN,KC_RGHT,KC_PGDN,KC_TRNS,
        KC_TRNS,KC_TRNS,
        KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS
    ),
    LAYOUT_ergodox(  // layer 3 : teensy bootloader functions
        // left hand
        QK_BOOT, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                      KC_TRNS,KC_TRNS,
                                           KC_TRNS,
                                 KC_TRNS,KC_TRNS,TO(0) ,
        // right hand
             KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
             KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                  KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
             KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,
        KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS
    ),


    LAYOUT_ergodox(  // layer 4: numpad
        // left hand
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                      KC_TRNS,KC_TRNS,
                                           KC_TRNS,
                                 KC_TRNS,KC_TRNS,KC_TRNS,
        // right hand
             KC_TRNS,KC_NUM, KC_PSLS,KC_PAST,KC_PAST,KC_PMNS,KC_BSPC,
             KC_TRNS,KC_NO,  KC_P7,  KC_P8,  KC_P9,  KC_PMNS,KC_BSPC,
                  KC_NO,  KC_P4,  KC_P5,  KC_P6,  KC_PPLS,KC_PENT,
             KC_TRNS,KC_NO,  KC_P1,  KC_P2,  KC_P3,  KC_PPLS,KC_PENT,
                       KC_P0,  KC_PDOT,KC_SLSH,KC_PENT,KC_PENT,
        KC_TRNS,KC_TRNS,
        KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS
    ),

};
