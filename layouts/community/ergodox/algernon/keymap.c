/*
 * algernon's ErgoDox EZ layout, please see the readme.md file!
 */

#include <stdarg.h>
#include QMK_KEYBOARD_H
#include "led.h"
#include "debug.h"
#include "action_layer.h"
#include "action_util.h"
#include "timer.h"
#include "keymap_plover.h"
#include "eeconfig.h"
#include "wait.h"
#include "version.h"

/* Layers */

enum {
  BASE = 0,
  ADORE,
  ARRW,
  APPSEL,
  HUN,
  NMDIA,
  PLVR,
};

/* Macros */

enum {
  NONE = 0,
  // Buttons that do extra stuff
  A_GUI,
  A_PLVR,
  A_MPN,

  // Application select keys
  APP_SLK, // Slack
  APP_EMCS, // Emacs
  APP_TERM, // Terminal
  APP_CHRM, // Chrome
  APP_MSIC, // Music

  // Hungarian layer keys
  HU_AA, // Á
  HU_OO, // Ó
  HU_EE, // É
  HU_UU, // Ú
  HU_II, // Í
  HU_OE, // Ö
  HU_UE, // Ü
  HU_OEE, // Ő
  HU_UEE, // Ű

  // number/symbol keys
  A_1, // 1
  A_2, // 2
  A_3, // ...
  A_4,
  A_5,
  A_6,
  A_7,
  A_8,
  A_9,
  A_0,

  // Fx
  Fx,
};

/* Fn keys */

enum {
  F_BSE = 0,
  F_HUN,
  F_GUI,
  F_SFT,
  F_ALT,
  F_CTRL
};

/* Custom keycodes */

enum {
  CT_CLN = 0,
  CT_TA,
  CT_LBP,
  CT_RBP,
  CT_TMUX,
  CT_TPS,
  CT_SR,
};

/* States & timers */

uint16_t gui_timer = 0;

#if KEYLOGGER_ENABLE
# ifdef AUTOLOG_ENABLE
bool log_enable = true;
# else
bool log_enable = false;
# endif
#endif

bool time_travel = false;
bool skip_leds = false;

static uint8_t is_adore = 0;

/* The Keymap */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Keymap 0: Base Layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * | Next/Prev | 9    | 7  @ | 5  * | 3  ^ | 1  $ | F11  |           |  Fx  | 0  % | 2  ! | 4  # | 6  & | 8    |    Plover |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * |         ~ |   '  |   ,  |   .  |   P  |   Y  |   (  |           |  )   |   F  |   G  |   C  |   R  |  L   | \         |
 * |-----------+------+------+------+------+------|   [  |           |  ]   |------+------+------+------+------+-----------|
 * | Tab/ARROW |   A  |   O  |   E  |   U  |   I  |------|           |------|   D  |   H  |   T  |   N  |  S   | = / Arrow |
 * |-----------+------+------+------+------+------| tmux |           | tmux |------+------+------+------+------+-----------|
 * | Play/Pause|   /  |   Q  |   J  |   K  |   X  |      |           | Pane |   B  |   M  |   W  |   V  |  Z   | Stop/Reset|
 * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
 *     |       |      |      |      |   :  |                                       |   -  |      |      |      |       |
 *     `-----------------------------------'                                       `-----------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         | LAlt | GUI  |           | MDIA | Del  |
 *                                  ,------|------|------|           |------+------+------.
 *                                  |      |      | Ctrl |           | LEAD |      |      |
 *                                  |Backsp|LShift|------|           |------| Enter| Space|
 *                                  |      |      | ESC  |           | HUN  |      |      |
 *                                  `--------------------'           `--------------------'
 */
[BASE] = LAYOUT_ergodox(
// left hand
 M(A_MPN)           ,M(A_9)      ,M(A_7)      ,M(A_5)  ,M(A_3)  ,M(A_1)  ,KC_F11
,KC_GRV             ,KC_QUOT     ,KC_COMM     ,KC_DOT  ,KC_P    ,KC_Y    ,TD(CT_LBP)
,TD(CT_TA)          ,KC_A        ,KC_O        ,KC_E    ,KC_U    ,KC_I
,KC_MPLY            ,KC_SLSH     ,KC_Q        ,KC_J    ,KC_K    ,KC_X    ,TD(CT_TMUX)
,KC_NO              ,KC_NO       ,KC_NO       ,KC_NO   ,TD(CT_CLN)

                                                            ,F(F_ALT),F(F_GUI)
                                                                     ,F(F_CTRL)
                                                    ,KC_BSPC,F(F_SFT),KC_ESC

                                                                // right hand
                                                               ,M(Fx)     ,M(A_0)  ,M(A_2)    ,M(A_4)  ,M(A_6)  ,M(A_8)   ,M(A_PLVR)
                                                               ,TD(CT_RBP),KC_F    ,KC_G      ,KC_C    ,KC_R    ,KC_L     ,KC_BSLS
                                                                          ,KC_D    ,KC_H      ,KC_T    ,KC_N    ,KC_S     ,KC_EQL
                                                               ,TD(CT_TPS),KC_B    ,KC_M      ,KC_W    ,KC_V    ,KC_Z     ,TD(CT_SR)
                                                                                   ,KC_MINS   ,KC_NO   ,KC_NO   ,KC_NO    ,KC_NO

                                                               ,OSL(NMDIA),KC_DEL
                                                               ,KC_LEAD
                                                               ,F(F_HUN)  ,KC_ENT ,KC_SPC
    ),

