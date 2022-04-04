#include QMK_KEYBOARD_H
#include "features/caps_word.h"
#include "features/pointing.h"
#include <stdio.h>

#if (__has_include("features/secrets.h") && !defined(NO_SECRETS))
#include "features/secrets.h"
#else
static const char * const secrets[] = {
  "test1",
  "test2"
};
#endif

enum layers{
  _BASE,
  _MOUSE,
  _MISC,
  _NAV,
  _SYMBOLS,
  _WORDS
};

enum userspace_keycodes {
#ifndef NO_CHARYBDIS_KEYCODES
  SARCASM = CHARYBDIS_SAFE_RANGE,
#else
  SARCASM = SAFE_RANGE,
#endif // !NO_CHARYBDIS_KEYCODES
  KC_SECRET_1,
  KC_SECRET_2
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
  #define BACK_WORDS LT(_WORDS, KC_BACKSPACE)
  #define MISC_DEL LT(_MISC, KC_DELETE)
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
  #define AM_RITE LALT(LCTL(LSFT(KC_2)))
  #define AM_LEFT LALT(LCTL(LSFT(KC_1)))
  #define AM_CYCLE LSFT(LALT(LCTL(KC_SPC)))
  #define AM_CW LSFT(LALT(KC_J))
  #define AM_CCW LSFT(LALT(KC_K))

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

/* Google Meet */
  #define MUTE_MIC LGUI(KC_D)
  #define MUTE_CAM LGUI(KC_E)
  #define RAZ_HAND LCTL(LGUI(KC_H))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_charybdis_3x5(
    KC_Q   , KC_W   , KC_E    , KC_R    , KC_T       ,                    KC_Y      , KC_U      , KC_I      , KC_O   , KC_P     ,
    KC_CA  , KC_AS  , KC_GD   , KC_SF   , KC_G       ,                    KC_H      , KC_SJ     , KC_GK     , KC_AL  , KC_CSCLN ,
    NAV_Z  , KC_X   , KC_C    , KC_V    , KC_B       ,                    KC_N      , KC_M      , KC_COMM   , KC_DOT , SYM_SLSH ,
                      SYM_ENT , KC_NO   , BACK_WORDS ,                                MISC_DEL , NAV_SPACE
  ),

  [_MISC] = LAYOUT_charybdis_3x5(
    _______  , _______ , DESKTOP , _______ , _______ ,                    _______  , _______  , _______ , _______  , RESET    ,
    AM_LEFT  , DESK_L  , MISSION , DESK_R  , AM_RITE ,                    AM_CYCLE , AM_1     , AM_2    , AM_CCW   , _______  ,
    KC_LCTRL , _______ , _______ , _______ , _______ ,                    _______  , MS_BACK  , MS_FORE , TAB_BACK , TAB_FORE ,
                         _______ , KC_NO   , _______ ,                    _______  , _______
  ),

  [_MOUSE] = LAYOUT_charybdis_3x5(
    _______ , _______ , _______ , _______ , _______ ,                     _______ , _______ , _______ , _______ , _______ ,
    _______ , _______ , _______ , _______ , _______ ,                     _______ , _______ , _______ , _______ , _______ ,
    _______ , SNIPING , _______ , DRGSCRL , _______ ,                     _______ , _______ , _______ , _______ , _______ ,
                        L_CLICK , KC_NO   , R_CLICK ,                     _______ , _______
  ),

  [_NAV] = LAYOUT_charybdis_3x5(
    _______ , KC_F6   , ALT_U   , _______ , _______ ,                     GUI_L      , KC_HOME , KC_END     , GUI_R , _______ ,
    _______ , WEB_B   , ALT_D   , WEB_F   , _______ ,                     LEFT       , KC_DOWN , KC_UP      , RIGHT , _______ ,
    _______ , _______ , _______ , _______ , _______ ,                     ALT_L      , _______ , _______    , ALT_R , _______ ,
                        _______ , KC_NO   , _______ ,                     SCREEN_CAP , _______
  ),

  [_SYMBOLS] = LAYOUT_charybdis_3x5(
    KC_RCBR , KC_RBRC , R_PAREN , KC_GRAVE , _______ ,                    _______ , KC_7 , KC_8   , KC_9 , KC_EQL  ,
    KC_LCBR , KC_LBRC , L_PAREN , KC_TILDE , _______ ,                    _______ , KC_4 , KC_5   , KC_6 , KC_COLN ,
    KC_LSFT , CUT     , COPY    , PASTE    , _______ ,                    KC_RSFT , KC_1 , KC_2   , KC_3 , KC_BSLS ,
                        _______ , KC_NO    , _______ ,                    KC_DOT  , KC_0
  ),

  [_WORDS] = LAYOUT_charybdis_3x5(
    KC_SECRET_1 , KC_SECRET_2 , _______ , _______ , _______ ,                    _______ , _______ , _______ , _______ , SARCASM ,
    _______     , _______     , _______ , CAPS    , _______ ,                    _______ , _______ , _______ , _______ , _______ ,
    _______     , _______     , _______ , _______ , _______ ,                    _______ , _______ , _______ , _______ , _______ ,
                                _______ , KC_NO   , _______ ,                    _______ , _______
  ),

  /* [_TEMPLATE] = LAYOUT_charybdis_3x5( */
  /*   _______ , _______ , _______ , _______ , _______ ,                    _______ , _______ , _______ , _______ , _______ , */
  /*   _______ , _______ , _______ , _______ , _______ ,                    _______ , _______ , _______ , _______ , _______ , */
  /*   _______ , _______ , _______ , _______ , _______ ,                    _______ , _______ , _______ , _______ , _______ , */
  /*                       _______ , KC_NO   , _______ ,                    _______ , _______ */
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

