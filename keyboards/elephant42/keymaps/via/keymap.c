/* Copyright 2021 illness072
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

#define KC_VU KC_AUDIO_VOL_UP
#define KC_VD KC_AUDIO_VOL_DOWN
#define KC_MU KC_AUDIO_MUTE
#define KC_LWSP LT(_LOWER, KC_SPC)
#define KC_RSSP LT(_RAISE, KC_SPC)

enum layer_names {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,

    NUMBER_OF_LAYERS
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( \
  //,-------+-------+-------+-------+-------+-------.                                    ,-------+-------+-------+-------+-------+-------.
     KC_TAB , KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,                                      KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,KC_BSLS,
  //|-------+-------+-------+-------+-------+-------|                                    |-------+-------+-------+-------+-------+-------|
     KC_LCTL, KC_A  , KC_S  , KC_D  , KC_F  , KC_G  ,                                      KC_H  , KC_J  , KC_K  , KC_L  ,KC_SCLN,KC_QUOT,
  //`-------+-------+-------+-------+-------+-------|                                    |-------+-------+-------+-------+-------+-------'
              KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,                                      KC_N  , KC_M  ,KC_COMM,KC_DOT ,KC_SLSH,
  //        `-------+-------+-------+-------+-------+-------+-------.    ,-------+-------+-------+-------+-------+-------+-------'
                                     KC_LALT,KC_LCMD,KC_LWSP,KC_LSFT,     KC_DEL ,KC_RSSP,KC_ENT ,KC_BSPC
  //                                `-------+-------+-------+-------'    `-------+-------+-------+-------'
  ),

  [_LOWER] = LAYOUT(
  //,-------+-------+-------+-------+-------+-------.                                    ,-------+-------+-------+-------+-------+-------.
     KC_ESC , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                                      KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_TILD,
  //|-------+-------+-------+-------+-------+-------|                                    |-------+-------+-------+-------+-------+-------|
     KC_LCTL,KC_EXLM,KC_AT  ,KC_HASH,KC_DLR ,KC_PERC,                                     KC_CIRC,KC_AMPR,KC_ASTR,KC_MINS,KC_PLUS,KC_GRV,
  //`-------+-------+-------+-------+-------+-------|                                    |-------+-------+-------+-------+-------+-------|
             XXXXXXX,XXXXXXX,KC_LCBR,KC_LBRC,KC_LPRN,                                     KC_RPRN,KC_RBRC,KC_RCBR,KC_UNDS,KC_EQL ,
  //        `-------+-------+-------+-------+-------+-------+-------.    ,-------+-------+-------+-------+-------+-------+-------'
                                     KC_LALT,KC_LCMD,KC_LWSP,KC_LSFT,     KC_DEL ,KC_RSSP,KC_ENT ,KC_BSPC
  //                                `-------+-------+-------+-------'    `-------+-------+-------+-------'
  ),

  [_RAISE] = LAYOUT(
  //,-------+-------+-------+-------+-------+-------.                                    ,-------+-------+-------+-------+-------+-------.
     KC_ESC , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,                                      KC_F6 , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,
  //|-------+-------+-------+-------+-------+-------|                                    |-------+-------+-------+-------+-------+-------|
     KC_LCTL, KC_VD , KC_VU , KC_MU ,RGB_HUI,RGB_VAI,                                     KC_LEFT,KC_DOWN, KC_UP ,KC_RGHT,XXXXXXX,KC_F12 ,
  //`-------+-------+-------+-------+-------+-------|                                    |-------+-------+-------+-------+-------+-------'
             KC_BRMD,KC_BRMU,RGB_TOG,RGB_MOD,RGB_VAD,                                     KC_HOME,KC_PGDN,KC_PGUP,KC_END ,XXXXXXX,
  //        `-------+-------+-------+-------+-------+-------+-------.    ,-------+-------+-------+-------+-------+-------+-------'
                                     KC_LALT,KC_LCMD,KC_LWSP,KC_LSFT,     KC_DEL ,KC_RSSP,KC_ENT ,KC_BSPC
  //                                `-------+-------+-------+-------'    `-------+-------+-------+-------'
  ),

  [_ADJUST] = LAYOUT(
  //,-------+-------+-------+-------+-------+-------.                                    ,-------+-------+-------+-------+-------+-------.
     XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                                     XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
  //|-------+-------+-------+-------+-------+-------|                                    |-------+-------+-------+-------+-------+-------|
     XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                                     XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
  //`-------+-------+-------+-------+-------+-------|                                    |-------+-------+-------+-------+-------+-------'
             XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                                     XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
  //        `-------+-------+-------+-------+-------+-------+-------.    ,-------+-------+-------+-------+-------+-------+-------'
                                     XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,     XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX
  //                                `-------+-------+-------+-------'    `-------+-------+-------+-------'
  )
};


#ifdef OLED_ENABLE
#   define STEPS 32

uint8_t keypresses = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        keypresses = (keypresses + 1) % STEPS;
    }
    return true;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        static char layer_names[NUMBER_OF_LAYERS][10] = {"Default", "Lower", "Raise", "Adjust"};
        static char l1[] = "                \x94\x95\x96\x97";
        static char l2[] = "                \xB4\xB5\xB6\xB7";
        static char r1[] = "                \x98\x99\x9A\x9B";
        static char r2[] = "                \xB8\xB9\xBA\xBB";
        int iconShift = keypresses % STEPS;
        if (iconShift > STEPS / 2) {
            iconShift = STEPS - iconShift;
        }
        bool goingLeft = keypresses < STEPS / 2;

        oled_write_P(PSTR("Layer: "), false);
        oled_write_ln(layer_names[get_highest_layer(layer_state)], false);
        oled_advance_page(true);
        oled_write_ln((goingLeft ? l1 : r1) + iconShift, false);
        oled_write_ln((goingLeft ? l2 : r2) + iconShift, false);
    } else {
        oled_advance_page(true);
        static const char PROGMEM logo[] = {
            0x8f,0x90,0x91,0x92,0x93,0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x0a,
            0xaf,0xb0,0xb1,0xb2,0xb3,0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0x0a,
            0xcf,0xd0,0xd1,0xd2,0xd3,0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0
        };

        oled_write_ln_P(logo, false);
    }

    return false;
}
#endif
