#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "keymap_swiss_fr.h"
#include "keymap_french.h"
#include "keymap_german.h"
#include "keymap_swiss_de.h"
#include "keymap_nordic.h"
#include "keymap_norwegian.h"
#include "keymap_spanish.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


[0] = LAYOUT_ergodox(NO_LABK,KC_1,KC_2,KC_3,KC_4,KC_5,KC_BSPACE,KC_TAB,KC_Q,KC_W,KC_E,KC_R,KC_T,TG(1),KC_BSPACE,KC_A,KC_S,KC_D,KC_F,KC_G,SFT_T(NO_QUOT),CTL_T(KC_Z),KC_X,KC_C,KC_V,KC_B,SFT_T(KC_EQUAL),MO(1),CTL_T(KC_GRAVE),KC_LGUI,KC_LEFT,KC_RIGHT,KC_ESCAPE,KC_CAPSLOCK,KC_HOME,KC_SPACE,KC_LGUI,KC_LALT,KC_DELETE,KC_6,KC_7,KC_8,KC_9,KC_0,NO_PLUS,TG(1),KC_Y,KC_U,KC_I,KC_O,KC_P,NO_ARNG,KC_H,KC_J,KC_K,KC_L,LT(2,NO_OSTR),NO_AE,SFT_T(KC_RBRC),KC_N,KC_M,KC_COMMA,KC_DOT,CTL_T(KC_SLASH),SFT_T(NO_QUOT),KC_DOWN,KC_UP,NO_LPRN,NO_RPRN,MO(1),NO_QUOT,CTL_T(KC_ESCAPE),NO_QUOT,KC_LALT,KC_LGUI,KC_ENTER),

[1] = LAYOUT_ergodox(M(0),KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,KC_BSPACE,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_BSPACE,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_LSHIFT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_LCTL,KC_LGUI,KC_LEFT,KC_RIGHT,KC_ESCAPE,KC_TRANSPARENT,KC_HOME,KC_SPACE,KC_LGUI,KC_LALT,KC_DELETE,KC_F6,KC_F7,KC_F8,KC_F9,KC_F10,KC_F11,KC_TRANSPARENT,KC_7,KC_8,KC_9,KC_TRANSPARENT,KC_TRANSPARENT,KC_F12,KC_4,KC_5,KC_6,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_0,KC_1,KC_2,KC_3,NO_LBRC,NO_RBRC,KC_LSHIFT,KC_COMMA,KC_DOT,LSFT(NO_LBRC),LSFT(NO_RBRC),KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_LALT,KC_LGUI,KC_ENTER),

[2] = LAYOUT_ergodox(KC_ESCAPE,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_MS_UP,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_MS_LEFT,KC_MS_DOWN,KC_MS_RIGHT,KC_TRANSPARENT,KC_LSHIFT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_LCTL,KC_LALT,KC_LGUI,KC_MS_BTN1,KC_MS_BTN2,KC_ESCAPE,KC_TRANSPARENT,KC_TRANSPARENT,KC_SPACE,KC_LGUI,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_MEDIA_PREV_TRACK,KC_MEDIA_PLAY_PAUSE,KC_MEDIA_NEXT_TRACK,KC_TRANSPARENT,KC_TRANSPARENT,KC_AUDIO_VOL_UP,KC_AUDIO_VOL_DOWN,KC_AUDIO_MUTE,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_ESCAPE,KC_MS_WH_UP,KC_MS_WH_DOWN,KC_MS_ACCEL0,KC_MS_ACCEL1),

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
      }
    return MACRO_NONE;
};

void matrix_scan_user(void) {

    uint8_t layer = get_highest_layer(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
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
            ergodox_right_led_2_on();
            break;
        case 5:
            ergodox_right_led_1_on();
            ergodox_right_led_3_on();
            break;
        case 6:
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        case 7:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        default:
            break;
    }

};
