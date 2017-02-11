// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.

#include "promethium.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "process_unicode.h"
#include "quantum.h"
#include "rgbsps.h"
#include "ps2_mouse.h"
#include "ps2.h"
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
#undef KC_RALT
#define KC_RALT MT(MOD_RALT, KC_SLCK)

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

extern keymap_config_t keymap_config;

enum layers {
  _QWERTY,
  _DVORAK,
  _COLEMAK,
  _WORKMAN,
  _NORMAN,

  _PUNC,
  _NUM,
  _FUNC,

  _GREEKU,
  _GREEKL,

  _EMOJI,
  _GUI,
  _SYS,
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
  PUNC,
  NUM,
  FUNC,
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
  AUDIO
};

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
};

// RGBSPS

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
  LED_PUNC,
  LED_NUM,
  LED_FUNC,
  LED_EMOJI
};

const uint8_t PROGMEM LED_INDICATORS[] = {
  LED_IND_EMOJI,
  LED_IND_NUM,
  LED_IND_FUNC,
  LED_IND_BATTERY,
  LED_IND_USB,
  LED_IND_BLUETOOTH,
};

const uint8_t PROGMEM LED_TRACKPOINT[] = {
  LED_TRACKPOINT1,
  LED_TRACKPOINT2,
  LED_TRACKPOINT3,
};

void led_turnoff_keys(void) {
  for(uint8_t i = 0; i < COUNT(LED_ALNUM); i++) {
    rgbsps_set(pgm_read_byte(&LED_ALNUM[i]), 0, 0, 0);
  }
  for(uint8_t i = 0; i < COUNT(LED_MODS); i++) {
    rgbsps_set(pgm_read_byte(&LED_MODS[i]), 0, 0, 0);
  }
  for(uint8_t i = 0; i < COUNT(LED_FN); i++) {
    rgbsps_set(pgm_read_byte(&LED_FN[i]), 0, 0, 0);
  }
}

void led_reset(void) {
  switch (glow_mode) {
    case GLOW_NONE:
      led_turnoff_keys();
      break;
    case GLOW_MIN:
      led_turnoff_keys();
      for(uint8_t i = 0; i < COUNT(LED_HOMING); i++) {
        rgbsps_set(pgm_read_byte(&LED_HOMING[i]), 8, 8, 8);
      }
      rgbsps_set(LED_F, 15, 0, 0);
      rgbsps_set(LED_J, 15, 0, 0);
      break;
    case GLOW_FULL:
      for(uint8_t i = 0; i < COUNT(LED_ALNUM); i++) {
        rgbsps_set(pgm_read_byte(&LED_ALNUM[i]), 8, 8, 8);
      }
      for(uint8_t i = 0; i < COUNT(LED_MODS); i++) {
        rgbsps_set(pgm_read_byte(&LED_MODS[i]), 0, 15, 0);
      }
      for(uint8_t i = 0; i < COUNT(LED_FN); i++) {
        rgbsps_set(pgm_read_byte(&LED_FN[i]), 0, 0, 15);
      }
      for(uint8_t i = 0; i < COUNT(LED_HOMING); i++) {
        rgbsps_set(pgm_read_byte(&LED_HOMING[i]), 15, 0, 0);
      }
      rgbsps_set(LED_F, 15, 15, 0);
      rgbsps_set(LED_J, 15, 15, 0);
      break;
  }
}

void led_set_layer_indicator(void) {
  static uint8_t oldlayer = 255;

  rgbsps_set(LED_IND_FUNC, 0, 0, 0);
  // rgbsps_set(LED_IND_NUM, 0, 0, 0);
  rgbsps_set(LED_IND_EMOJI, 0, 0, 0);

  led_reset();

  uint8_t layer = biton32(layer_state);
  if (oldlayer == layer) {
    return;
  }

  oldlayer = layer;

  if (layer <= _NORMAN) {
    rgbsps_send();
    return;
  }

  switch(layer) {
    case _FUNC:
      rgbsps_set(LED_IND_FUNC, 15, 0, 0);
      break;
    // case _NUM:
    //   rgbsps_set(LED_IND_NUM, 0, 0, 15);
    //   break;
    case _EMOJI:
      rgbsps_set(LED_IND_EMOJI, 15, 15, 0);
      break;
    default:
      rgbsps_set(LED_IND_FUNC, 3, 3, 3);
      rgbsps_set(LED_IND_NUM, 3, 3, 3);
      rgbsps_set(LED_IND_EMOJI, 3, 3, 3);
  }

  rgbsps_send();
}

