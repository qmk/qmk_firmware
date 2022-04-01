/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>
Copyright 2021 Emmanuel Villéger

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

#include QMK_KEYBOARD_H
#include "keymap_bepo.h"
#include "sendstring_bepo.h"

// super alt/tab macro
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

// timer for Mod-Tap
uint16_t mu_cced_timer = 0;

// record states of modifiers before using unicode
uint8_t mod_state;

#ifdef OLED_ENABLE
static uint32_t oled_timer = 0;
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layers {
  _BEPO,
  _NUMPAD,
  _LOWER,
  _RAISE,
  _PLOVER,
  _TOUCHCURSOR,
  _ADJUST
};

enum custom_keycodes {
  BEPO = SAFE_RANGE,
  NUMPAD,
  PLOVER,
  EXT_PLV,
  RGBRST,
  ALT_TAB, // super alt/tab macro
  // custom keycodes for shortcuts
  MVI_CLK, // clear keyboard
  MVI_CXU, // C-x u
  MVI_CCC, // C-c ;
  // custom keycode for personal mod_tap
  MU_CCED  // Mute when hold, ç when tapped
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

// Custom macros
#define TC_SPC   LT(_TOUCHCURSOR, KC_SPC)  // L-ayer T-ap T-ouch C-ursor on Space
#define TC_ENT   LT(_TOUCHCURSOR, KC_ENT)  // L-ayer T-ap T-ouch C-ursor on Enter
#define TC_PENT  LT(_TOUCHCURSOR, KC_PENT) // L-ayer T-ap T-ouch C-ursor on Enter
#define MVI_CUT  S(KC_DEL)  // cut
#define MVI_CPY  C(KC_INS)  // copy
#define MVI_PST  S(KC_INS)  // paste
#define XCV_CUT  C(BP_X)    // cut
#define XCV_CPY  C(BP_C)    // copy
#define XCV_PST  C(BP_V)    // paste
#define CTL_TAB  C(KC_TAB)    // C-Tab
#define CS_TAB   C(S(KC_TAB)) // C-Shift-Tab
#define MVI_MEN  LSFT(KC_F10) // Menu
  
// Left-hand home row mods
#define GUI_A  LGUI_T(BP_A)
#define ALT_U  LALT_T(BP_U)
#define SFT_I  LSFT_T(BP_I)
#define CTR_E  LCTL_T(BP_E)

#define GUI_F5 LGUI_T(KC_F5)
#define ALT_F6 LALT_T(KC_F6)
#define SFT_F7 LSFT_T(KC_F7)
#define CTR_F8 LCTL_T(KC_F8)

#define GUI_WHD LGUI_T(KC_WH_D)
#define ALT_MSL LALT_T(KC_MS_L)
#define SFT_MSD LSFT_T(KC_MS_D)
#define CTR_MSR LCTL_T(KC_MS_R)
  
// Right-hand home row mods
#define CTR_T  LCTL_T(BP_T)
#define SFT_S  RSFT_T(BP_S)
#define ALT_R  LALT_T(BP_R)
#define GUI_N  RGUI_T(BP_N)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BEPO] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     BP_W,    BP_B,    BP_EACU, BP_P,    BP_O,    BP_EGRV,                      BP_DCIR, BP_V,    BP_D,    BP_L,    BP_J,    KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     BP_Z,    GUI_A,   ALT_U,   SFT_I,   CTR_E,   BP_COMM,                      BP_C,    CTR_T,   SFT_S,   ALT_R,   GUI_N,   BP_M,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     BP_ECIR, BP_AGRV, BP_Y,    BP_X,    BP_DOT,  BP_K,                         BP_QUOT, BP_Q,    BP_G,    BP_H,    BP_F,    MU_CCED,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         KC_ALGR, LOWER,   TC_ENT,     TC_SPC,  RAISE,   KC_ALGR
                                      //`--------------------------'  `--------------------------'
  ),

  [_NUMPAD] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     KC_TAB,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_PMNS,                      KC_UP,   KC_NLCK, KC_P7,   KC_P8,   KC_P9,   KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_ESC,  GUI_F5,  ALT_F6,  SFT_F7,  CTR_F8,  KC_PPLS,                      KC_LEFT, KC_RGHT, KC_P4,   KC_P5,   KC_P6,   KC_PSLS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_CAPS, KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PEQL,                      KC_DOWN, KC_PDOT, KC_P1,   KC_P2,   KC_P3,   KC_PENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         MVI_PST, LOWER,   TC_PENT,     TC_SPC, RAISE,   KC_P0
                                      //`--------------------------'  `--------------------------'
  ),
  
  [_LOWER] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     BP_DLR,  BP_DQUO, BP_LDAQ, BP_RDAQ, BP_LPRN, BP_RPRN,                      BP_AT,   BP_PLUS, BP_MINS, BP_SLSH, BP_ASTR, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_ESC,  MVI_CXU, BP_LABK, BP_RABK, BP_LBRC, BP_RBRC,                      KC_PSCR, BP_EQL,  _______, _______, KC_TAB,  MVI_MEN,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_CAPS, ALT_TAB, BP_LEQL, BP_GEQL, CTL_TAB, _______,                      MVI_CCC, BP_PERC, MVI_CUT, MVI_CPY, MVI_PST, KC_VOLD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
 ),

  [_RAISE] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     BP_HASH, BP_1,    BP_2,    BP_3,    BP_4,    BP_5,                         BP_6,    BP_7,    BP_8,    BP_9,    BP_0,    _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   BP_DEG,  CTL_TAB, ALT_TAB, KC_TAB,  MVI_MEN,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_CAPS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,                       KC_F12,  BP_GRV,  XCV_CUT, XCV_CPY, XCV_PST, KC_VOLU,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_PLOVER] = LAYOUT( /* Plover layer (http://opensteno.org)
   *,-----------------------------------------------------.                    ,-----------------------------------------------------.
   *|   #    |   #    |   #    |   #    |   #    |   #    |                    |    #   |   #    |   #    |   #    |   #    |   #    |
   *|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
   *|        |   S    |   T    |   P    |   H    |   *    |                    |   *    |   F    |   P    |   L    |   T    |   D    |
   *|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
   *| Exit   |   S    |   K    |   W    |   R    |   *    |                    |   *    |   R    |   B    |   G    |   S    |   Z    |
   *`--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------|--------'
   *                                    |   A    |   O    |        |  |        |   E    |   U    |
   *                                    `--------------------------'  `--------------------------'
   */
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,                         KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     EXT_PLV, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         XXXXXXX, KC_C,    KC_V,       KC_N,    KC_M,    XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

  [_TOUCHCURSOR] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     KC_TAB,  KC_WH_U, KC_WH_L, KC_MS_U, KC_WH_R, KC_BTN1,                      KC_INS,  KC_HOME, KC_UP,   KC_PGUP, KC_BTN1, KC_ACL2,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_ESC,  GUI_WHD, ALT_MSL, SFT_MSD, CTR_MSR, KC_BTN2,                      KC_DEL,  KC_LEFT, KC_DOWN, KC_RGHT, KC_BTN2, KC_ACL1,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_CAPS, KC_ACL2, KC_ACL1, KC_ACL0, KC_BTN4, KC_BTN3,                      KC_BTN5, KC_END,  KC_DOWN, KC_PGDN, KC_BTN3, KC_ACL0,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         _______, _______, KC_SPC,      _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_ADJUST] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     RESET,   MVI_CLK, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, KC_DEL ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_ESC,  _______, _______, _______, _______, _______,                      _______, BEPO,    NUMPAD,  _______, PLOVER,  DEBUG,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  )
};

