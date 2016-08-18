/*
 * algernon's ErgoDox EZ layout, please see the readme.md file!
 */

#include "ergodox.h"
#include "led.h"
#include "debug.h"
#include "action_layer.h"
#include "action_util.h"
#include "mousekey.h"
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
  A_ESC,
  A_MPN,

  // Function / number keys
  KF_1, // 1, F1
  KF_2, // 2, F2
  KF_3, // ...
  KF_4,
  KF_5,
  KF_6,
  KF_7,
  KF_8,
  KF_9,
  KF_10,
  KF_11, // =, F11

  // Application select keys
  APP_SLK, // Slack
  APP_EMCS, // Emacs
  APP_TERM, // Terminal
  APP_CHRM, // Chrome
  APP_MSIC, // Music

  // Diagonal mouse movement
  A_MUL,
  A_MUR,
  A_MDL,
  A_MDR,

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
  CT_MNS,
  CT_TA,
  CT_LBP,
  CT_RBP
};

/* States & timers */

uint16_t gui_timer = 0;

uint16_t kf_timers[12];

#if KEYLOGGER_ENABLE
bool log_enable = false;
#endif

bool time_travel = false;

/* The Keymap */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Keymap 0: Base Layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * | Next/Prev | 1 F1 | 2 F2 | 3 F3 | 4 F4 | 5 F5 | Plvr |           | Apps | 6 F6 | 7 F7 | 8 F8 | 9 F9 | 0 F10|       F11 |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * |         ~ |   '  |   ,  |   .  |   P  |   Y  |   [  |           |  ]   |   F  |   G  |   C  |   R  |  L   | \         |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * | Tab/ARROW |   A  |   O  |   E  |   U  |   I  |------|           |------|   D  |   H  |   T  |   N  |  S   | = / Arrow |
 * |-----------+------+------+------+------+------|   (  |           |  )   |------+------+------+------+------+-----------|
 * | Play/Pause|   /  |   Q  |   J  |   K  |   X  |      |           |      |   B  |   M  |   W  |   V  |  Z   |      Stop |
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
[BASE] = KEYMAP(
// left hand
 M(A_MPN)           ,M(KF_1)     ,M(KF_2)     ,M(KF_3),M(KF_4),M(KF_5),M(A_PLVR)
,KC_GRV             ,KC_QUOT     ,KC_COMM     ,KC_DOT ,KC_P   ,KC_Y   ,KC_LBRC
,TD(CT_TA)          ,KC_A        ,KC_O        ,KC_E   ,KC_U   ,KC_I
,KC_MPLY            ,KC_SLSH     ,KC_Q        ,KC_J   ,KC_K   ,KC_X   ,KC_LPRN
,KC_NO              ,KC_NO       ,KC_NO       ,KC_NO  ,TD(CT_CLN)

                                                            ,F(F_ALT),F(F_GUI)
                                                                     ,F(F_CTRL)
                                                    ,KC_BSPC,F(F_SFT),M(A_ESC)

                                                                // right hand
                                                               ,KC_APP    ,M(KF_6),M(KF_7)   ,M(KF_8),M(KF_9) ,M(KF_10) ,KC_F11
                                                               ,KC_RBRC   ,KC_F   ,KC_G      ,KC_C   ,KC_R    ,KC_L     ,KC_BSLS
                                                                          ,KC_D   ,KC_H      ,KC_T   ,KC_N    ,KC_S     ,KC_EQL
                                                               ,KC_RPRN   ,KC_B   ,KC_M      ,KC_W   ,KC_V    ,KC_Z     ,KC_MSTP
                                                                                  ,TD(CT_MNS),KC_NO  ,KC_NO   ,KC_NO    ,KC_NO

                                                               ,OSL(NMDIA),KC_DEL
                                                               ,KC_LEAD
                                                               ,F(F_HUN)  ,KC_ENT ,KC_SPC
    ),

