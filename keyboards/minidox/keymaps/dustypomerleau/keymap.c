// dustypomerleau, Minidox keymap
// Thanks for checking out my keymap. The rationale behind this layout is described in the README.

#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

enum custom_layers {
  _CMK_DHM,
  _QWERTY,
  _MEDIA,
  _NAV,
  _NUM,
  _SYM_L,
  _SYM_R,
  _SYS
};

enum custom_keycodes {
  CMK_DHM = SAFE_RANGE,
  QWERTY,
  NAV,
  NUM,
  SYM_L,
  SYM_R,
  ALT_OP,
  CTL_CCB,
  GUI_CP
};

#define _______ KC_TRNS
#define ALT_2 LALT_T(KC_2)
#define ALT_3 LALT_T(KC_3)
#define ALT_8 LALT_T(KC_8)
#define ALT_D LALT_T(KC_D)
#define ALT_E LALT_T(KC_E)
#define ALT_K LALT_T(KC_K)
#define ALT_OB LALT_T(KC_LBRC)
#define ALT_S LALT_T(KC_S)
#define CTRL_2 LCTL_T(KC_2)
#define CTRL_4 LCTL_T(KC_4)
#define CTRL_5 LCTL_T(KC_5)
#define CTRL_9 LCTL_T(KC_9)
#define CTRL_EQ LCTL_T(KC_EQL)
#define CTRL_I LCTL_T(KC_I)
#define CTRL_L LCTL_T(KC_L)
#define CTRL_R LCTL_T(KC_R)
#define CTRL_S LCTL_T(KC_S)
#define GUI_0 LGUI_T(KC_0)
#define GUI_1 LGUI_T(KC_1)
#define GUI_4 LGUI_T(KC_4)
#define GUI_7 LGUI_T(KC_7)
#define GUI_CB LGUI_T(KC_RBRC)
#define GUI_F LGUI_T(KC_F)
#define GUI_J LGUI_T(KC_J)
#define GUI_N LGUI_T(KC_N)
#define GUI_T LGUI_T(KC_T)
#define MAC_EM S(LALT(KC_MINS))
#define MAC_EN LALT(KC_MINS)
#define NAV_BK LT(_NAV, KC_BSPC)
#define NAV_LK TG(_NAV)
#define NUM_LK TG(_NUM)
#define NUM_SPC LT(_NUM, KC_SPC)
#define SFT_OS OSM(MOD_LSFT)
#define SYML_OS OSL(_SYM_L)
#define SYMR_OS OSL(_SYM_R)
#define VOL_DN S(LALT(KC__VOLDOWN))
#define VOL_UP S(LALT(KC__VOLUP))
#define XXXXXXX KC_NO

#define SYMBOL_LAYER LAYOUT( \
  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,      KC_CIRC, KC_AMPR, KC_ASTR, KC_QUES, KC_QUOT, \
  KC_PLUS, CTRL_EQ, ALT_OP,  GUI_CP,  KC_DQT,       KC_COLN, GUI_CB,  ALT_OB,  CTL_CCB, KC_LCBR, \
  KC_LT,   KC_PIPE, KC_MINS, KC_GT,   KC_BSLS,      KC_GRV,  KC_UNDS, KC_SLSH, KC_TILD, KC_SCLN, \
                    _______, _______, MAC_EN,       MAC_EM,  _______, _______,                   \
)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Colemak DHm
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   Q  |   W  |   F  |   P  |   B  |           |   J  |   L  |   U  |   Y  |   '  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   A  | CTL/R| ALT/S| GUI/T|   G  |           |   M  | GUI/N| ALT/E| CTL/I|   O  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   Z  |   X  |   C  |   D  |   V  |           |   K  |   H  |   ,  |   .  |   ;  |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,--------------------.
 *                  |SYMLOS|SFT_OS|      |    |      |SFT_OS|SYMROS|
 *                  `------+------|NAV_BK|    |NUMSPC|------+------'
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_CMK_DHM] = LAYOUT( \
  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,         KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT, \
  KC_A,    CTRL_R,  ALT_S,   GUI_T,   KC_G,         KC_M,    GUI_N,   ALT_E,   CTRL_I,  KC_O,    \
  KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,         KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SCLN, \
                    SYML_OS, SFT_OS,  NAV_BK,       NUM_SPC, SFT_OS,  SYMR_OS                    \
),

/* QWERTY
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   Q  |   W  |   E  |   R  |   T  |           |   Y  |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   A  | CTL/S| ALT/D| GUI/F|   G  |           |   H  | GUI/J| ALT/K| CTL/L|   '  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   Z  |   X  |   C  |   V  |   B  |           |   N  |   M  |   ,  |   .  |   ;  |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,--------------------.
 *                  |SYMLOS|SFT_OS|      |    |      |SFT_OS|SYMROS|
 *                  `------+------|NAV_BK|    |NUMSPC|------+------'
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_QWERTY] = LAYOUT( \
  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, \
  KC_A,    CTRL_S,  ALT_D,   GUI_F,   KC_G,         KC_H,    GUI_J,   ALT_K,   CTRL_L,  KC_QUOT,    \
  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SCLN, \
                    SYML_OS, SFT_OS,  NAV_BK,       NUM_SPC, SFT_OS,  SYMR_OS                    \
),

