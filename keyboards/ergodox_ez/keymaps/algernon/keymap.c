/*
 * algernon's ErgoDox EZ layout, please see the readme.md file!
 */

#include "ergodox_ez.h"
#include "led.h"
#include "debug.h"
#include "action_layer.h"
#include "action_util.h"
#include "mousekey.h"
#include "timer.h"
#include "keymap_plover.h"

/* Layers */

enum {
  BASE = 0,
  EXPRM,
  ARRW,
  APPSEL,
  HUN,
  NMDIA,
  OHLFT,
  OHRGT,
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

  // One-handed layout specials
  OH_BSSPC,
  OH_ENTSFT,
  OH_BASE,
  OH_LEFT,
  OH_RIGHT,
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
  CT_CLN = 0x7101
};

/* States & timers */

uint16_t gui_timer = 0;

uint16_t kf_timers[12];

uint16_t oh_base_timer = 0;
uint16_t oh_bsspc_timer = 0;
uint16_t oh_entsft_timer = 0;

#define OH_BLINK_INTERVAL 500

uint8_t oh_left_blink = 0;
uint16_t oh_left_blink_timer = 0;
uint8_t oh_right_blink = 0;
uint16_t oh_right_blink_timer = 0;

uint8_t ct_cln_count = 0;
uint16_t ct_cln_timer = 0;

/* The Keymap */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Keymap 0: Base Layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * |        `~ | 1 F1 | 2 F2 | 3 F3 | 4 F4 | 5 F5 | Plvr |           | 1HND | 6 F6 | 7 F7 | 8 F8 | 9 F9 | 0 F10|       F11 |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * | Next/Prev |   '  |   ,  |   .  |   P  |   Y  |   [  |           |  ]   |   F  |   G  |   C  |   R  |  L   | \         |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |       Tab |   A  |   O  |   E  |   U  |   I  |------|           |------|   D  |   H  |   T  |   N  |  S   | =         |
 * |-----------+------+------+------+------+------|   (  |           |  )   |------+------+------+------+------+-----------|
 * | Play/Pause|   /  |   Q  |   J  |   K  |   X  |      |           |      |   B  |   M  |   W  |   V  |  Z   |      Stop |
 * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
 *     |       |      | Left |  Up  |   :  |                                       |   -  | Down | Rght |      |       |
 *     `-----------------------------------'                                       `-----------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         | LAlt | GUI  |           | MDIA | ARRW |
 *                                  ,------|------|------|           |------+------+------.
 *                                  |      |      | Ctrl |           | LEAD |      |      |
 *                                  |Backsp|LShift|------|           |------| Enter| Space|
 *                                  |      |      | ESC  |           | HUN  |      |      |
 *                                  `--------------------'           `--------------------'
 */
[BASE] = KEYMAP(
// left hand
 KC_GRV             ,M(KF_1)     ,M(KF_2)     ,M(KF_3),M(KF_4),M(KF_5),M(A_PLVR)
,M(A_MPN)           ,KC_QUOT     ,KC_COMM     ,KC_DOT ,KC_P   ,KC_Y   ,KC_LBRC
,KC_TAB             ,KC_A        ,KC_O        ,KC_E   ,KC_U   ,KC_I
,KC_MPLY            ,KC_SLSH     ,KC_Q        ,KC_J   ,KC_K   ,KC_X   ,KC_LPRN
,KC_NO              ,KC_NO       ,KC_LEFT     ,KC_UP  ,CT_CLN

                                                            ,F(F_ALT),F(F_GUI)
                                                                     ,F(F_CTRL)
                                                    ,KC_BSPC,F(F_SFT),M(A_ESC)

                                                                // right hand
                                                               ,M(OH_LEFT),M(KF_6),M(KF_7),M(KF_8),M(KF_9)     ,M(KF_10)    ,KC_F11
                                                               ,KC_RBRC   ,KC_F   ,KC_G   ,KC_C   ,KC_R        ,KC_L        ,KC_BSLS
                                                                          ,KC_D   ,KC_H   ,KC_T   ,KC_N        ,KC_S        ,KC_EQL
                                                               ,KC_RPRN   ,KC_B   ,KC_M   ,KC_W   ,KC_V        ,KC_Z        ,KC_MSTP
                                                                                  ,KC_MINS,KC_DOWN,KC_RGHT     ,KC_NO       ,KC_NO

                                                               ,OSL(NMDIA),OSL(ARRW)
                                                               ,KC_LEAD
                                                               ,F(F_HUN)  ,KC_ENT ,KC_SPC
    ),