#ifdef MOUSEKEY_ENABLE
static uint16_t mouse_timer           = 0;
static uint16_t mouse_debounce_timer  = 0;
static uint8_t  mouse_keycode_tracker = 0;
bool            tap_toggling = false, enable_acceleration = false;

#ifdef TAPPING_TERM_PER_KEY
#    define TAP_CHECK get_tapping_term(KC_BTN1, NULL)
#else
#    ifndef TAPPING_TERM
#        define TAPPING_TERM 200
#    endif
#    define TAP_CHECK TAPPING_TERM
#endif

__attribute__((weak)) report_mouse_t pointing_device_task_keymap(report_mouse_t mouse_report) {
    return mouse_report;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    int8_t x = mouse_report.x, y = mouse_report.y;
    mouse_report.x = 0;
    mouse_report.y = 0;

    if (x != 0 && y != 0) {
        mouse_timer = timer_read();
#ifdef OLED_ENABLE
        oled_timer = timer_read32();
#endif
        if (timer_elapsed(mouse_debounce_timer) > TAP_CHECK) {
            if (enable_acceleration) {
                x = (x > 0 ? x * x / 16 + x : -x * x / 16 + x);
                y = (y > 0 ? y * y / 16 + y : -y * y / 16 + y);
            }
            mouse_report.x = x;
            mouse_report.y = y;
            if (!layer_state_is(_MOUSE)) {
                layer_on(_MOUSE);
            }
        }
    } else if (timer_elapsed(mouse_timer) > 650 && layer_state_is(_MOUSE) && !mouse_keycode_tracker && !tap_toggling) {
        layer_off(_MOUSE);
    } else if (tap_toggling) {
        if (!layer_state_is(_MOUSE)) {
            layer_on(_MOUSE);
        }
    }

    return pointing_device_task_keymap(mouse_report);
}

bool process_record_pointing(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case TT(_MOUSE):
            if (record->event.pressed) {
                mouse_keycode_tracker++;
            } else {
#if TAPPING_TOGGLE != 0
                if (record->tap.count == TAPPING_TOGGLE) {
                    tap_toggling ^= 1;
#    if TAPPING_TOGGLE == 1
                    if (!tap_toggling) mouse_keycode_tracker -= record->tap.count + 1;
#    else
                    if (!tap_toggling) mouse_keycode_tracker -= record->tap.count;
#    endif
                } else {
                    mouse_keycode_tracker--;
                }
#endif
            }
            mouse_timer = timer_read();
            break;
        case TG(_MOUSE):
            if (record->event.pressed) {
                tap_toggling ^= 1;
            }
            break;
        case MO(_MOUSE):
#if defined(KEYBOARD_ploopy)
        case DPI_CONFIG:
#elif (defined(KEYBOARD_bastardkb_charybdis) || defined(KEYBOARD_handwired_tractyl_manuform)) && !defined(NO_CHARYBDIS_KEYCODES)
        case SAFE_RANGE ... (CHARYBDIS_SAFE_RANGE-1):
#endif
        case KC_MS_UP ... KC_MS_WH_RIGHT:
            record->event.pressed ? mouse_keycode_tracker++ : mouse_keycode_tracker--;
            mouse_timer = timer_read();
            break;
        case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX:
            break;
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            if (record->event.pressed || !record->tap.count) {
                break;
            }
        default:
            if (IS_NOEVENT(record->event)) break;
            if ((keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) && (((keycode >> 0x8) & 0xF) == _MOUSE)) {
                record->event.pressed ? mouse_keycode_tracker++ : mouse_keycode_tracker--;
                mouse_timer = timer_read();
                break;
            }
            if (layer_state_is(_MOUSE) && !mouse_keycode_tracker && !tap_toggling) {
                layer_off(_MOUSE);
            }
            mouse_keycode_tracker = 0;
            mouse_debounce_timer  = timer_read();
            break;
    }
    return true;
}
#endif

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
    case KC_SECRET_1 ... KC_SECRET_2: // Secrets!  Externally defined strings, not stored in repo
      if (!record->event.pressed) {
        send_string_with_delay(secrets[keycode - KC_SECRET_1], MACRO_TIMER);
      }
      return false;

    default:
      return true;
  }
}
