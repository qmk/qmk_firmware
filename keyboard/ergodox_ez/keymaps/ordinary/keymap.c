#include "ergodox_ez.h"
#include "led.h"
#include "debug.h"
#include "action_layer.h"
#include "action_util.h"

#define BASE    0 // default layer
#define LOCK    1 // shift-lock layer
#define SYMB_SH 2 // symbols shift layer
#define SYMB_LK 3 // symbols lock layer
#define SYMB_UN 4 // symbols unlock layer
#define MDIA_SH 5 // media shift layer
#define MDIA_LK 6 // media lock layer
#define MDIA_UN 7 // media unlock layer
#define UNLOCK  8 // clear to base layer

/*
 * The Ordinary Layout for the Ergodox EZ keyboard, v3.1
 * modifications from default by Nicholas Keene ergodoxez@nicholaskeene.com
 * Details: readme.md
 *          https://github.com/nrrkeene/qmk_firmware/tree/master/keyboard/ergodox_ez/keymaps/ordinary
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Keymap 0: Base Layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * | LOCK   `~ |   1  |   2  |   3  |   4  |   5  | ESC  |           |  -   |   6  |   7  |   8  |   9  |   0  | =    LOCK |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * | Media Tab |   Q  |   W  |   E  |   R  |   T  |   [  |           |  ]   |   Y  |   U  |   I  |   O  |   P  | \   Media |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * | Symbol    |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |  ;   | '  Symbol |
 * |-----------+------+------+------+------+------|Shift |           | Tab  |------+------+------+------+------+-----------|
 * | LShift    |   Z  |   X  |   C  |   V  |   B  | -Tab |           |      |   N  |   M  |   ,  |   .  |  /   |    RShift |
 * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
 *     | LCtrl | Meh  |Hyper | LAlt | LGui |                                       | RGui | RAlt | Hyper|  Meh | RCtrl |
 *     `-----------------------------------'                                       `-----------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         | Home | End  |           | Left | Right|
 *                                  ,------|------|------|           |------+------+------.
 *                                  |      |      | PgUp |           |  Up  |      |      |
 *                                  |Backsp| Del  |------|           |------| Enter| Space|
 *                                  |      |      | PgDn |           | Down |      |      |
 *                                  `--------------------'           `--------------------'
 */
[BASE] = KEYMAP(
// left hand
 LT(LOCK, KC_GRV)   ,KC_1        ,KC_2        ,KC_3   ,KC_4  ,KC_5  ,KC_ESC
,LT(MDIA_SH, KC_TAB),KC_Q        ,KC_W        ,KC_E   ,KC_R  ,KC_T  ,KC_LBRC
,MO(SYMB_SH)        ,KC_A        ,KC_S        ,KC_D   ,KC_F  ,KC_G
,KC_LSFT            ,KC_Z        ,KC_X        ,KC_C   ,KC_V  ,KC_B  ,LSFT(KC_TAB)
,KC_LCTL            ,MEH_T(KC_NO),ALL_T(KC_NO),KC_LALT,KC_LGUI

                                                            ,KC_HOME,KC_END
                                                                    ,KC_PGUP
                                                    ,KC_BSPC,KC_DEL ,KC_PGDN

                                                                // right hand
                                                               ,KC_MINS ,KC_6   ,KC_7   ,KC_8   ,KC_9        ,KC_0        ,LT(LOCK, KC_EQL)
                                                               ,KC_RBRC ,KC_Y   ,KC_U   ,KC_I   ,KC_O        ,KC_P        ,LT(MDIA_SH, KC_BSLS)
                                                                        ,KC_H   ,KC_J   ,KC_K   ,KC_L        ,KC_SCLN     ,LT(SYMB_SH, KC_QUOT)
                                                               ,KC_TAB  ,KC_N   ,KC_M   ,KC_COMM,KC_DOT      ,KC_SLSH     ,KC_RSFT
                                                                                ,KC_RGUI,KC_RALT,ALL_T(KC_NO),MEH_T(KC_NO),KC_RCTL

                                                               ,KC_LEFT ,KC_RGHT
                                                               ,KC_UP
                                                               ,KC_DOWN ,KC_ENT ,KC_SPC
    ),

