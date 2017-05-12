/*
Copyright 2017 Priyadi Iman Nurcahyo

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

#if defined(PRIYADI_PROMETHIUM)
  #include "promethium.h"
#elif defined(PRIYADI_PLANCK)
  #include "planck.h"
#else
  #error "no keyboard defined"
#endif

#include "action_layer.h"
#ifdef AUDIO_ENABLE
  #include "audio.h"
  #include "musical_notes.h"
#endif
#include "eeconfig.h"
#include "process_unicode.h"
#include "quantum.h"
#ifdef RGBSPS_ENABLE
#include "rgbsps.h"
#include "rgbtheme.h"
#endif
#ifdef PS2_MOUSE_ENABLE
#include "ps2_mouse.h"
#include "ps2.h"
#endif
#ifdef FAUXCLICKY_ENABLE
#include "fauxclicky.h"
#ifdef RGBSPS_ENABLE
#undef FAUXCLICKY_OFF
#define FAUXCLICKY_OFF do { \
    fauxclicky_enabled = false; \
    rgbsps_set(LED_AUDIO, COLOR_BLANK); \
    fauxclicky_stop(); \
} while (0)
#undef FAUXCLICKY_ON
#define FAUXCLICKY_ON do { \
    fauxclicky_enabled = true; \
    rgbsps_set(LED_AUDIO, THEME_COLOR_AUDIO); \
} while (0)
#endif
#endif
#include "outputselect.h"
#include "led.h"
#define COUNT(x) (sizeof (x) / sizeof (*(x)))

// Fillers to make layering clearer
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define G(x) LGUI(x)
#define KC_WWWB KC_WWW_BACK
#define KC_WWWF KC_WWW_FORWARD

// hybrid right-alt & scroll lock (mapped to Compose in OS)
#define C_RALT MT(MOD_RALT, KC_SLCK)

// dual use right-shift & del key
// #define C_RSFT MT(MOD_RSFT, KC_DEL)

bool capslock = false;
#ifdef DOUBLESPACE_LAYER_ENABLE
bool lspace_active = false;
bool rspace_active = false;
bool lspace_emitted = false;
bool rspace_emitted = false;
bool space_layer_entered = false;
#endif

// glow
enum glow_modes {
  GLOW_NONE,
  GLOW_MIN,
  GLOW_FULL
};
uint8_t glow_mode = GLOW_MIN;

void turn_off_capslock(void);
extern keymap_config_t keymap_config;

// layers, ordering is important!
enum layers {
  _QWERTY,
  _DVORAK,
  _COLEMAK,
  _WORKMAN,
  _NORMAN,
  _DEFAULT_LAYER_MAX = _NORMAN,

  _GREEKU,
  _GREEKL,

  _NUM,
  _FUN,
  _PUNC,

  _EMPTY,
  _EMOJI,
  _GUI,
  _SYS
};

// double-space layer
#define _SPACE _GUI

enum planck_keycodes {
  // layouts
  QWERTY = SAFE_RANGE,
  DVORAK,
  COLEMAK,
  WORKMAN,
  NORMAN,

  // layer switchers
  EMOJI,
  GUI,
  GREEK,

  // os switchers
  LINUX,
  WIN,
  OSX,

  // others
  LSPACE,
  RSPACE,
  GLOW,

  // stub
#ifndef FAUXCLICKY_ENABLE
  FC_TOG,
#endif
#ifndef MODULE_ADAFRUIT_BLE
  OUT_BT,
#endif
  RGBDEMO,
  KEYCODE_END
};

#define EMPTY MO(_EMPTY)
#define NUM MO(_NUM)
#define FUN MO(_FUN)
#define FUN0 LT(_FUN, KC_0)

// unicode map

enum unicode_name {
  GRIN, // grinning face 😊
  TJOY, // tears of joy 😂
  SMILE, // grining face with smiling eyes 😁
  HEART, // heart ❤
  EYERT, // smiling face with heart shaped eyes 😍
  CRY, // crying face 😭
  SMEYE, // smiling face with smiling eyes 😊
  UNAMU, // unamused 😒
  KISS, // kiss 😘
  HART2, // two hearts 💕
  WEARY, // weary 😩
  OKHND, // ok hand sign 👌
  PENSV, // pensive 😔
  SMIRK, // smirk 😏
  RECYC, // recycle ♻
  WINK, // wink 😉
  THMUP, // thumb up 👍
  THMDN, // thumb down 👎
  PRAY, // pray 🙏
  PHEW, // relieved 😌
  MUSIC, // musical notes
  FLUSH, // flushed 😳
  CELEB, // celebration 🙌
  CRY2, // crying face 😢
  COOL, // smile with sunglasses 😎
  NOEVS, // see no evil
  NOEVH, // hear no evil
  NOEVK, // speak no evil
  POO, // pile of poo
  EYES, // eyes
  VIC, // victory hand
  BHART, // broken heart
  SLEEP, // sleeping face
  SMIL2, // smiling face with open mouth & sweat
  HUNRD, // 100
  CONFU, // confused
  TONGU, // face with tongue & winking eye
  DISAP, // disappointed
  YUMMY, // face savoring delicious food
  CLAP, // hand clapping
  FEAR, // face screaming in fear
  HORNS, // smiling face with horns
  HALO, // smiling face with halo
  BYE, // waving hand
  SUN, // sun
  MOON, // moon
  SKULL, // skull

  // greek letters
  UALPH,
  UBETA,
  UGAMM,
  UDELT,
  UEPSI,
  UZETA,
  UETA,
  UTHET,
  UIOTA,
  UKAPP,
  ULAMB,
  UMU,
  UNU,
  UXI,
  UOMIC,
  UPI,
  URHO,
  USIGM,
  UTAU,
  UUPSI,
  UPHI,
  UCHI,
  UPSI,
  UOMEG,

  LALPH,
  LBETA,
  LGAMM,
  LDELT,
  LEPSI,
  LZETA,
  LETA,
  LTHET,
  LIOTA,
  LKAPP,
  LLAMB,
  LMU,
  LNU,
  LXI,
  LOMIC,
  LPI,
  LRHO,
  LSIGM,
  LTAU,
  LUPSI,
  LPHI,
  LCHI,
  LPSI,
  LOMEG,

  FSIGM,

  LTEQ,
  GTEQ,
  NOTEQ,
  PLMIN,
};

const uint32_t PROGMEM unicode_map[] = {
  [GRIN] = 0x1F600,
  [TJOY] = 0x1F602,
  [SMILE] = 0x1F601,
  [HEART] = 0x2764,
  [EYERT] = 0x1f60d,
  [CRY] = 0x1f62d,
  [SMEYE] = 0x1F60A,
  [UNAMU] = 0x1F612,
  [KISS] = 0x1F618,
  [HART2] = 0x1F495,
  [WEARY] = 0x1F629,
  [OKHND] = 0x1F44C,
  [PENSV] = 0x1F614,
  [SMIRK] = 0x1F60F,
  [RECYC] = 0x267B,
  [WINK] = 0x1F609,
  [THMUP] = 0x1F44D,
  [THMDN] = 0x1F44E,
  [PRAY] = 0x1F64F,
  [PHEW] = 0x1F60C,
  [MUSIC] = 0x1F3B6,
  [FLUSH] = 0x1F633,
  [CELEB] = 0x1F64C,
  [CRY2] = 0x1F622,
  [COOL] = 0x1F60E,
  [NOEVS] = 0x1F648,
  [NOEVH] = 0x1F649,
  [NOEVK] = 0x1F64A,
  [POO] = 0x1F4A9,
  [EYES] = 0x1F440,
  [VIC] = 0x270C,
  [BHART] = 0x1F494,
  [SLEEP] = 0x1F634,
  [SMIL2] = 0x1F605,
  [HUNRD] = 0x1F4AF,
  [CONFU] = 0x1F615,
  [TONGU] = 0x1F61C,
  [DISAP] = 0x1F61E,
  [YUMMY] = 0x1F60B,
  [CLAP] = 0x1F44F,
  [FEAR] = 0x1F631,
  [HORNS] = 0x1F608,
  [HALO] = 0x1F607,
  [BYE] = 0x1F44B,
  [SUN] = 0x2600,
  [MOON] = 0x1F314,
  [SKULL] = 0x1F480,

  // greek letters
  [UALPH] = 0x0391,
  [UBETA] = 0x0392,
  [UGAMM] = 0x0393,
  [UDELT] = 0x0394,
  [UEPSI] = 0x0395,
  [UZETA] = 0x0396,
  [UETA] = 0x0397,
  [UTHET] = 0x0398,
  [UIOTA] = 0x0399,
  [UKAPP] = 0x039A,
  [ULAMB] = 0x039B,
  [UMU] = 0x039C,
  [UNU] = 0x039D,
  [UXI] = 0x039E,
  [UOMIC] = 0x039F,
  [UPI] = 0x03A0,
  [URHO] = 0x03A1,
  [USIGM] = 0x03A3,
  [UTAU] = 0x03A4,
  [UUPSI] = 0x03A5,
  [UPHI] = 0x03A6,
  [UCHI] = 0x03A7,
  [UPSI] = 0x03A8,
  [UOMEG] = 0x03A9,
  [LALPH] = 0x03B1,
  [LBETA] = 0x03B2,
  [LGAMM] = 0x03B3,
  [LDELT] = 0x03B4,
  [LEPSI] = 0x03B5,
  [LZETA] = 0x03B6,
  [LETA] = 0x03B7,
  [LTHET] = 0x03B8,
  [LIOTA] = 0x03B9,
  [LKAPP] = 0x03BA,
  [LLAMB] = 0x03BB,
  [LMU] = 0x03BC,
  [LNU] = 0x03BD,
  [LXI] = 0x03BE,
  [LOMIC] = 0x03BF,
  [LPI] = 0x03C0,
  [LRHO] = 0x03C1,
  [LSIGM] = 0x03C3,
  [LTAU] = 0x03C4,
  [LUPSI] = 0x03C5,
  [LPHI] = 0x03C6,
  [LCHI] = 0x03C7,
  [LPSI] = 0x03C8,
  [LOMEG] = 0x03C9,
  [FSIGM] = 0x03C2,

  // other
  [LTEQ] = 0x2264, // less than or equal
  [GTEQ] = 0x2265, // greater than or equal
  [NOTEQ] = 0x2260, // not equal
  [PLMIN] = 0xB1, // plus minus
};

// RGBSPS

#ifdef RGBSPS_ENABLE
const uint8_t PROGMEM LED_ALNUM[] = {
  LED_Z,
  LED_A,
  LED_Q,
  LED_W,
  LED_S,
  LED_X,
  LED_C,
  LED_D,
  LED_E,
  LED_R,
  LED_F,
  LED_V,
  LED_B,
  LED_G,
  LED_T,
  LED_N,
  LED_HH,
  LED_Y,
  LED_U,
  LED_J,
  LED_M,
  LED_COMM,
  LED_K,
  LED_I,
  LED_O,
  LED_L,
  LED_DOT,
  LED_SLSH,
  LED_SCLN,
  LED_P,
  LED_LSPC,
  LED_RSPC
};

const uint8_t PROGMEM LED_HOMING[] = {
  LED_A,
  LED_S,
  LED_D,
  LED_F,
  LED_J,
  LED_K,
  LED_L,
  LED_SCLN
};

const uint8_t PROGMEM LED_MODS[] = {
  LED_TAB,
  LED_ESC,
  LED_LSFT,
  LED_LCTL,
  LED_LGUI,
  LED_LALT,
  LED_RALT,
  LED_RGUI,
  LED_BKSP,
  LED_ENT,
  LED_RSFT,
  LED_RCTL
};

const uint8_t PROGMEM LED_FN[] = {
  LED_EMPTY,
  LED_NUM,
  LED_FUN,
  LED_GREEK
};

const uint8_t PROGMEM LED_INDICATORS[] = {
  LED_IND_LINUX,
  LED_IND_APPLE,
  LED_IND_WINDOWS,
  LED_IND_QWERTY,
  LED_IND_ALT,
  LED_IND_AUDIO,
  LED_IND_BLUETOOTH,
  LED_IND_USB,

  LED_IND_BATTERY,
  LED_IND_CAPSLOCK,
  LED_IND_GUI,
  LED_IND_FUN,
  LED_IND_NUM,
  LED_IND_PUNC,
  LED_IND_EMOJI,
  LED_IND_GREEK,
};

const uint8_t PROGMEM LED_TRACKPOINT[] = {
  LED_TRACKPOINT1,
  LED_TRACKPOINT2,
  LED_TRACKPOINT3,
};

void led_turnoff_keys(void) {
  for(uint8_t i = 0; i < COUNT(LED_ALNUM); i++) {
    rgbsps_set(pgm_read_byte(&LED_ALNUM[i]), COLOR_BLACK);
  }
  for(uint8_t i = 0; i < COUNT(LED_MODS); i++) {
    rgbsps_set(pgm_read_byte(&LED_MODS[i]), COLOR_BLACK);
  }
  for(uint8_t i = 0; i < COUNT(LED_FN); i++) {
    rgbsps_set(pgm_read_byte(&LED_FN[i]), COLOR_BLACK);
  }
}

#ifdef RGBSPS_DEMO_ENABLE
void led_demo(void) {
  rgbsps_set(LED_IND_LINUX, THEME_COLOR_LINUX);
  rgbsps_set(LED_IND_APPLE, THEME_COLOR_APPLE);
  rgbsps_set(LED_IND_WINDOWS, THEME_COLOR_WINDOWS);
  rgbsps_set(LED_IND_QWERTY, THEME_COLOR_QWERTY);
  rgbsps_set(LED_IND_ALT, THEME_COLOR_ALT);
  rgbsps_set(LED_IND_AUDIO, THEME_COLOR_AUDIO);
  rgbsps_set(LED_IND_BLUETOOTH, THEME_COLOR_BLUETOOTH);
  rgbsps_set(LED_IND_USB, THEME_COLOR_USB);
  rgbsps_set(LED_IND_CAPSLOCK, THEME_COLOR_CAPSLOCK);
  rgbsps_set(LED_IND_GUI, THEME_COLOR_GUI);
  rgbsps_set(LED_IND_FUN, THEME_COLOR_FUN);
  rgbsps_set(LED_IND_NUM, THEME_COLOR_NUM);
  rgbsps_set(LED_IND_PUNC, THEME_COLOR_PUNC);
  rgbsps_set(LED_IND_GREEK, THEME_COLOR_GREEK);
  rgbsps_set(LED_IND_EMOJI, THEME_COLOR_EMOJI);
  rgbsps_send();
}
#endif

void led_reset(void) {
  switch (glow_mode) {
    case GLOW_NONE:
      led_turnoff_keys();
      break;
    case GLOW_MIN:
      led_turnoff_keys();
      for(uint8_t i = 0; i < COUNT(LED_HOMING); i++) {
        rgbsps_set(pgm_read_byte(&LED_HOMING[i]), THEME_COLOR_GLOW1_HOME);
      }
      rgbsps_set(LED_F, THEME_COLOR_GLOW1_HOMING);
      rgbsps_set(LED_J, THEME_COLOR_GLOW1_HOMING);
      break;
    case GLOW_FULL:
      for(uint8_t i = 0; i < COUNT(LED_ALNUM); i++) {
        rgbsps_set(pgm_read_byte(&LED_ALNUM[i]), THEME_COLOR_GLOW2_ALPHA);
      }
      for(uint8_t i = 0; i < COUNT(LED_MODS); i++) {
        rgbsps_set(pgm_read_byte(&LED_MODS[i]), THEME_COLOR_GLOW2_MODS);
      }
      for(uint8_t i = 0; i < COUNT(LED_FN); i++) {
        rgbsps_set(pgm_read_byte(&LED_FN[i]), THEME_COLOR_GLOW2_FN);
      }
      for(uint8_t i = 0; i < COUNT(LED_HOMING); i++) {
        rgbsps_set(pgm_read_byte(&LED_HOMING[i]), THEME_COLOR_GLOW2_HOME);
      }
      rgbsps_set(LED_F, THEME_COLOR_GLOW2_HOMING);
      rgbsps_set(LED_J, THEME_COLOR_GLOW2_HOMING);
      break;
  }
}

void led_set_default_layer_indicator(void) {
  uint8_t default_layer = biton32(default_layer_state);
  if (default_layer == _QWERTY) {
    rgbsps_set(LED_IND_QWERTY, THEME_COLOR_QWERTY);
    rgbsps_set(LED_IND_ALT, COLOR_BLANK);
  } else {
    rgbsps_set(LED_IND_QWERTY, COLOR_BLANK);
    rgbsps_set(LED_IND_ALT, THEME_COLOR_ALT);
  }
  rgbsps_send();
  return;
}

void led_set_layer_indicator(void) {
  static uint8_t oldlayer = 255;

  led_reset();

  rgbsps_set(LED_IND_GUI, COLOR_BLANK);
  rgbsps_set(LED_IND_FUN, COLOR_BLANK);
  rgbsps_set(LED_IND_NUM, COLOR_BLANK);
  rgbsps_set(LED_IND_PUNC, COLOR_BLANK);
  rgbsps_set(LED_IND_GREEK, COLOR_BLANK);
  rgbsps_set(LED_IND_EMOJI, COLOR_BLANK);

  uint8_t layer = biton32(layer_state);
  if (oldlayer == layer) {
    return;
  }

  oldlayer = layer;

  if (layer <= _DEFAULT_LAYER_MAX) {
    rgbsps_send();
    return;
  }

  switch(layer) {
    case _GUI:
      rgbsps_set(LED_IND_GUI, THEME_COLOR_GUI);
      break;
    case _FUN:
      rgbsps_set(LED_IND_FUN, THEME_COLOR_FUN);
      break;
    case _NUM:
      rgbsps_set(LED_IND_NUM, THEME_COLOR_NUM);
      break;
    case _PUNC:
      rgbsps_set(LED_IND_PUNC, THEME_COLOR_PUNC);
      break;
    case _GREEKL:
    case _GREEKU:
      rgbsps_set(LED_IND_GREEK, THEME_COLOR_GREEK);
      break;
    case _EMOJI:
      rgbsps_set(LED_IND_EMOJI, THEME_COLOR_EMOJI);
      break;
    default:
      rgbsps_set(LED_IND_GUI, THEME_COLOR_OTHERLAYER);
      rgbsps_set(LED_IND_FUN, THEME_COLOR_OTHERLAYER);
      rgbsps_set(LED_IND_NUM, THEME_COLOR_OTHERLAYER);
      rgbsps_set(LED_IND_PUNC, THEME_COLOR_OTHERLAYER);
      rgbsps_set(LED_IND_GREEK, THEME_COLOR_OTHERLAYER);
      rgbsps_set(LED_IND_EMOJI, THEME_COLOR_OTHERLAYER);
  }

  rgbsps_send();
}

void led_set_unicode_input_mode(void) {
  rgbsps_set(LED_IND_LINUX, COLOR_BLANK);
  rgbsps_set(LED_IND_APPLE, COLOR_BLANK);
  rgbsps_set(LED_IND_WINDOWS, COLOR_BLANK);

  switch (get_unicode_input_mode()) {
    case UC_LNX:
      rgbsps_set(LED_IND_LINUX, THEME_COLOR_LINUX);
      break;
    case UC_OSX:
      rgbsps_set(LED_IND_APPLE, THEME_COLOR_APPLE);
      break;
    case UC_WIN:
    case UC_WINC:
      rgbsps_set(LED_IND_WINDOWS, THEME_COLOR_WINDOWS);
      break;
  }
  rgbsps_send();
}

void led_set_output_ble(void) {
  rgbsps_set(LED_IND_BLUETOOTH, THEME_COLOR_BLUETOOTH);
  rgbsps_set(LED_IND_USB, COLOR_BLANK);
  rgbsps_send();
}

void led_set_output_usb(void) {
  rgbsps_set(LED_IND_BLUETOOTH, COLOR_BLANK);
  rgbsps_set(LED_IND_USB, THEME_COLOR_USB);
  rgbsps_send();
}

void led_set_output_none(void) {
  rgbsps_set(LED_IND_BLUETOOTH, COLOR_BLANK);
  rgbsps_set(LED_IND_USB, COLOR_BLANK);
  rgbsps_send();
}

void led_init(void) {
  // turn off all
  rgbsps_turnoff();

  // set trackpoint color
  rgbsps_set(LED_TRACKPOINT1, THEME_COLOR_TP1);
  rgbsps_set(LED_TRACKPOINT2, THEME_COLOR_TP2);
  rgbsps_set(LED_TRACKPOINT3, THEME_COLOR_TP3);

  // unicode input mode
  led_set_unicode_input_mode();

  // layer indicator
  led_set_layer_indicator();
  led_set_default_layer_indicator();

  // clicky
#ifdef FAUXCLICKY_ENABLE
  if (fauxclicky_enabled) {
    rgbsps_set(LED_IND_AUDIO, THEME_COLOR_AUDIO);
  } else {
    rgbsps_set(LED_IND_AUDIO, COLOR_BLANK);
  }
#endif

  rgbsps_send();
}


#endif // RGBSPS_ENABLE

// keymaps

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   '  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  | GUI  | Punc | Num  |    Space    | Fun  |Greek | GUI  |AltGr | Ctrl |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = KEYMAP(
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT, KC_ENT ,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  KC_LCTL, KC_LALT, KC_LGUI, EMPTY,   NUM,     LSPACE,  RSPACE,  FUN,     GREEK,   KC_RGUI, C_RALT,  KC_RCTL,
                                           _______, _______, _______
),

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   '  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   /  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  | GUI  | Punc | Num  |    Space    | Func |Greek | GUI  |AltGr | Ctrl |
 * `-----------------------------------------------------------------------------------'
 */