/* Keymap 1: Adore layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * | Play/Pause| 9    | 7  @ | 5  * | 3  ^ | 1  $ | F11  |           |  Fx  | 0  % | 2  ! | 4  # | 6  & | 8    |    Plover |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * |         \ |   X  |   W  |   C  |   H  |   F  |   (  |           |  )   |   M  |   G  |   L  |   P  |  /   | `~        |
 * |-----------+------+------+------+------+------|   [  |           |  ]   |------+------+------+------+------+-----------|
 * | Tab/Arrow |   A  |   O  |   E  |   I  |   U  |------|           |------|   D  |   R  |   T  |   N  |  S   | =         |
 * |-----------+------+------+------+------+------| tmux |           | tmux |------+------+------+------+------+-----------|
 * |           |   Z  |   Q  |   '  |   ,  |   .  |      |           | pane |   B  |   K  |   V  |   Y  |  J   |           |
 * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
 *     |       |      |      |      |   :  |                                       |   -  |      |      |      |       |
 *     `-----------------------------------'                                       `-----------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         | LAlt | GUI  |           | MDIA | Del  |
 *                                  ,------|------|------|           |------+------+------.
 *                                  |      |      | Ctrl |           | HUN  |      |      |
 *                                  |Backsp|LShift|------|           |------| Enter| Space|
 *                                  |      |      | ESC  |           | LEAD |      |      |
 *                                  `--------------------'           `--------------------'
 */
[ADORE] = LAYOUT_ergodox(
// left hand
 KC_MPLY            ,M(A_9)      ,M(A_7)      ,M(A_5)  ,M(A_3)  ,M(A_1) ,KC_F11
,KC_BSLS            ,KC_X        ,KC_W        ,KC_C    ,KC_H    ,KC_F   ,TD(CT_LBP)
,TD(CT_TA)          ,KC_A        ,KC_O        ,KC_E    ,KC_I    ,KC_U
,KC_NO              ,KC_Z        ,KC_Q        ,KC_QUOT ,KC_COMM ,KC_DOT ,TD(CT_TMUX)
,KC_NO              ,KC_NO       ,KC_NO       ,KC_NO   ,TD(CT_CLN)

                                                            ,F(F_ALT),F(F_GUI)
                                                                     ,F(F_CTRL)
                                                    ,KC_BSPC,F(F_SFT),KC_ESC

                                                                // right hand
                                                               ,M(Fx)     ,M(A_0)   ,M(A_2)  ,M(A_4)  ,M(A_6)  ,M(A_8)  ,M(A_PLVR)
                                                               ,TD(CT_RBP),KC_M     ,KC_G    ,KC_L    ,KC_P    ,KC_SLSH ,KC_GRV
                                                                          ,KC_D     ,KC_R    ,KC_T    ,KC_N    ,KC_S    ,KC_EQL
                                                               ,TD(CT_TPS),KC_B     ,KC_K    ,KC_V    ,KC_Y    ,KC_J    ,KC_NO
                                                                                    ,KC_MINS ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO

                                                               ,OSL(NMDIA),KC_DEL
                                                               ,F(F_HUN)
                                                               ,KC_LEAD   ,KC_ENT ,KC_SPC
    ),

/* Keymap 2: Arrow layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * |           |      |      |      |      |      |      |           |      |      |      |      |      |      |           |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * |           |      |      |      |      |      |      |           |      |      | Home |  Up  |  End |      |           |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |           |      |      |      |      |      |------|           |------|      | Left | Down | Rght |      |           |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |           |      |      |      |      |      |      |           |      |      |      |      |      |      |           |
 * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
 *      |      |      |      |      |      |                                       |      |      |      |      |      |
 *      `----------------------------------'                                       `----------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         |      |      |           |      |      |
 *                                  ,------|------|------|           |------+------+------.
 *                                  |      |      |      |           |      |      |      |
 *                                  | Enter|      |------|           |------| PgUp | PgDn |
 *                                  |      |      |      |           |      |      |      |
 *                                  `--------------------'           `--------------------'
 */

