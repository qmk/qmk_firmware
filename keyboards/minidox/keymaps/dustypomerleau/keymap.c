// Minidox keymap by dustypomerleau
// Thanks for checking out my keymap. The rationale behind the layout is described in the README.

#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

enum custom_layers {
  _CMK_DHM,
  _QWERTY,
  _SYS,
  _NAV,
  _NUM,
  _SYM,
};

enum custom_keycodes {
  CMK_DHM = SAFE_RANGE,
  QWERTY,
  SYS,
  NAV,
  NUM,
  SYM,
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
#define GUI_TEA LGUI_T(KC_T)
#define MAC_EM S(LALT(KC_MINS))
#define MAC_EN LALT(KC_MINS)
#define NAV_BK LT(_NAV, KC_BSPC)
#define NAV_LK TG(_NAV)
#define NUM_LK TG(_NUM)
#define NUM_SPC LT(_NUM, KC_SPC)
#define SFT_OS OSM(MOD_LSFT)
#define SYM_OS OSL(_SYM)
#define VOL_DN S(LALT(KC__VOLDOWN))
#define VOL_UP S(LALT(KC__VOLUP))
#define XXXXXXX KC_NO
#define Z_SYS LT(_SYS, KC_Z)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Colemak DHm
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   Q  |   W  |   F  |   P  |   B  |           |   J  |   L  |   U  |   Y  |   '  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   A  | CTL/R| ALT/S| GUI/T|   G  |           |   M  | GUI/N| ALT/E| CTL/I|   O  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | Z_SYS|   X  |   C  |   D  |   V  |           |   K  |   H  |   ,  |   .  |   ;  |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,--------------------.
 *                  |SFT_OS|NAV_BK|      |    |      |NUMSPC|SFT_OS|
 *                  `------+------|SYM_OS|    |SYM_OS|------+------'
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_CMK_DHM] = LAYOUT( \
  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,         KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT, \
  KC_A,    CTRL_R,  ALT_S,   GUI_TEA, KC_G,         KC_M,    GUI_N,   ALT_E,   CTRL_I,  KC_O,    \
  Z_SYS,   KC_X,    KC_C,    KC_D,    KC_V,         KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SCLN, \
                    SFT_OS,  NAV_BK,  SYM_OS,       SYM_OS, NUM_SPC, SFT_OS                      \
),

/* QWERTY
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   Q  |   W  |   E  |   R  |   T  |           |   Y  |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   A  | CTL/S| ALT/D| GUI/F|   G  |           |   H  | GUI/J| ALT/K| CTL/L|   '  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | Z_SYS|   X  |   C  |   V  |   B  |           |   N  |   M  |   ,  |   .  |   ;  |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,--------------------.
 *                  |SFT_OS|NAV_BK|      |    |      |NUMSPC|SFT_OS|
 *                  `------+------|SYM_OS|    |SYM_OS|------+------'
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_QWERTY] = LAYOUT( \
  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    \
  KC_A,    CTRL_S,  ALT_D,   GUI_F,   KC_G,         KC_H,    GUI_J,   ALT_K,   CTRL_L,  KC_QUOT, \
  Z_SYS,   KC_X,    KC_C,    KC_V,    KC_B,         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SCLN, \
                    SFT_OS,  NAV_BK,  SYM_OS,       SYM_OS, NUM_SPC, SFT_OS                      \
),

