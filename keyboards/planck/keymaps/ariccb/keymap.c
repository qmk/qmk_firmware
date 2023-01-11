 /* Copyright 2021 Aric Crosson Bouwers
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 2 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */

#include QMK_KEYBOARD_H
#include "muse.h"
#include "features/select_word.h"
#include "features/caps_word.h"

// using the Word Selection QMK Macro by Pascal Getreuer, found here: https://getreuer.info/posts/keyboards/select-word/index.html
// THANKS Pascal for such amazing functionality!!

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _COLEMAK_VCP 1
#define _LOWER 2
#define _RAISE 3
#define _NUMPAD 4
#define _FN 5
#define _ADJUST 6
#define _GAMING 7

#define MICMUTE LALT(KC_M)
#define DESKTR LGUI(LCTL(KC_RGHT))  // move one virtual desktop to the right
#define DESKTL LGUI(LCTL(KC_LEFT))  // move one virtual desktop to the left
#define MTLCTL_F9 MT(MOD_LCTL, KC_F9)
#define MTLSFT_F10 MT(MOD_LSFT, KC_F10)
#define MTLALT_F11 MT(MOD_LALT, KC_F11)
#define MTLGUI_Z MT(MOD_LGUI, KC_Z)
#define MTLALT_PL MT(MOD_LALT, KC_MPLY)
#define MTLALT_NXT MT(MOD_LALT, KC_MNXT)
#define MTENTER MT(MOD_LCTL, KC_ENT)
#define MTRSFTBSLS MT(MOD_RSFT, KC_BSLS)
#define MTRCTLQUO MT(MOD_RCTL, KC_QUOT)
#define MTTAB MT(MOD_LCTL | MOD_LGUI | MOD_LALT, KC_TAB)
#define LTESC LT(_FN, KC_ESC)
#define MTPLAY MT(MOD_RALT, KC_MPLY)
#define KC_COPY LCTL(KC_C)
#define KC_CUT LCTL(KC_X)
#define KC_PASTE LCTL(KC_V)
#define KC_WINPASTE LGUI(KC_V)
#define KC_PTXT LCTL(LSFT(KC_V))
#define KC_UNDO LCTL(KC_Z)
#define KC_REDO LCTL(KC_Y)

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK_VCP,
  LOWER,
  RAISE,
  FN,
  ADJUST,
  NUMPAD,
  GAMING,
  EXT_NUM,
  EXT_GAMING,
  SELWORD,
  BRACES,
  BRACES2,
  ARROW,
  ALT_TAB
};

// Define a type for as many tap dance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

 // Our custom tap dance keys; add any other tap dance keys to this enum
enum {
    UNDS_LOWER,
    PLAY_RAISE
};

// Declare the functions to be used with your tap dance key(s)
// Function associated with all tap dances
td_state_t cur_dance(qk_tap_dance_state_t *state);

// Functions associated with individual tap dances
void usl_finished(qk_tap_dance_state_t *state, void *user_data);
void usl_reset(qk_tap_dance_state_t *state, void *user_data);

/* ----------------------------------------------------------------------------------------------------------------------------- */

// This is a completely modified layout that stikes a balance between muscle memory for keys, where I was coming from a standard
// Qwerty keyboard, and efficiency gained by using layers. I've switched tab and esc because it's more natural to me this way, and
// added layer switch on hold functionality for each key. Enter has moved to the key beside LOWER, to allow usage while still having
// the right hand on the mouse.

// Lower incorporates a numpad on the right side, and all of the symbols included on the left. There is logic for the symbols needed for
// calculators and math are located around the numpad, and coding symbols are placed in easy to remember spots.

