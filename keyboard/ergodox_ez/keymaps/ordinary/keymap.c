#include "ergodox_ez.h"
#include "led.h"
#include "debug.h"
#include "action_layer.h"

#define BASE 0    // default layer
#define LOCK 1    // layer lock keys
#define SYMB_MO 2 // symbols momentary layer
#define SYMB_TG 3 // symbols lock layer
#define SYMB_XX 4 // symbols exit layer
#define MDIA_MO 5 // media momentary layer
#define MDIA_TG 6 // media lock layer
#define MDIA_XX 7 // media exit layer
#define UNLOCK 8  // clear to base layer

/*
 * Ordinary Ergodox EZ keyboard layout, v3
 * modifications from default by Nicholas Keene ergodoxez@nicholaskeene.com
 * Details: http://nicholas.rinard.us/2016/03/ergodox-ez-layout.html
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Keymap 0: Basic layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * | LOCK  Grv |   1  |   2  |   3  |   4  |   5  | ESC  |           |  -   |   6  |   7  |   8  |   9  |   0  | =    LOCK |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * | Media Tab |   Q  |   W  |   E  |   R  |   T  |   [  |           |  ]   |   Y  |   U  |   I  |   O  |   P  | \   Media |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * | Symbol    |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |  ;   | '  Symbol |
 * |-----------+------+------+------+------+------|Shift |           | Tab  |------+------+------+------+------+-----------|
 * | LShift    |   Z  |   X  |   C  |   V  |   B  | -Tab |           |      |   N  |   M  |   ,  |   .  |  /   |    RShift |
 * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
 *      |LCtrl | Meh  |Hyper | LAlt | LGui |                                       | RGui | RAlt | Hyper|  Meh |RCtrl |
 *      `----------------------------------'                                       `----------------------------------'
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
 LT(LOCK, KC_GRV),KC_1        ,KC_2        ,KC_3   ,KC_4   ,KC_5   ,KC_ESC
,LT(MDIA_MO, KC_TAB),KC_Q     ,KC_W        ,KC_E   ,KC_R   ,KC_T   ,KC_LBRC
,MO(SYMB_MO)     ,KC_A        ,KC_S        ,KC_D   ,KC_F   ,KC_G
,KC_LSFT         ,KC_Z        ,KC_X        ,KC_C   ,KC_V   ,KC_B   ,LSFT(KC_TAB)
,KC_LCTL         ,MEH_T(KC_NO),ALL_T(KC_NO),KC_LALT,KC_LGUI

                                                           ,KC_HOME,KC_END
                                                                   ,KC_PGUP
                                                   ,KC_BSPC,KC_DEL ,KC_PGDN

                                                                // right hand
                                                               ,KC_MINS ,KC_6   ,KC_7   ,KC_8   ,KC_9        ,KC_0        ,LT(LOCK, KC_EQL)
                                                               ,KC_RBRC ,KC_Y   ,KC_U   ,KC_I   ,KC_O        ,KC_P        ,LT(MDIA_MO, KC_BSLS)
                                                                        ,KC_H   ,KC_J   ,KC_K   ,KC_L        ,KC_SCLN     ,LT(SYMB_MO, KC_QUOT)
                                                               ,KC_TAB  ,KC_N   ,KC_M   ,KC_COMM,KC_DOT      ,KC_SLSH     ,KC_RSFT
                                                                                ,KC_RGUI,KC_RALT,ALL_T(KC_NO),MEH_T(KC_NO),KC_RCTL

                                                               ,KC_LEFT ,KC_RGHT
                                                               ,KC_UP
                                                               ,KC_DOWN ,KC_ENT ,KC_SPC
    ),

/* Keymap 1: Layer Lock Keys
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * |           |  Esc |      |      |      |      |      |           |      |      |      |      |      |      |           |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * | Media LOCK|      |      |      |      |      |      |           |      |      |      |      |      |      | Media LOCK|
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |Symbol LOCK|      |      |      |      |      |------|           |------|      |      |      |      |      |Symbol LOCK|
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |  Caps LOCK|      |      |      |      |      |      |           |      |      |      |      |      |      |  Caps LOCK|
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
[LOCK] = KEYMAP(
// left hand
 KC_TRNS      ,KC_ESC    ,KC_TRNS   ,KC_TRNS   ,KC_TRNS ,KC_TRNS  ,KC_TRNS
,KC_FN3       ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS ,KC_TRNS  ,KC_TRNS
,KC_FN2       ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS ,KC_TRNS
,KC_CAPS      ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS ,KC_TRNS  ,KC_TRNS
,KC_TRNS      ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS

                                                        ,KC_TRNS  ,KC_TRNS
                                                                  ,KC_TRNS
                                                ,KC_TRNS,KC_TRNS  ,KC_TRNS

                                                                // right hand
                                                               ,KC_TRNS ,KC_TRNS  ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS  ,KC_TRNS
                                                               ,KC_TRNS ,KC_TRNS  ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS  ,KC_FN3
                                                                        ,KC_TRNS  ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS  ,KC_FN2
                                                               ,KC_TRNS ,KC_TRNS  ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS  ,KC_CAPS
                                                                                  ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS  ,KC_TRNS

                                                               ,KC_TRNS ,KC_TRNS
                                                               ,KC_TRNS
                                                               ,KC_TRNS ,KC_TRNS  ,KC_TRNS
    ),

/* Keymap 2: Symbol Momentary Layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * |           |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |           |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * | Media     |   !  |   @  |   {  |   }  |   &  |  <   |           |  >   |   |  |   7  |   8  |   9  |   /  | Media     |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * | Symbol    |   #  |   $  |   (  |   )  |   `  |------|           |------|   /  |   4  |   5  |   6  |   *  | Symbol    |
 * |-----------+------+------+------+------+------| Tab  |           | Shift|------+------+------+------+------+-----------|
 * | Shift     |   %  |   ^  |   [  |   ]  |   ~  |      |           |  -Tab|   \  |   1  |   2  |   3  |   -  | Shift     |
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
[SYMB_MO] = KEYMAP(
// left hand
 KC_FN2        ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_TRNS
,MO(MDIA_MO)   ,KC_EXLM ,KC_AT   ,KC_LCBR ,KC_RCBR ,KC_AMPR ,LSFT(KC_COMM)
,MO(SYMB_MO)   ,KC_HASH ,KC_DLR  ,KC_LPRN ,KC_RPRN ,KC_GRV 
,KC_LSFT       ,KC_PERC ,KC_CIRC ,KC_LBRC ,KC_RBRC ,KC_TILD ,KC_TAB
,KC_TRNS       ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
                                                   ,KC_LEFT ,KC_RGHT
                                                            ,KC_UP
                                          ,KC_SPC  ,KC_ENT  ,KC_DOWN
                                                                    // right hand
                                                                    ,KC_TRNS     ,KC_F6   ,KC_F7 ,KC_F8  ,KC_F9 ,KC_F10  ,KC_FN2
                                                                    ,LSFT(KC_DOT),KC_PIPE ,KC_7  ,KC_8   ,KC_9  ,KC_SLSH ,MO(MDIA_MO)
                                                                                 ,KC_SLSH ,KC_4  ,KC_5   ,KC_6  ,KC_ASTR ,MO(SYMB_MO)
                                                                    ,LSFT(KC_TAB),KC_BSLS ,KC_1  ,KC_2   ,KC_3  ,KC_MINS ,KC_RSFT
                                                                                          ,KC_0  ,KC_DOT ,KC_EQL,KC_PLUS ,KC_ENT
                                                                    ,KC_HOME     ,KC_END
                                                                    ,KC_PGUP
                                                                    ,KC_PGDN     ,KC_BSPC ,KC_DEL
),

/* Keymap 3: Symbol Lock Layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * | Lock      |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 | Lock      |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * | Media     |   !  |   @  |   {  |   }  |   &  |  <   |           |  >   |   |  |   7  |   8  |   9  |   /  | Media     |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |           |   #  |   $  |   (  |   )  |   `  |------|           |------|   /  |   4  |   5  |   6  |   *  |           |
 * |-----------+------+------+------+------+------| Tab  |           | Shift|------+------+------+------+------+-----------|
 * | Shift     |   %  |   ^  |   [  |   ]  |   ~  |      |           |  -Tab|   \  |   1  |   2  |   3  |   -  | Shift     |
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
[SYMB_TG] = KEYMAP(  // layer 3 : return key for symbol lock layer
// left hand
 MO(SYMB_XX)  ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_TRNS
,MO(MDIA_MO)  ,KC_EXLM ,KC_AT   ,KC_LCBR ,KC_RCBR ,KC_AMPR ,LSFT(KC_COMM)
,MO(UNLOCK)   ,KC_HASH ,KC_DLR  ,KC_LPRN ,KC_RPRN ,KC_GRV
,KC_LSFT      ,KC_PERC ,KC_CIRC ,KC_LBRC ,KC_RBRC ,KC_TILD ,KC_TAB
,KC_TRNS      ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
                                                  ,KC_LEFT ,KC_RGHT
                                                           ,KC_UP
                                         ,KC_SPC  ,KC_ENT  ,KC_DOWN
                                                                    // right hand
                                                                    ,KC_TRNS     ,KC_F6   ,KC_F7 ,KC_F8  ,KC_F9 ,KC_F10  ,MO(SYMB_XX)
                                                                    ,LSFT(KC_DOT),KC_PIPE ,KC_7  ,KC_8   ,KC_9  ,KC_SLSH ,MO(MDIA_MO)
                                                                                 ,KC_SLSH ,KC_4  ,KC_5   ,KC_6  ,KC_ASTR ,MO(UNLOCK)
                                                                    ,LSFT(KC_TAB),KC_BSLS ,KC_1  ,KC_2   ,KC_3  ,KC_MINS ,KC_RSFT
                                                                                          ,KC_0  ,KC_DOT ,KC_EQL,KC_PLUS ,KC_ENT
                                                                    ,KC_HOME     ,KC_END
                                                                    ,KC_PGUP
                                                                    ,KC_PGDN     ,KC_BSPC ,KC_DEL
    ),

/* Keymap 4: Symbol Unlock Layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * |           | Esc  |      |      |      |      |      |           |      |      |      |      |      |      |           |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * | Unlock    |      |      |      |      |      |      |           |      |      |      |      |      |      |  Unlock   |
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
[SYMB_XX] = KEYMAP(
// left hand
 KC_TRNS      ,KC_ESC    ,KC_TRNS   ,KC_TRNS   ,KC_TRNS ,KC_TRNS  ,KC_TRNS
,TG(MDIA_TG)  ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS ,KC_TRNS  ,KC_TRNS
,KC_FN1       ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS ,KC_TRNS
,KC_CAPS      ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS ,KC_TRNS  ,KC_TRNS
,KC_TRNS      ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS
							,KC_TRNS  ,KC_TRNS
								  ,KC_TRNS
						,KC_TRNS,KC_TRNS  ,KC_TRNS
											// right hand
									   ,KC_TRNS ,KC_TRNS  ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS  ,KC_TRNS
									   ,KC_TRNS ,KC_TRNS  ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS  ,TG(MDIA_TG)
										    ,KC_TRNS  ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS  ,KC_FN1
									   ,KC_TRNS ,KC_TRNS  ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS  ,KC_CAPS
									   ,KC_TRNS ,KC_TRNS  ,KC_TRNS   ,KC_TRNS   ,KC_TRNS
									   ,KC_TRNS ,KC_TRNS
									   ,KC_TRNS
									   ,KC_TRNS ,KC_TRNS  ,KC_TRNS
	),

/* Keymap 5: Media Momentary Layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * |           | F11  | F12  | F13  | F14  | F15  |      |           |      | F16  | F17  | F18  | F19  | F20  |           |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * |           |ShutDn|      | MsUp |      |      |ScrlUp|           |ScrlUp|PrtScr| Home |  Up  | PgUp | Mail |           |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |           | Sleep|MsLeft|MsDown|MsRght|      |------|           |------|NumLok| Left | Down | Right|MyComp|           |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |           |      |      |MsDown|      |      |ScrlDn|           |ScrlDn|      | End  | Down | PgDn |      |           |
 * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
 *      | Mute |Vol Dn|Vol Up| Lclk | Rclk |                                       |Insert|Delete|      |      |      |
 *      `----------------------------------'                                       `----------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         | Stop |Refrsh|           | Prev | Next |
 *                                  ,------|------|------|           |------+------+------.
 *                                  |Brwser|Brwser|Search|           |VolUp |      |      |
 *                                  |Back  | Fwd  |------|           |------| Stop | Play-|
 *                                  |      |      | Home |           |VolDn |      | Pause|
 *                                  `--------------------'           `--------------------'
 */
