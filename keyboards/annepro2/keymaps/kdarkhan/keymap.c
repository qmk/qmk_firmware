#include "annepro2.h"
#include "qmk_ap2_led.h"
#include <print.h>
#include <stdint.h>
#ifdef ANNEPRO2_C18
#include "eeprom_w25x20cl.h"
#endif

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

enum custom_codes {
  KC_AP_WIN = AP2_SAFE_RANGE,
  KC_AP_LIN,
  KC_AP_MAC,
  KC_AP_UNICODE
};

enum tap_dance_codes {
  KC_AP_TD_RCTRL
};

// define out default user_config
user_config_t user_config = {.magic = 0xDE, .leds_on = 0, .leds_profile = 0};

// this means that there should not be more than 16 profiles
uint16_t dyn_key_mask = 0;

static uint8_t usb_buf[256];
static uint8_t buf_fil = 0;

enum anne_pro_layers {
  _BASE_LAYER,
  _MAC_LAYER,
  _CAPS_LAYER,
  _FN1_LAYER,
  _FN2_LAYER,
  _TAP2_LAYER,
};

// clang-format off
/*
 * Layer _BASE_LAYER
 * ,-----------------------------------------------------------------------------------------.
 * | `   |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |    Bksp   |
 * |-----------------------------------------------------------------------------------------+
 * | Tab    |  q  |  w  |  e  |  r  |  t  |  y  |  u  |  i  |  o  |  p  |  [  |  ]  |   \    |
 * |-----------------------------------------------------------------------------------------+
 * | Esc     |  a  |  s  |  d  |  f  |  g  |  h  |  j  |  k  |  l  |  ;  |  '  |    Enter    |
 * |-----------------------------------------------------------------------------------------+
 * | Shift      |  z  |  x  |  c  |  v  |  b  |  n  |  m  |  ,  |  .  |  /  |    Shift       |
 * |-----------------------------------------------------------------------------------------+
 * | Ctrl  |  GUI  |  Alt  |               space             |  FN1  |  FN2  |  Alt  | Ctrl  |
 * \-----------------------------------------------------------------------------------------/
 */
