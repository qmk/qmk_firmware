/* Copyright 2018 REPLACE_WITH_YOUR_NAME
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE,

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
  SHFT_DOT,
  SHFT_COMMA
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Programmer's Dvorak
  [0] = LAYOUT(
                            KC_F13,   KC_F14,   KC_F15,       KC_F16,   KC_F17,   KC_F18,   KC_F19,   KC_F20,       KC_F21,   KC_F22,   KC_F23,       KC_F24,
                            KC_F1,    KC_F2,    KC_F3,        KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,        KC_F9,    KC_F10,   KC_F11,       KC_F12,
    KC_ESC,     TO(1),      DVP_ESC,  DVP_AMPR, DVP_LBRACKET, DVP_LCBR, DVP_RCBR, DVP_LPRN, DVP_EQUAL,DVP_ASTERISK, DVP_RPRN, DVP_PLUS, DVP_RBRACKET, DVP_EXLM, DVP_HASH, KC_BSPC,    KC_INS,  KC_HOME, KC_PGUP,    KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
    KC_NO,      TO(2),      KC_TAB,   KC_SCOLON,KC_COMMA,     KC_DOT,   KC_P,     KC_Y,     KC_F,     KC_G,         KC_C,     KC_R,     KC_L,         KC_SLSH,  DVP_AT,   KC_ENTER,   KC_DEL,  KC_END,  KC_PGDN,    KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
    KC_NO,      KC_NO,      MO(3),    KC_A,     KC_O,         KC_E,     KC_U,     KC_I,     KC_D,     KC_H,         KC_T,     KC_N,     KC_S,         KC_MINUS, KC_BSLS,                       KC_UP,               KC_P4,   KC_P5,   KC_P6,   MO(4),
    LCTL(KC_F), KC_LALT,    KC_LSHIFT,KC_ESC,   KC_QUOT,      KC_Q,     KC_J,     KC_K,     KC_X,     KC_B,         KC_M,     KC_W,     KC_V,         KC_Z,     KC_RSFT,              KC_LEFT, KC_BTN3, KC_RIGHT,   KC_P1,   KC_P2,   KC_P3,   KC_PENT,
    LCTL(KC_C), LCTL(KC_V), KC_LCTRL, KC_LGUI,                                    KC_SPC,                                                             KC_RALT,  KC_RCTRL,                      KC_DOWN,             KC_P0,            KC_PDOT
  ),

  // Qwerty layer + function
  [1] = LAYOUT(
                    KC_F13,   KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, KC_F21, KC_F22,   KC_F23,    KC_F24,
                    KC_F1,    KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10,   KC_F11,    KC_F12,
    KC_ESC, TO(0),  KC_GRV,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,     KC_0,      KC_MINUS, KC_EQL, KC_BSPC,    KC_INS,  KC_HOME, KC_PGUP,    KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
    KC_NO,  KC_NO,  KC_TAB,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,     KC_P,      KC_LBRC,  KC_RBRC,KC_ENTER,   KC_DEL,  KC_END,  KC_PGDN,    KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
    KC_NO,  KC_NO,  MO(3),    KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,     KC_SCOLON, KC_QUOT,  KC_BSLS,                     KC_UP,               KC_P4,   KC_P5,   KC_P6,   KC_BSPC,
    KC_NO,  KC_NO,  KC_LSHIFT,KC_NO,  KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMMA, KC_DOT,    KC_SLSH,  KC_RSFT,            KC_LEFT, KC_WH_D, KC_RIGHT,   KC_P1,   KC_P2,   KC_P3,   KC_PENT,
    KC_NO,  KC_LALT,KC_LCTRL, KC_LGUI,                                      KC_SPC,                                KC_RALT,  KC_RCTRL,                    KC_DOWN,             KC_P0,            KC_PDOT
  ),

  // Orirginal Layer
  [2] = LAYOUT(
                    KC_F13,   KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, KC_F21, KC_F22,   KC_F23,    KC_F24,
                    KC_F1,    KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10,   KC_F11,    KC_F12,
    KC_ESC, TO(1),  KC_GRV,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,     KC_0,      KC_MINUS, KC_EQL, KC_BSPC,    KC_INS,  KC_HOME, KC_PGUP,    KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
    KC_NO,  TO(0),  KC_TAB,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,     KC_P,      KC_LBRC,  KC_RBRC,KC_ENTER,   KC_DEL,  KC_END,  KC_PGDN,    KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
    KC_NO,  KC_NO,  KC_CAPS,  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,     KC_SCOLON, KC_QUOT,  KC_BSLS,                     KC_UP,               KC_P4,   KC_P5,   KC_P6,   KC_BSPC,
    KC_NO,  KC_NO,  KC_LSHIFT,KC_NO,  KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMMA, KC_DOT,    KC_SLSH,  KC_RSFT,            KC_LEFT, KC_WH_D, KC_RIGHT,   KC_P1,   KC_P2,   KC_P3,   KC_PENT,
    KC_NO,  KC_LALT,KC_LCTRL, KC_LGUI,                                        KC_SPC,                              KC_RALT,  KC_RCTRL,                    KC_DOWN,             KC_P0,            KC_PDOT
  ),

  // Function Layer
  [3] = LAYOUT(
                      KC_F1,    KC_F2,  KC_F3,                KC_F4,                KC_F5,                KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,
                      KC_F13,   KC_F14, KC_F15,               KC_F16,               KC_F17,               KC_F18,   KC_F19,   KC_F20,   KC_F21,   KC_F22,   KC_F23,     KC_F24,
    MU_TOG, KC_NO,    KC_ESC,   KC_1,   KC_2,                 KC_3,                 KC_4,                 KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,       KC_MINUS, KC_EQL, KC_BSPC,    KC_INS,  KC_HOME, KC_PGUP,    KC_NLCK,    KC_PSLS,    KC_PAST,    KC_PMNS,
    MU_MOD, KC_NO,    KC_TAB,   KC_NO,  KC_MEDIA_PREV_TRACK,  KC_MEDIA_PLAY_PAUSE,  KC_MEDIA_NEXT_TRACK,  KC_NO,    KC_NO,    KC_PGUP,  KC_DEL,   KC_NO,    KC_NO,      KC_LBRC,  KC_RBRC,KC_ENTER,   KC_DEL,  KC_END,  KC_PGDN,    KC_NO,      KC_NO,      KC_NO,      KC_PPLS,
    KC_NO,  KC_NO,    KC_TRNS,  KC_NO,  KC_AUDIO_VOL_DOWN,    KC_AUDIO_VOL_UP,      KC_AUDIO_MUTE,        KC_NO,    KC_LEFT,  KC_DOWN,  KC_UP,    KC_RIGHT, KC_SCOLON,  KC_QUOT,  KC_BSLS,                     KC_UP,               LSFT(KC_E), LSFT(KC_F), KC_NO,      KC_BSPC,
    KC_NO,  KC_LALT,  KC_LSHIFT,KC_NO,  KC_NO,                KC_NO,                KC_NO,                KC_NO,    KC_NO,    KC_NO,    KC_PGDN,  KC_COMMA, KC_DOT,     KC_SLSH,  KC_RSFT,            KC_LEFT, KC_WH_D, KC_RIGHT,   LSFT(KC_B), LSFT(KC_C), LSFT(KC_D), KC_PENT,
    KC_NO,  KC_NO,    KC_LCTRL, KC_LGUI,                                                                            KC_SPC,                                 KC_RALT,    KC_CAPS,                               KC_DOWN,             LSFT(KC_A),             KC_PDOT
  ),

  // Literally just the numpad is different
  [4] = LAYOUT(
                          KC_F13,   KC_F14,   KC_F15,       KC_F16,   KC_F17,   KC_F18,   KC_F19,   KC_F20,       KC_F21,   KC_F22,   KC_F23,       KC_F24,
                          KC_F1,    KC_F2,    KC_F3,        KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,        KC_F9,    KC_F10,   KC_F11,       KC_F12,
  KC_ESC,     TO(1),      DVP_ESC,  DVP_AMPR, DVP_LBRACKET, DVP_LCBR, DVP_RCBR, DVP_LPRN, DVP_EQUAL,DVP_ASTERISK, DVP_RPRN, DVP_PLUS, DVP_RBRACKET, DVP_EXLM, DVP_HASH, KC_BSPC,    KC_INS,  KC_HOME, KC_PGUP,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
  KC_NO,      TO(2),      KC_TAB,   KC_SCOLON,KC_COMMA,     KC_DOT,   KC_P,     KC_Y,     KC_F,     KC_G,         KC_C,     KC_R,     KC_L,         KC_SLSH,  DVP_AT,   KC_ENTER,   KC_DEL,  KC_END,  KC_PGDN,    KC_BTN1,  KC_MS_U,  KC_BTN2,  KC_NO,
  KC_NO,      KC_NO,      TO(0),    KC_A,     KC_O,         KC_E,     KC_U,     KC_I,     KC_D,     KC_H,         KC_T,     KC_N,     KC_S,         KC_MINUS, KC_BSLS,                       KC_UP,               KC_MS_L,  KC_NO,    KC_MS_R,  KC_TRNS,
  LCTL(KC_F), KC_LALT,    KC_LSHIFT,KC_NO,    KC_QUOT,      KC_Q,     KC_J,     KC_K,     KC_X,     KC_B,         KC_M,     KC_W,     KC_V,         KC_Z,     KC_RSFT,              KC_LEFT, KC_BTN3, KC_RIGHT,   KC_GT,    KC_MS_D,  KC_GT,    KC_PENT,
  LCTL(KC_C), LCTL(KC_V), KC_LCTRL, KC_LGUI,                                    KC_SPC,                                                             KC_RALT,  KC_RCTRL,                      KC_DOWN,             KC_BTN1,            KC_PDOT

  ),

  /*
  [4] = LAYOUT(
                      KC_F13,   KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, KC_F21, KC_F22,   KC_F23, KC_F24,
                      KC_F1,    KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10,   KC_F11, KC_F12,
    MU_TOG, TO(0),    KC_DLR,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,     KC_0,   KC_MINUS, KC_EQL, KC_BSPC,    KC_INS,  KC_HOME, KC_PGUP,    KC_NLCK,    KC_PSLS,    KC_PAST,    KC_PMNS,
    MU_MOD, KC_NO,    KC_TAB,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_NO,  KC_LBRC,  KC_RBRC,KC_ENTER,   KC_DEL,  KC_END,  KC_PGDN,    KC_NO,      KC_NO,      KC_NO,      KC_PPLS,
    KC_NO,  KC_NO,    KC_TRNS,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_NO,  KC_QUOT,  KC_BSLS,                     KC_UP,               LSFT(KC_E), LSFT(KC_F), KC_NO,      KC_BSPC,
    KC_NO,  KC_LALT,  KC_LSHIFT,KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_COMMA, KC_DOT, KC_SLSH,  KC_RSFT,            KC_LEFT, KC_WH_D, KC_RIGHT,   LSFT(KC_B), LSFT(KC_C), LSFT(KC_D), KC_PENT,
    KC_NO,  KC_LGUI,  KC_LCTRL, KC_LALT,                                                  KC_SPC,                 KC_RALT,  KC_RCTRL,                    KC_DOWN,             LSFT(KC_A),             KC_PDOT

  ),*/
  /*[0] = LAYOUT(
     KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_NO,TO(1),KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1,
     KC_2, KC_2, KC_2, KC_2, KC_2, KC_2, KC_2, KC_2, KC_2, KC_2, KC_2, TO(2),KC_2, KC_2, KC_2, KC_2, KC_2, KC_2, KC_2, KC_2,
     KC_3, KC_3, KC_3, KC_3, KC_3, KC_3, KC_3, KC_3, KC_3, KC_3, KC_3, KC_3, KC_3, KC_3, KC_3, KC_3, KC_3, KC_3, KC_3, KC_3,
     KC_4, KC_4, KC_4, KC_4, KC_4, KC_4, KC_4, KC_4, KC_4, KC_4, KC_4, KC_4, KC_4, KC_4, KC_4, KC_BSPC,KC_4,KC_4,KC_4, KC_4,
     KC_5, KC_5, KC_5, KC_5, KC_5, KC_5, KC_5, KC_5, KC_5, KC_5, KC_5, KC_5, KC_5, KC_5, KC_5, KC_5, KC_5, KC_5, KC_5, KC_5,
     KC_6, KC_6, KC_6, KC_6, KC_6, KC_6, KC_6, KC_6, KC_6, KC_6, KC_6, KC_6, KC_6, KC_6, KC_6, KC_6, KC_6, KC_6, KC_6, KC_6,
     KC_7, KC_7, KC_7, KC_7, KC_7, KC_7, KC_7, KC_7, KC_7, KC_7, KC_7, KC_7, KC_7, KC_7, KC_7, KC_7, KC_7, KC_7, KC_7, KC_7,
     KC_8, KC_SPC,KC_8,KC_8, KC_8, KC_8, KC_8, KC_8, KC_8, KC_8, KC_8, KC_8, KC_8, KC_8, KC_8, KC_8, KC_8, KC_8, KC_8, TO(1)

  ),
  [1] = LAYOUT(
     KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_H, KC_I, KC_J, TO(0),KC_NO,KC_M, KC_N, KC_O, KC_P, KC_Q, KC_R, KC_S, KC_T,
     KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_H, KC_I, KC_J, KC_K, TO(2),KC_M, KC_N, KC_O, KC_P, KC_Q, KC_R, KC_S, KC_T,
     KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_H, KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P, KC_Q, KC_R, KC_S, KC_T,
     KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_H, KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_BSPC,KC_Q,KC_R,KC_S, KC_T,
     KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_H, KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P, KC_Q, KC_R, KC_S, KC_T,
     KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_H, KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P, KC_Q, KC_R, KC_S, KC_T,
     KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_H, KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P, KC_Q, KC_R, KC_S, KC_T,
     KC_A, KC_SPC,KC_C,KC_D, KC_E, KC_F, KC_G, KC_H, KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P, KC_Q, KC_R, KC_S, TO(0)
  ),
  [2] = LAYOUT(
     KC_LCTRL,    KC_LALT,  KC_C,     KC_RALT,    KC_E,       KC_F, KC_G, KC_G, KC_H, KC_J, TO(0),  TO(1),  KC_M,     KC_N,   KC_QUOT,    KC_DOWN,  KC_UP,  KC_R,     KC_S,       KC_ENTER,
     KC_PPLS,     KC_B,     KC_C,     KC_D,       KC_A,       KC_S, KC_D, KC_F, KC_J, KC_J, KC_K,   KC_NO,  KC_K,     KC_L,   KC_SCOLON,  KC_P4,    KC_DEL, KC_P5,    KC_P6,      KC_RIGHT,
     KC_PMNS,     KC_1,     KC_C,    KC_D,       KC_1,       KC_2, KC_3, KC_4, KC_7, KC_J, KC_K,   KC_L,   KC_8,     KC_9,   KC_0,       KC_NLCK,  KC_PGUP,KC_PSLS,  KC_PAST,    KC_T,
     KC_A,        KC_ESC,   TO(0),KC_D,     KC_GRV,     KC_F, KC_G, KC_5, KC_6, KC_J, KC_K,   KC_L,   KC_EQL,   KC_N,   KC_MINUS,   KC_BSPC,  KC_INS, KC_HOME,  KC_S,       KC_T,
     KC_PPLS,     KC_NO,    KC_TAB,   KC_D,       KC_Q,       KC_W, KC_E, KC_R, KC_U, KC_J, KC_K,   KC_L,   KC_I,     KC_O,   KC_P,       KC_P7,    KC_PGDN,KC_P8,    KC_P9,      KC_T,
     KC_A,        KC_B,     KC_C,     KC_D,       KC_E,       KC_F, KC_G, KC_T, KC_Y, KC_J, KC_K,   KC_L,   KC_RBRC,  KC_N,   KC_LBRC,    KC_P,     KC_END, KC_R,     KC_S,       KC_T,
     KC_LEFT,     KC_P1,    KC_CAPS,  KC_RSFT,    KC_Z,       KC_X, KC_C, KC_V, KC_M, KC_J, KC_K,   KC_L,   KC_COMMA, KC_DOT, KC_BSLS,    KC_PENT,  KC_Q,   KC_P2,    KC_P3,      KC_T,
     KC_LGUI,     KC_SPACE, KC_RCTRL, KC_LSHIFT,  KC_E,       KC_F, KC_G, KC_B, KC_N, KC_J, KC_K,   KC_L,   KC_M,     KC_N,   KC_SLSH,    KC_P,     KC_Q,   KC_P0,    KC_PDOT,    KC_KP_ENTER
    ),*/
};

