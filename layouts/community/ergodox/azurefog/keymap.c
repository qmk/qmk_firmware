#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"
//#include "keymap_german.h"
//#include "keymap_nordic.h"
//#include "rgb_matrix.h"


enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  RGB_SLD,

};


enum {
  TD_QUOT_SEMI = 0,
  TD_PGUP_HOME = 1,
  TD_PGDN_END = 2,
  TD_LEFT_CLEFT = 3,
  TD_RIGHT_CRIGHT = 4,
  TD_BKSPC = 5,
  TD_DEL_INS = 6
};

int i,j;

uint8_t row_def[5][13] = {
{0xFF, 0x00, 0x00, 0, 1, 2, 3, 4, 24, 25, 26, 27, 28},
{0xFF, 0x80, 0x00, 5, 6, 7, 8, 9, 29, 30, 31, 32, 33},
{0xFF, 0xFF, 0x00, 10, 11, 12, 13, 14, 34, 35, 36, 37, 38},
{0x00, 0xFF, 0x00, 15, 16, 17, 18, 19, 39, 40, 41, 42, 43},
{0x00, 0xFF, 0xFF, 20, 21, 22, 23, 44, 45, 46, 47, 47, 47}, //god forgive me for padding my array
};

void matrix_init_user() {
  rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
  rgb_matrix_set_color_all(0x00, 0xFF, 0xFF);
}

LEADER_EXTERNS();
void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();
    SEQ_ONE_KEY(KC_U) {
      SEND_STRING("");
    }
    SEQ_ONE_KEY(KC_2) {
      SEND_STRING(""SS_TAP(X_ENTER));
    }
    SEQ_ONE_KEY(KC_1) {
      SEND_STRING(""SS_TAP(X_ENTER));
    }
    SEQ_ONE_KEY(KC_5) {
      SEND_STRING(""SS_TAP(X_ENTER));
    }
    SEQ_ONE_KEY(KC_0) {
      SEND_STRING("make ergodox_ez:azurefog"SS_TAP(X_ENTER));
    }
    SEQ_ONE_KEY(KC_A) {
      SEND_STRING("azurefog@gmail.com"SS_TAP(X_ENTER));
    }
    SEQ_ONE_KEY(KC_R) {
      SEND_STRING(SS_LGUI("r")"https://www.reddit.com"SS_TAP(X_ENTER));
    }
    SEQ_ONE_KEY(KC_N) {
      SEND_STRING(SS_LCTRL(SS_LGUI(SS_TAP(X_RIGHT))));
    }
    SEQ_ONE_KEY(KC_B) {
      SEND_STRING(SS_LCTRL(SS_LGUI(SS_TAP(X_LEFT))));
    }
    SEQ_ONE_KEY(KC_M) {
      SEND_STRING(SS_LCTRL(SS_LGUI(SS_TAP(X_D))));
    }
    SEQ_ONE_KEY(KC_COMMA) {
      SEND_STRING(SS_LCTRL(SS_LGUI(SS_TAP(X_F4))));
    }
    SEQ_ONE_KEY(KC_C) {
      SEND_STRING(SS_LGUI("r")"cmd"SS_TAP(X_ENTER));
    }
  }
}

void leader_start(void) {
  ergodox_led_all_on();
}

void leader_end(void) {
  ergodox_led_all_off();
}



void del_dance (qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 0 ... 2:
      register_code(KC_DEL);
      unregister_code(KC_DEL);
      break;
    case 3:
      register_code(KC_INS);
      unregister_code(KC_INS);
      break;
  }
}

