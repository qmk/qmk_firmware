#include QMK_KEYBOARD_H
#include "version.h"

#include "keymap_german.h"

#include "keymap_nordic.h"

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here

  // Programmer's Dvorak "macros" :
  //  To be paired with get_mods to enable both
  //  Shift functionality and Programmer's Dvorak

  DVP_ESC, // Grave escape basically i think
  DVP_AMPR,
  DVP_LBRACKET,
  DVP_LCBR,
  DVP_RCBR,
  DVP_LPRN,
  DVP_AT,

  DVP_EQUAL,
  DVP_ASTERISK,
  DVP_RPRN,
  DVP_PLUS,
  DVP_RBRACKET,
  DVP_EXLM,
  DVP_HASH,

  RU_2,
  RU_3,
  RU_4,
  RU_6,
  RU_7,
  RU_DOT,

  SHFT_COMMA,
  SHFT_DOT,

  RGB_SLD,
  RGB_FF0000,
  RGB_008000,
  RGB_0000FF,
  RGB_FFFFFF,
  RGB_800080
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Programmer's Dvorak layer
  [0] = LAYOUT_ergodox(
    DVP_ESC,      DVP_AMPR,         DVP_LBRACKET, DVP_LCBR,         DVP_RCBR,     DVP_LPRN,   DVP_AT,
    KC_TAB,       KC_SCOLON,        KC_COMMA,     KC_DOT,           KC_P,         KC_Y,       MO(4),
    MO(3),        KC_A,             KC_O,         KC_E,             KC_U,         KC_I,
    KC_LSHIFT,    KC_QUOTE,         KC_Q,         KC_J,             KC_K,         KC_X,       KC_HYPR,
    KC_LCTL,      KC_LALT,          KC_LGUI,      LCTL(KC_C),       LCTL(KC_V),

      KC_MS_BTN3, TO(1),    KC_HOME,  KC_SPACE,   MO(4),  KC_END,

    DVP_EQUAL,    DVP_ASTERISK,     DVP_RPRN,     DVP_PLUS,         DVP_RBRACKET, DVP_EXLM,   DVP_HASH,
    TT(4),        KC_F,             KC_G,         KC_C,             KC_R,         KC_L,       KC_SLASH,
                  KC_D,             KC_H,         KC_T,             KC_N,         KC_S,       KC_MINUS,
    KC_MEH,       KC_B,             KC_M,         KC_W,             KC_V,         KC_Z,       MO(3),
                                    KC_DELETE,    KC_BSLASH,        KC_RGUI,      KC_RCTL,    LCTL(KC_F),

      KC_F17,     KC_F18,   KC_PGUP,  KC_PGDOWN,  KC_ENTER,   KC_BSPACE
  ),
  // Gaming QWERTY layer
  [1] = LAYOUT_ergodox(
    KC_ESCAPE,  KC_1,   KC_2,     KC_3,         KC_4,       KC_5,         KC_F14,
    KC_TAB,     KC_Q,   KC_W,     KC_E,         KC_R,       KC_T,         KC_F23,
    MO(3),      KC_A,   KC_S,     KC_D,         KC_F,       KC_G,
    KC_LSHIFT,  KC_Z,   KC_X,     KC_C,         KC_V,       KC_B,         KC_F24,
    KC_LCTL,    KC_F8,  KC_LALT,  KC_F14,      KC_F13,

      KC_HOME,  TO(0),  KC_F15,  KC_SPACE, KC_LCTL,  KC_LALT,

    KC_6,       KC_7,   KC_8,     KC_9,         KC_0,       KC_MINUS,   KC_EQUAL,
    KC_F24,     KC_Y,   KC_U,     KC_I,         KC_O,       KC_P,       KC_BSLASH,
                KC_H,   KC_J,     KC_K,         KC_L,       KC_SCOLON,  KC_QUOTE,
    KC_F17,     KC_N,   KC_M,     KC_COMMA,     KC_DOT,     KC_SLASH,   KC_RSHIFT,
            KC_DELETE,  KC_F19,   KC_LGUI,       KC_F21,     KC_F22,

      KC_F17,   KC_F18, KC_PGUP,  KC_PGDOWN,    KC_ENTER,   KC_BSPACE
  ),
  [2] = LAYOUT_ergodox(
    KC_ESCAPE,  KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_C,
    KC_TAB,     KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,      TO(0),
    MO(3),      KC_1,      KC_2,      KC_3,      KC_4,      KC_5,
    KC_LSHIFT,  KC_6,      KC_7,      KC_8,      KC_9,      KC_0,     KC_NO,
    KC_LCTL,    KC_F8,     KC_LALT,   KC_I,      KC_S,

    KC_MS_BTN3, TO(1),  KC_HOME,  KC_SPACE, KC_LSHIFT,  KC_END,

    KC_NO,     KC_NUMLOCK,     KC_KP_SLASH,    KC_KP_ASTERISK, KC_KP_MINUS,     KC_NO,   KC_NO,
    TO(0),     KC_KP_7,        KC_KP_8,        KC_KP_9,        KC_KP_PLUS,      KC_NO,   KC_NO,
               KC_KP_4,        KC_KP_5,        KC_KP_6,        KC_EQUAL,        KC_NO,  KC_NO,
    KC_NO,     KC_KP_1,        KC_KP_2,        KC_KP_3,        KC_KP_ENTER,     KC_NO,  KC_NO,
               KC_KP_0,        KC_KP_DOT,      KC_NO,          KC_NO,           KC_NO,

      TO(0), KC_F18, KC_PGUP,  KC_PGDOWN,  KC_ENTER, KC_BSPACE
  ),
  // Function Layer
  [3] = LAYOUT_ergodox(
    KC_DLR,         KC_F1,            KC_F2,              KC_F3,              KC_F4,              KC_F5,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT,   KC_MEDIA_PREV_TRACK,KC_MEDIA_PLAY_PAUSE,KC_MEDIA_NEXT_TRACK,KC_NO,          TT(4),
    KC_TRANSPARENT, KC_TRANSPARENT,   KC_AUDIO_VOL_DOWN,  KC_AUDIO_VOL_UP,    KC_AUDIO_MUTE,      KC_TRANSPARENT,
    KC_LSHIFT,      LALT(KC_Z),       KC_TRANSPARENT,     KC_TRANSPARENT,     KC_F12,             KC_TRANSPARENT, ALL_T(KC_NO),
    KC_LCTL,        KC_LALT,          KC_LGUI,            KC_CAPSLOCK,        LSFT(KC_F12),

     KC_PSCREEN, KC_PGUP,  KC_PGDOWN,  KC_SPACE, KC_LSHIFT,  KC_INSERT,

    KC_F6,          KC_F7,            KC_F8,              KC_F9,              KC_F10,             KC_F11,         KC_F12,
    KC_NO,          KC_HOME,          KC_TRANSPARENT,     KC_PSCREEN,         KC_SLCK,            KC_TRANSPARENT, KC_TRANSPARENT,
                    KC_LEFT,          KC_DOWN,            KC_UP,              KC_RIGHT,           KC_TRANSPARENT, KC_TRANSPARENT,
    MEH_T(KC_NO),   KC_CALCULATOR,    KC_TRANSPARENT,     KC_TRANSPARENT,     KC_TRANSPARENT,     KC_TRANSPARENT, KC_RSHIFT,
                                      KC_DELETE,          KC_INSERT,          KC_TRANSPARENT,     KC_F19,         KC_RCTL,

     TO(2),KC_TRANSPARENT,KC_TRANSPARENT,LALT(KC_F10),KC_ENTER,KC_BSPACE
  ),
  // Keypad, Lighting, and Mouse emulation layer
 ///*
    [4] = LAYOUT_ergodox(
    KC_ESCAPE,  KC_NO,      KC_NO,        KC_MS_BTN3, KC_NO,        KC_NO,          KC_NO,
    KC_TAB,     KC_NO,      KC_MS_BTN2,   KC_MS_UP,   KC_MS_BTN1,   KC_MS_WH_UP,    TO(0),
    KC_NO,      KC_NO,      KC_MS_LEFT,   KC_MS_DOWN, KC_MS_RIGHT,  KC_MS_WH_DOWN,
    KC_LSHIFT,  KC_NO,      KC_NO,        KC_UP,      KC_NO,        KC_NO,          TO(5),
    KC_LCTL,    KC_NO,      KC_LEFT,      KC_DOWN,    KC_RIGHT,

    KC_MS_BTN3, TO(1),  KC_HOME,  KC_SPACE, KC_LSHIFT,  KC_END,

    KC_NO,          KC_NUMLOCK,     KC_KP_SLASH,    KC_KP_ASTERISK, KC_CALCULATOR,    KC_NO,      RGB_VAI,
    TO(0),          KC_KP_7,        KC_KP_8,        KC_KP_9,        KC_KP_MINUS,      KC_NO,      RGB_VAD,
                    KC_KP_4,        KC_KP_5,        KC_KP_6,        KC_KP_PLUS,       KC_NO,    RGB_HUI,
    KC_NO,          KC_KP_1,        KC_KP_2,        KC_KP_3,        KC_EQUAL,         RGB_SLD,    RGB_HUD,
                                    KC_KP_0,        KC_KP_DOT,      KC_KP_ENTER,      RGB_MOD,   RGB_TOG,

      KC_F17, KC_F18, KC_PGUP,  KC_PGDOWN,  KC_ENTER, KC_BSPACE
  )
  //*/
  /*
  // Keypad, Lighting, and Mouse emulation layer
  [4] = KEYMAP(
    KC_ESCAPE,  KC_NO,      KC_NO,        KC_MS_BTN3, KC_NO,        KC_NO,          KC_NO,
    KC_TAB,     KC_NO,      KC_MS_BTN2,   KC_MS_UP,   KC_MS_BTN1,   KC_MS_WH_UP,    TO(0),
    KC_NO,      KC_NO,      KC_MS_LEFT,   KC_MS_DOWN, KC_MS_RIGHT,  KC_MS_WH_DOWN,
    KC_LSHIFT,  KC_NO,      KC_NO,        KC_UP,      KC_NO,        KC_NO,          TO(5),
    KC_LCTL,    KC_NO,      KC_LEFT,      KC_DOWN,    KC_RIGHT,

    KC_MS_BTN3, TO(1),  KC_HOME,  KC_SPACE, KC_LSHIFT,  KC_END,

    KC_NO,    KC_I,       KC_NUMLOCK,     KC_KP_SLASH,    KC_KP_ASTERISK, KC_CALCULATOR,  RGB_VAI,
    TO(0),    KC_G,       KC_KP_7,        KC_KP_8,        KC_KP_9,        KC_KP_MINUS,    RGB_VAD,
              SHFT_COMMA,       KC_KP_4,        KC_KP_5,        KC_KP_6,        KC_KP_PLUS,     RGB_HUI,
    KC_NO,    SHFT_DOT,       KC_KP_1,        KC_KP_2,        KC_KP_3,        KC_EQUAL,       RGB_HUD,
              KC_NO,                       KC_KP_0,        KC_KP_DOT,      KC_KP_ENTER,    RGB_TOG,

      KC_F17, KC_F18, KC_PGUP,  KC_PGDOWN,  KC_ENTER, KC_BSPACE
  )
  */

};