// CAPS has moved to the Fn layer, and a few additional shortcut modifiers like CTRL_ALT_UP and DOWN for adding additional cursors in VSCode.
// Play/Pause has a prime spot on the base layer, and the Fn version skips to next track

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* MIT Layout (QWERTY)
 *
 * ,------------------------------------------------------------------------.
 * |FN,Esc|  q  |  w  |  e  |  r  |  t  |  y  |  u  |  i  |  o  |  p  |Bsp  |
 * |------------------------------------------------------------------------|
  |CSW,Tab|  a  |  s  |  d  |  f  |  g  |  h  |  j  |  k  |  l  |  ;  |Ctl,'|
 * |------------------------------------------------------------------------|
 * |Shift |Win,z|  x  |  c  |  v  |  b  |  n  |  m  |  ,  |  .  |  /  |Sft,\|
 * |------------------------------------------------------------------------|
 * |      |     |     |Ctl,Ent|LOWER|  Space  |RAISE|Alt,Play|  |     |     |
 * `------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid( /* QWERTY */
    LTESC,   KC_Q,     KC_W,     KC_E,    KC_R,           KC_T,   KC_Y,   KC_U,   KC_I,      KC_O,   KC_P,    KC_BSPC,
    MTTAB,   KC_A,     KC_S,     KC_D,    KC_F,           KC_G,   KC_H,   KC_J,   KC_K,      KC_L,   KC_SCLN, MTRCTLQUO,
    KC_LSFT, MTLGUI_Z, KC_X,     KC_C,    KC_V,           KC_B,   KC_N,   KC_M,   KC_COMM,   KC_DOT, KC_SLSH, MTRSFTBSLS,
    KC_NO,   KC_NO,    KC_NO,    MTENTER, TD(UNDS_LOWER), KC_SPC, KC_SPC, MO(3),  MTLALT_PL, KC_NO,  KC_NO,   KC_NO
 ),

 /* MIT Layout (COLEMAK_VCP)
 *
 * ,------------------------------------------------------------------------.
 * |FN,ESC|  q  |  w  |  f  |  d  |  b  |  j  |  l  |  u  |  y  |  ;  | Bsp |
 * |------------------------------------------------------------------------|
  |CSW,Tab|  a  |  r  |  s  |  t  |  g  |  m  |  n  |  e  |  i  |  o  |Ctl,'|
 * |------------------------------------------------------------------------|
 * |Shift |Win,z|  x  |  v  |  c  |  p  |  k  |  h  |  ,  |  .  |  /  |Sft,\|
 * |------------------------------------------------------------------------|
 * |      |     |   |Ctl,Ent|LWR,_|   Space   |RAISE|Alt,Play|  |     |     |
 * `------------------------------------------------------------------------'
 */
[_COLEMAK_VCP] = LAYOUT_planck_grid( /* COLEMAK_VCP */
    LTESC,   KC_Q,     KC_W,     KC_F,    KC_D,           KC_B,   KC_J,   KC_L,   KC_U,      KC_Y,   KC_SCLN, KC_BSPC,
    MTTAB,   KC_A,     KC_R,     KC_S,    KC_T,           KC_G,   KC_M,   KC_N,   KC_E,      KC_I,   KC_O,    MTRCTLQUO,
    KC_LSFT, MTLGUI_Z, KC_X,     KC_V,    KC_C,           KC_P,   KC_K,   KC_H,   KC_COMM,   KC_DOT, KC_SLSH, MTRSFTBSLS,
    KC_NO,   KC_NO,    KC_NO,    MTENTER, TD(UNDS_LOWER), KC_SPC, KC_SPC, MO(3),  MTLALT_PL, KC_NO,  KC_NO,   KC_NO
 ),

/* MIT Layout (RAISE)
 *
 * ,----------------------------------------------------------------------------.
 * |  ~  |  !  |     |     |      |      |      |  Cut  | Undo| Redo|P2TXT| Bsp |
 * |----------------------------------------------------------------------------|
 * |     |Menu |     |     |      |      |ARROW |SELWORD|Copy|Paste|WinPst|  "  |
 * |----------------------------------------------------------------------------|
 * |     |Vol+ |Vol- | Mute|      |      |Braces|Braces2|  <  |  >  |  ?  |  !  |
 * |----------------------------------------------------------------------------|
 * |     |     |     |     |Adjust|             |       |     |     |     |     |
 * `----------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid( /* RAISE */
  KC_TILD, KC_EXLM, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_CUT,  KC_UNDO, KC_REDO,  KC_PTXT,     KC_BSPC,
  KC_TRNS, KC_APP,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, ARROW,   SELWORD, KC_COPY, KC_PASTE, KC_WINPASTE, KC_DQUO,
  KC_TRNS, KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS, BRACES,  BRACES2, KC_LABK, KC_RABK,  KC_QUES,     KC_EXLM,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(6),   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_NO,       KC_NO
),

