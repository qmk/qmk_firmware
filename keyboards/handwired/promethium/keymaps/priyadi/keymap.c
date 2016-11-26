// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.

#include "promethium.h"
#include "action_layer.h"
#ifdef AUDIO_ENABLE
  #include "audio.h"
  #include "musical_notes.h"
#endif
#include "eeconfig.h"
#include "process_unicode.h"
#include "quantum.h"
#include "rgbsps.h"
#define COUNT(x) (sizeof (x) / sizeof (*(x)))

// #define RGBLED_NUM 5
// struct cRGB led[RGBLED_NUM];


extern keymap_config_t keymap_config;

enum layers {
  _QWERTY,
  _COLEMAK,
  _WORKMAN,
  _PUNC,
  _NUM,
  _FUNC,
  _EMOJI,
  _GUI,
};

enum planck_keycodes {
  // layouts
  QWERTY = SAFE_RANGE,
  COLEMAK,
  WORKMAN,

  // layer switchers
  PUNC,
  NUM,
  FUNC,
  EMOJI,
  GUI,

  // os switchers
  LINUX,
  WIN,
  OSX,
};

// Fillers to make layering clearer

#define _______ KC_TRNS
#define XXXXXXX KC_NO

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
};


// hybrid shift - =
// #undef KC_LSFT
// #define KC_LSFT MT(MOD_LSFT, KC_MINS)
// #undef KC_RSFT
// #define KC_RSFT MT(MOD_LSFT, KC_EQL)


// hybrid right-gui & scroll lock (mapped to Compose in OS)
#undef KC_RCTL
#define KC_RCTL MT(MOD_LCTL, KC_SLCK)

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

void led_reset(void) {
  for(uint8_t i = 0; i < COUNT(LED_ALNUM); i++) {
    rgbsps_set(pgm_read_byte(&LED_ALNUM[i]), 15, 6, 0);
  }

  for(uint8_t i = 0; i < COUNT(LED_MODS); i++) {
    rgbsps_set(pgm_read_byte(&LED_MODS[i]), 15, 0, 0);
  }

  for(uint8_t i = 0; i < COUNT(LED_FN); i++) {
    rgbsps_set(pgm_read_byte(&LED_FN[i]), 15, 15, 15);
  }
}

void led_layer_normal(void) {
  rgbsps_set(LED_IND_FUNC, 0, 0, 0);
  rgbsps_set(LED_IND_NUM, 0, 0, 0);
  rgbsps_set(LED_IND_EMOJI, 0, 0, 0);

  led_reset();

  rgbsps_send();
}

void led_layer_func(void) {
  rgbsps_set(LED_IND_FUNC, 0, 15, 0);
  rgbsps_set(LED_IND_NUM, 0, 0, 0);
  rgbsps_set(LED_IND_EMOJI, 0, 0, 0);

  led_reset();

  for(uint8_t i = 0; i < COUNT(LED_ALNUM); i++) {
    rgbsps_set(pgm_read_byte(&LED_ALNUM[i]), 0, 0, 0);
  }

  rgbsps_set(LED_I, 15, 0, 15);
  rgbsps_set(LED_J, 15, 0, 15);
  rgbsps_set(LED_K, 15, 0, 15);
  rgbsps_set(LED_L, 15, 0, 15);

  rgbsps_set(LED_U, 15, 0, 10);
  rgbsps_set(LED_O, 15, 0, 10);
  rgbsps_set(LED_COMM, 15, 0, 10);
  rgbsps_set(LED_DOT, 15, 0, 10);
  rgbsps_set(LED_SCLN, 15, 0, 10);
  rgbsps_set(LED_P, 15, 0, 10);

  rgbsps_set(LED_Q, 10, 0, 15);
  rgbsps_set(LED_W, 10, 0, 15);
  rgbsps_set(LED_E, 10, 0, 15);
  rgbsps_set(LED_R, 10, 0, 15);
  rgbsps_set(LED_A, 10, 0, 15);
  rgbsps_set(LED_S, 10, 0, 15);
  rgbsps_set(LED_D, 10, 0, 15);
  rgbsps_set(LED_F, 10, 0, 15);
  rgbsps_set(LED_Z, 10, 0, 15);
  rgbsps_set(LED_X, 10, 0, 15);
  rgbsps_set(LED_C, 10, 0, 15);
  rgbsps_set(LED_V, 10, 0, 15);

  rgbsps_send();
}

