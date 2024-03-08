#include <stdint.h>
#include "annepro2.h"
#include "ap2_led.h"
#include "config.h"
#include QMK_KEYBOARD_H

//#include "sendstring_colemak.h"
enum anne_pro_layers {
    _BASE_LAYER,
    _FN1_LAYER,
    _FN2_LAYER,
};


//enum unicode_names { ARR, EUR, SNEK};
//
///* Unicode map */
//const uint32_t PROGMEM unicode_map[] = {
//[ARR] = 0x00E4,  // ä
//[EUR] = 0x20AC,  // €
//[SNEK]  = 0x1F40D,
//};

enum custom_keycodes {
    POOP,
};


//enum preonic_keycodes {
//    LOWER = SAFE_RANGE,
//    RAISE,
//    SHRUG,  // ¯\_(ツ)_/¯
//    TFLIP,  // (╯°□°)╯︵ ┻━┻
//    POOP,   // 💩
//    DPOINT, // (ಠ_ಠ)
//    STRUT   // ᕕ( ᐛ )ᕗ
//};


// Key symbols are based on QMK. Use them to remap your keyboard
/*
* Layer _BASE_LAYER
* ,-----------------------------------------------------------------------------------------.
* |   ` |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |    Bksp   |
* |-----------------------------------------------------------------------------------------+
* | Tab    |  q  |  w  |  e  |  r  |  t  |  y  |  u  |  i  |  o  |  p  |  [  |  ]  |   \    |
* |-----------------------------------------------------------------------------------------+
* | ESC    |  a  |  s  |  d  |  f  |  g  |  h  |  j  |  k  |  l  |  ;  |  '  |    Enter    |
* |-----------------------------------------------------------------------------------------+
* | Shift      |  z  |  x  |  c  |  v  |  b  |  n  |  m  |  ,  |  .  |  /  |    Shift       |
* |-----------------------------------------------------------------------------------------+
* | Ctrl  |  WIN   |  ALT  |               space             |  FN1  |  <-  |  v  | ->  |
* \------------------------------------------------------------oeu---------------------------/
* Layer TAP in _BASE_LAYER
* ,-----------------------------------------------------------------------------------------.
* |     |     |     |     |     |     |     |     |     |     |     |     |     |           |
* |-----------------------------------------------------------------------------------------+
* |        |     |     |     |     |     |     |     |     |     |     |     |     |        |
* |-----------------------------------------------------------------------------------------+
* |         |     |     |     |     |     |     |     |     |     |     |     |             |
* |-----------------------------------------------------------------------------------------+
* |            |     |     |     |     |     |     |     |     |     |     |       UP       |
* |-----------------------------------------------------------------------------------------+
* |       |       |       |                                 |       |  LEFT | DOWN  | RIGHT |
* \-----------------------------------------------------------------------------------------/
*/
const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE_LAYER] = LAYOUT_60_ansi( /* Base */
        KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
        KC_ESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, RSFT_T(KC_UP),
        KC_LCTL, KC_LGUI, KC_LALT , KC_SPC, MO(_FN1_LAYER), LT(_FN2_LAYER, KC_LEFT), KC_DOWN, KC_RGHT
    ),
    /*
    * Layer _FN1_LAYER
    * ,-----------------------------------------------------------------------------------------.
    * |  SLEEP  |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 |  DELETE   |
    * |-----------------------------------------------------------------------------------------+
    * | Tab    |  q  | >  |  END  |  r  |  t  |  y  |  u  |  i  |  o  | PS | HOME | END |   \    |
    * |-----------------------------------------------------------------------------------------+
    * | CAPS     |HOME |_ |END|  f  |  g  |  h  |  j  |  k  |  l  | PGUP| PGDN |    Enter    |
    * |-----------------------------------------------------------------------------------------+
    * | Shift      | _ | _ | _ |  v  |  b  |  n  |   MUTE |VOL_DOWN| VOL_UP | Brig_down |   BR_UP    |
    * |-----------------------------------------------------------------------------------------+
    * | Ctrl  |  L1   |  Alt  |               PAUSE             |  FN1  |  NEXT  |  PREV  | Ctrl  |
    * \-----------------------------------------------------------------------------------------/
    *
    */
    [_FN1_LAYER] = LAYOUT_60_ansi( /* Base */
        KC_EJCT, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL,
        KC_TRNS, UC(0x30C4), POOP, KC_END, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_HOME, KC_END, KC_TRNS,
        KC_CAPS_LOCK, KC_HOME, KC_TRNS, KC_END, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_PGDN, KC_TRNS,
        KC_TRNS, X(POOP), X(POOP), PB_3, PB_4, POOP, POOP, KC_MUTE, KC_VOLD, KC_VOLU, KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_MEDIA_PLAY_PAUSE, KC_TRNS, KC_MEDIA_NEXT_TRACK, KC_MEDIA_PREV_TRACK, KC_TRNS
    ),
    /*
    * Layer _FN2_LAYER
    * ,-----------------------------------------------------------------------------------------.
    * |  ~  | BT1 | BT2 | BT3 | BT4 |  F5 |  F6 |  F7 |LEDOF|LEDON| LED_INTESITY | LED_SPEED | F12 |    Bksp   |
    * |-----------------------------------------------------------------------------------------+
    * | Tab    |  q  | UP  |  e  |  r  |  t  |  y  |  u  |  i  |  o  | PS | HOME | END |   \    |
    * |-----------------------------------------------------------------------------------------+
    * | Esc     |LEFT |DOWN |RIGHT|  f  |  g  |  h  |  j  |  k  |  l  | PGUP|PGDN |    Enter    |
    * |-----------------------------------------------------------------------------------------+
    * | Shift      |  z  |  x  |  c  |  v  |  b  |  n  |  m  |  ,  |INSRT| DEL |    Shift       |
    * |-----------------------------------------------------------------------------------------+
    * | Ctrl  |  L1   |  Alt  |               space             |  Alt  |  FN1  |  FN2  | Ctrl  |
    * \-----------------------------------------------------------------------------------------/
    * .>>.....
    */
    [_FN2_LAYER] = LAYOUT_60_ansi( /* Base */
        KC_TRNS, KC_AP2_BT1, KC_AP2_BT2, KC_AP2_BT3, KC_AP2_BT4, KC_TRNS, KC_TRNS, KC_TRNS, KC_AP_LED_OFF, KC_AP_LED_ON, KC_AP_LED_NEXT_INTENSITY, KC_AP_LED_SPEED, KC_TRNS, KC_TRNS,
        MO(_FN2_LAYER), KC_TRNS, KC_UP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_HOME, KC_END, KC_TRNS,
        KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_PGDN, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_INS, KC_DEL, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(_FN1_LAYER), MO(_FN2_LAYER), KC_TRNS
    ),
};
const uint16_t keymaps_size = sizeof(keymaps);


