#include QMK_KEYBOARD_H

enum layer_names {
    BASE, // default layer
    SYMB, // symbols layer
    MDIA, // media layer
    SPEC  // special layer
};

/*
 * teckinesis layout for ErgoDox (EZ)
 * 
 * Modifications from The Ordinary Layout v4 by Will Wolff-Myren willwm@gmail.com
 * Modifications from default by Nicholas Keene ergodoxez@nicholaskeene.com
 *
 * No rights reserved. This software is in the public domain.
 * Credit me if you are friendly but if you're a jerk don't bother.
 * 
 * Details: readme.md
 *          https://github.com/willwm/qmk_firmware/tree/master/keyboard/ergodox_ez/keymaps/teckinesis
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/******* Base Layer ********************************************************************************************************
 *
 * ,------------------------------------------------------.           ,------------------------------------------------------.
 * | Special =+ |   1  |   2  |   3  |   4  |   5  | ESC  |           |  `   |   6  |   7  |   8  |   9  |   0  | -_ Special |
 * |------------+------+------+------+------+-------------|           |------+------+------+------+------+------+------------|
 * | Media  Tab |   Q  |   W  |   E  |   R  |   T  |   [  |           |  ]   |   Y  |   U  |   I  |   O  |   P  | \|   Media |
 * |------------+------+------+------+------+------|      |           |      |------+------+------+------+------+------------|
 * | Symbol     |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |  ;   | '"  Symbol |
 * |------------+------+------+------+------+------|Shift |           | Tab  |------+------+------+------+------+------------|
 * | Capitals   |   Z  |   X  |   C  |   V  |   B  | -Tab |           |      |   N  |   M  |   ,  |   .  |  /   |   Capitals |
 * `------------+------+------+------+------+-------------'           `-------------+------+------+------+------+------------'
 *      | LCtrl |Meh/\ |Hypr//| LAlt | LGui |                                       | RGui | RAlt |Hypr/[|Meh/] | RCtrl |
 *      `-----------------------------------'                                       `-----------------------------------'
 *                                          ,-------------.           ,-------------.
 *                                          | Home | End  |           | Left | Right|
 *                                   ,------|------|------|           |------+------+------.
 *                                   |      |      | PgUp |           |  Up  |      |      |
 *                                   |Backsp| Del  |------|           |------| Enter| Space|
 *                                   |      |      | PgDn |           | Down |      |      |
 *                                   `--------------------'           `--------------------'
 */
[BASE] = LAYOUT_ergodox(
// left hand
 KC_NO     ,KC_1,KC_2,KC_3   ,KC_4  ,KC_5  ,KC_ESC
,KC_NO     ,KC_Q   ,KC_W   ,KC_E   ,KC_R  ,KC_T  ,KC_LBRC
,KC_NO     ,KC_A   ,KC_S   ,KC_D   ,KC_F  ,KC_G
,KC_NO     ,KC_Z   ,KC_X   ,KC_C   ,KC_V  ,KC_B  ,LSFT(KC_TAB)
,KC_LCTL,MEH_T(KC_BSLS),ALL_T(KC_SLSH),KC_LALT,KC_LGUI
                                         ,KC_HOME,KC_END
                                                 ,KC_PGUP
                                 ,KC_BSPC,KC_DEL ,KC_PGDN
                                                                      // right hand
                                                                     ,KC_GRV  ,KC_6   ,KC_7   ,KC_8   ,KC_9    ,KC_0     ,KC_NO
                                                                     ,KC_RBRC ,KC_Y   ,KC_U   ,KC_I   ,KC_O    ,KC_P     ,KC_NO
                                                                              ,KC_H   ,KC_J   ,KC_K   ,KC_L    ,KC_SCLN  ,KC_NO
                                                                     ,KC_TAB  ,KC_N   ,KC_M   ,KC_COMM,KC_DOT  ,KC_SLSH  ,KC_NO
                                                                                      ,KC_RGUI,KC_RALT,ALL_T(KC_LBRC),MEH_T(KC_RBRC),KC_RCTL
                                                                     ,KC_LEFT ,KC_RGHT
                                                                     ,KC_UP
                                                                     ,KC_DOWN ,KC_ENT ,KC_SPC
    ),

