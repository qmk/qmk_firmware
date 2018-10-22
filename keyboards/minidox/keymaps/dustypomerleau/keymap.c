// dp minidox keymap

#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

enum custom_layers {
  _COLEMAK_DHM,
  _MEDIA,
  _NAV,
  _NUM,
  _SYM_L,
  _SYM_R,
  _SYS
};

enum custom_keycodes {
  COLEMAK_DHM = SAFE_RANGE, // Not currently in use, given only 1 default layer
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
#define ALT_E LALT_T(KC_E)
#define ALT_OB LALT_T(KC_LBRC)
#define ALT_S LALT_T(KC_S)
#define CTRL_4 LCTL_T(KC_4)
#define CTRL_5 LCTL_T(KC_5)
#define CTRL_EQ LCTL_T(KC_EQL)
#define CTRL_I LCTL_T(KC_I)
#define CTRL_R LCTL_T(KC_R)
#define GUI_0 LGUI_T(KC_0)
#define GUI_1 LGUI_T(KC_1)
#define GUI_CB LGUI_T(KC_RBRC)
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

/* Colemak DH(M)
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   Q  |   W  |   F  |   P  |   B  |           |   J  |   L  |   U  |   Y  |   '  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   A  |CTRL_R| ALT_S| GUI_T|   G  |           |   M  | GUI_N| ALT_E|CTRL_I|   O  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   Z  |   X  |   C  |   D  |   V  |           |   K  |   H  |   ,  |   .  |   ;  |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,--------------------.
 *                  |SYMLOS|SFT_OS|      |    |      |SFT_OS|SYMROS|
 *                  `------+------|NAV_BK|    |NUMSPC|------+------'
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_COLEMAK_DHM] = LAYOUT( \
  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,         KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT, \
  KC_A,    CTRL_R,  ALT_S,   GUI_T,   KC_G,         KC_M,    GUI_N,   ALT_E,   CTRL_I,  KC_O,    \
  KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,         KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SCLN, \
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
  _______, _______, KC__VOLUP, KC__VOLDOWN, _______,_______, _______, _______, _______, _______, \
  KC_DEL,  KC_LCTL, KC_LALT, KC_LGUI, NAV_LK,       KC_POWER,VOL_DN,  VOL_UP,  KC__MUTE,KC_MPLY, \
  _______, _______, _______, _______, _______,      _______, NUM_LK,  _______, _______, _______, \
                    _______, _______, _______,      _______, _______, _______,                   \
),

/* Navigation + mouse keys
 *
 * ,----------------------------------.           ,----------------------------------.
 * |      |      | WH_U | WH_D |      |           |      | PGDN | PGUP | HOME |  END |
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
  _______, _______, KC_WH_U, KC_WH_D, _______,      _______, KC_PGDN, KC_PGUP, KC_HOME, KC_END,  \
  KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, NAV_LK,       KC_CAPS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, \
  _______, KC_ACL0, KC_ACL1, KC_ACL2, KC_BTN2,      KC_BTN1, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, \
                    KC_ESC,  _______, _______,      KC_ENT,  _______, _______,                   \
),

/* Number + function keys
 *
 * ,----------------------------------.           ,----------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |           |  F6  |  F7  |  F8  |  F9  |  F10 |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   7  |CTRL_5| ALT_3| GUI_1|   9  |           |   8  | GUI_0| ALT_2|CTRL_4|   6  |
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

/* Symbols
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   !  |   @  |   #  |   $  |   %  |           |   ^  |   &  |   *  |   ?  |   '  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   +  |CTRLEQ|ALT_OP|GUI_CP|   "  |           |   :  |GUI_CB|ALT_OB|CTLCCB|   {  |
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
 * | RESET| DEBUG|AU_OFF| AU_ON|      |           |      |      |      |      |      |
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
  RESET,   DEBUG,   AU_OFF,  AU_ON,   _______,      _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, \
                    _______, _______, _______,      _______, _______, _______,                   \
),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case COLEMAK_DHM:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK_DHM);
      }
      return false;
      break;
    case NAV:
      if (record->event.pressed) {
        layer_on(_NAV);
        update_tri_layer(_NAV, _NUM, _MEDIA);
      } else {
        layer_off(_NAV);
        update_tri_layer(_NAV, _NUM, _MEDIA);
      }
      return false;
      break;
    case NUM:
      if (record->event.pressed) {
        layer_on(_NUM);
        update_tri_layer(_NAV, _NUM, _MEDIA);
      } else {
        layer_off(_NUM);
        update_tri_layer(_NAV, _NUM, _MEDIA);
      }
      return false;
      break;
    case SYM_L:
      if (record->event.pressed) {
        layer_on(_SYM_L);
        update_tri_layer(_SYM_L, _SYM_R, _SYS);
      } else {
        layer_off(_SYM_L);
        update_tri_layer(_SYM_L, _SYM_R, _SYS);
      }
      return false;
      break;
    case SYM_R:
      if (record->event.pressed) {
        layer_on(_SYM_R);
        update_tri_layer(_SYM_L, _SYM_R, _SYS);
      } else {
        layer_off(_SYM_R);
        update_tri_layer(_SYM_L, _SYM_R, _SYS);
      }
      return false;
      break;
    case ALT_OP: {
      if (record->event.pressed) {
        key_timer = timer_read();
        register_mods(MOD_BIT(KC_LALT));
      }
      else {
        unregister_mods(MOD_BIT(KC_LALT));
        if (timer_elapsed(key_timer) < TAPPING_TERM) {
          register_mods(MOD_BIT(KC_LSFT));
          register_code(KC_9);
          unregister_code(KC_9);
          unregister_mods(MOD_BIT(KC_LSFT));
        }
      }
      return false;
      break;
    case CTL_CCB: {
      if (record->event.pressed) {
        key_timer = timer_read();
        register_mods(MOD_BIT(KC_LCTL));
      }
      else {
        unregister_mods(MOD_BIT(KC_LCTL));
        if (timer_elapsed(key_timer) < TAPPING_TERM) {
          register_mods(MOD_BIT(KC_LSFT));
          register_code(KC_RBRC);
          unregister_code(KC_RBRC);
          unregister_mods(MOD_BIT(KC_LSFT));
        }
      }
      return false;
      break;
    case GUI_CP: {
      if (record->event.pressed) {
        key_timer = timer_read();
        register_mods(MOD_BIT(KC_LGUI));
      }
      else {
        unregister_mods(MOD_BIT(KC_LGUI));
        if (timer_elapsed(key_timer) < TAPPING_TERM) {
          register_mods(MOD_BIT(KC_LSFT));
          register_code(KC_0);
          unregister_code(KC_0);
          unregister_mods(MOD_BIT(KC_LSFT));
        }
      }
      return false;
      break;
  }
  return true;
};
