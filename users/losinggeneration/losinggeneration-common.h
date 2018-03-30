#ifndef LOSINGGENERATION_COMMON_H
#define LOSINGGENERATION_COMMON_H

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

/*
 * This will expand values sent to it to send to the KEYMAP macro so defines
 * can be used by KEYMAP
 */
#define CATMAP(...) KEYMAP(__VA_ARGS__)

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

#endif
