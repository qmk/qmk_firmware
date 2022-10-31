#include QMK_KEYBOARD_H

enum layer_names {
    BASE, // default layer
    SYMB, // symbols layer
    MDIA, // media layer
    SPEC, // special layer
    RBASE // reverse default layer
};

/*
 * The Ordinary Layout for the Ergodox EZ keyboard, v5
 *
 * Modifications from the default Ergodox EZ layout
 * by Nicholas Keene ergodoxez@nicholaskeene.com
 *
 * No rights reserved. This software is in the public domain.
 * Credit me if you are friendly but if you're a jerk don't bother.
 * If you use or modify this layout I would love to hear from you.
 *
 * Details: readme.md
 *          https://github.com/nrrkeene/qmk_firmware/tree/master/keyboards/ergodox/keymaps/ordinary
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/******* Base Layer ****************************************************************************************************
 *
 * ,------------------------------------------------------.       ,------------------------------------------------------.
 * | Special `~ |   1  |   2  |   3  |   4  |   5  | ESC  |       |  -   |   6  |   7  |   8  |   9  |   0  | =+ Special |
 * |------------+------+------+------+------+-------------|       |------+------+------+------+------+------+------------|
 * | Media  Tab |   Q  |   W  |   E  |   R  |   T  |Shift |       | Tab  |   Y  |   U  |   I  |   O  |   P  | \|   Media |
 * |------------+------+------+------+------+------|-Tab  |       |      |------+------+------+------+------+------------|
 * | Symbol     |  ^A  |   S  |   D  |  ^F  |   G  |------|       |------|   H  |  ^J  |   K  |   L  |  ^;  | '"  Symbol |
 * |------------+------+------+------+------+------|  [   |       |  ]   |------+------+------+------+------+------------|
 * | Capitals   |   Z  |   X  |   C  |   V  |   B  |      |       |      |   N  |   M  |   ,  |   .  |  /   |   Capitals |
 * `------------+------+------+------+------+-------------'       `-------------+------+------+------+------+------------'
 *      | Left | Right | LCtrl | LAlt | LGui|                                   | RGui | RAlt | RCtrl | Up |  Down  |
 *      `-----------------------------------'                                   `-----------------------------------'
 *                                          ,-------------.       ,-------------.
 *                                          | Home | End  |       | Left | Right|
 *                                   ,------|------|------|       |------+------+------.
 *                                   |      |      | PgUp |       |  Up  |      |      |
 *                                   |Backsp| Del  |------|       |------| Enter| Space|
 *                                   |      |      | PgDn |       | Down |      |      |
 *                                   `--------------------'       `--------------------'
 */
[BASE] = LAYOUT_ergodox(
// left hand
 KC_NO     ,KC_1           ,KC_2   ,KC_3   ,KC_4  ,KC_5  ,KC_ESC
,KC_NO     ,KC_Q           ,KC_W   ,KC_E   ,KC_R  ,KC_T  ,LSFT(KC_TAB)
,KC_NO     ,LT(RBASE, KC_A),KC_S   ,KC_D   ,LT(RBASE, KC_F)  ,KC_G
,KC_LSFT   ,KC_Z           ,KC_X   ,KC_C   ,KC_V  ,KC_B  ,KC_LBRC
,KC_LEFT   ,KC_RIGHT       ,KC_LCTL,KC_LALT,KC_LGUI
                                         ,KC_HOME,KC_END
                                                 ,KC_PGUP
                                 ,KC_BSPC,KC_DEL ,KC_PGDN
                                                                  // right hand
                                                                 ,KC_MINS ,KC_6 ,KC_7           ,KC_8   ,KC_9   ,KC_0             ,KC_NO
                                                                 ,KC_TAB  ,KC_Y ,KC_U           ,KC_I   ,KC_O   ,KC_P             ,KC_NO
                                                                          ,KC_H ,LT(RBASE, KC_J),KC_K   ,KC_L   ,LT(RBASE,KC_SCLN),KC_NO
                                                                 ,KC_RBRC ,KC_N ,KC_M           ,KC_COMM,KC_DOT ,KC_SLSH          ,KC_RSFT
                                                                                ,KC_RGUI        ,KC_RALT,KC_RCTL,KC_UP            ,KC_DOWN
                                                                 ,KC_LEFT ,KC_RGHT
                                                                 ,KC_UP
                                                                 ,KC_DOWN ,KC_ENT ,KC_SPC
),