/* Media + layer lock keys
 *
 * ,----------------------------------.           ,----------------------------------.
 * |      |      | VOLUP| VOLDN|      |           |      | MRWD | MFFD |      |      |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  DEL | CTRL |  ALT |  GUI |NAV_LK|           | POWER|VOL_DN|VOL_UP| MUTE | MPLY |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |      |      |      |      |      |           |      |NUM_LK|      |      |      |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  |      |      |      |    |      |      |      |
 *                  `-------------|      |    |      |------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_MEDIA] = LAYOUT( \
  _______, _______, KC__VOLUP, KC__VOLDOWN, _______,_______, KC_MRWD, KC_MFFD, _______, _______, \
  KC_DEL,  KC_LCTL, KC_LALT, KC_LGUI, NAV_LK,       KC_POWER,VOL_DN,  VOL_UP,  KC__MUTE,KC_MPLY, \
  _______, _______, _______, _______, _______,      _______, NUM_LK,  _______, _______, _______, \
                    _______, _______, _______,      _______, _______, _______,                   \
),

/* Navigation + mouse keys
 *
 * ,----------------------------------.           ,----------------------------------.
 * | PSCR |      | WH_U | WH_D | BSPC |           | DEL  | PGDN | PGUP | HOME |  END |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | SHIFT| CTRL |  ALT |  GUI |NAV_LK|           | CAPS | LEFT | DOWN |  UP  | RIGHT|
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |      | ACL0 | ACL1 | ACL2 | BTN2 |           | BTN1 | MS_L | MS_D | MS_U | MS_R |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,--------------------.
 *                  | ESC  |      |      |    |      |      |      |
 *                  `------+------|      |    | ENTER|------+------'
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_NAV] = LAYOUT( \
  KC_PSCR, _______, KC_WH_U, KC_WH_D, KC_BSPC,      KC_DEL,  KC_PGDN, KC_PGUP, KC_HOME, KC_END,  \
  KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, NAV_LK,       KC_CAPS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, \
  _______, KC_ACL0, KC_ACL1, KC_ACL2, KC_BTN2,      KC_BTN1, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, \
                    KC_ESC,  _______, _______,      KC_ENT,  _______, _______,                   \
),

/* Number + function keys
 *
 * ,----------------------------------.           ,----------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |           |  F6  |  F7  |  F8  |  F9  |  F10 |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   7  | CTL/5| ALT/3| GUI/1|   9  |           |   8  | GUI/0| ALT/2| CTL/4|   6  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |      |      |  F11 |  F12 |      |           |      |NUM_LK|      |      |      |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,--------------------.
 *                  |  ESC |      |      |    |      |      |      |
 *                  `------+------|  TAB |    |      |------+------'
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_NUM] = LAYOUT( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   \
  KC_7,    CTRL_5,  ALT_3,   GUI_1,   KC_9,         KC_8,    GUI_0,   ALT_2,   CTRL_4,  KC_6,     \
  _______, _______, KC_F11,  KC_F12,  _______,      _______, NUM_LK,  _______, _______, _______,  \
                    KC_ESC,  _______, KC_TAB,       _______, _______, _______,                    \
),

/* Vanilla numbers + function keys (uncomment if you prefer standard number order)
 *
 * ,----------------------------------.           ,----------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |           |  F6  |  F7  |  F8  |  F9  |  F10 |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   1  | CTL/2| ALT/3| GUI/4|   5  |           |   6  | GUI/7| ALT/8| CTL/9|   0  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |      |      |  F11 |  F12 |      |           |      |NUM_LK|      |      |      |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,--------------------.
 *                  |  ESC |      |      |    |      |      |      |
 *                  `------+------|  TAB |    |      |------+------'
 *                                |      |    |      |
 *                                `------'    `------'
 */
