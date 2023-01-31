// This is Sean Hunter's keymap file, customized from the canonical layout file for the Quantum project.
// If you want to add another keyboard, that is the style you want to emulate.

#include QMK_KEYBOARD_H
#include "mymappings.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.

enum planck_layers {
  _DVRK,
  _LOWER,
  _RAISE,
  _SDRK,
  _SLWER,
  _SRAIS,
  _NMPD,
  _MVMT,
  _ADJUST
};

enum planck_keycodes {
  DVRK = SAFE_RANGE,
  LOWER,
  RAISE,
  SDRK,
  SLWER,
  SRAIS,
  BACKLIT,
  BACKTOG,
  CUT,
  COPY,
  PASTE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * |   "  |   ,  |   .  |   P  |   Y  |   /  |   =  |   F  |   G  |   C  |   R  |   L  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   A  |   O  |   E  |   U  |   I  | ESC  | BSPC |   D  |   H  |   T  |   N  |   S  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   ;  |   Q  |   J  |   K  |   X  | TAB  | ENT  |   B  |   M  |   W  |   V  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Sft  | Ctl  | Alt  | Gui  |Lower |    Space    |Raise |   <  |   v  |   ^  |   >  |
 * `-----------------------------------------------------------------------------------'
 */
[_DVRK] = LAYOUT_planck_grid(
  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_SLSH, KC_EQL,  KC_F,     KC_G,    KC_C,   KC_R,    KC_L,
  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_ESC,  KC_BSPC, KC_D,     KC_H,    KC_T,   KC_N,    KC_S,
  KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_TAB,  KC_ENT,  KC_B,     KC_M,    KC_W,   KC_V,    KC_Z,
  KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE, KC_LEFT, KC_DOWN,  KC_UP, KC_RIGHT
),


/* Lower
 * ,-----------------------------------------------------------------------------------.
 * | F1   |  F2  |  F3  |  F4  |  F5  |  {   |  }   |  F6  |  F7  |  F8  |  F9  | F10  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  1   |   2  |   3  |   4  |   5  |  [   |  ]   |   6  |   7  |   8  |   9  |  0   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |   ~  |   |  |   `  |   -  |   _  | INS  | DEL  |   (  |   )  |   +  |   =  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Sft  | Ctl  | Alt  | Gui  |Lower |             |Raise | Home | PgDn | PgUp | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_LCBR, KC_RCBR, KC_F6,     KC_F7,    KC_F8,   KC_F9,    KC_F10,
  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_LBRC, KC_RBRC, KC_6,      KC_7,     KC_8,    KC_9,     KC_0,
  KC_TILD, KC_PIPE, KC_GRV,  KC_MINS, KC_UNDS, KC_INS,  KC_DEL,  KC_LPRN,   KC_RPRN,  KC_PLUS, KC_EQL,   KC_BSLS,
  _______, _______, _______, _______, _______, _______, _______, _______,   KC_HOME,  KC_PGDN, KC_PGUP,  KC_END
),


/* Raise
 * ,-----------------------------------------------------------------------------------.
 * | F11  |  F12 |  F13 |  F14 |  F15 |      |      |  F16 |  F17 |  F18 |  F19 | F20  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  !   |   @  |   #  |   $  |   %  |Sleep | Wake |   ^  |   &  |   *  |   (  |  )   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | GUI1 | GUI2 | GUI3 | GUI4 | GUI5 |             | GUI6 | GUI7 | GUI8 | GUI9 |GUI10 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Sft  | Ctl  | Alt  | Gui  |Lower |             |Raise | Gui  | Alt  | Ctl  | Sft  |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
   KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15, _______, _______,   KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,
  KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC, KC_SLEP, KC_WAKE,   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
    GUI_1,   GUI_2,   GUI_3,   GUI_4,   GUI_5, _______, _______,     GUI_6,   GUI_7,   GUI_8,   GUI_9,  GUI_10,
  KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,   LOWER,  KC_SPC,  KC_SPC,     RAISE, KC_RGUI, KC_RALT, KC_RCTL, KC_RSFT
),

/* 'Software Dvorak': Designed to look like dvorak in the mapping but depend on software
 * dvorak (ie the OS keymapping changed to dvorak).
 * ,-----------------------------------------------------------------------------------.
 * |   "  |   ,  |   .  |   P  |   Y  |   /  |   =  |   F  |   G  |   C  |   R  |   L  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   A  |   O  |   E  |   U  |   I  | ESC  | BSPC |   D  |   H  |   T  |   N  |   S  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   ;  |   Q  |   J  |   K  |   X  | TAB  | ENT  |   B  |   M  |   W  |   V  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Sft  | Ctl  | Alt  | Gui  |SLower|    Space    |SRaise|   <  |   v  |   ^  |   >  |
 * `-----------------------------------------------------------------------------------'
 */
