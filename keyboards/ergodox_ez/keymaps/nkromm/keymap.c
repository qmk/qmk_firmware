#include QMK_KEYBOARD_H
#include "muse.h"
#include "keymap_german.h"
#include "version.h"

// Left-hand home row mods
#define MOD_A LGUI_T(KC_A)
#define MOD_S LALT_T(KC_S)
#define MOD_D LSFT_T(KC_D)
#define MOD_F LCTL_T(KC_F)

// Right-hand home row mods
#define MOD_J RCTL_T(KC_J)
#define MOD_K RSFT_T(KC_K)
#define MOD_L LALT_T(KC_L)
#define MOD_SCLN RGUI_T(KC_SCLN)

enum layers {
    BASE,
    FN1,
    FN2,
    MEDIA,
    GAMING,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 *      ,--------------------------------------------------------.                   ,------------------------------------------------------.
 *      |  Esc   |   1   |   2   |   3   |   4   |   5   |   `   |                   |   `   |   6  |   7   |   8   |   9   |   0   |  Bspc  |
 *      |--------+-------+-------+-------+-------+---------------|                   |-------+------+-------+-------+-------+-------+--------|
 *      |  Tab   |   Q   |   W   |   E   |   R   |   T   |       |                   |       |   Y  |   U   |   I   |   O   |   P   |   \    |
 *      |--------+-------+-------+-------+-------+-------|       |                   |       |------+-------+-------+-------+-------+--------|
 *      |   '    | MOD_A | MOD_S | MOD_D | MOD_F |   G   |-------|                   |-------|   H  | MOD_J | MOD_K | MOD_L | MOD_; |   -    |
 *      |--------+-------+-------+-------+-------+-------|       |                   |       |------+-------+-------+-------+-------+--------|
 *      | LShift |   Z   |   X   |   C   |   V   |   B   |       |                   |       |   N  |   M   |   ,   |   .   |   /   | RShift |
 *      `--------+-------+-------+-------+-------+---------------'                   `--------------+-------+-------+-------+-------+--------'
 *        | LCtr |  GUI  | LAlt  | MO(2) | MO(1) |                                                  | Left  |  Down |   Up  | Right | MO(1) |
 *        `--------------------------------------'                                                  `---------------------------------------'
 *                                                 ,-------------.                   ,-------------.
 *                                                 |Caps |PrintSc|                   | TO(4) |     |
 *                                     ,-----------|-----|-------|                   |-------+-----+------------.
 *                                     |           |     |       |                   | TO(3) |     |            |
 *                                     | LT(1, Spc)| Spc |-------|                   |-------| Ent | LT(1, Spc) |
 *                                     |           |     |       |                   |       |     |            |
 *                                     `-------------------------'                   `--------------------------'
 */
[BASE] = LAYOUT_ergodox_pretty(
  KC_ESC,     KC_1,      KC_2,     KC_3,    KC_4,    KC_5,    KC_GRV,              KC_GRV,     KC_6,    KC_7,    KC_8,     KC_9,      KC_0,       KC_BSPC,
  KC_TAB,     KC_Q,      KC_W,     KC_E,    KC_R,    KC_T,    KC_NO,               KC_NO,      KC_Y,    KC_U,    KC_I,     KC_O,      KC_P,       KC_BSLS,
  KC_QUOT,    MOD_A,     MOD_S,    MOD_D,   MOD_F,   KC_G,                                     KC_H,    MOD_J,   MOD_K,    MOD_L,     MOD_SCLN,   KC_MINS,
  KC_LSFT,    KC_Z,      KC_X,     KC_C,    KC_V,    KC_B,    KC_NO,               KC_NO,      KC_N,    KC_M,    KC_COMM,  KC_DOT,    KC_SLSH,    KC_RSFT,
  KC_LCTRL,   KC_LGUI,   KC_LALT,  MO(2),   MO(1),                                                      KC_LEFT, KC_DOWN,  KC_UP,     KC_RGHT,    MO(1),
                                                    KC_CAPS, KC_PSCR,            TO(4), KC_NO,
                                                               KC_NO,            TO(3),
                                        LT(1, KC_SPC), KC_SPC, KC_NO,            KC_NO, KC_ENT, LT(1, KC_ENT)
),
/* Keymap 1: Navigation & Symbols1 layer
 *
 *                   ,-------------------------------------------------------.                ,-------------------------------------------------------.
 *                   |   Del  |   (    |   {   |   [   |   -   |       |     |                |     |       |   =   |   ]    |   }   |   )   |   Del  |
 *                   |--------+--------+-------+-------+-------+-------------|                |-----+-------+-------+--------+-------+-------+--------|
 *                   |   Ins  |   Tr   |   Tr  |  Tr   |  Tr   |  Tr   |     |                |     |  Tr   |  Tr   |   Tr   |   Tr  |   Tr  |   Ins  |
 *                   |--------+--------+-------+-------+-------+-------|     |                |     |-------+-------+--------+-------+-------+--------|
 *                   |   `    |   Tr   |   Tr  |  Tr   |  Tr   |  Tr   |-----|                |-----|  Tr   |  Tr   |   Tr   |   Tr  |   Tr  |   =    |
 *                   |--------+--------+-------+-------+-------+-------|     |                |     |-------+-------+--------+-------+-------+--------|
 *                   |   Tr   |   Tr   |  Tr   |  Tr   |  Tr   |  Tr   |     |                |     |  Tr   |  Tr   |   Tr   |   Tr  |   Tr  |   Tr   |
 *                   `--------+--------+-------+-------+-------+-------------'                `-------------+-------+--------+-------+-------+--------'
 *                     |  Tr  |   Tr   |  Tr   |       |  Tr   |                                            | Home  |  PgDn  |  PgUp |  End  |  Tr  |
 *                     `---------------------------------------'                                            `---------------------------------------'
 *                                                              ,-------------.                ,--------------.
 *                                                              |     |       |                |       |      |
 *                                                        ,-----|-----|-------|                |-------+------+-------.
 *                                                        |     |     |       |                |       |      |       |
 *                                                        | Tr  | Tr  |-------|                |-------|  Tr  |   Tr  |
 *                                                        |     |     |       |                |       |      |       |
 *                                                        `-------------------'                `----------------------'
 */
[FN1] = LAYOUT_ergodox_pretty(
  KC_DEL,     KC_LPRN,    KC_LCBR,    KC_LBRC,    KC_MINS,    KC_NO,     KC_NO,                KC_NO,    KC_NO,     KC_EQL,    KC_RBRC,    KC_RCBR,   KC_RPRN,   KC_DEL,
  KC_INS,     KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,   KC_NO,                KC_NO,    KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_INS,
  KC_GRV,     KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                                   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_EQL,
  KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,   KC_NO,                KC_NO,    KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_TRNS,
  KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_NO,      KC_TRNS,                                                          KC_HOME,   KC_PGDN,    KC_PGUP,   KC_END,    KC_TRNS,
                                                                 KC_NO,  KC_NO,                KC_NO, KC_NO,
                                                                         KC_NO,                KC_NO,
                                                       KC_TRNS, KC_TRNS, KC_NO,                KC_NO, KC_TRNS, KC_TRNS
),
/* Keymap 2: FN & Symbols2 layer
 *
 *            ,--------------------------------------------------------.                  ,-------------------------------------------------------.
 *            |  Ins   |  F1   |  F2   |  F3   |  F4   |  F5   |  F6   |                  |   F7  |  F8  |  F9   |  F10  |  F11  |  F12  |  Ins   |
 *            |--------+-------+-------+-------+-------+---------------|                  |-------+------+-------+-------+-------+-------+--------|
 *            |        |DE_ADIA|DE_UDIA|DE_ODIA|       |       |       |                  |       |      |       |       |       |       |        |
 *            |--------+-------+-------+-------+-------+-------|       |                  |       |------+-------+-------+-------+-------+--------|
 *            |        |  Tr   |  Tr   |  Tr   |  Tr   |       |-------|                  |-------|      |   Tr  |  Tr   |  Tr   |  Tr   |        |
 *            |--------+-------+-------+-------+-------+-------|       |                  |       |------+-------+-------+-------+-------+--------|
 *            |        |       |       |       |       |       |       |                  |       |      |       |       |       |       |        |
 *            `--------+-------+-------+-------+-------+---------------'                  `--------------+-------+-------+-------+-------+--------'
 *              |      |       |       |  Tr   |       |                                                 |       |       |       |       |      |
 *              `--------------------------------------'                                                 `--------------------------------------'
 *                                                       ,-------------.                  ,--------------.
 *                                                       |     |       |                  |       |      |
 *                                                 ,-----|-----|-------|                  |-------+------+-------.
 *                                                 |     |     |       |                  |       |      |       |
 *                                                 |     |     |-------|                  |-------|      |       |
 *                                                 |     |     |       |                  |       |      |       |
 *                                                 `-------------------'                  `----------------------'
 */
[FN2] = LAYOUT_ergodox_pretty(
  KC_INS,    KC_F1,      KC_F2,     KC_F3,    KC_F4,    KC_F5,    KC_F6,                   KC_F7,     KC_F8,      KC_F9,     KC_F10,    KC_F11,    KC_F12,    KC_INS,
  KC_NO,     DE_ADIA,    DE_UDIA,   DE_ODIA,  KC_NO,    KC_NO,    KC_NO,                   KC_NO,     KC_NO,      KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
  KC_NO,     KC_TRNS,    KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_NO,                                        KC_NO,      KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_NO,
  KC_NO,     KC_NO,      KC_NO,     KC_NO,    KC_NO,    KC_NO,    KC_NO,                   KC_NO,     KC_NO,      KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
  KC_NO,     KC_NO,      KC_NO,     KC_TRNS,  KC_NO,                                                              KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
                                                          KC_NO,  KC_NO,                   KC_NO, KC_NO,
                                                                  KC_NO,                   KC_NO,
                                                    KC_NO, KC_NO, KC_NO,                   KC_NO, KC_NO, KC_NO
),
/* Keymap 3: Media layer
 *
 *            ,--------------------------------------------------------.                 ,-------------------------------------------------------.
 *            |        |       |       |       |       |       |       |                 |       |      |       |       |       |       |        |
 *            |--------+-------+-------+-------+-------+---------------|                 |-------+------+-------+-------+-------+-------+--------|
 *            |        |       |       |       |       |       |       |                 |       |      |       |KC_VOLD|KC_VOLU|KC_MUTE|        |
 *            |--------+-------+-------+-------+-------+-------|       |                 |       |------+-------+-------+-------+-------+--------|
 *            |        |       |       |       |       |       |-------|                 |-------|      |       |KC_MPRV|KC_MNXT|KC_MPLY|        |
 *            |--------+-------+-------+-------+-------+-------|       |                 |       |------+-------+-------+-------+-------+--------|
 *            |        |       |       |       |       |       |       |                 |       |      |       |       |       |       |        |
 *            `--------+-------+-------+-------+-------+---------------'                 `--------------+-------+-------+-------+-------+--------'
 *              |      |       |       |       |       |                                                |       |       |       |       |      |
 *              `--------------------------------------'                                                `--------------------------------------'
 *                                                       ,-------------.                 ,--------------.
 *                                                       |     |       |                 |       |      |
 *                                                 ,-----|-----|-------|                 |-------+------+-------.
 *                                                 |     |     |       |                 | TO(0) |      |       |
 *                                                 |     |     |-------|                 |-------|      |       |
 *                                                 |     |     |       |                 |       |      |       |
 *                                                 `-------------------'                 `----------------------'
 */
[MEDIA] = LAYOUT_ergodox_pretty(
  KC_NO,     KC_NO,      KC_NO,     KC_NO,    KC_NO,    KC_NO,    KC_NO,                  KC_NO,     KC_NO,      KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
  KC_NO,     KC_NO,      KC_NO,     KC_NO,    KC_NO,    KC_NO,    KC_NO,                  KC_NO,     KC_NO,      KC_NO,     KC_VOLD,   KC_VOLU,   KC_MUTE,   KC_NO,
  KC_NO,     KC_NO,      KC_NO,     KC_NO,    KC_NO,    KC_NO,                                       KC_NO,      KC_NO,     KC_MPRV,   KC_MNXT,   KC_MPLY,   KC_NO,
  KC_NO,     KC_NO,      KC_NO,     KC_NO,    KC_NO,    KC_NO,    KC_NO,                  KC_NO,     KC_NO,      KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
  KC_NO,     KC_NO,      KC_NO,     KC_NO,    KC_NO,                                                             KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
                                                          KC_NO,  KC_NO,                  KC_NO, KC_NO,
                                                                  KC_NO,                  TO(0),
                                                    KC_NO, KC_NO, KC_NO,                  KC_NO, KC_NO, KC_NO
),
/* Keymap 4: Gaming layer  (not meant to be used with the other layers, it is mostly a copy of base layer)
 *
 *            ,--------------------------------------------------------.                 ,------------------------------------------------------.
 *            |   Esc  |   1   |   2   |   3   |   4   |   5   |   6   |                 |   `   |   6  |   7   |   8   |   9   |   0   |  Bspc  |
 *            |--------+-------+-------+-------+-------+---------------|                 |-------+------+-------+-------+-------+-------+--------|
 *            |   Tab  |   Q   |   W   |   E   |   R   |   T   |       |                 |   =   |   Y  |   U   |   I   |   O   |   P   |   \    |
 *            |--------+-------+-------+-------+-------+-------|   7   |                 |       |------+-------+-------+-------+-------+--------|
 *            |   `    |   A   |   S   |   D   |   F   |   G   |-------|                 |-------|   H  |   J   |   K   |   J   |   ;   |  Enter |
 *            |--------+-------+-------+-------+-------+-------|       |                 |   '   |------+-------+-------+-------+-------+--------|
 *            | LShift |   Z   |   X   |   C   |   V   |Lshift |   -   |                 |       |   N  |   M   |   ,   |   .   |   /   | RShift |
 *            `--------+-------+-------+-------+-------+---------------'                 `--------------+-------+-------+-------+-------+--------'
 *              |   B  |   N   |  LGUI |   ,   | Lctrl |                                                | Left  | Down  |  Up   | Right |      |
 *              `--------------------------------------'                                                `--------------------------------------'
 *                                                       ,-------------.                ,--------------.
 *                                                       |  8  |   9   |                | TO(0) |      |
 *                                                 ,-----|-----|-------|                |-------+------+-------.
 *                                                 |     |     |   0   |                |       |      |       |
 *                                                 |Space|  ;  |-------|                |-------| Ent  |  Ent  |
 *                                                 |     |     |   M   |                |       |      |       |
 *                                                 `-------------------'                `----------------------'
 */
[GAMING] = LAYOUT_ergodox_pretty(
  KC_ESC,    KC_1,      KC_2,      KC_3,     KC_4,     KC_5,     KC_6,                KC_GRV,     KC_6,    KC_7,    KC_8,     KC_9,      KC_0,       KC_BSPC,
  KC_TAB,    KC_Q,      KC_W,      KC_E,     KC_R,     KC_T,     KC_7,                KC_EQL,     KC_Y,    KC_U,    KC_I,     KC_O,      KC_P,       KC_BSLS,
  KC_GRV,    KC_A,      KC_S,      KC_D,     KC_F,     KC_G,                                      KC_H,    MOD_J,   MOD_K,    MOD_L,     MOD_SCLN,   KC_ENT,
  KC_LSFT,   KC_Z,      KC_X,      KC_C,     KC_V,     KC_LSFT,  KC_MINS,             KC_QUOT,    KC_N,    KC_M,    KC_COMM,  KC_DOT,    KC_SLSH,    KC_RSFT,
  KC_B,      KC_N,      KC_LGUI,   KC_COMM,  KC_LCTL,                                                      KC_LEFT, KC_DOWN,  KC_UP,     KC_RGHT,    KC_NO,
                                                         KC_8,   KC_9,                TO(0), KC_NO,
                                                                 KC_0,                KC_NO,
                                            KC_SPC,   KC_SCLN,   KC_M,                KC_NO, KC_ENT, KC_ENT
),
};
