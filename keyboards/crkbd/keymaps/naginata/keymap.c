#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

// 薙刀式
#include "naginata.h"
NGKEYS naginata_keys;
// 薙刀式

void update_led(void);

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum keymap_layers {
  _QWERTY,
  _EUCALYN,
  _EUCALYNK,
// 薙刀式
  _NAGINATA, // 薙刀式入力レイヤー
  _NGEDITL, // 薙刀式編集レイヤー
  _NGEDITR, // 薙刀式編集レイヤー
// 薙刀式
  _LOWER,
  _RAISE,
  _ADJUST,
};

// 薙刀式
enum combo_events {
  NAGINATA_ON_CMB,
  // NAGINATA_OFF_CMB,
};

#if defined(EUCALYN) || defined(EUCALYNKAI)
const uint16_t PROGMEM ngon_combo[]  = {KC_G, KC_T, COMBO_END};
// const uint16_t PROGMEM ngoff_combo[] = {KC_I, KC_U, COMBO_END};
#else
const uint16_t PROGMEM ngon_combo[]  = {KC_H, KC_J, COMBO_END};
// const uint16_t PROGMEM ngoff_combo[] = {KC_F, KC_G, COMBO_END};
#endif

combo_t key_combos[COMBO_COUNT] = {
  [NAGINATA_ON_CMB]  = COMBO_ACTION(ngon_combo),
  // [NAGINATA_OFF_CMB] = COMBO_ACTION(ngoff_combo),
};

// IME ON/OFFのcombo
void process_combo_event(uint8_t combo_index, bool pressed) {
  switch(combo_index) {
    case NAGINATA_ON_CMB:
      if (pressed) {
        naginata_on();
        update_led();
      }
      break;
    // case NAGINATA_OFF_CMB:
    //   if (pressed) {
    //     naginata_off();
    //     update_led();
    //   }
    //   break;
  }
}
// 薙刀式

enum custom_keycodes {
  KC_QWERTY = NG_SAFE_RANGE,
  KC_EUCALYN,
  KC_EUCALYNK,
  KC_EISU,
  KC_LOWER,
  KC_RAISE,
  KC_ADJUST,
  KC_BACKLIT,
  KC_KANA2,
  KC_UNDGL,
  RGBRST
};

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
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
#define KC_GUITB GUI_T(KC_TAB)
#define KC_RESET RESET
#define KC_ABLS LALT(KC_BSLS)
#define KC_CMDENT  CMD_T(KC_ENT)
#define KC_SFTSPC  LSFT_T(KC_SPC)
#define KC_CTLSPC  CTL_T(KC_SPC)
#define KC_ALTSPC  ALT_T(KC_SPC)
#define KC_CTLBS   CTL_T(KC_BSPC)
#define KC_CTLENT  CTL_T(KC_ENT)
// 薙刀式
// 編集モードを追加する場合
#define KC_C(A) C(KC_##A)
#define KC_S(A) S(KC_##A)
#define KC_G(A) G(KC_##A)
// 薙刀式

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        TAB,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LCTL,     A,     S,     D,     F,     G,                      H,     J,     K,     L,  SCLN,  RALT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,     Z,     X,     C,     V,     B,                      N,     M,  COMM,   DOT,  SLSH,  RCMD,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LOWER,SFTSPC, CTLBS,   CMDENT,SFTSPC, RAISE \
                              //`--------------------'  `--------------------'
  ),

  [_EUCALYN] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        TAB,     Q,     W,  COMM,   DOT,  SCLN,                      M,     R,     D,     Y,     P,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LCTL,     A,     O,     E,     I,     U,                      G,     T,     K,     S,     N,  RALT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,     Z,     X,     C,     V,     F,                      B,     H,     J,     L,  SLSH,  RCMD,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LOWER,SFTSPC, CTLBS,   CMDENT,SFTSPC, RAISE \
                              //`--------------------'  `--------------------'
  ),

  [_EUCALYNK] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        TAB,     Q,     W,     M,     R,  LEFT,                   RGHT,  BSPC,     D,     Y,     P,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LCTL,     A,     O,     E,     I,     U,                      G,     T,     K,     S,     N,  RALT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,     Z,     X,     C,     V,     F,                      B,     H,     J,     L,  SLSH,  RCMD,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LOWER,SFTSPC, CTLBS,   CMDENT,SFTSPC, RAISE \
                              //`--------------------'  `--------------------'
  ),