void led_set_keymap(uint8_t usb_led) {

}

void matrix_init_user (void) {

}


bool left_shift_down = false;
bool right_shift_down = false;

bool numlock = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    case KC_LSHIFT:
    if (record->event.pressed)
      {
        left_shift_down = true;
      return true;
      }
      else
      {
        left_shift_down = false;
        return true;
      }
    break;
    case KC_RSHIFT:

      if (record->event.pressed)
      {
        right_shift_down = true;
      return true;
      }
      else
      {
        right_shift_down = false;
        return true;
      }
    break;
    case KC_NUMLOCK:

      if (record->event.pressed)
      {
        numlock = !numlock;
    }
    break;

    case DVP_ESC:
    if (left_shift_down || right_shift_down)
    {
      if(record->event.pressed)
        SEND_STRING("~");
      return false;
    }
    else
    {
      if(record->event.pressed)
        SEND_STRING(SS_DOWN(X_ESCAPE));
      else
        SEND_STRING(SS_UP(X_ESCAPE));
      return false;
    }
    break;

    case DVP_AMPR:
    if (left_shift_down || right_shift_down)
    {
      if(record->event.pressed)
      {
        SEND_STRING("%");

      }
    }
    else
    {
      if(record->event.pressed)
        SEND_STRING("&");
    }
    return false;

    break;

    case SHFT_DOT:
      if(record->event.pressed)
        SEND_STRING(">");
      break;

    case SHFT_COMMA:
      if(record->event.pressed)
        SEND_STRING("<");
      break;

    case DVP_LBRACKET:
    if (left_shift_down || right_shift_down)
    {
      if(record->event.pressed)
        {
          if(left_shift_down)
            unregister_code(KC_LSHIFT);
          if(right_shift_down)
            unregister_code(KC_RSHIFT);

          register_code(KC_7);
          unregister_code(KC_7);

          if(left_shift_down)
            register_code(KC_LSHIFT);
          if(right_shift_down)
            register_code(KC_RSHIFT);
        }
    }
    else
    {
      if(record->event.pressed)
        SEND_STRING("[");
    }
    return false;

        return false;
        break;

    case DVP_LCBR:
    if (left_shift_down || right_shift_down)
    {
      if(record->event.pressed)
       {
          if(left_shift_down)
            unregister_code(KC_LSHIFT);
          if(right_shift_down)
            unregister_code(KC_RSHIFT);

          register_code(KC_5);
          unregister_code(KC_5);

          if(left_shift_down)
            register_code(KC_LSHIFT);
          if(right_shift_down)
            register_code(KC_RSHIFT);
        }
    }
    else
    {
      if(record->event.pressed)
        SEND_STRING("{");
    }
    return false;
    break;

    case DVP_RCBR:
    if (left_shift_down || right_shift_down)
    {
      if(record->event.pressed)
      {
        if(left_shift_down)
          unregister_code(KC_LSHIFT);
        if(right_shift_down)
          unregister_code(KC_RSHIFT);

        register_code(KC_3);
        unregister_code(KC_3);

        if(left_shift_down)
          register_code(KC_LSHIFT);
        if(right_shift_down)
          register_code(KC_RSHIFT);
      }
    }
    else
    {
      if(record->event.pressed)
        SEND_STRING("}");
    }
    return false;
    break;

    case DVP_LPRN:
    if (left_shift_down || right_shift_down)
    {
      if(record->event.pressed)
      {
        if(left_shift_down)
          unregister_code(KC_LSHIFT);
        if(right_shift_down)
          unregister_code(KC_RSHIFT);

        register_code(KC_1);
        unregister_code(KC_1);

        if(left_shift_down)
          register_code(KC_LSHIFT);
        if(right_shift_down)
          register_code(KC_RSHIFT);
      }
    }
    else
    {
      if(record->event.pressed)
        SEND_STRING("(");
    }
    return false;
    break;

    case DVP_AT:
    if (left_shift_down || right_shift_down)
    {
      if(record->event.pressed)
      {
        if(left_shift_down)
          unregister_code(KC_LSHIFT);
        if(right_shift_down)
          unregister_code(KC_RSHIFT);

        register_code(KC_LSHIFT);
        register_code(KC_6);
        unregister_code(KC_6);
        unregister_code(KC_LSHIFT);

        if(left_shift_down)
          register_code(KC_LSHIFT);
        if(right_shift_down)
          register_code(KC_RSHIFT);
      }
    }
    else
    {
      if(record->event.pressed)
        SEND_STRING("@");
    }
    return false;
    break;


    case DVP_EQUAL:
    if (left_shift_down || right_shift_down)
    {
      if(record->event.pressed)
      {
        if(left_shift_down)
          unregister_code(KC_LSHIFT);
        if(right_shift_down)
          unregister_code(KC_RSHIFT);

        register_code(KC_9);
        unregister_code(KC_9);

        if(left_shift_down)
          register_code(KC_LSHIFT);
        if(right_shift_down)
          register_code(KC_RSHIFT);
      }
    }
    else
    {
      if(record->event.pressed)
        SEND_STRING("=");
    }
    return false;
    break;

    case DVP_ASTERISK:
    if (left_shift_down || right_shift_down)
    {
      if(record->event.pressed)
      {
        if(left_shift_down)
          unregister_code(KC_LSHIFT);
        if(right_shift_down)
          unregister_code(KC_RSHIFT);

        register_code(KC_0);
        unregister_code(KC_0);

        if(left_shift_down)
          register_code(KC_LSHIFT);
        if(right_shift_down)
          register_code(KC_RSHIFT);
      }
    }
    else
    {
      if(record->event.pressed)
        SEND_STRING("*");
    }
    return false;
    break;

    case DVP_RPRN:
    if (left_shift_down || right_shift_down)
    {
      if(record->event.pressed)
      {
        if(left_shift_down)
          unregister_code(KC_LSHIFT);
        if(right_shift_down)
          unregister_code(KC_RSHIFT);

        register_code(KC_2);
        unregister_code(KC_2);

        if(left_shift_down)
          register_code(KC_LSHIFT);
        if(right_shift_down)
          register_code(KC_RSHIFT);
      }
    }
    else
    {
      if(record->event.pressed)
        SEND_STRING(")");
    }
    return false;
    break;

    case DVP_PLUS:
    if (left_shift_down || right_shift_down)
    {
      if(record->event.pressed)
      {
        if(left_shift_down)
          unregister_code(KC_LSHIFT);
        if(right_shift_down)
          unregister_code(KC_RSHIFT);

        register_code(KC_4);
        unregister_code(KC_4);

        if(left_shift_down)
          register_code(KC_LSHIFT);
        if(right_shift_down)
          register_code(KC_RSHIFT);
      }
    }
    else
    {
      if(record->event.pressed)
        SEND_STRING("+");
    }
    return false;
    break;

    case DVP_RBRACKET:
    if (left_shift_down || right_shift_down)
    {
      if(record->event.pressed)
      {
        if(left_shift_down)
          unregister_code(KC_LSHIFT);
        if(right_shift_down)
          unregister_code(KC_RSHIFT);

        register_code(KC_6);
        unregister_code(KC_6);

        if(left_shift_down)
          register_code(KC_LSHIFT);
        if(right_shift_down)
          register_code(KC_RSHIFT);
      }
    }
    else
    {
      if(record->event.pressed)
        SEND_STRING("]");
    }
    return false;
    break;

    case DVP_EXLM:
    if (left_shift_down || right_shift_down)
    {
      if(record->event.pressed)
      {
        if(left_shift_down)
          unregister_code(KC_LSHIFT);
        if(right_shift_down)
          unregister_code(KC_RSHIFT);

        register_code(KC_8);
        unregister_code(KC_8);

        if(left_shift_down)
          register_code(KC_LSHIFT);
        if(right_shift_down)
          register_code(KC_RSHIFT);
      }
    }
    else
    {
      if(record->event.pressed)
        SEND_STRING("!");
    }
    return false;
    break;

    case DVP_HASH:
    if (left_shift_down || right_shift_down)
    {
      if(record->event.pressed)
      {
        if(left_shift_down)
          unregister_code(KC_LSHIFT);
        if(right_shift_down)
          unregister_code(KC_RSHIFT);

        register_code(KC_GRAVE);
        unregister_code(KC_GRAVE);

        if(left_shift_down)
          register_code(KC_LSHIFT);
        if(right_shift_down)
          register_code(KC_RSHIFT);
      }
    }
    else
    {
      if(record->event.pressed)
        SEND_STRING("#");
    }
    return false;
    break;

    // Russian
    case RU_2:
    if (left_shift_down || right_shift_down)
    {
      if(record->event.pressed)
      {
        if(left_shift_down)
          unregister_code(KC_LSHIFT);
        if(right_shift_down)
          unregister_code(KC_RSHIFT);

        register_code(KC_GRAVE);
        unregister_code(KC_GRAVE);

        if(left_shift_down)
          register_code(KC_LSHIFT);
        if(right_shift_down)
          register_code(KC_RSHIFT);
      }
    }
    else
    {
      if(record->event.pressed)
        SEND_STRING("#");
    }
    return false;
    break;