[MDIA_MO] = KEYMAP(
// left hand
 KC_FN3        ,KC_F11  ,KC_F12  ,KC_F13  ,KC_F14  ,KC_F15  ,KC_TRNS
,MO(MDIA_MO)   ,KC_POWER,KC_TRNS ,KC_MS_U ,KC_TRNS ,KC_TRNS ,KC_WH_U
,MO(SYMB_MO)   ,KC_SLEP ,KC_MS_L ,KC_MS_D ,KC_MS_R ,KC_TRNS
,KC_LSFT       ,KC_TRNS ,KC_TRNS ,KC_MS_D ,KC_TRNS ,KC_TRNS ,KC_WH_D
,KC_MUTE       ,KC_VOLD ,KC_VOLU ,KC_BTN1 ,KC_BTN2
                                                   ,KC_WSTP ,KC_WREF
                                                            ,KC_WSCH
                                          ,KC_WBAK ,KC_TRNS ,KC_WHOM
                                                                     // right hand
                                                                     ,KC_TRNS  ,KC_F16  ,KC_F17 ,KC_F18  ,KC_F19  ,KC_F20  ,KC_FN3
                                                                     ,KC_WH_U  ,KC_PSCR ,KC_HOME,KC_UP   ,KC_PGUP ,KC_MAIL ,MO(MDIA_MO)
                                                                               ,KC_NLCK ,KC_LEFT,KC_DOWN ,KC_RIGHT,KC_MYCM ,MO(SYMB_MO)
                                                                     ,KC_WH_D  ,KC_TRNS ,KC_END ,KC_DOWN ,KC_PGDN ,KC_TRNS ,KC_RSFT
                                                                                        ,KC_INS ,KC_DEL  ,KC_TRNS ,KC_TRNS ,KC_TRNS
                                                                     ,KC_MPRV  ,KC_MNXT
                                                                     ,KC_VOLU
                                                                     ,KC_VOLD  ,KC_MSTP ,KC_MPLY
),