void led_set_output_ble(void) {
  rgbsps_set(LED_IND_BLUETOOTH, 0, 0, 15);
  rgbsps_set(LED_IND_USB, 0, 0, 0);
  rgbsps_send();
}

void led_set_output_usb(void) {
  rgbsps_set(LED_IND_BLUETOOTH, 0, 0, 0);
  rgbsps_set(LED_IND_USB, 15, 15, 15);
  rgbsps_send();
}

void led_set_output_none(void) {
  rgbsps_set(LED_IND_BLUETOOTH, 0, 0, 0);
  rgbsps_set(LED_IND_USB, 0, 0, 0);
  rgbsps_send();
}

void led_init(void) {
  // turn off all
  rgbsps_turnoff();

  // set trackpoint color
  rgbsps_set(LED_TRACKPOINT1, 15, 0, 0);
  rgbsps_set(LED_TRACKPOINT2, 0, 0, 15);
  rgbsps_set(LED_TRACKPOINT3, 15, 0, 0);
}


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
 * | Ctrl | Alt  | GUI  | Punc | Num  |    Space    | Func |Greek | GUI  |AltGr | Ctrl |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = KEYMAP(
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT, KC_ENT ,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  KC_LCTL, KC_LALT, KC_LGUI, PUNC,    NUM,     LSPACE,  RSPACE,  FUNC,    GREEK,   KC_RGUI, KC_RALT, KC_RCTL
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
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
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
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
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
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
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
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),
#endif