void led_layer_punc(void) {
  rgbsps_set(LED_IND_FUNC, 0, 15, 0);
  rgbsps_set(LED_IND_NUM, 0, 0, 15);
  rgbsps_set(LED_IND_EMOJI, 0, 0, 0);

  led_reset();

  rgbsps_send();
}

void led_layer_num(void) {
  rgbsps_set(LED_IND_FUNC, 0, 0, 0);
  rgbsps_set(LED_IND_NUM, 0, 0, 15);
  rgbsps_set(LED_IND_EMOJI, 0, 0, 0);

  led_reset();

  for(uint8_t i = 0; i < COUNT(LED_ALNUM); i++) {
    rgbsps_set(pgm_read_byte(&LED_ALNUM[i]), 0, 0, 0);
  }

  rgbsps_set(LED_U, 0, 5, 15);
  rgbsps_set(LED_I, 0, 5, 15);
  rgbsps_set(LED_O, 0, 5, 15);
  rgbsps_set(LED_J, 0, 5, 15);
  rgbsps_set(LED_K, 0, 5, 15);
  rgbsps_set(LED_L, 0, 5, 15);
  rgbsps_set(LED_M, 0, 5, 15);
  rgbsps_set(LED_COMM, 0, 5, 15);
  rgbsps_set(LED_DOT, 0, 5, 15);
  rgbsps_set(LED_FUNC, 0, 5, 15);

  rgbsps_set(LED_EMOJI, 0, 10, 15);
  rgbsps_set(LED_RALT, 0, 10, 15);

  rgbsps_set(LED_Q, 0, 10, 15);
  rgbsps_set(LED_W, 0, 10, 15);
  rgbsps_set(LED_E, 0, 10, 15);
  rgbsps_set(LED_R, 0, 10, 15);
  rgbsps_set(LED_T, 0, 10, 15);
  rgbsps_set(LED_Y, 0, 10, 15);
  rgbsps_set(LED_P, 0, 10, 15);

  rgbsps_set(LED_A, 0, 15, 15);
  rgbsps_set(LED_S, 0, 15, 15);
  rgbsps_set(LED_D, 0, 15, 15);
  rgbsps_set(LED_F, 0, 15, 15);
  rgbsps_set(LED_Z, 0, 15, 15);
  rgbsps_set(LED_X, 0, 15, 15);
  rgbsps_set(LED_C, 0, 15, 15);
  rgbsps_set(LED_V, 0, 15, 15);

  rgbsps_send();
}

void led_layer_emoji(void) {
  rgbsps_setall(15, 15, 0);

  rgbsps_set(LED_IND_FUNC, 0, 0, 0);
  rgbsps_set(LED_IND_NUM, 0, 0, 0);
  rgbsps_set(LED_IND_EMOJI, 15, 15, 0);

  rgbsps_set(LED_PUNC, 15, 15, 15);
  rgbsps_set(LED_EMOJI, 15, 15, 15);

  rgbsps_send();
}

void led_layer_gui(void) {
  rgbsps_set(LED_IND_FUNC, 15, 10, 15);
  rgbsps_set(LED_IND_NUM, 15, 10, 15);
  rgbsps_set(LED_IND_EMOJI, 15, 10, 15);
  rgbsps_send();
}

void led_init(void) {
  // turn off all
  rgbsps_turnoff();

  // set trackpoint color
  rgbsps_set(LED_TRACKPOINT1, 15, 0, 0);
  rgbsps_set(LED_TRACKPOINT2, 0, 0, 15);
  rgbsps_set(LED_TRACKPOINT3, 15, 0, 0);

  // // hardcode indicator for now
  rgbsps_set(LED_IND_BLUETOOTH, 0, 0, 15);
  rgbsps_set(LED_IND_USB, 15, 15, 15);
  rgbsps_set(LED_IND_BATTERY, 0, 15, 0);

  led_layer_normal();
}


// keymaps

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  | Punc | Num  |    Space    | Func |Emoji |AltGr | GUI  | Ctrl |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = KEYMAP(
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT ,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  KC_LCTL, KC_LGUI, KC_LALT, PUNC,    NUM,     KC_SPC,  KC_SPC,  FUNC,    EMOJI,   KC_RALT, KC_RGUI, KC_RCTL
),

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  | Punc | Num  |    Space    | Func |Emoji |AltGr | GUI  | Ctrl |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = KEYMAP(
  KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
  KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_ENT ,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  KC_LCTL, KC_LGUI, KC_LALT, PUNC,    NUM,     KC_SPC,  KC_SPC,  FUNC,    EMOJI,   KC_RALT, KC_RGUI, KC_RCTL
),