/* MIT Layout (LOWER)
 * XZ
 * ,-----------------------------------------------------------------------.
 * |  `  |  !  |  #  |  $  |  <  |  >  |  :  |  7  |  8  |  9  |  =  | Bsp |
 * |-----------------------------------------------------------------------|
 * |  '  |  _  |  ^  |  %  |  (  |  )  |  M  |  4  |  5  |  6  |  -  |  +  |
 * |-----------------------------------------------------------------------|
 * |Shift|  |  |  &  |  "  |  {  |  }  |  @  |  1  |  2  |  3  |  /  |  *  |
 * |-----------------------------------------------------------------------|
 * |     |     |     |     |     |         |MO(6),0|  .  |     |     |     |
 * `-----------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid( /* LOWER */
  KC_GRV,  KC_EXLM, KC_HASH, KC_DLR,  KC_LABK, KC_RABK, KC_COLN, KC_P7, KC_P8,   KC_P9,  KC_EQL,  KC_BSPC,
  KC_QUOT, KC_UNDS, KC_CIRC, KC_PERC, KC_LPRN, KC_RPRN, KC_M,    KC_P4, KC_P5,   KC_P6,  KC_PMNS, KC_PPLS,
  KC_TRNS, KC_PIPE, KC_AMPR, KC_DQUO, KC_LCBR, KC_RCBR, KC_AT,   KC_P1, KC_P2,   KC_P3,  KC_PSLS, KC_PAST,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P0, KC_PDOT, KC_NO,  KC_NO,   KC_NO
),

/* MIT Layout (GAMING)
 *.
 * ,-----------------------------------------------------------------------.
 * |ESC,`|  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |EXIT GAMING|
 * |-----------------------------------------------------------------------|
 * | TAB |  Q  |  W  |  E  |  R  |  T  |  I  |  4  |  5  |  6  |  -  |  +  |
 * |-----------------------------------------------------------------------|
 * |Shift|  A  |  S  |  D  |  F  |  G  |  K  |  1  |  2  |  3  |  /  |  *  |
 * |-----------------------------------------------------------------------|
 * |     |     |     |  Ctl | Alt |   SPACE   |  0  |  .  |     |     |    |
 * `-----------------------------------------------------------------------'
 */
[_GAMING] = LAYOUT_planck_grid( /* GAMING */
  QK_GESC, KC_1,  KC_2,  KC_3,    KC_4,    KC_5,   KC_6,   KC_7,  KC_P8,   KC_9,  KC_0,    EXT_GAMING,
  KC_TAB,  KC_Q,  KC_W,  KC_E,    KC_R,    KC_T,   KC_I,   KC_P4, KC_P5,   KC_P6, KC_PMNS, KC_PPLS,
  KC_LSFT, KC_A,  KC_S,  KC_D,    KC_F,    KC_G,   KC_K,   KC_P1, KC_P2,   KC_P3, KC_PSLS, KC_PAST,
  KC_NO,   KC_NO, KC_NO, KC_LCTL, KC_LALT, KC_SPC, KC_SPC, KC_P0, KC_PDOT, KC_NO, KC_NO,   KC_NO
),

/* MIT Layout (FN)
 *
 * ,----------------------------------------------------------------------------.
 * | |Ctl,F9 |Sft,F10|Alt,F11| F12 |MyComp|Calc  |home |  up  | end |PrtScr| Del |
 * |-----------------------------------------------------------------------------|
 * |    | F5 |   F6  |   F7  | F8  |DeskL |DeskR |left | down |right|ScrLck| CAPS|
 * |-----------------------------------------------------------------------------|
 * |    | F1 |   F2  |   F3  | F4  |ALT_TAB|MicM |pgup |LCA_dn| pgdn|Pse/Brk| Ins|
 * |-----------------------------------------------------------------------------|
 * |    |    |       |       |     |             |     |Alt,MNext|  |      |     |
 * `-----------------------------------------------------------------------------'
 */