bool left_shift_down = false;
bool right_shift_down = false;

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
        SEND_STRING("$");
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
      return false;
    }
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
      return false;
    }
    else
    {
      if(record->event.pressed)
        SEND_STRING("[");
      return false;
    }
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
      return false;
    }
    else
    {
      if(record->event.pressed)
        SEND_STRING("{");
      return false;
    }
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
      return false;
    }
    else
    {
      if(record->event.pressed)
        SEND_STRING("}");
      return false;
    }
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
    return false;
    }
    else
    {
      if(record->event.pressed)
        SEND_STRING("(");
    return false;
    }
    break;
//
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
    return false;
    }
    else
    {
      if(record->event.pressed)
        SEND_STRING("@");
    return false;
    }
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
    return false;
    }
    else
    {
      if(record->event.pressed)
        SEND_STRING("=");
    return false;
    }
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
    return false;
    }
    else
    {
      if(record->event.pressed)
        SEND_STRING("*");
    return false;
    }
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
    return false;
    }
    else
    {
      if(record->event.pressed)
        SEND_STRING(")");
    return false;
    }
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
     case SHFT_DOT:
      if(record->event.pressed)
        SEND_STRING(">");
      break;

    case SHFT_COMMA:
      if(record->event.pressed)
        SEND_STRING("<");
      break;

  }



  return true;
}

void led_set_user(uint8_t usb_led) {

}
