/*
 * Copyright 2021 milestogo
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
#include "milestogo.h"
#include "user_unicode.h"

//#include "virtser.h"

#ifdef COMBO_ENABLE
#    include "g/keymap_combo.h"
#endif


#define LAYOUT_local LAYOUT_mobile_xua
#define LAYOUT_local_wrap(...) LAYOUT_local(__VA_ARGS__)

// Shorter spacing
#define XXXX KC_NO
#define ____ KC_TRNS

// Custom macros

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*  QWERTY
     *
     * |ESC | F1 | F2 | F3 | F4 | F5 | F6 | f7 | F8 | F9 | F10| F11| F12|Vol-|Vol+|_CDH|
     *  -------------------------------------------------------------------------------'
     * |grv  |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |  0 |  - |  = |Bakspace| Del|
     * ---------------------------------------------------------------------------
     * | tab  |  q |  w |  e |  r |  t |  y |  u |  i |  o |  p |  [ |  ] |  \    |    |
     *  -------------------------------------------------------------------------------'
     * |ESC/Sym|  a |  s |  d |  f |  g |  h |  j |  k |  l |  ; |  ' | enter     |PgUp|
     * --------------------------------------------------------------------------------
     * |Lsft    |  z |  x |  c |  v |  b |  n |  m |  , |  . |  / |      Rsft| Up| PgDn|
     * ---------------------------------------------------------------------------------
     * |Lctl   |Lgui  |Lalt |       Space/Mov       | GUI |  Sym |  Rctl |Left|Down|Rght|
     * ---------------------------------------------------------------------------------
     */

    [_QWERTY] = LAYOUT_local_wrap(\
    KC_ESC,  KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_VOLD, KC_VOLU, TO(_CDH), \
    KC_GRAVE, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_EQL, KC_BSPC, KC_DEL,\
    KC_TAB, _________________QWERTY_L1_________________, _________________QWERTY_R1_________________, KC_LBRC, KC_RBRC, KC_BSLS, \
    ESCSYM, _________________QWERTY_L2_________________, _________________QWERTY_R2_________________, KC_QUOT, KC_ENT, KC_PGUP, \
    KC_LSFT,_________________QWERTY_L3_________________, _________________QWERTY_R3_________________, KC_RSFT, KC_UP, KC_PGDN, \
    KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RGUI, TT(_MOV), KC_RCTL, KC_LEFT, KC_DOWN, KC_RIGHT
    ),

    [_CDH] = LAYOUT_local_wrap(\
    ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, TO(_QWERTY), \
    ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____,\
    ____, ______________COLEMAK_MOD_DH_L1____________, ______________COLEMAK_MOD_DH_R1____________, ____, ____, ____, \
    ____, ______________COLEMAK_MOD_DH_L2____________, ______________COLEMAK_MOD_DH_R2____________, ____, ____, ____, \
    ____, ______________COLEMAK_MOD_DH_L3____________, ______________COLEMAK_MOD_DH_R3____________, ____, ____, ____, \
    B_2ME, B_1ME, ____, SMOVE, ____, ____, ____, ____, ____, ____
    ),

    [_MOV] = LAYOUT_local_wrap(\
    ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, VRSN, ____, REBOOT, \
    ____, __________50_______MOV_L1__________________, __________50_______MOV_R1__________________, ____, ____, ____,\
    ____, __________50_______MOV_L2__________________, __________50_______MOV_R2__________________, ____, ____, \
    ____, __________50_______MOV_L3__________________, __________50_______MOV_R3__________________, ____, ____, \
    ____, __________50_______MOV_L4__________________, __________50_______MOV_R4__________________, ____, ____, \
    B_2ME, B_1ME, ____, ____, ____, ____, ____, ____, ____, ____
    ),

    [_SYM] = LAYOUT_local_wrap(\
    ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, \
    ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____,\
    ____, __________50_______SYM_L1__________________, __________50_______SYM_R1__________________, ____, ____, ____, \
    ____, __________50_______SYM_L2__________________, __________50_______SYM_R2__________________, ____, ____, ____, \
    ____, __________50_______SYM_L3__________________, __________50_______SYM_R3__________________, ____, ____, ____, \
    ____, ____, ____, ____, ____, ____, ____, ____, ____, ____
    ),


    [_NUM] = LAYOUT_local_wrap(\
    ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, \
    ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____,\
    ____, ________________30_NUM_L1__________________, ________________30_NUM_R1__________________, ____, ____, ____, \
    ____, ________________30_NUM_L2__________________, ________________30_NUM_R2__________________, KC_GRV, ____, ____, \
    ____, ________________30_NUM_L3__________________, ________________30_NUM_R3__________________, ____, ____, ____, \
    ____, ____, ____, ____, ____, ____, ____, ____, ____, ____
    ),

    /*
    [_TRAN] = LAYOUT_local(\
      ____,     ____, ____, ____, ____, ____, ____, ____, ____,   ____, ____,    ____,     ____,   ____,    ____,     ____,  \
      ____,     ____, ____, ____, ____, ____,      ____, ____, ____, ____, ____,    ____, ____,   ____, ____,   \
      ____,     ____, ____, ____, ____, ____,      ____, ____, ____, ____, ____,    ____, ____,   ____, \
      ____,     ____, ____, ____, ____, ____,      ____, ____, ____, ____, ____,    ____, ____,   ____, \
      ____,     ____, ____, ____, ____, ____,      ____, ____, ____, ____, ____,    ____, ____,   ____, \
      ____,     ____, ____, ____, ____, ____,      ____, ____, ____, ____
    )
    */
};