[ARRW] = LAYOUT_ergodox(
// left hand
 KC_TRNS ,KC_TRNS    ,KC_TRNS   ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS
,KC_TRNS ,KC_TRNS    ,KC_TRNS   ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS
,KC_TRNS ,KC_TRNS    ,KC_TRNS   ,KC_TRNS    ,KC_TRNS    ,KC_TRNS
,KC_TRNS ,KC_TRNS    ,KC_TRNS   ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS
,KC_TRNS ,KC_TRNS    ,KC_TRNS   ,KC_TRNS    ,KC_TRNS

                                             ,KC_TRNS ,KC_TRNS
                                                      ,KC_TRNS
                                    ,KC_ENT  ,KC_TRNS ,KC_TRNS

                                                                // right hand
                                                               ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
                                                               ,KC_TRNS ,KC_TRNS ,KC_HOME ,KC_UP   ,KC_END  ,KC_TRNS ,KC_TRNS
                                                                        ,KC_TRNS ,KC_LEFT ,KC_DOWN ,KC_RGHT ,KC_TRNS ,KC_TRNS
                                                               ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
                                                                                 ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS

                                                               ,KC_TRNS ,KC_TRNS
                                                               ,KC_TRNS
                                                               ,KC_TRNS ,KC_PGUP ,KC_PGDN
    ),

/* Keymap 3: Application select layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * |           |Music |Slack |Emacs |Term  |Chrome|      |           |      |      |      |      |      |      |           |
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

[APPSEL] = LAYOUT_ergodox(
// left hand
 KC_TRNS ,M(APP_MSIC),M(APP_SLK),M(APP_EMCS),M(APP_TERM),M(APP_CHRM),KC_TRNS
,KC_TRNS ,KC_TRNS    ,KC_TRNS   ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS
,KC_TRNS ,KC_TRNS    ,KC_TRNS   ,KC_TRNS    ,KC_TRNS    ,KC_TRNS
,KC_TRNS ,KC_TRNS    ,KC_TRNS   ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS
,KC_TRNS ,KC_TRNS    ,KC_TRNS   ,KC_TRNS    ,KC_TRNS

                                             ,KC_TRNS ,KC_TRNS
                                                      ,KC_TRNS
                                    ,KC_TRNS ,KC_TRNS ,KC_TRNS

                                                                // right hand
                                                               ,KC_TRNS ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_TRNS
                                                               ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
                                                                        ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
                                                               ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
                                                                                 ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS

                                                               ,KC_TRNS ,KC_TRNS
                                                               ,KC_TRNS
                                                               ,KC_TRNS ,KC_TRNS  ,KC_TRNS
    ),


/* Keymap 4: Hungarian Layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * |           |      |      |      |      |      |      |           |      |      |      |      |      |      |           |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * |           |      |  Ő   |      |  Ű   |      |      |           |      |      |      |      |      |      |           |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |           |   Á  |  Ó   |  É   |  Ú   |  Í   |------|           |------|      |      |      |      |      |           |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |           |      |  Ö   |      |  Ü   |      |      |           |      |      |      |      |      |      |           |
 * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
 *      |      |      |      |      |      |                                       |      |      |      |      |      |
 *      `----------------------------------'                                       `----------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         |      |      |           |      |      |
 *                                  ,------|------|------|           |------+------+------.
 *                                  |      |      |      |           |      |      |      |
 *                                  |      |      |------|           |------|      |      |
 *                                  |      |      |      |           | BASE |      |      |
 *                                  `--------------------'           `--------------------'
 */

[HUN] = LAYOUT_ergodox(
// left hand
 KC_NO   ,KC_NO   ,KC_NO    ,KC_NO   ,KC_NO    ,KC_NO   ,KC_NO
,KC_NO   ,KC_NO   ,M(HU_OEE),KC_NO   ,M(HU_UEE),KC_NO   ,KC_NO
,KC_NO   ,M(HU_AA),M(HU_OO) ,M(HU_EE),M(HU_UU) ,M(HU_II)
,KC_NO   ,KC_NO   ,M(HU_OE) ,KC_NO   ,M(HU_UE) ,KC_NO   ,KC_NO
,KC_NO   ,KC_NO   ,KC_NO    ,KC_NO   ,KC_NO

                                             ,KC_NO   ,KC_NO
                                                      ,KC_NO
                                    ,KC_NO   ,KC_TRNS ,KC_TRNS

                                                                // right hand
                                                               ,KC_TRNS ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO
                                                               ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO
                                                                        ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO
                                                               ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO
                                                                                 ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO

                                                               ,KC_NO   ,KC_NO
                                                               ,KC_NO
                                                               ,F(F_BSE),KC_TRNS  ,KC_TRNS
    ),

/* Keymap 5: Navigation & Media layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * |           |  F9  |  F7  |  F5  |  F3  |  F1  |ScrLCK|           |      | F10  |  F2  |  F4  |  F6  |  F8  |           |
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
 *                                         | Mute | VlUp |           | BASE |      |
 *                                  ,------|------|------|           |------+------+------.
 *                                  |      |      | VlDn |           |      |      |      |
 *                                  |      |      |------|           |------|      |      |
 *                                  |      |      |      |           |      |      |      |
 *                                  `--------------------'           `--------------------'
 */
