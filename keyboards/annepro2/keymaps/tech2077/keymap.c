#include "annepro2.h"
#include <stdint.h>
#include <print.h>
#include <string.h>
#include "qmk_ap2_led.h"
#include "eeprom_w25x20cl.h"

// layout using eeprom and bidir-comms to keep user led settings persistent

// eeprom memory layout
typedef union {
    uint32_t raw;
    struct {
        uint8_t magic : 8;
        bool leds_on : 1;
        uint8_t leds_profile : 8;
    };
} user_config_t;

// define out default user_config
user_config_t user_config = {.magic = 0xDE, .leds_on = 0, .leds_profile = 0};

// keep the number of profiles so we can track along with the shine proc
uint8_t numProfiles = 0;

static uint8_t usb_buf[256];
static uint8_t buf_fil = 0;

enum anne_pro_layers {
    _BASE_LAYER,
    _FN1_LAYER,
    _FN2_LAYER,
};

/*
* Layer _BASE_LAYER
* ,-----------------------------------------------------------------------------------------.
* | esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |    Bksp   |
* |-----------------------------------------------------------------------------------------+
* | Tab    |  q  |  w  |  e  |  r  |  t  |  y  |  u  |  i  |  o  |  p  |  [  |  ]  |   \    |
* |-----------------------------------------------------------------------------------------+
* | Caps    |  a  |  s  |  d  |  f  |  g  |  h  |  j  |  k  |  l  |  ;  |  '  |    Enter    |
* |-----------------------------------------------------------------------------------------+
* | Shift      |  z  |  x  |  c  |  v  |  b  |  n  |  m  |  ,  |  .  |  /  |    Shift       |
* |-----------------------------------------------------------------------------------------+
* | Ctrl  |  GUI  |  Alt  |               space             |  GUI  |  ALT  |  FN1  | Ctrl  |
* \-----------------------------------------------------------------------------------------/
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
    [_BASE_LAYER] = KEYMAP(/* Base */
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
        KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, RSFT_T(KC_UP),
        KC_LCTL, KC_LALT, KC_LGUI, KC_SPC, KC_RGUI, LT(KC_RALT, KC_LEFT), LT(_FN1_LAYER, KC_DOWN), RCTL_T(KC_RGHT)),
    /*
  * Layer _FN1_LAYER
  * ,-----------------------------------------------------------------------------------------.
  * |  `  |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 |  DELETE   |
  * |-----------------------------------------------------------------------------------------+
  * | Tab    |  q  | UP  |  e  |  r  |  t  |  y  |  u  |  i  |  o  | PS | HOME | END |   \    |
  * |-----------------------------------------------------------------------------------------+
  * | Esc     |LEFT |DOWN |RIGHT|  f  |  g  |  h  |  j  |  k  |  l  | PGUP|PGDN |    Enter    |
  * |-----------------------------------------------------------------------------------------+
  * | Shift      |V-UP |V-DWN|MUTE |  v  |  b  |  n  |  m  |  ,  |INSRT| DEL |    Shift       |
  * |-----------------------------------------------------------------------------------------+
  * | Ctrl  |  L1   |  Alt  |               space             |  Alt  |  FN2  |  FN1  | Ctrl  |
  * \-----------------------------------------------------------------------------------------/
  *
  */
    [_FN1_LAYER] = KEYMAP(/* Base */
        KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL,
        KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_HOME, KC_END, KC_TRNS,
        MO(_FN2_LAYER), KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_PGDN, KC_TRNS,
        KC_TRNS, KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_INS, KC_DEL, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(_FN2_LAYER), KC_TRNS, KC_TRNS),
    /*
  * Layer _FN2_LAYER
  * ,-----------------------------------------------------------------------------------------.
  * |  ~  | BT1 | BT2 | BT3 | BT4 |  F5 |  F6 |  F7 |LEDOF|LEDON| F10 | F11 | F12 |    Bksp   |
  * |-----------------------------------------------------------------------------------------+
  * | Tab    |  q  | UP  |  e  |  r  |  t  |  y  |  u  |  i  |  o  | PS | HOME | END |   \    |
  * |-----------------------------------------------------------------------------------------+
  * | Esc     |LEFT |DOWN |RIGHT|  f  |  g  |  h  |  j  |  k  |  l  | PGUP|PGDN |    Enter    |
  * |-----------------------------------------------------------------------------------------+
  * | Shift      |  z  |  x  |  c  |  v  |  b  |  n  |  m  |  ,  |INSRT| DEL |    Shift       |
  * |-----------------------------------------------------------------------------------------+
  * | Ctrl  |  L1   |  Alt  |               space             |  Alt  |  FN2  |  FN1  | Ctrl  |
  * \-----------------------------------------------------------------------------------------/
  *
  */
    [_FN2_LAYER] = KEYMAP(/* Base */
        KC_TRNS, KC_AP2_BT1, KC_AP2_BT2, KC_AP2_BT3, KC_AP2_BT4, KC_TRNS, KC_TRNS, KC_TRNS, KC_AP_LED_OFF, KC_AP_LED_ON, KC_AP_LED_NEXT_PROFILE, KC_TRNS, KC_TRNS, KC_TRNS,
        MO(_FN2_LAYER), KC_TRNS, KC_UP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_HOME, KC_END, KC_TRNS,
        KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_PGDN, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_INS, KC_DEL, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(_FN2_LAYER), MO(_FN1_LAYER), KC_TRNS),
};
const uint16_t keymaps_size = sizeof(keymaps);

