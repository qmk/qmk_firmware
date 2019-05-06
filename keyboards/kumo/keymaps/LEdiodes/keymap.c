// Normal + arrow layout for MiniVan Kumo
// Created by LEdiodes on 5-2-19

#include "kumo.h"
#include "action_layer.h"
#define ____ KC_TRNS    // Creates an alias for KC_TRNS which means blank key

// Tap Dance & Layer Declarations
enum {
        L0 = 0, // Layer zero  - Off   - Default layer
        L1 = 1, // Layer one   - Blue  - Numbers
        L2 = 2, // Layer two   - Red   - Macros and Arrows
        L3 = 3, // Layer three - Green - Media Controls
        L4 = 4, // Layer four  - Green - Mouse and Arrow Control
        TD_KC_ESC_F5     = 10, //   Esc   -->   F5
        TD_KC_WIN_WIN_E  = 11, //   Win   -->   Explorer
        TD_RBRC_RPRN     = 12, //     (   -->   [
        TD_SPC_ENT       = 13, //   Spc   -->   Ent
        TD_DQT_QUOT      = 14, //     "   -->   '
        TD_LBRC_LPRN     = 15, //     (   -->   )
        TD_HOME_END      = 16, //  Home   -->   End
        TD_DOT_QUES      = 17, //     .   -->   ?
        TD_BSLASH_SLASH  = 18, //     \   -->   /
        TD_LCTL_HASH     = 19, //  Ctrl   -->   #
        TERMINAL = SAFE_RANGE,
};

// Macro Declarations
enum {
        snip      = 55, // screenshot with OneNote
        cad       = 57, // Ctrl+Alt+Del
        note      = 61, // notepad[].exe
        pin       = 65, // pin tab in chrome
        thumbup   = 68, // thumbs up emoji for skype
        handsh    = 69, // (handshake)
        bigsm     = 70, // :D
};

// Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_BSLASH_SLASH]  = ACTION_TAP_DANCE_DOUBLE(KC_BSLASH, KC_SLASH), // Tap once for \, tap twice for /
  [TD_HOME_END]      = ACTION_TAP_DANCE_DOUBLE(KC_HOME, KC_END),     // Tap once for space, tap twice for enter
  [TD_DQT_QUOT]      = ACTION_TAP_DANCE_DOUBLE(KC_DQT,	KC_QUOT),    // Tap once for ", tap twice for '
  [TD_LBRC_LPRN]     = ACTION_TAP_DANCE_DOUBLE(KC_LBRC,	KC_LPRN),    // Tap once for [, tap twice for (
  [TD_DOT_QUES]      = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_QUES),     // Tap once for ., tap twice for ?
  [TD_RBRC_RPRN]     = ACTION_TAP_DANCE_DOUBLE(KC_RBRC,	KC_RPRN),    // Tap once for left bracket, tap twice for right bracket. (,)
  [TD_KC_WIN_WIN_E]  = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, LGUI(KC_E)), // Tap once for windows, twice for windows+E to open explorer
  [TD_KC_ESC_F5]     = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_F5),       // Tap once for Esc, twice for F5 to refresh webpages and stuff
  [TD_LCTL_HASH]     = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, KC_HASH),    // Tap once for Left Ctrl, twice for #
  // Other declarations would go here, separated by commas, if you have them
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*  Default Layer 0
 * ,---------------------------------------------------------------------------.
 * |L4|EF5|  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  | BckSpc |
 * |---------------------------------------------------------------------------+
 * |  Tab  |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |L4+Ent |
 * |---------------------------------------------------------------------------+
 * | Shift    |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |Shift|    |
 * |---------------------------------------------------------------------------+
 * |Ctrl+# | Win+Exp | Alt  |    L3(DEL)  | (L3)SPACE |  L2 | [+( | ]+)  | "+' |
 * `---------------------------------------------------------------------------'
 */
[L0] = LAYOUT(LT(MO(L4),TD(TD_KC_ESC_F5)), KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, \
              LT(MO(L2), KC_TAB), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, LT(MO(L3),KC_ENT), \
              KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_RSHIFT, MO(L1), \
              TD(TD_LCTL_HASH), TD(TD_KC_WIN_WIN_E), KC_LALT, KC_NO, LT(MO(L3), KC_DEL), LT(MO(L3), KC_SPC), MO(L2), TD(TD_LBRC_LPRN), TD(TD_RBRC_RPRN), TD(TD_DQT_QUOT) \
             ),

/* Blue Layer 1 - Numbers
 * ,----------------------------------------------------------------------------.
 * | F1+ | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 |   F12    |
 * |----------------------------------------------------------------------------+
 * | 1    |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |    =    |
 * |----------------------------------------------------------------------------+
 * |          |     |     |     |     |  '  |  /  |  [  |  ]  |  \  |SHIFT|     |
 * |----------------------------------------------------------------------------+
 * | RESET |        |      |             | HOME+END |         |VOL- |MUTE |VOL+ |
 * `----------------------------------------------------------------------------'
 */
[L1] = KEYMAP(LT(KC_F1, KC_GRV), KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, \
              KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, \
              ____, ____, ____, ____, ____, KC_QUOT, KC_SLSH, KC_LBRC, KC_RBRC, KC_BSLS, KC_LSFT, ____, \
              RESET, ____, ____, KC_NO, ____, TD(TD_HOME_END), ____, KC_VOLD, KC_MUTE, KC_VOLU \
             ),