#ifdef LAYOUT_DVORAK
[_DVORAK] = KEYMAP(
  _______, KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    _______,
  _______, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    _______,
  _______, KC_SLSH, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                           _______, _______, _______
),
#endif

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  | GUI  | Punc | Num  |    Space    | Func |Greek | GUI  |AltGr | Ctrl |
 * `-----------------------------------------------------------------------------------'
 */

#ifdef LAYOUT_COLEMAK
[_COLEMAK] = KEYMAP(
  _______, KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT, _______,
  _______, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    _______,
  _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                           _______, _______, _______
),
#endif

/* Norman
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   D  |   F  |   K  |   J  |   U  |   R  |   L  |   ;  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   E  |   T  |   G  |   Y  |   N  |   I  |   O  |   H  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   P  |   M  |   ,  |   .  |   /  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  | GUI  | Punc | Num  |    Space    | Func |Greek | GUI  |AltGr | Ctrl |
 * `-----------------------------------------------------------------------------------'
 */

#ifdef LAYOUT_NORMAN
[_NORMAN] = KEYMAP(
  _______, KC_Q,    KC_W,    KC_D,    KC_F,    KC_K,    KC_J,    KC_U,    KC_R,    KC_L,    KC_QUOT, _______,
  _______, KC_A,    KC_S,    KC_E,    KC_T,    KC_G,    KC_Y,    KC_N,    KC_I,    KC_O,    KC_H,    _______,
  _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_P,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                           _______, _______, _______
),
#endif

