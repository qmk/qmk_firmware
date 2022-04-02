#include QMK_KEYBOARD_H
#include "features/caps_word.h"
#include <stdio.h>

char wpm_str[10];

enum layers{
  _BASE,
  _MOUSE,
  _MISC,
  _NAV,
  _SYMBOLS,
};

enum custom_keycodes {
  _DUMMY = SAFE_RANGE,
  SARCASM
};

/* Homerow mod tap */
  #define KC_CA LCTL_T(KC_A)
  #define KC_AS LALT_T(KC_S)
  #define KC_GD LGUI_T(KC_D)
  #define KC_SF LSFT_T(KC_F)
  #define KC_SJ RSFT_T(KC_J)
  #define KC_GK RGUI_T(KC_K)
  #define KC_AL RALT_T(KC_L)
  #define KC_CSCLN RCTL_T(KC_SCLN)

/* Layer Tap */
  #define CAPS_MOUSE LT(_MOUSE, KC_CAPSLOCK)
  #define MISC_DASH LT(_MISC, KC_MINUS)
  #define NAV_SPACE LT(_NAV, KC_SPC)
  #define NAV_Z LT(_NAV, KC_Z)
  #define SYM_ENT LT(_SYMBOLS, KC_ENT)
  #define SYM_SLSH LT(_SYMBOLS, KC_SLSH)

/* Abbreviations */
  #define CAPS KC_CAPSLOCK
  #define DEL KC_DELETE
  #define L_PAREN KC_LEFT_PAREN
  #define LEFT KC_LEFT
  #define R_PAREN KC_RIGHT_PAREN
  #define RIGHT KC_RIGHT

/* TEXT NAV */
  #define ALT_L RALT(KC_LEFT)
  #define ALT_R RALT(KC_RIGHT)
  #define GUI_L RGUI(KC_LEFT)
  #define GUI_R RGUI(KC_RIGHT)
  #define GUI_BSPC RGUI(KC_BSPC)

/* APP nav */
  #define ALT_D RALT(KC_DOWN)
  #define ALT_U RALT(KC_UP)
  #define WEB_B RGUI(KC_LBRC)
  #define WEB_F RGUI(KC_RBRC)

/* Shortcuts */
  #define SCREEN_CAP LSFT(LGUI(KC_4))
  #define SCRN_BRIT KC_F15
  #define SCRN_DARK KC_F14
  #define COPY LGUI(KC_C)
  #define CUT LGUI(KC_X)
  #define PASTE LGUI(KC_V)

/* Mission Control */
  #define DESK_L RCTL(KC_LEFT)
  #define DESK_R RCTL(KC_RIGHT)
  #define DESKTOP KC_F11
  #define MISSION RCTL(KC_UP)
/* Amethyst */
  #define AM_1 KC_F4
  #define AM_2 KC_F2

/* MOUSE */
  #define L_CLICK KC_MS_BTN1
  #define R_CLICK KC_MS_BTN2
  /* These are mapped in SteerMouse */
  #define MS_BACK KC_MS_BTN4
  #define MS_FORE KC_MS_BTN5

  #define TAB_BACK LCTL(LSFT(KC_TAB))
  #define TAB_FORE LCTL(KC_TAB)

/* Audio */
  #define VOL_D KC_AUDIO_VOL_DOWN
  #define VOL_U KC_AUDIO_VOL_UP
  #define MUTE KC_AUDIO_MUTE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_Q   , KC_W  , KC_E       , KC_R  , KC_T ,  MUTE , KC_Y , KC_U  , KC_I      , KC_O   , KC_P      ,
    KC_CA  , KC_AS , KC_GD      , KC_SF , KC_G ,         KC_H , KC_SJ , KC_GK     , KC_AL  , KC_CSCLN  ,
    NAV_Z  , KC_X  , KC_C       , KC_V  , KC_B ,         KC_N , KC_M  , KC_COMM   , KC_DOT , SYM_SLSH ,
                     CAPS_MOUSE ,    SYM_ENT   ,           NAV_SPACE  , MISC_DASH
  ),

