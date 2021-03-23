#include QMK_KEYBOARD_H

//extern uint8_t is_master;


#define _COLEMAK 0
#define _SYMBOL 1
#define _NAVIGATION 2
#define _FKEYS 3


//keycode shorthands
#define SYM  MO(1)
#define NAV  LT(2, KC_ESC)
#define FKEY MO(3)

//aliases for clarity in layering
#define SftEnt SFT_T(KC_ENT)   // Shift when held, Enter when tapped
#define BSCTL  LCTL_T(KC_BSPC) // Ctrl when held, Backspace when tapped
#define CTAB   LCTL(KC_TAB)
#define ATAB   LALT(KC_TAB)

//aliases for Navigation layer
#define CBSPC LCTL(KC_BSPC)  // delete whole word
#define C_CL   LCTL(KC_LEFT) // move cursor one word back
#define C_CR   LCTL(KC_RGHT) // move cursor one word forward

//internet browser tab shortcuts and window swapping
#define CTLPGDN LCTL(KC_PGDN)
#define CTLPGUP LCTL(KC_PGUP)

#define G_GRV   LGUI(KC_GRV)
#define SftEnt  SFT_T(KC_ENT)

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE,
  SET_RGB,
};

/*
enum layers {
    _COLEMAK = 0,
    _SYMBOL = 1,
    _NAVIGATION = 2,
    _FKEYS = 3
};
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEMAK] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                        KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      NAV   ,    KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                        KC_H,    KC_N,    KC_E,    KC_I, KC_O   , KC_QUOT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                        KC_K,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  SftEnt,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT, KC_LGUI,   BSCTL,   KC_SPC,   SYM ,   FKEY \
                                      //`--------------------------'  `--------------------------'

  ),

  [_SYMBOL] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_LBRC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_RBRC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_BSLS, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_EQL ,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_HOME, KC_END,  _______, _______, _______,                       KC_GRV, KC_MINS, KC_PGUP, _______, _______, _______,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, KC_PGDN \
                                      //`--------------------------'  `--------------------------'
  ),

  [_NAVIGATION] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, _______, _______, _______, _______, _______,                      CTAB ,   C_CL  ,   KC_UP,   C_CR  ,  KC_DEL, _______,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                     CTLPGUP, KC_LEFT , KC_DOWN, KC_RGHT, CTLPGDN, _______,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        RESET, _______, _______, _______, _______, _______,                      ATAB   , CBSPC , KC_HOME, KC_END, _______, _______,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, KC_RALT \
                                      //`--------------------------'  `--------------------------'
  ),

  [_FKEYS] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_F12,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, RGB_SAI, RGB_HUI, RGB_VAI, RGB_TOG, SET_RGB,                     _______, _______, _______, _______, _______,  _______,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, RGB_MOD, RGB_M_P, KC_VOLD, KC_VOLU, KC_MPLY,                     _______, _______, _______, _______, _______, _______,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,     _______, _______, _______ \
                                      //`--------------------------'  `--------------------------'
  )
};

void matrix_init_user(void) {
//    rgb_matrix_sethsv(191, 43, 81);
    rgblight_mode(RGB_MATRIX_TYPING_HEATMAP);
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        
        case SET_RGB:
            if (record->event.pressed) {
                rgb_matrix_sethsv(18, 86, 95);
            }
            return false;
            break;

    }
    return true;
}

// change RGB Matrix leds based on current layer
/*
layer_state_t layer_state_set_user(layer_state_t state) {
    switch(biton32(state)) {
        case _COLEMAK:
            rgb_matrix_sethsv(191, 43, 81);
            break;
        case _SYMBOL:
            rgb_matrix_sethsv(18, 86, 95);
            break;
        case _NAVIGATION:
            rgb_matrix_sethsv(121, 100, 58);
            break;
        case _FKEYS:
            rgb_matrix_sethsv(14, 72, 65);
            break;
    }
    return state;
}
*/


void suspend_power_down_user(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_user(void) {
    rgb_matrix_set_suspend_state(false);
}