const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE_LAYER]  = KEYMAP(/* Base */
        KC_GRAVE, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, LT(_TAP2_LAYER, KC_BSLS),
        LT(_CAPS_LAYER, KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCOLON, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, TT(_FN1_LAYER), LT(_FN2_LAYER, KC_APP), KC_RALT, TD(KC_AP_TD_RCTRL)),
    [_MAC_LAYER]   = KEYMAP(/* Mac */
        KC_GRAVE, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, LT(_TAP2_LAYER, KC_BSLS),
        LT(_CAPS_LAYER, KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCOLON, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
        KC_LCTL, KC_LALT, KC_LGUI, KC_SPC, TT(_FN1_LAYER), LT(_FN2_LAYER, KC_APP), KC_RALT, TD(KC_AP_TD_RCTRL)),
    [_CAPS_LAYER] = KEYMAP(/* Hold CapsLock */
        _______, _______, _______, _______, _______, KC_AUDIO_VOL_DOWN, KC_AUDIO_MUTE, KC_AUDIO_VOL_UP, _______, _______, _______, _______, _______, KC_DELETE,
        _______, _______, _______, _______, KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK, KC_WWW_BACK, KC_WWW_HOME, KC_WWW_SEARCH, KC_PSCREEN, KC_HOME, KC_END, _______,
        _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_PGUP, KC_PGDN, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_INSERT, KC_DELETE, _______,
        _______, _______, _______, _______, _______, _______, _______, _______),
    [_FN1_LAYER]   = KEYMAP(/* FN1 */
        _______, _______, _______, _______, _______, _______, _______, _______, KC_KP_ASTERISK, KC_NUMLOCK, KC_KP_0, KC_KP_MINUS, KC_KP_PLUS, _______,
        _______, _______, _______, _______, _______, _______, _______, KC_KP_7, KC_KP_8, KC_KP_9, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, KC_KP_4, KC_KP_5, KC_KP_6, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_SLASH, KC_UP,
        _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT),
    [_FN2_LAYER]   = KEYMAP(/* FN2 */
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, KC_AP_WIN, _______, _______, _______, _______, _______, _______, _______, KC_PSCREEN, KC_HOME, KC_END, KC_AP_LED_ON,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_AP_LIN, KC_PGUP, KC_PGDN, KC_AP_LED_OFF,
        KC_AP2_USB, KC_AP2_BT_UNPAIR, KC_AP2_BT1, KC_AP2_BT2, KC_AP2_BT3, KC_AP2_BT4, _______, KC_AP_MAC, _______, _______, _______, KC_AP_LED_NEXT_INTENSITY,
        _______, _______, _______, _______, _______, _______, _______, KC_AP_LED_SPEED),
    [_TAP2_LAYER]   = KEYMAP(/* Hold |\ */
        _______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, _______,
        _______, KC_MS_BTN1, KC_MS_UP, KC_MS_BTN2, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_CAPS, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_MS_WH_DOWN, _______, KC_MS_WH_UP, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______),
};
// clang-format on

const uint16_t keymaps_size = sizeof(keymaps);

void matrix_init_user(void) {
      set_unicode_input_mode(UC_LNX);
}

void matrix_scan_user(void) {}

layer_state_t layer_state_set_user(layer_state_t layer) { return layer; }

void raw_hid_receive(uint8_t *data, uint8_t length) {
#ifdef CONSOLE_ENABLE
  uprintf("raw_hid len: %u\n", length);
#endif
  if (length == 1)
    annepro2LedSetProfile(data[0]);
  else {
    for (uint8_t i = 0; i < length; i++) {
      usb_buf[buf_fil + i] = data[i];
    }
    buf_fil += length;
    if (buf_fil >= 211) {
      sdWrite(&SD0, usb_buf, 211);
      buf_fil = 0;
    }
  }
}

/*!
 * @returns false   processing for this keycode has been completed.
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef ANNEPRO2_C18
  if (record->event.pressed) {
    dprintf("pressed %d %d\n", record->event.key.row, record->event.key.col);
  }
  switch (keycode) {
  case KC_AP_WIN:
    if (record->event.pressed) {
      default_layer_set(1 << _BASE_LAYER);
      // requires installation of
      // https://github.com/samhocevar/wincompose
      // on Windows machine
      set_unicode_input_mode(UC_WINC);
    }
    return false;
  case KC_AP_LIN:
    if (record->event.pressed) {
      default_layer_set(1 << _BASE_LAYER);
      set_unicode_input_mode(UC_LNX);
    }
    return false;
  case KC_AP_MAC:
    if (record->event.pressed) {
      default_layer_set(1 << _MAC_LAYER);
      set_unicode_input_mode(UC_MAC);
    }
    return false;
  case KC_AP_UNICODE:
    if (record->event.pressed) {
        qk_ucis_start();
    }
    return false;
  case KC_AP_LED_OFF:
    if (record->event.pressed) {
      user_config.leds_on = false;
      eeprom_write((void *)&user_config, 0, sizeof(user_config_t));
    }
    return false;
  case KC_AP_LED_ON:
    if (record->event.pressed) {
      if (user_config.leds_on) {
        user_config.leds_profile = (user_config.leds_profile + 1) % annepro2LedStatus.amountOfProfiles;
      } else {
        user_config.leds_on = true;
      }
      annepro2LedSetProfile(user_config.leds_profile);
      eeprom_write((void *)&user_config, 0, sizeof(user_config_t));
    }
    return false;
  case KC_AP_LED_NEXT_PROFILE:
    if (record->event.pressed) {
      user_config.leds_profile = (user_config.leds_profile + 1) % annepro2LedStatus.amountOfProfiles;
      annepro2LedSetProfile(user_config.leds_profile);
      eeprom_write((void *)&user_config, 0, sizeof(user_config_t));
    }
    return false;
  case KC_AP_LED_NEXT_INTENSITY:
    if (record->event.pressed) {
      annepro2LedNextIntensity();
    }
    return false;
  default:
    break;
  }
#endif
  return true;
}

void keyboard_post_init_user(void) {
#ifdef CONSOLE_ENABLE
  // Customize these values to desired behavior
  debug_enable = true;
  debug_matrix = true;
  // debug_keyboard=true;
  // debug_mouse=true;
#endif

#ifdef ANNEPRO2_C18
  // Read the user config from EEPROM
  eeprom_read((void *)&user_config, 0, sizeof(user_config_t));

  // initialize a new eeprom
  if (user_config.magic != 0xDE) {
    user_config.magic = 0xDE;
    user_config.leds_on = false;
    user_config.leds_profile = 0;
    eeprom_write((void *)&user_config, 0, sizeof(user_config_t));
  }

  if (user_config.leds_on) {
    // send profile before so that we don't get a flicker on startup
    annepro2LedSetProfile(user_config.leds_profile);
    annepro2LedEnable();
  } else {
    annepro2LedDisable();
  }
#endif
}

void dance_cln_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 3) {
        // tap 3 times to start unicode input
        qk_ucis_start();
    } else {
        register_code(KC_RCTL);
    }
}

void dance_cln_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count != 3) {
        unregister_code(KC_RCTL);
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [KC_AP_TD_RCTRL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cln_finished, dance_cln_reset),
};

const qk_ucis_symbol_t ucis_symbol_table[] = UCIS_TABLE(
    UCIS_SYM("poop", 0x1F4A9),                  // 💩
    UCIS_SYM("rofl", 0x1F923),                  // 🤣
    UCIS_SYM("tm", 0x2122),                     // ™
    UCIS_SYM("copy", 0x00A9),                   //©
    UCIS_SYM("look", 0x0CA0, 0x005F, 0x0CA0),   // ಠ_ಠ
    UCIS_SYM("euro", 0x20AC),                   // €
    UCIS_SYM("shrug", 0xAF, 0x5C, 0X5F, 0x28, 0x30C4, 0x29, 0x5F, 0x2F, 0xAF),  // ¯\_(ツ)_/¯
    UCIS_SYM("sweat", 0x1F605),                  // 😅
    UCIS_SYM("kiss", 0x1F48B),                   // 💋
    UCIS_SYM("wave", 0x1F44B),                   // 👋
    UCIS_SYM("thumb", 0x1F44D),                  // 👍
    UCIS_SYM("up", 0x2B06, 0xFE0F),              // ⬆
    UCIS_SYM("down", 0x2B07, 0xFE0F),             // ⬆
    UCIS_SYM("flip", 0x28, 0x256F, 0xB0, 0x25A1, 0xB0, 0x29, 0x256F, 0xFE35, 0x20, 0x253B, 0x2501, 0x253B),             // (╯°□°)╯︵ ┻━┻
    UCIS_SYM("face",0x28, 0x20, 0x360, 0xB0, 0x20, 0x35F, 0x296, 0x20, 0x361, 0xB0, 0x29)  // ( ͠° ͟ʖ ͡°)
);