[_FN] = LAYOUT_planck_grid( /* FUNCTION */
  KC_TRNS, MTLCTL_F9, MTLSFT_F10, MTLALT_F11, KC_F12,  KC_MYCM, KC_CALC, KC_HOME, KC_UP,        KC_END,  KC_PSCR,   KC_DEL,
  KC_TRNS, KC_F5,     KC_F6,      KC_F7,      KC_F8,   DESKTL,  DESKTR,  KC_LEFT, KC_DOWN,      KC_RGHT, KC_SCRL,   KC_CAPS,
  KC_TRNS, KC_F1,     KC_F2,      KC_F3,      KC_F4,   ALT_TAB, MICMUTE, KC_PGUP, LCA(KC_DOWN), KC_PGDN, KC_PAUSE, KC_INS,
  KC_NO,   KC_NO,     KC_NO,      KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MTLALT_NXT,   KC_NO,   KC_NO,    KC_NO
),

/* MIT Layout (ADJUST)
 *
 * ,-----------------------------------------------------------------------------.
 * |RGBtog|Ms3 | Ms2 |MsUp | Ms1  |  Hue+|  Hue- | Sat+| Sat- |Brt+ |Brt- | Boot |
 * |-----------------------------------------------------------------------------|
 * |RGBMod| MWL | MsL |MDn  |MsR  |GAMING|       |AU_ON|AU_OFF|MU_ON|MU_OF| Debug|
 * |-----------------------------------------------------------------------------|
 * |     |MWLft|MWUp |NWDn |NWRght|QWERTY|CMK_VCP|MI_ON|MI_OF |     |     |MU_Mod|
 * |-----------------------------------------------------------------------------|
 * |     |     |     |SLEEP|      |              |     |      |     |     |      |
 * `-----------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid( /* ADJUST LAYER */
  RGB_TOG, KC_BTN3, KC_BTN2, KC_MS_U, KC_BTN1, RGB_HUI, RGB_HUD,     RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, QK_BOOT,
  RGB_MOD, KC_NO,   KC_MS_L, KC_MS_D, KC_MS_R, GAMING,  KC_NO,       AU_ON,   AU_OFF,  MU_ON,   MU_OFF,  DB_TOGG,
  KC_TRNS, KC_WH_L, KC_WH_U, KC_WH_D, KC_WH_R, QWERTY,  COLEMAK_VCP, MI_ON,   MI_OFF,  KC_TRNS, KC_TRNS, MU_NEXT,
  KC_NO,   KC_NO,   KC_NO,   KC_SLEP, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,   KC_NO
)
};

#ifdef AUDIO_ENABLE
float layerswitch_song[][2] = SONG(PLANCK_SOUND);
float tone_startup[][2]     = SONG(STARTUP_SOUND);
float tone_qwerty[][2]      = SONG(QWERTY_SOUND);
float tone_COLEMAK_VCP[][2] = SONG(COLEMAK_SOUND);
float music_scale[][2]      = SONG(MUSIC_SCALE_SOUND);
float tone_goodbye[][2]     = SONG(GOODBYE_SOUND);

#endif

