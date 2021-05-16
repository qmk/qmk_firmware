/* Copyright 2015-2017 Jack Humbert
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

/* modified by Gun Pinyo */

extern keymap_config_t keymap_config;

enum planck_layers {
  LY_0000, LY_0001, LY_0010, LY_0011,
  LY_0100, LY_0101, LY_0110, LY_0111,
  LY_1000, LY_1001, LY_1010, LY_1011,
  LY_1100, LY_1101, LY_1110, LY_1111,
  LY_THAI_A, LY_THAI_B, LY_THAI_C,
  LY_SANDBOX, LY_STICK,
};

enum planck_keycodes {
  MIN_KC = SAFE_RANGE,
  FN_A, FN_B, FN_C, FN_D,
  SANDBOX, STICK,
  OS_LINUX, OS_WIN, OS_OSX,
  THAI_IM_XKB, THAI_IM_UC,
  THAI_A, THAI_B, THAI_C,
  MOTION_LY, MOUSE_LY, MEDIA_LY,
  MY_NAME, MY_EMAIL,
  MAX_KC,
  DYNAMIC_MACRO_RANGE,
};
#include "dynamic_macro.h"

#define KC_R0_5 KC_TAB
#define KC_R1_5 KC_ENT
#define KC_R2_5 KC_RSFT

#define KC_R2_1 FN_A
#define KC_R2_2 FN_B
#define KC_R2_3 FN_C

#define KC_R3_0 FN_D
#define KC_R3_1 KC_SPC
#define KC_R3_2 KC_PAUSE

#define KC_L2_0 KC_LSFT

#define KC_L3_0 MT(MOD_LCTL, KC_PGDN)
#define KC_L3_1 MT(MOD_LALT, KC_PGUP)
#define KC_L3_2 MT(MOD_LGUI, KC_APP)

#define LAYOUT_gunp( k00, k01, k02, k03, k04, k05, \
                     k10, k11, k12, k13, k14, k15, \
                     k20, k21, k22, k23, k24, k25, \
                     k30, k31, k32, k33, k34, k35) \
LAYOUT_ortho_4x12( \
k00,k01,k02,k03,k04,k05, MEDIA_LY, KC_LEFT, KC_BSPC, KC_RGHT, XXXXXXX, KC_R0_5,\
k10,k11,k12,k13,k14,k15, MOUSE_LY, THAI_A,  THAI_B,  THAI_C,  XXXXXXX, KC_R1_5,\
k20,k21,k22,k23,k24,k25, MOTION_LY,KC_R2_1, KC_R2_2, KC_R2_3, XXXXXXX, KC_R2_5,\
k30,k31,k32,k33,k34,k35, KC_R3_0,  KC_R3_1, KC_R3_2, KC_RGUI, KC_RALT, KC_RCTL)

#define UNUSED_LAYER LAYOUT_gunp(\
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),

#define F1_F12_LAYER(M) LAYOUT_gunp(\
  S(M(KC_F7 )),S(M(KC_F8 )),M(KC_F7 ),M(KC_F8 ),M(KC_F9 ),S(M(KC_F9 )),\
  S(M(KC_F4 )),S(M(KC_F5 )),M(KC_F4 ),M(KC_F5 ),M(KC_F6 ),S(M(KC_F6 )),\
  S(M(KC_F1 )),S(M(KC_F2 )),M(KC_F1 ),M(KC_F2 ),M(KC_F3 ),S(M(KC_F3 )),\
  S(M(KC_F10)),S(M(KC_F11)),M(KC_F10),M(KC_F11),M(KC_F12),S(M(KC_F12))),