uint8_t RGB_current_mode;

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
  RGB_current_mode = rgblight_get_mode();
    #endif
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

void render_space(void) {
    oled_write_P(PSTR("     "), false);
}

void render_mod_status_gui_alt(uint8_t modifiers) {
    static const char PROGMEM gui_off_1[] = {0x85, 0x86, 0};
    static const char PROGMEM gui_off_2[] = {0xa5, 0xa6, 0};
    static const char PROGMEM gui_on_1[] = {0x8d, 0x8e, 0};
    static const char PROGMEM gui_on_2[] = {0xad, 0xae, 0};

    static const char PROGMEM alt_off_1[] = {0x87, 0x88, 0};
    static const char PROGMEM alt_off_2[] = {0xa7, 0xa8, 0};
    static const char PROGMEM alt_on_1[] = {0x8f, 0x90, 0};
    static const char PROGMEM alt_on_2[] = {0xaf, 0xb0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_1, false);
    } else {
        oled_write_P(gui_off_1, false);
    }

    if ((modifiers & MOD_MASK_GUI) && (modifiers & MOD_MASK_ALT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_1, false);
    } else {
        oled_write_P(alt_off_1, false);
    }

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_2, false);
    } else {
        oled_write_P(gui_off_2, false);
    }

    if (modifiers & MOD_MASK_GUI & MOD_MASK_ALT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_2, false);
    } else {
        oled_write_P(alt_off_2, false);
    }
}