/******* Symbols Layer *****************************************************************************************************
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * |           |  F1  |  F2  |  F3  |  F4  |  F5  | Esc  |           |  -   |  F6  |  F7  |  F8  |  F9  |  F10 |           |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * |           |   !  |   @  |   {  |   }  |   &  |  <   |           |  >   |   |  |   7  |   8  |   9  |   /  |           |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |           |   #  |   $  |   (  |   )  |   `  |------|           |------|   /  |   4  |   5  |   6  |   *  |           |
 * |-----------+------+------+------+------+------| Tab  |           | Shift|------+------+------+------+------+-----------|
 * |           |   %  |   ^  |   [  |   ]  |   ~  |      |           |  -Tab|   \  |   1  |   2  |   3  |   -  |           |
 * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
 *     | LCtrl | Meh  |Hyper | LAlt | LGui |                                       |RGui/0|RAlt/.|Hypr/=|Meh/+ |RCtrl/Ent|
 *     `-----------------------------------'                                       `-------------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         | Left | Right|           | Home | End  |
 *                                  ,------|------|------|           |------+------+------.
 *                                  |      |      |  Up  |           | PgUp |      |      |
 *                                  |Space |Enter |------|           |------|BackSp| Del  |
 *                                  |      |      | Down |           | PgDn |      |      |
 *                                  `--------------------'           `--------------------'
 */
[SYMB] = LAYOUT_ergodox(
// left hand
 KC_TRNS ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_ESC
,KC_TRNS ,KC_EXLM ,KC_AT   ,KC_LCBR ,KC_RCBR ,KC_AMPR ,LSFT(KC_COMM)
,KC_TRNS ,KC_HASH ,KC_DLR  ,KC_LPRN ,KC_RPRN ,KC_GRV 
,KC_TRNS ,KC_PERC ,KC_CIRC ,KC_LBRC ,KC_RBRC ,KC_TILD ,KC_TAB
,KC_LCTL ,KC_MEH  ,KC_HYPR ,KC_LALT ,KC_LGUI
                                             ,KC_LEFT ,KC_RGHT
                                                      ,KC_UP
                                    ,KC_SPC  ,KC_ENT  ,KC_DOWN
                                                                     // right hand
                                                                     ,KC_MINS     ,KC_F6   ,KC_F7 ,KC_F8  ,KC_F9 ,KC_F10  ,KC_TRNS
                                                                     ,LSFT(KC_DOT),KC_PIPE ,KC_7  ,KC_8   ,KC_9  ,KC_SLSH ,KC_TRNS
                                                                                  ,KC_SLSH ,KC_4  ,KC_5   ,KC_6  ,KC_ASTR ,KC_TRNS
                                                                     ,LSFT(KC_TAB),KC_BSLS ,KC_1  ,KC_2   ,KC_3  ,KC_MINS ,KC_TRNS
                                                                                           ,GUI_T(KC_0),ALT_T(KC_DOT),ALL_T(KC_EQL),MEH_T(KC_PLUS),CTL_T(KC_ENT)
                                                                     ,KC_HOME     ,KC_END
                                                                     ,KC_PGUP
                                                                     ,KC_PGDN     ,KC_BSPC ,KC_DEL
),

/******* Media Layer *******************************************************************************************************
 *
 * ,---------------------------------------------------------------.           ,---------------------------------------------------------------.
 * |      |   F11   |   F12   |   F13   |   F14   |   F15   | Esc  |           |      |   F16   |   F17   |   F18   |   F19   |   F20   |      |
 * |------+---------+---------+---------+---------+----------------|           |------+---------+---------+---------+---------+---------+------|
 * |      |         |MouseUpLf|Mouse Up |MouseUpRg|Volume Up|Scroll|           |Scroll|PrintScrn|   Home  |    Up   |   PgUp  |         |      |
 * |------+---------+---------+---------+---------+---------|  Up  |           |  Up  |---------+---------+---------+---------+---------+------|
 * |      |         |MouseLeft|MouseDown|MouseRght|Volume Dn|------|           |------| Num Lock|   Left  |   Down  |   Right |         |      |
 * |------+---------+---------+---------+---------+---------|Scroll|           |Scroll|---------+---------+---------+---------+---------+------|
 * |      |         |MouseDnLf|MouseDown|MouseDnRg|  Mute   | Down |           | Down |         |   End   |   Down  |   PgDn  |         |      |
 * `------+---------+---------+---------+---------+----------------'           `----------------+---------+---------+---------+---------+------'
 *  |LCtrl|   Meh   |  MClick | LClick  |  R Click|                                             |Cmd/Insrt|Optn/Del | Hyper   |  Meh    |RCtrl|
 *  `---------------------------------------------'                                             `---------------------------------------------'
 *                                                   ,-------------.           ,-------------.
 *                                                   | Stop |Refrsh|           | Prev | Next |
 *                                            ,------|------|------|           |------+------+------.
 *                                            |Brwser|Brwser|Search|           |VolUp |      |      |
 *                                            |Back  | Fwd  |------|           |------| Stop | Play-|
 *                                            |      |      | Home |           |VolDn |      | Pause|
 *                                            `--------------------'           `--------------------'
 */
