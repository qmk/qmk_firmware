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
  COLEMAK_DHM = SAFE_RANGE, // techically you could remove this I think, since you don't actually use a keycode to set your default layer.
  NAV,
  NUM,
  SYM_L,
  SYM_R,
  ALT_OP, // define in process_record_user
  CTL_CCB, // define in process_record_user
  GUI_CP, // define in process_record_user
  MAC_EM, // define in process_record_user
  MAC_EN, // define in process_record_user
  VOL_DN, // define in process_record_user
  VOL_UP // define in process_record_user
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
#define NAV_BK LT(_NAV, KC_BSPC)
#define NAV_LK TG(_NAV)
#define NUM_LK TG(_NUM)
#define NUM_SPC LT(_NUM, KC_SPC)
#define SFT_OS OSM(MOD_LSFT)
#define SYML_OS OSL(_SYM_L)
#define SYMR_OS OSL(_SYM_R)
#define XXXXXXX KC_NO

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

/* Media + lock keys
 *
 * ,----------------------------------.           ,----------------------------------.
 * |      |      | VOLU | VOLD |      |           |      | MRWD | MFFD |      |      |
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
  _______, _______, KC_VOLU, KC_VOLD, _______,      _______, _______, _______, _______, _______, \
  KC_DEL,  KC_LCTL, KC_LALT, KC_LGUI, NAV_LK,       KC_POWER,VOL_DN,  VOL_UP,  KC_MUTE, KC_MPLY, \
  _______, _______, _______, _______, _______,      _______, NUM_LK,  _______, _______, _______, \
                    _______, _______, _______,      _______, _______, _______,                   \
),

/* Navigation
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

/* Number
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

/* Symbol (left hand)
 *
 * ,----------------------------------.           ,----------------------------------.
 * |      |      | WH_U | WH_D |      |           |      | PGDN | PGUP | HOME |  END |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | SHIFT| CTRL |  ALT |  GUI |NAV_LK|           | CAPS | LEFT | DOWN |  UP  | RIGHT|
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |      | ACL0 | ACL1 | ACL2 | BTN2 |           | BTN1 | MS_L | MS_D | MS_U | MS_R |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,--------------------.
 *                  |      |      |      |    |      |      |      |
 *                  `------+------|      |    |      |------+------'
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_SYM_L] = LAYOUT( \
  _______, _______, KC_WH_U, KC_WH_D, _______,      _______, KC_PGDN, KC_PGUP, KC_HOME, KC_END, \
  KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, NAV_LK,       KC_CAPS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, \
  _______, KC_ACL0, KC_ACL1, KC_ACL2, KC_BTN2,      KC_BTN1, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, \
                    _______, _______, _______,      _______, _______, _______, \
),

/* Symbol (right hand)
 *
 * ,----------------------------------.           ,----------------------------------.
 * |      |      | WH_U | WH_D |      |           |      | PGDN | PGUP | HOME |  END |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | SHIFT| CTRL |  ALT |  GUI |NAV_LK|           | CAPS | LEFT | DOWN |  UP  | RIGHT|
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |      | ACL0 | ACL1 | ACL2 | BTN2 |           | BTN1 | MS_L | MS_D | MS_U | MS_R |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,--------------------.
 *                  |      |      |      |    |      |      |      |
 *                  `------+------|      |    |      |------+------'
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_SYM_R] = LAYOUT( \
  _______, _______, KC_WH_U, KC_WH_D, _______,      _______, KC_PGDN, KC_PGUP, KC_HOME, KC_END, \
  KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, NAV_LK,       KC_CAPS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, \
  _______, KC_ACL0, KC_ACL1, KC_ACL2, KC_BTN2,      KC_BTN1, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, \
                    _______, _______, _______,      _______, _______, _______, \
),

/* System
 *
 * ,----------------------------------.           ,----------------------------------.
 * |      |      | WH_U | WH_D |      |           |      | PGDN | PGUP | HOME |  END |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | SHIFT| CTRL |  ALT |  GUI |NAV_LK|           | CAPS | LEFT | DOWN |  UP  | RIGHT|
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |      | ACL0 | ACL1 | ACL2 | BTN2 |           | BTN1 | MS_L | MS_D | MS_U | MS_R |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,--------------------.
 *                  |      |      |      |    |      |      |      |
 *                  `------+------|      |    |      |------+------'
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_SYS] = LAYOUT( \
  _______, _______, KC_WH_U, KC_WH_D, _______,      _______, KC_PGDN, KC_PGUP, KC_HOME, KC_END, \
  KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, NAV_LK,       KC_CAPS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, \
  _______, KC_ACL0, KC_ACL1, KC_ACL2, KC_BTN2,      KC_BTN1, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, \
                    _______, _______, _______,      _______, _______, _______, \
),

};

// copy preonic to below and use as template:
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistant_default_layer_set(1UL<<_QWERTY);
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
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