// [_NUM] = LAYOUT( \
//   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   \
//   KC_1,    CTRL_2,  ALT_3,   GUI_4,   KC_5,         KC_6,    GUI_7,   ALT_8,   CTRL_9,  KC_0,     \
//   _______, _______, KC_F11,  KC_F12,  _______,      _______, NUM_LK,  _______, _______, _______,  \
//                     KC_ESC,  _______, KC_TAB,       _______, _______, _______,                    \
// ),

/* Symbols
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   !  |   @  |   #  |   $  |   %  |           |   ^  |   &  |   *  |   ?  |   '  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   +  | CTL/=| ALT/(| GUI/)|   "  |           |   :  | GUI/]| ALT/[| CTL/}|   {  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   <  |   |  |   -  |   >  |   \  |           |   `  |   _  |   /  |   ~  |   ;  |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,--------------------.
 *                  |      |      |      |    |      |      |      |
 *                  `------+------|MAC_EN|    |MAC_EM|------+------'
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_SYM_L] = SYMBOL_LAYER,
[_SYM_R] = SYMBOL_LAYER,

/* System
 *
 * ,----------------------------------.           ,----------------------------------.
 * |      |      |      |      |      |           |      |      |      |      |      |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | RESET| DEBUG|AU_OFF| AU_ON|      |           |      |COLEMK|QWERTY|      |      |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |      |      |      |      |      |           |      |      |      |      |      |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,--------------------.
 *                  |      |      |      |    |      |      |      |
 *                  `------+------|      |    |      |------+------'
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_SYS] = LAYOUT( \
  _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, \
  RESET,   DEBUG,   AU_OFF,  AU_ON,   _______,      _______, CMK_DHM, QWERTY, _______, _______, \
  _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, \
                    _______, _______, _______,      _______, _______, _______,                   \
),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CMK_DHM:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_CMK_DHM);
      }
      return false;
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
    case NAV:
      if (record->event.pressed) {
        layer_on(_NAV);
        update_tri_layer(_NAV, _NUM, _MEDIA);
      } else {
        layer_off(_NAV);
        update_tri_layer(_NAV, _NUM, _MEDIA);
      }
      return false;
    case NUM:
      if (record->event.pressed) {
        layer_on(_NUM);
        update_tri_layer(_NAV, _NUM, _MEDIA);
      } else {
        layer_off(_NUM);
        update_tri_layer(_NAV, _NUM, _MEDIA);
      }
      return false;
    case SYM_L:
      if (record->event.pressed) {
        layer_on(_SYM_L);
        update_tri_layer(_SYM_L, _SYM_R, _SYS);
      } else {
        layer_off(_SYM_L);
        update_tri_layer(_SYM_L, _SYM_R, _SYS);
      }
      return false;
    case SYM_R:
      if (record->event.pressed) {
        layer_on(_SYM_R);
        update_tri_layer(_SYM_L, _SYM_R, _SYS);
      } else {
        layer_off(_SYM_R);
        update_tri_layer(_SYM_L, _SYM_R, _SYS);
      }
      return false;
    case ALT_OP:
      if (record->event.pressed) {
        key_timer = timer_read();
        register_mods(MOD_BIT(KC_LALT));
      }
      else {
        unregister_mods(MOD_BIT(KC_LALT));
        if (timer_elapsed(key_timer) < TAPPING_TERM) {
          register_mods(MOD_BIT(KC_LSFT));
          tap_code(KC_9);
          unregister_mods(MOD_BIT(KC_LSFT));
        }
      }
      return false;
    case CTL_CCB:
      if (record->event.pressed) {
        key_timer = timer_read();
        register_mods(MOD_BIT(KC_LCTL));
      }
      else {
        unregister_mods(MOD_BIT(KC_LCTL));
        if (timer_elapsed(key_timer) < TAPPING_TERM) {
          register_mods(MOD_BIT(KC_LSFT));
          tap_code(KC_RBRC);
          unregister_mods(MOD_BIT(KC_LSFT));
        }
      }
      return false;
    case GUI_CP:
      if (record->event.pressed) {
        key_timer = timer_read();
        register_mods(MOD_BIT(KC_LGUI));
      }
      else {
        unregister_mods(MOD_BIT(KC_LGUI));
        if (timer_elapsed(key_timer) < TAPPING_TERM) {
          register_mods(MOD_BIT(KC_LSFT));
          tap_code(KC_0);
          unregister_mods(MOD_BIT(KC_LSFT));
        }
      }
      return false;
    default:
      return true;
  }
};
