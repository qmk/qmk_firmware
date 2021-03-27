#include QMK_KEYBOARD_H

enum layers {
  LAYER_HOME, // home base layer
  LAYER_FUNC, // function keys and cursors
  LAYER_LOWER,
  LAYER_RAISE, 
  LAYER_SYST, // media, mouse and other system keys
  LAYER_ARROWPAD,
  LAYER_NUMPAD,
  LAYER_MEDIAPAD,
};

enum custom_keycodes {
  CK_TRIPLEZERO = SAFE_RANGE,
  KC_PRVWD,
  KC_NXTWD,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * LEGEND:
 *
 * ,--------------------------------.
 * |     Top row: shifted character |
 * | Central row: standard char     |
 * |  Bottom row: hold modifier     |
 * `--------------------------------'
 *
 *  "____" means free to be assigned
 *
 */

/* Qwerty Home Layer
 * ,---------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |
 * |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |
 * | ____ | ____ | ____ | ____ | ____ | FnNav|      |  Alt | Ctrl | Shift|
 * |------+------+------+------+-------------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |
 * |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  | Enter|
 * | Shift| SysL |      | AltGr| OSkey| OSkey| AltGr| FnNav|      | Shift|
 * '------+------+------+------+------+------|------+------+------+------'
 * |      |      |      |      |      |      |      |      |      |      |       
 * |   Z  |   X  |   C  |   V  |Enter |Space |   B  |   N  |   M  | Space|       
 * | Ctrl |  Alt | Cmd  | FunL |Lower |Raise | Nav  |  Alt | Ctrl | Shift|       
 * '---------------------------------------------------------------------'       
 */
  [LAYER_HOME] = LAYOUT_ortho_3x10(
    LT(LAYER_ARROWPAD, KC_Q), LT(LAYER_NUMPAD, KC_W), LT(LAYER_MEDIAPAD, KC_E), KC_R, KC_T, LT(LAYER_FUNC, KC_Y), KC_U, MT(MOD_LALT, KC_I), MT(MOD_RCTL, KC_O), MT(MOD_RSFT, KC_P),
    MT(MOD_LSFT, KC_A), LT(LAYER_SYST, KC_S), KC_D, MT(MOD_RALT, KC_F), MT(MOD_LGUI, KC_G), MT(MOD_RGUI, KC_H), MT(MOD_RALT, KC_J), LT(LAYER_FUNC, KC_K), KC_L, MT(MOD_RSFT, KC_BSPC),
    MT(MOD_LCTL, KC_Z), MT(MOD_LALT, KC_X), MT(KC_LCMD, KC_C), LT(LAYER_FUNC, KC_V), LT(LAYER_LOWER, KC_ENT), LT(LAYER_RAISE, KC_SPC), LT(LAYER_ARROWPAD, KC_B), MT(MOD_LALT, KC_N), MT(MOD_RCTL, KC_M), MT(MOD_RSFT, KC_BSPC)
  ),

/* Function and Navigation Layer
 * ,---------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |
 * | ____ | ____ | ____ | ____ | ____ | ____ |SysLay|  Alt | Ctrl | Shift|
 * |------+------+------+------+-------------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |
 * |  ESC | Home | PgDn | PgUp |  End | Left | Down |  Up  | Right|Backsp|
 * | Shift| ____ |SysLay| AltGr| OSkey| OSkey| AltGr| ____ |SysLay| Shift|
 * |------+------+------+------+------+------|------+------+------+------'
 * |      |      |      |      |      |      |      |      |      |      |       
 * |      |  F11 |  F12 |      | Space|PrnScr|ScrLck|Pause |Backsp|      |       
 * |      | Ctrl |  Alt | ____ |SysLay| Shift|  Alt | Ctrl | Shift|      |       
 * `---------------------------------------------------------------------'       
 */
  [LAYER_FUNC] = LAYOUT_ortho_3x10(
    KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, LT(LAYER_SYST, KC_F7), MT(MOD_LALT, KC_F8), MT(MOD_RCTL,KC_F9), MT(MOD_RSFT, KC_F10),
    MT(MOD_LSFT, KC_ESC), KC_HOME, LT(LAYER_SYST, KC_PGDN), MT(MOD_RALT, KC_PGUP), MT(MOD_LGUI, KC_END), MT(MOD_RGUI, KC_LEFT), MT(MOD_RALT, KC_DOWN), KC_UP, LT(LAYER_SYST, KC_RGHT), MT(MOD_RSFT, KC_BSPC),
    KC_DOWN, MT(KC_LCTL, KC_F11), MT(KC_LALT, KC_F12), KC_NO, LT(LAYER_SYST, KC_SPACE), MT(KC_LSFT, KC_PSCR), MT(KC_LALT, KC_SLCK), MT(KC_RCTL, KC_PAUS), MT(MOD_RSFT, KC_BSPC), KC_UP
  ),

/* Lower (Symbols Layer)
 * ,---------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |
 * |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |
 * | ____ | ____ | ____ | ____ | ____ | ____ | ____ |      |      |      |
 * |------+------+------+------+-------------+------+------+------+------|
 * |      |   ~  |   _  |   +  |      |      |      |      |      |      |
 * |  TAB |   `  |   -  |   =  |   [  |   ]  |  _   |   +  |   {  |   }  |
 * | Shift|SysLay| ____ | AltGr| OSkey| OSkey| AltGr|SysLay| ____ | Shift|
 * ' -----+------+------+------+------+------|------+------+------+------'
 * |      |      |      |      |      |      |   <  |   >  |   ?  |      | 
 * |      |BackSp|  Del |      |      |      |   ,  |   .  |   /  | Shift|
 * |      | Ctrl |  Alt |      |      |      |  Alt | Ctrl | Shift|      |       
 * ----------------------------------------------------------------------'       
 */
  [LAYER_LOWER] = LAYOUT_ortho_3x10(
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN,
    MT(MOD_LSFT, KC_TAB), LT(LAYER_SYST, KC_GRV), KC_MINS, MT(MOD_RALT, KC_EQL), MT(MOD_LGUI, KC_LBRC), MT(MOD_RGUI, KC_RBRC), KC_UNDS, KC_PLUS, KC_LCBR, MT(MOD_RSFT, KC_RCBR),
    _______, MT(KC_LCTL, KC_BSPC), MT(KC_LALT, KC_DEL), _______, _______, _______, MT(MOD_LSFT, KC_COMM), MT(MOD_LALT, KC_DOT), MT(MOD_RCTL, KC_SLSH), MOD_RSFT
  ),

