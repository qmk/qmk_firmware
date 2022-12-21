/* Copyright 2022 Clickety Split Ltd.
 *                https://clicketysplit.ca
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
#include <stdio.h>

// #include "ps2_mouse.h"
// #include "mousekey.h"

#include "features/select_word.h"
#include "features/adaptive_keys.h"
#include "features/layer_lock.h"

//#include "features/caps_word.h"
//#include "features/autocorrection.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skiep them
// entirely and just use numbers.
enum layer_names {
    _COLEMAKDH,
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST
};

#define XXXXX KC_NO
#define _____ KC_TRNS
#define DESKTR LGUI(LCTL(KC_RGHT))  // move one virtual desktop to the right
#define DESKTL LGUI(LCTL(KC_LEFT))  // move one virtual desktop to the left
#define LOW_OSS LT(_LOWER, KC_F24)   // lower on hold, One Shot Shift on tap
#define L_RAISE MO(_RAISE)
#define MTLCTL_F9 MT(MOD_LCTL, KC_9)
#define MTLSFT_F10 MT(MOD_LSFT, KC_F10)
#define MTLALT_F11 MT(MOD_LALT, KC_F11)
#define ALT_DEL MT(MOD_LALT, KC_DEL)
#define MTLGUI_Z MT(MOD_LGUI, KC_Z)
#define MTALT_APP MT(MOD_LALT, KC_APP)
#define MTLALT_PL MT(MOD_LALT, KC_MPLY)
#define MTLALT_NXT MT(MOD_LALT, KC_MNXT)
#define MTCTL_ENT MT(MOD_LCTL, KC_ENT)
#define MTRSFTBSLS MT(MOD_RSFT, KC_BSLS)
#define MTRCTLQUO MT(MOD_RCTL, KC_QUOT)
#define HYPERESC MT(MOD_LCTL | MOD_LGUI | MOD_LALT | MOD_LSFT, KC_ESC) // Hyper on hold, Esc on tap
#define MTTAB MT(MOD_LCTL | MOD_LGUI | MOD_LALT, KC_TAB) // MEH on hold, Tab on tap
#define FN_A LT(_ADJUST, KC_A)
#define MTPLAY MT(MOD_RALT, KC_MPLY)
#define KC_COPY LCTL(KC_C)
#define KC_CUT LCTL(KC_X)
#define KC_PASTE LCTL(KC_V)
#define KC_WINPASTE LGUI(KC_V)
#define KC_PTXT LCTL(LSFT(KC_V))
#define KC_UNDO LCTL(KC_Z)
#define KC_REDO LCTL(KC_Y)
#define PTOYSMUTE C(G(A(KC_BSPC)))
#define SUPERHUMAN A(KC_S)
#define BWSRLEFT A(KC_LEFT)
#define BWSRRHGT A(KC_RGHT)
#define ALT_TAB LALT(KC_TAB)
#define TIDYTABS LCTL(LALT(LGUI(KC_R)))


enum planck_keycodes {
  COLEMAKDH = SAFE_RANGE,
  QWERTY,
  LOWER,
  RAISE,
  ADJUST,
  NUMPAD,
  GAMING,
  EXT_NUM,
  SELWORD,
  BRACES,
  BRACES2,
  ARROW,
  CTRL_TAB,
  LLOCK,
  SELWLEFT,
  SELWRIGHT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* MIT Layout (COLEMAKH-DH)
 * .------------F1---------------------------.                                      .--------------------------F8-------------.
 * | HYPER|  F2  |  F9  |  F10 |  F11 |  F12 |                                      |  F3  |  F4  |  F5  |  F6  |  F7  |Select|
 * |------+------+------+------+------+------|                                      |------+------+------+------+------+------|
 * |ADJ,ESC| Q   |  W   |  F   |  P   |  B   |                                      |  J   |  L   |  U   |  Y   |  ;   | BSPC |
 * |------+------+------+------+------+------|                                      |------+------+------+------+------+------|
 * |HYPERESC| A  |  R   |  S   |  T   |  G   |-------.                      .-------|  M   |  N   |  E   |  I   |  O   |CTRL,'|
 * |------+------+------+------+------+------|Alt-Tab|                      | Ctrl  |------+------+------+------+------+------|
 * | SHIFT| WIN_Z|  X   |  C   |  D   |  V   |       |-->Play/Pause         | Tab   |  K   |  H   |  ,   |  .   |  /   |SFT,\ |
 * .-----------------------------------------|-------|   on Button Press    |-------|-----------------------------------------'
 *                      | ALT | CTRL |  LOW  /      /                        \ LALT \       |     |Expand Selection R/L|  //Hdr On/off On Press
 *                      | APP | ENTER| OSSft/ SPACE/                          \DELETE\ SPACE|RAISE| DIAL2|--> Right Scroll whole word
 *                      `-------------------------'                            '-------------------------'
 */
  [_COLEMAKDH] = LAYOUT(
  KC_HYPR,  KC_F2,    KC_F9,  KC_F10,    KC_F11,    KC_F12,                           KC_F3,   KC_F4,   KC_F5,   KC_F6,  KC_F7,   KC_SLCT,
  HYPERESC, KC_Q,     KC_W,   KC_F,      KC_P,      KC_B,                             KC_J,    KC_L,    KC_U,    KC_Y,   KC_SCLN, KC_BSPC,
  MTTAB,    FN_A,     KC_R,   KC_S,      KC_T,      KC_G,                             KC_M,    KC_N,    KC_E,    KC_I,   KC_O,    MTRCTLQUO,
  KC_LSFT,  MTLGUI_Z, KC_X,   KC_C,      KC_D,      KC_V,    KC_MPLY,       CTRL_TAB, KC_K,    KC_H,    KC_COMM, KC_DOT, KC_SLSH, MTRSFTBSLS,
                              MTALT_APP, MTCTL_ENT, LOW_OSS, KC_SPC,        ALT_DEL,  KC_SPC,  L_RAISE, PTOYSMUTE //Mute Mic
),