#define MC(kc)  LCTL(kc)
#define MA(kc)  LALT(kc)
#define MG(kc)  LGUI(kc)
#define MSC(kc) LSFT(LCTL(kc))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[LY_0000] = LAYOUT_ortho_4x12(
  KC_DEL,  KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, KC_K,  KC_R0_5,
  KC_BSPC, KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E, KC_I, KC_O,  KC_R1_5,
  KC_L2_0, KC_Z, KC_X, KC_C, KC_V, KC_B,
                                KC_M, KC_R2_1, KC_R2_2, KC_R2_3, KC_UP, KC_R2_5,
  KC_L3_0, KC_L3_1, KC_L3_2, KC_ESC, KC_PSCR, STICK,
                             KC_R3_0, KC_R3_1, KC_R3_2, KC_LEFT,KC_DOWN,KC_RIGHT
),
[LY_1000] = LAYOUT_gunp(
  XXXXXXX,   KC_PERC,   KC_QUES,   KC_EXLM,   KC_GRV,    XXXXXXX,
  XXXXXXX,   KC_AT,     KC_COMM,   KC_DOT,    KC_QUOT,   KC_EQL,
  KC_L2_0,   KC_DLR,    KC_SCLN,   KC_COLN,   KC_DQUO,   KC_UNDS,
  KC_L3_0,   KC_L3_1,   KC_L3_2,   XXXXXXX,   XXXXXXX,   XXXXXXX
),
[LY_0010] = LAYOUT_gunp(
  XXXXXXX,   KC_AMPR,   KC_PIPE,   KC_TILD,   KC_CIRC,   XXXXXXX,
  XXXXXXX,   KC_LCBR,   KC_LBRC,   KC_LPRN,   KC_LT,     KC_SLSH,
  KC_L2_0,   KC_RCBR,   KC_RBRC,   KC_RPRN,   KC_GT,     KC_BSLS,
  KC_L3_0,   KC_L3_1,   KC_L3_2,   XXXXXXX,   XXXXXXX,   XXXXXXX
),
[LY_1010] = LAYOUT_gunp(
  XXXXXXX,   KC_HASH,   KC_7,      KC_8,      KC_9,      XXXXXXX,
  XXXXXXX,   KC_ASTR,   KC_4,      KC_5,      KC_6,      KC_PLUS,
  KC_L2_0,   KC_0,      KC_1,      KC_2,      KC_3,      KC_MINS,
  KC_L3_0,   KC_L3_1,   KC_L3_2,   XXXXXXX,   XXXXXXX,   XXXXXXX
),
[LY_0100] = LAYOUT_gunp(
  XXXXXXX,   KC_SELECT,    KC_HOME,      KC_UP,      KC_END,       MC(KC_UP),
  XXXXXXX,   KC_PGUP,      KC_LEFT,      KC_DOWN,    KC_RGHT,      MC(KC_DOWN),
  XXXXXXX,   KC_PGDN,      MC(KC_S),     MC(KC_A),   MC(KC_Z),     MSC(KC_Z),
  XXXXXXX,   MC(KC_LEFT),  MC(KC_PGUP),  MC(KC_F),   MC(KC_PGDN),  MC(KC_RGHT)
),
[LY_1100] = LAYOUT_gunp(
  XXXXXXX,   KC_EXECUTE,   S(KC_HOME),   S(KC_UP),   S(KC_END),    MSC(KC_UP),
  XXXXXXX,   S(KC_PGUP),   S(KC_LEFT),   S(KC_DOWN), S(KC_RIGHT),  MSC(KC_DOWN),
  XXXXXXX,   S(KC_PGDN),   MC(KC_X),     MC(KC_C),   MC(KC_V),     MC(KC_L),
  XXXXXXX,   MSC(KC_LEFT), MSC(KC_PGUP), MC(KC_R),   MSC(KC_PGDN), MSC(KC_RIGHT)
),
[LY_0110] = F1_F12_LAYER()
[LY_1110] = F1_F12_LAYER(MG)
[LY_0001] = LAYOUT_gunp(
  KC_WFAV,       KC_BTN5,       KC_WH_L,       KC_MS_U,    KC_WH_R,    KC_WH_U,
  KC_ACL0,       XXXXXXX,       KC_MS_L,       KC_MS_D,    KC_MS_R,    KC_WH_D,
  KC_ACL1,       KC_BTN4,       KC_WBAK,       KC_WREF,    KC_WFWD,    KC_WSTP,
  KC_ACL2,       KC_BTN3,       KC_WHOM,       KC_WSCH,    KC_BTN1,    KC_BTN2
),
[LY_1111] = LAYOUT_gunp(
  OSM(MOD_RCTL), OSM(MOD_RALT), OSM(MOD_RGUI), KC_MSEL,    AU_OFF,     AU_ON,
  OSM(MOD_RSFT), XXXXXXX,       KC_VOLD,       KC_MUTE,    KC_VOLU,    KC_BRIU,
  OSM(MOD_LSFT), KC_INS,        KC_MPRV,       KC_MPLY,    KC_MNXT,    KC_BRID,
  OSM(MOD_LCTL), OSM(MOD_LALT), OSM(MOD_LGUI), KC_MSTP,    MY_NAME,    MY_EMAIL
),
[LY_1011] = LAYOUT_gunp(
  KC_SYSREQ, KC_SLCK,  OS_WIN,          OS_LINUX,     OS_OSX,          RESET,
  KC_WAKE,   KC_CLCK,  DYN_MACRO_PLAY1, RGB_MOD,      DYN_MACRO_PLAY2, DEBUG,
  KC_SLEP,   KC_NLCK,  THAI_IM_XKB,     RGB_TOG,      THAI_IM_UC,      EEP_RST,
  KC_PWR,    SANDBOX,  DYN_REC_START1,  DYN_REC_STOP, DYN_REC_START2,  KC_LOCK
),
[LY_0111] = UNUSED_LAYER
[LY_1101] = UNUSED_LAYER
// note when change: also update `LY_THAI_A`, `LY_THAI_B`, `LY_THAI_C` as well
[LY_1001] = LAYOUT_gunp(
  UC(L'ฌ'),  UC(L'ฅ'),  UC(L'ค'),  UC(L'ม'),  UC(L'ฤ'),  UC(L'ฦ'),
  UC(L'ณ'),  UC(L'ว'),  UC(L'ง'),  UC(L'น'),  UC(L'ร'),  UC(L'ล'),
  UC(L'ญ'),  UC(L'ธ'),  UC(L'ท'),  UC(L'ย'),  UC(L'ช'),  UC(L'ซ'),
  UC(L'ฒ'),  UC(L'ฆ'),  UC(L'ฑ'),  UC(L'ฬ'),  UC(L'พ'),  UC(L'ฟ')
),
[LY_0101] = LAYOUT_gunp(
  UC(L'์'),  UC(L'็'),  UC(L'่'),  UC(L'้'),  UC(L'๊'), UC(L'๋'),
  UC(L'โ'), UC(L'แ'), UC(L'เ'), UC(L'า'), UC(L'ั'), UC(L'ะ'),
  UC(L'ใ'), UC(L'ไ'), UC(L'ิ'),  UC(L'ี'),  UC(L'ึ'), UC(L'ื'),
  UC(L'ๅ'), UC(L'ฺ'),  UC(L'ํ'),  UC(L'ำ'), UC(L'ุ'), UC(L'ู')
),
[LY_0011] = LAYOUT_gunp(
  UC(L'ภ'),  UC(L'ฃ'),  UC(L'ข'),  UC(L'ฮ'),  UC(L'ฎ'),  UC(L'ฏ'),
  UC(L'ถ'),  UC(L'จ'),  UC(L'ก'),  UC(L'อ'),  UC(L'ด'),  UC(L'ต'),
  UC(L'ศ'),  UC(L'ษ'),  UC(L'ส'),  UC(L'ห'),  UC(L'บ'),  UC(L'ป'),
  UC(L'ฯ'),  UC(L'ๆ'),  UC(L'ฐ'),  UC(L'ฉ'),  UC(L'ผ'),  UC(L'ฝ')
),
/* mapping from US QWERTY to TH Kedmanee */
// note when change: also update `LY_0101`, `LY_0111`, `LY_0011` as well
[LY_THAI_A] = LAYOUT_gunp(
  S(KC_G),  KC_PIPE,  KC_8,     KC_COMM,  S(KC_A),  KC_QUES,
  S(KC_I),  KC_SCLN,  KC_QUOT,  KC_O,     KC_I,     KC_RBRC,
  S(KC_P),  S(KC_T),  KC_M,     KC_P,     KC_EQL,   KC_COLN,
  KC_LT,    S(KC_S),  S(KC_R),  KC_GT,    KC_R,     KC_A
),
[LY_THAI_B] = LAYOUT_gunp(
  S(KC_N),  S(KC_H),  KC_J,     KC_H,     S(KC_U),  S(KC_J),
  S(KC_F),  KC_C,     KC_G,     KC_K,     KC_Y,     KC_T,
  KC_DOT,   KC_W,     KC_B,     KC_U,     KC_7,     KC_N,
  KC_1,     S(KC_B),  S(KC_Y),  KC_E,     KC_6,     KC_CIRC
),
[LY_THAI_C] = LAYOUT_gunp(
  KC_4,     KC_BSLS,  KC_MINS,  S(KC_V),  S(KC_E),  S(KC_D),
  KC_5,     KC_0,     KC_D,     KC_V,     KC_F,     KC_9,
  S(KC_L),  S(KC_K),  KC_L,     KC_S,     KC_LBRC,  KC_X,
  S(KC_O),  KC_Q,     KC_LCBR,  S(KC_C),  KC_Z,     KC_SLSH
),
[LY_SANDBOX] = LAYOUT_ortho_4x12(
  KC_LCBR, KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, KC_K, KC_RCBR,
  KC_LBRC, KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E, KC_I, KC_O, KC_RBRC,
  KC_LPRN,KC_Z,KC_X,KC_C,KC_V,KC_B,KC_M,KC_COMM,KC_DOT,KC_SCLN,KC_COLN,KC_RPRN,
  KC_LT  , KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_GT
),
[LY_STICK] = UNUSED_LAYER // as a gateway to other persistant layers
};

