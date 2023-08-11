// Minidox keymap by dustypomerleau
// Thanks for checking out my keymap. The rationale behind the layout is described in the README.

#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

enum my_layers {
  _CMK_DHM,
  _QWERTY,
  _SYS,
  _NAV,
  _NUM_E,
  _NUM_N,
  _SYM
};

enum my_keycodes {
  CMK_DHM = SAFE_RANGE,
  QWERTY,
  SYS,
  NAV,
  NUM_E,
  NUM_N,
  SYM
};

enum td_keycodes {
  ALT_LP,
  CTL_RCB,
  GUI_RP,
  SFT_LCB,
  SFT_PLS
};

typedef enum {
  SINGLE_TAP,
  SINGLE_HOLD,
  DOUBLE_SINGLE_TAP
} td_state_t;

static td_state_t td_state;
int cur_dance (tap_dance_state_t *state);
void altlp_finished (tap_dance_state_t *state, void *user_data);
void altlp_reset (tap_dance_state_t *state, void *user_data);
void ctlrcb_finished (tap_dance_state_t *state, void *user_data);
void ctlrcb_reset (tap_dance_state_t *state, void *user_data);
void guirp_finished (tap_dance_state_t *state, void *user_data);
void guirp_reset (tap_dance_state_t *state, void *user_data);
void sftlcb_finished (tap_dance_state_t *state, void *user_data);
void sftlcb_reset (tap_dance_state_t *state, void *user_data);
void sftpls_finished (tap_dance_state_t *state, void *user_data);
void sftpls_reset (tap_dance_state_t *state, void *user_data);

#define ALT_2 LALT_T(KC_2)
#define ALT_3 LALT_T(KC_3)
#define ALT_8 LALT_T(KC_8)
#define ALT_D LALT_T(KC_D)
#define ALT_E LALT_T(KC_E)
#define ALT_K LALT_T(KC_K)
#define ALT_LB LALT_T(KC_LBRC)
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
#define GUI_RB LGUI_T(KC_RBRC)
#define GUI_F LGUI_T(KC_F)
#define GUI_J LGUI_T(KC_J)
#define GUI_N LGUI_T(KC_N)
#define GUI_TEA LGUI_T(KC_T)
#define MAC_EM S(LALT(KC_MINS))
#define MAC_EN LALT(KC_MINS)
#define NAV_BK LT(_NAV, KC_BSPC)
#define NAV_LK TG(_NAV)
#define NUME_SPC LT(_NUM_E, KC_SPC)
#define NUMLK_E TG(_NUM_E)
#define NUMLK_N TG(_NUM_N)
#define NUMN_SPC LT(_NUM_N, KC_SPC)
#define SFT_0 LSFT_T(KC_0)
#define SFT_1 LSFT_T(KC_1)
#define SFT_6 LSFT_T(KC_6)
#define SFT_7 LSFT_T(KC_7)
#define SFT_A LSFT_T(KC_A)
#define SFT_O LSFT_T(KC_O)
#define SFT_OS OSM(MOD_LSFT)
#define SFT_QOT LSFT_T(KC_QUOT)
#define SYM_OS OSL(_SYM)
#define SYS_Z LT(_SYS, KC_Z)
#define VOL_DN S(LALT(KC_VOLD))
#define VOL_UP S(LALT(KC_VOLU))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Colemak DHm
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   Q  |   W  |   F  |   P  |   B  |           |   J  |   L  |   U  |   Y  |   '  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | SFT/A| CTL/R| ALT/S| GUI/T|   G  |           |   M  | GUI/N| ALT/E| CTL/I| SFT/O|
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | SYS/Z|   X  |   C  |   D  |   V  |           |   K  |   H  |   ,  |   .  |   ;  |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,--------------------.
 *                  |SFT/OS|NAV/BK|      |    |      |NUM/SP|SFT/OS|
 *                  `------+------|SYM/OS|    |SYM/OS|------+------'
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_CMK_DHM] = LAYOUT(
  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,         KC_J,    KC_L,     KC_U,    KC_Y,    KC_QUOT,
  SFT_A,   CTRL_R,  ALT_S,   GUI_TEA, KC_G,         KC_M,    GUI_N,    ALT_E,   CTRL_I,  SFT_O,
  SYS_Z,   KC_X,    KC_C,    KC_D,    KC_V,         KC_K,    KC_H,     KC_COMM, KC_DOT,  KC_SCLN,
                    SFT_OS,  NAV_BK,  SYM_OS,       SYM_OS,  NUME_SPC, SFT_OS
),

/* QWERTY
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   Q  |   W  |   E  |   R  |   T  |           |   Y  |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | SFT/A| CTL/S| ALT/D| GUI/F|   G  |           |   H  | GUI/J| ALT/K| CTL/L| SFT/'|
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | SYS/Z|   X  |   C  |   V  |   B  |           |   N  |   M  |   ,  |   .  |   ;  |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,--------------------.
 *                  |SFT/OS|NAV/BK|      |    |      |NUM/SP|SFT/OS|
 *                  `------+------|SYM/OS|    |SYM/OS|------+------'
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_QWERTY] = LAYOUT(
  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,         KC_Y,    KC_U,     KC_I,    KC_O,    KC_P,
  SFT_A,   CTRL_S,  ALT_D,   GUI_F,   KC_G,         KC_H,    GUI_J,    ALT_K,   CTRL_L,  SFT_QOT,
  SYS_Z,   KC_X,    KC_C,    KC_V,    KC_B,         KC_N,    KC_M,     KC_COMM, KC_DOT,  KC_SCLN,
                    SFT_OS,  NAV_BK,  SYM_OS,       SYM_OS,  NUMN_SPC, SFT_OS
),