/* MIT Layout (QWERTY)
 * .------------F1---------------------------.                                      .--------------------------F8-------------.
 * | HYPER|  F2  |  F9  |  F10 |  F11 |  F12 |                                      |  F3  |  F4  |  F5  |  F6  |  F7  |Select|
 * |------+------+------+------+------+------|                                      |------+------+------+------+------+------|
 * |ADJ,ESC| Q   |  W   |  E   |  R   |  T   |                                      |  Y   |  U   |  I   |  O   |  P   | BSPC |
 * |------+------+------+------+------+------|                                      |------+------+------+------+------+------|
 * |HYPERESC| A  |  S   |  D   |  F   |  G   |-------.                      .-------|  H   |  J   |  K   |  L   |  ;   |CTRL,'|
 * |------+------+------+------+------+------|Alt-Tab|                      | Ctrl  |------+------+------+------+------+------|
 * | SHIFT| WIN_Z|  X   |  C   |  V   |  B   |       |-->Play/Pause         | Tab   |  N   |  M   |  ,   |  .   |  /   |SFT,\ |
 * .-----------------------------------------|-------|   on Button Press    |-------|-----------------------------------------'
 *                      | ALT | CTRL |  LOW  /      /                        \ LALT \       |     |Expand Selection R/L|  //Hdr On/off On Press
 *                      | APP | ENTER| OSSft/ SPACE/                          \DELETE\ SPACE|RAISE| DIAL2|--> Right Scroll Whole word
 *                      `-------------------------'                            '-------------------------'
 */
  [_QWERTY] = LAYOUT(
  KC_HYPR,  KC_F2,    KC_F9,  KC_F10,    KC_F11,    KC_F12,                           KC_F3,   KC_F4,   KC_F5,   KC_F6,  KC_F7,   KC_SLCT,
  HYPERESC, KC_Q,     KC_W,   KC_E,      KC_R,      KC_T,                             KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,    KC_BSPC,
  MTTAB,    FN_A,     KC_S,   KC_D,      KC_F,      KC_G,                             KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN, MTRCTLQUO,
  KC_LSFT,  MTLGUI_Z, KC_X,   KC_C,      KC_V,      KC_B,    KC_MPLY,       CTRL_TAB, KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, MTRSFTBSLS,
                              MTALT_APP, MTCTL_ENT, LOW_OSS, KC_SPC,        ALT_DEL,  KC_SPC,  L_RAISE, PTOYSMUTE
),