/* Workman
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   D  |   R  |   W  |   B  |   J  |   F  |   U  |   P  |   ;  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   H  |   T  |   G  |   Y  |   N  |   E  |   O  |   I  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   M  |   C  |   V  |   K  |   K  |   ,  |   .  |   /  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  | GUI  | Punc | Num  |    Space    | Func |Greek | GUI  |AltGr | Ctrl |
 * `-----------------------------------------------------------------------------------'
 */

#ifdef LAYOUT_WORKMAN
[_WORKMAN] = KEYMAP(
  _______, KC_Q,    KC_D,    KC_R,    KC_W,    KC_B,    KC_J,    KC_F,    KC_U,    KC_P,    KC_QUOT, _______,
  _______, KC_A,    KC_S,    KC_H,    KC_T,    KC_G,    KC_Y,    KC_N,    KC_E,    KC_O,    KC_I,    _______,
  _______, KC_Z,    KC_X,    KC_M,    KC_C,    KC_V,    KC_K,    KC_L,    KC_COMM, KC_DOT,  KC_SLSH, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                           _______, _______, _______
),
#endif

/* Punc
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   ≤  |   ≥  |   `  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   *  |   \  |   -  |   =  |   /  |   ≠  |   (  |   )  |   <  |   >  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |   &  |   ^  |   |  |   _  |   +  |   ?  |   ±  |   [  |   ]  |   {  |   }  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |   :  |      |
 * `-----------------------------------------------------------------------------------'
 */