/* Keymap 1: Adore layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * | Play/Pause| 1 F1 | 2 F2 | 3 F3 | 4 F4 | 5 F5 | Plvr |           | Apps | 6 F6 | 7 F7 | 8 F8 | 9 F9 | 0 F10|       F11 |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * |        `~ |   X  |   W  |   K  |   L  |   M  |   (  |           |  )   |   F  |   H  |   C  |   P  |  Y   | \         |
 * |-----------+------+------+------+------+------|   [  |           |  ]   |------+------+------+------+------+-----------|
 * | Tab/Arrow |   A  |   O  |   E  |   I  |   U  |------|           |------|   D  |   R  |   T  |   N  |  S   | =         |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |           |   Z  |   Q  |   '  |   ,  |   .  |   :  |           |  -   |   B  |   G  |   V  |   J  |  /   |           |
 * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
 *     |       |      |      |      |      |                                       |      |      |      |      |       |
 *     `-----------------------------------'                                       `-----------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         | LAlt | GUI  |           | MDIA | Del  |
 *                                  ,------|------|------|           |------+------+------.
 *                                  |      |      | Ctrl |           | HUN  |      |      |
 *                                  |Backsp|LShift|------|           |------| Enter| Space|
 *                                  |      |      | ESC  |           | LEAD |      |      |
 *                                  `--------------------'           `--------------------'
 */