/* MIT Layout (LOWER)
 * .-----------------------------------------.                                      .-----------------------------------------.
 * | HYPER|  F1  |  F2  |  F3  |  F4  |  F5  |                                      |  F6  |  F7  |  F8  |  F9  | F10  |Delete|
 * |------+------+------+------+------+------|                                      |------+------+------+------+------+------|
*  |  `   |  ~   |  <   |  >   |  ]   |  ?   |                                      |   ^  |   7  |   8  |   9  |   :  | Bsp  |
 * |------+------+------+------+------+------|                                      |------+------+------+------+------+------|
 * |S(TAB)|  !   |  %   |  (   |  )   |  =   |-------.                      .-------|   =  |   4  |   5  |   6  |   -  |  +   |
 * |------+------+------+------+------+------|Volume |                      | Layer |------+------+------+------+------+------|
 * |SHIFT |  #   |  $   |  {   |  }   |  &   | DIAL1 |--> Reset Audio       | Lock  |   @  |   1  |   2  |   3  |   /  |  *   |
 * .-----------------------------------------|-------|    Recording Device  |-------|-----------------------------------------'
 *                      | ALT | CTRL |  LOW  /      /     on Button Press    \       \      |     |Expand Selection|
 *                      | APP | ENTER| OSSft/ SPACE/                          \ Space \  0  |  .  | DIAL2|--> does a configurable keyboard shortcut: Hyper(J)
 *                      `-------------------------'                            '-------------------------'
 */
  [_LOWER] = LAYOUT(
  KC_HYPR,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,  KC_F8, KC_F9, KC_F10,  KC_DEL,
  KC_GRV,    KC_TILD, KC_LABK, KC_RABK, KC_RBRC, KC_QUES,                            KC_CIRC, KC_7,   KC_8,  KC_9,  KC_COLN, KC_BSPC,
  S(KC_TAB), KC_EXLM, KC_PERC, KC_LPRN, KC_RPRN, KC_EQL,                             KC_EQL,  KC_4,   KC_5,  KC_6,  KC_PMNS, KC_PPLS,
  KC_LSFT,   KC_HASH, KC_DLR,  KC_LCBR, KC_RCBR, KC_AMPR, LCTL(KC_0),        LLOCK,  KC_AT,   KC_1,   KC_2,  KC_3,  KC_PSLS, KC_PAST,
                               _____,   _____,   _____,   _____,             KC_SPC, KC_0,    KC_DOT, A(S(KC_J)) //
),

/* MIT Layout (RAISE)
 * .-----------------------------------------.                                      .-----------------------------------------.
 * | HYPER|      |      |      |      |DEBUG |                               track  |MBtn 2|      |NumLck|      |      |QWERTY|
 * |------+------+------+------+------+------|                               point  |------+------+------+------+------+------|
 * | Menu | Mb3  | Mb2  | MsUp | Mb1  | Mute |                               mouse  |      |      | MbMid|      |   :  | Bksp |
 * |------+------+------+------+------+------|                                      |------+------+------+------+------+------|
 * |      |      | MsLft| MDown|Mright| Vol+ |-------.                      .-------|ARROW | MbLft|SELWORD|MbRgt|      |   "  |
 * |------+------+------+------+------+------|Undo/Redo|                    | Layer |------+------+------+------+------+------|
 * |      | MWLft| MWUp | NWDn |NWRght| Vol- | DIAL1 |-->pins current       | Lock  |  <>  |  []  |   [  |   ]  |   !  |   |  |
 * .-----------------------------------------|-------|   window to all      |-------|-----------------------------------------'
 *                      | ALT | CTRL |  LOW  /      /    virtual destktops on\ Mouse\ Mouse |******|Search|
 *                      | APP | ENTER| OSSft/ SPACE/     Button Press         \ Btn 1\ Btn 3|******| DIAL2|--> sends CTRL(KC_F)
 *                      `-------------------------'                            '--------------------------'    on Button Press
 */
  [_RAISE] = LAYOUT(
  KC_HYPR, XXXXX, XXXXX,   XXXXX,   XXXXX,   XXXXX,                                    KC_BTN2, XXXXX,   KC_NUM,  XXXXX,   XXXXX,   TG(_QWERTY),
  KC_APP, KC_BTN3, KC_BTN2, KC_MS_U, KC_BTN1, KC_MUTE,                                  _____,   LLOCK,   KC_BTN3, _____,   KC_COLN, KC_BSPC,
  _____, _____,  KC_MS_L, KC_MS_D, KC_MS_R, KC_VOLU,                                  ARROW,   KC_BTN1, SELWORD, KC_BTN2, _____,   KC_DQUO,
  _____, KC_WH_L, KC_WH_U, KC_WH_D, KC_WH_R, KC_VOLD, C(A(KC_P)),             LLOCK,   BRACES,  BRACES2, KC_LBRC, KC_RBRC, KC_EXLM, KC_PIPE,
                             _____, _____, _____, _____,                      KC_BTN1, KC_BTN3, _____,   LCTL(KC_F) // search on page (ctrl f)
),