/* Workman
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   D  |   R  |   W  |   B  |   J  |   F  |   U  |   P  |   ;  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   H  |   T  |   G  |   Y  |   N  |   E  |   O  |   I  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   M  |   C  |   V  |   K  |   K  |   ,  |   .  |   /  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  | Punc | Num  |    Space    | Func |Emoji |AltGr | GUI  | Ctrl |
 * `-----------------------------------------------------------------------------------'
 */
[_WORKMAN] = KEYMAP(
  KC_TAB,  KC_Q,    KC_D,    KC_R,    KC_W,    KC_B,    KC_J,    KC_F,    KC_U,    KC_P,    KC_SCLN, KC_BSPC,
  KC_ESC,  KC_A,    KC_S,    KC_H,    KC_T,    KC_G,    KC_Y,    KC_N,    KC_E,    KC_O,    KC_I,    KC_ENT ,
  KC_LSFT, KC_Z,    KC_X,    KC_M,    KC_C,    KC_V,    KC_K,    KC_L,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  KC_LCTL, KC_LGUI, KC_LALT, PUNC,    NUM,     KC_SPC,  KC_SPC,  FUNC,    EMOJI,   KC_RALT, KC_RGUI, KC_RCTL
),

/* Punc
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |   `  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |   \  |   -  |   =  |   <  |   >  |   (  |   )  |   '  |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |   |  |   _  |   +  |   {  |   }  |   [  |   ]  |   "  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_PUNC] = KEYMAP(
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_GRV ,
  XXXXXXX, XXXXXXX, KC_BSLS, KC_MINS,  KC_EQL, KC_LABK, KC_RABK, KC_LPRN, KC_RPRN, KC_QUOT, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, KC_PIPE, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_DQUO, XXXXXXX, XXXXXXX,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Num
 * ,-----------------------------------------------------------------------------------.
 * |  ^   |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |  @   |  A   |  B   |  C   |  (   |  )   |   4  |   5  |   6  |   :  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |  &   |  #   |  D   |  E   |  F   |  [   |  ]   |   1  |   2  |   3  |   /  |  *   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |  x   |      |             |   0  |   ,  |   .  |   +  |  -   |
 * `-----------------------------------------------------------------------------------'
 */
[_NUM] = KEYMAP(
  KC_CIRC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  KC_ESC,    KC_AT, S(KC_A), S(KC_B), S(KC_C), KC_LPRN, KC_RPRN,    KC_4,    KC_5,    KC_6, KC_COLN,  KC_ENT,
  KC_AMPR, KC_HASH, S(KC_D), S(KC_E), S(KC_F), KC_LBRC, KC_RBRC,    KC_1,    KC_2,    KC_3, KC_SLSH, KC_ASTR,
  _______, _______, _______,    KC_X, _______,  KC_SPC,  KC_SPC,    KC_0, KC_COMM,  KC_DOT, KC_PLUS, KC_MINS
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
    X(POO), X(EYES),X(HUNRD), _______,X(SKULL),X(HORNS), X(HALO), X(FEAR), _______,X(YUMMY),X(DISAP),X(NOEVK)
),

/* GUI
 * ,-----------------------------------------------------------------------------------.
 * |      |  D1  |  D2  |  D3  |  D4  |  D5  |  D6  |  D7  |  D8  |  D9  |  D10 |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |Linux |      | Vol- | Mute | Vol+ |      |      |  D-  |      |  D+  |      |Qwerty|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Win  |      | Prev | Play | Next |      |      |      |      |      |      |Colmak|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | OSX  |      |      |      |      |  BL- |  BL+ |      |      |      |      |Workmn|
 * `-----------------------------------------------------------------------------------'
 */
[_GUI] = KEYMAP(
  _______, LGUI(KC_1),LGUI(KC_2),LGUI(KC_3),LGUI(KC_4),LGUI(KC_5),LGUI(KC_6),LGUI(KC_7),LGUI(KC_8),LGUI(KC_9),LGUI(KC_0), _______,
    LINUX, _______, KC_VOLD, KC_MUTE, KC_VOLU,_______,_______,KC_WWW_BACK,_______,KC_WWW_FORWARD,_______, QWERTY,
      WIN, _______, KC_MPRV, KC_MPLY, KC_MNXT, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, COLEMAK,
      OSX, _______, _______, _______, _______,  BL_DEC,  BL_INC, _______, _______, RGB_VAI, RGB_VAD, WORKMAN
),

};