[_PUNC] = KEYMAP(
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, X(LTEQ), X(GTEQ), _______,
  KC_GRV,  KC_ASTR, KC_BSLS, KC_MINS,  KC_EQL, KC_SLSH, X(NOTEQ),KC_LPRN, KC_RPRN, KC_LABK, KC_RABK, _______,
  KC_AMPR, KC_CIRC, KC_PIPE, KC_UNDS, KC_PLUS, KC_QUES, X(PLMIN),KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_COLN, _______,
                                           _______, _______, _______
),

/* Num
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   A  |   7  |   8  |   9  |   D  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   `  |   *  |   \  |   -  |   =  |   /  |   B  |   4  |   5  |   6  |   E  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |   &  |   ^  |   |  |   _  |   +  |   ?  |   C  |   1  |   2  |   3  |   F  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |   x  |      |      |      |      |   0  |   ,  |   .  |   :  |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUM] = KEYMAP(
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, S(KC_A),  KC_1,    KC_2,    KC_3,   S(KC_D), _______,
  KC_GRV,  KC_ASTR, KC_BSLS, KC_MINS,  KC_EQL, KC_SLSH, S(KC_B),  KC_4,    KC_5,    KC_6,   S(KC_E), _______,
  KC_AMPR, KC_CIRC, KC_PIPE, KC_UNDS, KC_PLUS, KC_QUES, S(KC_C),  KC_7,    KC_8,    KC_9,   S(KC_F), _______,
  _______, _______, KC_X,    _______, _______, _______, _______,  FUN0 ,   KC_COMM, KC_DOT, KC_COLN, _______,
                                           _______, _______, _______
),

/* Func
 * ,-----------------------------------------------------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  | Ins  |      | PgUp |  Up  | PgDn | PgUp |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Caps |  F5  |  F6  |  F7  |  F8  |PrtSc |      | Left | Down | Right| PgDn |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F9  |  F10 |  F11 |  F12 |Pause |      |      | Home |  End |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FUN] = KEYMAP(
  XXXXXXX,   KC_F1,   KC_F2,   KC_F3,  KC_F4,   KC_INS,  XXXXXXX, KC_PGUP,   KC_UP, KC_PGDN, KC_PGUP, KC_DEL,
  KC_CAPS,   KC_F5,   KC_F6,   KC_F7,  KC_F8,   KC_PSCR, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______,
  _______,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_PAUS, XXXXXXX, XXXXXXX, KC_HOME,  KC_END, XXXXXXX, _______,
  _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______,
                                           _______, _______, _______
),

/* Uppercase Greek
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_GREEKU] = KEYMAP(
  _______, XXXXXXX, XXXXXXX,X(UEPSI), X(URHO), X(UTAU),X(UUPSI),X(UTHET),X(UIOTA),X(UOMIC),  X(UPI), _______,
  _______,X(UALPH),X(USIGM),X(UDELT), X(UPHI),X(UGAMM), X(UETA),  X(UXI),X(UKAPP),X(ULAMB), KC_QUOT, _______,
  _______,X(UZETA), X(UCHI), X(UPSI),X(UOMEG),X(UBETA),  X(UNU),  X(UMU), KC_COMM, KC_DOT,  KC_SLSH, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                           _______, _______, _______
),

/* Lowercase Greek
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_GREEKL] = KEYMAP(
  _______, XXXXXXX,X(FSIGM),X(LEPSI), X(LRHO), X(LTAU),X(LUPSI),X(LTHET),X(LIOTA),X(LOMIC),  X(LPI), _______,
  _______,X(LALPH),X(LSIGM),X(LDELT), X(LPHI),X(LGAMM), X(LETA),  X(LXI),X(LKAPP),X(LLAMB), KC_QUOT, _______,
  _______,X(LZETA), X(LCHI), X(LPSI),X(LOMEG),X(LBETA),  X(LNU),  X(LMU), KC_COMM, KC_DOT,  KC_SLSH, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                           _______, _______, _______
),

/* Empty
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_EMPTY] = KEYMAP(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                           _______, _______, _______
),

/* Emoji
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_EMOJI] = KEYMAP(
  X(HART2), X(CRY2),X(WEARY),X(EYERT),X(SMIRK), X(TJOY),X(RECYC),X(UNAMU),X(MUSIC),X(OKHND),X(PENSV), X(PHEW),
  X(THMUP), X(PRAY),X(SMILE),X(SMIL2),X(FLUSH), X(GRIN),X(HEART),  X(BYE), X(KISS),X(CELEB), X(COOL),X(NOEVS),
  X(THMDN),X(SLEEP), X(CLAP),  X(CRY),  X(VIC),X(BHART),  X(SUN),X(SMEYE), X(WINK), X(MOON),X(CONFU),X(NOEVH),
    X(POO), X(EYES), X(HUNRD),_______, X(SKULL),X(HORNS), X(HALO), X(FEAR),_______,X(YUMMY),X(DISAP),X(NOEVK),
                                           _______, _______, _______
),

/* GUI
 * ,-----------------------------------------------------------------------------------.
 * |      |  D1  |  D2  |  D3  |  D4  |  D5  |  D6  |  D7  |  D8  |  D9  |  D10 |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |      | Btab | Esc  | Tab  |      |      | Prev |      | Next |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      | Prev | Play | Next |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_GUI] = KEYMAP(
  XXXXXXX, G(KC_1), G(KC_2), G(KC_3), G(KC_4), G(KC_5), G(KC_6), G(KC_7), G(KC_8), G(KC_9), G(KC_0), XXXXXXX,
  KC_ESC,  XXXXXXX, S(KC_TAB),KC_ESC, KC_TAB,  XXXXXXX, XXXXXXX, KC_WWWB, XXXXXXX, KC_WWWF, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, KC_SPC,  KC_SPC,  KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                           _______, _______, _______
),

/* Sys
 * ,-----------------------------------------------------------------------------------.
 * |      |Qwerty| Win  |      |Reset |      |      | USB  |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |Audio |      |Dvorak|      | Glow |      |      |WorkMn|Linux |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |Colmak|      | BLE  |Norman|MacOS |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_SYS] = KEYMAP(
  DEBUG,   QWERTY,  WIN,     XXXXXXX, RESET,   XXXXXXX, XXXXXXX, OUT_USB, XXXXXXX, XXXXXXX, XXXXXXX, RGBDEMO,
  XXXXXXX, FC_TOG,  XXXXXXX, DVORAK,  XXXXXXX, GLOW,    XXXXXXX, XXXXXXX, WORKMAN, LINUX,   XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, COLEMAK, XXXXXXX, OUT_BT,  NORMAN,  OSX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
                                           _______, _______, _______
),


};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
#ifdef RGBSPS_ENABLE
  led_set_default_layer_indicator();
#endif
}

#ifdef DOUBLESPACE_LAYER_ENABLE
void process_doublespace(bool pressed, bool *isactive, bool *otheractive, bool *isemitted) {
  if (pressed) {
    *isactive = true;
    if (*otheractive) {
      layer_on(_SPACE);
      register_code(KC_LALT);  // sends alt and enter layer
      space_layer_entered = true;
    }
  } else {
    *isactive = false;
    if (space_layer_entered) {
      unregister_code(KC_LALT);  // release alt and exit layer
      layer_off(_SPACE);
      if (!*otheractive) {
        space_layer_entered = false;
      }
    } else {
      if (!*isemitted) {
        register_code(KC_SPC);
        unregister_code(KC_SPC);
      }
      *isemitted = false;
    }
  }
}
#endif

uint32_t layer_state_set_kb(uint32_t state)
{
  // turn on punc layer if both fun & num are on
  if ((state & ((1UL<<_NUM) | (1UL<<_FUN))) == ((1UL<<_NUM) | (1UL<<_FUN))) {
    state |= (1UL<<_PUNC);
  } else {
    state &= ~(1UL<<_PUNC);
  }

  // turn on emoji layer if empty and greek layer are on
  if (
    (state & ((1UL<<_EMPTY) | (1UL<<_GREEKU))) == ((1UL<<_EMPTY) | (1UL<<_GREEKU))
    || (state & ((1UL<<_EMPTY) | (1UL<<_GREEKL))) == ((1UL<<_EMPTY) | (1UL<<_GREEKL))
  ) {
    state |= (1UL<<_EMOJI);
  } else {
    state &= ~(1UL<<_EMOJI);
  }
  return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static bool lshift = false;
  static bool rshift = false;
  static uint8_t layer = 0;

  lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
  rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
  layer = biton32(layer_state);

#ifdef DOUBLESPACE_LAYER_ENABLE
  // double-space: send space immediately if any other key depressed before space is released
  if ((lspace_active ^ rspace_active)
      && keycode != LSPACE
      && keycode != RSPACE
      && record->event.pressed)
  {
    if (lspace_active) {
      if (!lspace_emitted) {
        register_code(KC_SPC);
        unregister_code(KC_SPC);
      }
      lspace_emitted = true;
    }
    if (rspace_active) {
      if (!rspace_emitted) {
        register_code(KC_SPC);
        unregister_code(KC_SPC);
      }
      rspace_emitted = true;
    }
  }

  if (layer == _SPACE && keycode != S(KC_TAB) && keycode != KC_TAB && keycode != KC_ESC && keycode != XXXXXXX) {
    if (record->event.pressed) {
      unregister_code(KC_LALT);
    } else {
      register_code(KC_LALT);
    }
  }
#endif

  switch (keycode) {

#ifdef DOUBLESPACE_LAYER_ENABLE
    // double-space enter space layer
    case LSPACE:
      process_doublespace(record->event.pressed, &lspace_active, &rspace_active, &lspace_emitted);
      return false;
      break;
    case RSPACE:
      process_doublespace(record->event.pressed, &rspace_active, &lspace_active, &rspace_emitted);
      return false;
      break;
#endif

    // handle greek layer shift
    case KC_LSFT:
    case KC_RSFT:
      ;
      if (layer == _GREEKU || layer == _GREEKL) {
        if (record->event.pressed) {
          layer_on(_GREEKU);
          layer_off(_GREEKL);
        } else {
          if (lshift ^ rshift) { // if only one shift was pressed
            layer_on(_GREEKL);
            layer_off(_GREEKU);
          }
        }
      }
      return true;
      break;

    // press both ctrls to activate SYS layer
    case KC_LCTL:
    case KC_RCTL:
      ;
      bool lctrl = keyboard_report->mods & MOD_BIT(KC_LCTL);
      bool rctrl = keyboard_report->mods & MOD_BIT(KC_RCTL);
      if (record->event.pressed) {
        if (lctrl ^ rctrl) { // if only one ctrl was pressed
          layer_on(_SYS);
        }
      } else {
        layer_off(_SYS);
      }
      return true;
      break;

    // QWERTZ style comma and dot: semicolon and colon when shifted
    case KC_COMM:
      if (record->event.pressed) {
        if (lshift || rshift) {
          if (lshift) unregister_code(KC_LSFT);
          if (rshift) unregister_code(KC_RSFT);
          register_code(KC_SCLN);
          unregister_code(KC_SCLN);
          if (lshift) register_code(KC_LSFT);
          if (rshift) register_code(KC_RSFT);
        } else {
          register_code(KC_COMM);
          unregister_code(KC_COMM);
        }
      }
      return false;
      break;
    case KC_DOT:
      if (record->event.pressed) {
        if ((keyboard_report->mods & MOD_BIT(KC_LSFT)) || (keyboard_report->mods & MOD_BIT(KC_RSFT))) {
          register_code(KC_SCLN);
          unregister_code(KC_SCLN);
        } else {
          register_code(KC_DOT);
          unregister_code(KC_DOT);
        }
      }
      return false;
      break;

    // layout switchers
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
#ifdef LAYOUT_DVORAK
    case DVORAK:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_DVORAK);
      }
      return false;
      break;
#endif
#ifdef LAYOUT_COLEMAK
    case COLEMAK:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_COLEMAK);
      }
      return false;
      break;
#endif
#ifdef LAYOUT_WORKMAN
    case WORKMAN:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_WORKMAN);
      }
      return false;
      break;
#endif
#ifdef LAYOUT_NORMAN
    case NORMAN:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_NORMAN);
      }
      return false;
      break;
#endif

    // only process Fnumber on key release, and only when layer switcher is still pressed.
    // this is to avoid accidental presses on potentially destructive keys
    case KC_F1 ... KC_F12:
    case KC_PAUS:
    case KC_PSCR:
    case KC_INS:
      if (!record->event.pressed && layer == _FUN) { // key released and still in FUN layer
          register_code(keycode);
          unregister_code(keycode);
      }
      return false;
      break;

    // layer switcher
    //
    case GREEK:
      if (record->event.pressed) {
        if (lshift || rshift) {
          layer_on(_GREEKU);
          layer_off(_GREEKL);
        } else {
          layer_on(_GREEKL);
          layer_off(_GREEKU);
        }
      } else {
        layer_off(_GREEKU);
        layer_off(_GREEKL);
      }
      return false;
      break;

    // OS switchers
    case LINUX:
      set_unicode_input_mode(UC_LNX);
#ifdef RGBSPS_ENABLE
      led_set_unicode_input_mode();
#endif
      return false;
      break;
    case WIN:
      set_unicode_input_mode(UC_WINC);
#ifdef RGBSPS_ENABLE
      led_set_unicode_input_mode();
#endif
      return false;
      break;
    case OSX:
      set_unicode_input_mode(UC_OSX);
#ifdef RGBSPS_ENABLE
      led_set_unicode_input_mode();
#endif
      return false;
      break;

    // glow mode changer
#ifdef RGBSPS_ENABLE
    case GLOW:
      if (record->event.pressed) {
        glow_mode++;
        if (glow_mode > GLOW_FULL) {
          glow_mode = GLOW_NONE;
        }
        led_reset();
        rgbsps_send();
      }
      return false;
      break;
#endif

    // faux clicky indicator
#ifdef FAUXCLICKY_ENABLE
    case FC_TOG:
#ifdef RGBSPS_ENABLE
      if (fauxclicky_enabled) {
        rgbsps_set(LED_IND_AUDIO, THEME_COLOR_AUDIO);
      } else {
        rgbsps_set(LED_IND_AUDIO, COLOR_BLANK);
      }
      rgbsps_send();
#endif
      return true;
      break;
#endif

#ifdef RGBSPS_DEMO_ENABLE
    case RGBDEMO:
      led_demo();
      return false;
      break;
#endif
  }
  return true;
}

void set_output_user(uint8_t output) {
#ifdef MODULE_ADAFRUIT_BLE
  switch(output) {
    case OUTPUT_USB:
      led_set_output_usb();
      break;
    case OUTPUT_BLUETOOTH:
      led_set_output_ble();
      break;
    default:
      led_set_output_none();
  }
#endif
}

void matrix_init_user() {
  _delay_ms(500); // give time for usb to initialize

  set_unicode_input_mode(UC_LNX);

#ifdef RGBSPS_ENABLE
  led_init();
#endif

  // auto detect output on init
#ifdef MODULE_ADAFRUIT_BLE
  uint8_t output = auto_detect_output();
  if (output == OUTPUT_USB) {
    set_output(OUTPUT_USB);
  } else {
    set_output(OUTPUT_BLUETOOTH);
  }
#endif
}

void turn_off_capslock() {
  if (capslock) {
    register_code(KC_CAPS);
    unregister_code(KC_CAPS);
  }
}

#ifdef RGBSPS_ENABLE
  void matrix_scan_user(void) {
    led_set_layer_indicator();
  }

  void battery_poll(uint8_t level) {
    rgbsps_sethsv(LED_IND_BATTERY, level * 120/255, 255, 15);
    rgbsps_send();
  }

  void led_set_user(uint8_t usb_led) {
    bool new_capslock = usb_led & (1<<USB_LED_CAPS_LOCK);
    if (new_capslock ^ capslock) { // capslock state is different
      if ((capslock = new_capslock)) {
        rgbsps_set(LED_IND_CAPSLOCK, THEME_COLOR_CAPSLOCK);
      } else {
        rgbsps_set(LED_IND_CAPSLOCK, COLOR_BLANK);
      }
      rgbsps_send();
    }
  }
#endif

#ifdef PS2_MOUSE_ENABLE
  void ps2_mouse_init_user() {
      uint8_t rcv;

      // set TrackPoint sensitivity
      PS2_MOUSE_SEND(0xE2, "tpsens: 0xE2");
      PS2_MOUSE_SEND(0x81, "tpsens: 0x81");
      PS2_MOUSE_SEND(0x4A, "tpsens: 0x4A");
      PS2_MOUSE_SEND(0x49, "tpsens: 0x59");

      // set TrackPoint Negative Inertia factor
      PS2_MOUSE_SEND(0xE2, "tpnegin: 0xE2");
      PS2_MOUSE_SEND(0x81, "tpnegin: 0x81");
      PS2_MOUSE_SEND(0x4D, "tpnegin: 0x4D");
      PS2_MOUSE_SEND(0x06, "tpnegin: 0x06");

      // set TrackPoint speed
      // (transfer function upper plateau speed)
      PS2_MOUSE_SEND(0xE2, "tpsp: 0xE2");
      PS2_MOUSE_SEND(0x81, "tpsp: 0x81");
      PS2_MOUSE_SEND(0x60, "tpsp: 0x60");
      PS2_MOUSE_SEND(0x61, "tpsp: 0x61");

      // inquire pts status
      rcv = ps2_host_send(0xE2);
      rcv = ps2_host_send(0x2C);
      rcv = ps2_host_recv_response();
      if ((rcv & 1) == 1) {
        // if on, disable pts
        rcv = ps2_host_send(0xE2);
        rcv = ps2_host_send(0x47);
        rcv = ps2_host_send(0x2C);
        rcv = ps2_host_send(0x01);
      }
  }
#endif