// USING_MIDI
// USING_BACKLIGHT
#include "keymap_common.h"
#ifdef BACKLIGHT_ENABLE
  #include "backlight.h"
#endif
#include "action_layer.h"
#include "keymap_midi.h"
#include "audio.h"
#include <avr/boot.h>

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = { /* Qwerty */
  {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,   KC_BSPC},
  {KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT},
  {M(0), KC_LCTL, KC_LALT, KC_LGUI, FUNC(2),    KC_SPC,   KC_SPC,    FUNC(1),   KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT}
                                                // Space is repeated to accommadate for both spacebar wiring positions
},
[1] = { /* Colemak */
  {KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC},
  {KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,     KC_QUOT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT},
  {KC_FN3, KC_LCTL, KC_LALT, KC_LGUI, FUNC(2),    KC_SPC,   KC_SPC,    FUNC(1),   KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT}
},
[2] = { /* RAISE */
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC},
  {KC_TRNS, FUNC(3), FUNC(4), RESET, KC_TRNS, KC_TRNS, KC_TRNS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS},
  {KC_TRNS, KC_F11,  KC_F12,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS},
  {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,   KC_TRNS,  FUNC(1),   KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
},
[3] = { /* LOWER */
  {S(KC_GRV),  S(KC_1),    S(KC_2),    S(KC_3),    S(KC_4),    S(KC_5),    S(KC_6),    S(KC_7),    S(KC_8),    S(KC_9),    S(KC_0), KC_BSPC},
  {KC_TRNS, FUNC(3), FUNC(4), RESET, KC_TRNS, KC_TRNS, KC_TRNS, S(KC_MINS), S(KC_EQL),  S(KC_LBRC), S(KC_RBRC), S(KC_BSLS)},
  {KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_TRNS},
  {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, FUNC(2),   KC_TRNS,   KC_TRNS,   KC_TRNS, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
},
[4] = { /* TENKEY */
  {KC_TAB,  N_C5, N_D5, N_E5, N_F5, N_G5, N_A5,    KC_KP_7,    KC_KP_8,    KC_KP_9,    KC_P,   KC_BSPC},
  {KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_KP_4,    KC_KP_5,    KC_KP_6,    KC_SCLN,  KC_QUOT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_KP_1,    KC_KP_2,    KC_KP_3,  KC_SLSH, KC_ENT},
  {KC_TRNS, KC_LCTL, KC_LALT, KC_LGUI, KC_TRNS,    KC_SPC,   KC_SPC, KC_KP_0,   KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT}
},
[5] = {
  { MIDI12 },
  { MIDI12 },
  { MIDI12 },
  {M(0), KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,    KC_SPC,   KC_SPC,    FUNC(1),   MIDI, MIDI, MIDI,  MIDI}
}
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_MOMENTARY(2),  // to RAISE
    [2] = ACTION_LAYER_MOMENTARY(3),  // to LOWER

    [3] = ACTION_DEFAULT_LAYER_SET(0),
    [4] = ACTION_DEFAULT_LAYER_SET(1),

};

uint16_t hextokeycode(int hex) {
    if (hex == 0x0) {
        return KC_0;
    } else if (hex < 0xA) {
        return KC_1 + (hex - 0x1);
    } else {
        return KC_A + (hex - 0xA);
    }
}

float walk_up[][2] = {
  {440.0*pow(2.0,(60)/12.0), 400},
  {0, 50},
  {440.0*pow(2.0,(67)/12.0), 600},
};

float walk_dn[][2] = {
  {440.0*pow(2.0,(67)/12.0), 400},
  {0, 50},
  {440.0*pow(2.0,(60)/12.0), 600},
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) 
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:   
        if (record->event.pressed) {

          play_notes(&walk_up, 3, false);
          // play_note(440, 20);
          // register_code(KC_RSFT);
          #ifdef BACKLIGHT_ENABLE
            backlight_set(BACKLIGHT_LEVELS);
          #endif
          default_layer_and(0); 
          default_layer_or((1<<5));

          // uint8_t low = boot_lock_fuse_bits_get(0x0000);
          // uint8_t high = boot_lock_fuse_bits_get(0x0003);
          // uint8_t ext = boot_lock_fuse_bits_get(0x0002);
          // uint8_t lock = boot_lock_fuse_bits_get(0x0001);

          // register_code(hextokeycode((low & 0xF0) >> 4));
          // unregister_code(hextokeycode((low & 0xF0) >> 4));
          // register_code(hextokeycode((low & 0x0F)));
          // unregister_code(hextokeycode((low & 0x0F)));


          // register_code(hextokeycode((high & 0xF0) >> 4));
          // unregister_code(hextokeycode((high & 0xF0) >> 4));
          // register_code(hextokeycode((high & 0x0F)));
          // unregister_code(hextokeycode((high & 0x0F)));


          // register_code(hextokeycode((ext & 0xF0) >> 4));
          // unregister_code(hextokeycode((ext & 0xF0) >> 4));
          // register_code(hextokeycode((ext & 0x0F)));
          // unregister_code(hextokeycode((ext & 0x0F)));


          // register_code(hextokeycode((lock & 0xF0) >> 4));
          // unregister_code(hextokeycode((lock & 0xF0) >> 4));
          // register_code(hextokeycode((lock & 0x0F)));
          // unregister_code(hextokeycode((lock & 0x0F)));

        } else {
          unregister_code(KC_RSFT);
          play_notes(&walk_dn, 3, false);
          #ifdef BACKLIGHT_ENABLE
            backlight_set(0);
          #endif
          default_layer_and(0); 
          default_layer_or(0);
        }
        break;
      } 
    return MACRO_NONE;
};

float start_up[][2] = {
  {440.0*pow(2.0,(67)/12.0), 600},
  {0, 50},
  {440.0*pow(2.0,(64)/12.0), 400},
  {0, 50},
  {440.0*pow(2.0,(55)/12.0), 400},
  {0, 50},
  {440.0*pow(2.0,(60)/12.0), 400},
  {0, 50},
  {440.0*pow(2.0,(64)/12.0), 1000},
};

void * matrix_init_user(void) {
    init_notes();
    play_notes(&start_up, 9, false);
}