// 薙刀式
  // デフォルトレイヤーに関係なくQWERTYで
  [_NAGINATA] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      _____,     Q,     W,     E,     R,  LEFT,                   RGHT,     U,     I,     O,     P, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,     A,     S,     D,     F,     G,                      H,     J,     K,     L,  SCLN, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,     Z,     X,     C,     V,     B,                      N,     M,  COMM,   DOT,  SLSH, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____,NGSHFT, _____,    _____,NGSHFT, _____ \
                              //`--------------------'  `--------------------'
  ),

  // 編集モードを追加する場合
  [_NGEDITL] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      _____,G(DOWN),G(UP), XXXXX, XXXXX, CHR10,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,  C(Y),  C(S),  PGDN,  PGUP, CHR20,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,  C(Z),  C(X),  C(C),  C(V), CHR30,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____,NGSHFT, _____,    _____,NGSHFT, _____ \
                              //`--------------------'  `--------------------'
  ),

  [_NGEDITR] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      _____, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                   HOME,G(DEL), XXXXX,   DEL,   ESC, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                  XXXXX,    UP, S(UP),   UP5,    F7, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                    END,  DOWN,S(DOWN),DOWN5,    F6, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____,NGSHFT, _____,    _____,NGSHFT, _____ \
                              //`--------------------'  `--------------------'
  ),
// 薙刀式

  [_LOWER] = LAYOUT_kc( \
  //+------+------+------+------+------+------+                +------+------+------+------+------+------+
  //             !      @      #      $      %                       :     /                           -
        ESC,  EXLM,    AT,  HASH,   DLR,  PERC,                   COLN,  SLSH,     7,     8,     9,  MINS, \
  //+------+------+------+------+------+------+                +------+------+------+------+------+------+
  //             ^      &      '      "     `                        ;     *                           +
      XXXXX,  CIRC,  AMPR,  QUOT,  DQUO,  GRV,                    SCLN,  ASTR,     4,     5,     6,  PLUS, \
  //+------+------+------+------+------+------+                +------+------+------+------+------+------+
  //             \      |      ~     _       ¥
      XXXXX,  ABLS,  PIPE,  TILD,  UNDS,  BSLS,                    EQL,   DOT,     1,     2,     3,     0, \
  //+------+------+------+------+------+------+------+  +------+------+------+------+------+------+------+
                                  LOWER, XXXXX, CTLBS,   CMDENT, XXXXX, RAISE \
  //                            +------+------+------+  +------+------+------+
  ),

  [_RAISE] = LAYOUT_kc( \
  //+------+------+------+------+------+------+                +------+------+------+------+------+------+
  //                           <      >
      _____, XXXXX, XXXXX,    LT,    GT, XXXXX,                  XXXXX,  PGUP,    UP, XXXXX,  PGUP,   DEL,\
  //+------+------+------+------+------+------+                +------+------+------+------+------+------+
  //             (      )      {      }
      XXXXX,  LPRN,  RPRN,  LCBR,  RCBR, XXXXX,                  XXXXX,  LEFT,  DOWN,  RGHT,  PGDN,  EISU,\
  //+------+------+------+------+------+------+                +------+------+------+------+------+------+
  //             [      ]
      XXXXX,  LBRC,  RBRC, XXXXX,  COMM, XXXXX,                  XXXXX,  PGDN, XXXXX, XXXXX, XXXXX, KANA2,\
  //+------+------+------+------+------+------+------+  +------+------+------+------+------+------+------+
                                  LOWER, XXXXX, CTLBS,   CMDENT, XXXXX, RAISE \
  //                            +------+------+------+  +------+------+------+
  ),

  [_ADJUST] = LAYOUT_kc( \
  //+------+------+------+------+------+------+                +------+------+------+------+------+------+
       LHUI,  LHUD,  WAKE, XXXXX, RESET, UNDGL,                   LTOG, XXXXX,  VOLU, XXXXX,  BRIU,QWERTY,\
  //+------+------+------+------+------+------+                +------+------+------+------+------+------+
       LSAI,  LSAD, XXXXX, XXXXX, XXXXX, XXXXX,                   LMOD,  MRWD,  VOLD,  MFFD,  BRID,EUCALYN,\
  //+------+------+------+------+------+------+                +------+------+------+------+------+------+
       LVAI,  LVAD,  SLEP, XXXXX, XXXXX, XXXXX,                   LRST, XXXXX,  MPLY, XXXXX, XXXXX,EUCALYNK,\
  //+------+------+------+------+------+------+------+  +------+------+------+------+------+------+------+
                                  LOWER, XXXXX, CTLBS,   CMDENT, XXXXX, RAISE \
  //                            +------+------+------+  +------+------+------+
  )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
  // 薙刀式
  set_naginata(_NAGINATA);
  #ifdef NAGINATA_EDIT_MODE
  set_naginata_edit(_NGEDITL, _NGEDITR);
  #endif
  // 薙刀式

  #ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
  #endif
  //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
  #ifdef SSD1306OLED
      iota_gfx_init(!has_usb());   // turns on the display
  #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

