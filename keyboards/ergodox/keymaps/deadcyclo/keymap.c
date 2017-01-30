#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys
#define NAVG 3 // navigation

enum macros {
  RUN
};

enum function_ids {
  EMOJI,
  EMOJI2,
  EPRM,
  VRSN,
  RGB_SLD,
  GO_GROUP
};

/* opt can only be 0-15 */
enum emojis {
  SHRUG,
  YAY,
  HUG,
  SMILE,
  SMILE2,
  HMM1,
  HMM2,
  BEAR1,
  BEAR2,
  FUU,
  EGGY1,
  EGGY2,
  FACE1,
  FACE2,
  UHU,
  SMRK1
};

enum emojis2 {
  SMRK2,
  LOVE
};

enum progmem_ids {
  EMOJI_SHRUG,
  EMOJI_YAY,
  EMOJI_HUG,
  EMOJI_SMILE,
  EMOJI_SMILE2,
  EMOJI_HMM1,
  EMOJI_HMM2,
  EMOJI_BEAR1,
  EMOJI_BEAR2,
  EMOJI_FUU,
  EMOJI_EGGY1,
  EMOJI_EGGY2,
  EMOJI_FACE1,
  EMOJI_FACE2,
  EMOJI_UHU,
  EMOJI_SMRK1,
  EMOJI_SMRK2,
  EMOJI_LOVE,
  F_EPRM,
  F_VRSN,
  F_RGB_SLD,
  I3_GO_GROUP_10,
  I3_GO_GROUP_1,
  I3_GO_GROUP_2,
  I3_GO_GROUP_3,
  I3_GO_GROUP_4,
  I3_GO_GROUP_5,
  I3_GO_GROUP_6,
  I3_GO_GROUP_7,
  I3_GO_GROUP_8,
  I3_GO_GROUP_9,
};

// TODO: Finish the macros for i3 (Macros should potentially be own function instead to make things easier? some of them at least, f. ex. the ones that use 1-0 keys so we can have a single switch)

// TODO: Do stuff with hyper and meh keys
// TODO: Add macros for lots of stuff. (Lastpass cli, pushbullet cli, other push service cli, linode cli, more?)
// TODO: Make macros for gnu screen and i3wm
// TODO: Need to change hotkeys for lastpass, and potentially make my own keys for them on one of my layers
// TODO: Look into using tap dance
// TODO: Use leader key for stuff. See https://github.com/qmk/qmk_firmware/wiki
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Esc/L3 |   1  |   2  |   3  |   4  |   5  |  6   |           |   6  |   7  |   8  |   9  |   0  |   -  |   =/L3 |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab/L1 |   Q  |   W  |   E  |   R  |   T  |  L1  |           |  L1  |   Y  |   U  |   I  |   O  |   P  |   \/L1 |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LCtrl  |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |; / L2| ctrl/'|
 * |--------+------+------+------+------+------| Hyper|           | Meh  |------+------+------+------+------+--------|
 * | LShift |Z/Ctrl|   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |//Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Grv/L1|  UNI |AltShf| Lalt | Ralt |                                       | Lalt | Ralt | LEAD |  UNI | ~/L1 |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | App  | Home |       | PgUp |  Ins   |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | End  |       | PgDn |        |      |
 *                                 | Space|  TAB |------|       |------|  BSPC  |Enter |
 *                                 |      |      |   [  |       |  ]   |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = KEYMAP(  // layer 0 : default
        // left hand
	LT(NAVG,KC_ESC),         KC_1,         KC_2,   KC_3,   KC_4,   KC_5,   KC_6,
        LT(SYMB,KC_TAB),        KC_Q,         KC_W,   KC_E,   KC_R,   KC_T,   TG(SYMB),
        KC_LCTL,        LT(MDIA, KC_A),         KC_S,   KC_D,   KC_F,   KC_G,
        KC_LSFT,        CTL_T(KC_Z),  KC_X,   KC_C,   KC_V,   KC_B,   ALL_T(KC_NO),
        LT(SYMB,KC_GRV),LCTL(LSFT(KC_U)),      LALT(KC_LSFT),  KC_RALT,KC_LALT,
                                              ALT_T(KC_APP),  KC_HOME,
                                                              KC_END,
                                               KC_SPC,KC_TAB,KC_LBRC,
        // right hand
		KC_6,     KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,             LT(NAVG,KC_EQL),
	TG(SYMB),    KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,             LT(SYMB, KC_BSLS),
	KC_H,   KC_J,   KC_K,   KC_L,   LT(MDIA, KC_SCLN),CTL_T(KC_QUOT),
             MEH_T(KC_NO),KC_N,   KC_M,   KC_COMM,KC_DOT, CTL_T(KC_SLSH),   KC_RSFT,
		KC_LALT,  KC_RALT,KC_LEAD,LCTL(LSFT(KC_U)),          LT(SYMB,KC_TILD),
             KC_PGUP,        KC_INS,
             KC_PGDN,
             KC_RBRC,KC_BSPC, KC_ENT
    ),
