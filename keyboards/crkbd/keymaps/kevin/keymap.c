/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
bool is_alt_tab_active = false; // ADD this near the beginning of keymap.c

#include QMK_KEYBOARD_H

enum custom_keycodes {
    // KC_LGUI_TAB = SAFE_RANGE,
    SMTD_KEYCODES_BEGIN = SAFE_RANGE,
    CKC_A, // reads as C(ustom) + KC_A, but you may give any name here
    CKC_S,
    CKC_D,
    CKC_F,
    CKC_J, // reads as C(ustom) + KC_A, but you may give any name here
    CKC_K,
    CKC_L,
    CLT_1SPC,
    CLT_1BSPC,
    CLT_3TAB,
    CLT_2RET,
    CKC_GESC,
    CKC_QUOT,
    TILDE_SPC,
    KC_LGUI_TAB,
    CUSTOM_CAPSWORD,
    SMTD_KEYCODES_END,
};


enum layers {
    _BASE,
    _NAV,
    _SYM,
    _MOU,
};

#define COMBO_REF_DEFAULT _BASE

enum {
    TD_CAPSW,
    TD_CP,
    TD_UNDO,
};

enum combos {
    BSLS_COMB,
    SLSH_COMB,
    LBRC_COMB,
    RBRC_COMB,
    LCBRC_COMB,
    RCBRC_COMB,
    LPRN_COMB,
    RPRN_COMB,


    HT_COMB,
    LT_COMB,
    DQUT_COMB,
    CSPC_COMB,
    OSM_L1_COMB,
    QUES_COMB,
    UND_COMB,
    COLON_COMB,
    CLN_COMB,
    SCLN_COMB,
    AT_COMB,
    EXCL_COMB,
    HASH_COMB,
    DOL_COMB,
    PERC_COMB,
    CARET_COMB,
    AMPER_COMB,
    ASTER_COMB,


    GRVSPC_COMB,
    PIPE_COMB,
    SENTER_COMB,
    TILDE_COMB,

    MINUS_COMB,
    PLUS_COMB,
    EQUAL_COMB,

    TILDE_DOT_COMB,
    TILDE_SPC_COMB,

    CMB_ALTTAB
};


void td_capsword_fn(tap_dance_state_t *state, void *user_data) {
    if (state->count >= 2) {
        tap_code16(CUSTOM_CAPSWORD);
    } else{
        set_oneshot_mods (MOD_LSFT);
    }
}

void td_copy_cut_fn(tap_dance_state_t *state, void *user_data) {
    if (state->count >= 2) {
        tap_code16(G(KC_X));
    } else{
        tap_code16(G(KC_C));
    }
}


void td_undo_fn(tap_dance_state_t *state, void *user_data) {
    if (state->count >= 2) {
        tap_code16(S(G(KC_Z)));
    } else {
        tap_code16(G(KC_Z));
    }
}


tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_CAPSW] = ACTION_TAP_DANCE_FN(td_capsword_fn),
    [TD_CP] = ACTION_TAP_DANCE_FN(td_copy_cut_fn),
    [TD_UNDO] = ACTION_TAP_DANCE_FN(td_undo_fn),
};

const uint16_t PROGMEM combo_alttab[] = {KC_F, KC_G, COMBO_END};
const uint16_t PROGMEM backslash[] = {CKC_D, KC_V, COMBO_END};
const uint16_t PROGMEM slash[] = {CKC_K, KC_M, COMBO_END};
const uint16_t PROGMEM lbracket[] = {CKC_J, CKC_K, COMBO_END};
const uint16_t PROGMEM lcbracket[] = {CKC_J, CKC_K, COMBO_END};
const uint16_t PROGMEM rbracket[] = {CKC_K, CKC_L, COMBO_END};
const uint16_t PROGMEM rcbracket[] = {CKC_K, CKC_L, COMBO_END};

