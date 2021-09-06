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

#ifdef OLED_ENABLE
#   include <stdio.h>
#   include <string.h>
#endif

#define KC_VU KC__VOLUP
#define KC_VD KC__VOLDOWN
#define KC_MU KC__MUTE
#define KC_LSPC LT(_LOWER, KC_SPC)
#define KC_RSPC LT(_RAISE, KC_SPC)

enum layer_names {
    _QWERTY,
    _LOWER,
    _RAISE,

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
                                     KC_LALT,KC_LCMD,KC_LSPC,KC_LSFT,     KC_DEL ,KC_RSPC,KC_ENT ,KC_BSPC
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
                                     KC_LALT,KC_LCMD,KC_LSPC,KC_LSFT,     KC_DEL ,KC_RSPC,KC_ENT ,KC_BSPC
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
                                     KC_LALT,KC_LCMD,KC_LSPC,KC_LSFT,     KC_DEL ,KC_RSPC,KC_ENT ,KC_BSPC
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

void oled_task_user(void) {
    if (is_keyboard_master()) {
        char disp[21 * 4];
        static char layer_names[NUMBER_OF_LAYERS][10] = {"Default", "Lower", "Raise"};
        static char l1[] = "                \x94\x95\x96\x97";
        static char l2[] = "                \xB4\xB5\xB6\xB7";
        static char r1[] = "                \x98\x99\x9A\x9B";
        static char r2[] = "                \xB8\xB9\xBA\xBB";
        int iconShift = keypresses % STEPS;
        if (iconShift > STEPS / 2) {
            iconShift = STEPS - iconShift;
        }
        bool goingLeft = keypresses < STEPS / 2;

        strcpy(disp, "Layer: ");
        strcat(disp, layer_names[get_highest_layer(layer_state)]);
        strcat(disp, "\n\n");
        strcat(disp, (goingLeft ? l1 : r1) + iconShift);
        strcat(disp, "\n");
        strcat(disp, (goingLeft ? l2 : r2) + iconShift);
        strcat(disp, "\n");

        oled_write(disp, false);
    } else {
        static char *logo = "\n"
        "\x8f\x90\x91\x92\x93\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\n"
        "\xaf\xb0\xb1\xb2\xb3\xa0\xa1\xa2\xa3\xa4\xa5\xa6\xa7\xa8\xa9\xaa\xab\xac\xad\xae\n"
        "\xcf\xd0\xd1\xd2\xd3\xc0\xc1\xc2\xc3\xc4\xc5\xc6\xc7\xc8\xc9\xca\xcb\xcc\xcd\xce\n";
        oled_write(logo, false);
    }
}
#endif