void matrix_init_user(void) {

}

void matrix_scan_user(void) {
}

// Code to run after initializing the keyboard
void keyboard_post_init_user(void) {
    // Here are two common functions that you can use. For more LED functions, refer to the file "qmk_ap2_led.h"

    // annepro2-shine disables LEDs by default. Uncomment this function to enable them at startup.
    ap2_led_enable();

    // Additionally, it also chooses the first LED profile by default. Refer to the "profiles" array in main.c in
    // annepro2-shine to see the order. Replace "i" with the index of your preferred profile. (i.e the RED profile is index 0)
    ap2_led_set_profile(0);
//    annepro2LedSetProfile(0);
}

layer_state_t layer_state_set_user(layer_state_t layer) {
    switch(get_highest_layer(layer)) {
        case _FN1_LAYER:
            // Set the leds to orange
            ap2_led_set_foreground_color(0xf5, 0x75, 0x42);
            break;
        case _FN2_LAYER:
            // Set the leds to pink
            ap2_led_set_foreground_color(0xf5, 0x42, 0x93);
            break;
        default:
            // Reset back to the cu097 rrent profil
            ap2_led_reset_foreground_color();
            break;
    }
    return layer;
}

// The function to handle the caps lock logic
bool led_update_user(led_t leds) {
    if (leds.caps_lock) {
        // Set the leds to green
        ap2_led_set_foreground_color(0x00, 0xFF, 0x00);
    } else {
        // Reset back to the current profile if there is no layer active
        if(!layer_state_is(_FN1_LAYER) && !layer_state_is(_FN2_LAYER)) {
            ap2_led_reset_foreground_color();
        }
    }

    return true;
}

// NOT USED
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case POOP:
            if (record->event.pressed) {
                send_string("Test");
            }
            return false;
            break;

    }
    return true;
};