const uint16_t PROGMEM lpar[] = {KC_M, KC_COMM, COMBO_END};
const uint16_t PROGMEM rpar[] = {KC_COMM, KC_DOT, COMBO_END};

const uint16_t PROGMEM lt[] = {KC_M, KC_COMM, COMBO_END};
const uint16_t PROGMEM ht[] = {KC_COMM, KC_DOT, COMBO_END};

const uint16_t PROGMEM excl[] = {CKC_W, KC_D, COMBO_END};
const uint16_t PROGMEM at[] = {CKC_S, KC_W, COMBO_END};
const uint16_t PROGMEM hash[] = {CKC_D, KC_E, COMBO_END};
const uint16_t PROGMEM dollar[] = {CKC_F, KC_R, COMBO_END};
const uint16_t PROGMEM percent[] = {KC_G, KC_T, COMBO_END};
const uint16_t PROGMEM caret[] = {KC_H, KC_Y, COMBO_END};
const uint16_t PROGMEM amper[] = {CKC_J, KC_U, COMBO_END};
const uint16_t PROGMEM aster[] = {CKC_K, KC_I, COMBO_END};


const uint16_t PROGMEM dquote[] = {CKC_J, KC_I, COMBO_END};
const uint16_t PROGMEM osml1[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM cspc[] = {CKC_D, CKC_S, COMBO_END};
const uint16_t PROGMEM ques[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM und[] = {KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM cln[] = {CKC_D, CKC_F, COMBO_END};
const uint16_t PROGMEM scln[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM senter_combo[] = {KC_U, KC_I, COMBO_END};


const uint16_t PROGMEM tilde[] = {CKC_L, KC_O, COMBO_END};  // You can change these keys to your preferenc
const uint16_t PROGMEM tilde_spc[] = {KC_I, KC_O, COMBO_END};  // You can change these keys to your preference
const uint16_t PROGMEM tilde_dot[] = {CKC_L, KC_QUOT, COMBO_END};  // You can change these keys to your preference
const uint16_t PROGMEM pipe[] = {KC_H, KC_N, COMBO_END};  // You can change these keys to your preference
//
const uint16_t PROGMEM minus[] = {CKC_J, KC_M, COMBO_END};  // You can change these keys to your preference
const uint16_t PROGMEM plus[] = {CKC_F, KC_V, COMBO_END};  // You can change these keys to your preference
const uint16_t PROGMEM equal[] = {KC_C, KC_V, COMBO_END};  // You can change these keys to your preference
//

const uint16_t PROGMEM grave[] = {KC_E, CKC_F, COMBO_END};  // You can change these keys to your preference

bool caps_word_press_user(uint16_t keycode) {
  switch (keycode) {
    // Continue Caps Word for alphanumerics + underscore/backspace/delete
    case KC_A ... KC_Z:
    case KC_0 ... KC_9:
    case KC_UNDS:     // _
    case KC_BSPC:     // Backspace
    case KC_DEL:      // Delete
      if (keycode >= KC_A && keycode <= KC_Z) {
        add_weak_mods(MOD_BIT(KC_LSFT)); // Auto-shift letters
      }
      return true;

    // Word-breaking keys (non-alnum except those above)
    default:
      return false; // Deactivate Caps Word
  }
}

//
combo_t key_combos[] = {

    [SENTER_COMB] = COMBO(senter_combo, S(KC_ENT)), // KC_NO to leave processing for process_combo_event
    [CMB_ALTTAB] = COMBO(combo_alttab, KC_NO), // KC_NO to leave processing for process_combo_event
    [BSLS_COMB] = COMBO(backslash, KC_BSLS),
    [SLSH_COMB] = COMBO(slash, KC_SLSH),
    [LBRC_COMB] = COMBO(lbracket, KC_LBRC),
    [LCBRC_COMB] = COMBO(lcbracket, KC_LCBR),

    [RBRC_COMB] = COMBO(rbracket, KC_RBRC),
    [RCBRC_COMB] = COMBO(rcbracket, KC_RCBR),

    [LPRN_COMB] = COMBO(lpar, KC_LPRN),
    [RPRN_COMB] = COMBO(rpar, KC_RPRN),

    [HT_COMB] = COMBO(ht, KC_GT),
    [LT_COMB] = COMBO(lt, KC_LT),

    [EXCL_COMB] = COMBO(excl, KC_EXLM),
    [AT_COMB] = COMBO(at, KC_AT),
    [HASH_COMB] = COMBO(hash, KC_HASH),
    [DOL_COMB] = COMBO(dollar, KC_DLR),
    [PERC_COMB] = COMBO(percent, KC_PERC),
    [CARET_COMB] = COMBO(caret, KC_CIRC),
    [AMPER_COMB] = COMBO(amper, KC_AMPR),
    [ASTER_COMB] = COMBO(aster, KC_ASTR),


    [OSM_L1_COMB] = COMBO(osml1, OSL(1)),
    [CSPC_COMB] = COMBO(cspc, LCTL(KC_SPC)),
    [QUES_COMB] = COMBO(ques, KC_QUES),
    [UND_COMB] = COMBO(und, KC_UNDS),
    [CLN_COMB] = COMBO(cln, KC_COLN),
    [SCLN_COMB] = COMBO(scln, KC_SCLN),
    [PIPE_COMB] = COMBO(pipe, KC_PIPE),

    [MINUS_COMB] = COMBO(minus, KC_MINS),
    [PLUS_COMB] = COMBO(plus, KC_PLUS),
    [EQUAL_COMB] = COMBO(equal, KC_EQL),

    [TILDE_COMB] = COMBO(tilde, KC_TILD),
    [GRVSPC_COMB] = COMBO_ACTION(grave),
    [TILDE_DOT_COMB] = COMBO_ACTION(tilde_dot),
    [TILDE_SPC_COMB] = COMBO_ACTION(tilde_spc),
    [DQUT_COMB] = COMBO_ACTION(dquote),
};


#include "sm_td.h"
#ifdef LAYOUT_split_3x5_3_ex2
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_split_3x5_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,  KC_VOLU,    KC_MUTE,   KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+---:w-----+--------+--------+--------|
      CKC_A,   CKC_S,   CKC_D,   CKC_F,   KC_G,  KC_VOLD,    KC_MPLY,   KC_H,   CKC_J,   CKC_K,   CKC_L,CKC_QUOT,
   //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                         CKC_GESC, CLT_1SPC, CLT_3TAB,                CLT_2RET, CLT_1BSPC, OSM(MOD_LSFT)

  ),

  [_NAV] = LAYOUT_split_3x5_3_ex2(
  //,------------------------------------------------------.  ,--------------------------------------------------------------.
       KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   S(KC_G),      S(KC_G),    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
  //|--------+--------+--------+--------+--------+--------+  |--------+--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, S(KC_G), KC_VOLD, KC_MPLY, KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, CW_TOGG,
  //|--------+--------+--------+--------+--------+--------+  `--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, OSM(MOD_LSFT), C(KC_SPC), G(KC_TAB),           KC_HOME, KC_PGDN, KC_PGUP, KC_END, S(KC_G),
  //|--------+--------+--------+--------+--------+--------+  ,--------+--------+--------+--------+--------+--------+--------|
                                 KC_LGUI, TD(TD_CAPSW),  KC_SPC,     KC_ENT, KC_BSPC, KC_DEL
                                      //`--------------------------'  `--------------------------'
  ),


  [_SYM] = LAYOUT_split_3x5_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,    KC_F6,   KC_F7,      KC_F8,    KC_F9,    KC_F10, KC_F11, KC_F12,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_GRV,   KC_LALT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,    KC_F6,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
LCTL(KC_GRV), LALT(KC_GRV), LGUI(KC_GRV), LSFT(KC_GRV),KC_TILD,       KC_UNDS, KC_PLUS,  KC_LPRN, KC_RPRN,  KC_PIPE,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                KC_LGUI, KC_SPC,  KC_SPC,   KC_ENT, KC_BSPC, KC_LSFT
                                      //`--------------------------'  `--------------------------'
  ),

    [_MOU] = LAYOUT_split_3x5_3_ex2(
  //,- --------------------------------------------------------------------------.  ,--------------------------------------------------------------.
      G(KC_TAB),    G(KC_LCBR),G(KC_RCBR),   KC_BSPC,      KC_DEL,      G(S(KC_4)),  XXXXXXX,   G(KC_ENT), S(KC_ENT), MS_UP, XXXXXXX,  XXXXXXX,
  //|--------+-------------+-------------+----------+-----------+--------+-------|  |--------+--------+--------+--------+--------+--------+--------|
      G(KC_GRV),   G(KC_Z),   TD(TD_CP),      G(KC_V),    G(S(KC_Z)), C(G(S(KC_3))), G(S(KC_5)), MS_WHLL,   MS_LEFT, MS_DOWN, MS_RGHT, MS_WHLR,
        //|--------+-------------+------------+------------+--------+--------'`--------+--------+--------+--------+--------+--------+--------|
      G(KC_X),     G(KC_ENT), S(KC_ENT),    KC_ENT,        G(S(KC_V)),                 S(KC_ENT),    MS_WHLD, MS_WHLU, KC_ENT, XXXXXXX,
  //|--------+-------------+--------------+------------+------------+------+--------.  ,--------+--------+--------+------,--+--------+--------+--------|
                                  KC_LGUI, KC_SPC,  KC_SPC,     MS_BTN1, MS_BTN2, MS_BTN3

                                      //`--------------------------'  `--------------------------'
  ),

};
#endif

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [0] = { ENCODER_CCW_CW(RGB_MOD, RGB_RMOD), ENCODER_CCW_CW(RGB_HUI, RGB_HUD), ENCODER_CCW_CW(RGB_VAI, RGB_VAD), ENCODER_CCW_CW(RGB_SAI, RGB_SAD), },
  [1] = { ENCODER_CCW_CW(RGB_MOD, RGB_RMOD), ENCODER_CCW_CW(RGB_HUI, RGB_HUD), ENCODER_CCW_CW(RGB_VAI, RGB_VAD), ENCODER_CCW_CW(RGB_SAI, RGB_SAD), },
  [2] = { ENCODER_CCW_CW(RGB_MOD, RGB_RMOD), ENCODER_CCW_CW(RGB_HUI, RGB_HUD), ENCODER_CCW_CW(RGB_VAI, RGB_VAD), ENCODER_CCW_CW(RGB_SAI, RGB_SAD), },
  [3] = { ENCODER_CCW_CW(RGB_MOD, RGB_RMOD), ENCODER_CCW_CW(RGB_HUI, RGB_HUD), ENCODER_CCW_CW(RGB_VAI, RGB_VAD), ENCODER_CCW_CW(RGB_SAI, RGB_SAD), },
};
#endif


