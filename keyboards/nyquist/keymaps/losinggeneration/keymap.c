#include QMK_KEYBOARD_H
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

/*
  Each layer gets a name for readability, which is then used in the keymap matrix below.
  The underscores don't mean anything - you can have a layer called STUFF or any other name.
  Layer names don't all need to be of the same length, obviously, and you can also skip them
  entirely and just use numbers.
*/
#define _QWERTY  0
#define _COLEMAK 1
#define _WORKMAN 2
#define _DVORAK  3
#define _GAME    4
#define _NUMPAD  5
#define _MOUSE   6
#define _LOWER  14
#define _RAISE  15
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  WORKMAN,
  DVORAK,
  LOWER,
  RAISE,
};

/* Custom keys & combinations to be shorter for keymaps */
#define KC_LCA LCA(KC_NO)
/* Fillers to make layering more clear */
#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define OSM_LSFT OSM(MOD_LSFT)
#define TD_CTL TD(TD_CTL_CTLALT)
#define TD_GUI TD(TD_LGUI_RGUI)
#define TD_ALT TD(TD_LALT_RALT)
#define MT_ENT SFT_T(KC_ENT)
#define MT_ESC CTL_T(KC_ESC)

/* Custom layer movements for keymaps */
#define TD_ADJ  TD(TD_ADJUST)
#define TO_GAME TO(_GAME)
#define TO_MS   TO(_MOUSE)
#define TO_NUM  TO(_NUMPAD)
#define MO_ADJ  MO(_ADJUST)

/* Mouse keys */
#define MS_BTN1 KC_MS_BTN1
#define MS_BTN2 KC_MS_BTN2
#define MS_BTN3 KC_MS_BTN3
#define MS_BTN4 KC_MS_BTN4
#define MS_BTN5 KC_MS_BTN5
#define MS_LEFT KC_MS_LEFT
#define MS_DOWN KC_MS_DOWN
#define MS_UP  KC_MS_UP
#define MS_RGHT KC_MS_RIGHT
#define MW_LEFT KC_MS_WH_LEFT
#define MW_DOWN KC_MS_WH_DOWN
#define MW_UP  KC_MS_WH_UP
#define MW_RGHT KC_MS_WH_RIGHT
#define MS_ACL0 KC_MS_ACCEL0
#define MS_ACL1 KC_MS_ACCEL1
#define MS_ACL2 KC_MS_ACCEL2

/* Tap dance keycodes */
enum tap_dance_keycodes {
  TD_CTL_CTLALT = 0,
  TD_LGUI_RGUI,
  TD_LALT_RALT,
  TD_ADJUST,
};

/*
  Used to indicate a CTRL should be pressed on one press, or CTRL+ALT on
  a double tap
*/
void dance_ctl_ctlalt_each(qk_tap_dance_state_t *state, void *user_data) {
  register_code(KC_LCTL);
  if(state->count > 1) {
    register_code(KC_LALT);
  }
}

/* Used to release CTRL or the double tapped variant CTRL+ALT */
void dance_ctl_ctlalt_reset(qk_tap_dance_state_t *state, void *user_data) {
  unregister_code(KC_LCTL);
  if(state->count > 1) {
    unregister_code(KC_LALT);
  }
}

/*
  Set ADJUST layer on the first press and off after that.
  Each is used to make sure ADJUST activates as soon as it's pressed the first
  time.
*/
void dance_adj_each(qk_tap_dance_state_t *state, void *user_data) {
  if(state->count == 1) {
    layer_on(_ADJUST);
  } else {
    layer_off(_ADJUST);
  }
}

/* Set NUMPAD layer on second tap and MOUSE layer on 3rd */
void dance_adj_finish(qk_tap_dance_state_t *state, void *user_data) {
  switch(state->count) {
    case 1: break;
    case 2:
      layer_on(_NUMPAD);
      break;
    case 3:
      layer_on(_MOUSE);
      break;
    default:
      reset_tap_dance(state);
      break;
  }
}