[NMDIA] = LAYOUT_ergodox(
// left hand
 KC_NO      ,KC_F9       ,KC_F7      ,KC_F5   ,KC_F3   ,KC_F1   ,LGUI(KC_L)
,KC_NO      ,KC_NO       ,KC_NO      ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO
,KC_NO      ,KC_NO       ,KC_NO      ,KC_NO   ,KC_NO   ,KC_NO
,KC_NO      ,KC_NO       ,KC_NO      ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO
,KC_NO      ,KC_NO       ,KC_NO      ,KC_NO   ,KC_NO
                                                        ,KC_MUTE ,KC_VOLU
                                                                 ,KC_VOLD
                                                 ,KC_NO ,KC_NO   ,KC_TRNS

                                                                     // right hand
                                                                     ,KC_TRNS   ,KC_F10  ,KC_F2   ,KC_F4   ,KC_F6   ,KC_F8    ,KC_NO
                                                                     ,KC_NO     ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO    ,KC_NO
                                                                                ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO    ,KC_NO
                                                                     ,KC_NO     ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO    ,KC_NO
                                                                                         ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO    ,KC_NO

                                                                     ,KC_TRNS   ,KC_NO
                                                                     ,KC_NO
                                                                     ,KC_NO     ,KC_NO   ,KC_NO
    ),

/* Keymap 6: Steno for Plover
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |  BASE  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   #  |   #  |   #  |   #  |   #  |   #  |           |  #   |  #   |  #   |   #  |   #  |  #   |   #    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |   T  |   P  |   H  |      |------|           |------|      |  F   |   P  |   L  |  T   |   D    |
 * |--------+   S  +------+------+------+   *  |   *  |           |  *   |  *   +------+------+------+------+--------|
 * |        |      |   K  |   W  |   R  |      |      |           |      |      |  R   |   B  |   G  |  S   |   Z    |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |   A  |   O  |------|       |------|  E   |  U   |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */

[PLVR] = LAYOUT_ergodox(
// left hand
KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO,  KC_NO,   KC_NO,
KC_NO,  PV_NUM, PV_NUM, PV_NUM,  PV_NUM, PV_NUM,  PV_NUM,
KC_NO,  PV_LS,  PV_LT,  PV_LP,   PV_LH,  PV_STAR,
KC_NO,  PV_LS,  PV_LK,  PV_LW,   PV_LR,  PV_STAR, PV_STAR,
KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO,
                                           KC_NO, KC_NO,
                                           KC_NO,
                                           PV_A,  PV_O,  KC_NO,

                                                 // right hand
                                                 KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   M(A_PLVR),
                                                 PV_NUM,  PV_NUM,  PV_NUM,  PV_NUM,  PV_NUM,  PV_NUM,  PV_NUM,
                                                          PV_STAR, PV_RF,   PV_RP,   PV_RL,   PV_RT,   PV_RD,
                                                 PV_STAR, PV_STAR, PV_RR,   PV_RB,   PV_RG,   PV_RS,   PV_RZ,
                                                                   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                                           KC_NO,      KC_NO,
                                           KC_NO,
                                           KC_NO,PV_E, PV_U
 ),

};

const uint16_t PROGMEM fn_actions[] = {
   [F_BSE]  = ACTION_LAYER_CLEAR(ON_PRESS)
  ,[F_HUN]  = ACTION_LAYER_INVERT(HUN, ON_PRESS)
  ,[F_GUI]  = ACTION_MACRO_TAP(A_GUI)
  ,[F_SFT]  = ACTION_MODS_ONESHOT (MOD_LSFT)
  ,[F_ALT]  = ACTION_MODS_ONESHOT (MOD_LALT)
  ,[F_CTRL] = ACTION_MODS_ONESHOT (MOD_LCTL)
};

static void toggle_steno(int pressed)
{
  uint8_t layer = biton32(layer_state);

  if (pressed) {
    if (layer != PLVR) layer_on(PLVR); else layer_off(PLVR);

    register_code(PV_LP);
    register_code(PV_LH);
    register_code(PV_LR);
    register_code(PV_O);
    register_code(PV_RL);
    register_code(PV_RG);
  } else {
    unregister_code(PV_LP);
    unregister_code(PV_LH);
    unregister_code(PV_LR);
    unregister_code(PV_O);
    unregister_code(PV_RL);
    unregister_code(PV_RG);
  }
}

