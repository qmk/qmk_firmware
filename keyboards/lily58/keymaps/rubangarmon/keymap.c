#include QMK_KEYBOARD_H

enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _NUMER,
  _FUNC,  
  _ADJUST
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ADJUS MO(_ADJUST)
// #define NUMERL MO(_NUMER)
#define LCTLESC LCTL_T(KC_ESC)
// #define NUM_A LT(_NUMER, KC_A)
#define FUCSCLN LT(_FUNC, KC_SCLN)
#define NUMQUOT LT(_NUMER, KC_QUOT)
#define NUMTAB LT(_NUMER, KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1! |   2@ |   3# |   4$ |   5% |                    |   6^ |   7& |   8* |   9( |   0) |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab* |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |BackSP|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL*|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |  ;*  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI | LAlt |LOWER | /Space  /       \Enter \  |RAISE | RAlt | LGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 * 
 * - Tap dance Ctrl/Esc
 * - Tap dance Function layer/semi-colon
 */

 [_QWERTY] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
  NUMTAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  LCTLESC,  KC_A,  KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    FUCSCLN, NUMQUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                        KC_LGUI, KC_LALT, LOWER,  KC_SPC,  KC_ENT,  RAISE,  KC_RALT, KC_LGUI
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1! |   2@ |   3# |   4$ |   5% |                    |   6^ |   7& |   8* |   9( |   0) |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      | Menu |      |      |                    |      |      |      |      | PScrn| Del  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      | LAlt |LCtrl |LShift|      |-------.    ,-------| Left | Down |  Up  |Right |      | Ins  |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |LShift|      |      |      |      |      |-------|    |-------| Home | PGDN | PGUP | End  |      |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | NUM  | LAlt |HOLD  | /Space  /       \Enter \  |RAISE | RAlt | LGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_LOWER] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______,_______, _______, _______,
  _______, _______, _______, KC_LGUI, _______, _______,                   _______, _______, _______,_______, KC_PSCR, KC_DEL ,
  _______, _______, KC_LALT, KC_LCTL, KC_LSFT, _______,                   KC_LEFT, KC_DOWN, KC_UP  ,KC_RGHT, _______, KC_INS ,
  _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END, _______, _______,
                             _______, _______, _______, _______, _______,  ADJUS, _______, _______
),
/* Raise
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |  !   |  @   |  #   |  $   |  %   |                    |  ^   |   &  |   *  |   -  |   +  |   \  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   (  |  )   |  {   |  }   |  =   |-------.    ,-------|  ?   |   :  |   "  |   _  |   =  |      |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |      |   <  |  >   |  [   |  ]   |  >   |-------|    |-------|  !   |   |  |   ~  |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI | LAlt |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_RAISE] = LAYOUT(
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  KC_GRV , KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_MINS, KC_PLUS, KC_BSLS,
  _______, KC_LPRN, KC_RPRN, KC_LCBR, KC_RCBR, KC_EQL ,                   KC_QUES, KC_COLN, KC_DQUO, KC_UNDS, KC_EQL , KC_INS,
  _______, KC_LT  , KC_GT  , KC_LBRC, KC_RBRC, KC_GT  , _______, _______, KC_EXLM, KC_PIPE, KC_TILD, XXXXXXX, XXXXXXX, _______,
                             _______, _______, ADJUS  , _______, _______, _______, _______, _______
),

/* Numeric
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |  Del | Bksp |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |   7  |   8  |   9  |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |   -  |   +  |      |-------.    ,-------|      |   4  |   5  |   6  |   +  |  HOLD|
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |   /  |   *  |      |-------|    |-------|      |   1  |   2  |   3  |   -  |   *  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | HOLD |      |      | /Space  /       \Enter \  |  0   |   ,  |  /   |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_NUMER] = LAYOUT(
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC,
  _______, KC_1,   KC_2,    KC_3,    KC_4,    KC_5    ,                   KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSPC,
  _______, XXXXXXX, XXXXXXX, KC_PPLS, KC_PMNS, XXXXXXX,                   XXXXXXX, KC_4   , KC_5   , KC_6   , KC_PPLS, _______,
  _______, XXXXXXX, XXXXXXX, KC_PAST, KC_PSLS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_1   , KC_2   , KC_3   , KC_PMNS, KC_PSLS,
                             _______, _______, _______, KC_ESC , KC_ENT , KC_0   , KC_PDOT, KC_PAST
  ),

  /* Functions
  * ,-----------------------------------------.                    ,-----------------------------------------.
  * |      |      |      |      |      |      |                    | Calc |      |      |      |      | CLock|
  * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
  * |      |  F1  |  F2  |  F3  |  F4  |      |                    |      |      |      |      |      |      |
  * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
  * | LCtl |  F5  |  F6  |  F7  |  F8  |      |-------.    ,-------|      | LShft| LCtl | LAlt | HOLD |      |
  * |------+------+------+------+------+------| Prev  |    |  Next |------+------+------+------+------+------|
  * | LShft|  F9  |  F10 |  F11 |  F12 |      |-------|    |-------|      | Mute |      |      |      |      |
  * `-----------------------------------------/       /     \      \-----------------------------------------'
  *                   |      |      | Vol- | /  Play /       \Enter \  | Vol+ |      |      |
  *                   |      |      |      |/       /         \      \ |      |      |      |
  *                   `----------------------------'           '------''--------------------'
  */
    [_FUNC] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_CALC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_CAPS,
    NUMTAB , KC_F1  , KC_F2  , KC_F3  , KC_F4  , XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_LCTL, KC_F5  , KC_F6  , KC_F7  , KC_F8  , XXXXXXX,                   XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, _______, XXXXXXX,
    KC_LSFT, KC_F9  , KC_F10 , KC_F11 , KC_F12 , XXXXXXX, KC_MPRV, KC_MNXT, XXXXXXX, KC_MUTE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                               XXXXXXX, XXXXXXX, KC_VOLD, KC_MPLY, KC_ENT , KC_VOLU, XXXXXXX, XXXXXXX
  ),



  /* Adjust (Lower + Raise)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | Reset| Debug|      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------| GAME  |    |QWERTY |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      | HOLD | /       /       \      \  | HOLD |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
  */
    [_ADJUST] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, QK_BOOT, DB_TOGG, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QWERTY , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                               XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX,  _______, XXXXXXX, XXXXXXX
    )

  /* Game
  * ,-----------------------------------------.                    ,-----------------------------------------.
  * | Esc  |   1! |   2@ |   3# |   4$ |   5% |                    |   6^ |   7& |   8* |   9( |   0) |BackSP|
  * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
  * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |      |
  * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
  * | CLck |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |  ;*  |  '   |
  * |------+------+------+------+------+------|BackSP |    |QWERTY |------+------+------+------+------+------|
  * | Shft |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
  * `-----------------------------------------/       /     \      \-----------------------------------------'
  *                   | Ctrl | LAlt | Lower| /Space  /       \Enter \  |Raise | RAlt | LGUI |
  *                   |      |      |      |/       /         \      \ |      |      |      |
  *                   `----------------------------'           '------''--------------------'
    [_GAME] = LAYOUT(
    KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,  KC_8   , KC_9,    KC_0,    KC_BSPC,
    KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,  KC_I   , KC_O,    KC_P,    XXXXXXX,
    KC_CAPS,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,  KC_K   , KC_L,    FUCSCLN, KC_QUOT,
    KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_BSPC,  QWERTY ,   KC_N,    KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                            KC_LCTL, KC_LALT,  LOWER , KC_SPC ,  KC_ENT ,  RAISE, KC_RALT,  KC_LGUI
    )    
  */
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    oled_write(read_logo(), false);
  }
    return false;
}
#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  return true;
}