/* Keymap 1: Layer Lock Keys
 *
 * ,-------------------------------------------------------.           ,-------------------------------------------------------.
 * |             |  Esc |      |      |      |      |      |           |      |      |      |      |      | Bspc |             |
 * |-------------+------+------+------+------+-------------|           |------+------+------+------+------+------+-------------|
 * | Media  LOCK |      |      |      |      |      |      |           |      |      |      |      |      |      | Media  LOCK |
 * |-------------+------+------+------+------+------|      |           |      |------+------+------+------+------+-------------|
 * | Symbol LOCK |      |      |      |      |      |------|           |------|      |      |      |      |      | Symbol LOCK |
 * |-------------+------+------+------+------+------|      |           |      |------+------+------+------+------+-------------|
 * | Caps   LOCK |      |      |      |      |      |      |           |      |      |      |      |      |      | Caps   LOCK |
 * `-------------+------+------+------+------+-------------'           `-------------+------+------+------+------+-------------'
 *      |        |      |      |      |      |                                       |      |      |      |      |        |
 *      `------------------------------------'                                       `------------------------------------'
 *                                           ,-------------.           ,-------------.
 *                                           |      |      |           |      |      |
 *                                    ,------|------|------|           |------+------+------.
 *                                    |      |      |      |           |      |      |      |
 *                                    |      |      |------|           |------|      |      |
 *                                    |      |      |      |           |      |      |      |
 *                                    `--------------------'           `--------------------'
 */
[LOCK] = KEYMAP(
// left hand
 KC_TRNS ,KC_ESC  ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
,KC_FN3  ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
,KC_FN2  ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
,KC_CAPS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS

                                             ,KC_TRNS ,KC_TRNS
                                                      ,KC_TRNS
                                     ,KC_TRNS,KC_TRNS ,KC_TRNS

                                                                // right hand
                                                               ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_BSPC ,KC_TRNS
                                                               ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_FN3
                                                                        ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_FN2
                                                               ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_CAPS
                                                                                 ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS

                                                               ,KC_TRNS ,KC_TRNS
                                                               ,KC_TRNS
                                                               ,KC_TRNS ,KC_TRNS ,KC_TRNS
    ),

/* Keymap 2: Symbol Shift Layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * | LOCK      |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |  -   |  F6  |  F7  |  F8  |  F9  |  F10 |      LOCK |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * | Media     |   !  |   @  |   {  |   }  |   &  |  <   |           |  >   |   |  |   7  |   8  |   9  |   /  |     Media |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * | Symbol    |   #  |   $  |   (  |   )  |   `  |------|           |------|   /  |   4  |   5  |   6  |   *  |    Symbol |
 * |-----------+------+------+------+------+------| Tab  |           | Shift|------+------+------+------+------+-----------|
 * | LShift    |   %  |   ^  |   [  |   ]  |   ~  |      |           |  -Tab|   \  |   1  |   2  |   3  |   -  |    RShift |
 * `-----------+------+------+------+------+-------------'           `------------+------+------+------+------+------------'
 *      |      |      |      |      |      |                                       |   0  |    . |   =  |   +  | Entr |
 *      `----------------------------------'                                       `----------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         | Left | Right|           | Home | End  |
 *                                  ,------|------|------|           |------+------+------.
 *                                  |      |      |  Up  |           | PgUp |      |      |
 *                                  |Space |Enter |------|           |------|BackSp| Del  |
 *                                  |      |      | Down |           | PgDn |      |      |
 *                                  `--------------------'           `--------------------'
 */