[ADORE] = KEYMAP(
// left hand
 KC_MPLY            ,M(KF_1)     ,M(KF_2)     ,M(KF_3),M(KF_4),M(KF_5),M(A_PLVR)
,KC_GRV             ,KC_X        ,KC_W        ,KC_K   ,KC_L   ,KC_M   ,TD(CT_LBP)
,TD(CT_TA)          ,KC_A        ,KC_O        ,KC_E   ,KC_I   ,KC_U
,KC_NO              ,KC_Z        ,KC_Q        ,KC_QUOT,KC_COMM,KC_DOT ,TD(CT_CLN)
,KC_NO              ,KC_NO       ,KC_NO       ,KC_NO  ,KC_NO

                                                            ,F(F_ALT),F(F_GUI)
                                                                     ,F(F_CTRL)
                                                    ,KC_BSPC,F(F_SFT),M(A_ESC)

                                                                // right hand
                                                               ,KC_APP    ,M(KF_6),M(KF_7),M(KF_8),M(KF_9) ,M(KF_10) ,KC_F11
                                                               ,TD(CT_RBP),KC_F   ,KC_H   ,KC_C   ,KC_P    ,KC_Y     ,KC_BSLS
                                                                          ,KC_D   ,KC_R   ,KC_T   ,KC_N    ,KC_S     ,KC_EQL
                                                               ,TD(CT_MNS),KC_B   ,KC_G   ,KC_V   ,KC_J    ,KC_SLSH  ,KC_NO
                                                                                  ,KC_NO  ,KC_NO  ,KC_NO   ,KC_NO    ,KC_NO

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

[ARRW] = KEYMAP(
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

[APPSEL] = KEYMAP(
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

[HUN] = KEYMAP(
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
 * | MS Slow   |      |      |      |      |      |ScrLCK|           |ScrLCK|      |      |      |      |      |           |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * | MS Normal |      | Home |  Up  | PgUp |      |      |           |Scroll|      |MsUpL | MsUp |MsUpR |      |PrintScreen|
 * |-----------+------+------+------+------+------|      |           |  Up  |------+------+------+------+------+-----------|
 * | MS Fast   |      | Left | Down | Right|      |------|           |------|      |MsLeft| MsDn |MsRght|      |           |
 * |-----------+------+------+------+------+------|      |           |Scroll|------+------+------+------+------+-----------|
 * | Play/Pause|      | End  | Down | PgDn |      |      |           | Down |      |MsDnL | MsDn |MsDnR |      |      Stop |
 * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
 *      |      |      |      |      |      |                                       |      |      |      |      |      |
 *      `----------------------------------'                                       `----------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         | Mute | VlUp |           | BASE | MClk |
 *                                  ,------|------|------|           |------+------+------.
 *                                  |      |      | VlDn |           | Prev |Left  |Right |
 *                                  |  SPC | Enter|------|           |------| Click| Click|
 *                                  |      |      | ESC  |           | Next |      |      |
 *                                  `--------------------'           `--------------------'
 */
[NMDIA] = KEYMAP(
// left hand
 KC_ACL0    ,KC_NO       ,KC_NO      ,KC_NO   ,KC_NO   ,KC_NO   ,LGUI(KC_L)
,KC_ACL1    ,KC_NO       ,KC_HOME    ,KC_UP   ,KC_PGUP ,KC_NO   ,KC_NO
,KC_ACL2    ,KC_NO       ,KC_LEFT    ,KC_DOWN ,KC_RIGHT,KC_NO
,KC_MPLY    ,KC_NO       ,KC_END     ,KC_DOWN ,KC_PGDN ,KC_NO   ,KC_NO
,KC_NO      ,KC_NO       ,KC_NO      ,KC_NO   ,KC_NO
                                                        ,KC_MUTE ,KC_VOLU
                                                                 ,KC_VOLD
                                                 ,KC_SPC,KC_ENTER,M(A_ESC)

                                                                     // right hand
                                                                     ,LGUI(KC_L),KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO    ,KC_NO
                                                                     ,KC_WH_U   ,KC_NO   ,M(A_MUL),KC_MS_U ,M(A_MUR),KC_NO    ,KC_PSCR
                                                                                ,KC_NO   ,KC_MS_L ,KC_MS_D ,KC_MS_R ,KC_NO    ,KC_NO
                                                                     ,KC_WH_D   ,KC_NO   ,M(A_MDL),KC_MS_D ,M(A_MDR),KC_NO    ,KC_MSTP
                                                                                         ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO    ,KC_NO

                                                                     ,KC_TRNS   ,KC_MS_BTN3
                                                                     ,KC_MPRV
                                                                     ,KC_MNXT   ,KC_BTN1 ,KC_BTN2
    ),

/* Keymap 6: Steno for Plover
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      | BASE |           |      |      |      |      |      |      |        |
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

[PLVR] = KEYMAP(
// left hand
KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO,  KC_NO,   M(A_PLVR),
KC_NO,  PV_NUM, PV_NUM, PV_NUM,  PV_NUM, PV_NUM,  PV_NUM,
KC_NO,  PV_LS,  PV_LT,  PV_LP,   PV_LH,  PV_STAR,
KC_NO,  PV_LS,  PV_LK,  PV_LW,   PV_LR,  PV_STAR, PV_STAR,
KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO,
                                           KC_NO, KC_NO,
                                           KC_NO,
                                           PV_A,  PV_O,  KC_NO,

                                                 // right hand
                                                 KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
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

void toggle_steno(int pressed)
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

macro_t *ang_do_hun (keyrecord_t *record, uint16_t accent, uint16_t hun_char)
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

void ang_handle_kf (keyrecord_t *record, uint8_t id)
{
  uint8_t code = id - KF_1;

  if (record->event.pressed) {
    kf_timers[code] = timer_read ();
  } else {
    uint8_t kc;

    if (timer_elapsed (kf_timers[code]) > TAPPING_TERM) {
      // Long press
      kc = KC_F1 + code;
    } else {
      if (id == KF_11)
        kc = KC_EQL;
      else
        kc = KC_1 + code;
    }

    register_code (kc);
    unregister_code (kc);
  }
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
      case A_ESC:
        if (record->event.pressed) {
          if ((get_oneshot_mods ()) && !has_oneshot_mods_timed_out ()) {
            clear_oneshot_mods ();
          } else {
            register_code (KC_ESC);
          }
          layer_off (HUN);
        } else {
          unregister_code (KC_ESC);
        }
        break;

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

        /* Mouse movement */
      case A_MUL:
        if (record->event.pressed) {
          mousekey_on(KC_MS_UP);
          mousekey_on(KC_MS_LEFT);
        } else {
          mousekey_off(KC_MS_UP);
          mousekey_off(KC_MS_LEFT);
        }
        mousekey_send();
        break;

      case A_MUR:
        if (record->event.pressed) {
          mousekey_on(KC_MS_UP);
          mousekey_on(KC_MS_RIGHT);
        } else {
          mousekey_off(KC_MS_UP);
          mousekey_off(KC_MS_RIGHT);
        }
        mousekey_send();
        break;

      case A_MDL:
        if (record->event.pressed) {
          mousekey_on(KC_MS_DOWN);
          mousekey_on(KC_MS_LEFT);
        } else {
          mousekey_off(KC_MS_DOWN);
          mousekey_off(KC_MS_LEFT);
        }
        mousekey_send();
        break;

      case A_MDR:
        if (record->event.pressed) {
          mousekey_on(KC_MS_DOWN);
          mousekey_on(KC_MS_RIGHT);
        } else {
          mousekey_off(KC_MS_DOWN);
          mousekey_off(KC_MS_RIGHT);
        }
        mousekey_send();
        break;

        /* Plover base */
      case A_PLVR:
        toggle_steno(record->event.pressed);
        break;

        /* GUI & AppSel */
      case A_GUI:
        if (record->event.pressed) {
          register_code (KC_LGUI);
          if (record->tap.count && !record->tap.interrupted) {
            if (record->tap.count >= 2) {
              register_code (KC_W);
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
              unregister_code (KC_W);
              clear_oneshot_layer_state (ONESHOT_PRESSED);
            }
          gui_timer = timer_read ();
        }
        break;

      case APP_SLK:
        return MACRODOWN(T(S), T(L), T(A), T(C), T(K), T(ENT), END);

      case APP_EMCS:
        return MACRODOWN(T(G), T(N), T(U), T(SPC), T(E), T(M), T(A), T(C), T(S), T(SPC), T(2), T(4), T(ENT), END);

      case APP_TERM:
        return MACRODOWN(T(T), T(E), T(R), T(M), T(ENT), END);

      case APP_CHRM:
        return MACRODOWN(T(C), T(H), T(R), T(O), T(M), T(ENT), END);

      case APP_MSIC:
        return MACRODOWN(T(R), T(H), T(Y), T(T), T(H), T(M), T(B), T(O), T(X), T(ENT), END);

        /* Function keys */
      case KF_1 ... KF_11:
        ang_handle_kf (record, id);
        break;
      }

      return MACRO_NONE;
};

uint8_t is_adore = 0;

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
  uint8_t dl;

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
#if ADORE_AUTOLOG
    log_enable = true;
#endif
  }
};

LEADER_EXTERNS();

void ang_do_unicode (void) {
  register_code (KC_RCTL);
  register_code (KC_RSFT);
  register_code (KC_U);
  unregister_code (KC_U);
  unregister_code (KC_RSFT);
  unregister_code (KC_RCTL);
  wait_ms (100);
}

void ang_tap (uint16_t codes[]) {
  for (int i = 0; codes[i] != 0; i++) {
    register_code (codes[i]);
    unregister_code (codes[i]);
    wait_ms (50);
  }
}

#define TAP_ONCE(code)  \
  register_code (code); \
  unregister_code (code)

void ang_tap_dance_bp_finished (qk_tap_dance_state_t *state, void *user_data) {
  bool left, parens;

  if (state->count > 2) {
    state->count = 0;
    return;
  }

  if (state->keycode == TD(CT_LBP))
    left = true;
  else
    left = false;

  if (state->count == 1)
    parens = false;
  else
    parens = true;

  if (parens) {
    register_code (KC_RSFT);
    if (left) {
      TAP_ONCE(KC_9);
    } else {
      TAP_ONCE(KC_0);
    }
    unregister_code (KC_RSFT);
  } else {
    if (left) {
      TAP_ONCE (KC_LBRC);
    } else {
      TAP_ONCE (KC_RBRC);
    }
  }
}

void ang_tap_dance_cln_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_RSFT);
    register_code (KC_SCLN);
  } else if (state->count == 2) {
    register_code (KC_SCLN);
  }
}