[_SDRK] = LAYOUT_planck_grid(
  DV_QUOT, DV_COMM, DV_DOT,  DV_P,    DV_Y,    DV_SLSH, DV_EQL,  DV_F,     DV_G,    DV_C,   DV_R,    DV_L,
  DV_A,    DV_O,    DV_E,    DV_U,    DV_I,    KC_ESC,  KC_BSPC, DV_D,     DV_H,    DV_T,   DV_N,    DV_S,
  DV_SCLN, DV_Q,    DV_J,    DV_K,    DV_X,    KC_TAB,  KC_ENT,  DV_B,     DV_M,    DV_W,   DV_V,    DV_Z,
  KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, SLWER,   KC_SPC,  KC_SPC, SRAIS, KC_LEFT, KC_DOWN,  KC_UP, KC_RIGHT
),


/* 'Software dvorak lower mode':  Puts all the braces etc in the right places so it works
 * just like the lower mode above except that it depends on the OS keymapping being set
 * to dvorak.
 * ,-----------------------------------------------------------------------------------.
 * | F1   |  F2  |  F3  |  F4  |  F5  |  {   |  }   |  F6  |  F7  |  F8  |  F9  | F10  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  1   |   2  |   3  |   4  |   5  |  [   |  ]   |   6  |   7  |   8  |   9  |  0   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |   ~  |   |  |   `  |   -  |   _  | INS  | DEL  |   (  |   )  |   +  |   =  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Sft  | Ctl  | Alt  | Gui  |SLower|             |SRaise| Home | PgDn | PgUp | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_SLWER] = LAYOUT_planck_grid(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   DV_LCBR, DV_RCBR, KC_F6,     KC_F7,    KC_F8,   KC_F9,    KC_F10,
  DV_1,    DV_2,    DV_3,    DV_4,    DV_5,    DV_LBRC, DV_RBRC, DV_6,      DV_7,     DV_8,    DV_9,     DV_0,
  DV_TILD, DV_PIPE, DV_GRV,  DV_MINS, DV_UNDS, KC_INS,  KC_DEL,  DV_LPRN,   DV_RPRN,  DV_PLUS, DV_EQL,   DV_BSLS,
  _______, _______, _______, _______, _______, _______, _______, _______,   KC_HOME,  KC_PGDN, KC_PGUP,  KC_END
),


/* 'Software dvorak raise mode'
 * ,-----------------------------------------------------------------------------------.
 * | F11  |  F12 |  F13 |  F14 |  F15 |      |      |  F16 |  F17 |  F18 |  F19 | F20  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  !   |   @  |   #  |   $  |   %  |Sleep | Wake |   ^  |   &  |   *  |   (  |  )   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | GUI1 | GUI2 | GUI3 | GUI4 | GUI5 |             | GUI6 | GUI7 | GUI8 | GUI9 |GUI10 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Sft  | Ctl  | Alt  | Gui  |Lower |             |Raise | Gui  | Alt  | Ctl  | Sft  |
 * `-----------------------------------------------------------------------------------'
 */
[_SRAIS] = LAYOUT_planck_grid(
   KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15, _______, _______,   KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,
  DV_EXLM,   DV_AT, DV_HASH,  DV_DLR, DV_PERC, KC_SLEP, KC_WAKE,   DV_CIRC, DV_AMPR, DV_ASTR, DV_LPRN, DV_RPRN,
    GUI_1,   GUI_2,   GUI_3,   GUI_4,   GUI_5, _______, _______,     GUI_6,   GUI_7,   GUI_8,   GUI_9,  GUI_10,
  KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,   SLWER,  KC_SPC,  KC_SPC,     SRAIS, KC_RGUI, KC_RALT, KC_RCTL, KC_RSFT
),


