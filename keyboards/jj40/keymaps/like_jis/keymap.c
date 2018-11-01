#include QMK_KEYBOARD_H

#define _QWERTY 0
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 16

enum custom_keycodes {
  LOWER = SAFE_RANGE,
  RAISE,
  ADJUST,
  RGBRST
};

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_KANJI KC_GRV

#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_ADJST ADJUST

#define KC_RST   RESET

#define KC_LRST  RGBRST
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LSMOD RGB_SMOD
#define KC_BTOG  BL_TOGG
#define KC_BINC  BL_INC
#define KC_BDEC  BL_DEC
// #define KC_BRTG  BL_BRTG

#define KC_KNRM  AG_NORM
#define KC_KSWP  AG_SWAP

// Layer Mode aliases
// #define KC_L_LO  MO(_LOWER)
// #define KC_L_RA  MO(_RAISE)
// #define KC_L_AD  MO(_ADJUST)
#define KC_TBSF  LSFT_T(KC_TAB)
// #define KC_SPSF  LSFT_T(KC_SPC)
// #define KC_GUAP  LALT_T(KC_APP)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = KC_LAYOUT_ortho_4x12( \
  //,-----------------------------------------------------------------------------------.
        ESC,     Q,     W,     E,     R,     T,     Y,     U,     I,     O,     P,  MINS,\
  //|------+------+------+------+------+------|------+------+------+------+------+------|
       TBSF,     A,     S,     D,     F,     G,     H,     J,     K,     L,  SCLN,   ENT,\
  //|------+------+------+------+------+------|------+------+------+------+------+------|
       LSFT,     Z,     X,     C,     V,     B,     N,     M,  COMM,   DOT,    UP,  RSFT,\
  //|------+------+------+------+------+------|------+------+------+------+------+------|
      LCTRL,  LALT,  LGUI, ADJST, LOWER,  BSPC,   SPC, RAISE,   APP,  LEFT,  DOWN,  RGHT \
  //|------+------+------+------+------+-------------+------+------+------+------+------|
  ),

  [_LOWER] = KC_LAYOUT_ortho_4x12( \
  //,-----------------------------------------------------------------------------------.
        TAB,    F1,    F2,    F3,    F4,    F5, XXXXX,  MINS,   EQL,  JYEN,  LBRC,  RBRC,\
  //|------+------+------+------+------+------|------+------+------+------+------+------|
      _____,    F6,    F7,    F8,    F9,   F10, XXXXX, XXXXX, XXXXX,  SCLN,  QUOT,  BSLS,\
  //|------+------+------+------+------+------|------+------+------+------+------+------|
      _____,   F11,   F12, XXXXX, KANJI,   ENT, XXXXX, XXXXX,  COMM,   DOT,  SLSH,    RO,\
  //|------+------+------+------+------+-------------+------+------+------+------+------|
      _____, _____, _____, _____, _____,   DEL, _____, _____, _____, _____, _____, _____ \
  //|------+------+------+------+------+-------------+------+------+------+------+------|
  ),

  [_RAISE] = KC_LAYOUT_ortho_4x12( \
  //,-----------------------------------------------------------------------------------.
      _____,     1,     2,     3,     4,     5,     6,     7,     8,     9,     0,  MINS,\
  //|------+------+------+------+------+------|------+------+------+------+------+------|
      _____, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,     4,     5,     6,  QUOT,  PLUS,\
  //|------+------+------+------+------+------|------+------+------+------+------+------|
      _____, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,     0,     1,     2,     3,   DOT,  SLSH,\
  //|------+------+------+------+------+-------------+------+------+------+------+------|
      _____, _____, _____, _____, _____,  BSPC, _____, _____, _____, _____, _____, _____ \
  //|------+------+------+------+------+-------------+------+------+------+------+------|
  ),

  [_ADJUST] = KC_LAYOUT_ortho_4x12( \
  //,-----------------------------------------------------------------------------------.
      XXXXX,   RST,  LRST,  KNRM,  KSWP, XXXXX, XXXXX,  WH_L,  WH_U,  HOME,  PGUP, XXXXX,\
  //|------+------+------+------+------+------|------+------+------+------+------+------|
      XXXXX,  LTOG,  LHUI,  LSAI,  LVAI,  BTOG,  BINC,  WH_R,  WH_D,   END,  PGDN, XXXXX,\
  //|------+------+------+------+------+------|------+------+------+------+------+------|
      XXXXX, LSMOD,  LHUD,  LSAD,  LVAD, XXXXX,  BDEC, XXXXX,  BTN1,  BTN2,  MS_U, XXXXX,\
  //|------+------+------+------+------+-------------+------+------+------+------+------|
      _____, _____, _____, _____, _____, XXXXX, XXXXX, _____, _____,  MS_L,  MS_D,  MS_R \
  //|------+------+------+------+------+-------------+------+------+------+------+------|
  )
};


#ifdef BACKLIGHT_ENABLE
  extern backlight_config_t backlight_config;

  inline void enable_backright(bool on) {
      backlight_config.enable = on;
      if (backlight_config.raw == 1) // enabled but level = 0
          backlight_config.level = 1;
      eeconfig_update_backlight(backlight_config.raw);
      // dprintf("backlight toggle: %u\n", backlight_config.enable);
      backlight_set(backlight_config.enable ? backlight_config.level : 0);
  }

  uint8_t bl_breath_count;
  uint8_t bl_breath_speed = 10;
  int8_t bl_breath_updown = 1;
  bool bl_breath_on;
  backlight_config_t bl_breath_backup;

  void bl_breath_start(uint8_t speed) {

    bl_breath_on = true;
    bl_breath_speed = speed;
    bl_breath_backup = backlight_config;
  }

  void bl_breath_end(void) {

    bl_breath_on = false;
    backlight_config = bl_breath_backup;
    eeconfig_update_backlight(backlight_config.raw);
    backlight_set(backlight_config.enable ? backlight_config.level : 0);
  }

  void bl_breath_update(void) {

    if (bl_breath_on) {
      ++bl_breath_count;
      if (bl_breath_count > bl_breath_speed) {
        bl_breath_count = 0;

        backlight_config.level += bl_breath_updown;
        bl_breath_updown = (backlight_config.level > BACKLIGHT_LEVELS) ? -1 :
                          (backlight_config.level <= 0) ? 1 :
                          bl_breath_updown;
        enable_backright(true);
      }
    }
  }

  #define BL_BREATH_START bl_breath_start
  #define BL_BREATH_END bl_breath_end
  #define BL_BREATH_UPDATE bl_breath_update

#else

  #define BL_BREATH_START(a)
  #define BL_BREATH_END()
  #define BL_BREATH_UPDATE()
#endif

// Loop
void matrix_scan_user(void) {

  BL_BREATH_UPDATE();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        BL_BREATH_START(50);
        layer_on(_LOWER);
      } else {
        BL_BREATH_END();
        layer_off(_LOWER);
      }
      break;
    case RAISE:
      if (record->event.pressed) {
        BL_BREATH_START(100);
        layer_on(_RAISE);
      } else {
        BL_BREATH_END();
        layer_off(_RAISE);
      }
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      break;
    default:
      return true;
  }

  return false;
}