/* Keymap 1: Experimental layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * |        `~ | 1 F1 | 2 F2 | 3 F3 | 4 F4 | 5 F5 | Plvr |           | 1HND | 6 F6 | 7 F7 | 8 F8 | 9 F9 | 0 F10|       F11 |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * | Next/Prev |   '  |   ,  |   .  |   P  |   Y  |   [  |           |  ]   |   L  |   F  |   C  |   R  |  J   | =         |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |       Tab |   A  |   O  |   E  |   U  |   I  |------|           |------|   D  |   H  |   T  |   N  |  S   | \         |
 * |-----------+------+------+------+------+------|   (  |           |  )   |------+------+------+------+------+-----------|
 * | Play/Pause|   Z  |   G  |   V  |   K  |   X  |      |           |      |   Q  |   M  |   W  |   B  |  /   |      Stop |
 * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
 *     |       |      | Left |  Up  |   :  |                                       |   -  | Down | Rght |      |       |
 *     `-----------------------------------'                                       `-----------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         | LAlt | GUI  |           | MDIA | ARRW |
 *                                  ,------|------|------|           |------+------+------.
 *                                  |      |      | Ctrl |           | LEAD |      |      |
 *                                  |Backsp|LShift|------|           |------| Enter| Space|
 *                                  |      |      | ESC  |           | HUN  |      |      |
 *                                  `--------------------'           `--------------------'
 */
[EXPRM] = KEYMAP(
// left hand
 KC_GRV             ,M(KF_1)     ,M(KF_2)     ,M(KF_3),M(KF_4),M(KF_5),M(A_PLVR)
,M(A_MPN)           ,KC_QUOT     ,KC_COMM     ,KC_DOT ,KC_P   ,KC_Y   ,KC_LBRC
,KC_TAB             ,KC_A        ,KC_O        ,KC_E   ,KC_U   ,KC_I
,KC_MPLY            ,KC_Z        ,KC_G        ,KC_V   ,KC_K   ,KC_X   ,KC_LPRN
,KC_NO              ,KC_NO       ,KC_LEFT     ,KC_UP  ,CT_CLN

                                                            ,F(F_ALT),F(F_GUI)
                                                                     ,F(F_CTRL)
                                                    ,KC_BSPC,F(F_SFT),M(A_ESC)

                                                                // right hand
                                                               ,M(OH_LEFT),M(KF_6),M(KF_7),M(KF_8),M(KF_9)     ,M(KF_10)    ,KC_F11
                                                               ,KC_RBRC   ,KC_L   ,KC_F   ,KC_C   ,KC_R        ,KC_J        ,KC_BSLS
                                                                          ,KC_D   ,KC_H   ,KC_T   ,KC_N        ,KC_S        ,KC_EQL
                                                               ,KC_RPRN   ,KC_Q   ,KC_M   ,KC_W   ,KC_B        ,KC_SLSH     ,KC_MSTP
                                                                                  ,KC_MINS,KC_DOWN,KC_RGHT     ,KC_NO       ,KC_NO

                                                               ,OSL(NMDIA),OSL(ARRW)
                                                               ,KC_LEAD
                                                               ,F(F_HUN)  ,KC_ENT ,KC_SPC
    ),

