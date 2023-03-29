#include QMK_KEYBOARD_H

#define LT_1 RALT(KC_1)
#define LT_2 RALT(KC_2)
#define LT_3 RALT(KC_3)
#define LT_4 RALT(KC_4)
#define LT_5 RALT(KC_5)
#define LT_6 RALT(KC_6)
#define LT_7 RALT(KC_7)
#define LT_8 RALT(KC_8)
#define LT_9 RALT(KC_9)
#define LT_0 RALT(KC_0)
#define LT_EXLM RALT(KC_EXLM)
#define LT_AT RALT(KC_AT)
#define LT_HASH RALT(KC_HASH)
#define LT_DLR RALT(KC_DLR)
#define LT_PERC RALT(KC_PERC)
#define LT_CIRC RALT(KC_CIRC)
#define LT_AMPR RALT(KC_AMPR)
#define LT_ASTR RALT(KC_ASTR)

// Naming according to Unicode specifications
#define LT_A_OG KC_1
#define LT_C_CA KC_2
#define LT_E_OG KC_3
#define LT_E_DO KC_4
#define LT_I_OG KC_5
#define LT_S_CA KC_6
#define LT_U_OG KC_7
#define LT_U_MA KC_8
#define LT_Z_CA KC_EQL

// Cockpit bindings
#define CP_LOCK LGUI(KC_L)

enum jj40_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _FUNC
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  FUNC
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |      |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |      |
 * | Esc  |   q  |   w  |   e  |   r  |   t  |   y  |   u  |   i  |   o  |   p  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   :  |   "  |
 * | Tab  |   a  |   s  |   d  |   f  |   g  |   h  |   j  |   k  |   l  |   ;  |   '  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   <  |   >  |   ?  |      |
 * |Shift |   z  |   x  |   c  |   v  |   b  |   n  |   m  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * | Ctrl |  Fn  | GUI  | Alt  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_mit(
  QK_GESC, KC_Q,      KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  KC_TAB,  KC_A,      KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Z,      KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
  KC_LCTL, MO(_FUNC), KC_LGUI, KC_LALT, MO(_LOWER),  KC_SPC,  MO(_RAISE),   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

 /* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   Ą  |   Č  |   Ę  |   Ė  |   Į  |   Š  |   Ų  |   Ū  |   Ž  |   _  |      |
 * |   `  |   ą  |   č  |   ę  |   ė  |   į  |   š  |   ų  |   ū  |   ž  |   -  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * | Tab  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |   {  |   }  |      |      |      |      |      |
 * |Shift |   =  |   +  |   -  |   |  |   [  |   ]  |   <  |   >  |   {  |   }  | Ins  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      ||||||||             |      |      |      |      |      |
 * | Ctrl |      |      | Alt  |Lower||    Space    |      | Home | PgDn | PgUp | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_mit(
  KC_GRV,  LT_A_OG, LT_C_CA, LT_E_OG, LT_E_DO, LT_I_OG, LT_S_CA, LT_U_OG, LT_U_MA, LT_Z_CA, KC_MINS, KC_BSPC,
  KC_TAB,  LT_EXLM, LT_AT,   LT_HASH, LT_DLR,  LT_PERC, LT_CIRC, LT_AMPR, LT_ASTR, KC_LPRN, KC_RPRN, KC_DEL ,
  KC_LSFT, KC_PEQL, KC_PPLS, KC_PMNS, KC_PIPE, KC_LBRC, KC_RBRC, KC_LABK, KC_RABK, KC_LCBR, KC_RCBR, KC_INS ,
  KC_LCTL, _______, _______, KC_LALT, _______,      KC_SPC,      _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
),

 /* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |      |
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   $  |   %  |   ^  |      |      |      |      |      |      |      |   |  |
 * | Tab  |   4  |   5  |   6  |      |      |      |      |      |      |      |   \  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   &  |   *  |   (  |   )  |      |      |      |   <  |   >  |   ?  |      |
 * |Shift |   7  |   8  |   9  |   0  |      |      |      |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             ||||||||      |      |      |      |
 * | Ctrl |      |      | Alt  |      |    Space    |Raise|| Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_mit(
  KC_GRV,  LT_1,    LT_2,    LT_3,    LT_4,    LT_5,    LT_6,    LT_7,    LT_8,    LT_9,    LT_0,    KC_BSPC,
  KC_TAB,  LT_4,    LT_5,    LT_6,    _______, _______, _______, _______, _______, _______, _______, KC_BSLS,
  KC_LSFT, LT_7,    LT_8,    LT_9,    LT_0,    _______, _______, _______, KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
  KC_LCTL, _______, _______, KC_LALT, _______,      KC_SPC,      _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

 /* Functions
 *  Note: Terminal uses Calculator shortcut, change your OS keyboard shortcut appropriately.
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | RGB  | RGB  | RGB  | RGB  |  BL  |  BL  |  BL  |      | Scr  |      |      |
 * | Caps | Togl | Hue+ | Sat+ | Brt+ | Togl |Breath| Brt+ |      | Brt+ |      | Vol+ |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      | RGB  | RGB  | RGB  | WWW  | WWW  |  BL  |      | Scr  |      |      |
 * |Shift | Term | Hue- | Sat- | Brt- |  <   |  >   | Brt- |      | Brt- |PrScr | Vol- |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |||||||| RGB  |      |      |             |      |      |      |      |      |
 * | Ctrl |||Fn||| Mode | Alt  |      |    Space    |MPrev |MStop |MNext |MPlay | Lock |
 * `-----------------------------------------------------------------------------------'
 */
[_FUNC] = LAYOUT_planck_mit(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  KC_CAPS, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, BL_TOGG, BL_BRTG, BL_UP,   _______, KC_BRIU, _______, KC_VOLU,
  KC_LSFT, KC_CALC, RGB_HUD, RGB_SAD, RGB_VAD, KC_WBAK, KC_WFWD, BL_DOWN, _______, KC_BRID, KC_PSCR, KC_VOLD,
  KC_LCTL, _______, RGB_MOD, KC_LALT, _______,      KC_SPC,      KC_MPRV, KC_MSTP, KC_MNXT, KC_MPLY, CP_LOCK
)
};

// Loop
void matrix_scan_user(void) {
  // Empty
};