/* Keymap 6: Media Lock Layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * |           | F11  | F12  | F13  | F14  | F15  |      |           |      | F16  | F17  | F18  | F19  | F20  |           |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * |           |ShutDn|      | MsUp |      |      |ScrlUp|           |ScrlUp|PrtScr| Home |  Up  | PgUp | Mail |           |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |           | Sleep|MsLeft|MsDown|MsRght|      |------|           |------|NumLok| Left | Down | Right|MyComp|           |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |           |      |      |MsDown|      |      |ScrlDn|           |ScrlDn|      | End  | Down | PgDn |      |           |
 * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
 *      | Mute |Vol Dn|Vol Up| Lclk | Rclk |                                       |Insert|Delete|      |      |      |
 *      `----------------------------------'                                       `----------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         | Stop |Refrsh|           | Prev | Next |
 *                                  ,------|------|------|           |------+------+------.
 *                                  |Brwser|Brwser|Search|           |VolUp |      |      |
 *                                  |Back  | Fwd  |------|           |------| Stop | Play-|
 *                                  |      |      | Home |           |VolDn |      | Pause|
 *                                  `--------------------'           `--------------------'
 */
[MDIA_TG] = KEYMAP(
// left hand
 MO(MDIA_XX)  ,KC_F11  ,KC_F12  ,KC_F13  ,KC_F14  ,KC_F15  ,KC_TRNS
,MO(UNLOCK)   ,KC_POWER,KC_TRNS ,KC_MS_U ,KC_TRNS ,KC_TRNS ,KC_WH_U
,KC_NO        ,KC_SLEP ,KC_MS_L ,KC_MS_D ,KC_MS_R ,KC_TRNS
,KC_LSFT      ,KC_TRNS ,KC_TRNS ,KC_MS_D ,KC_TRNS ,KC_TRNS ,KC_WH_D
,KC_MUTE      ,KC_VOLD ,KC_VOLU ,KC_BTN1 ,KC_BTN2
                                                    ,KC_WSTP ,KC_WREF
                                                             ,KC_WSCH
                                           ,KC_WBAK ,KC_TRNS ,KC_WHOM
                                                                     // right hand
                                                                     ,KC_TRNS  ,KC_F16  ,KC_F17 ,KC_F18  ,KC_F19  ,KC_F20  ,MO(MDIA_XX)
                                                                     ,KC_WH_U  ,KC_PSCR ,KC_HOME,KC_UP   ,KC_PGUP ,KC_MAIL ,MO(UNLOCK)
                                                                               ,KC_NLCK ,KC_LEFT,KC_DOWN ,KC_RIGHT,KC_MYCM ,KC_NO
                                                                     ,KC_WH_D  ,KC_TRNS ,KC_END ,KC_DOWN ,KC_PGDN ,KC_TRNS ,KC_RSFT
                                                                                        ,KC_INS ,KC_DEL  ,KC_TRNS ,KC_TRNS ,KC_TRNS
                                                                     ,KC_MPRV  ,KC_MNXT
                                                                     ,KC_VOLU
                                                                     ,KC_VOLD  ,KC_MSTP ,KC_MPLY
    ),