/* Keymap 2: Arrow layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * |           |      |      |      |      |      |      |           |      |      |      |      |      |      |           |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * |           |      |      |      |      |      |      |           |      |      |      |      |      |      |           |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |           |      |      |      |      |      |------|           |------|      |      |      |      |      |           |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |           |      |      |      |      |      |      |           |      |      |      |      |      |      |           |
 * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
 *      |      |      | Home | PgUp |      |                                       |      | PgDn | End  |      |      |
 *      `----------------------------------'                                       `----------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         |      |      |           |      |      |
 *                                  ,------|------|------|           |------+------+------.
 *                                  |      |      |      |           |      |      |      |
 *                                  |      |      |------|           |------|      |      |
 *                                  |      |      |      |           |      |      |      |
 *                                  `--------------------'           `--------------------'
 */

[ARRW] = KEYMAP(
// left hand
 KC_TRNS ,KC_TRNS    ,KC_TRNS   ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS
,KC_TRNS ,KC_TRNS    ,KC_TRNS   ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS
,KC_TRNS ,KC_TRNS    ,KC_TRNS   ,KC_TRNS    ,KC_TRNS    ,KC_TRNS
,KC_TRNS ,KC_TRNS    ,KC_TRNS   ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS
,KC_TRNS ,KC_TRNS    ,KC_HOME   ,KC_PGUP    ,KC_TRNS

                                             ,KC_TRNS ,KC_TRNS
                                                      ,KC_TRNS
                                    ,KC_TRNS ,KC_TRNS ,KC_TRNS

                                                                // right hand
                                                               ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
                                                               ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
                                                                        ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
                                                               ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
                                                                                 ,KC_TRNS ,KC_PGDN ,KC_END  ,KC_TRNS ,KC_TRNS

                                                               ,KC_TRNS ,KC_TRNS
                                                               ,KC_TRNS
                                                               ,KC_TRNS ,KC_TRNS ,KC_TRNS
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

/* Keymap 6: One-handed, left side
 *
 * ,-----------------------------------------------------.
 * |        `~ | 1 F1 | 2 F2 | 3 F3 | 4 F4 | 5 F5 |A  BSE|
 * |-----------+------+------+------+------+-------------|
 * |       Tab |   '  |   ,  |   .  |   P  |   Y  |   [  |
 * |-----------+------+------+------+------+------|      |
 * |         - |   A  |   O  |   E  |   U  |   I  |------|
 * |-----------+------+------+------+------+------|   (  |
 * | Play/Pause|   ;  |   Q  |   J  |   K  |   X  |      |
 * `-----------+------+------+------+------+-------------'
 *     |  Home | End  | Down |  Up  | ESC  |
 *     `-----------------------------------'
 *                                         ,-------------.
 *                                         | LAlt | GUI  |
 *                                  ,------|------|------|
 *                                  |BackSp|LShift| Ctrl |
 *                                  |      |      |------|
 *                                  |Space |Enter |OTHER |
 *                                  `--------------------'
 */
[OHLFT] = KEYMAP(
// left hand
 KC_GRV     ,M(KF_1)     ,M(KF_2)     ,M(KF_3)   ,M(KF_4)    ,M(KF_5) ,M(OH_BASE)
,KC_TAB     ,KC_QUOT     ,KC_COMM     ,KC_DOT    ,KC_P       ,KC_Y    ,KC_LBRC
,KC_MINS    ,KC_A        ,KC_O        ,KC_E      ,KC_U       ,KC_I
,KC_MPLY    ,KC_SCLN     ,KC_Q        ,KC_J      ,KC_K       ,KC_X    ,KC_LPRN
,KC_HOME    ,KC_END      ,KC_DOWN     ,KC_UP     ,M(A_ESC)

                                                                ,KC_TRNS     ,KC_TRNS
                                                                             ,KC_TRNS
                                                    ,M(OH_BSSPC),M(OH_ENTSFT),M(OH_RIGHT)

                                                                // right hand
                                                               ,KC_NO   ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO       ,KC_NO       ,KC_NO
                                                               ,KC_NO   ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO       ,KC_NO       ,KC_NO
                                                                        ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO       ,KC_NO       ,KC_NO
                                                               ,KC_NO   ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO       ,KC_NO       ,KC_NO
                                                                                ,KC_NO  ,KC_NO  ,KC_NO       ,KC_NO       ,KC_NO

                                                               ,KC_NO   ,KC_NO
                                                               ,KC_NO
                                                               ,KC_NO   ,KC_NO  ,KC_NO
    ),

/* Keymap 7: One-handed, right side
 *
 * ,-----------------------------------------------------.
 * | =     F11 | 0 F10| 9 F9 | 8 F8 | 7 F7 | 6 F6 |A  BSE|
 * |-----------+------+------+------+------+-------------|
 * |         / |   L  |   R  |   C  |   G  |   F  |   ]  |
 * |-----------+------+------+------+------+------|      |
 * |         \ |   S  |   N  |   T  |   H  |   D  |------|
 * |-----------+------+------+------+------+------|   )  |
 * |      Stop |   Z  |   V  |   W  |   M  |   B  |      |
 * `-----------+------+------+------+------+-------------'
 *     |  PgDn | PgUp | Right| Left | ESC  |
 *     `-----------------------------------'
 *                                         ,-------------.
 *                                         | LAlt | GUI  |
 *                                  ,------|------|------|
 *                                  |BackSp|LShift| Ctrl |
 *                                  |      |      |------|
 *                                  |Space |Enter |OTHER |
 *                                  `--------------------'
 */
[OHRGT] = KEYMAP(
// left hand
 M(KF_11)   ,M(KF_10)    ,M(KF_9)     ,M(KF_8)   ,M(KF_7)    ,M(KF_6) ,M(OH_BASE)
,KC_SLSH    ,KC_L        ,KC_R        ,KC_C      ,KC_G       ,KC_F    ,KC_RBRC
,KC_BSLS    ,KC_S        ,KC_N        ,KC_T      ,KC_H       ,KC_D
,KC_MSTP    ,KC_Z        ,KC_V        ,KC_W      ,KC_M       ,KC_B    ,KC_RPRN
,KC_PGDN    ,KC_PGUP     ,KC_RGHT     ,KC_LEFT   ,M(A_ESC)

                                                                ,KC_TRNS     ,KC_TRNS
                                                                             ,KC_TRNS
                                                    ,M(OH_BSSPC),M(OH_ENTSFT),M(OH_LEFT)

                                                                // right hand
                                                               ,KC_NO   ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO       ,KC_NO       ,KC_NO
                                                               ,KC_NO   ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO       ,KC_NO       ,KC_NO
                                                                        ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO       ,KC_NO       ,KC_NO
                                                               ,KC_NO   ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO       ,KC_NO       ,KC_NO
                                                                                ,KC_NO  ,KC_NO  ,KC_NO       ,KC_NO       ,KC_NO

                                                               ,KC_NO   ,KC_NO
                                                               ,KC_NO
                                                               ,KC_NO   ,KC_NO  ,KC_NO
    ),

/* Keymap 8: Steno for Plover
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
        return MACRODOWN(T(E), T(M), T(A), T(C), T(S), T(ENT), END);

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

        /* 1HAND layout */
      case OH_BASE:
        if (record->event.pressed) {
          oh_base_timer = timer_read ();
        } else {
          if (timer_elapsed (oh_base_timer) > TAPPING_TERM) {
            layer_clear ();
          } else {
            return MACRO (T(APP), END);
          }
        }
        break;

      case OH_BSSPC:
        if (record->event.pressed) {
          oh_bsspc_timer = timer_read ();
        } else {
          if (timer_elapsed (oh_bsspc_timer) > TAPPING_TERM) {
            return MACRO (T(BSPC), END);
          } else {
            return MACRO (T(SPC), END);
          }
        }
        break;

      case OH_ENTSFT:
        if (record->event.pressed) {
          oh_entsft_timer = timer_read ();
        } else {
          if (timer_elapsed (oh_entsft_timer) > TAPPING_TERM) {
            if (keyboard_report->mods & MOD_BIT(KC_LSFT))
              unregister_code (KC_LSFT);
            else
              register_code (KC_LSFT);
          } else {
            return MACRO (T(ENT), END);
          }
        }
        break;

      case OH_LEFT:
        if (record->event.pressed) {
          layer_move (OHLFT);
          oh_left_blink = 1;
          oh_left_blink_timer = timer_read ();
          ergodox_right_led_1_on ();
        }
        break;

      case OH_RIGHT:
        if (record->event.pressed) {
          layer_move (OHRGT);
          oh_right_blink = 1;
          oh_right_blink_timer = timer_read ();
          ergodox_right_led_3_on ();
        }
        break;
      }
      return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
  ergodox_led_all_on();
  for (int i = LED_BRIGHTNESS_HI; i > LED_BRIGHTNESS_LO; i--) {
    ergodox_led_all_set (i);
    _delay_ms (5);
  }
  _delay_ms(1000);
  for (int i = LED_BRIGHTNESS_LO; i > 0; i--) {
    ergodox_led_all_set (i);
    _delay_ms (10);
  }
  ergodox_led_all_off();
};