  /* Raise (Numbers)
 * ,---------------------------------------------------------------------.
 * |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |
 * |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |
 * | ____ | ____ | ____ | ____ | ____ |      | ____ |  Alt | Ctrl | Shift|
 * |------+------+------+------+-------------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |   "  |      |
 * |  Esc |      |      | Vol+ |      |      |   -  |   =  |   '  | Del  |
 * | Shift|      |      |      |      |      |      |      | ____ | Shift|
 * ' -----+------+------+------+------+------|------+------+------+------'
 * |      |      |      |      |      |      |   <  |   >  |   ?  |      |       
 * | Prev | Next | Pause| Vol- | Enter|      |   ,  |   .  |   /  | Enter|       
 * |      |      |      |      |SysLay| ____ |      |      |      |      |       
 * ----------------------------------------------------------------------'       
 */
  [LAYER_RAISE] = LAYOUT_ortho_3x10(
    KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0,
    MT(MOD_LSFT, KC_ESC), _______, _______, KC_VOLD, _______, _______, KC_MINS, KC_EQL, KC_QUOT, MT(MOD_RSFT, KC_DEL),
    KC_MPRV, KC_MNXT, KC_MPLY, KC_VOLD, _______, _______, KC_COMM, KC_DOT,  KC_SLSH, _______
  ),

/* System Layer
 * ,---------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |
 * | Play | Stop | Prev | Next |MsBtn1|MsLeft|MSDown| MsUp |MsRigh|RESET |
 * | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ |      |
 * |------+------+------+------+-------------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |
 * |Backsp| Mute |      |      |MsWhlD| Left | Down |  Up  | Right|Backsp|
 * | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ |
 * '------+------+------+------+------+------|------+------+------+------'
 * |      |      |      |      |      |      |      |      |      |      |       
 * |      | ____ | ____ | Enter| Space| Mute | Vol- | Vol+ | Space|      |       
 * |      | Ctrl |  Alt | ____ | ____ | Shift| Alt  | Ctrl | ____ |      |       
 * '---------------------------------------------------------------------'       
 */
  [LAYER_SYST] = LAYOUT_ortho_3x10(
    KC_MPLY, KC_STOP, KC_MPRV, KC_MNXT, KC_MS_BTN1, KC_MS_LEFT, KC_MS_DOWN, KC_MS_UP, KC_MS_RIGHT, RESET,
    KC_BSPC, XXXXXXX, XXXXXXX, XXXXXXX, KC_APP, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_BSPC,
    KC_PGDN, MT(KC_LCTL, KC_CAPS), MT(KC_LALT, KC_INS), KC_ENT, KC_SPC, MT(MOD_RSFT, KC_MUTE), MT(MOD_LALT, KC_VOLD), MT(MOD_RCTL, KC_VOLU), KC_SPC, KC_PGUP
  ),

