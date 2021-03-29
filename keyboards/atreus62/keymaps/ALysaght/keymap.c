// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

// qmk compile -kb atreus62
// qmk flash -kb atreus62

#include QMK_KEYBOARD_H

enum layer_names {
  _QWERTY,
  _LOWER,
  _RAISE,
  _NUM,
  _ADJUST
};

enum keymap_custom_keycodes {
  LOWER = SAFE_RANGE,
  RAISE,
  R_ASIGN,
  R_PIPE,
  GITFETC,
  GITPULL,
  GITPUSH,
  GITREBA,
  GITADD,
  GITCOMM,
  GITBRCH,
  GITCOUT,
  GITWTAD,
  GITWTPR,
  GITSTAT,
  GITBDEL,
  GITMAIN,
  GITORIG
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Qwerty layer, more "standard" for other people who may need to use my keyboard or for games where using Qwerty is just easier
 * ,-----------------------------------------.                ,-----------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |                |   6  |   7  |   8  |   9  |   0  |  \   |
 * |------+------+------+------+------+------|                |------+------+------+------+------+------|
 * | `    |   Q  |   W  |   E  |   R  |   T  |                |   Y  |   U  |   I  |   O  |   P  |  [   |
 * |------+------+------+------+------+------|                |------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |,------.,------.|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------||      ||      ||------+------+------+------+------+------|
 * |Shift |   Z  |   X  |   C  |   V  |   B  ||Super ||SftEnt||   N  |   M  |   ,  |   .  |   /  |SftEnt|
 * |------+------+------+------+------+------||      ||      ||------+------+------+------+------+------|
 * | NUM  |Ctrl  | Alt  |   _  |Lower | Bksp |`------'`------'|Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------'                `-----------------------------------------'
 */

  [_QWERTY] = LAYOUT(
      KC_ESC,     KC_1,    KC_2,    KC_3,    KC_4,      KC_5,                         KC_6,    KC_7,       KC_8,    KC_9,      KC_0,    KC_BSLS,
      KC_GRV,     KC_Q,    KC_W,    KC_E,    KC_R,      KC_T,                         KC_Y,    KC_U,       KC_I,    KC_O,      KC_P,    KC_LBRC,
      KC_TAB,     KC_A,    KC_S,    KC_D,    KC_F,      KC_G,                         KC_H,    KC_J,       KC_K,    KC_L,   KC_SCLN,    KC_QUOT,
     KC_LSFT,     KC_Z,    KC_X,    KC_C,    KC_V,      KC_B,                         KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_SFTENT,
    TG(_NUM),  KC_LCTL, KC_LALT, KC_UNDS,   LOWER,   KC_BSPC,  KC_LGUI,  KC_SFTENT, KC_SPC,   RAISE,    KC_LEFT, KC_DOWN,     KC_UP,   KC_RIGHT
  ),


  /* "Lower" layer
 * ,-----------------------------------------.                ,-----------------------------------------.
 * |  F11 |  F1  |  F2  |  F3  |  F4  |  F5  |                |  F6  |  F7  |  F8  |  F9  | F10  | F12  |
 * |------+------+------+------+------+------|                |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                |      |      |      |      |      |  ]   |
 * |------+------+------+------+------+------|                |------+------+------+------+------+------|
 * |      |      |      |      |      |      |,------.,------.|      |  <-  |  %>% |   -  |   =  |      |
 * |------+------+------+------+------+------||      ||      ||------+------+------+------+------+------|
 * |      |      |      |      |      |      ||      ||      ||      |      |      |      |      |      |
 * |------+------+------+------+------+------||      ||      ||------+------+------+------+------+------|
 * |      |      |      |ScrSht|      | Del  |`------'`------'|  Ins |      | Mute | VolD | VolU | Play |
 * `-----------------------------------------'                `-----------------------------------------'
 */

  [_LOWER] = LAYOUT(
     KC_F11,        KC_F1,   KC_F2,         KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,   KC_F12,
    _______,      _______, _______,       _______, _______, _______,                   _______, _______, _______, _______, _______,  KC_RBRC,
    _______,      _______, _______,       _______, _______, _______,                   _______, R_ASIGN,  R_PIPE, KC_MINS,  KC_EQL,  _______,
    _______,      _______, _______,       _______, _______, _______,                   _______, _______, _______, _______, _______,  _______,
    SGUI(KC_F12), _______, _______, SGUI(C(KC_4)), _______,  KC_DEL,  _______, _______, KC_INS, _______, KC_MUTE, KC_VOLD, KC_VOLU,  KC_MPLY
  ),