#ifdef RGB_MATRIX_ENABLE
  [_MISC] = LAYOUT(
    RGB_MOD  , RGB_VAI , RGB_HUI , RGB_SAI , DEBUG   , RGB_TOG , _______ , _______   , _______   , _______ , SARCASM ,
    RGB_RMOD , RGB_VAD , RGB_HUD , RGB_SAD , _______ ,           _______ , VOL_D     , VOL_U     , MUTE    , _______ ,
    _______  , _______ , _______ , _______ , RESET   ,           _______ , SCRN_DARK , SCRN_BRIT , _______ , _______ ,
                         _______ ,      _______      ,                _______        , _______
  ),
#else
  [_MISC] = LAYOUT(
    _______ , _______ , DESKTOP , _______ , DEBUG   , _______ , _______ , _______ , _______ , _______ , SARCASM ,
    _______ , DESK_L  , MISSION , DESK_R  , _______ ,           _______ , VOL_D   , VOL_U   , MUTE    , _______ ,
    _______ , _______ , _______ , _______ , RESET   ,           _______ , _______ , _______ , _______ , _______ ,
                        _______ ,      _______      ,                _______      , _______
  ),
#endif

  [_MOUSE] = LAYOUT(
    MS_BACK  , MS_FORE  , _______ , KC_ACL2 ,  _______ , _______ , _______    , AM_1       , AM_2     , _______     , _______ ,
    TAB_BACK , TAB_FORE , _______ , KC_ACL1 ,  _______ ,           KC_MS_LEFT , KC_MS_DOWN , KC_MS_UP , KC_MS_RIGHT , _______ ,
    _______  , _______  , _______ , KC_ACL0 ,  _______ ,           KC_LGUI    , KC_LSFT    , _______  , _______     , _______ ,
                          _______ ,      KC_ACL2       ,                   L_CLICK         , R_CLICK
  ),

  [_NAV] = LAYOUT(
    _______ , KC_F6   , ALT_U   , _______ , _______ , _______ , GUI_L , KC_HOME , KC_END     , GUI_R , _______ ,
    _______ , WEB_B   , ALT_D   , WEB_F   , _______ ,           LEFT  , KC_DOWN , KC_UP      , RIGHT , _______ ,
    _______ , _______ , _______ , _______ , _______ ,           ALT_L , _______ , _______    , ALT_R , _______ ,
                        _______ ,     _______       ,               _______     , SCREEN_CAP
  ),

  [_SYMBOLS] = LAYOUT(
    KC_RCBR , KC_RBRC , R_PAREN , KC_GRAVE , _______ , _______ , _______ , KC_7 , KC_8   , KC_9 , KC_EQL  ,
    KC_LCBR , KC_LBRC , L_PAREN , KC_TILDE , _______ ,           _______ , KC_4 , KC_5   , KC_6 , KC_COLN ,
    KC_LSFT , CUT     , COPY    , PASTE    , _______ ,           KC_RSFT , KC_1 , KC_2   , KC_3 , KC_BSLS ,
                        _______ ,       _______      ,                 KC_0     , KC_DOT
  ),

  /* [_TEMPLATE] = LAYOUT( */
    /* _______ , _______ , _______ , _______ ,  _______ , _______ , _______ , _______ , _______ , _______ , _______ , */
  /*   _______ , _______ , _______ , _______ ,  _______ ,           _______ , _______ , _______ , _______ , _______ , */
  /*   _______ , _______ , _______ , _______ ,  _______ ,           _______ , _______ , _______ , _______ , _______ , */
  /*                       _______ ,      _______       ,                _______      , _______ */
  /* ), */
};

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) {
    if (IS_LAYER_ON(_NAV)) {
      if (clockwise) {
        tap_code(KC_MS_WH_UP);
      } else {
        tap_code(KC_MS_WH_DOWN);
     }
    } else if (IS_LAYER_ON(_SYMBOLS)) {
      if (clockwise) {
        tap_code(KC_MS_WH_LEFT);
      } else {
        tap_code(KC_MS_WH_RIGHT);
     }
    } else if (IS_LAYER_ON(_MISC)){
      if (clockwise) {
        tap_code(KC_NO);
      } else {
        tap_code(KC_NO);
     }
    } else {
      if (clockwise) {
        tap_code(KC_VOLU);
      } else {
        tap_code(KC_VOLD);
      }
   }
  }
  return true;
}
#endif