[SYMB_SH] = KEYMAP(
// left hand
 KC_FN2        ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_TRNS
,MO(MDIA_SH)   ,KC_EXLM ,KC_AT   ,KC_LCBR ,KC_RCBR ,KC_AMPR ,LSFT(KC_COMM)
,MO(SYMB_SH)   ,KC_HASH ,KC_DLR  ,KC_LPRN ,KC_RPRN ,KC_GRV 
,KC_LSFT       ,KC_PERC ,KC_CIRC ,KC_LBRC ,KC_RBRC ,KC_TILD ,KC_TAB
,KC_TRNS       ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
                                                   ,KC_LEFT ,KC_RGHT
                                                            ,KC_UP
                                          ,KC_SPC  ,KC_ENT  ,KC_DOWN
                                                                    // right hand
                                                                    ,KC_MINS     ,KC_F6   ,KC_F7 ,KC_F8  ,KC_F9 ,KC_F10  ,KC_FN2
                                                                    ,LSFT(KC_DOT),KC_PIPE ,KC_7  ,KC_8   ,KC_9  ,KC_SLSH ,MO(MDIA_SH)
                                                                                 ,KC_SLSH ,KC_4  ,KC_5   ,KC_6  ,KC_ASTR ,MO(SYMB_SH)
                                                                    ,LSFT(KC_TAB),KC_BSLS ,KC_1  ,KC_2   ,KC_3  ,KC_MINS ,KC_RSFT
                                                                                          ,GUI_T(KC_0),ALT_T(KC_DOT),ALL_T(KC_EQL),MEH_T(KC_PLUS),CTL_T(KC_ENT)
                                                                    ,KC_HOME     ,KC_END
                                                                    ,KC_PGUP
                                                                    ,KC_PGDN     ,KC_BSPC ,KC_DEL
),

/* Keymap 3: Symbol Lock Layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * | LOCK      |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |  -   |  F6  |  F7  |  F8  |  F9  |  F10 |      LOCK |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * | Media     |   !  |   @  |   {  |   }  |   &  |  <   |           |  >   |   |  |   7  |   8  |   9  |   /  |     Media |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * | Symbol    |   #  |   $  |   (  |   )  |   `  |------|           |------|   /  |   4  |   5  |   6  |   *  |    Symbol |
 * |-----------+------+------+------+------+------| Tab  |           | Shift|------+------+------+------+------+-----------|
 * | LShift    |   %  |   ^  |   [  |   ]  |   ~  |      |           |  -Tab|   \  |   1  |   2  |   3  |   -  |    RShift |
 * `-----------+------+------+------+------+-------------'           `------------+------+------+------+------+------------'
 *      |      |      |      |      |      |                                       |   0  |    . |   =  |   +  | Entr |
 *      `----------------------------------'                                       `----------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         | Left | Right|           | Home | End  |
 *                                  ,------|------|------|           |------+------+------.
 *                                  |      |      |  Up  |           | PgUp |      |      |
 *                                  |Space |Enter |------|           |------|BackSp| Del  |
 *                                  |      |      | Down |           | PgDn |      |      |
 *                                  `--------------------'           `--------------------'
 */
[SYMB_LK] = KEYMAP(
// left hand
 MO(SYMB_UN)  ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_TRNS
,MO(MDIA_SH) ,KC_EXLM ,KC_AT   ,KC_LCBR ,KC_RCBR ,KC_AMPR ,LSFT(KC_COMM)
,MO(UNLOCK)  ,KC_HASH ,KC_DLR  ,KC_LPRN ,KC_RPRN ,KC_GRV
,KC_LSFT     ,KC_PERC ,KC_CIRC ,KC_LBRC ,KC_RBRC ,KC_TILD ,KC_TAB
,KC_TRNS     ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
                                                 ,KC_LEFT ,KC_RGHT
                                                          ,KC_UP
                                        ,KC_SPC  ,KC_ENT  ,KC_DOWN
                                                                    // right hand
                                                                    ,KC_MINS     ,KC_F6   ,KC_F7 ,KC_F8  ,KC_F9 ,KC_F10  ,MO(SYMB_UN)
                                                                    ,LSFT(KC_DOT),KC_PIPE ,KC_7  ,KC_8   ,KC_9  ,KC_SLSH ,MO(MDIA_SH)
                                                                                 ,KC_SLSH ,KC_4  ,KC_5   ,KC_6  ,KC_ASTR ,MO(UNLOCK)
                                                                    ,LSFT(KC_TAB),KC_BSLS ,KC_1  ,KC_2   ,KC_3  ,KC_MINS ,KC_RSFT
                                                                                          ,GUI_T(KC_0),ALT_T(KC_DOT),ALL_T(KC_EQL),MEH_T(KC_PLUS),CTL_T(KC_ENT)
                                                                    ,KC_HOME     ,KC_END
                                                                    ,KC_PGUP
                                                                    ,KC_PGDN     ,KC_BSPC ,KC_DEL
    ),

