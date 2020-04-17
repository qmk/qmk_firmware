#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
  LOWER = SAFE_RANGE,
  RAISE,
  ADJUST,
  RGBRST
};


#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_RST   RESET
#define KC_LRST  RGBRST
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LMOD  RGB_MOD
#define KC_CTLTB CTL_T(KC_TAB)
#define KC_SFIME SFT_T(KC_ZKHK)
#define KC_LOWDL LT(_LOWER, KC_DEL)
#define KC_RAIBS LT(_RAISE, KC_BSPC)
#define KC_ADJST MO(_ADJUST)
#define KC_ALTHN ALT_T(KC_HENK)
#define KC_GUIMH GUI_T(KC_MHEN)
#define KC_SWAP  AG_SWAP
#define KC_NORM  AG_NORM
#define KC_DTR   SGUI(KC_RIGHT)
#define KC_DTL   SGUI(KC_LEFT)
#define KC_SCRS  LGUI(KC_PSCR)
#define KC_RESET RESET

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc( \
  //,-----------------------------------------.         ,-----------------------------------------.
        ESC,     Q,     W,     E,     R,     T,               Y,     U,     I,     O,     P,  BSPC,\
  //|------+------+------+------+------+------|         |------+------+------+------+------+------|
      CTLTB,     A,     S,     D,     F,     G,               H,     J,     K,     L,  MINS,  QUOT,\
  //|------+------+------+------+------+------|         |------+------+------+------+------+------|
      ADJST,     Z,     X,     C,     V,     B,               N,     M,  COMM,   DOT,  SLSH,    RO,\
  //|------+------+------+------+------+------|         |------+------+------+------+------+------|
      SFIME,                      LOWDL, GUIMH,           ALTHN, RAIBS,                       LSFT,\
  //|------+------+------+------+------+------|         |------+------+------+------+------+------|
                                    SPC,                           ENT
  //`-----------------------------------------'         `-----------------------------------------'
  ),
  [_LOWER] = LAYOUT_kc( \
  //,-----------------------------------------.         ,-----------------------------------------.
       TRNS,  PSCR,  SCRS,   INS,  CAPS,  TRNS,            MAIL,  WSCH,  TRNS,  TRNS,  TRNS,  TRNS,\
  //|------+------+------+------+------+------|         |------+------+------+------+------+------|
       TRNS,  MUTE,  LEFT,    UP, RIGHT,  PGUP,              F1,    F2,    F3,    F4,    F5,    F6,\
  //|------+------+------+------+------+------|         |------+------+------+------+------+------|
       TRNS,   DTL,  HOME,  DOWN,   END,  PGDN,              F7,    F8,    F9,   F10,   F11,   F12,\
  //|------+------+------+------+------+------|         |------+------+------+------+------+------|
       TRNS,                       TRNS,  TRNS,            TRNS,  TRNS,                       TRNS,\
  //|------+------+------+------+------+------|         |------+------+------+------+------+------|
                                   TRNS,                          TRNS
  //`-----------------------------------------'         `-----------------------------------------'
  ),
  [_RAISE] = LAYOUT_kc( \
  //,-----------------------------------------.         ,-----------------------------------------.
       TRNS,  EXLM,    AT,  HASH,   DLR,  PERC,            PDOT,     7,     8,     9,  PPLS,  TRNS,\
  //|------+------+------+------+------+------|         |------+------+------+------+------+------|
       TRNS,  RBRC,  LABK,  ASTR,  SCLN,  LBRC,            PSLS,     4,     5,     6,  PMNS,  PDOT,\
  //|------+------+------+------+------+------|         |------+------+------+------+------+------|
       TRNS,  BSLS,  RABK,  LPRN,  JYEN,   EQL,            PAST,     1,     2,     3,     0,  COMM,\
  //|------+------+------+------+------+------|         |------+------+------+------+------+------|
       TRNS,                       TRNS,  TRNS,            TRNS,  TRNS,                       TRNS,\
  //|------+------+------+------+------+------|         |------+------+------+------+------+------|
                                   TRNS,                          TRNS
  //`-----------------------------------------'         `-----------------------------------------'
  ),
  [_ADJUST] = LAYOUT_kc( \
  //,-----------------------------------------.         ,-----------------------------------------.
       TRNS,  LRST,  LTOG,  LMOD, RESET, XXXXX,           XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|         |------+------+------+------+------+------|
       TRNS,  LHUI,  LSAI,  LVAI,  SWAP, XXXXX,           XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|         |------+------+------+------+------+------|
       TRNS,  LHUD,  LSAD,  LVAD,  NORM, XXXXX,           XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|         |------+------+------+------+------+------|
       TRNS,                       TRNS,  TRNS,            TRNS,  TRNS,                       TRNS,\
  //|------+------+------+------+------+------|         |------+------+------+------+------+------|
                                   TRNS,                          TRNS
  //`-----------------------------------------'         `-----------------------------------------'
  )
};

int RGB_current_mode;

void keyboard_post_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_get_mode();
    #endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    // set_timelog();
  }

  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_get_mode();
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_get_mode();
        }
      #endif
      break;
  }
  return true;
}

#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    }

    return rotation;
}

void oled_task_user(void) {
  void render_status(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("LOWER\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("RAISE\n"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("ADJUST\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
  }


  void render_logo(void) {
      static const char PROGMEM qmk_logo[] = {
          0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
          0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
          0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
      };

      oled_write_P(qmk_logo, false);
  }

    if (is_keyboard_master()) {
        render_status();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_logo();  // Renders a static logo
    }
}
#endif