/* Turn off any layer that may have been tapped on */
void dance_adj_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch(state->count) {
    case 1:
      layer_off(_ADJUST);
      break;
    case 2:
      layer_off(_NUMPAD);
      break;
    case 3:
      layer_off(_MOUSE);
      break;
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_CTL_CTLALT] = ACTION_TAP_DANCE_FN_ADVANCED(dance_ctl_ctlalt_each, NULL, dance_ctl_ctlalt_reset),
  [TD_LGUI_RGUI]  = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, KC_RGUI),
  [TD_LALT_RALT]  = ACTION_TAP_DANCE_DOUBLE(KC_LALT, KC_RALT),
  [TD_ADJUST]     = ACTION_TAP_DANCE_FN_ADVANCED(dance_adj_each, dance_adj_finish, dance_adj_reset),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------..-----------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  ||   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  ||   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  ||   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  ||   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |Adjust| Ctrl | Alt  | GUI  |Lower | Bksp ||Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------'`-----------------------------------------'
 */
[_QWERTY] = KEYMAP( \
  KC_GRV  ,KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_DEL , \
  KC_TAB  ,KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC, \
  MT_ESC  ,KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, \
  OSM_LSFT,KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, MT_ENT , \
  TD_ADJ  ,TD_CTL , TD_ALT , TD_GUI , LOWER  , KC_BSPC, KC_SPC , RAISE  , KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT  \
),

/* Colemak
 * ,-----------------------------------------.,-----------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  ||   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   F  |   P  |   G  ||   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  ||   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  ||   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |Adjust| Ctrl | Alt  | GUI  |Lower | Bskp ||Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------'`-----------------------------------------'
 */
[_COLEMAK] = KEYMAP( \
  KC_GRV  ,KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_DEL , \
  KC_TAB  ,KC_Q   , KC_W   , KC_F   , KC_P   , KC_G   , KC_J   , KC_L   , KC_U   , KC_Y   , KC_SCLN, KC_BSPC, \
  MT_ESC  ,KC_A   , KC_R   , KC_S   , KC_T   , KC_D   , KC_H   , KC_N   , KC_E   , KC_I   , KC_O   , KC_QUOT, \
  OSM_LSFT,KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_K   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, MT_ENT , \
  TD_ADJ  ,TD_CTL , TD_ALT , TD_GUI , LOWER  , KC_BSPC, KC_SPC , RAISE  , KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT  \
),

/* Workman
 * ,-----------------------------------------..-----------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  ||   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Tab  |   Q  |   D  |   R  |   W  |   B  ||   J  |   F  |   U  |   P  |   ;  | Bksp |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   H  |   T  |   G  ||   Y  |   N  |   E  |   O  |   I  |  "   |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   M  |   C  |   V  ||   K  |   L  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |Adjust| Ctrl | Alt  | GUI  |Lower | Bskp ||Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------'`-----------------------------------------'
 */
[_WORKMAN] = KEYMAP( \
  KC_GRV  ,KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_DEL , \
  KC_TAB  ,KC_Q   , KC_D   , KC_R   , KC_W   , KC_B   , KC_J   , KC_F   , KC_U   , KC_P   , KC_SCLN, KC_BSPC, \
  MT_ESC  ,KC_A   , KC_S   , KC_H   , KC_T   , KC_G   , KC_Y   , KC_N   , KC_E   , KC_O   , KC_I   , KC_QUOT, \
  OSM_LSFT,KC_Z   , KC_X   , KC_M   , KC_C   , KC_V   , KC_K   , KC_L   , KC_COMM, KC_DOT , KC_SLSH, MT_ENT , \
  TD_ADJ  ,TD_CTL , TD_ALT , TD_GUI , LOWER  , KC_BSPC, KC_SPC , RAISE  , KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT  \
),

/* Dvorak
 * ,-----------------------------------------..-----------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  ||   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  ||   F  |   G  |   C  |   R  |   L  | Bksp |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  ||   D  |   H  |   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  ||   B  |   M  |   W  |   V  |   Z  |Enter |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |Adjust| Ctrl | Alt  | GUI  |Lower | Bskp ||Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------'`-----------------------------------------'
 */