/* Keymap 4: Symbol Unlock Layer
 *
 * ,------------------------------------------------------.           ,------------------------------------------------------.
 * |            | Esc  |      |      |      |      |      |           |      |      |      |      |      | Bspc |            |
 * |------------+------+------+------+------+-------------|           |------+------+------+------+------+------+------------|
 * | Media LOCK |      |      |      |      |      |      |           |      |      |      |      |      |      | Media LOCK |
 * |------------+------+------+------+------+------|      |           |      |------+------+------+------+------+------------|
 * |     UNLOCK |      |      |      |      |      |------|           |------|      |      |      |      |      |     UNLOCK |
 * |------------+------+------+------+------+------|      |           |      |------+------+------+------+------+------------|
 * | Caps  LOCK |      |      |      |      |      |      |           |      |      |      |      |      |      | Caps  LOCK |
 * `------------+------+------+------+------+-------------'           `-------------+------+------+------+------+------------'
 *       |      |      |      |      |      |                                       |      |      |      |      |      |
 *       `----------------------------------'                                       `----------------------------------'
 *                                          ,-------------.           ,-------------.
 *                                          |      |      |           |      |      |
 *                                   ,------|------|------|           |------+------+------.
 *                                   |      |      |      |           |      |      |      |
 *                                   |      |      |------|           |------|      |      |
 *                                   |      |      |      |           |      |      |      |
 *                                   `--------------------'           `--------------------'
 */
[SYMB_UN] = KEYMAP(
// left hand
 KC_TRNS     ,KC_ESC  ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
,TG(MDIA_LK) ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
,KC_FN1      ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
,KC_CAPS     ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
,KC_TRNS     ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
                                                ,KC_TRNS  ,KC_TRNS
                                                          ,KC_TRNS
                                        ,KC_TRNS,KC_TRNS  ,KC_TRNS
                                                                     // right hand
                                                                     ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_BSPC ,KC_TRNS
                                                                     ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,TG(MDIA_LK)
                                                                              ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_FN1
                                                                     ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_CAPS
                                                                     ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
                                                                     ,KC_TRNS ,KC_TRNS
                                                                     ,KC_TRNS
                                                                     ,KC_TRNS ,KC_TRNS ,KC_TRNS
),

/* Keymap 5: Media Shift Layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * | LOCK      | F11  | F12  | F13  | F14  | F15  |      |           |      | F16  | F17  | F18  | F19  | F20  |      LOCK |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * | Media     |ShutDn|LClick| MsUp |RClick|Vol Up|ScrlUp|           |ScrlUp|PrtScr| Home |  Up  | PgUp | Mail |     Media |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * | Symbol    | Sleep|MsLeft|MsDown|MsRght|Vol Dn|------|           |------|NumLok| Left | Down | Right|MyComp|    Symbol |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * | LShift    |      |      |MsDown|      | Mute |ScrlDn|           |ScrlDn|      | End  | Down | PgDn |      |    RShift |
 * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
 *      | LCtrl| Meh  |Hyper | LAlt | LGui |                                       |Insert|Delete| Hyper| LAlt | LGui |
 *      `----------------------------------'                                       `----------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         | Stop |Refrsh|           | Prev | Next |
 *                                  ,------|------|------|           |------+------+------.
 *                                  |Brwser|Brwser|Search|           |VolUp |      |      |
 *                                  |Back  | Fwd  |------|           |------| Stop | Play-|
 *                                  |      |      | Home |           |VolDn |      | Pause|
 *                                  `--------------------'           `--------------------'
 */