/******* Symbols Layer *************************************************************************************************
 *
 * ,-----------------------------------------------------.       ,-----------------------------------------------------.
 * |           |  F1  |  F2  |  F3  |  F4  |  F5  | Esc  |       |  -   |  F6  |  F7  |  F8  |  F9  |  F10 |           |
 * |-----------+------+------+------+------+-------------|       |------+------+------+------+------+------+-----------|
 * |           |   !  |   @  |   {  |   }  |   &  |  <   |       |  >   |   |  |   7  |   8  |   9  |   /  |           |
 * |-----------+------+------+------+------+------|      |       |      |------+------+------+------+------+-----------|
 * |           |   #  |   $  |   (  |   )  |   `  |------|       |------|   /  |   4  |   5  |   6  |   *  |           |
 * |-----------+------+------+------+------+------|  '   |       |  "   |------+------+------+------+------+-----------|
 * |           |   %  |   ^  |   [  |   ]  |   ~  |      |       |      |   \  |   1  |   2  |   3  |   -  |           |
 * `-----------+------+------+------+------+-------------'       `-------------+------+------+------+------+-----------'
 *     |   ;   |   &  |   *  |   <  |   >  |                                   |   0  |   .  |   =  |   +  | Enter |
 *     `-----------------------------------'                                   `-----------------------------------'
 *                                         ,-------------.       ,-------------.
 *                                         | |||| | |||| |       | |||| | |||| |
 *                                  ,------|------|------|       |------+------+------.
 *                                  | Plus | Equal| |||| |       | |||| | Under| Dash |
 *                                  |      |      |------|       |------| Score|      |
 *                                  |  +   |   =  |  !=  |       |  ->  |  _   |  -   |
 *                                  `--------------------'       `--------------------'
 */
[SYMB] = LAYOUT_ergodox(
// left hand
 KC_TRNS ,KC_F1       ,KC_F2        ,KC_F3   ,KC_F4   ,KC_F5   ,KC_ESC
,KC_TRNS ,KC_EXLM     ,KC_AT        ,KC_LCBR ,KC_RCBR ,KC_AMPR ,LSFT(KC_COMM)
,KC_TRNS ,KC_HASH     ,KC_DLR       ,KC_LPRN ,KC_RPRN ,KC_GRV
,KC_TRNS ,KC_PERC     ,KC_CIRC      ,KC_LBRC ,KC_RBRC ,KC_TILD ,KC_QUOT
,KC_SCLN ,KC_AMPR     ,KC_ASTR ,LSFT(KC_COMM),LSFT(KC_DOT)
                                                      ,KC_NO,KC_NO
                                                               ,KC_NO
                                             ,KC_PLUS ,KC_EQL  ,KC_NO
                                                                 // right hand
                                                                 ,KC_MINS     ,KC_F6        ,KC_F7 ,KC_F8  ,KC_F9 ,KC_F10  ,KC_TRNS
                                                                 ,LSFT(KC_DOT),KC_PIPE      ,KC_7  ,KC_8   ,KC_9  ,KC_SLSH ,KC_TRNS
                                                                              ,KC_SLSH      ,KC_4  ,KC_5   ,KC_6  ,KC_ASTR ,KC_TRNS
                                                                 ,LSFT(KC_QUOT),KC_BSLS     ,KC_1  ,KC_2   ,KC_3  ,KC_MINS ,KC_TRNS
                                                                                            ,KC_0  ,KC_DOT ,KC_EQL,KC_PLUS ,KC_ENT
                                                                 ,KC_NO       ,KC_NO
                                                                 ,KC_NO
                                                                 ,KC_NO    ,LSFT(KC_MINS),KC_MINS
),

/******* Media Layer *******************************************************************************************************
 *
 * ,---------------------------------------------------------------.    ,---------------------------------------------------------------.
 * |      |   F11   |   F12   |   F13   |   F14   |   F15   | Esc  |    | |||| |   F16   |   F17   |   F18   |   F19   |   F20   |      |
 * |------+---------+---------+---------+---------+----------------|    |------+---------+---------+---------+---------+---------+------|
 * |      |Shut Down|MouseUpLf|Mouse Up |MouseUpRg|Volume Up|Scroll|    |Scroll|PrintScrn|   Home  |    Up   |   PgUp  |   Mail  |      |
 * |------+---------+---------+---------+---------+---------|  Up  |    |  Up  |---------+---------+---------+---------+---------+------|
 * |      |  Sleep  |MouseLeft|MouseDown|MouseRght|Volume Dn|------|    |------| Num Lock|   Left  |   Down  |   Right | MyComp  |      |
 * |------+---------+---------+---------+---------+---------|Scroll|    |Scroll|---------+---------+---------+---------+---------+------|
 * |      |  ||||   |MouseDnLf|MouseDown|MouseDnRg|  Mute   | Down |    | Down |  ||||   |   End   |   Down  |   PgDn  |  ||||   |      |
 * `------+---------+---------+---------+---------+----------------'    `----------------+---------+---------+---------+---------+------'
 *  | ||| |  ||||   |  MClick | LClick  |  R Click|                                      |  Insert |   Del   |   ||||  |  ||||   | ||| |
 *  `---------------------------------------------'                                      `---------------------------------------------'
 *                                                   ,-------------.    ,-------------.
 *                                                   | Stop |Refrsh|    | Prev | Next |
 *                                            ,------|------|------|    |------+------+------.
 *                                            |Brwser|Brwser|Search|    |VolUp |      |      |
 *                                            |Back  | Fwd  |------|    |------| Stop | Play-|
 *                                            |      |      | Home |    |VolDn |      | Pause|
 *                                            `--------------------'    `--------------------'
 */