/* MIT Layout (ADJUST)
 * .-----------------------------------------.                                      .-----------------------------------------.
 * | HYPER|      |      |      |      |Calc  |                                      |TabUp | Back |C+A_Up|Frward|      |SclLok|
 * |------+------+------+------+------+------|                                      |------+------+------+------+------+------|
 * |      |  F5  |      |      |      |MyComp|                                      |TabDn | Home |  Up  |  End | PAUSE|Delete|
 * |------+------+------+------+------+------|                                      |------+------+------+------+------+------|
 * |      |******| Ctrl | Shift| Alt  |      |--------.                     .-------|SWLeft| Left | Down | Right|SWRigt|CAPSLK|
 * |------+------+------+------+------+------| Virtual|                     | Layer |------+------+------+------+------+------|
 * |      |      |      |      |      |      |Desktop |-->  Next Song       | Lock  | Back |PageUp|C+A_Dn|PageDn|Forwrd|INSERT|
 * .-----------------------------------------|--------|                     |-------|-----------------------------------------'
 *                      | ALT | CTRL |  Alt  / Next  /                       \       \       |      |Volume|
 *                      | APP | ENTER| Tab  /TidyTab/                         \       \      |      | DIAL2|--> Toggle HDR
 *                      `--------------------------'                           '---------------------------'    on Button Press
 */
  [_ADJUST] = LAYOUT(
  KC_HYPR, XXXXX, XXXXX,   XXXXX,   XXXXX,   KC_CALC,                           C(KC_PGUP), BWSRLEFT, LCA(KC_UP),   BWSRRHGT, XXXXX,     KC_SCRL,
  _____,   KC_F5, _____,   _____,   _____,   KC_MYCM,                           C(KC_PGDN), KC_HOME,  KC_UP,        KC_END,   KC_PAUSE,     KC_DEL,
  _____,   _____, KC_LCTL, KC_LSFT, KC_LALT, _____,                             SELWLEFT,   KC_LEFT,  KC_DOWN,      KC_RGHT,  SELWRIGHT, KC_CAPS,
  _____,   _____, _____,   _____,   _____,   _____, KC_MNXT,             _____, BWSRLEFT,   KC_PGUP,  LCA(KC_DOWN), KC_PGDN,  BWSRRHGT,  KC_INS,
                           _____,   _____, ALT_TAB, TIDYTABS,            _____, _____,  _____, G(A(KC_B))
)
};

static fast_timer_t last_encoding_time = 0;
static const fast_timer_t ENCODER_DEBOUNCE = 50;

// layer_state_t layer_state_set_user(layer_state_t state) {