[_DVORAK] = KEYMAP( \
  KC_GRV  ,KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_DEL , \
  KC_TAB  ,KC_QUOT, KC_COMM, KC_DOT , KC_P   , KC_Y   , KC_F   , KC_G   , KC_C   , KC_R   , KC_L   , KC_BSPC, \
  MT_ESC  ,KC_A   , KC_O   , KC_E   , KC_U   , KC_I   , KC_D   , KC_H   , KC_T   , KC_N   , KC_S   , KC_SLSH, \
  OSM_LSFT,KC_SCLN, KC_Q   , KC_J   , KC_K   , KC_X   , KC_B   , KC_M   , KC_W   , KC_V   , KC_Z   , MT_ENT , \
  TD_ADJ  ,TD_CTL , TD_ALT , TD_GUI , LOWER  , KC_BSPC, KC_SPC , RAISE  , KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT  \
),

/* Game (Qwerty without one shot modifiers & tap dancing)
 * ,-----------------------------------------..-----------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  ||   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  ||   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  ||   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  ||   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |Adjust| Ctrl | Alt  | GUI  |Lower |Space ||Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------'`-----------------------------------------'
 */
[_GAME] = KEYMAP( \
  KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_DEL , \
  KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC, \
  KC_ESC , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, \
  KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_ENT , \
  MO_ADJ , KC_LCTL, KC_LALT, KC_LGUI, LOWER  , KC_SPC , KC_SPC , RAISE  , KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT  \
),

/* Number pad
 * ,-----------------------------------------..-----------------------------------------.
 * | XXX  | XXX  | XXX  | XXX  | XXX  | XXX  || XXX  | NLCK |  *   |   /  | BKSP | XXX  |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Tab  | XXX  | XXX  | XXX  | XXX  | XXX  || XXX  |   7  |  8   |   9  |  -   | XXX  |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Esc  | XXX  | XXX  | XXX  | XXX  | XXX  || XXX  |   4  |  5   |   6  |  +   | XXX  |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |Shift | XXX  | XXX  | XXX  | XXX  | XXX  || XXX  |   1  |  2   |   3  | ENT  | XXX  |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |Adjust| Ctrl | Alt  | GUI  | XXX  |Space ||Space |   0  |  0   |   .  | ENT  | XXX  |
 * `-----------------------------------------''-----------------------------------------'
 */
[_NUMPAD] =  KEYMAP( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_NLCK, KC_PAST, KC_PSLS, KC_BSPC, XXXXXXX, \
  KC_TAB , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_P7  , KC_P8  , KC_P9  , KC_PMNS, XXXXXXX, \
  KC_ESC , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_P4  , KC_P5  , KC_P6  , KC_PPLS, XXXXXXX, \
  KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_P1  , KC_P2  , KC_P3  , KC_PENT, XXXXXXX, \
  TD_ADJ , TD_CTL , TD_ALT , TD_GUI , XXXXXXX, KC_SPC , KC_SPC , KC_P0  , KC_P0  , KC_PDOT, KC_PENT, XXXXXXX  \
),

/* Mouse movement
 * ,-----------------------------------------..-----------------------------------------.
 * | XXX  | XXX  | XXX  | XXX  | XXX  | XXX  || XXX  | XXX  | XXX  | XXX  | XXX  | XXX  |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Tab  | MB_1 | MB_3 | MB_2 | MB_4 | MB_5 || MA_0 | MB_1 | MB_3 | MB_2 | MB_4 | MB_5 |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Esc  | MW_L | MW_U | MW_D | MW_R | XXX  || MA_1 | M_LT | M_UP | M_DN | M_RT | XXX  |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |Shift | MA_0 | MA_1 | MA_2 | XXX  | XXX  || MA_2 | MW_L | MW_U | MW_D | MW_R | XXX  |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |Adjust| Ctrl | Alt  | GUI  | XXX  |Space || XXX  | XXX  | XXX  |  XXX | XXX  | XXX  |
 * `-----------------------------------------''-----------------------------------------'
 */