/* System, media, and layer lock keys
 *
 * ,----------------------------------.           ,----------------------------------.
 * | RESET|DEBUG |QWERTY|CMKDHM|      |           |      | MRWD | MFFD | VOLUP| VOLDN|
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  DEL | CTRL |  ALT |  GUI |NAV_LK|           | POWER|VOL_DN|VOL_UP| MUTE | MPLY |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |      |      |      |AU_OFF|AU_ON |           |      |NUM_LK|      |      |      |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  |      |      |      |    |      |      |      |
 *                  `-------------|      |    |      |------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_SYS] = LAYOUT( \
  RESET,   DEBUG,   QWERTY,  CMK_DHM, _______,      _______, KC_MRWD, KC_MFFD, KC__VOLUP, KC__VOLDOWN, \
  KC_DEL,  KC_LCTL, KC_LALT, KC_LGUI, NAV_LK,       KC_POWER,VOL_DN,  VOL_UP,  KC__MUTE,  KC_MPLY,     \
  _______, _______, _______, AU_OFF,  AU_ON,        _______, NUM_LK,  _______, _______,   _______,     \
                    _______, _______, _______,      _______, _______, _______                          \
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
 *                  |      |      |      |    |      | ENTER|      |
 *                  `------+------|  ESC |    | DEL  |------+------'
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_NAV] = LAYOUT( \
  KC_PSCR, _______, KC_WH_U, KC_WH_D, KC_BSPC,      KC_DEL,  KC_PGDN, KC_PGUP, KC_HOME, KC_END,  \
  KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, NAV_LK,       KC_CAPS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, \
  _______, KC_ACL0, KC_ACL1, KC_ACL2, KC_BTN2,      KC_BTN1, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, \
                    _______, _______, KC_ESC,       KC_DEL,  KC_ENT,  _______                    \
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
 *                  |      | TAB  |      |    |      |      |      |
 *                  `------+------|  ESC |    |      |------+------'
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_NUM] = LAYOUT( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   \
  KC_7,    CTRL_5,  ALT_3,   GUI_1,   KC_9,         KC_8,    GUI_0,   ALT_2,   CTRL_4,  KC_6,     \
  _______, _______, KC_F11,  KC_F12,  _______,      _______, NUM_LK,  _______, _______, _______,  \
                    _______, KC_TAB,  KC_ESC,       _______, _______, _______                     \
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
 *                  |      | TAB  |      |    |      |      |      |
 *                  `------+------|  ESC |    |      |------+------'
 *                                |      |    |      |
 *                                `------'    `------'
 */
/*
* [_NUM] = LAYOUT( \
*   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   \
*   KC_1,    CTRL_2,  ALT_3,   GUI_4,   KC_5,         KC_6,    GUI_7,   ALT_8,   CTRL_9,  KC_0,     \
*   _______, _______, KC_F11,  KC_F12,  _______,      _______, NUM_LK,  _______, _______, _______,  \
*                     _______, KC_TAB,  KC_ESC,       _______, _______, _______                     \
* ),
*/

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
 *                  |      |MAC_EN|      |    |      |MAC_EM|      |
 *                  `------+------|      |    |      |------+------'
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_SYM] = LAYOUT( \
  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,      KC_CIRC, KC_AMPR, KC_ASTR, KC_QUES, KC_QUOT, \
  KC_PLUS, CTRL_EQ, ALT_OP,  GUI_CP,  KC_DQT,       KC_COLN, GUI_CB,  ALT_OB,  CTL_CCB, KC_LCBR, \
  KC_LT,   KC_PIPE, KC_MINS, KC_GT,   KC_BSLS,      KC_GRV,  KC_UNDS, KC_SLSH, KC_TILD, KC_SCLN, \
                    _______, MAC_EN,  _______,      _______, MAC_EM,  _______                    \
)

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  static uint16_t key_timer;
  bool tap_not_interrupted = record->tap.count > 0 && !record->tap.interrupted;

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

    case ALT_OP:
      if (record->event.pressed) {
        key_timer = timer_read();
        if (!tap_not_interrupted) {
          register_mods(MOD_BIT(KC_LALT));
        }
        reset_oneshot_layer();
      }
      else if (tap_not_interrupted && timer_elapsed(key_timer) < TAPPING_TERM) {
        add_weak_mods(MOD_BIT(KC_LSFT));
        tap_code(KC_9);
        del_weak_mods(MOD_BIT(KC_LSFT));
      }
      else {
        unregister_mods(MOD_BIT(KC_LALT));
      }
      return false;

    case CTL_CCB:
      if (record->event.pressed) {
        key_timer = timer_read();
        if (!tap_not_interrupted) {
          register_mods(MOD_BIT(KC_LCTL));
        }
        reset_oneshot_layer();
      }
      else if (tap_not_interrupted && timer_elapsed(key_timer) < TAPPING_TERM) {
        add_weak_mods(MOD_BIT(KC_LSFT));
        tap_code(KC_RBRC);
        del_weak_mods(MOD_BIT(KC_LSFT));
      }
      else {
        unregister_mods(MOD_BIT(KC_LCTL));
      }
      return false;

    case GUI_CP:
      if (record->event.pressed) {
        key_timer = timer_read();
        if (!tap_not_interrupted) {
          register_mods(MOD_BIT(KC_LGUI));
        }
        reset_oneshot_layer();
      }
      else if (tap_not_interrupted && timer_elapsed(key_timer) < TAPPING_TERM) {
        add_weak_mods(MOD_BIT(KC_LSFT));
        tap_code(KC_0);
        del_weak_mods(MOD_BIT(KC_LSFT));
      }
      else {
        unregister_mods(MOD_BIT(KC_LGUI));
      }
      return false;

    default:
      return true;

  }

};