LEADER_EXTERNS();

void ang_do_unicode (void) {
  register_code (KC_RCTL);
  register_code (KC_RSFT);
  register_code (KC_U);
  unregister_code (KC_U);
  unregister_code (KC_RSFT);
  unregister_code (KC_RCTL);
  _delay_ms (100);
}

void ang_tap (uint16_t codes[]) {
  for (int i = 0; codes[i] != 0; i++) {
    register_code (codes[i]);
    unregister_code (codes[i]);
    _delay_ms (50);
  }
}

#define TAP_ONCE(code) \
  register_code (code); \
  unregister_code (code)

uint8_t is_exp = 0;

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
  uint8_t layer = biton32(layer_state);

  if (gui_timer && timer_elapsed (gui_timer) > TAPPING_TERM)
    unregister_code (KC_LGUI);

  if (ct_cln_timer && timer_elapsed (ct_cln_timer) > TAPPING_TERM) {
    if (ct_cln_count == 1) {
      register_code (KC_RSFT);
      register_code (KC_SCLN);
      unregister_code (KC_SCLN);
      unregister_code (KC_RSFT);
    } else if (ct_cln_count == 2) {
      register_code (KC_SCLN);
      unregister_code (KC_SCLN);
    }

    ct_cln_count = 0;
    ct_cln_timer = 0;
  }

  if (layer != OHLFT)
    oh_left_blink = 0;
  if (layer != OHRGT)
    oh_right_blink = 0;

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
  } else if (layer == EXPRM) {
    ergodox_right_led_1_on ();
    ergodox_right_led_2_on ();
    ergodox_right_led_3_on ();

    ergodox_right_led_2_set (LED_BRIGHTNESS_HI);
  }

  if (layer == OHLFT || layer == OHRGT) {
    ergodox_right_led_2_on();

    if (oh_left_blink) {
      if (timer_elapsed (oh_left_blink_timer) > OH_BLINK_INTERVAL) {
        if ((keyboard_report->mods & MOD_BIT(KC_LSFT)) == 0)
          ergodox_right_led_1_off ();
      }
      if (timer_elapsed (oh_left_blink_timer) > OH_BLINK_INTERVAL * 2) {
        ergodox_right_led_1_on ();
        oh_left_blink_timer = timer_read ();
      }
    }

    if (oh_right_blink) {
      if (timer_elapsed (oh_right_blink_timer) > OH_BLINK_INTERVAL) {
        if ((keyboard_report->mods & MOD_BIT(KC_LCTRL)) == 0)
          ergodox_right_led_3_off ();
      }
      if (timer_elapsed (oh_right_blink_timer) > OH_BLINK_INTERVAL * 2) {
        ergodox_right_led_3_on ();
        oh_right_blink_timer = timer_read ();
      }
    }
  }

  if (keyboard_report->mods & MOD_BIT(KC_LSFT) ||
      ((get_oneshot_mods() & MOD_BIT(KC_LSFT)) && !has_oneshot_mods_timed_out())) {
    ergodox_right_led_1_set (LED_BRIGHTNESS_HI);
    ergodox_right_led_1_on ();
  } else {
    ergodox_right_led_1_set (LED_BRIGHTNESS_LO);
    if (layer != OHLFT && layer != NMDIA && layer != PLVR && layer != EXPRM)
      ergodox_right_led_1_off ();
  }

  if (keyboard_report->mods & MOD_BIT(KC_LALT) ||
      ((get_oneshot_mods() & MOD_BIT(KC_LALT)) && !has_oneshot_mods_timed_out())) {
    ergodox_right_led_2_set (LED_BRIGHTNESS_HI);
    ergodox_right_led_2_on ();
  } else {
    ergodox_right_led_2_set (LED_BRIGHTNESS_LO);
    if (layer != OHRGT && layer != HUN && layer != OHLFT && layer != NMDIA && layer != PLVR && layer != EXPRM)
      ergodox_right_led_2_off ();
  }

  if (keyboard_report->mods & MOD_BIT(KC_LCTRL) ||
      ((get_oneshot_mods() & MOD_BIT(KC_LCTRL)) && !has_oneshot_mods_timed_out())) {
    ergodox_right_led_3_set (LED_BRIGHTNESS_HI);
    ergodox_right_led_3_on ();
  } else {
    ergodox_right_led_3_set (LED_BRIGHTNESS_LO);
    if (layer != OHRGT && layer != HUN && layer != PLVR && layer != EXPRM)
      ergodox_right_led_3_off ();
  }

  LEADER_DICTIONARY() {
    leading = false;
    leader_end ();

    SEQ_ONE_KEY (KC_U) {
      ang_do_unicode ();
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

      _delay_ms (1000);

      uint16_t codes[] = {KC_M, KC_A, KC_X, KC_MINS, KC_F, KC_O, KC_C, KC_U, KC_S, KC_E, KC_D, KC_ENT, 0};
      ang_tap (codes);
      register_code (KC_LGUI);
      register_code (KC_UP);
      unregister_code (KC_UP);
      unregister_code (KC_LGUI);
    }

    SEQ_ONE_KEY (KC_E) {
      if (is_exp == 0) {
        default_layer_and (0);
        default_layer_or ((1 << EXPRM));
        is_exp = 1;

        ergodox_led_all_off ();
        ergodox_right_led_3_on ();
        _delay_ms (100);
        ergodox_right_led_2_on ();
        _delay_ms (100);
        ergodox_right_led_3_off ();
        ergodox_right_led_1_on ();
        _delay_ms (100);
        ergodox_right_led_2_off ();
        _delay_ms (100);
        ergodox_right_led_1_off ();
      } else {
        is_exp = 0;
        default_layer_and (0);
        default_layer_or (1 << BASE);

        ergodox_led_all_off ();
        ergodox_right_led_1_on ();
        _delay_ms (100);
        ergodox_right_led_2_on ();
        _delay_ms (100);
        ergodox_right_led_1_off ();
        ergodox_right_led_3_on ();
        _delay_ms (100);
        ergodox_right_led_2_off ();
        _delay_ms (100);
        ergodox_right_led_3_off ();
      }
    }
  }
}

bool process_record_user (uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
  case CT_CLN:
    if (record->event.pressed) {
      ct_cln_count++;
      ct_cln_timer = timer_read ();
    } else {
    }
    return false;
    break;

  default:
    if (ct_cln_count == 1) {
      register_code (KC_RSFT);
      register_code (KC_SCLN);
      unregister_code (KC_SCLN);
      unregister_code (KC_RSFT);
    } else if (ct_cln_count == 2) {
      register_code (KC_SCLN);
      unregister_code (KC_SCLN);
    }
    ct_cln_count = 0;
    ct_cln_timer = 0;
    break;
  }

  return true;
}