[MDIA_SH] = KEYMAP(
// left hand
 KC_FN3        ,KC_F11      ,KC_F12  ,KC_F13  ,KC_F14  ,KC_F15  ,KC_NO
,MO(MDIA_SH)   ,KC_POWER    ,KC_BTN1 ,KC_MS_U ,KC_BTN2 ,KC_VOLU ,KC_WH_U
,MO(SYMB_SH)   ,KC_SLEP     ,KC_MS_L ,KC_MS_D ,KC_MS_R ,KC_VOLD
,KC_LSFT       ,KC_NO       ,KC_NO   ,KC_MS_D ,KC_NO   ,KC_MUTE ,KC_WH_D
,KC_LCTL       ,MEH_T(KC_NO),ALL_T(KC_NO),KC_LALT,KC_LGUI
                                                       ,KC_WSTP ,KC_WREF
                                                                ,KC_WSCH
                                              ,KC_WBAK ,KC_NO   ,KC_WHOM
                                                                     // right hand
                                                                     ,KC_NO    ,KC_F16  ,KC_F17 ,KC_F18  ,KC_F19  ,KC_F20  ,KC_FN3
                                                                     ,KC_WH_U  ,KC_PSCR ,KC_HOME,KC_UP   ,KC_PGUP ,KC_MAIL ,MO(MDIA_SH)
                                                                               ,KC_NLCK ,KC_LEFT,KC_DOWN ,KC_RIGHT,KC_MYCM ,MO(SYMB_SH)
                                                                     ,KC_WH_D  ,KC_NO   ,KC_END ,KC_DOWN ,KC_PGDN ,KC_NO   ,KC_RSFT
                                                                                        ,GUI_T(KC_INS),ALT_T(KC_DEL),ALL_T(KC_NO),MEH_T(KC_NO),KC_RCTL
                                                                     ,KC_MPRV  ,KC_MNXT
                                                                     ,KC_VOLU
                                                                     ,KC_VOLD  ,KC_MSTP ,KC_MPLY
),

/* Keymap 6: Media Lock Layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * | LOCK      | F11  | F12  | F13  | F14  | F15  |      |           |      | F16  | F17  | F18  | F19  | F20  |      LOCK |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * | Media     |ShutDn|LClick| MsUp |RClick|Vol Up|ScrlUp|           |ScrlUp|PrtScr| Home |  Up  | PgUp | Mail |     Media |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |           | Sleep|MsLeft|MsDown|MsRght|Vol Dn|------|           |------|NumLok| Left | Down | Right|MyComp|           |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * | LShift    |      |      |MsDown|      | Mute |ScrlDn|           |ScrlDn|      | End  | Down | PgDn |      |    RShift |
 * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
 *      | LCtrl| Meh  |Hyper | LAlt | LGui |                                       |Insert|Delete| Hyper| LAlt | LGui |
 *      `----------------------------------'                                       `----------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         | Stop |Refrsh|           | Prev | Next |
 *                                  ,------|------|------|           |------+------+------.
 *                                  |Brwser|Brwser|Search|           |VolUp |      |      |
 *                                  |Back  | Fwd  |------|           |------| Stop | Play-|
 *                                  |      |      | Home |           |VolDn |      | Pause|
 *                                  `--------------------'           `--------------------'
 */
[MDIA_LK] = KEYMAP(
// left hand
 MO(MDIA_UN),KC_F11      ,KC_F12  ,KC_F13  ,KC_F14  ,KC_F15  ,KC_NO
,MO(UNLOCK) ,KC_POWER    ,KC_BTN1 ,KC_MS_U ,KC_BTN2 ,KC_VOLU ,KC_WH_U
,KC_NO      ,KC_SLEP     ,KC_MS_L ,KC_MS_D ,KC_MS_R ,KC_VOLD  
,KC_LSFT    ,KC_NO       ,KC_NO   ,KC_MS_D ,KC_NO   ,KC_MUTE ,KC_WH_D
,KC_LCTL    ,MEH_T(KC_NO),ALL_T(KC_NO),KC_LALT,KC_LGUI
                                                    ,KC_WSTP ,KC_WREF
                                                             ,KC_WSCH
                                           ,KC_WBAK ,KC_NO   ,KC_WHOM
                                                                     // right hand
                                                                     ,KC_NO    ,KC_F16  ,KC_F17 ,KC_F18  ,KC_F19  ,KC_F20  ,MO(MDIA_UN)
                                                                     ,KC_WH_U  ,KC_PSCR ,KC_HOME,KC_UP   ,KC_PGUP ,KC_MAIL ,MO(UNLOCK)
                                                                               ,KC_NLCK ,KC_LEFT,KC_DOWN ,KC_RIGHT,KC_MYCM ,KC_NO
                                                                     ,KC_WH_D  ,KC_NO   ,KC_END ,KC_DOWN ,KC_PGDN ,KC_NO   ,KC_RSFT
                                                                                        ,GUI_T(KC_INS),ALT_T(KC_DEL),ALL_T(KC_NO),MEH_T(KC_NO),KC_RCTL
                                                                     ,KC_MPRV  ,KC_MNXT
                                                                     ,KC_VOLU
                                                                     ,KC_VOLD  ,KC_MSTP ,KC_MPLY
    ),