void render_mod_status_shift_ctrl(uint8_t modifiers) {
    static const char PROGMEM shift_off_1[] = {0x89, 0x8a, 0};
    static const char PROGMEM shift_off_2[] = {0xa9, 0xaa, 0};
    static const char PROGMEM shift_on_1[] = {0x91, 0x92, 0};
    static const char PROGMEM shift_on_2[] = {0xb1, 0xb2, 0};

    static const char PROGMEM ctrl_off_1[] = {0x8b, 0x8c, 0};
    static const char PROGMEM ctrl_off_2[] = {0xab, 0xac, 0};
    static const char PROGMEM ctrl_on_1[] = {0xcd, 0xce, 0};
    static const char PROGMEM ctrl_on_2[] = {0xcf, 0xd0, 0};
    
    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_1, false);
    } else {
        oled_write_P(shift_off_1, false);
    }

    if ((modifiers & MOD_MASK_SHIFT) && (modifiers & MOD_MASK_CTRL)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_1, false);
    } else {
        oled_write_P(ctrl_off_1, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_2, false);
    } else {
        oled_write_P(shift_off_2, false);
    }

    if (modifiers & MOD_MASK_SHIFT & MOD_MASK_CTRL) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_2, false);
    } else {
        oled_write_P(ctrl_off_2, false);
    }
}

void render_lock_status(void) {
  led_t led_state = host_keyboard_led_state();
  oled_write_P(led_state.num_lock ? PSTR("NUM  ") : PSTR("     "), false);
  oled_write_P(led_state.caps_lock ? PSTR("CAP  ") : PSTR("     "), false);
  oled_write_P(led_state.scroll_lock ? PSTR("SCR  ") : PSTR("     "), false);
}

void render_layer_state(void) {
    static const char PROGMEM default_layer[] = {
        0x20, 0x94, 0x95, 0x96, 0x20,
        0x20, 0xb4, 0xb5, 0xb6, 0x20,
        0x20, 0xd4, 0xd5, 0xd6, 0x20, 0};
    static const char PROGMEM raise_layer[] = {
        0x20, 0x97, 0x98, 0x99, 0x20,
        0x20, 0xb7, 0xb8, 0xb9, 0x20,
        0x20, 0xd7, 0xd8, 0xd9, 0x20, 0};
    static const char PROGMEM lower_layer[] = {
        0x20, 0x9a, 0x9b, 0x9c, 0x20,
        0x20, 0xba, 0xbb, 0xbc, 0x20,
        0x20, 0xda, 0xdb, 0xdc, 0x20, 0};
    static const char PROGMEM adjust_layer[] = {
        0x20, 0x9d, 0x9e, 0x9f, 0x20,
        0x20, 0xbd, 0xbe, 0xbf, 0x20,
        0x20, 0xdd, 0xde, 0xdf, 0x20, 0};
    if(layer_state_is(_ADJUST)) {
      oled_write_P(adjust_layer, false);
    } else if(layer_state_is(_LOWER)) {
      oled_write_P(lower_layer, false);
    } else if(layer_state_is(_RAISE)) {
      oled_write_P(raise_layer, false);
    } else {
      oled_write_P(default_layer, false);
    }
    switch(get_highest_layer(default_layer_state)) {
    case _BEPO:
	oled_write_P(PSTR("BEPO "),false);
	break;
    case _NUMPAD:
      oled_write_P(PSTR("PAVE "),false);
      break;
    default:
      oled_write_P(PSTR("UNKNW"),false);
    }
}