bool is_alt_tab_active = false;
layer_state_t layer_state_set_user(layer_state_t state) {

	static bool is_this_layer_on = false;
	if (layer_state_cmp(state, 4) != is_this_layer_on) {
		is_this_layer_on = layer_state_cmp(state, 4);
		if (is_this_layer_on) {
			PLAY_SONG(layerswitch_song);
		}
		else {
			stop_all_notes();
		}
	}
  if (is_alt_tab_active) {
        unregister_code(KC_LALT);
        is_alt_tab_active = false;
    }
    return state;

	switch (get_highest_layer(state)) {
		case _ADJUST:
			rgblight_setrgb (0xFF,  0x00, 0x00);
			break;
		case _LOWER:
			rgblight_setrgb (0x00,  0x00, 0xFF);
			break;
    case _NUMPAD:
			rgblight_setrgb (0x00,  0x00, 0xFF);
			break;
		case _RAISE:
			rgblight_setrgb (0x7A,  0x00, 0xFF);
			break;
		case _FN:
			rgblight_setrgb (0x00,  0xFF, 0x00);
			break;
		default: //  for any other layers, or the default layer
			rgblight_setrgb (0xFF,  0xFF, 0xFF);
			break;
		}
	  return state;
}

// void dance_media (qk_tap_dance_state_t *state, void *user_data)
//     if (state->count == 1) {
//         tap_code(KC_MPLY);
//     } else if (state->count == 2) {
//         tap_code (KC_MNXT);
//     } else if (state->count == 3) {
//         tap_code(KC_MPRV);
//     } else {
//         reset_tap_dance (state);
//     }
// }

// qk_tap_dance_action_t tap_dance_actions[] = {
//  [0] = ACTION_TAP_DANCE_FN (dance_media),
// };

// Determine the current tap dance state
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->interrupted) return TD_SINGLE_HOLD;
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) return TD_DOUBLE_TAP;
    else return TD_UNKNOWN;
}

// Initialize tap structure associated with example tap dance key
static td_tap_t usl_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void usl_finished(qk_tap_dance_state_t *state, void *user_data) {
    usl_tap_state.state = cur_dance(state);
    switch (usl_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code16(KC_UNDS);
            break;
        case TD_SINGLE_HOLD:
            layer_on(_LOWER);
            // update_tri_layer(_LOWER, _RAISE, _ADJUST);
            break;
        case TD_DOUBLE_TAP:
            // Check to see if the layer is already set
            if (layer_state_is(_LOWER)) {
                // If already set, then switch it off
                layer_off(_LOWER);
                #ifdef AUDIO_ENABLE
                  PLAY_SONG(tone_goodbye);
                #endif
            } else {
                // If not already set, then switch the layer on
                layer_on(_LOWER);
                #ifdef AUDIO_ENABLE
                  PLAY_SONG(layerswitch_song);
                #endif
            }
            break;
        default:
            break;
    }
}

void usl_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (usl_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(_LOWER);
        // update_tri_layer(_LOWER, _RAISE, _ADJUST);
    }
    usl_tap_state.state = TD_NONE;
}

// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [UNDS_LOWER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, usl_finished, usl_reset)
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(UNDS_LOWER):
            return 175;
        default:
            return TAPPING_TERM;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_select_word(keycode, record, SELWORD)) { return false; }
  if (!process_caps_word(keycode, record)) { return false; }

  const uint8_t mods = get_mods();
  const uint8_t oneshot_mods = get_oneshot_mods();

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case KC_CAPS:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        register_code(KC_CAPS);
      }
      return false;
      break;
    case GAMING:
      if (record->event.pressed) {
        layer_off(_RAISE);
        layer_off(_LOWER);
        layer_off(_ADJUST);
        layer_on(_GAMING);
        #ifdef AUDIO_ENABLE
          PLAY_SONG(layerswitch_song);
        #endif
      }
      return false;
      break;
    case EXT_GAMING:
      if (record->event.pressed) {
        layer_off(_GAMING);
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_goodbye);
        #endif
      }
      return false;
      break;
    case COLEMAK_VCP:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK_VCP);
      }
      return false;
      break;
    case BRACES:  // Types (), or {}, and puts cursor between braces.
      if (record->event.pressed) {
        clear_mods();  // Temporarily disable mods.
        clear_oneshot_mods();
        if ((mods | oneshot_mods) & MOD_MASK_SHIFT) {
          SEND_STRING("{}");
        } else {
          SEND_STRING("<>");
        }
        tap_code(KC_LEFT);  // Move cursor between braces.
        set_mods(mods);  // Restore mods.
      }
      return false;
    case BRACES2:  // Types [], or <>, and puts cursor between braces.
      if (record->event.pressed) {
        clear_mods();  // Temporarily disable mods.
        clear_oneshot_mods();
        if ((mods | oneshot_mods) & MOD_MASK_SHIFT) {
          SEND_STRING("()");
        } else {
          SEND_STRING("[]");
        }
        tap_code(KC_LEFT);  // Move cursor between braces.
        set_mods(mods);  // Restore mods.
      }
      return false;
    case ARROW:  // Arrow macro, types -> or =>.
      if (record->event.pressed) {
        if ((mods | oneshot_mods) & MOD_MASK_SHIFT) {  // Is shift held?
          del_mods(MOD_MASK_SHIFT);  // Temporarily delete shift.
          del_oneshot_mods(MOD_MASK_SHIFT);
          SEND_STRING("->");
          set_mods(mods);            // Restore mods.
        } else {
          SEND_STRING("=>");
        }
      }
      return false;
    case ALT_TAB: // super alt tab macro
      if (record->event.pressed) {
          if (!is_alt_tab_active) {
              is_alt_tab_active = true;
              register_code(KC_LALT);
          }
          register_code(KC_TAB);
      } else {
          unregister_code(KC_TAB);
      }
      return false;
      break;
  }
  return true;
}