/* Red Layer 2 - Macros and Arrows
 * ,----------------------------------------------------------------------------.
 * |     |     |     |     |     |     |     |PGUP | UP  |PGDN |     |          |
 * |----------------------------------------------------------------------------+
 * | CAPS |     |     |     |     |     |HOME |LEFT |DOWN |RIGHT|     |         |
 * |----------------------------------------------------------------------------+
 * |         |     |     |     |     |     | END |     |     |     |THMBUP|     |
 * |----------------------------------------------------------------------------+
 * | RESET |  CAD  |      |             |           |        |SNIP |HNDSHK|NOTE |
 * `----------------------------------------------------------------------------'
 */
[L2] = KEYMAP(____, ____, ____, ____, ____, ____, ____, KC_PGUP, KC_UP, KC_PGDN, ____, ____, \
              KC_CAPS, ____, ____, ____, ____, ____, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, ____, ____, \
              ____, ____, ____, ____, ____, ____, KC_END, ____, ____, ____, M(thumbup), ____, \
              RESET, ____, M(cad), KC_NO, ____, ____, ____, M(snip), M(handsh), M(note) \
             ),

/* Green Layer 3 - Media Controls
 * ,---------------------------------------------------------------------------.
 * |     |     |     |     |     |     |     |     |     |     |     |   DEL   |
 * |---------------------------------------------------------------------------+
 * |      |     |     |     |     |     |     |     |     |     |     |  VOL+  |
 * |---------------------------------------------------------------------------+
 * |         |     |     |     |     |     |     |     |     |MUTE |STOP |VOL- |
 * |---------------------------------------------------------------------------+
 * |RESET |        |      |             |            |   L2  |PREV |PLAY |NEXT |
 * `---------------------------------------------------------------------------'
 */
[L3] = KEYMAP(____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, KC_DEL, \
              ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, KC_VOLU, \
              ____, ____, ____, ____,____, ____, ____, ____, ____, KC_MUTE, KC_MSTP, KC_VOLD, \
              RESET,  ____, ____, KC_NO, ____, ____, ____, KC_MPRV, KC_MPLY, KC_MNXT \
             ),

/* Green Layer 4 - Mouse and Arrow Control
 * ,---------------------------------------------------------------------------.
 * | BTN1|     |     |     |     |     |     |BTN1 | M-U |BTN2 |     |  BTN2   |
 * |---------------------------------------------------------------------------+
 * |      |     |     |     |     |     |     | M-L | M-D | M-R |     |        |
 * |---------------------------------------------------------------------------+
 * |         |     |     |     |     |     |     |     |     |     | UP  |     |
 * |---------------------------------------------------------------------------+
 * |RESET |        |      |             |            |       |LEFT |DOWN |RIGHT|
 * `---------------------------------------------------------------------------'
 */
[L4] = KEYMAP(KC_BTN1, ____, ____, ____, ____, ____, ____, KC_BTN1, KC_MS_U, KC_BTN2, ____, KC_BTN2, \
              ____, ____, ____, ____, ____, ____, ____, KC_MS_L, KC_MS_D, KC_MS_R, ____, ____, \
              ____, ____, ____, ____,____, ____, ____, ____, ____, ____, KC_UP, ____, \
              RESET,  ____, ____, KC_NO, ____, ____, ____, KC_LEFT, KC_DOWN, KC_RIGHT \
             ),
};
// Macros
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
	switch (id) {
		case snip: // screenshot with OneNote
			if (record->event.pressed) {
				return MACRO( D(LSFT), D(LGUI), T(S), U(LGUI), U(LSFT), END );
			}
			break;
		case cad: // Ctrl+Alt+Del
			if (record->event.pressed) {
				return MACRO( D(LALT), D(LCTL), D(DEL), U(DEL), U(LCTL), U(LALT) );
			}
			break;
		case note: // notepad.exe
			if (record->event.pressed) {
                return MACRO( D(LGUI), T(R), W(100), U(LGUI), T(N), T(O), T(T), T(E), T(P), T(A), T(D), T(DOT), T(E), T(X), T(E), T(ENT), END );
			}
      break;
    case pin:
			if (record->event.pressed) {
				return MACRO( D(LCTL), D(LSFT), W(10), D(X), U(X), U(LSFT), U(LCTL), END );
			}
      break;
    case thumbup:
			if (record->event.pressed) {
				return MACRO( I(10), D(LSFT), T(9), U(LSFT), T(Y), D(LSFT), T(0), U(LSFT), END );
			}
      break;
    case handsh:
			if (record->event.pressed) {
				return MACRO( I(10), D(LSFT), T(9), U(LSFT), T(H), T(A), T(N), T(D), T(S), T(H), T(A), T(K), T(E), D(LSFT), T(0), U(LSFT), END );
			}
      break;
    case bigsm:
			if (record->event.pressed) {
				return MACRO( I(10), D(LSFT), T(SCOLON), U(LSFT), D(LSFT), T(D), U(LSFT), END );
			}
      break;
	}
	return MACRO_NONE;
}

// LED control per layer
// purple -- (0x7A,  0x00, 0xFF);
uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
    case 0:
        // Off
        rgblight_setrgb (0x00,  0x00, 0x00);
        //rgblight_sethsv_at(360, 255, 255, 0);
        break;
    case 1:
        // Blue
        rgblight_setrgb (0x00,  0x00, 0xFF);
        //rgblight_sethsv_at(140, 255, 255, 1);
        break;
    case 2:
        // Red
        rgblight_setrgb (0xFF,  0x00, 0x00);
        //rgblight_sethsv_at(140, 125, 125, 1);
        break;
    case 3:
        // Green
        rgblight_setrgb (0x00,  0xFF, 0x00);
        break;
    default: //  Else, default(PowerShell), any other layer not specified
        // Off
        rgblight_setrgb (0x00,  0x00, 0x00);
        break;
    }
  return state;
}