//   if (is_ctrl_tab_active) {
//         unregister_code(KC_LCTL);
//         is_ctrl_tab_active = false;
//     }
//     return state;
// }

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
  if (TIMER_DIFF_FAST(timer_read_fast(), last_encoding_time) >= ENCODER_DEBOUNCE) {
        last_encoding_time = timer_read_fast();
    }
    else {
        return false;
    }
    // then goes the rest of your rotary encoder handling code.
    if (index == 0) {
        switch (biton32(layer_state)) {
            case _LOWER:
            // Volume Up/Down
                if (!clockwise) {
                    tap_code16(KC_VOLU);
                    tap_code16(KC_VOLU);
                    tap_code16(KC_VOLU);
                    tap_code16(KC_VOLU);
                } else {
                    tap_code16(KC_VOLD);
                    tap_code16(KC_VOLD);
                    tap_code16(KC_VOLD);
                    tap_code16(KC_VOLD);
                }
                break;
                // Next song on button press
            case _RAISE:
            // Undo/ Redo Revision History
              if (!clockwise) {
                tap_code16(LCTL(KC_Y));
                } else {
                  tap_code16(LCTL(KC_Z));
                  }
              // Save As on button press
              break;
            case _ADJUST:
            // Forward/Back Windows Virtual Desktops
                if (!clockwise) {
                  tap_code16(G(C(KC_RGHT)));
                  } else {
                    tap_code16(G(C(KC_LEFT)));
                    }
                // Play/pause on button press
                break;
                //Pins current window to all desktops C(A(KC_P))
            // case _ADJUST:
            //     // ALT Tab through open windows
            //   if (!clockwise) {
            //       tabtimer = timer_read();
            //       if(!tabbing) {
            //         register_code(KC_LGUI);
            //         register_code(KC_TAB);
            //         unregister_code(KC_LGUI);
            //         unregister_code(KC_TAB);
            //         tabbing = true;
            //       }
            //       tap_code(KC_RGHT);
            //   } else {
            //       tabtimer = timer_read();
            //       if(!tabbing) {
            //           register_code(KC_LGUI);
            //           register_code(KC_TAB);
            //           unregister_code(KC_LGUI);
            //           unregister_code(KC_TAB);
            //           tabbing = true;
            //       }
            //       tap_code(KC_LEFT);
            //     }
            //     break;
            //     //Pins current window to all desktops C(A(KC_P))
            default:
              // ALT Tab through open windows
              if (!clockwise) {
                  tabtimer = timer_read();
                  if(!tabbing) {
                    register_code(KC_LALT);
                    tabbing = true;
                  }
                  tap_code(KC_TAB);
              } else {
                  tabtimer = timer_read();
                  if(!tabbing) {
                      register_code(KC_LALT);
                      tabbing = true;
                  }
                  register_code(KC_LSFT);
                  tap_code(KC_TAB);
                  unregister_code(KC_LSFT);
                }
                break;
        }

    } else if (index == 1) {
        switch (biton32(layer_state)) {
            case _LOWER:
                // Expand selection in VSCode
                if (!clockwise) {
                    tap_code16(LALT(LSFT(KC_LEFT)));
                } else {
                    tap_code16(LALT(LSFT(KC_RGHT)));
                }
                break;
                // Change Audio Recording Source on button press (Alt Shift J)
            case _RAISE:
                // Scrolling Through Search Results (ctrl(f), aka F3)
                if (clockwise) {
                     tap_code(KC_F3);
                } else {
                    tap_code16(S(KC_F3));
                }
                // on button press sends CTRL(KC_F)
                break;
            case _ADJUST:
                // Select Whole Word
                if (!clockwise) {
                    tap_code16(LCTL(LSFT(KC_LEFT)));
                } else {
                    tap_code16(LCTL(LSFT(KC_RGHT)));
                }
                break;
                // Next song on button press
            default:
                // Mouse Wheel Right/Left
                if (!clockwise) {
                    tap_code16(KC_WH_U);
                } else {
                    tap_code16(KC_WH_D);
                }
                break;
                // mute powertoys
        }
    }
    return false;
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_layer_lock(keycode, record, LLOCK)) { return false; }
  if (!process_select_word(keycode, record, SELWORD)) { return false; }
  if (!process_adaptive_key(keycode, record)) { return false; }
 // if (!process_caps_word(keycode, record)) { return false; }
  //if (!process_autocorrection(keycode, record)) { return false; }

  const uint8_t mods = get_mods();
  const uint8_t oneshot_mods = get_oneshot_mods();

  switch (keycode) {
      case BRACES:  // Types (), or {}, and puts cursor between braces.
        if (record->event.pressed) {
            clear_mods();  // Temporarily disable mods.
            clear_oneshot_mods();
            if ((mods | oneshot_mods) & MOD_MASK_SHIFT) {
            SEND_STRING("()");
            } else {
            SEND_STRING("<>");
            }
            tap_code(KC_LEFT);  // Move cursor between braces.
            set_mods(mods);  // Restore mods.
        }
        return false;
        break;
      case BRACES2:  // Types [], or <>, and puts cursor between braces.
        if (record->event.pressed) {
            clear_mods();  // Temporarily disable mods.
            clear_oneshot_mods();
            if ((mods | oneshot_mods) & MOD_MASK_SHIFT) {
            SEND_STRING("{}");
            } else {
            SEND_STRING("[]");
            }
            tap_code(KC_LEFT);  // Move cursor between braces.
            set_mods(mods);  // Restore mods.
        }
        return false;
        break;
      case ARROW:  // Arrow macro, types -> or =>.
        if (record->event.pressed) {
            if ((mods | oneshot_mods) & MOD_MASK_SHIFT) {  // Is shift held?
            del_mods(MOD_MASK_SHIFT);  // Temporarily delete shift.
            del_oneshot_mods(MOD_MASK_SHIFT);
            SEND_STRING("const yourFuncVariable = (x,y) => x + y.method;");
            for (int counter = 0; counter <= 24; counter++){
              tap_code(KC_LEFT);
            }
            tap_code16(LCTL(LSFT(KC_LEFT)));
            set_mods(mods);  // Restore mods.
            } else {
              SEND_STRING("() => ;");
              tap_code(KC_LEFT);
              set_mods(mods); // Restore mods.
            }
        }
        return false;
        break;
      case CTRL_TAB:
        if (record->event.pressed) {
          ctrl_tabtimer = timer_read_fast();
          if(!ctrl_tabbing) {
          register_code(KC_LCTL);
            ctrl_tabbing = true;
          }
          tap_code(KC_TAB);
        }
        return false;
        break;
      case LT(_LOWER, KC_F24):
        if (record->tap.count > 0) {
        if (record->event.pressed) {
            set_oneshot_mods(MOD_LSFT);
        }
        return false;
        }
        break;
      case SELWLEFT:
        if (record->event.pressed){
          tap_code16(LCTL(LSFT(KC_LEFT)));
        }
        break;
        case SELWRIGHT:
        if (record->event.pressed){
          tap_code16(LCTL(LSFT(KC_RGHT)));
        }
        break;
  }
  return true;
};