void ang_tap_dance_cln_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_SCLN);
    unregister_code (KC_RSFT);
  } else if (state->count == 2) {
    unregister_code (KC_SCLN);
  }
}

void ang_tap_dance_mns_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_MINS);
  } else if (state->count == 2) {
    register_code (KC_RSFT);
    register_code (KC_MINS);
  }
}

void ang_tap_dance_mns_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_MINS);
  } else if (state->count == 2) {
    unregister_code (KC_RSFT);
    unregister_code (KC_MINS);
  }
}

typedef struct {
  bool layer_toggle;
  bool sticky;
  bool finished_once;
} td_ta_state_t;

void ang_tap_dance_ta_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_ta_state_t *td_ta = (td_ta_state_t *) user_data;

  if (td_ta->finished_once) {
    return;
  }

  if (td_ta->sticky) {
    td_ta->sticky = false;
    td_ta->layer_toggle = false;
    layer_off (ARRW);
    return;
  }

  td_ta->finished_once = true;
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

void ang_tap_dance_ta_reset (qk_tap_dance_state_t *state, void *user_data) {
  td_ta_state_t *td_ta = (td_ta_state_t *) user_data;

  if (!td_ta->layer_toggle)
    unregister_code (KC_TAB);
  if (!td_ta->sticky)
    layer_off (ARRW);

  td_ta->finished_once = false;
}