void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    // debug_enable=true;
    // debug_matrix=true;
    // debug_keyboard=true;
    // debug_mouse=true;
}

void matrix_init_kb(void) {
#ifdef RGBLIGHT_ENABLE
#    ifdef RGB_DI_PIN
    rgblight_setrgb(RGB_RED);
#    endif
#endif  // RGB_matrix
}

// Assign indicators to LEDs
#define LED_LAYER 2   // layer: raise/Lower
#define LED_LAYOUT 1  // qwerty , colemak, dv
#define LED_CAPS 4    // caps on/off
#define LED_MACRO 0   // babble os indicator: windows/chrome/mac/linux


// Runs whenever there is a layer state change.
layer_state_t layer_state_set_kb(layer_state_t state) {
#ifdef RGBLIGHT_ENABLE
    rgblight_init();
    //// keyboard layout modes

    if (layer_state_cmp(state, _CDH)) {
#    ifdef RGBLIGHT_COLOR_LAYER_1
        rgblight_setrgb_at(RGBLIGHT_COLOR_LAYER_1, LED_LAYOUT);
#    endif
    }
    if (layer_state_cmp(state, _QWERTY)) {
#    ifdef RGBLIGHT_COLOR_LAYER_0
        rgblight_setrgb_at(RGBLIGHT_COLOR_LAYER_0, LED_LAYOUT);

#    endif
    }

    uint8_t layer = get_highest_layer(state);
    switch (layer) {
        case _MOV:
#    ifdef RGBLIGHT_COLOR_LAYER_2
            rgblight_setrgb_at(COLOR_MOV, LED_LAYER);
#    endif
            break;

        case _DMOV:
#    ifdef RGBLIGHT_COLOR_LAYER_3
            rgblight_setrgb_at(COLOR_DMOV, LED_LAYER);
#    endif
            break;

        case _SYM:
#    ifdef RGBLIGHT_COLOR_LAYER_4
            rgblight_setrgb_at(COLOR_SYM, LED_LAYER);
#    endif
            break;

        case _NUM:
#    ifdef RGBLIGHT_COLOR_LAYER_5
            rgblight_setrgb_at(COLOR_NUM, LED_LAYER);
#    endif
            break;

        default:
            rgblight_setrgb_at(RGBLIGHT_OFF, LED_LAYER);
            break;
    }
#endif  // RGB

#ifdef VIRTSER_ENABLE
        // virtser_send(layer + 48); // ascii 0 is 48
#endif

    return state;
};


#ifdef VIRTSER_ENABLE
/* listen on serial for commands. Either a set of lower case letters mapped to colors,
/  or upper case letters that change RGB mode.
/  special command C takes 3 numbers as arguments, terminated with a newline or comma or excess digits.
Command C takes 3-5octets of RGB settings. Numbers can be terminated with a comma or period.
3 octets = set all LED, 4th argument specfies specfic LED, 4+5 specify start and stop LEDs.
*/

uint8_t ser_rgbByte[18];       // ascii string
uint8_t ser_cmd_started  = 0;  // are we in process
uint8_t ser_got_RGBbytes = 0;  // how many bytes we've recived.
uint8_t rgb_r[6];              // R, g, b, P1, p2
uint8_t bs = 0;                // how many bytes into our rgbBytestring.