void bs_dance (qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 0 ... 1:
      tap_code(KC_BSPACE);
      break;
    case 2:
      register_code(KC_LSHIFT);
      tap_code(KC_HOME);
      unregister_code(KC_LSHIFT);
      tap_code(KC_DEL);
      break;
    case 3:
      register_code(KC_LSHIFT);
      register_code(KC_LCTRL);
      tap_code(KC_HOME);
      unregister_code(KC_LCTRL);
      unregister_code(KC_LSHIFT);
      tap_code(KC_DEL);
      break;
    case 4:
      register_code(KC_LSHIFT);
      tap_code(KC_END);

      unregister_code(KC_LSHIFT);
      tap_code(KC_DEL);
      break;
    case 5:
      register_code(KC_LSHIFT);
      register_code(KC_LCTRL);
      tap_code(KC_END);
      unregister_code(KC_LCTRL);
      unregister_code(KC_LSHIFT);
      tap_code(KC_DEL);
      break;
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_QUOT_SEMI]  = ACTION_TAP_DANCE_DOUBLE(KC_QUOTE, KC_SCOLON),
  [TD_PGUP_HOME]  = ACTION_TAP_DANCE_DOUBLE(KC_PGUP, LCTL(KC_HOME)),
  [TD_PGDN_END]  = ACTION_TAP_DANCE_DOUBLE(KC_PGDN, LCTL(KC_END)),
  [TD_LEFT_CLEFT]  = ACTION_TAP_DANCE_DOUBLE(KC_LEFT, LCTL(KC_LEFT)),
  [TD_RIGHT_CRIGHT]  = ACTION_TAP_DANCE_DOUBLE(KC_RIGHT, LCTL(KC_RIGHT)),
  [TD_BKSPC] = ACTION_TAP_DANCE_FN(bs_dance),
  [TD_DEL_INS] = ACTION_TAP_DANCE_FN(del_dance)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ergodox(  // layer 0 : default
//.---------------------------------------------. .---------------------------------------------.
//| ESC   | 1   | 2   | 3   | 4   | 5   | To 4  | ! TT 2  | 6   | 7   | 8   | 9   | 0   | -     |
//!-------+-----+-----+-----+-----+-------------! !-------+-----+-----+-----+-----+-----+-------!
//|LT3/Tab| Q   | W   | E   | R   | T   |  MO   | !  MO   | Y   | U   | I   | O   | P   | \     |
//!-------+-----+-----+-----x-----x-----!   1   ! !  1    !-----x-----x-----+-----+-----+-------!
//|OS(CTL)| A   | S   | D   | F   | G   |-------! !-------! H   | J   | K   | L   |TD(;)|LT2/Ent|
//!-------+-----+-----+-----x-----x-----! HYPR  ! !  MEH  !-----x-----x-----+-----+-----+-------!
//|OS(LSH)| Z   | X   | C   | V   | B   |       | !       | N   | M   | ,   | .   |Cl(/)|SpcCL  |
//'-------+-----+-----+-----+-----+-------------' '-------------+-----+-----+-----+-----+-------'
//|AltT(")| LEAD| `   |TD(L)|TD(R)|                             ! UP  | DN  | [   | ]   |AltT(=)|
// '------------------------------'                             '------------------------------'
//                              .---------------. .---------------.
//                              | rclk  | win   | !TD(del)|CtlT(E)|
//                      .-------+-------+-------! !-------+-------+-------.
//                      ! Back  !  Tap  | Home  | ! TD(PU)| SPC   !  SPC  !
//                      ! Space ! Dance !-------! !-------!       !       !
//                      |       | BSpace| End   | ! TD(PD)|       |       |
//                      '-----------------------' '-----------------------'
        // left hand
        KC_GESC,      KC_1,      KC_2,      KC_3,     KC_4,   KC_5,   TO(4),
        LT(3,KC_TAB),   KC_Q,      KC_W,      KC_E,     KC_R,   KC_T,   MO(1),
        OSM(MOD_LCTL),  KC_A,      KC_S,      KC_D,     KC_F,   KC_G,
        OSM(MOD_LSFT),  KC_Z,      KC_X,      KC_C,     KC_V,   KC_B,   MT(MOD_HYPR, KC_NO),
        ALT_T(KC_QUOTE),KC_LEAD,   KC_GRAVE,  TD(TD_LEFT_CLEFT),TD(TD_RIGHT_CRIGHT),
                                              ALT_T(KC_APPLICATION),  KC_LGUI,
                                                                      KC_HOME,
                                               KC_BSPACE, TD(TD_BKSPC),  KC_END,
       // right hand
       TT(2),  KC_6,        KC_7,   KC_8,   KC_9,       KC_0,             KC_MINUS,
       MO(1),  KC_Y,        KC_U,   KC_I,   KC_O,       KC_P,             KC_BSLASH,
               KC_H,        KC_J,   KC_K,   KC_L,       TD(TD_QUOT_SEMI), LT(2, KC_ENTER),
       MT(MOD_MEH, KC_NO),  KC_N,   KC_M,   KC_COMMA,   KC_DOT,           RCTL_T(KC_SLASH), KC_LSPO,
                            KC_UP,  KC_DOWN,KC_LBRACKET,KC_RBRACKET,      ALT_T(KC_EQUAL),
       TD(TD_DEL_INS),           CTL_T(KC_ESC),
       TD(TD_PGUP_HOME),
       TD(TD_PGDN_END),KC_SPACE, KC_SPACE
       ),
    [1] = LAYOUT_ergodox(  // layer 1 : punctuation, etc.
//.---------------------------------------------. .---------------------------------------------.
//| ESC   | F1  | F2  | F3  | F4  | F5  | To(3) | ! ____  | F6  | F7  | F8  | F9  | F10 | F11   |
//!-------+-----+-----+-----+-----+-------------! !-------+-----+-----+-----+-----+-----+-------!
//| ____  | !   | @   | {   | }   | |   | +--+  | ! ____  | UP  | 7   | 8   | 9   | *   | F12   |
//!-------+-----+-----+-----x-----x-----!       ! !       !-----x-----x-----+-----+-----+-------!
//| ____  | #   | $   | (   | )   | `   |-------! !-------! DN  | 4   | 5   | 6   | '   | Enter |
//!-------+-----+-----+-----x-----x-----! +--+  ! ! ____  !-----x-----x-----+-----+-----+-------!
//| ____  | %   | ^   | [   | ]   | ~   |       | !       | &   | 1   | 2   | 3   | \   | =     |
//'-------+-----+-----+-----+-----+-------------' '-------------+-----+-----+-----+-----+-------'
// | ____ | LEAD| +--+| +--+| +--+|                             ! 0   | 0   | .   | =   | =    |
// '------------------------------'                             '------------------------------'
//                              .---------------. .---------------.
//                              |RGB_MOD| +--+  | !RGB_TOG|RGB_SLD|
//                      .-------+-------+-------! !-------+-------+-------.
//                      ! RGB   ! RGB   | +--+  | ! +--+  | RGB   ! RGB   !
//                      ! VAL   ! VAL   !-------! !-------! HUE   ! HUE   !
//                      |  -    |  +    | +--+  | ! +--+  |  -    |  +    |
//                      '-----------------------' '-----------------------'
        // left hand
        KC_ESCAPE,      KC_F1,    KC_F2,    KC_F3,        KC_F4,        KC_F5,    TO(3),
        KC_TRANSPARENT, KC_EXLM,  KC_AT,    KC_LCBR,      KC_RCBR,      KC_PIPE,  KC_NO,
        KC_TRANSPARENT,          KC_HASH,  KC_DLR,   KC_LPRN,      KC_RPRN,      KC_GRAVE,
        KC_TRANSPARENT,          KC_PERC,  KC_CIRC,  KC_LBRACKET,  KC_RBRACKET,  KC_TILD,  KC_NO,
        KC_TRANSPARENT,          KC_LEAD,  KC_NO,    KC_NO,        KC_NO,
                                              RGB_MOD,            KC_NO,
                                                                  KC_NO,
                                              RGB_VAD,   RGB_VAI, KC_NO,
        // right hand
       KC_TRANSPARENT,  KC_F6,    KC_F7,   KC_F8,  KC_F9,  KC_F10,    KC_F11,
       KC_TRANSPARENT,  KC_UP,    KC_7,    KC_8,   KC_9,   KC_ASTR,   KC_F12,
                        KC_DOWN,  KC_4,    KC_5,   KC_6,   KC_QUOTE,  KC_ENTER,
       KC_TRANSPARENT,  KC_AMPR,  KC_1,    KC_2,   KC_3,   KC_BSLASH, KC_EQUAL,
                                  KC_0,    KC_0,   KC_DOT, KC_EQUAL,  KC_EQUAL,
       RGB_TOG,             RGB_SLD,
       KC_NO,
       KC_NO,      RGB_HUD,  RGB_HUI
       ),
    [2] = LAYOUT_ergodox(  // layer 2 : navigation and mouse
//.---------------------------------------------. .---------------------------------------------.
//| +--+  |+--+ |+--+ |+--+ |+--+ |+--+ |+--+   | ! TO(0) |VL UP|VL DN|+--+ |+--+ |+--+ | Reset |
//!-------+-----+-----+-----+-----+-------------! !-------+-----+-----+-----+-----+-----+-------!
//|OS(ALT)|+--+ |+--+ |M UP |+--+ |WH UP|+--+   | !+--+   |+--+ |+--+ |+--+ |+--+ |+--+ |+--+   |
//!-------+-----+-----+-----x-----x-----!       ! !       !-----x-----x-----+-----+-----+-------!
//|OS(CTL)|CL(A)|M LFT|M DN |M RGT|WH DN|-------! !-------! UP  | DN  | LFT | RGT |+--+ | Entr  |
//!-------+-----+-----+-----x-----x-----!       ! !+--+   !-----x-----x-----+-----+-----+-------!
//|OS(SFT)|CL(Z)|CL(X)|CL(C)|CL(V)|+--+ |+--+   | !       |+--+ |+--+ | Prev| Next|+--+ |+--+   |
//'-------+-----+-----+-----+-----+-------------' '-------------+-----+-----+-----+-----+-------'
// |+--+  |+--+ |+--+ |CSLft|CSRht|                             !VL UP|VL DN|MUTE |+--+ |+--+  |
// '------------------------------'                             '------------------------------'
//                              .---------------. .---------------.
//                              |+--+   |MB 5   | !MS SPD1|MS SPD2|
//                      .-------+-------+-------! !-------+-------+-------.
//                      !Mouse  !Mouse  |MB 4   | !+--+   |       !       !
//                      !Button !Button !-------! !-------!       !MS SPD0!
//                      |   1   |  2    |MB 3   | !WWW BK |WWW FWD|       |
//                      '-----------------------' '-----------------------'
        // left hand
        KC_NO,          KC_NO,      KC_NO,      KC_NO,      KC_NO,        KC_NO,        KC_NO,
        OSM(MOD_LALT),  KC_NO,      KC_NO,      KC_MS_UP,   KC_NO,        KC_MS_WH_UP,  KC_NO,
        OSM(MOD_LCTL),  LCTL(KC_A), KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT,  KC_MS_WH_DOWN,
        OSM(MOD_LSFT),  LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V),   KC_NO,        KC_NO,
        KC_NO,          KC_NO,      KC_NO,      LCTL(LSFT(KC_LEFT)), LCTL(LSFT(KC_RIGHT)),
                                                            KC_NO,                  KC_MS_BTN5,
                                                                                    KC_MS_BTN4,
                                                            KC_MS_BTN1, KC_MS_BTN2, KC_MS_BTN3,
        // right hand
        TO(0), KC_AUDIO_VOL_UP,KC_AUDIO_VOL_DOWN, KC_NO,  KC_NO, KC_NO, RESET,
        KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,
        KC_UP, KC_DOWN, KC_LEFT,  KC_RIGHT, KC_NO, KC_ENTER,
        KC_NO, KC_NO, KC_NO,   KC_MEDIA_PREV_TRACK, KC_MEDIA_NEXT_TRACK,KC_NO, KC_NO,
               KC_AUDIO_VOL_UP,  KC_AUDIO_VOL_DOWN,KC_AUDIO_MUTE, KC_NO, KC_NO,
        KC_MS_ACCEL1,       KC_MS_ACCEL2,
        KC_NO,
        KC_WWW_BACK,KC_WWW_FORWARD,KC_MS_ACCEL0
        ),
    [3] = LAYOUT_ergodox(  // layer 3 : editing and moving
//.---------------------------------------------. .---------------------------------------------.
//|+--+   |+--+ |+--+ |+--+ |Altf4|+--+ |Ctl(f5)| ! To(0) |+--+ |AltF7|+--+ |+--+ |+--+ |+--+   |
//!-------+-----+-----+-----+-----+-------------! !-------+-----+-----+-----+-----+-----+-------!
//| ____  |+--+ |+--+ |+--+ |+--+ |+--+ | Ctl   | ! +--+  |Ctl Y|+--+ |+--+ |+--+ |Pg UP|+--+   |
//!-------+-----+-----+-----x-----x-----! AltIns! !       !-----x-----x-----+-----+-----+-------!
//| ____  |Ctl A|+--+ |+--+ |+--+ |+--+ |-------! !-------! Up  | Dn  | Left|Right|Pg DN|+--+   |
//!-------+-----+-----+-----x-----x-----! Ctl   ! ! Shift !-----x-----x-----+-----+-----+-------!
//| ____  |Ctl Z|Ctl X|Ctl C|Ctl V|+--+ | Del   | !  Tab  |+--+ |+--+ |+--+ |+--+ |+--+ |+--+   |
//'-------+-----+-----+-----+-----+-------------' '-------------+-----+-----+-----+-----+-------'
// |+--+  |+--+ |+--+ |+--+ |+--+ |                             !     |     |     |     |      |
// '------------------------------'                             '------------------------------'
//                              .---------------. .---------------.
//                              |+--+   |+--+   | !+--+   |+--+   |
//                      .-------+-------+-------! !-------+-------+-------.
//                      !       !       |+--+   | !+--+   |       !       !
//                      ! ALT   ! CTL   !-------! !-------!       ! Tab   !
//                      |       |       | Win   | !WWW Bk |WWW Fwd|       |
//                      '-----------------------' '-----------------------'
        // left hand
        KC_NO,          KC_NO,      KC_NO,      KC_NO,      LALT(KC_F4),  KC_NO,  LCTL(KC_F5),
        KC_TRANSPARENT, KC_NO,      KC_NO,      KC_NO,      KC_NO,        KC_NO,  LALT(LCTL(KC_INSERT)),
        KC_TRANSPARENT, LCTL(KC_A), KC_NO,      KC_NO,      KC_NO,        KC_NO,
        KC_TRANSPARENT, LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V),   KC_NO,    LCTL(KC_DELETE),
        KC_NO,          KC_NO,      KC_NO,      KC_NO,      KC_NO,
        KC_NO,          KC_NO,
        KC_NO,
        RALT_T(KC_NO),  CTL_T(KC_NO),         GUI_T(KC_NO),
        // right hand
        TO(0),        KC_NO,      LALT(KC_F7),  KC_NO,    KC_NO,    KC_NO,    KC_NO,
        KC_NO,        LCTL(KC_Y), KC_NO,        KC_NO,    KC_NO,    KC_PGUP,  KC_NO,
                      KC_UP,      KC_DOWN,      KC_LEFT,  KC_RIGHT, KC_PGDOWN,KC_NO,
        LSFT(KC_TAB), KC_NO,      KC_NO,        KC_NO,    KC_NO,    KC_NO,    KC_NO,
                      KC_NO,      KC_NO,        KC_NO,    KC_NO,    KC_NO,
        KC_NO,        KC_NO,
        KC_NO,
        KC_WWW_BACK,  KC_WWW_FORWARD,    KC_TAB
        ),
    [4] = LAYOUT_ergodox(  // layer 4 : gaming
//.---------------------------------------------. .---------------------------------------------.
//| ESC   | 1   | 2   | 3   | 4   | 5   | To 0  | ! TT 2  | 6   | 7   | 8   | 9   | 0   | -     |
//!-------+-----+-----+-----+-----+-------------! !-------+-----+-----+-----+-----+-----+-------!
//| Tab   | Q   | W   | E   | R   | T   |  MO   | !  MO   | Y   | U   | I   | O   | P   | \     |
//!-------+-----+-----+-----x-----x-----!   1   ! !  1    !-----x-----x-----+-----+-----+-------!
//| CTL   | A   | S   | D   | F   | G   |-------! !-------! H   | J   | K   | L   |TD(;)|Enter  |
//!-------+-----+-----+-----x-----x-----! HYPR  ! !  MEH  !-----x-----x-----+-----+-----+-------!
//| LSHFT | Z   | X   | C   | V   | B   |       | !       | N   | M   | ,   | .   |Cl(/)|SpcCL  |
//'-------+-----+-----+-----+-----+-------------' '-------------+-----+-----+-----+-----+-------'
//| Alt   | LEAD| `   |LEFT |RIGHT|                             ! UP  | DN  | [   | ]   |AltT(=)|
// '------------------------------'                             '------------------------------'
//                              .---------------. .---------------.
//                              | rclk  | win   | !TD(del)|CtlT(E)|
//                      .-------+-------+-------! !-------+-------+-------.
//                      ! Back  !  Tap  | Home  | ! TD(PU)| SPC   !  SPC  !
//                      ! Space ! Dance !-------! !-------!       !       !
//                      |       | BSpace| End   | ! TD(PD)|       |       |
//                      '-----------------------' '-----------------------'
        // left hand
        KC_ESCAPE,  KC_1,      KC_2,      KC_3,     KC_4,   KC_5,   TO(0),
        KC_TAB,     KC_Q,      KC_W,      KC_E,     KC_R,   KC_T,   MO(1),
        KC_LCTRL,   KC_A,      KC_S,      KC_D,     KC_F,   KC_G,
        KC_LSHIFT,  KC_Z,      KC_X,      KC_C,     KC_V,   KC_B,   MT(MOD_HYPR, KC_NO),
        KC_LALT,    KC_LEAD,  KC_GRAVE,   KC_LEFT,  KC_RIGHT,
                                              ALT_T(KC_APPLICATION),  KC_LGUI,
                                                                      KC_HOME,
                                               KC_SPACE, KC_BSPACE,   KC_END,
       // right hand
       TT(2),  KC_6,        KC_7,   KC_8,   KC_9,       KC_0,             KC_MINUS,
       MO(1),  KC_Y,        KC_U,   KC_I,   KC_O,       KC_P,             KC_BSLASH,
               KC_H,        KC_J,   KC_K,   KC_L,       TD(TD_QUOT_SEMI), KC_ENTER,
       MT(MOD_MEH, KC_NO),  KC_N,   KC_M,   KC_COMMA,   KC_DOT,           RCTL_T(KC_SLASH), KC_RSHIFT,
               KC_UP,       KC_DOWN,KC_LBRACKET,KC_RBRACKET,      ALT_T(KC_EQUAL),
       TD(TD_DEL_INS),           CTL_T(KC_ESC),
       TD(TD_PGUP_HOME),
       TD(TD_PGDN_END),KC_SPACE, KC_SPACE
       ),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
      break;
    };
  return true;
};



void rgb_matrix_indicators_kb(void) {
  switch (biton32(layer_state)) {
      case 1:
        rgb_matrix_set_color_all(0x00, 0xFF, 0x00);
        break;
      case 2:
        rgb_matrix_set_color_all(0xFF, 0xFF, 0x00);
        break;
      case 3:
        rgb_matrix_set_color_all(0xFF, 0x80, 0x00);
        break;
      case 4:
       rgb_matrix_set_color_all(0x00, 0xFF, 0xFF);
        break;
      default:
        for (i = 0; i < 5; i++) {
          for (j = 3; j < 13; j++) {
            rgb_matrix_set_color(row_def[i][j], row_def[i][0], row_def[i][1], row_def[i][2]);
          }
        }
        break;
  }
}