enum combo_events {
  EM_EMAIL,
  EM_WORK_EMAIL,
  HTML_P,
  HTML_TITLE,
  HTML_DIV,
  HTML_HTML,
  HTML_HEAD,
  HTML_BODY,
  HTML_FOOTER,
  HTML_A_HREF,
  HTML_IMG,
  CSS_STYLE,
  HTML_GENERIC_TAG,
  CTLRGHT,
  CTLLEFT,
  COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH; // remove the COMBO_COUNT define and use this instead!

const uint16_t PROGMEM email_combo[] = {KC_E, KC_M, COMBO_END};
const uint16_t PROGMEM email_work_combo[] = {KC_E, KC_K, COMBO_END};
const uint16_t PROGMEM html_p_combo[] = {KC_P, KC_DOT, COMBO_END};
const uint16_t PROGMEM html_title_combo[] = {KC_T, KC_DOT, COMBO_END};
const uint16_t PROGMEM html_div_combo[] = {KC_D, KC_DOT, COMBO_END};
const uint16_t PROGMEM html_html_combo[] = {KC_Q, KC_DOT, COMBO_END};
const uint16_t PROGMEM html_head_combo[] = {KC_W, KC_DOT, COMBO_END};
const uint16_t PROGMEM html_body_combo[] = {KC_R, KC_DOT, COMBO_END};
const uint16_t PROGMEM html_footer_combo[] = {KC_X, KC_DOT, COMBO_END};
const uint16_t PROGMEM html_a_href_combo[] = {KC_A, KC_DOT, COMBO_END};
const uint16_t PROGMEM html_img_combo[] = {KC_F, KC_DOT, COMBO_END};
const uint16_t PROGMEM css_style_combo[] = {KC_S, KC_DOT, COMBO_END};
const uint16_t PROGMEM html_generic_tag_combo[] = {KC_G, KC_DOT, COMBO_END};
const uint16_t PROGMEM ctrrght_combo[] = {KC_RGHT, KC_DOWN, COMBO_END};
const uint16_t PROGMEM ctrleft_combo[] = {KC_LEFT, KC_DOWN, COMBO_END};
// const uint8_t combo_mods = get_mods();
// const uint8_t combo_oneshot_mods = get_oneshot_mods();

combo_t key_combos[] = {
  [EM_EMAIL] = COMBO_ACTION(email_combo),
  [EM_WORK_EMAIL] = COMBO_ACTION(email_work_combo),
  [HTML_P] = COMBO_ACTION(html_p_combo),
  [HTML_TITLE] = COMBO_ACTION(html_title_combo),
  [HTML_DIV] = COMBO_ACTION(html_div_combo),
  [HTML_HTML] = COMBO_ACTION(html_html_combo),
  [HTML_HEAD] = COMBO_ACTION(html_head_combo),
  [HTML_BODY] = COMBO_ACTION(html_body_combo),
  [HTML_FOOTER] = COMBO_ACTION(html_footer_combo),
  [HTML_A_HREF] = COMBO_ACTION(html_a_href_combo),
  [HTML_IMG] = COMBO_ACTION(html_img_combo),
  [CSS_STYLE] = COMBO_ACTION(css_style_combo),
  [HTML_GENERIC_TAG] = COMBO_ACTION(html_generic_tag_combo),
  [CTLRGHT] = COMBO_ACTION(ctrrght_combo),
  [CTLLEFT] = COMBO_ACTION(ctrleft_combo),
};
/* COMBO_ACTION(x) is same as COMBO(x, KC_NO) */

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case EM_EMAIL:
      if (pressed) {
        SEND_STRING("aricbouwers@outlook.com");
      }
      break;
    case EM_WORK_EMAIL:
      if (pressed) {
        SEND_STRING("acrossonbouwers@rjc.ca");
      }
      break;
    case HTML_DIV:
      if (pressed) {
        SEND_STRING("<div></div>");
        for (int i = 0; i < 6; i++) {
          tap_code16(KC_LEFT);
        }
      }
      break;
    case HTML_P:
      if (pressed) {
        SEND_STRING("<p></p>");
        for (int i = 0; i < 4; i++) {
          tap_code16(KC_LEFT);
        }
      }
      break;
    case HTML_TITLE:
      if (pressed) {
        SEND_STRING("<title></title>");
        for (int i = 0; i < 8; i++) {
          tap_code16(KC_LEFT);
        }
      }
      break;
      case CSS_STYLE:
      if (pressed) {
        SEND_STRING("<style></style>");
         for (int i = 0; i < 8; i++) {
          tap_code16(KC_LEFT);
        }
      }
      break;
    case HTML_HTML:
      if (pressed) {
        SEND_STRING("<html lang=\"en\"></html>");
        for (int i = 0; i < 7; i++) {
          tap_code16(KC_LEFT);
        }
      }
      break;
    case HTML_HEAD:
      if (pressed) {
        SEND_STRING("<head></head>");
        for (int i = 0; i < 7; i++) {
          tap_code16(KC_LEFT);
        }
      }
      break;
    case HTML_BODY:
      if (pressed) {
        SEND_STRING("<body></body>");
        for (int i = 0; i < 7; i++) {
          tap_code16(KC_LEFT);
        }
      }
      break;
    case HTML_FOOTER:
      if (pressed) {
        SEND_STRING("<footer></footer>");
        for (int i = 0; i < 9; i++) {
          tap_code16(KC_LEFT);
        }
      }
      break;
    case HTML_A_HREF:
      if (pressed) {
        SEND_STRING("<a href=\"link_goes_here\">name_of_link_goes_here</a>");
        tap_code16(KC_HOME);
        for (int i = 0; i < 10; i++) {
          tap_code16(KC_RGHT);
        }
      }
      break;
    case HTML_IMG:
      if (pressed) {
        SEND_STRING("<img src=\"image_source_or_link_goes_here\" alt=\"name_if_cant_load\" width=\"num_pixels\" height=\"num_pixels\">");
        tap_code16(KC_HOME);
        for (int i = 0; i < 11; i++) {
          tap_code16(KC_RGHT);
        }
      }
      break;
    case HTML_GENERIC_TAG:
      if (pressed) {
        SEND_STRING("<TAG></TAG>");
        tap_code16(KC_ESC);
        for (int i = 0; i < 9; i++) {
          tap_code16(KC_LEFT);
        }
        tap_code16(LCTL(KC_D));
        tap_code16(LCTL(KC_D));
        tap_code16(KC_BSPC);
      }
      break;
    case CTLLEFT:
      if (pressed) {
        tap_code16(C(KC_LEFT));
      }
      break;
    case CTLRGHT:
      if (pressed) {
        tap_code16(C(KC_RGHT));
      }
      break;
  }
}