#define NUM_LANGS 2
#define LANG_ENG  0
#define LANG_THAI 1

uint16_t cur_layer = LY_0000;
uint16_t cur_lang = LANG_ENG;
bool is_layer_persistant = false;
bool is_thai_using_im_xkb = true;

void change_layer(uint16_t new_layer) {
  if(cur_layer != new_layer) {
    layer_off(cur_layer);
    layer_on(new_layer);
    cur_layer = new_layer;
  }
}

void change_lang(uint16_t lang) {
  while(lang != cur_lang) {
    SEND_STRING(SS_LGUI(" "));
    cur_lang = (cur_lang + 1) % NUM_LANGS;
  }
}

void update_env_maybe_thai(void) {
  if(is_thai_using_im_xkb) {
    if(LY_THAI_A <= cur_layer && cur_layer <= LY_THAI_C) {
      change_lang(LANG_THAI);
    } else {
      change_lang(LANG_ENG);
    }
  } else {
    switch(cur_layer) {
      case LY_THAI_A: change_layer(LY_1001); break;
      case LY_THAI_B: change_layer(LY_0101); break;
      case LY_THAI_C: change_layer(LY_0011); break;
    }
  }
}

uint16_t get_persistant_layer_from_keycode(uint16_t keycode) {
  switch(keycode) {
    case THAI_A:    return LY_THAI_A;
    case THAI_B:    return LY_THAI_B;
    case THAI_C:    return LY_THAI_C;
    case FN_A:      return LY_1000;
    case FN_B:      return LY_1010;
    case FN_C:      return LY_0010;
    case FN_D:      return LY_0000;
    case MOTION_LY: return LY_0100;
    case MOUSE_LY:  return LY_0001;
    case MEDIA_LY:  return LY_1111;
  }
  return 0; // this line is unreachable but be here to make the complier happy
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if(!is_layer_persistant && FN_A <= keycode && keycode <= FN_D) {
    uint16_t mask = 1 << (3 - (keycode - FN_A));
    uint16_t cur_layer_code = cur_layer - LY_0000;
    if(!(LY_0000 <= cur_layer && cur_layer <= LY_1111))
      SEND_STRING("error: Planck Keyboard Panic!");
    if(!(cur_layer_code & mask) == record->event.pressed)
      change_layer((mask ^ cur_layer_code) + LY_0000);
    return false;
  }

  if(!(record->event.pressed))
    return !(MIN_KC <= keycode && keycode <= MAX_KC);

  switch(keycode) {
    case MY_NAME:  SEND_STRING("Gun Pinyo");          return false;
    case MY_EMAIL: SEND_STRING("gunpinyo@gmail.com"); return false;

    case SANDBOX:
    case STICK:
      change_layer(keycode == STICK ? LY_STICK : LY_SANDBOX);
      change_lang(LANG_ENG);
      is_layer_persistant = true;
      return false;

    case OS_LINUX: set_unicode_input_mode(UC_LNX);  return false;
    case OS_WIN:   set_unicode_input_mode(UC_WINC); return false;
    case OS_OSX:   set_unicode_input_mode(UC_OSX);  return false;

    case THAI_IM_XKB:
    case THAI_IM_UC:
      is_thai_using_im_xkb = keycode == THAI_IM_XKB;
      change_lang(LANG_ENG);
      return false;

    case FN_A:      case FN_B:     case FN_C:     case FN_D:
    case THAI_A:    case THAI_B:   case THAI_C:
    case MOTION_LY: case MOUSE_LY: case MEDIA_LY:
      if(is_layer_persistant) {
        change_layer(get_persistant_layer_from_keycode(keycode));
        update_env_maybe_thai();
        // `FN_D` will reset the layer configuration when `is_layer_persistant`
        is_layer_persistant = keycode != FN_D;
      }
      return false;
  }
  return true;
}

#ifdef RGB_MATRIX_ENABLE
  void rgb_matrix_indicators_kb(void) {
    // `42` is the index of the middle light at the bottom row (in planck light)
    // it is disabled because it does not have a cover, hence irritates my eyes
    rgb_matrix_set_color(42, 0, 0, 0);
  }
#endif

#ifdef AUDIO_ENABLE
  float tone_startup[][2]    = SONG(STARTUP_SOUND);
  float tone_goodbye[][2]    = SONG(GOODBYE_SOUND);

  float tone_ly_normal[][2]  = SONG(QWERTY_SOUND);
  float tone_ly_spacial[][2] = SONG(DVORAK_SOUND);

  float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
#endif

void startup_user() {
  /* _delay_ms(20); // get rid of tick */
  set_unicode_input_mode(UC_LNX);
#ifdef AUDIO_ENABLE
  PLAY_SONG(tone_startup);
#endif
}

void shutdown_user() {
#ifdef AUDIO_ENABLE
  PLAY_SONG(tone_goodbye);
  /* _delay_ms(150); */
  stop_all_notes();
#endif
}