static bool underglow = false;

void update_led() {
  if (layer_state_is(_LOWER) && !isLeftHand) {
    // rgblight_setrgb_at(0, 0, 200, 7);
    rgblight_sethsv_at(200, 100, 255, 15);
    rgblight_sethsv_at(200, 100, 255, 16);
    rgblight_sethsv_at(200, 100, 255, 17);
    rgblight_sethsv_at(200, 100, 255, 18);
    rgblight_sethsv_at(200, 100, 255, 19);
    rgblight_sethsv_at(200, 100, 255, 20);
    rgblight_sethsv_at(200, 100, 255, 21);
    rgblight_sethsv_at(200, 100, 255, 22);
    rgblight_sethsv_at(200, 100, 255, 23);
  }
  if (layer_state_is(_RAISE) && !isLeftHand) {
    rgblight_sethsv_at(200, 100, 255, 11);
    rgblight_sethsv_at(200, 100, 255, 16);
    rgblight_sethsv_at(200, 100, 255, 17);
    rgblight_sethsv_at(200, 100, 255, 19);
  }
  if (!layer_state_is(_LOWER) && !layer_state_is(_RAISE)) {
    rgblight_sethsv_range(0, 0, 0, 6, 27);
  }
  if (naginata_state()) {
    rgblight_sethsv_at(200, 200, 255, 6);
    rgblight_sethsv_at(200, 200, 255, 13);
    rgblight_sethsv_at(200, 200, 255, 14);
  } else {
    rgblight_sethsv_at(0, 0, 0, 6);
    rgblight_sethsv_at(0, 0, 0, 13);
    rgblight_sethsv_at(0, 0, 0, 14);
  }
  if (underglow) {
    rgblight_sethsv_range(200, 200, 255, 0, 6);
  } else {
    rgblight_sethsv_range(200, 200, 0, 0, 6);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case KC_UNDGL:
      if (record->event.pressed) {
        underglow = !underglow;
      }
      update_led();
      return false;
      break;
    case KC_QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case KC_EUCALYN:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_EUCALYN);
      }
      return false;
      break;
    case KC_EUCALYNK:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_EUCALYNK);
      }
      return false;
      break;
    case KC_EISU:
      if (record->event.pressed) {
        // 薙刀式
        naginata_off();
        // 薙刀式
        update_led();
      }
      return false;
      break;
    case KC_KANA2:
      if (record->event.pressed) {
        // 薙刀式
        naginata_on();
        // 薙刀式
        update_led();
      }
      return false;
      break;
    case KC_ADJUST:
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
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
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
      return false;
      break;
    case KC_LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      update_tri_layer(_LOWER, _RAISE, _ADJUST);
      update_led();
      return false;
      break;
    case KC_RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      update_tri_layer(_LOWER, _RAISE, _ADJUST);
      update_led();
      return false;
      break;
  }

  // 薙刀式
  bool a = true;
  if (naginata_state()) {
    naginata_mode(keycode, record);
    a = process_naginata(keycode, record);
    update_led();
  }
  #ifdef NAGINATA_EDIT_MODE
    bool b = process_naginata_edit(keycode, record);
    return a & b;
  #else
    return a;
  #endif
  return true;
  // 薙刀式
}