void virtser_recv(uint8_t serIn) {
#    ifdef RGBLIGHT_ENABLE
    if ((serIn == 10) || (serIn == 13) || ser_got_RGBbytes >= 5) {  // reached newline or max digits

        if (ser_cmd_started) {
            ser_cmd_started = 0;  // end loop at newline
            virtser_send('|');

            if (ser_got_RGBbytes == 3) {
                rgblight_setrgb(rgb_r[0], rgb_r[1], rgb_r[2]);
            }

            if (ser_got_RGBbytes == 4) {
                if ((rgb_r[3] >= 0) && (rgb_r[3] <= RGBLED_NUM)) {  // is pos1 plausible
                    rgblight_setrgb_at(rgb_r[0], rgb_r[1], rgb_r[2], rgb_r[3]);
                } else {
                    rgblight_setrgb(rgb_r[0], rgb_r[1], rgb_r[2]);
                }
            }

            if (ser_got_RGBbytes == 5) {  // are start and end positions plausible?
                if ((rgb_r[4] > 0) && (rgb_r[4] <= RGBLED_NUM) && (rgb_r[4] > rgb_r[3]) && (rgb_r[3] >= 0) && (rgb_r[3] <= (RGBLED_NUM - 1))) {
                    rgblight_setrgb_range(rgb_r[0], rgb_r[1], rgb_r[2], rgb_r[3], rgb_r[4]);
                } else {
                    rgblight_setrgb(rgb_r[0], rgb_r[1], rgb_r[2]);
                }
            }
        } else {  // newline outside of command loop, or something that can be ignored.
                  // virtser_send('.');
        }
    }

    if (1 == ser_cmd_started) {                                  // collecting bytes.
        if (                                                     // it is time to compute a byte
            (((serIn == ',') || (serIn == '.')) && (bs > 0)) ||  // signal done with the byte.
            (bs == 2)) {                                         // or we know this is last.

            if ((serIn <= '9') && (serIn >= '0')) {  // 3rd asci digit
                ser_rgbByte[bs] = serIn;
                bs++;
                //  virtser_send(serIn);
            }

            if (bs > 3) {
                rgb_r[ser_got_RGBbytes] = 255;
                ser_got_RGBbytes++;
            }
            if (bs == 3) {
                rgb_r[ser_got_RGBbytes] = (ser_rgbByte[0] - '0') * 100 + (ser_rgbByte[1] - '0') * 10 + (ser_rgbByte[2] - '0');
                ser_got_RGBbytes++;
            }
            if (bs == 2) {
                rgb_r[ser_got_RGBbytes] = (ser_rgbByte[0] - '0') * 10 + (ser_rgbByte[1] - '0');
                ser_got_RGBbytes++;
            }
            if (bs == 1) {
                rgb_r[ser_got_RGBbytes] = (ser_rgbByte[0] - '0');
                ser_got_RGBbytes++;
            }  // {else wipe & start over}

            bs = 0;
            //  virtser_send(ser_got_RGBbytes+'0');

        } else {                                     // haven't got enough for our byte / no terminal marker
            if ((serIn <= '9') && (serIn >= '0')) {  // ascii only
                ser_rgbByte[bs] = serIn;
                bs++;
                //    virtser_send(serIn);
            }
        }
    } else {  // not in command loop - next is command w/o arguments, or start of one.
        switch (serIn) {
            case 'C':  // color switch
                ser_cmd_started  = 1;
                ser_got_RGBbytes = bs = 0;
                virtser_send('/');
                break;

            case 'r':  // red
                rgblight_setrgb(RGB_RED);
                break;

            case 'g':
                rgblight_setrgb(RGB_GREEN);
                break;

            case 'b':  // color switch
                rgblight_setrgb(RGB_BLUE);
                break;

            case 'w':  // color switch
                rgblight_setrgb(RGB_WHITE);
                break;

            case 'o':  // color black/off
                rgblight_setrgb(0, 0, 0);
                break;

            case 'T':  // toggle
                rgblight_toggle();
                break;

            case 'P':  // pulse led
                rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING);
                break;
            case 'S':  // Static
                rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
                break;

            case 'U':  // Rainbow
                rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_MOOD);
                break;

            default:
                //     virtser_send(serIn);
                break;
        }
    }
#    endif  // RGBLIGHT_ENABLE
}

#endif  // VirtSerial