[MDIA] = LAYOUT_ergodox(
// left hand
 KC_TRNS ,KC_F11   ,KC_F12  ,KC_F13   ,KC_F14  ,KC_F15  ,KC_ESC
,KC_TRNS ,KC_POWER ,KC_NO   ,KC_MS_U  ,KC_NO   ,KC_VOLU ,KC_WH_U
,KC_TRNS ,KC_SLEP  ,KC_MS_L ,KC_MS_D  ,KC_MS_R ,KC_VOLD
,KC_TRNS ,KC_NO    ,KC_NO   ,KC_MS_D  ,KC_NO   ,KC_MUTE ,KC_WH_D
,KC_NO ,KC_NO   ,KC_BTN3 ,KC_BTN1  ,KC_BTN2
                                               ,KC_WSTP ,KC_WREF
                                                        ,KC_WSCH
                                      ,KC_WBAK ,KC_NO   ,KC_WHOM
                                                                     // right hand
                                                                     ,KC_NO    ,KC_F16  ,KC_F17       ,KC_F18       ,KC_F19  ,KC_F20  ,KC_TRNS
                                                                     ,KC_WH_U  ,KC_PSCR ,KC_HOME      ,KC_UP        ,KC_PGUP ,KC_MAIL ,KC_TRNS
                                                                               ,KC_NLCK ,KC_LEFT      ,KC_DOWN      ,KC_RIGHT,KC_MYCM ,KC_TRNS
                                                                     ,KC_WH_D  ,KC_NO   ,KC_END       ,KC_DOWN      ,KC_PGDN ,KC_NO   ,KC_TRNS
                                                                                        ,KC_INS       ,KC_DEL       ,KC_NO   ,KC_NO   ,KC_NO
                                                                     ,KC_MPRV  ,KC_MNXT
                                                                     ,KC_VOLU
                                                                     ,KC_VOLD  ,KC_MSTP ,KC_MPLY
),

/******* Special Layer *****************************************************************************************************
 *
 * ,-------------------------------------------------------.    ,-------------------------------------------------------.
 * |             |  Esc |      |      |      |      |      |    |      |      |      |      |   -  | Bspc |             |
 * |-------------+------+------+------+------+-------------|    |------+------+------+------+------+------+-------------|
 * | Media Lock  |      |      |      |      |      |      |    |      |      |      |      |  [   |   ]  | Media Lock  |
 * |-------------+------+------+------+------+------|      |    |      |------+------+------+------+------+-------------|
 * | Symbol Lock |      |      |      |      |      |------|    |------|      |      |      |      |      | Symbol Lock |
 * |-------------+------+------+------+------+------|      |    |      |------+------+------+------+------+-------------|
 * | Caps Lock   |      |      |      |      |      |      |    |      |      |      |      |      |      | Caps Lock   |
 * `-------------+------+------+------+------+-------------'    `-------------+------+------+------+------+-------------'
 *      |        |      |      |      |      |                                |      |      |      |      |        |
 *      `------------------------------------'                                `------------------------------------'
 *                                         ,-------------.     ,-------------.
 *                                         |      |      |     |      |      |
 *                                  ,------|------|------|     |------+------+------.
 *                                  |      |      |      |     |      |      |      |
 *                                  |      |      |------|     |------|      |      |
 *                                  |      |      |      |     |      |      |      |
 *                                  `--------------------'     `--------------------'
 */
[SPEC] = LAYOUT_ergodox(
// left hand
 KC_TRNS ,KC_ESC  ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
,KC_CAPS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
                                             ,KC_TRNS ,KC_TRNS
                                                      ,KC_TRNS
                                     ,KC_TRNS,KC_TRNS ,KC_TRNS
                                                             // right hand
                                                             ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_MINS ,KC_BSPC ,KC_TRNS
                                                             ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_LBRC ,KC_RBRC ,KC_TRNS
                                                                      ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
                                                             ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_CAPS
                                                                               ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
                                                             ,KC_TRNS ,KC_TRNS
                                                             ,KC_TRNS
                                                             ,KC_TRNS ,KC_TRNS ,KC_TRNS
),