[MDIA] = LAYOUT_ergodox(
// left hand
 KC_TRNS ,KC_F11   ,KC_F12  ,KC_F13   ,KC_F14  ,KC_F15  ,KC_ESC
,KC_TRNS ,KC_NO    ,KC_NO   ,KC_MS_U  ,KC_NO   ,KC_VOLU ,KC_WH_U
,KC_TRNS ,KC_NO    ,KC_MS_L ,KC_MS_D  ,KC_MS_R ,KC_VOLD
,KC_TRNS ,KC_NO    ,KC_NO   ,KC_MS_D  ,KC_NO   ,KC_MUTE ,KC_WH_D
,KC_LCTL ,KC_MEH   ,KC_BTN3 ,KC_BTN1  ,KC_BTN2
                                               ,KC_WSTP ,KC_WREF
                                                        ,KC_WSCH
                                      ,KC_WBAK ,KC_NO   ,KC_WHOM
                                                                     // right hand
                                                                     ,KC_NO    ,KC_F16  ,KC_F17       ,KC_F18       ,KC_F19  ,KC_F20  ,KC_TRNS
                                                                     ,KC_WH_U  ,KC_PSCR ,KC_HOME      ,KC_UP        ,KC_PGUP ,KC_NO   ,KC_TRNS
                                                                               ,KC_NUM  ,KC_LEFT      ,KC_DOWN      ,KC_RIGHT,KC_NO   ,KC_TRNS
                                                                     ,KC_WH_D  ,KC_NO   ,KC_END       ,KC_DOWN      ,KC_PGDN ,KC_NO   ,KC_TRNS
                                                                                        ,GUI_T(KC_INS),ALT_T(KC_DEL),KC_HYPR ,KC_MEH  ,KC_RCTL
                                                                     ,KC_MPRV  ,KC_MNXT
                                                                     ,KC_VOLU
                                                                     ,KC_VOLD  ,KC_MSTP ,KC_MPLY
),

/******* Special Layer *****************************************************************************************************
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * |           |  Esc |      |      |      |      |      |           |      |      |      |      |      | Bspc |           |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * |           |      |      |      |      |      |      |           |      |      |      |      |      |      |           |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |           |      |      |      |      |      |------|           |------|      |      |      |      |      |           |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |           |      |      |      |      |      |      |           |      |      |      |      |      |      | RShift    |
 * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
 *      |      |      |      |      |      |                                       |      |      |      |      |      |
 *      `----------------------------------'                                       `----------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         |      |      |           |      |      |
 *                                  ,------|------|------|           |------+------+------.
 *                                  |      |      |      |           |      |      |      |
 *                                  |      |      |------|           |------|      |      |
 *                                  |      |      |      |           |      |      |      |
 *                                  `--------------------'           `--------------------'
 */
[SPEC] = LAYOUT_ergodox(
// left hand
 KC_TRNS ,KC_ESC  ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS

                                             ,KC_TRNS ,KC_TRNS
                                                      ,KC_TRNS
                                     ,KC_TRNS,KC_TRNS ,KC_TRNS
                                                                     // right hand
                                                                     ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_BSPC ,KC_TRNS
                                                                     ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
                                                                              ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
                                                                     ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_RSFT
                                                                                       ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS

                                                                     ,KC_TRNS ,KC_TRNS
                                                                     ,KC_TRNS
                                                                     ,KC_TRNS ,KC_TRNS ,KC_TRNS
    )
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    // shift or caps lock turns on red light
    if((keyboard_report->mods & MOD_BIT(KC_RSFT)) || (host_keyboard_led_state().caps_lock)) {
        ergodox_right_led_1_on();
    } else {
        ergodox_right_led_1_off();
    }

    // Symbol layer turns on green light
    if(IS_LAYER_ON(SYMB)) {
        ergodox_right_led_2_on();
    } else {
        ergodox_right_led_2_off();
    }

    // Media layer turns on blue light
    if(IS_LAYER_ON(MDIA)) {
        ergodox_right_led_3_on();
    } else {
        ergodox_right_led_3_off();
    }
}