static macro_t *ang_do_hun (keyrecord_t *record, uint16_t accent, uint16_t hun_char)
{
  uint8_t need_shift = 0;
  uint8_t hold_shift = 0;

  if (!record->event.pressed)
    return MACRO_NONE;

  layer_off (HUN);

  if (keyboard_report->mods & MOD_BIT (KC_LSFT)) {
    hold_shift = 1;
    need_shift = 1;
    unregister_code (KC_LSFT);
  }
  if ((get_oneshot_mods () & MOD_BIT(KC_LSFT)) && !has_oneshot_mods_timed_out ()) {
    need_shift = 1;
    hold_shift = 0;
    unregister_code (KC_LSFT);
  }

  clear_oneshot_mods ();

  register_code (KC_RALT);
  unregister_code (KC_RALT);
  if (accent == (KC_DQT)) {
    register_code (KC_RSFT);
  }
  register_code (accent);
  unregister_code (accent);
  if (need_shift && accent != (KC_DQT)) {
    register_code (KC_RSFT);
  } else if (accent == (KC_DQT) && !need_shift) {
    unregister_code (KC_RSFT);
  }
  register_code (hun_char);
  unregister_code (hun_char);
  if (need_shift || accent == (KC_DQT))
    unregister_code (KC_RSFT);
  if (hold_shift)
    register_code (KC_LSFT);

  return MACRO_NONE;
}

static void ang_handle_num_row(uint8_t id, keyrecord_t *record) {
  uint8_t idx = id - A_1;
  uint8_t kc;
  static bool shifted[10];

  if (keyboard_report->mods & MOD_BIT(KC_LSFT) ||
      ((get_oneshot_mods() & MOD_BIT(KC_LSFT)) && !has_oneshot_mods_timed_out())) {
    if (record->event.pressed)
      shifted[idx] = true;
  }

  if (!shifted[idx]) {
    kc = idx + KC_1;
  } else {
    switch (id) {
    case A_8:
    case A_9:
      shifted[idx] = false;
      return;

    case A_7:
      kc = KC_2;
      break;
    case A_5:
      kc = KC_8;
      break;
    case A_3:
      kc = KC_6;
      break;
    case A_1:
      kc = KC_4;
      break;

    case A_0:
      kc = KC_5;
      break;
    case A_2:
      kc = KC_1;
      break;
    case A_4:
      kc = KC_3;
      break;
    case A_6:
      kc = KC_7;
      break;
    }
  }

  if (record->event.pressed) {
    register_code (kc);
  } else {
    unregister_code (kc);
    shifted[idx] = false;
  }
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
      case A_MPN:
        if (record->event.pressed) {
          if (keyboard_report->mods & MOD_BIT(KC_LSFT) ||
              ((get_oneshot_mods() & MOD_BIT(KC_LSFT)) && !has_oneshot_mods_timed_out())) {
            int oneshot = ((get_oneshot_mods() & MOD_BIT(KC_LSFT)) && !has_oneshot_mods_timed_out());

            if (oneshot)
              clear_oneshot_mods ();
            unregister_code (KC_LSFT);

            register_code (KC_MPRV);
            unregister_code (KC_MPRV);

            if (!oneshot)
              register_code (KC_LSFT);
          } else {
            return MACRO (T(MNXT), END);
          }
        }
        break;

        /* Hungarian layer */
      case HU_AA:
        return ang_do_hun (record, KC_QUOT, KC_A);
      case HU_OO:
        return ang_do_hun (record, KC_QUOT, KC_O);
      case HU_EE:
        return ang_do_hun (record, KC_QUOT, KC_E);
      case HU_UU:
        return ang_do_hun (record, KC_QUOT, KC_U);
      case HU_II:
        return ang_do_hun (record, KC_QUOT, KC_I);
      case HU_OE:
        return ang_do_hun (record, KC_DQT, KC_O);
      case HU_UE:
        return ang_do_hun (record, KC_DQT, KC_U);
      case HU_OEE:
        return ang_do_hun (record, KC_EQL, KC_O);
      case HU_UEE:
        return ang_do_hun (record, KC_EQL, KC_U);

        /* Plover base */
      case A_PLVR:
        toggle_steno(record->event.pressed);
        break;

        /* Fx */
      case Fx:
        if (record->event.pressed) {
          set_oneshot_mods (MOD_LALT);
          layer_on (NMDIA);
          set_oneshot_layer (NMDIA, ONESHOT_START);
        } else {
          clear_oneshot_layer_state (ONESHOT_PRESSED);
        }
        break;

        /* GUI & AppSel */
      case A_GUI:
        if (record->event.pressed) {
          register_code (KC_LGUI);
          if (record->tap.count && !record->tap.interrupted) {
            if (record->tap.count >= 2) {
              uprintf("CMD:appsel_start\n");
              layer_on (APPSEL);
              set_oneshot_layer (APPSEL, ONESHOT_START);
            }
          } else {
            record->tap.count = 0;
          }
          gui_timer = 0;
        } else {
          if (record->tap.count >= 2)
            {
              clear_oneshot_layer_state (ONESHOT_PRESSED);
            }
          gui_timer = timer_read ();
        }
        break;

      case APP_SLK:
        if (record->event.pressed)
          uprintf("CMD:appsel_slack\n");
        break;

      case APP_EMCS:
        if (record->event.pressed)
          uprintf("CMD:appsel_emacs\n");
        break;

      case APP_TERM:
        if (record->event.pressed)
          uprintf("CMD:appsel_term\n");
        break;

      case APP_CHRM:
        if (record->event.pressed)
          uprintf("CMD:appsel_chrome\n");
        break;

      case APP_MSIC:
        if (record->event.pressed)
          uprintf("CMD:appsel_music\n");
        break;

        // number row and symbols
      case A_1 ... A_0:
        ang_handle_num_row(id, record);
        break;
      }

      return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
  uint8_t dl;

  set_unicode_input_mode(UC_LNX);

  ergodox_led_all_on();
  for (int i = LED_BRIGHTNESS_HI; i > LED_BRIGHTNESS_LO; i--) {
    ergodox_led_all_set (i);
    wait_ms (5);
  }
  wait_ms(1000);
  for (int i = LED_BRIGHTNESS_LO; i > 0; i--) {
    ergodox_led_all_set (i);
    wait_ms (10);
  }
  ergodox_led_all_off();

  if (!eeconfig_is_enabled())
    eeconfig_init();
  dl = eeconfig_read_default_layer ();
  if (dl == (1UL << ADORE)) {
    is_adore = 1;
  }
};

