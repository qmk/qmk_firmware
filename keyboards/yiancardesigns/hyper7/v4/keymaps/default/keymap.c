/* Copyright 2023 Yiancar-Designs, Bit-Shifter
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

enum my_keycodes {
    MACRO = QK_USER_0,
    QUOTE,
    CLRIN,
    SQUAR,
    CIRCL,
    TRIAN,
    DIAMO,
    WRITE,
    TTY,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case MACRO:
        if (record->event.pressed) {
            // when keycode MACRO is pressed
            SEND_STRING("Hyper7 is the best thing ever!");
        } else {
            // when keycode MACRO is released
        }
        break;
    case QUOTE:
        if (record->event.pressed) {
            // when keycode QUOTE is pressed
            SEND_STRING("\"\"" SS_TAP(X_LEFT));
        } else {
            // when keycode QUOTE is released
        }
        break;
    case CLRIN:
        if (record->event.pressed) {
            // when keycode CLRIN is pressed
            SEND_STRING(SS_LCTL("a") SS_TAP(X_DEL));
        } else {
            // when keycode CLRIN is released
        }
        break;
    case SQUAR:
        if (record->event.pressed) {
            // when keycode SQUAR is pressed
            SEND_STRING("I like squares");
        } else {
            // when keycode SQUAR is released
        }
        break;
    case CIRCL:
        if (record->event.pressed) {
            // when keycode CIRCL is pressed
            SEND_STRING("I like circles");
        } else {
            // when keycode CIRCL is released
        }
        break;
    case TRIAN:
        if (record->event.pressed) {
            // when keycode TRIAN is pressed
            SEND_STRING("I like the illuminati");
        } else {
            // when keycode TRIAN is released
        }
        break;
    case DIAMO:
        if (record->event.pressed) {
            // when keycode DIAMO is pressed
            SEND_STRING("Everyone likes diamonds");
        } else {
            // when keycode DIAMO is released
        }
        break;
    case WRITE:
        if (record->event.pressed) {
            // when keycode WRITE is pressed
            SEND_STRING(SS_LGUI("x") "notepad" SS_TAP(X_ENT));
        } else {
            // when keycode WRITE is released
        }
        break;
    case TTY:
        if (record->event.pressed) {
            // when keycode TTY is pressed
            SEND_STRING(SS_LGUI("x") "cmd" SS_TAP(X_ENT));
        } else {
            // when keycode TTY is released
        }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* _BASE: Base Layer(Default)
     * ,---------------------------------------------------------------------------------------------------------------------------------------------------------------------------.
     * |   Help    |   Macro   |#| Terminal  |   Quote   | OverStrike| ClearInput|ClearScreen|HoldOutput | StopOutput|   Abort   |   Break   |  Resume   |#|   Call    |   RESET   |
     * |---------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |   Local   |  Network  |#|  System   |  Refresh  |   Buffer  |   Square  |   Circle  | Triangle  |  Diamond  |   Repeat  |  Transmit |  Status   |#|  Suspend  |  CapsLock |
     * |---------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * | F1  | F2  |Close|Open |#|   Esc     |  ?  |  !  |  @  |  £  |  €  |  ¥  |  '  |  “  |  ”  |  '  |  _  |  <  |  >  |  |  |  {  |  }  | Complete  |#|  ^  |  %  |  #  |  $  |
     * |---------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * |##########################################################################################################################################################################|
     * |---------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * | F3  | F4  |Find |Write|#|Compose | "/± | :/~ |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |  |  | {/‹  | }/›  | Undo |#|  ~  |  /  |  *  |  -  |
     * |---------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * | F5  | F6  |Mark |Undo |#|Paste|  Cut   |Tab     |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  (  |  )  | Bspace | Clear  |Begin|#|  7  |  8  |  9  |  +  |
     * |---------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * | F7  | F8  |Selec|Debug|#|Function|  Mode  |  Top   |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  | Return |  Line  |  Page  |#|  4  |  5  |  6  |  &  |
     * |---------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * | F9  | F10 | TTY |LOCK |#|Begin| End | Symbol | Shift  |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  | Shift  | Symbol |  Up | End |#|  1  |  2  |  3  |  =  |
     * |---------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
     * | F11 | F12 |Home | EOF |#|Prev |Next |7bit | Ctrl | Alt  | Spr |  Hyper  | Space |TRNS |  Del   |  Ctrl  | Spr  | Hyper  |Meta |Left |Down |Right|#| Del |  0  |  .  | Run |
     * `---------------------------------------------------------------------------------------------------------------------------------------------------------------------------'
     */
    [0] = LAYOUT(
        LGUI(KC_F1),  KC_NO,    MACRO,        KC_NO,             RCS(KC_ESC),    KC_NO,            QUOTE,          KC_NO,          KC_INS,        KC_NO,    CLRIN,    KC_NO,    LGUI(KC_D),  KC_NO,     LCTL(KC_S),  KC_NO,     LCTL(KC_C),  KC_NO,      LALT(KC_F4),  KC_NO,      KC_PAUS,       KC_NO,      LCTL(KC_P),    KC_NO,        LGUI(LCTL(KC_Q)),  KC_NO,      LCA(KC_DEL),  KC_NO,   //14
        LGUI(KC_X),   KC_NO,    KC_WHOM,      KC_NO,             LGUI(KC_PAUS),  KC_NO,            LCTL(KC_R),     KC_NO,          LALT(KC_TAB),  KC_NO,    SQUAR,    KC_NO,    CIRCL,       KC_NO,     TRIAN,       KC_NO,     DIAMO,       KC_NO,      LCTL(KC_Y),   KC_NO,      LAG(KC_R),     KC_NO,      RCS(KC_ESC),   KC_NO,        LGUI(KC_L),        KC_NO,      KC_CAPS,      KC_NO,   //14
        KC_F1,        KC_F2,    LALT(KC_F4),  LGUI(KC_R),        KC_ESC,         KC_NO,            KC_QUES,        KC_EXLM,        KC_AT,         KC_AT,    KC_AT,    KC_AT,    KC_GRV,      KC_GRV,    KC_GRV,      KC_GRV,    KC_UNDS,     KC_LABK,    KC_RABK,      KC_PIPE,    KC_LCBR,       KC_RCBR,    LCTL(KC_ENT),  KC_NO,        KC_CIRC,           KC_PERC,    KC_HASH,      KC_DLR,  //26

        KC_F3,        KC_F4,     LCTL(KC_F),  WRITE,             LSFT(KC_N),     KC_NO,            KC_TILD,        KC_1,           KC_2,          KC_3,     KC_4,     KC_5,     KC_6,        KC_7,      KC_8,        KC_9,      KC_0,        KC_MINS,    KC_EQL,       KC_NUBS,    KC_LBRC,       KC_RBRC,    LCTL(KC_Z),                  KC_PMNS,           KC_PSLS,    KC_PAST,      KC_PMNS, //27
        KC_F5,        KC_F6,     LCTL(KC_M),  LCTL(KC_Z),                        LCTL(KC_V),       LCTL(KC_X),     KC_TAB,         KC_Q,          KC_W,     KC_E,     KC_R,     KC_T,        KC_Y,      KC_U,        KC_I,      KC_O,        KC_P,       KC_LCBR,      KC_RCBR,    KC_BSPC,       KC_CLEAR,   LCTL(KC_HOME),               KC_P7,             KC_P8,      KC_P9,        KC_PPLS, //26
        KC_F7,        KC_F8,     LCTL(KC_A),  KC_F12,                            MO(1),            KC_NO,          KC_PGUP,        KC_A,          KC_S,     KC_D,     KC_F,     KC_G,        KC_H,      KC_J,        KC_K,      KC_L,        KC_COLN,    KC_QUOT,              KC_ENT ,           KC_HOME,    KC_PGDN,                     KC_P4,             KC_P5,      KC_P6,        KC_AMPR, //25
        KC_F9,        KC_F10,    TTY,         LGUI(KC_L),        LCTL(KC_HOME),  KC_END ,          LGUI(KC_DOT),   KC_LSFT,        KC_Z,          KC_X,     KC_C,     KC_V,     KC_B,        KC_N,      KC_M,        KC_COMM,   KC_DOT,      KC_SLSH,           KC_RSFT,           LGUI(KC_DOT),  KC_UP,      KC_LGUI,                     KC_P1,             KC_P2,      KC_P3,        KC_EQL,  //26
        KC_F11,       KC_F12,    KC_HOME,     LCTL(KC_END),                      LCTL(KC_LEFT),    LCTL(KC_RGHT),  LGUI(KC_DOWN),  KC_LCTL,       KC_LALT,  KC_LGUI,  KC_HYPR,  KC_SPC,           KC_SPC,            KC_DEL,    KC_RCTL,     KC_RGUI,    KC_HYPR,      KC_RALT,    KC_LEFT,       KC_DOWN,    KC_RGHT,                     KC_DEL,            KC_P0,      KC_PDOT,      KC_ENTER,//25
                                                                                                                                                                                                  KC_SPC
    )
};