/* Keymap 1: Symbol Layer LCTL(LSFT(KC_U))
 *                                                  
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |           |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |   F12  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |    . |   0  |   =  |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |Toggle|Animat|       | Hue+ | Hue- |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |Bright|Bright|Solid |       |      |      |      |
 *                                 |ness- |ness+ |------|       |------| DEL  |      |
 *                                 |      |      |      |       | EPRM |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = KEYMAP(
       // left hand
       KC_TRNS,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,
       KC_TRNS,KC_EXLM,KC_AT,  KC_LCBR,KC_RCBR,KC_PIPE,KC_TRNS,
       KC_TRNS,KC_HASH,KC_DLR, KC_LPRN,KC_RPRN,KC_GRV,
       KC_TRNS,KC_PERC,KC_CIRC,KC_LBRC,KC_RBRC,KC_TILD,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       RGB_TOG,RGB_MOD,
       F(F_RGB_SLD),
                               RGB_VAD,RGB_VAI,KC_TRNS,
       // right hand
       KC_F6, KC_F7,   KC_F8,  KC_F9,   KC_F10,   KC_F11,  KC_F12,
       KC_TRNS, KC_UP,   KC_7,   KC_8,    KC_9,    KC_ASTR, KC_TRNS,
                KC_DOWN, KC_4,   KC_5,    KC_6,    KC_PLUS, KC_TRNS,
       KC_TRNS, KC_AMPR, KC_1,   KC_2,    KC_3,    KC_BSLS, KC_TRNS,
                         KC_TRNS,KC_DOT,  KC_0,    KC_EQL,  KC_TRNS,
       RGB_HUD, RGB_HUI,
       KC_TRNS,
       F(F_EPRM), KC_DEL, KC_TRNS
),
/* Keymap 2: Media, mouse and navigation
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        | gg(1)|      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp | RUN  |      |      |           |      |      |      |  Up  |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      | Left | Down | Right|      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA , MOUSE and NAVIGATION
[MDIA] = KEYMAP(
		KC_TRNS, F(I3_GO_GROUP_1), F(I3_GO_GROUP_2), F(I3_GO_GROUP_3), F(I3_GO_GROUP_4), F(I3_GO_GROUP_5), F(I3_GO_GROUP_6),
KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, M(RUN), KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
		F(I3_GO_GROUP_6), F(I3_GO_GROUP_7), F(I3_GO_GROUP_8), F(I3_GO_GROUP_9), F(I3_GO_GROUP_10), KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_UP,   KC_TRNS,  KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT, KC_TRNS, KC_MPLY,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT,  KC_TRNS, KC_TRNS,
                          KC_VOLU, KC_VOLD, KC_MUTE,  KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_WBAK
),

/* Keymap 3: Unicode
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  ┌   |  ┐   |  └   |  ┘   |  │   |  ─   |           |  ╔   |  ╗   |  ╚   |  ╝   |  ║   |  ═   |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        | shrug| yay  | hug  | smile|smile2|      |           |      |  ■   |  λ   |  →   |  ➙   |  ▻   |  █     |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | hmm1 | hmm2 | bear1| bear2| fuu  |------|           |------|  ☺   |  ☻   |  ☹   |  ♡   |  ♥   |  ░     |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | eggy1| eggy2| face1| face2| uhu  |      |           |      |  ❤   |  ☐   |  ☑   |  ☒   |  ✓   |  ▄     |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      | smrk1| smrk2| love | VER  |                                       |  ✔   |  ✗   |  ✘   |  ●   |  ▀   |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |   ▒  |  ▓   |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      | 
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// Unicode
[NAVG] = KEYMAP(
		KC_TRNS, UC(0x250c), UC(0x2510), UC(0x2514), UC(0x2518), UC(0x2502), UC(0x2500),
		KC_TRNS, F(EMOJI_SHRUG), F(EMOJI_YAY), F(EMOJI_HUG), F(EMOJI_SMILE), F(EMOJI_SMILE2), KC_TRNS,
		KC_TRNS, F(EMOJI_HMM1), F(EMOJI_HMM2), F(EMOJI_BEAR1), F(EMOJI_BEAR2), F(EMOJI_FUU),
		KC_TRNS, F(EMOJI_EGGY1), F(EMOJI_EGGY2), F(EMOJI_FACE1), F(EMOJI_FACE2), F(EMOJI_UHU), KC_TRNS,
		KC_TRNS, F(EMOJI_SMRK1), F(EMOJI_SMRK2), F(EMOJI_LOVE), F(F_VRSN),
		KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       UC(0x2554),  UC(0x2557), UC(0x255a), UC(0x255d), UC(0x2551), UC(0x2550), KC_TRNS,
       KC_TRNS,  UC(0x25a0), UC(0x03bb), UC(0x2192), UC(0x2799), UC(0x25bb), UC(0x2588),
                 UC(0x263a), UC(0x263b), UC(0x2639), UC(0x2661), UC(0x2665), UC(0x2591),
       KC_TRNS,  UC(0x2764), UC(0x2610), UC(0x2611), UC(0x2612), UC(0x2713), UC(0x2584),
       UC(0x2714), UC(0x2717), UC(0x2718), UC(0x25cf), UC(0x2580),
		UC(0x2592), UC(0x2593),
		KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS
),
};

const uint16_t PROGMEM fn_actions[] = {
  [EMOJI_SHRUG]   = ACTION_FUNCTION_OPT(EMOJI, SHRUG),
  [EMOJI_YAY]     = ACTION_FUNCTION_OPT(EMOJI, YAY),
  [EMOJI_HUG]     = ACTION_FUNCTION_OPT(EMOJI,HUG),
  [EMOJI_SMILE]   = ACTION_FUNCTION_OPT(EMOJI,SMILE),
  [EMOJI_SMILE2]  = ACTION_FUNCTION_OPT(EMOJI,SMILE2),
  [EMOJI_HMM1]    = ACTION_FUNCTION_OPT(EMOJI,HMM1),
  [EMOJI_HMM2]    = ACTION_FUNCTION_OPT(EMOJI,HMM2),
  [EMOJI_BEAR1]   = ACTION_FUNCTION_OPT(EMOJI,BEAR1),
  [EMOJI_BEAR2]   = ACTION_FUNCTION_OPT(EMOJI,BEAR2),
  [EMOJI_FUU]     = ACTION_FUNCTION_OPT(EMOJI,FUU),
  [EMOJI_EGGY1]   = ACTION_FUNCTION_OPT(EMOJI,EGGY1),
  [EMOJI_EGGY2]   = ACTION_FUNCTION_OPT(EMOJI,EGGY2),
  [EMOJI_FACE1]   = ACTION_FUNCTION_OPT(EMOJI,FACE1),
  [EMOJI_FACE2]   = ACTION_FUNCTION_OPT(EMOJI,FACE2),
  [EMOJI_UHU]     = ACTION_FUNCTION_OPT(EMOJI,UHU),
  [EMOJI_SMRK1]   = ACTION_FUNCTION_OPT(EMOJI,SMRK1),
  [EMOJI_SMRK2]   = ACTION_FUNCTION_OPT(EMOJI2,SMRK2),
  [EMOJI_LOVE]    = ACTION_FUNCTION_OPT(EMOJI2,LOVE),
  [F_EPRM]        = ACTION_FUNCTION(EPRM),
  [F_VRSN]        = ACTION_FUNCTION(VRSN),
  [F_RGB_SLD]     = ACTION_FUNCTION(RGB_SLD),
  [I3_GO_GROUP_10]= ACTION_FUNCTION_OPT(GO_GROUP,0),
  [I3_GO_GROUP_1] = ACTION_FUNCTION_OPT(GO_GROUP,1),
  [I3_GO_GROUP_2] = ACTION_FUNCTION_OPT(GO_GROUP,2),
  [I3_GO_GROUP_3] = ACTION_FUNCTION_OPT(GO_GROUP,3),
  [I3_GO_GROUP_4] = ACTION_FUNCTION_OPT(GO_GROUP,4),
  [I3_GO_GROUP_5] = ACTION_FUNCTION_OPT(GO_GROUP,5),
  [I3_GO_GROUP_6] = ACTION_FUNCTION_OPT(GO_GROUP,6),
  [I3_GO_GROUP_7] = ACTION_FUNCTION_OPT(GO_GROUP,7),
  [I3_GO_GROUP_8] = ACTION_FUNCTION_OPT(GO_GROUP,8),
  [I3_GO_GROUP_9] = ACTION_FUNCTION_OPT(GO_GROUP,9),
};

#define TAP_ONCE(code)  \
  register_code (code); \
  unregister_code (code)

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  if (record->event.pressed) {
    switch(id) {
    case EPRM:
      eeconfig_init();
      break;
    case VRSN:
      SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      break;
    case RGB_SLD:
#ifdef RGBLIGHT_ENABLE
      rgblight_mode(1);
#endif
      break;
    case GO_GROUP:
      register_code(KC_LCTL); TAP_ONCE(KC_I); unregister_code(KC_LCTL);
      TAP_ONCE(KC_G);
      if (opt == 0) {
	TAP_ONCE(39);
      } else {
	TAP_ONCE(29+opt);
      }
      break;
    case EMOJI:
      switch(opt) {
      case SHRUG:
	unicode_input_start(); register_hex(0xaf); unicode_input_finish();
	TAP_ONCE (KC_BSLS);
	register_code (KC_RSFT); TAP_ONCE (KC_MINS); TAP_ONCE (KC_9); unregister_code (KC_RSFT);
	unicode_input_start (); register_hex(0x30c4); unicode_input_finish();
	register_code (KC_RSFT); TAP_ONCE (KC_0); TAP_ONCE (KC_MINS); unregister_code (KC_RSFT);
	TAP_ONCE (KC_SLSH);
	unicode_input_start (); register_hex(0xaf); unicode_input_finish();
	break;
      case YAY:
	SEND_STRING ("\\o/");	
	break;
      case HUG:
	unicode_input_start(); register_hex(0x0f3c); unicode_input_finish();
	TAP_ONCE (KC_SPC);
	unicode_input_start(); register_hex(0x3064); unicode_input_finish();
	TAP_ONCE (KC_SPC);
	unicode_input_start(); register_hex(0x25d5); unicode_input_finish();
	unicode_input_start(); register_hex(0x005f); unicode_input_finish();
	unicode_input_start(); register_hex(0x25d5); unicode_input_finish();
	TAP_ONCE (KC_SPC);
	unicode_input_start(); register_hex(0x0f3d); unicode_input_finish();
	unicode_input_start(); register_hex(0x3064); unicode_input_finish();
	break;
      case SMILE:
	unicode_input_start(); register_hex(0x0298); unicode_input_finish();
	unicode_input_start(); register_hex(0x203f); unicode_input_finish();
	unicode_input_start(); register_hex(0x0298); unicode_input_finish();
	break;
      case SMILE2:
	unicode_input_start(); register_hex(0x0028); unicode_input_finish();
	unicode_input_start(); register_hex(0x0298); unicode_input_finish();
	unicode_input_start(); register_hex(0x203f); unicode_input_finish();
	unicode_input_start(); register_hex(0x0298); unicode_input_finish();
	unicode_input_start(); register_hex(0x0029); unicode_input_finish();
	break;
      case HMM1:
	unicode_input_start(); register_hex(0x0ca0); unicode_input_finish();
	unicode_input_start(); register_hex(0x005f); unicode_input_finish();
	unicode_input_start(); register_hex(0x0ca0); unicode_input_finish();
	break;
      case HMM2:
	unicode_input_start(); register_hex(0x0028); unicode_input_finish();
	unicode_input_start(); register_hex(0x0ca0); unicode_input_finish();
	unicode_input_start(); register_hex(0x005f); unicode_input_finish();
	unicode_input_start(); register_hex(0x0ca0); unicode_input_finish();
	unicode_input_start(); register_hex(0x0029); unicode_input_finish();
	break;
      case BEAR1:
	unicode_input_start(); register_hex(0x0295); unicode_input_finish();
	unicode_input_start(); register_hex(0x2022); unicode_input_finish();
	unicode_input_start(); register_hex(0x1d25); unicode_input_finish();
	unicode_input_start(); register_hex(0x2022); unicode_input_finish();
	unicode_input_start(); register_hex(0x0294); unicode_input_finish();
	break;
      case BEAR2:
	unicode_input_start(); register_hex(0x0028); unicode_input_finish();
	unicode_input_start(); register_hex(0x1d54); unicode_input_finish();
	unicode_input_start(); register_hex(0x1d25); unicode_input_finish();
	unicode_input_start(); register_hex(0x1d54); unicode_input_finish();
	unicode_input_start(); register_hex(0x0029); unicode_input_finish();
	break;
      case FUU:
	unicode_input_start(); register_hex(0x256d); unicode_input_finish();
	unicode_input_start(); register_hex(0x2229); unicode_input_finish();
	unicode_input_start(); register_hex(0x256e); unicode_input_finish();
	unicode_input_start(); register_hex(0x0028); unicode_input_finish();
	unicode_input_start(); register_hex(0x002d); unicode_input_finish();
	unicode_input_start(); register_hex(0x005f); unicode_input_finish();
	unicode_input_start(); register_hex(0x002d); unicode_input_finish();
	unicode_input_start(); register_hex(0x0029); unicode_input_finish();
	unicode_input_start(); register_hex(0x256d); unicode_input_finish();
	unicode_input_start(); register_hex(0x2229); unicode_input_finish();
	unicode_input_start(); register_hex(0x256e); unicode_input_finish();
	break;
      case EGGY1:
	unicode_input_start(); register_hex(0x0028); unicode_input_finish();
	unicode_input_start(); register_hex(0x256f); unicode_input_finish();
	unicode_input_start(); register_hex(0x00b0); unicode_input_finish();
	unicode_input_start(); register_hex(0x25a1); unicode_input_finish();
	unicode_input_start(); register_hex(0x00b0); unicode_input_finish();
	unicode_input_start(); register_hex(0xff09); unicode_input_finish();
	unicode_input_start(); register_hex(0x256f); unicode_input_finish();
	break;
      case EGGY2:
	unicode_input_start(); register_hex(0x30ce); unicode_input_finish();
	unicode_input_start(); register_hex(0x0028); unicode_input_finish();
	unicode_input_start(); register_hex(0x0020); unicode_input_finish();
	unicode_input_start(); register_hex(0x309c); unicode_input_finish();
	unicode_input_start(); register_hex(0x002d); unicode_input_finish();
	unicode_input_start(); register_hex(0x309c); unicode_input_finish();
	unicode_input_start(); register_hex(0x30ce); unicode_input_finish();
	unicode_input_start(); register_hex(0x0029); unicode_input_finish();
	break;
      case FACE1:
	unicode_input_start(); register_hex(0x0028); unicode_input_finish();
	unicode_input_start(); register_hex(0x002d); unicode_input_finish();
	unicode_input_start(); register_hex(0x005f); unicode_input_finish();
	unicode_input_start(); register_hex(0x002d); unicode_input_finish();
	unicode_input_start(); register_hex(0x0029); unicode_input_finish();
	break;
      case FACE2:
	unicode_input_start(); register_hex(0x0028); unicode_input_finish();
	unicode_input_start(); register_hex(0x2022); unicode_input_finish();
	unicode_input_start(); register_hex(0x005f); unicode_input_finish();
	unicode_input_start(); register_hex(0x2022); unicode_input_finish();
	unicode_input_start(); register_hex(0x0029); unicode_input_finish();
	break;
      case UHU:
	unicode_input_start(); register_hex(0x2299); unicode_input_finish();
	unicode_input_start(); register_hex(0xfe4f); unicode_input_finish();
	unicode_input_start(); register_hex(0x2299); unicode_input_finish();
	break;
      case SMRK1:
	unicode_input_start(); register_hex(0x005e); unicode_input_finish();
	unicode_input_start(); register_hex(0x032e); unicode_input_finish();
	unicode_input_start(); register_hex(0x005e); unicode_input_finish();
	break;
      }
      break;
    case EMOJI2:
      switch(opt) {
	case SMRK2:
	  unicode_input_start(); register_hex(0x0028); unicode_input_finish();
	  unicode_input_start(); register_hex(0x005e); unicode_input_finish();
	  unicode_input_start(); register_hex(0x032e); unicode_input_finish();
	  unicode_input_start(); register_hex(0x005e); unicode_input_finish();
	  unicode_input_start(); register_hex(0x0029); unicode_input_finish();
	  break;
      case LOVE:
	unicode_input_start(); register_hex(0x2665); unicode_input_finish();
	unicode_input_start(); register_hex(0x203f); unicode_input_finish();
	unicode_input_start(); register_hex(0x2665); unicode_input_finish();
	break;
      }
      break;   
    }
  }
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  if (record->event.pressed) {
    switch(id) {
      case RUN:
	return MACRO( D(LCTL), T(I), U(LCTL), T(R), END  );
      break;
    }
  }
  return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
  set_unicode_input_mode(UC_LNX);
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
    case 1:
      ergodox_right_led_1_on();
      #ifdef RGBLIGHT_ENABLE
      rgblight_setrgb(0xff,0x00,0x00);
      #endif
      break;
    case 2:
      ergodox_right_led_2_on();
      #ifdef RGBLIGHT_ENABLE
      rgblight_setrgb(0x00,0xff,0x00);
      #endif
      break;
    case 3:
      ergodox_right_led_3_on();
      #ifdef RGBLIGHT_ENABLE
       rgblight_setrgb(0x00,0x00,0xff);
      #endif
      break;
    case 4:
      ergodox_right_led_1_on(); // TODO: Make a fourth layer
      ergodox_right_led_3_on();
      break;
    default:
      // none
      break;
    }

};