void matrix_init_user(void)
{
}

void matrix_scan_user(void)
{
}

layer_state_t layer_state_set_user(layer_state_t layer)
{
    return layer;
}

void raw_hid_receive(uint8_t *data, uint8_t length) {
  uprintf("raw_hid len: %u\n", length);
  if (length == 1)
    annepro2LedSetProfile(data[0]);
  else {
    for (uint8_t i = 0; i < length; i++){
      usb_buf[buf_fil + i] = data[i];
    }
    buf_fil += length;
    if (buf_fil >= 211) {
      sdWrite(&SD0, usb_buf, 211);
      buf_fil = 0;
    }
//    for (int i = 0; i < length; i++) {
//      sdPut(&SD0, data[i]);
//      sdGet(&SD0);
//    }
  }
}

/*!
 * @returns false   processing for this keycode has been completed.
 */
bool process_record_user(uint16_t keycode, keyrecord_t* record)
{
    switch (keycode) {
    case KC_AP_LED_OFF:
        if (record->event.pressed) {
            user_config.leds_on = false;
            eeprom_write((void*)&user_config, 0, sizeof(user_config_t));
        }
        return false;
    case KC_AP_LED_ON:
        if (record->event.pressed) {
            user_config.leds_on = true;
            eeprom_write((void*)&user_config, 0, sizeof(user_config_t));
        }
        return false;
    case KC_AP_LED_NEXT_PROFILE:
        if (record->event.pressed) {
            user_config.leds_profile = (user_config.leds_profile + 1) % numProfiles;
            annepro2LedSetProfile(user_config.leds_profile);
            eeprom_write((void*)&user_config, 0, sizeof(user_config_t));
        }
        return false;
    default:
        break;
    }
    return true;
}

void keyboard_post_init_user(void)
{
    // Customize these values to desired behavior
    debug_enable = true;
    //debug_matrix = true;
    //debug_keyboard=true;
    //debug_mouse=true;

    // Read the user config from EEPROM
    eeprom_read((void*)&user_config, 0, sizeof(user_config_t));

    // initialize a new eeprom
    if (user_config.magic != 0xDE)
    {
        user_config.magic = 0xDE;
        user_config.leds_on = false;
        user_config.leds_profile = 0;
        eeprom_write((void*)&user_config, 0, sizeof(user_config_t));
    }

    numProfiles = annepro2LedGetNumProfiles();

    if (user_config.leds_on) {
        // send profile before so that we don't get a flicker on startup
        annepro2LedSetProfile(user_config.leds_profile);
        annepro2LedEnable();
    } else {
        annepro2LedDisable();
    }
}