#ifdef TAPPING_TERM_PER_KEY
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_F):
           return TAPPING_TERM - 100;
        case RSFT_T(KC_J):
            return TAPPING_TERM - 100;
        case LT(_SYMBOLS, KC_ENT):
            return TAPPING_TERM - 75;
        case LT(_NAV, KC_SPC):
            return TAPPING_TERM - 75;
        default:
           return TAPPING_TERM;
    }
}
#endif

#ifdef COMBO_ENABLE
enum combo_events {
  COMBO_ALFRED,
  COMBO_AMPERSAND,
  COMBO_BSPC,
  COMBO_WORD_CAPS,
  COMBO_DASH,
  COMBO_DBL_QUOT,
  COMBO_DEL,
  COMBO_ESC,
  COMBO_L_CURLY_BRACE,
  COMBO_L_PAREN,
  COMBO_L_SQR_BRACK,
  COMBO_NUMBAK,
  COMBO_QUOT,
  COMBO_R_CURLY_BRACE,
  COMBO_R_PAREN,
  COMBO_R_SQR_BRACK,
  COMBO_TAB,
  COMBO_TERMINAL,
  COMBO_UNDERSCORE,
  COMBO_LENGTH
};

uint16_t COMBO_LEN = COMBO_LENGTH;
const uint16_t PROGMEM combo_alfred[] = {NAV_SPACE, SYM_ENT, COMBO_END};
const uint16_t PROGMEM combo_ampersand[] = {KC_I, KC_U, COMBO_END};
const uint16_t PROGMEM combo_bspc[] = {KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM combo_wcaps[] = {KC_SF, KC_SJ, COMBO_END};
const uint16_t PROGMEM combo_dash[] = {KC_DOT, SYM_SLSH, COMBO_END};
const uint16_t PROGMEM combo_del[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM combo_dub_quot[] = {KC_AL, KC_GK, COMBO_END};
const uint16_t PROGMEM combo_esc[] = {KC_CA, KC_AS, COMBO_END};
const uint16_t PROGMEM combo_l_curly[] = {KC_V, KC_B, COMBO_END};
const uint16_t PROGMEM combo_l_paren[] = {KC_G, KC_SF, COMBO_END};
const uint16_t PROGMEM combo_l_sqr_brack[] = {KC_R, KC_T, COMBO_END};
const uint16_t PROGMEM combo_numbak[] = {KC_EQL, KC_9, COMBO_END};
const uint16_t PROGMEM combo_quot[] = {KC_AL, KC_CSCLN, COMBO_END};
const uint16_t PROGMEM combo_r_curly[] = {KC_N, KC_M, COMBO_END};
const uint16_t PROGMEM combo_r_paren[] = {KC_H, KC_SJ, COMBO_END};
const uint16_t PROGMEM combo_r_sqr_brack[] = {KC_Y, KC_U, COMBO_END};
const uint16_t PROGMEM combo_tab[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM combo_terminal[] = {KC_SF, KC_GD, COMBO_END};
const uint16_t PROGMEM combo_unds[] = {KC_DOT, KC_COMM, COMBO_END};

combo_t key_combos[] = {
  [COMBO_ALFRED] = COMBO(combo_alfred, LGUI(KC_SPC)),
  [COMBO_AMPERSAND] = COMBO(combo_ampersand, KC_AMPERSAND),
  [COMBO_BSPC] = COMBO(combo_bspc,KC_BSPC),
  [COMBO_WORD_CAPS] = COMBO_ACTION(combo_wcaps),
  [COMBO_DASH] = COMBO(combo_dash, KC_MINUS),
  [COMBO_DBL_QUOT] = COMBO(combo_dub_quot, KC_DOUBLE_QUOTE),
  [COMBO_DEL] = COMBO(combo_del,KC_DEL),
  [COMBO_ESC] = COMBO(combo_esc,KC_ESC),
  [COMBO_L_CURLY_BRACE] = COMBO(combo_l_curly, KC_LCBR),
  [COMBO_L_PAREN] = COMBO(combo_l_paren, KC_LEFT_PAREN),
  [COMBO_L_SQR_BRACK] = COMBO(combo_l_sqr_brack, KC_LBRC),
  [COMBO_NUMBAK] = COMBO(combo_numbak,KC_BSPC),
  [COMBO_QUOT] = COMBO(combo_quot, KC_QUOT),
  [COMBO_R_CURLY_BRACE] = COMBO(combo_r_curly, KC_RCBR),
  [COMBO_R_PAREN] = COMBO(combo_r_paren, KC_RIGHT_PAREN),
  [COMBO_R_SQR_BRACK] = COMBO(combo_r_sqr_brack, KC_RBRC),
  [COMBO_TAB] = COMBO(combo_tab,KC_TAB),
  [COMBO_TERMINAL] = COMBO(combo_terminal, KC_NUMLOCK),
  [COMBO_UNDERSCORE] = COMBO(combo_unds, KC_UNDS)
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case COMBO_WORD_CAPS:
      if (pressed) {
        caps_word_set(true);
      }
      break;
  }
}
#endif

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return OLED_ROTATION_90;
}

void render_lechiffre_logo(void) {
  static const char PROGMEM lechiffre_logo[] = {
  // 'lechiffre_logo', 32x20px
   0x00, 0x3e, 0x20, 0x20, 0x00, 0x18, 0x2c, 0xa8, 0x80, 0x00, 0x1c, 0x22, 0x22, 0x00, 0x3e, 0x08,
0x30, 0x00, 0x34, 0x00, 0x3c, 0x0a, 0x00, 0xbc, 0x8a, 0x00, 0x38, 0x08, 0x00, 0x18, 0x2c, 0x28,
0x00, 0xb6, 0xb6, 0x00, 0xdb, 0xdb, 0x00, 0x6d, 0x6d, 0x00, 0xdb, 0xdb, 0x00, 0xdb, 0xdb, 0x00,
0x00, 0xdb, 0xdb, 0x00, 0xdb, 0xdb, 0x00, 0x6d, 0x6d, 0x00, 0xdb, 0xdb, 0x00, 0xb6, 0xb6, 0x00,
0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x06, 0x06, 0x06, 0x00, 0x06, 0x06, 0x06, 0x06, 0x06, 0x00,
0x00, 0x06, 0x06, 0x06, 0x06, 0x06, 0x00, 0x06, 0x06, 0x06, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00
};

  oled_write_raw_P(lechiffre_logo, sizeof(lechiffre_logo));
}

static void render_layer_status(void) {
  oled_write_ln_P(PSTR(" "), false);
  switch (get_highest_layer(layer_state)) {
    case _BASE:
      oled_write_P(PSTR("BASIC"), false);
      break;
    case _SYMBOLS:
      oled_write_P(PSTR("SYMBL"), false);
      break;
    case _NAV:
      oled_write_P(PSTR("NAVIG"), false);
      break;
    case _MISC:
      oled_write_P(PSTR("MISCL"), false);
      break;
    case _MOUSE:
      oled_write_P(PSTR("MOUSE"), false);
      break;
    default:
      oled_write_P(PSTR("?????"), false);
    }
}

void render_keylock_status(led_t led_state) {
  oled_write_ln_P(PSTR(" "), false);
  oled_write_P(PSTR("W "), caps_word_get());
  oled_write_P(PSTR("CAP"), (caps_word_get() || led_state.caps_lock));
}

void render_mod_status(uint8_t modifiers) {
  static const char PROGMEM gui_off_1[] = {0x85, 0x86, 0};
  static const char PROGMEM gui_off_2[] = {0xa5, 0xa6, 0};
  static const char PROGMEM gui_on_1[] = {0x8d, 0x8e, 0};
  static const char PROGMEM gui_on_2[] = {0xad, 0xae, 0};

  static const char PROGMEM alt_off_1[] = {0x87, 0x88, 0};
  static const char PROGMEM alt_off_2[] = {0xa7, 0xa8, 0};
  static const char PROGMEM alt_on_1[] = {0x8f, 0x90, 0};
  static const char PROGMEM alt_on_2[] = {0xaf, 0xb0, 0};

  static const char PROGMEM ctrl_off_1[] = {0x89, 0x8a, 0};
  static const char PROGMEM ctrl_off_2[] = {0xa9, 0xaa, 0};
  static const char PROGMEM ctrl_on_1[] = {0x91, 0x92, 0};
  static const char PROGMEM ctrl_on_2[] = {0xb1, 0xb2, 0};

  static const char PROGMEM shift_off_1[] = {0x8b, 0x8c, 0};
  static const char PROGMEM shift_off_2[] = {0xab, 0xac, 0};
  static const char PROGMEM shift_on_1[] = {0xcd, 0xce, 0};
  static const char PROGMEM shift_on_2[] = {0xcf, 0xd0, 0};

  // fillers between the modifier icons bleed into the icon frames
  static const char PROGMEM off_off_1[] = {0xc5, 0};
  static const char PROGMEM off_off_2[] = {0xc6, 0};
  static const char PROGMEM on_off_1[] = {0xc7, 0};
  static const char PROGMEM on_off_2[] = {0xc8, 0};
  static const char PROGMEM off_on_1[] = {0xc9, 0};
  static const char PROGMEM off_on_2[] = {0xca, 0};
  static const char PROGMEM on_on_1[] = {0xcb, 0};
  static const char PROGMEM on_on_2[] = {0xcc, 0};

  oled_write_ln_P(PSTR(" "), false);

  if(modifiers & MOD_MASK_CTRL) {
      oled_write_P(ctrl_on_1, false);
  } else {
      oled_write_P(ctrl_off_1, false);
  }

  if ((modifiers & MOD_MASK_CTRL) && (modifiers & MOD_MASK_SHIFT)) {
      oled_write_P(on_on_1, false);
  } else if(modifiers & MOD_MASK_CTRL) {
      oled_write_P(on_off_1, false);
  } else if(modifiers & MOD_MASK_SHIFT) {
      oled_write_P(off_on_1, false);
  } else {
      oled_write_P(off_off_1, false);
  }

  if(modifiers & MOD_MASK_SHIFT) {
      oled_write_P(shift_on_1, false);
  } else {
      oled_write_P(shift_off_1, false);
  }

  if(modifiers & MOD_MASK_CTRL) {
      oled_write_P(ctrl_on_2, false);
  } else {
      oled_write_P(ctrl_off_2, false);
  }

  if (modifiers & MOD_MASK_CTRL & MOD_MASK_SHIFT) {
      oled_write_P(on_on_2, false);
  } else if(modifiers & MOD_MASK_CTRL) {
      oled_write_P(on_off_2, false);
  } else if(modifiers & MOD_MASK_SHIFT) {
      oled_write_P(off_on_2, false);
  } else {
      oled_write_P(off_off_2, false);
  }

  if(modifiers & MOD_MASK_SHIFT) {
      oled_write_P(shift_on_2, false);
  } else {
      oled_write_P(shift_off_2, false);
  }

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

static void render_wpm(void) {
  oled_write_ln_P(PSTR(" "), false);
  sprintf(wpm_str, " %03d", get_current_wpm());
  oled_write(wpm_str, false);
}

void oled_task_user(void) {
  render_lechiffre_logo();
  oled_set_cursor(0,3);
  render_layer_status();
  render_mod_status(get_mods()|get_oneshot_mods());
  render_keylock_status(host_keyboard_led_state());
  render_wpm();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_caps_word(keycode, record)) { return false; }

  static bool tAuNtTeXt = false;

  if (tAuNtTeXt) {
    if (record->event.pressed) {
      if (keycode != KC_SPC) {
        tap_code(KC_CAPS);
      }
    }
  }

  switch (keycode) {
    case SARCASM:
      if (record->event.pressed) {
        tAuNtTeXt = !tAuNtTeXt;
        if (tAuNtTeXt) {
          tap_code(KC_CAPS);
        }
        else if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
          tap_code(KC_CAPS);
        }
      }
      return false;

    default:
      return true;
  }
}
#endif