  /* "Raise" layer
 * ,-----------------------------------------.                ,-----------------------------------------.
 * |      |      |      |      |      |      |                |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                |------+------+------+------+------+------|
 * |      |GITCOU|GITFET|GITPUL|GITREB|      |                |      |      |      |  <-  | %>%  |      |
 * |------+------+------+------+------+------|                |------+------+------+------+------+------|
 * |      |GITADD|GITSTA|GITCOM|GITPUS|      |,------.,------.|      |Origin|      |      |      |      |
 * |------+------+------+------+------+------||      ||      ||------+------+------+------+------+------|
 * |      |GITBRC|GITBDE|GITWTA|GITWTP|      ||      ||      ||      | Main |      |      |      |      |
 * |------+------+------+------+------+------||      ||      ||------+------+------+------+------+------|
 * |      |      |      |      |      |      |`------'`------'|      |      | Home | PgDn | PgUp | End  |
 * `-----------------------------------------'                `-----------------------------------------'
 */

[_RAISE] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  _______, GITCOUT, GITFETC, GITPULL, GITREBA, _______,                    _______, _______, _______, R_ASIGN,  R_PIPE, _______,
  _______,  GITADD, GITSTAT, GITCOMM, GITPUSH, _______,                    _______, GITORIG, _______, _______, _______, _______,
  _______, GITBRCH, GITBDEL, GITWTAD, GITWTPR, _______,                    _______, GITMAIN, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP,  KC_END
),


  /* "Numpad" layer
 * ,-----------------------------------------.                ,-----------------------------------------.
 * |      |      |      |      |      |      |                |  NO  |Clear |  NO  |  NO  |   *  |  NO  |
 * |------+------+------+------+------+------|                |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                |  NO  |   7  |   8  |   9  |   +  |  NO  |
 * |------+------+------+------+------+------|                |------+------+------+------+------+------|
 * |      |      |      |      |      |      |,------.,------.|  NO  |   4  |   5  |   6  |   -  |  NO  |
 * |------+------+------+------+------+------||      ||      ||------+------+------+------+------+------|
 * |      |      |      |      |      |      ||Clear ||Enter || Spc  |   1  |   2  |   3  |   /  |Enter |
 * |------+------+------+------+------+------||      ||      ||------+------+------+------+------+------|
 * |      |      |      |      |      | Bksp |`------'`------'|   0  |   .  | Left | Down |  Up  |Right |
 * `-----------------------------------------'                `-----------------------------------------'
 */

  [_NUM] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                   XXXXXXX,    KC_C, XXXXXXX, XXXXXXX, KC_PAST, XXXXXXX,
    _______, _______, _______, _______, _______, _______,                   XXXXXXX, KC_KP_7, KC_KP_8, KC_KP_9, KC_PPLS, XXXXXXX,
    _______, _______, _______, _______, _______, _______,                   XXXXXXX, KC_KP_4, KC_KP_5, KC_KP_6, KC_PMNS, XXXXXXX,
    _______, _______, _______, _______, _______, _______,                    KC_SPC, KC_KP_1, KC_KP_2, KC_KP_3, KC_PSLS, KC_PENT,
    _______, _______, _______, _______, _______, KC_BSPC,    KC_C, KC_PENT, KC_KP_0, KC_PDOT, KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT
  ),



  /* "Adjust" layer, only active if both "Lower" and "Raise" are active at the same time
   * All unused keys are blanked out for this layer
   * ,-----------------------------------------.                ,-----------------------------------------.
   * |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |                |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |
   * |------+------+------+------+------+------|                |------+------+------+------+------+------|
   * |  NO  |RESET |  NO  |  NO  |  NO  |  NO  |                |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |
   * |------+------+------+------+------+------|                |------+------+------+------+------+------|
   * |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |,------.,------.|  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |
   * |------+------+------+------+------+------||      ||      ||------+------+------+------+------+------|
   * |  NO  |  NO  |  NO  |  NO  |  NO  |  NO  ||      ||      ||  NO  |  NO  |  NO  |  NO  |  NO  |  NO  |
   * |------+------+------+------+------+------||      ||      ||------+------+------+------+------+------|
   * |  NO  |  NO  |  NO  |  NO  |      |  NO  |`------'`------'|  NO  |      |  NO  |  NO  |  NO  |  NO  |
   * `-----------------------------------------'                `-----------------------------------------'
   */

  [_ADJUST] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX,   RESET, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  )

};



bool process_record_user( uint16_t keycode, keyrecord_t *record ) {
  switch ( keycode ) {
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
    case R_ASIGN:
      if (record->event.pressed) {
        SEND_STRING("<- ");
      }
      break;
    case R_PIPE:
      if (record->event.pressed) {
        SEND_STRING(" %>%\n");
      }
      break;
    case GITFETC:
      if (record->event.pressed) {
        SEND_STRING("git fetch ");
      }
      break;
    case GITPULL:
      if (record->event.pressed) {
        SEND_STRING("git pull ");
      }
      break;
    case GITPUSH:
      if (record->event.pressed) {
        SEND_STRING("git push ");
      }
      break;
     case GITREBA:
       if (record->event.pressed) {
         SEND_STRING("git pull --rebase ");
       }
       break;
     case GITADD:
       if (record->event.pressed) {
         SEND_STRING("git add ");
       }
       break;
     case GITCOMM:
       if (record->event.pressed) {
         SEND_STRING("git commit -m ");
       }
       break;
     case GITBRCH:
       if (record->event.pressed) {
         SEND_STRING("git branch ");
       }
       break;
     case GITCOUT:
       if (record->event.pressed) {
         SEND_STRING("git checkout ");
       }
       break;
     case GITWTAD:
       if (record->event.pressed) {
         SEND_STRING("git worktree add ");
       }
       break;
     case GITWTPR:
       if (record->event.pressed) {
         SEND_STRING("git git worktree prune ");
       }
       break;
     case GITSTAT:
       if (record->event.pressed) {
         SEND_STRING("git status ");
       }
       break;
     case GITBDEL:
       if (record->event.pressed) {
         SEND_STRING("git branch -d ");
       }
       break;
     case GITMAIN:
       if (record->event.pressed) {
         SEND_STRING("main ");
       }
       break;
     case GITORIG:
       if (record->event.pressed) {
         SEND_STRING("origin ");
       }
       break;
  }
  return true;
};
