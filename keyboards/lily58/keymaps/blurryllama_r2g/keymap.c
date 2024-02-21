#include QMK_KEYBOARD_H
#include "os_detection.h"





enum custom_layers {
  _QWERTY,
  _FN,
  _ADJ,
//   _RAISE,
//   _FN2,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  FN,
  ADJ,
  SS,
  CALC,
  LOCK,
  INSP,
  KILL,
  VOLMAN,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  =   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |  \   |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |  TAB | /Space  /       \Enter \  |BackSP|  DEL  |FN    |
 *                   |      |      |      |/       /         \      \ |      |       |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL,
  KC_GRV,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
  KC_LCTL, KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
                           KC_LALT, KC_LGUI, KC_TAB,  KC_SPC,   KC_ENT,  KC_BSPC, KC_DEL, FN
),
/* FN
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  | F9  |  F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | F12  |      |      |  up  |  ADJ | PGUP |                    |      |      | INSP |      | P/S  | HOME |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | CAPS |      |  lft |  dwn |  rt  | PGDN |-------.    ,-------|      |      | KILL | LOCK |      | END  |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      | CALC |VOLMAN| BACK |-------|    |-------| NEXT | MUTE | VOLD | VOLU |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |       |     | /       /       \ PLAY \  |      |       |      |
 *                   |      |       |     |/       /         \ PAUSE\ |      |       |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_FN] = LAYOUT(
  _______,   KC_F1,   KC_F2,   KC_F3,     KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  KC_F12,  _______, _______,   KC_UP,       ADJ, KC_PGUP,                   _______, _______,    INSP, _______,      SS, KC_HOME,
  KC_CAPS, _______, KC_LEFT, KC_DOWN,  KC_RIGHT, KC_PGDN,                   _______, _______,    KILL,    LOCK, _______,  KC_END,
  _______, _______, _______,    CALC,  VOLMAN,  KC_MPRV, _______, _______, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,
                             _______,  _______,  _______, _______, KC_MPLY, _______, _______, _______
),

/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      | ADJ  |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |RGBTOG|RGBHUI|RGBSAI|RGBVAI|RGBSPI|      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |RGBMOD|RGBHUD|RGBSAD|RGBVAD|RGBSPD|      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |  TAB | /Space  /       \Enter \  |BackSP|  DEL |FN    |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

  [_ADJ] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                             _______, _______, _______, _______, _______,  _______, _______, _______
  )
};


oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_keyboard_master())
    return OLED_ROTATION_270;// flips the display 180 degrees if offhand
    else
    return OLED_ROTATION_180;
  return rotation;
}

static const char PROGMEM windows_logo[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbc, 0xbc, 0xbe, 0xbe, 0x00, 0xbe, 0xbe, 0xbf, 0xbf, 0xbf, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x0f, 0x0f, 0x00, 0x0f, 0x0f, 0x1f, 0x1f, 0x1f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const char PROGMEM mac_logo[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xf0, 0xf8, 0xf8, 0xf8, 0xf0, 0xf6, 0xfb, 0xfb, 0x38, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x0f, 0x1f, 0x1f, 0x0f, 0x0f, 0x1f, 0x1f, 0x0f, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const char PROGMEM qmk_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192, 96, 48, 96,192,128,  0,  0,  0, 64,224, 64, 64,192,224,192, 64,224,240,224, 64,  0,  0,  0,  0,  0,  0,192,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,128,  0,  0,  0,128,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,192,192,192,192,192,192,192,192,128,  0,  0,  0,  0,  0,  0,128,128,192,192,192,192,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 62,242,130,  6,  4,  4, 12, 12,  8, 30, 51, 97,192,128,  0,  0,  3,126,248, 64,228,255,238, 68, 96,241, 96, 68, 78,255, 68,  0,  0,  0,  0,  0,  0,  0,255,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,240,241,  0,  0,  0,  0,255,255,  0,  0,  0, 48,240,240,128,  0,  0,  0,  0,  0,128,240,240, 48,  0,  0,127,255,255,225,113,113,241,241,225,193,129,  0,  0,  0,  0, 12, 63,255,243,225,193,193,129,129,195,255,127, 28,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0, 96,240,144,152,140,  4,  6,  7,  2,  2,  2,  2,  2,  2,  6,  4,  4,136,225,179, 48, 24,  4,  7,  2,  2,  3,  2,  2,  6,  4, 12,136,216,112, 96,  0,  0,  0,  0,  0,  0,  0,255,255,128,128,128,128,128,128,128,128,128,  0,  0,255,255,  0,  0,  0,  0,255,255,128,  0,  0,  0,  0,  3, 31,126,248,224,240,126, 31,  3,  0,  0,  0,  0,224,224,192,192,128,128,128,192,225,255,127, 63,  0,  0,  0, 62,255,255,193,192,128,129,129,195,195,255,254, 60,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  3,  2,  2,  2,  2,  2,  2,  2,  2,  3,  1,  1,  0,  1,  1,  3,  2,  2,  2,  2,  2,  2,  2,  2,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  1,  1,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0, 96, 96,112, 56, 31, 15,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    };
/* KEYBOARD PET START */