qk_tap_dance_action_t tap_dance_actions[] = {
   [CT_CLN] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, ang_tap_dance_cln_finished, ang_tap_dance_cln_reset)
  ,[CT_MNS] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, ang_tap_dance_mns_finished, ang_tap_dance_mns_reset)
  ,[CT_TA]  = {
     .fn = { NULL, ang_tap_dance_ta_finished, ang_tap_dance_ta_reset },
     .user_data = (void *)&((td_ta_state_t) { false, false, false })
   }
  ,[CT_LBP] = ACTION_TAP_DANCE_FN (ang_tap_dance_bp_finished)
  ,[CT_RBP] = ACTION_TAP_DANCE_FN (ang_tap_dance_bp_finished)
};

static uint16_t uni[32];
static uint8_t unicnt;
static bool unimagic = false;

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
  uint8_t layer = biton32(layer_state);

  if (gui_timer && timer_elapsed (gui_timer) > TAPPING_TERM)
    unregister_code (KC_LGUI);

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

  if (keyboard_report->mods & MOD_BIT(KC_LSFT) ||
      ((get_oneshot_mods() & MOD_BIT(KC_LSFT)) && !has_oneshot_mods_timed_out())) {
    ergodox_right_led_1_set (LED_BRIGHTNESS_HI);
    ergodox_right_led_1_on ();
  } else {
    ergodox_right_led_1_set (LED_BRIGHTNESS_LO);
    if (layer != NMDIA && layer != PLVR && layer != ADORE)
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
    if (layer != HUN && layer != PLVR && layer != ADORE)
      ergodox_right_led_3_off ();
  }

  LEADER_DICTIONARY() {
    leading = false;
    leader_end ();

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
      ang_do_unicode ();
    }

    SEQ_TWO_KEYS (KC_LEAD, KC_U) {
      unicnt = 0;
      unimagic = true;
      register_code(KC_RSFT);
      TAP_ONCE(KC_U);
      unregister_code(KC_RSFT);
    }

    SEQ_ONE_KEY (KC_V) {
      SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ (" QMK_VERSION "/" KEYMAP_VERSION ")");
    }

    SEQ_ONE_KEY (KC_L) {
      /* λ */
      ang_do_unicode ();

      uint16_t codes[] = {KC_0, KC_3, KC_B, KC_B, KC_ENT, 0};
      ang_tap (codes);
    }

    SEQ_ONE_KEY (KC_Y) {
      uint16_t codes[] = {KC_BSLS, KC_O, KC_SLSH, 0};
      ang_tap (codes);
    }

    SEQ_ONE_KEY (KC_S) {
      ang_do_unicode (); TAP_ONCE (KC_A); TAP_ONCE (KC_F); TAP_ONCE (KC_SPC);
      TAP_ONCE (KC_BSLS);
      register_code (KC_RSFT); TAP_ONCE (KC_MINS); TAP_ONCE (KC_9); unregister_code (KC_RSFT);
      ang_do_unicode (); TAP_ONCE (KC_3); TAP_ONCE (KC_0); TAP_ONCE (KC_C); TAP_ONCE (KC_4); TAP_ONCE (KC_SPC);
      register_code (KC_RSFT); TAP_ONCE (KC_0); TAP_ONCE (KC_MINS); unregister_code (KC_RSFT);
      TAP_ONCE (KC_SLSH);
      ang_do_unicode (); TAP_ONCE (KC_A); TAP_ONCE (KC_F); TAP_ONCE (KC_SPC);
    }

    SEQ_TWO_KEYS (KC_W, KC_M) {
      register_code (KC_LALT);
      register_code (KC_F2);
      unregister_code (KC_F2);
      unregister_code (KC_LALT);

      wait_ms (1000);

      uint16_t codes[] = {KC_M, KC_A, KC_X, KC_MINS, KC_F, KC_O, KC_C, KC_U, KC_S, KC_E, KC_D, KC_ENT, 0};
      ang_tap (codes);
      register_code (KC_LGUI);
      register_code (KC_UP);
      unregister_code (KC_UP);
      unregister_code (KC_LGUI);
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
#if ADORE_AUTOLOG
        log_enable = true;
#endif
      } else {
#if ADORE_AUTOLOG
        log_enable = false;
#endif
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

bool is_uni_seq(char *seq) {
  uint8_t i;

  for (i = 0; seq[i]; i++) {
    uint16_t code;
    if (('1' <= seq[i]) && (seq[i] <= '9'))
      code = seq[i] - '1' + KC_1;
    else if (seq[i] == '0')
      code = KC_0;
    else
      code = seq[i] - 'a' + KC_A;

    if (i > unicnt)
      return false;
    if (uni[i] != code)
      return false;
  }

  if (uni[i] == KC_ENT || uni[i] == KC_SPC)
    return true;

  return false;
}

uint16_t hex_to_keycode(uint8_t hex)
{
  if (hex == 0x0) {
    return KC_0;
  } else if (hex < 0xA) {
    return KC_1 + (hex - 0x1);
  } else {
    return KC_A + (hex - 0xA);
  }
}

void register_hex(uint16_t hex) {
  bool leading_zeros = true;

  for(int i = 3; i >= 0; i--) {
    uint8_t digit = ((hex >> (i*4)) & 0xF);
    if (digit != 0)
      leading_zeros = false;
    else if (leading_zeros)
      continue;
    register_code(hex_to_keycode(digit));
    unregister_code(hex_to_keycode(digit));
    wait_ms(10);
  }
}

typedef struct {
  char *symbol;
  uint16_t codes[4];
} qk_ucis_symbol_t;

static qk_ucis_symbol_t ucis_symbol_table[] = {
  {"poop", {0x1, 0xf4a9, 0}},
  {"rofl", {0x1, 0xf923, 0}},
  {"kiss", {0x1, 0xf619, 0}},
  {"snowman", {0x2603, 0}},
  {NULL, {}}
};

bool process_record_ucis (uint16_t keycode, keyrecord_t *record) {
  uint8_t i;

  if (!unimagic)
    return true;

  if (!record->event.pressed)
    return true;

  uni[unicnt] = keycode;
  unicnt++;

  if (keycode == KC_BSPC) {
    if (unicnt >= 2) {
      unicnt-= 2;
      return true;
    } else {
      unicnt--;
      return false;
    }
  }

  if (keycode == KC_ENT || keycode == KC_SPC) {
    bool symbol_found = false;

    for (i = unicnt; i > 0; i--) {
      register_code (KC_BSPC);
      unregister_code (KC_BSPC);
      wait_ms(10);
    }

    ang_do_unicode();
    wait_ms(10);
    for (i = 0; ucis_symbol_table[i].symbol; i++) {
      if (is_uni_seq (ucis_symbol_table[i].symbol)) {
        symbol_found = true;
        for (uint8_t j = 0; ucis_symbol_table[i].codes[j]; j++) {
          register_hex(ucis_symbol_table[i].codes[j]);
        }
        break;
      }
    }
    if (!symbol_found) {
      for (i = 0; i < unicnt - 1; i++) {
        uint8_t code;

        if (uni[i] > KF_1)
          code = uni[i] - KF_1 + KC_1;
        else
          code = uni[i];
        TAP_ONCE(code);
        wait_ms (10);
      }
    }

    unimagic = false;
    return true;
  }
  return true;
}

bool process_record_user (uint16_t keycode, keyrecord_t *record) {
#if KEYLOGGER_ENABLE
  if (log_enable) {
    xprintf ("KL: col=%d, row=%d\n", record->event.key.col,
             record->event.key.row);
  }
#endif

  if (!process_record_ucis (keycode, record))
    return false;

  if (time_travel && !record->event.pressed) {
    uint8_t p;

    // shift cache one to the left
    for (p = 0; p < 3; p++) {
      last4[p] = last4[p + 1];
    }
    last4[3] = keycode;

    if (last4[0] == KC_D && last4[1] == KC_A && last4[2] == KC_T && last4[3] == KC_E) {
      uint16_t codes[] = {KC_E, KC_SPC, KC_MINS, KC_D, KC_SPC, KC_QUOT, 0};
      ang_tap (codes);
      register_code (KC_RSFT);
      register_code (KC_EQL);
      unregister_code (KC_EQL);
      unregister_code (KC_RSFT);

      uint16_t codes2[] = {KC_4, KC_SPC, KC_D, KC_A, KC_Y, KC_S, KC_QUOT, 0};
      ang_tap (codes2);

      return false;
    }
  }

  return true;
}