case RU_3:
    if (left_shift_down || right_shift_down)
    {
      if(record->event.pressed)
      {
        if(left_shift_down)
          unregister_code(KC_LSHIFT);
        if(right_shift_down)
          unregister_code(KC_RSHIFT);

        register_code(KC_GRAVE);
        unregister_code(KC_GRAVE);

        if(left_shift_down)
          register_code(KC_LSHIFT);
        if(right_shift_down)
          register_code(KC_RSHIFT);
      }
    }
    else
    {
      if(record->event.pressed)
        SEND_STRING("#");
    }
    return false;
    break;
case RU_4:
    if (left_shift_down || right_shift_down)
    {
      if(record->event.pressed)
      {
        if(left_shift_down)
          unregister_code(KC_LSHIFT);
        if(right_shift_down)
          unregister_code(KC_RSHIFT);

        register_code(KC_GRAVE);
        unregister_code(KC_GRAVE);

        if(left_shift_down)
          register_code(KC_LSHIFT);
        if(right_shift_down)
          register_code(KC_RSHIFT);
      }
    }
    else
    {
      if(record->event.pressed)
        SEND_STRING("#");
    }
    return false;
    break;
case RU_6:
    if (left_shift_down || right_shift_down)
    {
      if(record->event.pressed)
      {
        if(left_shift_down)
          unregister_code(KC_LSHIFT);
        if(right_shift_down)
          unregister_code(KC_RSHIFT);

        register_code(KC_GRAVE);
        unregister_code(KC_GRAVE);

        if(left_shift_down)
          register_code(KC_LSHIFT);
        if(right_shift_down)
          register_code(KC_RSHIFT);
      }
    }
    else
    {
      if(record->event.pressed)
        SEND_STRING("#");
    }
    return false;
    break;