/* settings */
#    define MIN_WALK_SPEED      10
#    define MIN_RUN_SPEED       40

/* advanced settings */
#    define ANIM_FRAME_DURATION 200  // how long each frame lasts in ms
#    define ANIM_SIZE           96   // number of bytes in array. If you change sprites, minimize for adequate firmware size. max is 1024

/* timers */
uint32_t anim_timer = 0;
uint32_t anim_sleep = 0;

/* current frame */
uint8_t current_frame = 0;

/* status variables */
int   current_wpm = 0;
led_t led_usb_state;


bool isBarking = false;
bool isSneaking = false;
bool isJumping  = false;
bool showedJump = true;
bool isShft = false;
bool isCtrl = false;
bool isAlt = false;
bool isGui = false;
bool isFun = false;
bool isAdj = false;
uint8_t previousOs;

/* logic */
static void render_luna(int LUNA_X, int LUNA_Y) {
    /* Sit */
    static const char PROGMEM sit[2][ANIM_SIZE] = {/* 'sit1', 32x22px */
                                                   {
                                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c, 0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x68, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28, 0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                   },

                                                   /* 'sit2', 32x22px */
                                                   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c, 0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x90, 0x08, 0x18, 0x60, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0e, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28, 0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

    /* Walk */
    static const char PROGMEM walk[2][ANIM_SIZE] = {/* 'walk1', 32x22px */
                                                    {
                                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x90, 0x90, 0x90, 0xa0, 0xc0, 0x80, 0x80, 0x80, 0x70, 0x08, 0x14, 0x08, 0x90, 0x10, 0x10, 0x08, 0xa4, 0x78, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0xfc, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x18, 0xea, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x03, 0x06, 0x18, 0x20, 0x20, 0x3c, 0x0c, 0x12, 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    },

                                                    /* 'walk2', 32x22px */
                                                    {
                                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x20, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x28, 0x10, 0x20, 0x20, 0x20, 0x10, 0x48, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x20, 0xf8, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 0x30, 0xd5, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e, 0x02, 0x1c, 0x14, 0x08, 0x10, 0x20, 0x2c, 0x32, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    }};

    /* Run */
    static const char PROGMEM run[2][ANIM_SIZE] = {/* 'run1', 32x22px */
                                                   {
                                                       0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x08, 0xc8, 0xb0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x40, 0x40, 0x3c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0xc4, 0xa4, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x58, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x09, 0x04, 0x04, 0x04, 0x04, 0x02, 0x03, 0x02, 0x01, 0x01, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                   },

                                                   /* 'run2', 32x22px */
                                                   {
                                                       0x00, 0x00, 0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x78, 0x28, 0x08, 0x10, 0x20, 0x30, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0xb0, 0x50, 0x55, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x1e, 0x20, 0x20, 0x18, 0x0c, 0x14, 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                   }};

    /* Bark */
    static const char PROGMEM bark[2][ANIM_SIZE] = {/* 'bark1', 32x22px */
                                                    {
                                                        0x00, 0xc0, 0x20, 0x10, 0xd0, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x3c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x48, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    },

                                                    /* 'bark2', 32x22px */
                                                    {
                                                        0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x40, 0x2c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x48, 0x28, 0x2a, 0x10, 0x0f, 0x20, 0x4a, 0x09, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    }};

    /* Sneak */
    static const char PROGMEM sneak[2][ANIM_SIZE] = {/* 'sneak1', 32x22px */
                                                     {
                                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x40, 0x40, 0x80, 0x00, 0x80, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x21, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x04, 0x04, 0x04, 0x03, 0x01, 0x00, 0x00, 0x09, 0x01, 0x80, 0x80, 0xab, 0x04, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x02, 0x06, 0x18, 0x20, 0x20, 0x38, 0x08, 0x10, 0x18, 0x04, 0x04, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00,
                                                     },

                                                     /* 'sneak2', 32x22px */
                                                     {
                                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xa0, 0x20, 0x40, 0x80, 0xc0, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x41, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x02, 0x04, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x40, 0x40, 0x55, 0x82, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e, 0x04, 0x18, 0x10, 0x08, 0x10, 0x20, 0x28, 0x34, 0x06, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                     }};

    /* animation */
    void animate_luna(void) {
        /* jump */
        if (isJumping || !showedJump) {
            /* clear */
            oled_set_cursor(LUNA_X, LUNA_Y + 2);
            oled_write("     ", false);

            oled_set_cursor(LUNA_X, LUNA_Y - 1);

            showedJump = true;
        } else {
            /* clear */
            oled_set_cursor(LUNA_X, LUNA_Y - 1);
            oled_write("     ", false);

            oled_set_cursor(LUNA_X, LUNA_Y);
        }
        /* switch frame */
        current_frame = (current_frame + 1) % 2;

        /* current status */
        if (led_usb_state.caps_lock) {
            oled_write_raw_P(bark[abs(1 - current_frame)], ANIM_SIZE);

        } else if (isBarking) {
            oled_write_raw_P(bark[abs(1 - current_frame)], ANIM_SIZE);

        } else if (isSneaking) {
            oled_write_raw_P(sneak[abs(1 - current_frame)], ANIM_SIZE);

        } else if (current_wpm <= MIN_WALK_SPEED) {
            oled_write_raw_P(sit[abs(1 - current_frame)], ANIM_SIZE);

        } else if (current_wpm <= MIN_RUN_SPEED) {
            oled_write_raw_P(walk[abs(1 - current_frame)], ANIM_SIZE);

        } else {
            oled_write_raw_P(run[abs(1 - current_frame)], ANIM_SIZE);
        }
    }

    /* animation timer */
    if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
        anim_timer = timer_read32();
        animate_luna();
    }

}