LEADER_EXTERNS();

static void ang_tap (uint16_t code, ...) {
  uint16_t kc = code;
  va_list ap;

  va_start(ap, code);

  do {
    register_code16(kc);
    unregister_code16(kc);
    wait_ms(50);
    kc = va_arg(ap, int);
  } while (kc != 0);
  va_end(ap);
}

#define TAP_ONCE(code)  \
  register_code (code); \
  unregister_code (code)

typedef struct {
  bool layer_toggle;
  bool sticky;
} td_ta_state_t;

static void ang_tap_dance_ta_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_ta_state_t *td_ta = (td_ta_state_t *) user_data;

  if (td_ta->sticky) {
    td_ta->sticky = false;
    td_ta->layer_toggle = false;
    layer_off (ARRW);
    return;
  }

  if (state->count == 1 && !state->pressed) {
    register_code (KC_TAB);
    td_ta->sticky = false;
    td_ta->layer_toggle = false;
  } else {
    td_ta->layer_toggle = true;
    layer_on (ARRW);
    td_ta->sticky = (state->count == 2);
  }
}

static void ang_tap_dance_ta_reset (qk_tap_dance_state_t *state, void *user_data) {
  td_ta_state_t *td_ta = (td_ta_state_t *) user_data;

  if (!td_ta->layer_toggle)
    unregister_code (KC_TAB);
  if (!td_ta->sticky)
    layer_off (ARRW);
}

static void ang_tap_dance_tmux_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code(KC_LALT);
    register_code(KC_SPC);
    unregister_code(KC_SPC);
    unregister_code(KC_LALT);
  } else {
    register_code(KC_LCTL);
    register_code(KC_A);
    unregister_code(KC_A);
    unregister_code(KC_LCTL);
  }
}

static void ang_tap_dance_tmux_pane_select (qk_tap_dance_state_t *state, void *user_data) {
  uint8_t kc = KC_P;

  if (state->count >= 2) {
    kc = KC_Z;
  }

  register_code(KC_LALT);
  register_code(KC_SPC);
  unregister_code(KC_SPC);
  unregister_code(KC_LALT);

  register_code(kc);
  unregister_code(kc);
}

static void
_td_sr_each (qk_tap_dance_state_t *state, void *user_data) {
  skip_leds = true;

  switch (state->count) {
  case 1:
    ergodox_right_led_3_on ();
    break;
  case 2:
    ergodox_right_led_2_on ();
    break;
  case 3:
    ergodox_right_led_1_on ();
    break;
  case 4:
    ergodox_right_led_3_off ();
    wait_ms (50);
    ergodox_right_led_2_off ();
    wait_ms (50);
    ergodox_right_led_1_off ();
    break;
  }
}

static void
_td_sr_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_MSTP);
  }
  if (state->count >= 4) {
    uprintf("CMD:reflash\n");
    wait_ms (1000);
    reset_keyboard ();
    reset_tap_dance (state);
  }
}