case RU_7:
    if (left_shift_down || right_shift_down)
    {
      if(record->event.pressed)
      {
        if(left_shift_down)
          unregister_code(KC_LSHIFT);
        if(right_shift_down)
          unregister_code(KC_RSHIFT);

        register_code(KC_GRAVE);
        unregister_code(KC_GRAVE);

        if(left_shift_down)
          register_code(KC_LSHIFT);
        if(right_shift_down)
          register_code(KC_RSHIFT);
      }
    }
    else
    {
      if(record->event.pressed)
        SEND_STRING("#");
    }
    return false;
    break;

  case RU_DOT:
    if (left_shift_down || right_shift_down)
    {
      if(record->event.pressed)
      {
        if(left_shift_down)
          unregister_code(KC_LSHIFT);
        if(right_shift_down)
          unregister_code(KC_RSHIFT);

        register_code(KC_GRAVE);
        unregister_code(KC_GRAVE);

        if(left_shift_down)
          register_code(KC_LSHIFT);
        if(right_shift_down)
          register_code(KC_RSHIFT);
      }
    }
    else
    {
      if(record->event.pressed)
        SEND_STRING("#");
    }
    return false;
    break;


    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
      break;

    case RGB_FF0000:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_enable();
          rgblight_mode(1);
          rgblight_setrgb(0xff,0x00,0x00);
        #endif
      }
      return false;
      break;

    case RGB_008000:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_enable();
          rgblight_mode(1);
          rgblight_setrgb(0x00,0x80,0x00);
        #endif
      }
      return false;
      break;

    case RGB_0000FF:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_enable();
          rgblight_mode(1);
          rgblight_setrgb(0x00,0x00,0xff);
        #endif
      }
      return false;
      break;

    case RGB_FFFFFF:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_enable();
          rgblight_mode(1);
          rgblight_setrgb(0xff,0xff,0xff);
        #endif
      }
      return false;
      break;

    case RGB_800080:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_enable();
          rgblight_mode(1);
          rgblight_setrgb(0x80,0x00,0x80);
        #endif
      }
      return false;
      break;

  }
  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {

    uint8_t layer = biton32(state);

  //  ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      case 0:
        break;
      case 1:
        ergodox_right_led_1_on();
        break;
      case 2:
        ergodox_right_led_2_on();
        break;
      case 3:
        ergodox_right_led_3_on();
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        break;
      default:
        break;
    }
    return state;

};