enum combo_events {
  EM_EMAIL,
  EM_WORK_EMAIL,
  HOME_ADDRESS,
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
  UNDO,
  REDO,
  CUT,
  COPY,
  PASTE,
  PASTECLIPBOARD,
  PASTETEXT,
  SELECTALL,
  QUESTIONMARK,
  EXCLAMATIONMARK,
  DQUOTE,
  UNDERSCORE,
  DASH,
  TWODQUOTE,
  LOWERTOGGLE,
  SLEEP,
  RESETKEY,
  NUMLOCKC,
  F1COMBO,
  F8COMBO,
  CAPSWORD,
  COMBO_LENGTH
};


uint16_t COMBO_LEN = COMBO_LENGTH; // remove the COMBO_COUNT define and use this instead

const uint16_t PROGMEM email_combo[]                = {KC_E, KC_M, COMBO_END};
const uint16_t PROGMEM email_work_combo[]           = {KC_E, KC_K, COMBO_END};
const uint16_t PROGMEM home_address_combo[]         = {KC_E, KC_J, COMBO_END};
const uint16_t PROGMEM html_p_combo[]               = {KC_P, KC_DOT, COMBO_END};
const uint16_t PROGMEM html_title_combo[]           = {KC_T, KC_DOT, COMBO_END};
const uint16_t PROGMEM html_div_combo[]             = {KC_D, KC_DOT, COMBO_END};
const uint16_t PROGMEM html_html_combo[]            = {KC_Q, KC_DOT, COMBO_END};
const uint16_t PROGMEM html_head_combo[]            = {KC_W, KC_DOT, COMBO_END};
const uint16_t PROGMEM html_body_combo[]            = {KC_R, KC_DOT, COMBO_END};
const uint16_t PROGMEM html_footer_combo[]          = {KC_X, KC_DOT, COMBO_END};
const uint16_t PROGMEM html_a_href_combo[]          = {KC_A, KC_DOT, COMBO_END};
const uint16_t PROGMEM html_img_combo[]             = {KC_F, KC_DOT, COMBO_END};
const uint16_t PROGMEM css_style_combo[]            = {KC_S, KC_DOT, COMBO_END};
const uint16_t PROGMEM html_generic_tag_combo[]     = {KC_G, KC_DOT, COMBO_END};
const uint16_t PROGMEM undo_combo[]                 = {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM redo_combo[]                 = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM cut_combo[]                  = {MTLGUI_Z, KC_X, COMBO_END};
const uint16_t PROGMEM copy_combo[]                 = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM paste_combo[]                = {KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM pasteclip_combo[]            = {KC_X, KC_D, COMBO_END};
const uint16_t PROGMEM pastetxt_combo[]             = {KC_X, KC_V, COMBO_END};
const uint16_t PROGMEM selectall_combo[]            = {MTLGUI_Z, KC_D, COMBO_END};
const uint16_t PROGMEM questionmark_combo[]         = {KC_DOT, KC_SLSH, COMBO_END};
const uint16_t PROGMEM exclamationmark_combo[]      = {KC_SLSH, MTRSFTBSLS, COMBO_END};
const uint16_t PROGMEM dquote_combo[]               = {KC_O, MTRCTLQUO, COMBO_END};
const uint16_t PROGMEM underscore_combo[]           = {KC_COMMA, KC_DOT, COMBO_END};
const uint16_t PROGMEM dash_combo[]                 = {KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM twodquote_combo[]            = {KC_H, KC_COMMA, COMBO_END};
const uint16_t PROGMEM lowertoggle_combo[]          = {LT(_LOWER, KC_F24), MTCTL_ENT, COMBO_END};
const uint16_t PROGMEM sleep_combo[]                = {KC_F2, KC_F9, KC_F10, KC_F11, COMBO_END};
const uint16_t PROGMEM reset_combo[]                = {KC_BSPC, MTRCTLQUO, MTRSFTBSLS, COMBO_END};
const uint16_t PROGMEM numlock_combo[]              = {KC_L, KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM f1_combo[]                   = {KC_F2, KC_F9, COMBO_END};
const uint16_t PROGMEM f8_combo[]                   = {KC_F6, KC_F7, COMBO_END};
const uint16_t PROGMEM capsword_combo[]             = {KC_LSFT, MTRSFTBSLS, COMBO_END};


// const uint8_t combo_mods = get_mods();r
// const uint8_t combo_oneshot_mods = get_oneshot_mods();

combo_t key_combos[] = {
  [EM_EMAIL] = COMBO_ACTION(email_combo),
  [EM_WORK_EMAIL] = COMBO_ACTION(email_work_combo),
  [HOME_ADDRESS] = COMBO_ACTION(home_address_combo),
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
  [UNDO] = COMBO_ACTION(undo_combo),
  [REDO] = COMBO_ACTION(redo_combo),
  [CUT] = COMBO_ACTION(cut_combo),
  [COPY] = COMBO_ACTION(copy_combo),
  [PASTE] = COMBO_ACTION(paste_combo),
  [PASTECLIPBOARD] = COMBO_ACTION(pasteclip_combo),
  [PASTETEXT] = COMBO_ACTION(pastetxt_combo),
  [SELECTALL] = COMBO_ACTION(selectall_combo),
  [QUESTIONMARK] = COMBO_ACTION(questionmark_combo),
  [EXCLAMATIONMARK] = COMBO_ACTION(exclamationmark_combo),
  [DQUOTE] = COMBO_ACTION(dquote_combo),
  [UNDERSCORE] = COMBO_ACTION(underscore_combo),
  [DASH] = COMBO_ACTION(dash_combo),
  [TWODQUOTE] = COMBO_ACTION(twodquote_combo),
  [LOWERTOGGLE] = COMBO_ACTION(lowertoggle_combo),
  [SLEEP] = COMBO_ACTION(sleep_combo),
  [RESETKEY] = COMBO_ACTION(reset_combo),
  [NUMLOCKC] = COMBO_ACTION(numlock_combo),
  [F1COMBO] = COMBO_ACTION(f1_combo),
  [F8COMBO] = COMBO_ACTION(f8_combo),
  [CAPSWORD] = COMBO_ACTION(capsword_combo)
};
/* COMBO_ACTION(x) is same as COMBO(x, XXXXX) */

void process_combo_event(uint16_t combo_index, bool pressed) {
  const uint8_t mods = get_mods();
  const uint8_t oneshot_mods = get_oneshot_mods();

  switch(combo_index) {
    case EM_EMAIL:
      if (pressed) {
        SEND_STRING("aricbouwers@outlook.com");
      }
      break;
    case EM_WORK_EMAIL:
      if (pressed) {
        SEND_STRING("acbouwers@freedomsadvocate.ca");
      }
      break;
    case HOME_ADDRESS:
      if (pressed) {
        SEND_STRING("111 Highview Gate SE");
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
    case UNDO:
      if (pressed) {
        tap_code16(C(KC_Z));
      }
      break;
    case REDO:
      if (pressed) {
        tap_code16(C(KC_Y));
      }
      break;
    case CUT:
      if (pressed) {
        tap_code16(C(KC_X));
      }
      break;
    case COPY:
      if (pressed) {
        tap_code16(C(KC_C));
      }
      break;
    case PASTE:
      if (pressed) {
        tap_code16(C(KC_V));
      }
      break;
    case PASTECLIPBOARD:
      if (pressed) {
        tap_code16(LWIN(KC_V));
      }
      break;
    case PASTETEXT:
      if (pressed) {
        tap_code16(C(S(KC_V)));
      }
      break;
    case SELECTALL:
      if (pressed) {
        tap_code16(C(KC_A));
      }
      break;
    case QUESTIONMARK:
      if (pressed) {
        tap_code16(KC_QUES);
      }
      break;
    case EXCLAMATIONMARK:
      if (pressed) {
        tap_code16(KC_EXLM);
      }
      break;
    case DQUOTE:
      if (pressed) {
        tap_code16(KC_DQUO);
      }
      break;
    case UNDERSCORE:
      if (pressed) {
        tap_code16(KC_UNDS);
      }
      break;
    case DASH:
      if (pressed) {
        tap_code16(KC_PMNS);
      }
      break;
    case TWODQUOTE:
      if (pressed) {
        clear_mods();  // Temporarily disable mods.
        clear_oneshot_mods();
        if ((mods | oneshot_mods) & MOD_MASK_SHIFT) {
          SEND_STRING("''");
        } else {
          SEND_STRING("\"\"");
        }
        tap_code(KC_LEFT);  // Move cursor between braces.
        set_mods(mods);  // Restore mods.
        }
        break;
    case LOWERTOGGLE:
      if (pressed) {
        layer_invert(_LOWER);
        if(IS_LAYER_ON(_LOWER)){
          #ifdef AUDIO_ENABLE
              PLAY_SONG(tone_startup);
          #endif
        }
        if(IS_LAYER_OFF(_LOWER)){
          #ifdef AUDIO_ENABLE
              PLAY_SONG(tone_goodbye);
          #endif
        }
      }
      break;
    case SLEEP:
      if (pressed) {
        tap_code16(KC_SLEP);
      }
      break;
    case RESETKEY:
      if (pressed) {
        reset_keyboard();
      }
      break;
    case NUMLOCKC:
      if (pressed) {
        tap_code16(KC_NUM);
      }
      break;
    case F1COMBO:
      if (pressed) {
        tap_code16(KC_F1);
      }
      break;
    case F8COMBO:
      if (pressed) {
        tap_code16(KC_F8);
      }
      break;
    case CAPSWORD:
      caps_word_on();
      break;
    }
};