static void
_td_sr_reset (qk_tap_dance_state_t *state, void *user_data) {
  ergodox_right_led_1_off ();
  wait_ms (50);
  ergodox_right_led_2_off ();
  wait_ms (50);
  ergodox_right_led_3_off ();

  if (state->count == 1) {
    unregister_code (KC_MSTP);
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
   [CT_CLN] = ACTION_TAP_DANCE_DOUBLE (KC_COLN, KC_SCLN)
  ,[CT_TA]  = {
     .fn = { NULL, ang_tap_dance_ta_finished, ang_tap_dance_ta_reset },
     .user_data = (void *)&((td_ta_state_t) { false, false })
   }
  ,[CT_LBP] = ACTION_TAP_DANCE_DOUBLE (KC_LBRC, KC_LPRN)
  ,[CT_RBP] = ACTION_TAP_DANCE_DOUBLE (KC_RBRC, KC_RPRN)
  ,[CT_TMUX]= ACTION_TAP_DANCE_FN (ang_tap_dance_tmux_finished)
  ,[CT_TPS] = ACTION_TAP_DANCE_FN (ang_tap_dance_tmux_pane_select)
  ,[CT_SR]  = ACTION_TAP_DANCE_FN_ADVANCED (_td_sr_each, _td_sr_finished, _td_sr_reset)
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
  uint8_t layer = biton32(layer_state);
  bool is_arrow = false;

  if (gui_timer && timer_elapsed (gui_timer) > TAPPING_TERM)
    unregister_code (KC_LGUI);

  if (!skip_leds) {
    if (layer == HUN) {
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();
    } else if (layer == NMDIA) {
      ergodox_right_led_1_on();
      ergodox_right_led_2_on();
    } else if (layer == PLVR) {
      ergodox_right_led_1_on ();
      ergodox_right_led_2_on ();
      ergodox_right_led_3_on ();
    } else if (layer == ADORE) {
      ergodox_right_led_1_on ();
      ergodox_right_led_2_on ();
      ergodox_right_led_3_on ();

      ergodox_right_led_2_set (LED_BRIGHTNESS_HI);
    }
  }

  if (layer_state & (1UL << ARRW)) {
    if (!skip_leds) {
      ergodox_right_led_1_on ();
      ergodox_right_led_3_on ();
    }
    is_arrow = true;
  }

  if (!skip_leds) {
    if (keyboard_report->mods & MOD_BIT(KC_LSFT) ||
        ((get_oneshot_mods() & MOD_BIT(KC_LSFT)) && !has_oneshot_mods_timed_out())) {
      ergodox_right_led_1_set (LED_BRIGHTNESS_HI);
      ergodox_right_led_1_on ();
    } else {
      ergodox_right_led_1_set (LED_BRIGHTNESS_LO);
      if (layer != NMDIA && layer != PLVR && layer != ADORE && !is_arrow)
        ergodox_right_led_1_off ();
    }

    if (keyboard_report->mods & MOD_BIT(KC_LALT) ||
        ((get_oneshot_mods() & MOD_BIT(KC_LALT)) && !has_oneshot_mods_timed_out())) {
      ergodox_right_led_2_set (LED_BRIGHTNESS_HI);
      ergodox_right_led_2_on ();
    } else {
      ergodox_right_led_2_set (LED_BRIGHTNESS_LO);
      if (layer != HUN && layer != NMDIA && layer != PLVR && layer != ADORE)
        ergodox_right_led_2_off ();
    }

    if (keyboard_report->mods & MOD_BIT(KC_LCTRL) ||
        ((get_oneshot_mods() & MOD_BIT(KC_LCTRL)) && !has_oneshot_mods_timed_out())) {
      ergodox_right_led_3_set (LED_BRIGHTNESS_HI);
      ergodox_right_led_3_on ();
    } else {
      ergodox_right_led_3_set (LED_BRIGHTNESS_LO);
      if (layer != HUN && layer != PLVR && layer != ADORE && !is_arrow)
        ergodox_right_led_3_off ();
    }
  }

  LEADER_DICTIONARY() {
    leading = false;
    leader_end ();

    SEQ_ONE_KEY (KC_C) {
      ang_tap (LSFT(KC_C), KC_S, KC_I, KC_L, KC_L, KC_RALT, KC_QUOT, KC_A, KC_M, KC_A, KC_S,
               KC_S, KC_Z, KC_O, KC_N, KC_Y, KC_K, KC_RALT, KC_QUOT, KC_A, KC_M, 0);
    }

    SEQ_ONE_KEY (KC_G) {
      ang_tap (LSFT(KC_G), KC_E, KC_J, KC_G, KC_RALT, KC_EQL, KC_O,
               KC_RALT, KC_EQL, KC_O,
               KC_RALT, KC_EQL, KC_O, 0);
    }

#if KEYLOGGER_ENABLE
    SEQ_ONE_KEY (KC_D) {
      ergodox_led_all_on();
      wait_ms(100);
      ergodox_led_all_off();
      log_enable = !log_enable;
    }
#endif

    SEQ_ONE_KEY (KC_T) {
      time_travel = !time_travel;
    }

    SEQ_ONE_KEY (KC_U) {
      qk_ucis_start();
    }

    SEQ_ONE_KEY (KC_V) {
      SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ (" QMK_VERSION "/" LAYOUT_ergodox_VERSION ")");
    }

    SEQ_ONE_KEY (KC_L) {
      /* λ */
      unicode_input_start();
      register_hex(0x03bb);
      unicode_input_finish();
    }

    SEQ_ONE_KEY (KC_Y) {
      ang_tap (KC_BSLS, KC_O, KC_SLSH, 0);
    }

    SEQ_ONE_KEY (KC_S) {
      unicode_input_start(); register_hex(0xaf); unicode_input_finish();
      TAP_ONCE (KC_BSLS);
      register_code (KC_RSFT); TAP_ONCE (KC_MINS); TAP_ONCE (KC_9); unregister_code (KC_RSFT);
      unicode_input_start (); register_hex(0x30c4); unicode_input_finish();
      register_code (KC_RSFT); TAP_ONCE (KC_0); TAP_ONCE (KC_MINS); unregister_code (KC_RSFT);
      TAP_ONCE (KC_SLSH);
      unicode_input_start (); register_hex(0xaf); unicode_input_finish();
    }

    SEQ_TWO_KEYS (KC_W, KC_M) {
      uprintf("CMD:wm\n");
    }

    SEQ_ONE_KEY (KC_A) {
      if (is_adore == 0) {
        default_layer_and (0);
        default_layer_or ((1UL << ADORE));
        eeconfig_update_default_layer ((1UL << ADORE));
        is_adore = 1;

        ergodox_led_all_off ();
        ergodox_right_led_3_on ();
        wait_ms (100);
        ergodox_right_led_2_on ();
        wait_ms (100);
        ergodox_right_led_3_off ();
        ergodox_right_led_1_on ();
        wait_ms (100);
        ergodox_right_led_2_off ();
        wait_ms (100);
        ergodox_right_led_1_off ();
      } else {
        is_adore = 0;
        default_layer_and (0);
        default_layer_or (1UL << BASE);
        eeconfig_update_default_layer ((1UL << BASE));

        ergodox_led_all_off ();
        ergodox_right_led_1_on ();
        wait_ms (100);
        ergodox_right_led_2_on ();
        wait_ms (100);
        ergodox_right_led_1_off ();
        ergodox_right_led_3_on ();
        wait_ms (100);
        ergodox_right_led_2_off ();
        wait_ms (100);
        ergodox_right_led_3_off ();
      }
    }
  }
}

static uint16_t last4[4];

const qk_ucis_symbol_t ucis_symbol_table[] = UCIS_TABLE
(
 UCIS_SYM("poop", 0x1f4a9),
 UCIS_SYM("rofl", 0x1f923),
 UCIS_SYM("kiss", 0x1f619),
 UCIS_SYM("snowman", 0x2603),
 UCIS_SYM("coffee", 0x2615),
 UCIS_SYM("heart", 0x2764),
 UCIS_SYM("bolt", 0x26a1),
 UCIS_SYM("pi", 0x03c0),
 UCIS_SYM("mouse", 0x1f401),
 UCIS_SYM("micro", 0x00b5),
 UCIS_SYM("tm", 0x2122)
);

bool process_record_user (uint16_t keycode, keyrecord_t *record) {
#if KEYLOGGER_ENABLE
  if (log_enable) {
    uint8_t layer = biton32(layer_state);

    if ((layer == ADORE) || (layer == BASE))
      uprintf ("KL: col=%02d, row=%02d, pressed=%d, layer=%s\n", record->event.key.col,
               record->event.key.row, record->event.pressed, (is_adore) ? "ADORE" : "Dvorak");
  }
#endif

  if (keycode == KC_ESC && record->event.pressed) {
    bool queue = true;

    if ((get_oneshot_mods ()) && !has_oneshot_mods_timed_out ()) {
      clear_oneshot_mods ();
      queue = false;
    }
    if (layer_state & (1UL<<HUN)) {
      layer_off (HUN);
      queue = false;
    }
    return queue;
  }

  if (time_travel && !record->event.pressed) {
    uint8_t p;

    // shift cache one to the left
    for (p = 0; p < 3; p++) {
      last4[p] = last4[p + 1];
    }
    last4[3] = keycode;

    if (last4[0] == KC_D && last4[1] == KC_A && last4[2] == KC_T && last4[3] == KC_E) {
      ang_tap (KC_E, KC_SPC, KC_MINS, KC_D, KC_SPC, KC_QUOT, 0);
      register_code (KC_RSFT);
      register_code (KC_EQL);
      unregister_code (KC_EQL);
      unregister_code (KC_RSFT);

      ang_tap (KC_4, KC_SPC, KC_D, KC_A, KC_Y, KC_S, KC_QUOT, 0);

      return false;
    }
  }

  return true;
}

void qk_ucis_symbol_fallback (void) {
  for (uint8_t i = 0; i < qk_ucis_state.count - 1; i++) {
    uint8_t code;

    if ((qk_ucis_state.codes[i] >= M(A_1)) && (qk_ucis_state.codes[i] <= M(A_0)))
      code = qk_ucis_state.codes[i] - M(A_1) + KC_1;
    else
      code = qk_ucis_state.codes[i];
    register_code(code);
    unregister_code(code);
    wait_ms (10);
  }
}