#ifdef AUDIO_ENABLE
float tone_startup[][2]    = SONG(STARTUP_SOUND);
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
float tone_workman[][2]    = SONG(DVORAK_SOUND);
float tone_goodbye[][2] = SONG(GOODBYE_SOUND);
float tone_linux[][2] = SONG(CAPS_LOCK_ON_SOUND);
float tone_windows[][2] = SONG(SCROLL_LOCK_ON_SOUND);
float tone_osx[][2] = SONG(NUM_LOCK_ON_SOUND);
float tone_click[][2] = SONG(MUSICAL_NOTE(_F3, 2));
#endif

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  #ifdef AUDIO_ENABLE
  // faux clicky
  if (record->event.pressed) PLAY_NOTE_ARRAY(tone_click, false, 0);
  #endif

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
        #endif
        persistant_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_colemak, false, 0);
        #endif
        persistant_default_layer_set(1UL<<_COLEMAK);
      }
      return false;
      break;
    case WORKMAN:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_workman, false, 0);
        #endif
        persistant_default_layer_set(1UL<<_WORKMAN);
      }
      return false;
      break;



    case PUNC:
      if (record->event.pressed) {
        layer_on(_PUNC);
        update_tri_layer(_PUNC, _EMOJI, _GUI);
        if (IS_LAYER_ON(_GUI)) {
          led_layer_gui();
        } else {
          led_layer_punc();;
        }
      } else {
        layer_off(_PUNC);
        update_tri_layer(_PUNC, _EMOJI, _GUI);
        if (IS_LAYER_ON(_EMOJI)) {
          led_layer_emoji();
        } else {
          led_layer_normal();;
        }
      }
      return false;
      break;
    case EMOJI:
      if (record->event.pressed) {
        layer_on(_EMOJI);
        update_tri_layer(_PUNC, _EMOJI, _GUI);
        if (IS_LAYER_ON(_GUI)) {
          led_layer_gui();
        } else {
          led_layer_emoji();;
        }
      } else {
        layer_off(_EMOJI);
        update_tri_layer(_PUNC, _EMOJI, _GUI);
        if (IS_LAYER_ON(_PUNC)) {
          led_layer_punc();
        } else {
          led_layer_normal();;
        }
      }
      return false;
      break;
    case NUM:
      if (record->event.pressed) {
        layer_on(_NUM);
        led_layer_num();
      } else {
        layer_off(_NUM);
        led_layer_normal();
      }
      return false;
      break;
    case FUNC:
      if (record->event.pressed) {
        layer_on(_FUNC);
        led_layer_func();
      } else {
        layer_off(_FUNC);
        led_layer_normal();
      }
      return false;
      break;


    case LINUX:
      set_unicode_input_mode(UC_LNX);
      #ifdef AUDIO_ENABLE
        PLAY_NOTE_ARRAY(tone_linux, false, 0);
      #endif
      return false;
      break;
    case WIN:
      set_unicode_input_mode(UC_WINC);
      #ifdef AUDIO_ENABLE
        PLAY_NOTE_ARRAY(tone_windows, false, 0);
      #endif
      return false;
      break;
    case OSX:
      set_unicode_input_mode(UC_OSX);
      #ifdef AUDIO_ENABLE
        PLAY_NOTE_ARRAY(tone_osx, false, 0);
      #endif
      return false;
      break;
  }
  return true;
}

void matrix_init_user(void) {
  #ifdef AUDIO_ENABLE
      startup_user();
  #endif
  set_unicode_input_mode(UC_LNX);
  led_init();
}

// void init_rgblight(void) {
//   for (uint8_t i = 0; i < RGBLED_NUM; i++) {
//     led[i].r = 255;
//     led[i].g = 85;
//     led[i].b = 0;
//   }
//   ws2812_setleds(led, RGBLED_NUM);
// }


#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
    PLAY_NOTE_ARRAY(tone_startup, false, 0);
}

void shutdown_user()
{
    PLAY_NOTE_ARRAY(tone_goodbye, false, 0);
    _delay_ms(150);
    stop_all_notes();
}

#endif