[_MOUSE] =  KEYMAP( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  KC_TAB , MS_BTN1, MS_BTN3, MS_BTN2, MS_BTN4, MS_BTN5, MS_ACL0, MS_BTN1, MS_BTN3, MS_BTN2, MS_BTN4, MS_BTN5, \
  KC_ESC , MW_LEFT, MW_DOWN, MW_UP  , MW_RGHT, XXXXXXX, MS_ACL1, MS_LEFT, MS_DOWN, MS_UP  , MS_RGHT, XXXXXXX, \
  KC_LSFT, MS_ACL0, MS_ACL1, MS_ACL2, XXXXXXX, XXXXXXX, MS_ACL2, MW_LEFT, MW_DOWN, MW_UP  , MW_RGHT, XXXXXXX, \
  TD_ADJ , TD_CTL , TD_ALT , TD_GUI , XXXXXXX, KC_SPC , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  \
),

/* Lower
 * ,-----------------------------------------..-----------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  ||   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |   ~  |   !  |   @  |   #  |   $  |   %  ||   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  ||  F6  |   _  |   +  |      |   \  |  |   |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 ||  F12 | PgUp | PgDn | Home | End  |      |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |      |      |      |      |      |      ||      |      | Mute | Vol- | Vol+ |      |
 * `-----------------------------------------'`-----------------------------------------'
 */
[_LOWER] = KEYMAP( \
  KC_TILD, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL , \
  KC_TILD, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, \
  KC_DEL , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
  _______, KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_PGUP, KC_PGDN, KC_HOME, KC_END , _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______  \
),

/* Raise
 * ,-----------------------------------------..-----------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  ||   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  ||   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  ||  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 ||  F12 | PgUp | PgDn | Home | End  |      |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |      |      |      |      |      |      ||      |      | Mute | Vol- | Vol+ |      |
 * `-----------------------------------------''-----------------------------------------'
 */
[_RAISE] = KEYMAP( \
  KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_DEL , \
  KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSPC, \
  KC_DEL , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_MINS, KC_EQL , KC_LBRC, KC_RBRC, KC_BSLS, \
  _______, KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_PGUP, KC_PGDN, KC_HOME, KC_END , _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______  \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------..-----------------------------------------.
 * | RESET|DEBUG |      |      |      |      ||      |      |      |      |      |      |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |      ||      | Game |Numpad| Mouse|      |      |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |      |  F5  |  F6  |  F7  |  F8  |      ||      |Qwerty|Colmak|Workmn|Dvorak|      |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | CAPS |  F9  |  F10 |  F11 |  F12 |      ||      |      |      |      |  Up  |      |
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * |      |      |      |      |      |      ||      |      | XXX  | Left | Down |Right |
 * `-----------------------------------------''-----------------------------------------'
 */
[_ADJUST] =  KEYMAP( \
   RESET , DEBUG  , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, KC_F1  ,  KC_F2 , KC_F3  , KC_F4  , _______, _______, TO_GAME, TO_NUM , TO_MS  , _______, _______, \
  _______, KC_F5  ,  KC_F6 , KC_F7  , KC_F8  , _______, _______, QWERTY , COLEMAK, WORKMAN, DVORAK , _______, \
  KC_CAPS, KC_F9  ,  KC_F10, KC_F11 , KC_F12 , _______, _______, _______, _______, _______, KC_UP  , _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT  \
)

};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
float tone_workman[][2]    = SONG(PLOVER_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  layer_state_set(default_layer);
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_colemak);
        #endif
        persistent_default_layer_set(1UL<<_COLEMAK);
      }
      return false;
      break;
    case WORKMAN:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_workman);
        #endif
        persistent_default_layer_set(1UL<<_WORKMAN);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_dvorak);
        #endif
        persistent_default_layer_set(1UL<<_DVORAK);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
  }

  return true;
}