/* System, media, and layer lock keys
 * If you use QWERTY + the Vanilla numbers primarily, change NUMLK_E to NUMLK_N here.
 *
 * ,----------------------------------.           ,----------------------------------.
 * | Boot |Debug |QWERTY|CMKDHM|      |           |      | VOL--| VOL++|BRITE-|BRITE+|
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | SHIFT| CTRL |  ALT |  GUI |NAV LK|           | POWER| VOL- | VOL+ | MUTE | MPLY |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |      |      |AU OFF| AU ON|      |           |      |NUM LK| MRWD | MFFD |      |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  |      |      |      |    |      |      |      |
 *                  `-------------|      |    |      |------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_SYS] = LAYOUT(
  QK_BOOT, DB_TOGG, QWERTY,  CMK_DHM, _______,       _______,  KC_VOLD, KC_VOLU, KC_BRID, KC_BRIU,
  KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, NAV_LK,        KC_PWR,   VOL_DN,  VOL_UP,  KC_MUTE, KC_MPLY,
  _______, _______, AU_OFF,  AU_ON,   _______,       _______,  NUMLK_E, KC_MRWD, KC_MFFD, _______,
                    _______, _______, _______,       _______,  _______, _______
),

/* Navigation + mouse keys
 *
 * ,----------------------------------.           ,----------------------------------.
 * | PSCR |      | WH U | WH D |      |           | BSPC | PGDN | PGUP | HOME |  END |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | SHIFT| CTRL |  ALT |  GUI |NAV LK|           | CAPS | LEFT | DOWN |  UP  | RIGHT|
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |      | ACL0 | ACL1 | ACL2 | BTN2 |           | BTN1 | MS L | MS D | MS U | MS R |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,--------------------.
 *                  |      |      |      |    |      | ENTER|      |
 *                  `------+------|  ESC |    | DEL  |------+------'
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_NAV] = LAYOUT(
  KC_PSCR, _______, KC_WH_U, KC_WH_D, _______,       KC_BSPC, KC_PGDN, KC_PGUP, KC_HOME, KC_END,
  KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, NAV_LK,        KC_CAPS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
  _______, KC_ACL0, KC_ACL1, KC_ACL2, KC_BTN2,       KC_BTN1, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,
                    _______, _______, KC_ESC,        KC_DEL,  KC_ENT,  _______
),

/* Number + function keys (ergonomic number order - default pairing with Colemak)
 *
 * ,----------------------------------.           ,----------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |           |  F6  |  F7  |  F8  |  F9  |  F10 |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | SFT/7| CTL/5| ALT/3| GUI/1|   9  |           |   8  | GUI/0| ALT/2| CTL/4| SFT/6|
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  F11 |  F12 |   -  | SPACE| BSPC |           |  DEL |NUM LK|      |      |   /  |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,--------------------.
 *                  |      | TAB  |      |    |      |      |      |
 *                  `------+------|  ESC |    |      |------+------'
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_NUM_E] = LAYOUT(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,         KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
  SFT_7,   CTRL_5,  ALT_3,   GUI_1,   KC_9,          KC_8,    GUI_0,   ALT_2,   CTRL_4,  SFT_6,
  KC_F11,  KC_F12,  KC_MINS, KC_SPC,  KC_BSPC,       KC_DEL,  NUMLK_E, _______, _______, KC_SLSH,
                    _______, KC_TAB,  KC_ESC,        _______, _______, _______
),

/* Number + function keys (numeric number order - default pairing with QWERTY)
 *
 * ,----------------------------------.           ,----------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |           |  F6  |  F7  |  F8  |  F9  |  F10 |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | SFT/1| CTL/2| ALT/3| GUI/4|   5  |           |   6  | GUI/7| ALT/8| CTL/9| SFT/0|
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  F11 |  F12 |   -  | SPACE| BSPC |           |  DEL |NUM LK|      |      |   /  |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,--------------------.
 *                  |      | TAB  |      |    |      |      |      |
 *                  `------+------|  ESC |    |      |------+------'
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_NUM_N] = LAYOUT(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,         KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
  SFT_1,   CTRL_2,  ALT_3,   GUI_4,   KC_5,          KC_6,    GUI_7,   ALT_8,   CTRL_9,  SFT_0,
  KC_F11,  KC_F12,  KC_MINS, KC_SPC,  KC_BSPC,       KC_DEL,  NUMLK_N, _______, _______, KC_SLSH,
                    _______, KC_TAB,  KC_ESC,        _______, _______, _______
),


/* Symbols
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   !  |   @  |   #  |   $  |   %  |           |   ^  |   &  |   *  |   ?  |   '  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | SFT/+| CTL/=| ALT/(| GUI/)|   "  |           |   :  | GUI/]| ALT/[| CTL/}| SFT/{|
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   <  |   |  |   -  |   >  |   \  |           |   `  |   _  |   /  |   ~  |   ;  |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,--------------------.
 *                  |      |ENDASH|      |    |      |EMDASH|      |
 *                  `------+------|      |    |      |------+------'
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_SYM] = LAYOUT(
  KC_EXLM,     KC_AT,   KC_HASH,    KC_DLR,     KC_PERC,       KC_CIRC, KC_AMPR, KC_ASTR, KC_QUES,     KC_QUOT,
  TD(SFT_PLS), CTRL_EQ, TD(ALT_LP), TD(GUI_RP), KC_DQT,        KC_COLN, GUI_RB,  ALT_LB,  TD(CTL_RCB), TD(SFT_LCB),
  KC_LT,       KC_PIPE, KC_MINS,    KC_GT,      KC_BSLS,       KC_GRV,  KC_UNDS, KC_SLSH, KC_TILD,     KC_SCLN,
                        _______,    MAC_EN,     _______,       _______, MAC_EM,  _______
)

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
    default:
      return true;
  }
};

int cur_dance (tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) return SINGLE_TAP;
    else return SINGLE_HOLD;
  }
  if (state->count == 2) return DOUBLE_SINGLE_TAP;
  else return 3;
}

void altlp_finished (tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:
      register_code16(KC_LPRN);
      break;
    case SINGLE_HOLD:
      register_mods(MOD_BIT(KC_LALT));
      break;
    case DOUBLE_SINGLE_TAP:
      tap_code16(KC_LPRN);
      register_code16(KC_LPRN);
  }
}

void altlp_reset (tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case SINGLE_TAP:
      unregister_code16(KC_LPRN);
      break;
    case SINGLE_HOLD:
      unregister_mods(MOD_BIT(KC_LALT));
      break;
    case DOUBLE_SINGLE_TAP:
      unregister_code16(KC_LPRN);
  }
}

void ctlrcb_finished (tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:
      register_code16(KC_RCBR);
      break;
    case SINGLE_HOLD:
      register_mods(MOD_BIT(KC_LCTL));
      break;
    case DOUBLE_SINGLE_TAP:
      tap_code16(KC_RCBR);
      register_code16(KC_RCBR);
  }
}

void ctlrcb_reset (tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case SINGLE_TAP:
      unregister_code16(KC_RCBR);
      break;
    case SINGLE_HOLD:
      unregister_mods(MOD_BIT(KC_LCTL));
      break;
    case DOUBLE_SINGLE_TAP:
      unregister_code16(KC_RCBR);
  }
}

void guirp_finished (tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:
      register_code16(KC_RPRN);
      break;
    case SINGLE_HOLD:
      register_mods(MOD_BIT(KC_LGUI));
      break;
    case DOUBLE_SINGLE_TAP:
      tap_code16(KC_RPRN);
      register_code16(KC_RPRN);
  }
}

void guirp_reset (tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case SINGLE_TAP:
      unregister_code16(KC_RPRN);
      break;
    case SINGLE_HOLD:
      unregister_mods(MOD_BIT(KC_LGUI));
      break;
    case DOUBLE_SINGLE_TAP:
      unregister_code16(KC_RPRN);
  }
}

void sftlcb_finished (tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:
      register_code16(KC_LCBR);
      break;
    case SINGLE_HOLD:
      register_mods(MOD_BIT(KC_LSFT));
      break;
    case DOUBLE_SINGLE_TAP:
      tap_code16(KC_LCBR);
      register_code16(KC_LCBR);
  }
}

void sftlcb_reset (tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case SINGLE_TAP:
      unregister_code16(KC_LCBR);
      break;
    case SINGLE_HOLD:
      unregister_mods(MOD_BIT(KC_LSFT));
      break;
    case DOUBLE_SINGLE_TAP:
      unregister_code16(KC_LCBR);
  }
}

void sftpls_finished (tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:
      register_code16(KC_PLUS);
      break;
    case SINGLE_HOLD:
      register_mods(MOD_BIT(KC_LSFT));
      break;
    case DOUBLE_SINGLE_TAP:
      tap_code16(KC_PLUS);
      register_code16(KC_PLUS);
  }
}

void sftpls_reset (tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case SINGLE_TAP:
      unregister_code16(KC_PLUS);
      break;
    case SINGLE_HOLD:
      unregister_mods(MOD_BIT(KC_LSFT));
      break;
    case DOUBLE_SINGLE_TAP:
      unregister_code16(KC_PLUS);
  }
}

tap_dance_action_t tap_dance_actions[] = {
  [ALT_LP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, altlp_finished, altlp_reset),
  [CTL_RCB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctlrcb_finished, ctlrcb_reset),
  [GUI_RP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, guirp_finished, guirp_reset),
  [SFT_LCB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sftlcb_finished, sftlcb_reset),
  [SFT_PLS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sftpls_finished, sftpls_reset)
};