void render_plover_state(void) {
    static const char PROGMEM plover_layer[] = {
        0x80, 0x81, 0x82, 0x83, 0x84,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4,
        0x01, 0x02, 0x03, 0x04, 0x05, 0};
    oled_write_P(plover_layer, false);
    render_space();
    oled_write_P(PSTR("PLOVR"),false);      
}

void render_status_main(void) {
  if (IS_LAYER_OFF(_PLOVER)) {
    render_layer_state();
    render_space();
    render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
    render_mod_status_shift_ctrl(get_mods()|get_oneshot_mods());
    render_space();
    render_lock_status();
  }
  else {
    render_space();
    render_space();
    render_space();
    render_space();
    render_plover_state();
    render_space();
    render_space();
    render_space();
    render_space();
  }
}

void render_status_secondary(void) {
    render_space();
    render_layer_state();
    render_space();
    render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
    render_mod_status_shift_ctrl(get_mods()|get_oneshot_mods());
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
      render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc.)
    } else {
      render_status_secondary();
    }
    return false;
}

#endif


layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_ENABLE
        oled_timer = timer_read32();
#endif
    // set_timelog();
  }

  switch (keycode) {
    case BEPO:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_BEPO);
      }
      return false;
      break;
    case NUMPAD:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_NUMPAD);
      }
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      #ifdef RGB_MATRIX_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgb_matrix_default();
          rgb_matrix_enable();
        }
      #endif
      break;
    case PLOVER:
      if (record->event.pressed) {
        layer_off(_RAISE);
        layer_off(_LOWER);
        layer_off(_ADJUST);
        layer_on(_PLOVER);
        if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false;
      break;
    case EXT_PLV:
      if (record->event.pressed) {
        layer_off(_PLOVER);
      }
      return false;
      break;
  case ALT_TAB:
    if (record->event.pressed) {
      if (!is_alt_tab_active) {
	is_alt_tab_active = true;
	register_code(KC_LALT);
      }
      alt_tab_timer = timer_read();
      register_code(KC_TAB);
    } else {
      unregister_code(KC_TAB);
    }
    break;
  case MU_CCED:
    if (record->event.pressed) {
      mu_cced_timer = timer_read();
    } else {
      if (timer_elapsed(mu_cced_timer) < TAPPING_TERM) {
	tap_code16(BP_CCED);
      }
      else {
	tap_code(KC_MUTE);
      }
    }
    break;
  case MVI_CLK:
    if (record->event.pressed) { // clear all mods and keys currently pressed
      clear_keyboard();
    }
    return false;
    break;
  case MVI_CXU:
    if (record->event.pressed) { // C-x u, undo in Emacs
      register_code(KC_LCTL);
      tap_code16(BP_X);
      unregister_code(KC_LCTL);
      tap_code16(BP_U);
    }
    return false;
    break;
  case MVI_CCC:
    if (record->event.pressed) { // C-c ;, comment/uncomment region in Emacs/AucTeX
      register_code(KC_LCTL);
      tap_code16(BP_C);
      unregister_code(KC_LCTL);
      tap_code16(S(BP_COMM));
    }
    return false;
    break;
  }
  return true;
}

void matrix_scan_user(void) { // The very important timer for alt/tab macro.
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > ALT_TAB_TERM) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}