/* Adjust (Lower + Raise or SLower + SRaise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |AGnorm|AGswap|      |      |HRevl |HReset|HMenu |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | PWR  | EJCT | CUT  | COPY |PASTE |PrScr |SysReq| CAPS | <<   |  >>  | Mute | Stop |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |DVORAK|NUMPAD| MVMT | SDRK |      |      |      |      | Next | Vol- | Vol+ | Play |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Brite |BToggl|      |      |             |      |      | Gui  | Alt  | Ctl  | Sft  |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
  _______,     QK_BOOT, _______, _______, _______, AG_NORM,   AG_SWAP, _______, _______,    HRVL,  HRESET,  HMENU,
   KC_PWR,   KC_EJCT,       CUT,    COPY,   PASTE, KC_PSCR, KC_SYSREQ, KC_CAPS, KC_MRWD, KC_MFFD, KC_MUTE, KC_MSTP,
     DVRK, TO(_NMPD), TO(_MVMT),    SDRK, _______, _______,   _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY,
  BACKLIT,   BACKTOG,   _______, _______, _______, _______,   _______, _______, KC_RGUI, KC_RALT, KC_RCTL, KC_RSFT
),


/* Numpad
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |NumLck|   7  |   8  |   9  |   /  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |Enter |   4  |   5  |   6  |   *  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |DVORAK|NUMPAD| MVMT | SDRK |      |      |      |      |   3  |   2  |   1  |   -  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |   0  |   .  |   +  |
 * `-----------------------------------------------------------------------------------'
 */
[_NMPD] = LAYOUT_planck_grid(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_NLCK, KC_P7,   KC_P8,   KC_P9,   KC_PSLS,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PENT, KC_P4,   KC_P5,   KC_P6,   KC_PAST,
    TO(_DVRK),TO(_NMPD),TO(_MVMT),SDRK, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_P1,   KC_P2,   KC_P3,   KC_PMNS,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_P0,   KC_PDOT, KC_PPLS
),


/* Movement
 * ,-----------------------------------------------------------------------------------.
 * |MsBut2|MsWhDn|MsWhUp|MsBut1|MsBut3|      |      |      | Home | PgDn | PgUp |  End |
 * +------+------+------+------+------+------+------+------+------+------+------+------+
 * |Ms Lft|Ms Dn |Ms Up |Ms Rht|      |      |      |      | Left | Down |  Up  | Right|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |DVORAK|NUMPAD| MVMT | SDRK |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Sft  | Ctl  | Alt  | Gui  |      |             |      | Gui  | Alt  | Ctl  | Sft  |
 * `-----------------------------------------------------------------------------------'
 */
[_MVMT] = LAYOUT_planck_grid(
    KC_MB2,  KC_MWDN, KC_MWUP, KC_MB1,   KC_MB3, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END,
    KC_MLFT, KC_MDN,  KC_MUP,  KC_MRGT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
    TO(_DVRK),TO(_NMPD),TO(_MVMT),SDRK,XXXXXXX,XXXXXXX,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, _______, _______, _______, _______, KC_RGUI, KC_RALT, KC_RCTL, KC_RSFT
),
};


void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case DVRK:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_DVRK);
        layer_on(_DVRK);
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
    case SDRK:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_SDRK);
        layer_on(_SDRK);
      }
      return false;
      break;
    case SLWER:
      if (record->event.pressed) {
        layer_on(_SLWER);
        update_tri_layer(_SLWER, _SRAIS, _ADJUST);
      } else {
        layer_off(_SLWER);
        update_tri_layer(_SLWER, _SRAIS, _ADJUST);
      }
      return false;
      break;
    case SRAIS:
      if (record->event.pressed) {
        layer_on(_SRAIS);
        update_tri_layer(_SLWER, _SRAIS, _ADJUST);
      } else {
        layer_off(_SRAIS);
        update_tri_layer(_SLWER, _SRAIS, _ADJUST);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
      } else {
        unregister_code(KC_RSFT);
      }
      return false;
      break;
    case BACKTOG:
      if (record->event.pressed) {
        #ifdef BACKLIGHT_ENABLE
          backlight_toggle();
        #endif
      }
      return false;
      break;
    case CUT: //cut macro
	    return MACRODOWN( DOWN(KC_LCTL), TYPE(KC_X), UP(KC_LCTL), END );
    case COPY: // copy macro
	    return MACRODOWN( DOWN(KC_LCTL), TYPE(KC_C), UP(KC_LCTL), END );
    case PASTE: // paste macro
	    return MACRODOWN( DOWN(KC_LCTL), TYPE(KC_V), UP(KC_LCTL), END );
  }
  return true;
}

void matrix_init_user(void) {
}
