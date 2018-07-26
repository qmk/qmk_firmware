#include "CMD60.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = KEYMAP( /* CMD60 - QWERTY */
      KC_ESC,   KC_1,     KC_2,     KC_3,    KC_4,     KC_5,     KC_6,     KC_7,    KC_8,  KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  \
      KC_TAB,   KC_Q,     KC_W,     KC_E,    KC_R,     KC_T,     KC_Y,     KC_U,    KC_I,  KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  \
      LT(3, KC_ENT),  KC_A,     KC_S,     KC_D,    KC_F,     KC_G,     KC_H,     KC_J,    KC_K,  KC_L,     KC_SCLN,  KC_QUOT,  KC_NO,    KC_ENT,   \
      KC_LSFT,  KC_Z,    KC_X,     KC_C,    KC_V,     KC_B,     KC_N,     KC_M,    KC_COMM,  KC_DOT,  KC_SLSH,   KC_NO,  KC_NO,    KC_RSFT,  \
      KC_LCTL,  KC_LGUI,  KC_LALT,                     LT(2, KC_SPC),                                       MO(3),  MO(4),  MO(5),  TG(1) \
  ),
  [1] = KEYMAP( /* CMD60 - GameMode */
      KC_TRNS,   KC_TRNS,     KC_TRNS,     KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,    KC_TRNS,  KC_TRNS,     KC_TRNS,     KC_TRNS,  KC_TRNS,   KC_TRNS,  \
      KC_TRNS,   KC_TRNS,     KC_TRNS,     KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,    KC_TRNS,  KC_TRNS,     KC_TRNS,     KC_TRNS,  KC_TRNS,  KC_TRNS,  \
      KC_CAPS,  KC_TRNS,  KC_TRNS,     KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,    KC_TRNS,  KC_TRNS,     KC_TRNS,  KC_TRNS,  KC_NO,    KC_TRNS,   \
      KC_LSFT,  KC_TRNS,    KC_TRNS,     KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_NO,  KC_NO,    KC_RSFT,  \
      KC_TRNS,  KC_NO,  KC_TRNS,                     KC_SPC,                                       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS \
  ),
  [2] = KEYMAP( /* CMD60 - Arrows */
      KC_GRV,   KC_F1,     KC_F2,     KC_F3,    KC_F4,     KC_F5,     KC_F6,     KC_F7,    KC_F8,  KC_F9,     KC_F10,     KC_F11,  KC_F12,   KC_DEL,  \
      KC_TRNS,   KC_BSPC,     KC_UP,     KC_DEL,    KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_BSPC,    KC_UP,  KC_DEL,     KC_PSCR,     KC_SLCK,  KC_PAUS,  KC_TRNS,  \
      KC_TRNS,  KC_LEFT,  KC_DOWN,     KC_RIGHT,    KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_LEFT,    KC_DOWN,  KC_RIGHT,     KC_TRNS,  KC_TRNS,  KC_NO,    KC_TRNS,   \
      KC_TRNS,  KC_TRNS,    KC_TRNS,     KC_TRNS,    KC_SPC,     KC_TRNS,     KC_TRNS,     KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_NO,  KC_NO,    KC_TRNS,  \
      KC_TRNS,  KC_TRNS,  KC_TRNS,                     KC_TRNS,                                       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS \
  ),
  [3] = KEYMAP( /* CMD60 - Functions */
      KC_GRV,   KC_F1,     KC_F2,     KC_F3,    KC_F4,     KC_F5,     KC_F6,     KC_F7,    KC_F8,  KC_F9,     KC_F10,     KC_F11,  KC_F12,   KC_DEL,  \
      KC_AUDIO_MUTE,   KC_BSPC,     KC_PGUP,     KC_DEL,    KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_PGUP,    KC_UP,  KC_PGDN,     KC_TRNS,     KC_PAUSE,  KC_SLCK,  KC_PSCREEN,  \
      KC_TRNS,  KC_HOME,  KC_PGDN,     KC_END,    KC_TRNS,     KC_TRNS,     KC_HOME,     KC_LEFT,    KC_DOWN,  KC_RIGHT,     KC_TRNS,  KC_INSERT,  KC_NO,    KC_TRNS,   \
      KC_TRNS,  KC_TRNS,    KC_TRNS,     KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_END,     KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_NO,  KC_NO,    KC_TRNS,  \
      KC_TRNS,  KC_TRNS,  KC_TRNS,                     KC_TRNS,                                       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS \
  ),
  [4] = KEYMAP( /* CMD60 - Mouse */
      KC_SYSTEM_SLEEP,   KC_TRNS,     KC_TRNS,     KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,    KC_TRNS,  KC_TRNS,     KC_TRNS,     KC_TRNS,  KC_TRNS,   KC_TRNS,  \
      KC_TRNS,   KC_TRNS,     KC_TRNS,     KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,    KC_MS_BTN1,  KC_MS_UP,     KC_MS_BTN2,     KC_TRNS,  KC_TRNS,  KC_TRNS,  \
      KC_TRNS,  KC_TRNS,  KC_TRNS,     KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,    KC_MS_LEFT,  KC_MS_DOWN,     KC_MS_RIGHT,  KC_TRNS,  KC_NO,    KC_TRNS,   \
      KC_TRNS,  KC_TRNS,    KC_TRNS,     KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,    KC_MS_WH_UP,  KC_MS_BTN3,  KC_MS_WH_DOWN,   KC_NO,  KC_NO,    KC_TRNS,  \
      KC_TRNS,  KC_TRNS,  KC_TRNS,                     KC_TRNS,                                       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS \
  ),
  [5] = KEYMAP( /* CMD60 - Media */
      KC_SYSTEM_WAKE,   KC_TRNS,     KC_TRNS,     KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,    KC_TRNS,  KC_TRNS,     KC_TRNS,     KC_TRNS,  KC_TRNS,   KC_TRNS,  \
      KC_TRNS,   KC_TRNS,     KC_TRNS,     KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,    KC_TRNS,  KC_TRNS,     KC_TRNS,     KC_AUDIO_VOL_DOWN,  KC_AUDIO_VOL_UP,  KC_AUDIO_MUTE,  \
      KC_TRNS,  KC_TRNS,  KC_TRNS,     KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,    KC_TRNS,  KC_TRNS,     KC_TRNS,  KC_MEDIA_PREV_TRACK,  KC_MEDIA_NEXT_TRACK,    KC_MEDIA_PLAY_PAUSE,   \
      KC_TRNS,  KC_TRNS,    KC_TRNS,     KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,    KC_TRNS,  KC_WWW_BACK,  KC_WWW_FORWARD,   KC_NO,  KC_NO,    KC_WWW_REFRESH,  \
      KC_TRNS,  KC_TRNS,  KC_TRNS,                     KC_TRNS,                                       KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS \
  ),
};

const uint16_t PROGMEM fn_actions[] = {

};


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};