/* Punc
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |   `  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   *  |   \  |   -  |   =  |   /  |      |   (  |   )  |   <  |   >  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |   &  |   ^  |   |  |   _  |   +  |   ?  |      |   [  |   ]  |   {  |   }  |   :  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_PUNC] = KEYMAP(
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_GRV ,
  XXXXXXX, KC_ASTR, KC_BSLS, KC_MINS,  KC_EQL, KC_SLSH, XXXXXXX, KC_LPRN, KC_RPRN, KC_LABK, KC_RABK, XXXXXXX,
  KC_AMPR, KC_CIRC, KC_PIPE, KC_UNDS, KC_PLUS, KC_QUES, XXXXXXX, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, KC_COLN,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Num
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   A  |   7  |   8  |   9  |   D  |   `  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   *  |   \  |   -  |   =  |   /  |   B  |   4  |   5  |   6  |   E  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |   &  |   ^  |   |  |   _  |   +  |   ?  |   C  |   1  |   2  |   3  |   F  |  :   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |   x  |   0  |   ,  |   .  |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUM] = KEYMAP(
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, S(KC_A),    KC_7,    KC_8,    KC_9, S(KC_D), KC_GRV,
  XXXXXXX, KC_ASTR, KC_BSLS, KC_MINS,  KC_EQL, KC_SLSH, S(KC_B),    KC_4,    KC_5,    KC_6, S(KC_E), _______,
  KC_AMPR, KC_CIRC, KC_PIPE, KC_UNDS, KC_PLUS, KC_QUES, S(KC_C),    KC_1,    KC_2,    KC_3, S(KC_F), KC_COLN,
  _______, _______, _______, _______, _______, _______, _______,    KC_0, KC_COMM,  KC_DOT, KC_X,    _______
),

/* Func
 * ,-----------------------------------------------------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |      |      | PgUp |  Up  | PgDn | PgUp | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F5  |  F6  |  F7  |  F8  |PrtSc |      | Left | Down | Right| PgDn | Ins  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F9  |  F10 |  F11 |  F12 |      |      |      | Home |  End |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FUNC] = KEYMAP(
  XXXXXXX,   KC_F1,   KC_F2,   KC_F3,   KC_F4, XXXXXXX, XXXXXXX, KC_PGUP,   KC_UP, KC_PGDN, KC_PGUP,  KC_DEL,
  XXXXXXX,   KC_F5,   KC_F6,   KC_F7,  KC_F8,KC_PSCREEN,XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,  KC_INS,
  _______,   KC_F9,  KC_F10,  KC_F11,  KC_F12, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME,  KC_END, XXXXXXX, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
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
  _______, _______, _______,X(UEPSI), X(URHO), X(UTAU),X(UUPSI),X(UTHET),X(UIOTA),X(UOMIC),  X(UPI), _______,
  _______,X(UALPH),X(USIGM),X(UDELT), X(UPHI),X(UGAMM), X(UETA),  X(UXI),X(UKAPP),X(ULAMB), _______, _______,
  _______,X(UZETA), X(UCHI), X(UPSI),X(UOMEG),X(UBETA),  X(UNU),  X(UMU), _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
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
  _______, _______,X(FSIGM),X(LEPSI), X(LRHO), X(LTAU),X(LUPSI),X(LTHET),X(LIOTA),X(LOMIC),  X(LPI), _______,
  _______,X(LALPH),X(LSIGM),X(LDELT), X(LPHI),X(LGAMM), X(LETA),  X(LXI),X(LKAPP),X(LLAMB), _______, _______,
  _______,X(LZETA), X(LCHI), X(LPSI),X(LOMEG),X(LBETA),  X(LNU),  X(LMU), _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
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
    X(POO), X(EYES), _______,X(HUNRD), X(SKULL),X(HORNS), X(HALO), X(FEAR),X(YUMMY),_______,X(DISAP),X(NOEVK)
),

/* GUI
 * ,-----------------------------------------------------------------------------------.
 * |      |  D1  |  D2  |  D3  |  D4  |  D5  |  D6  |  D7  |  D8  |  D9  |  D10 |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      | Vol- | Mute | Vol+ |      |      | Prev |      | Next |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      | Prev | Play | Next |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_GUI] = KEYMAP(
  XXXXXXX, G(KC_1), G(KC_2), G(KC_3), G(KC_4), G(KC_5), G(KC_6), G(KC_7), G(KC_8), G(KC_9), G(KC_0), XXXXXXX,
  XXXXXXX, XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX, KC_WWWB, XXXXXXX, KC_WWWF, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, KC_SPC,  KC_SPC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX
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
  XXXXXXX, QWERTY,  WIN,     XXXXXXX, RESET,   XXXXXXX, XXXXXXX, OUT_USB, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, AUDIO,   XXXXXXX, DVORAK,  XXXXXXX, GLOW,    XXXXXXX, XXXXXXX, WORKMAN, LINUX,   XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, COLEMAK, XXXXXXX, OUT_BLE, NORMAN,  OSX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______
),

};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
  bool rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);

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
#endif

  switch (keycode) {

#ifdef DOUBLESPACE_LAYER_ENABLE
    // double-space enter space layer
    case LSPACE:
      if (record->event.pressed) {
        lspace_active = true;
        if (rspace_active) {
          layer_on(_SPACE);
          space_layer_entered = true;
        }
      } else {
        lspace_active = false;
        if (space_layer_entered) {
          layer_off(_SPACE);
          if (!rspace_active) {
            space_layer_entered = false;
          }
        } else {
          if (!lspace_emitted) {
            register_code(KC_SPC);
            unregister_code(KC_SPC);
          }
          lspace_emitted = false;
        }
      }
      return false;
      break;
    case RSPACE:
      if (record->event.pressed) {
        rspace_active = true;
        if (lspace_active) {
          layer_on(_SPACE);
          space_layer_entered = true;
        }
      } else {
        rspace_active = false;
        if (space_layer_entered) {
          layer_off(_SPACE);
          if (!lspace_active) {
            space_layer_entered = false;
          }
        } else {
          if (!rspace_emitted) {
            register_code(KC_SPC);
            unregister_code(KC_SPC);
          }
          rspace_emitted = false;
        }
      }
      return false;
      break;
#endif

    // handle greek layer shift
    // handle both shift = capslock
    case KC_LSFT:
    case KC_RSFT:
      ;
      uint8_t layer = biton32(layer_state);
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
      } else {
        if (record->event.pressed) {
          if (lshift ^ rshift) { // if only one shift was pressed
            register_code(KC_CAPS);
            unregister_code(KC_CAPS);
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
        persistant_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
#ifdef LAYOUT_DVORAK
    case DVORAK:
      if (record->event.pressed) {
        persistant_default_layer_set(1UL<<_DVORAK);
      }
      return false;
      break;
#endif
#ifdef LAYOUT_COLEMAK
    case COLEMAK:
      if (record->event.pressed) {
        persistant_default_layer_set(1UL<<_COLEMAK);
      }
      return false;
      break;
#endif
#ifdef LAYOUT_WORKMAN
    case WORKMAN:
      if (record->event.pressed) {
        persistant_default_layer_set(1UL<<_WORKMAN);
      }
      return false;
      break;
#endif
#ifdef LAYOUT_NORMAN
    case NORMAN:
      if (record->event.pressed) {
        persistant_default_layer_set(1UL<<_NORMAN);
      }
      return false;
      break;
#endif

    // layer switcher
    case PUNC:
      if (record->event.pressed) {
        layer_on(_PUNC);
        update_tri_layer(_PUNC, _GREEKL, _EMOJI);
      } else {
        layer_off(_PUNC);
        update_tri_layer(_PUNC, _GREEKL, _EMOJI);
      }
      return false;
      break;

    case GREEK:
      if (record->event.pressed) {
        if (lshift || rshift) {
          layer_on(_GREEKU);
          layer_off(_GREEKL);
        } else {
          layer_on(_GREEKL);
          layer_off(_GREEKU);
          update_tri_layer(_PUNC, _GREEKL, _EMOJI);
        }
      } else {
        layer_off(_GREEKU);
        layer_off(_GREEKL);
        update_tri_layer(_PUNC, _GREEKL, _EMOJI);
      }
      return false;
      break;

    case NUM:
      if (record->event.pressed) {
        turn_off_capslock();
        layer_on(_NUM);
      } else {
        layer_off(_NUM);
      }
      return false;
      break;

    case FUNC:
      if (record->event.pressed) {
        layer_on(_FUNC);
      } else {
        layer_off(_FUNC);
      }
      return false;
      break;

    // OS switchers
    case LINUX:
      set_unicode_input_mode(UC_LNX);
      return false;
      break;
    case WIN:
      set_unicode_input_mode(UC_WINC);
      return false;
      break;
    case OSX:
      set_unicode_input_mode(UC_OSX);
      return false;
      break;

    // glow mode changer
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

    // faux clicky toggle, TBD
    case AUDIO:
      return false;
      break;
  }
  return true;
}

void set_output_user(uint8_t output) {
  switch(output) {
    case OUTPUT_USB:
      led_set_output_usb();
      break;
    case OUTPUT_ADAFRUIT_BLE:
      led_set_output_ble();
      break;
    default:
      led_set_output_none();
  }
}

void matrix_init_user(void) {
  _delay_ms(500); // give time for usb to initialize

  set_unicode_input_mode(UC_LNX);
  led_init();

  // auto detect output on init
  uint8_t output = auto_detect_output();
  if (output == OUTPUT_USB) {
    set_output(OUTPUT_USB);
  } else {
    set_output(OUTPUT_ADAFRUIT_BLE);
  }
}

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
    if (capslock = new_capslock) {
      rgbsps_set(LED_IND_NUM, 15, 0, 0);
    } else {
      rgbsps_set(LED_IND_NUM, 0, 0, 0);
    }
    rgbsps_send();
  }
}

void turn_off_capslock() {
  if (capslock) {
    register_code(KC_CAPS);
    unregister_code(KC_CAPS);
  }
}

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