/* Keymap 7: Media Unlock Layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * |           | Esc  |      |      |      |      |      |           |      |      |      |      |      | Bspc |           |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * |    UNLOCK |      |      |      |      |      |      |           |      |      |      |      |      |      |    UNLOCK |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |           |      |      |      |      |      |------|           |------|      |      |      |      |      |           |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * | Caps LOCK |      |      |      |      |      |      |           |      |      |      |      |      |      | Caps LOCK |
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
[MDIA_UN] = KEYMAP(
// left hand
 KC_TRNS ,KC_ESC  ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
,KC_FN1  ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
,KC_CAPS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS

                                             ,KC_TRNS ,KC_TRNS
                                                      ,KC_TRNS
                                    ,KC_TRNS ,KC_TRNS ,KC_TRNS

                                                                // right hand
                                                               ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_BSPC ,KC_TRNS
                                                               ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_FN1
                                                                        ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
                                                               ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_CAPS
                                                                                 ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS

                                                               ,KC_TRNS ,KC_TRNS
                                                               ,KC_TRNS
                                                               ,KC_TRNS ,KC_TRNS ,KC_TRNS
    ),

/* Keymap 8: Unlock Layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * | UNLOCK    |      |      |      |      |      |      |           |      |      |      |      |      |      |    UNLOCK |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * |           |      |      |      |      |      |      |           |      |      |      |      |      |      |           |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |           |      |      |      |      |      |------|           |------|      |      |      |      |      |           |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |           |      |      |      |      |      |      |           |      |      |      |      |      |      |           |
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
[UNLOCK] = KEYMAP(
// left hand
 KC_FN1  ,KC_ESC  ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS

                                             ,KC_TRNS ,KC_TRNS
                                                      ,KC_TRNS
                                    ,KC_TRNS ,KC_TRNS ,KC_TRNS

                                                                // right hand
                                                               ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_FN1
                                                               ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
                                                                        ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
                                                               ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
                                                                                 ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS

                                                               ,KC_TRNS ,KC_TRNS
                                                               ,KC_TRNS
                                                               ,KC_TRNS ,KC_TRNS  ,KC_TRNS
    )
};

const uint16_t PROGMEM fn_actions[] = {
     [1] = ACTION_LAYER_CLEAR(ON_PRESS)           // FN1 - clear to base layer
    ,[2] = ACTION_LAYER_INVERT(SYMB_LK, ON_PRESS) // FN2 - toggle to Symbols on press
    ,[3] = ACTION_LAYER_INVERT(MDIA_LK, ON_PRESS) // FN3 - toggle to Media on press
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
        if (record->event.pressed) {
          register_code(KC_RSFT);
        } else {
          unregister_code(KC_RSFT);
        }
        break;
      }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);

    // shift or caps lock turns on red light
    if((keyboard_report->mods & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))) || (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK))) {
        ergodox_right_led_1_on();
    } else {
        ergodox_right_led_1_off();
    }

    // do not change lights while locking and unlocking
    if(layer == LOCK || layer == SYMB_UN || layer == MDIA_UN || layer == UNLOCK) {
        return;
    }

    //ergodox_board_led_off();

    // symbol turns on green light
    if(layer == SYMB_SH || layer == SYMB_LK) {
        ergodox_right_led_2_on();
    } else {
        ergodox_right_led_2_off();
    }

    // media turns on blue light
    if(layer == MDIA_SH || layer == MDIA_LK) {
        ergodox_right_led_3_on();
    } else {
        ergodox_right_led_3_off();
    }
};