/* KEYBOARD PET END */

char wpm_str[16];


bool oled_task_user(void) {
    if (!is_oled_on()) {
        oled_on();
    }
    current_wpm   = get_current_wpm();
    led_usb_state = host_keyboard_led_state();
    if (is_keyboard_master()) {
        oled_set_cursor(0, 0);

        if (keymap_config.swap_lctl_lgui) {
            oled_write_raw_P(mac_logo, sizeof(mac_logo));
        } else {
            oled_write_raw_P(windows_logo, sizeof(windows_logo));
        }

        if (isShft) {
            oled_set_cursor(1, 3);
            oled_write("SHFT", false);
        } else {
            oled_set_cursor(1, 3);
            oled_write("    ", false);
        }
        if (isCtrl) {
            if (keymap_config.swap_lctl_lgui) {
                oled_set_cursor(1, 4);
                oled_write(" CMD", false);
            } else {
                oled_set_cursor(1, 4);
                oled_write("CTRL", false);
            }
        } else {
            oled_set_cursor(1, 4);
            oled_write("    ", false);
        }
        if (isAlt) {
            if (keymap_config.swap_lctl_lgui) {
                oled_set_cursor(1, 5);
                oled_write(" OPT", false);
            } else {
                oled_set_cursor(1, 5);
                oled_write(" ALT", false);
            }
        } else {
            oled_set_cursor(1, 5);
            oled_write("    ", false);
        }
        if (isGui) {
            if (keymap_config.swap_lctl_lgui) {
                oled_set_cursor(1, 6);
                oled_write("CTRL", false);
            } else {
                oled_set_cursor(1, 6);
                oled_write(" WIN", false);
            }
        } else {
            oled_set_cursor(1, 6);
            oled_write("    ", false);
        }
        if (isFun) {
            oled_set_cursor(1, 7);
            oled_write("  Fn", false);
        } else {
            oled_set_cursor(1, 7);
            oled_write("    ", false);
        }
        if (led_usb_state.caps_lock) {
            oled_set_cursor(1, 9);
            oled_write("CAPS", true);
        } else {
            oled_set_cursor(0, 9);
            oled_write("      ", false);
        }
        if (isAdj) {
            oled_set_cursor(1, 10);
            oled_write(" RGB", false);
        } else {
            oled_set_cursor(1, 10);
            oled_write("    ", false);
        }
        render_luna(0, 13);
    } else {
        oled_write_raw_P(qmk_logo, sizeof(qmk_logo));
    }
    return true;
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t host_os = detected_host_os();
    if (previousOs != host_os) {
        previousOs = host_os;
        if (host_os == OS_MACOS || host_os == OS_IOS) {
            process_magic(CG_SWAP, record);
        } else {
            process_magic(CG_NORM, record);
        }
    }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case FN:
      if (record->event.pressed) {
        isFun = true;
        layer_on(_FN);
      } else {
        isFun = false;
        layer_off(_FN);
      }
      return false;
      break;
    case ADJ:
      if (record->event.pressed) {
        if (isAdj) {
            isAdj = false;
            layer_off(_ADJ);

        } else {
            isAdj = true;
            layer_on(_ADJ);
        }
      }
      return false;
      break;
    case SS:
        if (record->event.pressed) {
            if (keymap_config.swap_lctl_lgui) { // mac action
                register_mods(mod_config(MOD_LCTL));
                register_mods(mod_config(MOD_LSFT));
                register_code(KC_5);
            } else { // windows action
                register_mods(mod_config(MOD_LGUI));
                register_mods(mod_config(MOD_LSFT));
                register_code(KC_S);
            }
        }
        else {
            if (keymap_config.swap_lctl_lgui) { // mac action
                unregister_mods(mod_config(MOD_LCTL));
                unregister_mods(mod_config(MOD_LSFT));
                unregister_code(KC_5);
            } else { // windows action
                unregister_mods(mod_config(MOD_LGUI));
                unregister_mods(mod_config(MOD_LSFT));
                unregister_code(KC_S);
            }
        }
        return false;
        break;
    case CALC:
        if (record->event.pressed) {
            if (keymap_config.swap_lctl_lgui) { // mac action
                register_mods(mod_config(MOD_LGUI));
                register_mods(mod_config(MOD_LALT));
                register_code(KC_C);
            } else { // windows action
                register_code(KC_CALC);
            }
        } else {
            if (keymap_config.swap_lctl_lgui) { // mac action
                unregister_mods(mod_config(MOD_LGUI));
                unregister_mods(mod_config(MOD_LALT));
                unregister_code(KC_C);
            } else { // windows action
                unregister_code(KC_CALC);
            }
        }
        return false;
        break;
    case INSP:
        if (record->event.pressed) {
            if (keymap_config.swap_lctl_lgui) { // mac action
                register_mods(mod_config(MOD_LCTL));
                register_mods(mod_config(MOD_LALT));
                register_code(KC_I);
            } else { // windows action
                register_mods(mod_config(MOD_LCTL));
                register_mods(mod_config(MOD_LSFT));
                register_code(KC_I);
            }
        } else {
            if (keymap_config.swap_lctl_lgui) { // mac action
                unregister_mods(mod_config(MOD_LCTL));
                unregister_mods(mod_config(MOD_LALT));
                unregister_code(KC_I);
            } else { // windows action
                unregister_mods(mod_config(MOD_LCTL));
                unregister_mods(mod_config(MOD_LSFT));
                unregister_code(KC_I);
            }
        }
        return false;
        break;
    case KILL:
        if (record->event.pressed) {
            if (keymap_config.swap_lctl_lgui) { // mac action
                register_mods(mod_config(MOD_LGUI));
                register_mods(mod_config(MOD_LALT));
                register_code(KC_ESC);
            } else { // windows action
                register_mods(mod_config(MOD_LALT));
                register_code(KC_F4);
            }
        } else {
            if (keymap_config.swap_lctl_lgui) { // mac action
                unregister_mods(mod_config(MOD_LGUI));
                unregister_mods(mod_config(MOD_LALT));
                unregister_code(KC_ESC);
            } else { // windows action
                unregister_mods(mod_config(MOD_LALT));
                unregister_code(KC_F4);
            }
        }
        return false;
        break;
    case LOCK:
        if (record->event.pressed) {
            if (keymap_config.swap_lctl_lgui) { // mac action
                register_mods(mod_config(MOD_LGUI));
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_Q);
            } else { // windows action
                register_mods(mod_config(MOD_LGUI));
                register_code(KC_L);
            }
        } else {
            if (keymap_config.swap_lctl_lgui) { // mac action
                unregister_mods(mod_config(MOD_LGUI));
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_Q);
            } else { // windows action
                unregister_mods(mod_config(MOD_LGUI));
                unregister_code(KC_L);
            }
        }
        return false;
        break;
    case VOLMAN:
        if (record->event.pressed) {
            if (keymap_config.swap_lctl_lgui) { // mac action
                // No Mac Action
            } else { // windows action
                register_mods(mod_config(MOD_LCTL));
                register_mods(mod_config(MOD_LALT));
                register_code(KC_V);
            }
        } else {
            if (keymap_config.swap_lctl_lgui) { // mac action
                // No Mac Action
            } else { // windows action
                unregister_mods(mod_config(MOD_LCTL));
                unregister_mods(mod_config(MOD_LALT));
                unregister_code(KC_V);
            }
        }
        return false;
        break;
        /* KEYBOARD PET STATUS START */
    case KC_LCTL:
    case KC_RCTL:
        if (record->event.pressed) {
            isCtrl = true;
            isSneaking = true;
        } else {
            isCtrl = false;
            isSneaking = false;
        }
        break;
    case KC_LSFT:
    case KC_RSFT:
        if (record->event.pressed) {
            isShft = true;
            isBarking = true;
        } else {
            isShft = false;
            isBarking = false;
        }
        break;
    case KC_LALT:
    case KC_RALT:
        if (record->event.pressed) {
            isAlt = true;
        } else {
            isAlt = false;
        }
      break;
    case KC_LGUI:
    case KC_RGUI:
        if (record->event.pressed) {
            isGui = true;
        } else {
            isGui = false;
        }
        break;
    case KC_SPC:
        if (record->event.pressed) {
            isJumping  = true;
            showedJump = false;
        } else {
            isJumping = false;
        }
        break;
            /* KEYBOARD PET STATUS END */
    }
  return true;
}