/******* Reverse Base Layer *********************************************************************************************
 *
 * ,------------------------------------------------------.       ,------------------------------------------------------.
 * |    =+      |   0  |   9  |   8  |   7  |   6  |  -   |       |  Esc |   5  |   4  |   3  |   2  |   1  |    `~      |
 * |------------+------+------+------+------+-------------|       |------+------+------+------+------+------+------------|
 * |    \|      |   P  |   O  |   I  |   U  |   Y  |   ]  |       |  [   |   T  |   R  |   E  |   W  |   Q  |    Tab     |
 * |------------+------+------+------+------+------|      |       |      |------+------+------+------+------+------------|
 * |    '"      |   ;  |   L  |   K  |   J  |   H  |------|       |------|   G  |   F  |   D  |   S  |  A   |            |
 * |------------+------+------+------+------+------| Tab  |       |Shift |------+------+------+------+------+------------|
 * | Capitals   |   /  |   .  |   ,  |   M  |   N  |      |       | -Tab |   B  |   V  |   C  |   X  |  Z   |   Capitals |
 * `------------+------+------+------+------+-------------'       `-------------+------+------+------+------+------------'
 *      | LCtrl | Meh  |Hyper | LAlt | LGui |                                   | RGui | RAlt | Hyper|  Meh | RCtrl |
 *      `-----------------------------------'                                   `-----------------------------------'
 *                                         ,-------------.       ,-------------.
 *                                         | Left | Right|       | Home | End  |
 *                                  ,------|------|------|       |------+------+------.
 *                                  |      |      |  Up  |       | PgUp |      |      |
 *                                  |Space |Enter |------|       |------|BackSp| Del  |
 *                                  |      |      | Down |       | PgDn |      |      |
 *                                  `--------------------'       `--------------------'
 */
[RBASE] = LAYOUT_ergodox(
// left hand
 KC_EQL    ,KC_0        ,KC_9   ,KC_8   ,KC_7  ,KC_6  ,KC_MINS
,KC_BSLS   ,KC_P        ,KC_O   ,KC_I   ,KC_U  ,KC_Y  ,KC_RBRC
,KC_QUOT     ,LT(RBASE, KC_SCLN)     ,KC_L   ,KC_K   ,LT(RBASE, KC_J)  ,KC_H
,KC_RSFT   ,KC_SLSH     ,KC_DOT ,KC_COMM,KC_M  ,KC_N  ,KC_TAB
,KC_RCTL   ,MEH_T(KC_NO),ALL_T(KC_NO),KC_RALT,KC_RGUI
                                             ,KC_LEFT ,KC_RGHT
                                                      ,KC_UP
                                    ,KC_SPC  ,KC_ENT  ,KC_DOWN
                                                                  // right hand
                                                                 ,KC_ESC      ,KC_5   ,KC_4   ,KC_3   ,KC_2    ,KC_1  ,KC_GRV
                                                                 ,KC_LBRC     ,KC_T   ,KC_R   ,KC_E   ,KC_W    ,KC_Q  ,KC_TAB
                                                                              ,KC_G   ,LT(RBASE, KC_F),KC_D   ,KC_S   ,LT(RBASE, KC_A)  ,KC_NO
                                                                 ,LSFT(KC_TAB),KC_B   ,KC_V   ,KC_C   ,KC_X    ,KC_Z  ,KC_LSFT
                                                                                      ,KC_LGUI,KC_LALT,KC_HYPR ,KC_MEH,KC_LCTL
                                                                 ,KC_HOME     ,KC_END
                                                                 ,KC_PGUP
                                                                 ,KC_PGDN     ,KC_BSPC ,KC_DEL
)
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    // shift or caps lock turns on red light
    if ((keyboard_report->mods & MOD_BIT(KC_LSFT)) || (keyboard_report->mods & MOD_BIT(KC_RSFT)) || (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK))) {
        ergodox_right_led_1_on();
    } else {
        ergodox_right_led_1_off();
    }

    // Symbol layer turns on green light
    if (layer_state & (1UL<<SYMB)) {
        ergodox_right_led_2_on();
    } else {
        ergodox_right_led_2_off();
    }

    // Media layer turns on blue light
    if (layer_state & (1UL<<MDIA)) {
        ergodox_right_led_3_on();
    } else {
        ergodox_right_led_3_off();
    }
}