 /* ArrowPad   /------mouse-------\ /-----cursor-------\
 * ,---------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |
 * |      |      |      |MsBtn1| MsUp |MsBtn2|PrevW |  Up  | NextW|Backsp|
 * | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ |
 * |------+------+------+------+-------------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |
 * |  Esc |      |      |MsLeft|MsDown|MsRigh| Left | Down | Right| Enter|
 * |      | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ |
 * '------+------+------+------+------+------|------+------+------+------'
 *        |      |      |      |      |      |      |      |      |      |        
 *        |      |      |MsWhlU|MsDown|MsWhlD| Home | PgUp | PgDn | End  |       
 *        | Ctrl |  Alt | ____ | ____ | ____ | ____ | ____ | ____ |      |       
 *        '--------------------------------------------------------------'       
 */
  [LAYER_ARROWPAD] = LAYOUT_ortho_3x10(
    KC_NO, KC_NO, KC_NO, KC_MS_BTN1, KC_MS_UP, KC_MS_BTN2, KC_PRVWD, KC_UP, KC_NXTWD, KC_BSPC, 
    KC_ESC, KC_NO, KC_NO, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, KC_LEFT, KC_DOWN, KC_RIGHT, KC_ENT, 
    XXXXXXX, KC_LCTL, KC_LALT, KC_MS_WH_UP, KC_MS_DOWN, KC_MS_WH_DOWN, KC_HOME, KC_PGUP, KC_PGDN, KC_END 
  ),

/* NumPad (mod su W)
 * ,---------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |
 * |      |      |   3  |   *  |   -  |Backsp|   7  |   8  |   9  |  0   |
 * | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ |
 * |------+------+------+------+-------------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |
 * |      |      |   /  |   =  |   +  |   .  |   4  |   5  |   6  | Enter|
 * | Shift| ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ |
 * '------+------+------+------+------+------|------+------+------+------'
 *        |      |      |      |      |      |      |      |      |      |       
 *        |      |      |      |  Tab |   ,  |   1  |   2  |   3  |      |       
 *        | Ctrl |  Alt | ____ | ____ | ____ | ____ | ____ | ____ |      |       
 *        '--------------------------------------------------------------'       
 */
  [LAYER_NUMPAD] = LAYOUT_ortho_3x10(
    KC_NO, KC_NO, KC_3, KC_KP_ASTERISK, KC_KP_MINUS, KC_BSPC, KC_7, KC_8, KC_9, KC_0, 
    KC_LSFT, KC_NO, KC_KP_SLASH, KC_KP_EQUAL, KC_KP_PLUS, KC_DOT, KC_4, KC_5, KC_6, KC_ENT, 
    XXXXXXX, KC_LCTL, KC_LALT, KC_NO, KC_TAB, KC_COMM, KC_1, KC_2, KC_3, XXXXXXX 
  ),

    
};


void matrix_init_user(void) {
  // eeconfig_init(); // reset keyboard to a standard default state; useful when new releases messup with eeprom values
  // set num lock on at start (for numonly layer to work)
  if (!host_keyboard_led_state().num_lock) {
      tap_code(KC_NUMLOCK);
  }
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CK_TRIPLEZERO:
      if (record->event.pressed) {
        SEND_STRING("000");
      } // else { when released }
      break;
    case KC_PRVWD:
    if (record->event.pressed) {
        if (keymap_config.swap_lctl_lgui) {
            register_mods(mod_config(MOD_LALT));
            register_code(KC_LEFT);
        } else {
            register_mods(mod_config(MOD_LCTL));
            register_code(KC_LEFT);
        }
    } else {
        if (keymap_config.swap_lctl_lgui) {
            unregister_mods(mod_config(MOD_LALT));
            unregister_code(KC_LEFT);
        } else {
            unregister_mods(mod_config(MOD_LCTL));
            unregister_code(KC_LEFT);
        }
    }
    break;
case KC_NXTWD:
      if (record->event.pressed) {
        if (keymap_config.swap_lctl_lgui) {
            register_mods(mod_config(MOD_LALT));
            register_code(KC_RIGHT);
        } else {
            register_mods(mod_config(MOD_LCTL));
            register_code(KC_RIGHT);
        }
    } else {
        if (keymap_config.swap_lctl_lgui) {
            unregister_mods(mod_config(MOD_LALT));
            unregister_code(KC_RIGHT);
        } else {
            unregister_mods(mod_config(MOD_LCTL));
            unregister_code(KC_RIGHT);
        }
    }
    break;
  }
  return true;
};

void keyboard_pre_init_user(void) {
  // Set our LED pins as output
  setPinOutput(D5);
  setPinOutput(B0);
}

bool led_update_user(led_t led_state) {
    writePin(D5, !led_state.num_lock);
    writePin(B0, !led_state.caps_lock);
    return false; // prevent keyboard from processing state
}