bool caps_word_press_user(uint16_t keycode) {
  switch (keycode) {
    case KC_A ... KC_Z:  // Valid range (ASCII order)
    case KC_1 ... KC_9:  // Numbers 1-9
    case KC_0:           // Handle zero separately
    case KC_UNDS:
      add_weak_mods(MOD_BIT(KC_LSFT));
      return true;


    // Additional keys that should turn off caps word
    case KC_BSPC:
    case CKC_GESC:
    case CLT_1SPC:
    case CLT_3TAB:
    case CLT_2RET:
    case CLT_1BSPC:
    case KC_ESC:
    case KC_DEL:
    case KC_ENTER:
    case KC_SPC:
    case OSM(MOD_LSFT):
      return false;
    default:
      return false;
  }
}


void on_smtd_action(uint16_t keycode, smtd_action action, uint8_t tap_count) {
    switch (keycode) {
        SMTD_MT(CKC_A, KC_A, KC_LEFT_CTRL)
        SMTD_MT(CKC_S, KC_S, KC_LEFT_ALT)
        SMTD_MT(CKC_D, KC_D, KC_LEFT_GUI)
        SMTD_MT(CKC_F, KC_F, KC_LSFT)

        SMTD_MT(CKC_J, KC_J, KC_LSFT)
        SMTD_MT(CKC_K, KC_K, KC_LEFT_GUI)
        SMTD_MT(CKC_L, KC_L, KC_LEFT_ALT)
        SMTD_MT(CKC_QUOT, KC_QUOT, KC_LEFT_CTRL)


        SMTD_MT(CKC_GESC, KC_ESC, KC_LGUI)
        SMTD_LT(CLT_1SPC, KC_SPC, 1)
        SMTD_LT(CLT_1BSPC, KC_BSPC, 1)
        SMTD_LT(CLT_2RET, KC_ENT, 2)
        SMTD_LT(CLT_3TAB, KC_TAB, 3)
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    if (is_alt_tab_active) {
        unregister_code(KC_LGUI);
        is_alt_tab_active = false;
    }
    return state;
}


bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (!process_smtd(keycode, record)) {
        return false;
    }
    switch (keycode){
        case KC_LGUI_TAB: // super alt tab macro
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LGUI);
                }
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
            return false;
    }
    return true;
}
//
// void matrix_scan_user(void) { // The very important timer.
//   if (is_alt_tab_active) {
//     if (timer_elapsed(alt_tab_timer) > 1000) {
//       unregister_code(KC_LGUI);
//       is_alt_tab_active = false;
//     }
//   } ()
// }  {  }
//
//[]
//
//
bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    /* Disable combo `SOME_COMBO` on layer `_LAYER_A` */
    switch (combo_index) {
        case LCBRC_COMB:
            if (layer_state_is(_BASE)) {
                return false;
            }
        break;
        case RCBRC_COMB:
            if (layer_state_is(_BASE)) {
                return false;
            }
        break;
        case LBRC_COMB:
            if (layer_state_is(_NAV)) {
                return false;
            }
        break;
        case RBRC_COMB:
            if (layer_state_is(_NAV)) {
                return false;
            }
        break;
        case HT_COMB:
            if (layer_state_is(_BASE)) {
                return false;
            }
        break;
        case LT_COMB:
            if (layer_state_is(_BASE)) {
                return false;
            }
        break;
        case LPRN_COMB:
            if (layer_state_is(_NAV)) {
                return false;
            }
        break;
        case RPRN_COMB:
            if (layer_state_is(_NAV)) {
                return false;
            }
        break;

    }

    return true;
}

bool process_combo_key_repress(uint16_t combo_index, combo_t *combo, uint8_t key_index, uint16_t keycode) {
    switch (combo_index) {
        case CMB_ALTTAB:
            switch (keycode) {
                case KC_F:
                    tap_code16(S(KC_TAB));
                    return true;
                case KC_G:
                    tap_code(KC_TAB);
                    return true;
            }
    }
    return false;
}



void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
        case CMB_ALTTAB:
            if (pressed) {
                register_mods(MOD_LALT);
                tap_code(KC_TAB);
            } else {
                unregister_mods(MOD_LALT);
            }
            break;

        case TILDE_SPC_COMB:
            if (pressed) {
                tap_code16(KC_TILD);
                tap_code16(KC_SPC);
            }
            break;

        case TILDE_DOT_COMB:
            if (pressed) {
                tap_code16(KC_TILD);
                tap_code16(KC_SPC);
                tap_code16(KC_SLSH);
            }
            break;
        case DQUT_COMB:

            if (pressed) {
                tap_code16(KC_DQT);
                tap_code16(KC_SPC);
            }
            break;
        case GRVSPC_COMB:
            if (pressed) {
                tap_code16(KC_GRV);
                tap_code16(KC_SPC);
            }
            break;
    }
}