/* Keymap 7: Media Unlock Layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * |           | Esc  |      |      |      |      |      |           |      |      |      |      |      |      |           |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * | Unlock    |      |      |      |      |      |      |           |      |      |      |      |      |      | Unlock    |
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
[MDIA_XX] = KEYMAP(
// left hand
 KC_TRNS      ,KC_ESC    ,KC_TRNS   ,KC_TRNS   ,KC_TRNS ,KC_TRNS  ,KC_TRNS
,KC_FN1       ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS ,KC_TRNS  ,KC_TRNS
,KC_TRNS      ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS ,KC_TRNS
,KC_CAPS      ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS ,KC_TRNS  ,KC_TRNS
,KC_TRNS      ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS

                                                        ,KC_TRNS  ,KC_TRNS
                                                                  ,KC_TRNS
                                                ,KC_TRNS,KC_TRNS  ,KC_TRNS

                                                                // right hand
                                                               ,KC_TRNS ,KC_TRNS  ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS  ,KC_TRNS
                                                               ,KC_TRNS ,KC_TRNS  ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS  ,KC_FN1
                                                                        ,KC_TRNS  ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS  ,KC_TRNS
                                                               ,KC_TRNS ,KC_TRNS  ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS  ,KC_CAPS
                                                                                  ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS  ,KC_TRNS

                                                               ,KC_TRNS ,KC_TRNS
                                                               ,KC_TRNS
                                                               ,KC_TRNS ,KC_TRNS  ,KC_TRNS
    ),

/* Keymap 8: Unlock Layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * | Unlock    |      |      |      |      |      |      |           |      |      |      |      |      |      | Unlock    |
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
 KC_FN1       ,KC_ESC    ,KC_TRNS   ,KC_TRNS   ,KC_TRNS ,KC_TRNS  ,KC_TRNS
,KC_TRNS       ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS ,KC_TRNS  ,KC_TRNS
,KC_TRNS      ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS ,KC_TRNS
,KC_TRNS      ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS ,KC_TRNS  ,KC_TRNS
,KC_TRNS      ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS

                                                        ,KC_TRNS  ,KC_TRNS
                                                                  ,KC_TRNS
                                                ,KC_TRNS,KC_TRNS  ,KC_TRNS

                                                                // right hand
                                                               ,KC_TRNS ,KC_TRNS  ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS  ,KC_FN1
                                                               ,KC_TRNS ,KC_TRNS  ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS  ,KC_TRNS
                                                                        ,KC_TRNS  ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS  ,KC_TRNS
                                                               ,KC_TRNS ,KC_TRNS  ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS  ,KC_TRNS
                                                                                  ,KC_TRNS   ,KC_TRNS   ,KC_TRNS   ,KC_TRNS  ,KC_TRNS

                                                               ,KC_TRNS ,KC_TRNS
                                                               ,KC_TRNS
                                                               ,KC_TRNS ,KC_TRNS  ,KC_TRNS
    )
};

const uint16_t PROGMEM fn_actions[] = {
         [1] = ACTION_LAYER_CLEAR(ON_PRESS)                // FN1 - clear to base layer
	,[2] = ACTION_LAYER_INVERT(SYMB_TG, ON_PRESS)      // FN2 - toggle to Symbols on press
	,[3] = ACTION_LAYER_INVERT(MDIA_TG, ON_PRESS)      // FN3 - toggle to Media on press
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

    // do not change lights for locking and unlocking
    if(layer == UNLOCK || layer == LOCK || layer == SYMB_XX || layer == MDIA_XX) {
        return;
    }

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();

    // caps lock turns on red light
    if(host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
        ergodox_right_led_1_on();
    }

    // symbol lock turns on green light
    if(layer == SYMB_MO || layer == SYMB_TG) {
        ergodox_right_led_2_on();
    }

    // media lock turns on blue light
    if(layer == MDIA_MO || layer == MDIA_TG) {
        ergodox_right_led_3_on();
    }
};

