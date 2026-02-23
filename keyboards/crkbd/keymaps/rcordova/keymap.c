#include QMK_KEYBOARD_H

// ──────────────────────────────────────────────────────────────
// Keymaps
// ──────────────────────────────────────────────────────────────

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* ┌────────────────────────────── Layer 0: Base ───────────────────────────────┐
   * │  GESC    Q     W     E     R     T   │   Y     U     I     O     P     \   │
   * │  TAB     A     S     D     F     G   │   H     J     K     L     ;     '   │
   * │  BSPC     Z     X     C     V     B   │   N     M     ,     .     /   DEL │
   * │                 GUI/ESC  MO(1)  SPC  │  ENT  MO(2)  ALT/TAB               │
   * └───────────────────────────────────────────────────────────────────────────┘
   *
   * Notes:
   * - QK_GESC = Esc, but becomes `~ when Shift is held (see GRAVE_ESC_* overrides).
   * - Outer thumbs: tap Esc/Tab, hold Win/Alt (Windows-friendly).
   */
  [0] = LAYOUT_split_3x6_3(
    QK_GESC,           KC_Q,            KC_W,            KC_E,            KC_R,            KC_T,              KC_Y,            KC_U,            KC_I,            KC_O,            KC_P,            KC_BSLS,
    KC_TAB,            LGUI_T(KC_A),     LALT_T(KC_S),    LSFT_T(KC_D),    LCTL_T(KC_F),    KC_G,             KC_H,            RCTL_T(KC_J),     RSFT_T(KC_K),     RALT_T(KC_L),     RGUI_T(KC_SCLN),  KC_QUOT,
    KC_BSPC,           KC_Z,            KC_X,            KC_C,            KC_V,            KC_B,              KC_N,            KC_M,            KC_COMM,         KC_DOT,          KC_SLSH,         KC_DEL,
                                         LGUI_T(KC_ESC),  MO(1),          LSFT_T(KC_SPC),                     RCTL_T(KC_ENT),  MO(2),           LALT_T(KC_TAB)
  ),

  /* ┌────────────────────────── Layer 1: Symbols / Media ─────────────────────────┐
   * │  TO(0)    _     !     @     #     [  │   ]     7     8     9     +     -    |
   * │   _     VOL+    $     %     ^     {  │   }     4     5     6     *     /    │
   * │   _     VOL-    &     *     (     )  │   0     1     2     3     +     =    │
   * │                 PREV    _     _      │  PLAY    _    NEXT                   │
   * └─────────────────────────────────────────────────────────────────────────────┘
   */
  [1] = LAYOUT_split_3x6_3(
    TO(0),            _______,         KC_EXLM,         KC_AT,           KC_HASH,         KC_LBRC,           KC_RCBR,         KC_7,            KC_8,            KC_9,            KC_PLUS,         KC_MINS,
    _______,          KC_VOLU,         KC_DLR,          KC_PERC,         KC_CIRC,         KC_LCBR,           KC_RCBR,         KC_4,            KC_5,            KC_6,            KC_ASTR,         KC_SLSH,
    _______,          KC_VOLD,         KC_AMPR,         KC_ASTR,         KC_LPRN,         KC_RPRN,           KC_0,            KC_1,            KC_2,            KC_3,            KC_PLUS,         KC_EQUAL,
                                                        KC_MPRV,        _______,         _______,            KC_MPLY,          _______,         KC_MNXT
  ),

  /* ┌──────────────────────────── Layer 2: F-keys / Nav ───────────────────────────┐
   * │  TO(0)   F1    F2    F3    F4    F5 │  PGUP  HOME   UP    END  PGDN    _     │
   * │   _      F6    F7    F8    F9   F10 │   _    LEFT  DOWN  RGHT    _     _     │
   * │   _       _     _     _   F11   F12 │   _   Ctrl←   _   Ctrl→    _     _     │
   * │                  _     _    SPC     │    _     _     _                       │
   * └──────────────────────────────────────────────────────────────────────────────┘
   */
  [2] = LAYOUT_split_3x6_3(
    TO(0),            KC_F1,           KC_F2,           KC_F3,           KC_F4,           KC_F5,             KC_PGUP,         KC_HOME,         KC_UP,           KC_END,          KC_PGDN,         _______,
    _______,          KC_F6,           KC_F7,           KC_F8,           KC_F9,           KC_F10,            _______,         KC_LEFT,         KC_DOWN,         KC_RGHT,         _______,         _______,
    _______,          _______,         _______,         _______,         KC_F11,          KC_F12,            _______,         LCTL(KC_LEFT),    _______,         LCTL(KC_RGHT),   _______,         _______,
                                                        _______,         _______,         _______,           _______,         _______,         _______
  ),

  /* ┌──────────────────────────── Layer 3: RGB Matrix / Boot ──────────────────────┐
   * │  TO(0)    _     _     _     _     _  │   _     _     _     _     _   BOOT   │
   * │  RM_TG  HUE+  SAT+  VAL+  SPD+   _   │   _     _     _     _     _     _    │
   * │  RM_NX  HUE-  SAT-  VAL-  SPD-   _   │   _     _     _     _     _     _    │
   * │                  _     _     _       │   _     _     _                  │
   * └──────────────────────────────────────────────────────────────────────────────┘
   */
  [3] = LAYOUT_split_3x6_3(
    TO(0),            _______,         _______,         _______,         _______,         _______,           _______,         _______,         _______,         _______,         _______,         QK_BOOT,
    RM_TOGG,          RM_HUEU,         RM_SATU,         RM_VALU,         RM_SPDU,         _______,           _______,         _______,         _______,         _______,         _______,         _______,
    RM_NEXT,          RM_HUED,         RM_SATD,         RM_VALD,         RM_SPDD,         _______,           _______,         _______,         _______,         _______,         _______,         _______,
                                                        _______,         _______,         _______,           _______,         _______,         _______
  ),
};

void keyboard_post_init_user(void) {
    rgb_matrix_enable();  // force on after boot
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, 1, 2, 3);
}
// ──────────────────────────────────────────────────────────────
// OLED (Right: logo + rain + TV glitch, Left: layer + WPM)
// Master (LEFT) controls sleep/wake; slave follows via SPLIT_OLED_ENABLE.
// ──────────────────────────────────────────────────────────────

#ifdef OLED_ENABLE

#include "timer.h"
#include "wpm.h"
#include <stdio.h>
#include <string.h>
#include <avr/pgmspace.h>
#include "rgb_matrix.h"

// ──────────────────────────────────────────────────────────────
// RGB idle effect swap (rainbow chevron when OLED sleeps)
// ──────────────────────────────────────────────────────────────
#ifdef RGB_MATRIX_ENABLE
static bool     rgb_idle_active = false;
static uint8_t  rgb_saved_mode  = 0;
static uint8_t  rgb_saved_hue   = 0;
static uint8_t  rgb_saved_sat   = 0;
static uint8_t  rgb_saved_val   = 0;
static uint8_t  rgb_saved_speed = 0;

static void rgb_enter_idle(void) {
    if (rgb_idle_active) return;
    rgb_idle_active = true;

    rgb_saved_mode  = rgb_matrix_get_mode();
    rgb_saved_hue   = rgb_matrix_config.hsv.h;
    rgb_saved_sat   = rgb_matrix_config.hsv.s;
    rgb_saved_val   = rgb_matrix_config.hsv.v;
    rgb_saved_speed = rgb_matrix_config.speed;

    rgb_matrix_mode_noeeprom(RGB_MATRIX_RAINBOW_MOVING_CHEVRON);
}

static void rgb_exit_idle(void) {
    if (!rgb_idle_active) return;
    rgb_idle_active = false;

    rgb_matrix_mode_noeeprom(rgb_saved_mode);
    rgb_matrix_sethsv_noeeprom(rgb_saved_hue, rgb_saved_sat, rgb_saved_val);
    rgb_matrix_set_speed_noeeprom(rgb_saved_speed);
}
#endif

// ──────────────────────────────────────────────────────────────
// OLED globals / geometry
// ──────────────────────────────────────────────────────────────
#define OLED_IDLE_TIMEOUT_MS (60000UL * 3UL)   // 3 minutes

#define OLED_W      128 // width of oled screen
#define OLED_H       32 // height of oled screen
#define OLED_BYTES  (OLED_W * OLED_H / 8) // how much space on screen in pages of 8 bytes

// ───────── Left OLED sprite + status ─────────
#define SPR_W 32 // doom guy widht
#define SPR_H 32 // doom guy height
#define TEXT_COL 6 //the column where ill start text so it does not overlap with the sprite

#define SPR_SRC_CHUNK_W 32 // useful to check if sprite pages are page major (32 bytes)
#define SPR_SWAP_BITS 0 // useful if i export the sprites with bytes swap enabled

#define DOOM_X 0 //position to start drawing doom x axis
#define DOOM_Y 0 // same but y axis

// dragon slayer sword sprites values
#define SWORD_W 96
#define SWORD_H 32
#define SWORD_X 32
#define SWORD_Y 0

static uint32_t oled_last_activity_ms = 0;
static uint16_t wpm_peak = 0;

#define DOOM_FRAME_MS 333 // how fast the doom guy animation runs in ms
static uint32_t doom_last_anim_ms = 0;
static uint8_t  doom_frame_idx   = 0;

// ──────────────────────────────────────────────────────────────
// Dragonslayer (96x32) 
// ──────────────────────────────────────────────────────────────
static const uint8_t PROGMEM dragonslayer_sword[] = {
    // 'dragonSlayer', 96x32px
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x80, 0xc0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
    0x80, 0xf0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 
    0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 
    0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0x80, 0x80, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
    0x03, 0x0f, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 
    0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 
    0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x03, 0x01, 0x01, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// ──────────────────────────────────────────────────────────────
// Doomguy frames (32x32) - your bytes
// ──────────────────────────────────────────────────────────────
static const uint8_t PROGMEM doomguyAngry[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0xe0, 0x30, 0x1c, 0xee, 0xcb, 0xcf, 0xe1, 0x01, 0xc1, 0xe1, 0xff, 0xcf, 0x00, 0x00, 
    0x90, 0xfe, 0x3f, 0x1f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x03, 0x07, 0x18, 0x13, 0x69, 0x73, 0xe3, 0xc0, 0xc0, 0xc3, 0xff, 0xf8, 0x80, 0x00, 
    0x04, 0x3f, 0x7e, 0x3c, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8_t PROGMEM doomguyLeft[] = {
    0x00, 0x00, 0xc0, 0xe0, 0xf0, 0xb0, 0x90, 0x10, 0x10, 0x80, 0x10, 0xb0, 0xb0, 0xb0, 0x30, 0x30, 
    0x00, 0xc0, 0xf0, 0xf0, 0xf0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x07, 0x07, 0x00, 0xcf, 0xcf, 0x87, 0x82, 0xcf, 0xe0, 0xfb, 0xf3, 0xf3, 0xe3, 0xc2, 
    0x80, 0x06, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x01, 0x11, 0xff, 0xf8, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x0d, 0x01, 0x00, 0x03, 0x07, 0x07, 0x06, 
    0x00, 0x04, 0x03, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8_t PROGMEM doomguyRight[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xd0, 0xd8, 0xc0, 0xc0, 0x80, 0xe0, 0xf0, 0xb0, 0x80, 
    0x40, 0x00, 0xe0, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
    0x00, 0xf0, 0xf0, 0xc0, 0x02, 0xf1, 0xf1, 0x21, 0xf9, 0x03, 0x03, 0xef, 0xe7, 0xe3, 0x21, 0x01, 
    0x00, 0xf8, 0xff, 0xff, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x1f, 0x0f, 0x03, 0x00, 0x00, 
    0x00, 0x01, 0x03, 0x07, 0x07, 0x06, 0x04, 0x04, 0x00, 0x04, 0x04, 0x06, 0x0e, 0x06, 0x06, 0x00, 
    0x00, 0x01, 0x07, 0x07, 0x07, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// store only animation frames here to swap when animation is running
static const uint8_t *const doom_frames[] PROGMEM = {
    doomguyLeft,
    doomguyRight
};
// useful to count frames and not hardcoded it in code
#define DOOM_FRAME_COUNT (sizeof(doom_frames) / sizeof(doom_frames[0]))

//oled screens expects bits in the oposite vertical order, so useful for swapping them i.e. ghef cdab → hgfedcba
static inline uint8_t reverse8(uint8_t b) {
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
    return b;
}

// ──────────────────────────────────────────────────────────────
// LEFT OLED: TV glitch but ONLY for regions we blit (doom/sword)
// ──────────────────────────────────────────────────────────────
#define LEFT_FX_PERIOD_MS    3000 // interval when we apply the effect
#define LEFT_FX_DURATION_MS  1500 // how much time the effect lasts
#define LEFT_FX_MAX_PASSES      4 // how much effect we give to the renderer

//rng seed for left oled display
static uint32_t left_rng_state = 0xC0FFEE01u;
//fast code generate the rng state without crypto
static uint32_t left_xorshift32(void) {
    uint32_t x = left_rng_state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    left_rng_state = x;
    return x;
}
//useful if i only need one rng bit
static inline uint8_t left_rand8(void) {
    return (uint8_t)left_xorshift32();
}
// pick a random page 
static inline uint8_t left_rand_u8(uint8_t max_exclusive) {
    return (uint8_t)(left_xorshift32() % max_exclusive);
}
//In SSD1306-style buffers, one byte = a vertical column of 8 pixels (one “page” tall). Each bit is one pixel in that vertical slice.
static inline uint8_t tvfx_byte(uint8_t orig, uint8_t amt) {
    //just return and do nothing if if all bytes are off
    if (!orig) return 0;

    uint8_t out = orig;
    //“randomly erase bits” using AND mask
    for (uint8_t p = 0; p < amt; p++) {
        out &= left_rand8();
    }
    //add noisy pixels near the original pixels
    if (amt) {
        uint8_t area  = orig | (uint8_t)(orig << 1) | (uint8_t)(orig >> 1);
        uint8_t noise = left_rand8();

        out |= (noise & area);
        //occasional “invert/toggle” bursts
        if ((left_rand8() & 0x03) == 0) {
            out ^= (left_rand8() & area);
        }
    }

    return out;
}

// reads a monochrome bitmap stored in PROGMEM (data)
// blits (copies) it into the OLED at (x,y), size (w,h)
// and optionally applies TV glitch only inside that blit region.
static void oled_blit_raw_region_tvfx_P(
    const uint8_t *data,
    uint8_t x,
    uint8_t y,
    uint8_t w,
    uint8_t h) {

    // Convert pixels to “pages” and locate starting page
    uint8_t pages = h / 8;
    uint8_t page0 = y / 8;
    // Clip width to screen
    if (x >= OLED_W) return;
    if (x + w > OLED_W) w = OLED_W - x;
    // mix rng with timer so glitch does not look repetitive
    left_rng_state ^= timer_read32();

    uint32_t now   = timer_read32();
    uint32_t phase = now % LEFT_FX_PERIOD_MS;
    // amt is the glitch intensity.
    uint8_t amt = 0;
    if (phase < LEFT_FX_DURATION_MS) {
        uint16_t half = LEFT_FX_DURATION_MS / 2;
        amt = (phase < half)
            ? (uint8_t)((phase * LEFT_FX_MAX_PASSES) / half)
            : (uint8_t)(((LEFT_FX_DURATION_MS - phase) * LEFT_FX_MAX_PASSES) / half);
    }

    bool   do_shift  = (amt >= 2) && (left_rand8() < 80);
    uint8_t shift_pg = do_shift ? left_rand_u8(pages) : 0;
    int8_t shift_dir = (left_rand8() & 1) ? 1 : -1;

    //This holds one page’s worth of bytes for the region before writing it out with the size of the sword logo
    static uint8_t rowbuf[96];
    //Each page is an 8px-tall strip. Inside each page, iterate across columns.
    for (uint8_t page = 0; page < pages; page++) {
        if (do_shift && page == shift_pg) {
            for (uint8_t col = 0; col < w; col++) {
                uint16_t src = (uint16_t)page * w + col;   // page-major
                uint8_t orig = pgm_read_byte(data + src);
                rowbuf[col]  = (amt ? tvfx_byte(orig, amt) : orig);
            }

            if (shift_dir > 0) {
                for (int16_t c = (int16_t)w - 1; c > 0; c--) rowbuf[c] = rowbuf[c - 1];
                rowbuf[0] = 0;
            } else {
                for (uint8_t c = 0; c < w - 1; c++) rowbuf[c] = rowbuf[c + 1];
                rowbuf[w - 1] = 0;
            }

            for (uint8_t col = 0; col < w; col++) {
                uint16_t dst = (uint16_t)(page0 + page) * OLED_W + (uint16_t)(x + col);
                oled_write_raw_byte(rowbuf[col], dst);
            }
        } else {
            for (uint8_t col = 0; col < w; col++) {
                uint16_t src  = (uint16_t)page * w + col;  // page-major
                uint8_t orig  = pgm_read_byte(data + src);
                uint8_t out   = (amt ? tvfx_byte(orig, amt) : orig);

                uint16_t dst = (uint16_t)(page0 + page) * OLED_W + (uint16_t)(x + col);
                oled_write_raw_byte(out, dst);
            }
        }
    }
}

// ──────────────────────────────────────────────────────────────
// Left OLED: Doomguy + Sword + Status (text is NOT glitched)
// ──────────────────────────────────────────────────────────────
static void render_doom_anim(void) {
    uint8_t wpm = get_current_wpm();

    // no typing? then set the idle frame and draw doom angry with the tv glitch applied to it
    if (wpm == 0) {
        doom_frame_idx    = 0;
        doom_last_anim_ms = timer_read32();
        oled_blit_raw_region_tvfx_P(doomguyAngry, DOOM_X, DOOM_Y, SPR_W, SPR_H);
        return;
    }
    //get the doom frame animation beetween one or two
    uint32_t now = timer_read32();
    if (timer_elapsed32(doom_last_anim_ms) > DOOM_FRAME_MS) {
        doom_last_anim_ms = now;
        doom_frame_idx = (doom_frame_idx + 1) % DOOM_FRAME_COUNT;
    }
    //read the animation frame and apply the glitch effect
    const uint8_t *frame = (const uint8_t *)pgm_read_ptr(&doom_frames[doom_frame_idx]);
    oled_blit_raw_region_tvfx_P(frame, DOOM_X, DOOM_Y, SPR_W, SPR_H);
}
// renders the dragon slayer sword with the tv glitch applied, i added an 8 pixel padding so we reduce height in 8 pixels so it does not overflow
static void render_dragonslayer(void) {
    oled_blit_raw_region_tvfx_P(dragonslayer_sword, SWORD_X, SWORD_Y + 8, SWORD_W, SWORD_H - 8);
}
// useful for layers names
static const char *layer_name_upper(uint8_t layer) {
    switch (layer) {
        case 1:  return "SYM";
        case 2:  return "NAV";
        case 3:  return "RGB";
        default: return "QWR";
    }
}

static void oled_render_cheatsheet_and_stats(void) {
    uint8_t layer = get_highest_layer(layer_state);
    uint8_t wpm   = get_current_wpm();
    //update peak wpm
    if (wpm > wpm_peak) wpm_peak = wpm;
    //size of the text line
    char line[22];
    snprintf(line, sizeof(line), "%s W:%3d P:%3d", layer_name_upper(layer), wpm, wpm_peak);
    //set the cursos to start writing without overlapping the doom logo
    oled_set_cursor(TEXT_COL, 0);
    oled_write(line, false);
}

static void oled_render_left(void) {
    //clear oled so no artifacts remain
    oled_clear();

    // Glitched visuals (only these regions)
    render_dragonslayer();
    render_doom_anim();
    // Clean text last (never glitched)
    oled_render_cheatsheet_and_stats();
}

// ──────────────────────────────────────────────────────────────
// Right OLED: logo + rain + TV glitch
// ──────────────────────────────────────────────────────────────
#define NUM_DROPS        14     //how much raind drops ill draw
#define FRAME_MS         60     //how long does a frame runs in ms
#define FX_PERIOD_MS     3000   //interval when next glitch effect occurs
#define FX_DURATION_MS   1500   //duration of the glitch effect
#define FX_MAX_PASSES    4

//object to store rain drops or the horizontal lines we animate
typedef struct {
    uint8_t x;
    int16_t y;
    uint8_t speed;
    uint8_t len;
} drop_t;

static drop_t   drops[NUM_DROPS];       //store the drops
static bool     drops_inited = false;   //flag for animation

static uint32_t rng_state = 0xA5A5A5A5u;//rng seed for right oled
static uint8_t  frame[OLED_BYTES];      //frame buffer for the right oled

// (128x32, vertical 1-bit, SSD1306 raw)
static const uint8_t PROGMEM raw_logo[] = {
    // 'Brand of the sacrificefixed, 128x32px
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x60, 0x30, 0x18, 0x1c, 0x0e, 0x1e, 0x3c, 0x70, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf0, 0x7c, 0x3c, 0x0e, 0x0e, 0x08, 0x78, 0xf0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x90, 0xa2, 0xc1, 0xc0, 0xc0, 0x80, 0x80, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc3, 0xc3, 0x8f, 0x0e, 0xbc, 0xf8, 0xf0, 0xf0, 0xf8, 0xfc, 0xde, 0xcf, 0xc7, 0x83, 0xc1, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0xc1, 0xc2, 0xc3, 0xcf, 0xdc, 0xdc, 0xf8, 0xf0, 0xe0, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x41, 0x80, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x01, 0x01, 0xc1, 0xc1, 0xc1, 0xd1, 0x3c, 0x1f, 0x0f, 0x07, 0x01, 0x01, 0x03, 0x0f, 0x1f, 0x05, 0x69, 0x31, 0x60, 0x81, 0x81, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0xc1, 0xe0, 0x71, 0x79, 0x3d, 0x1f, 0x0f, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x06, 0x04, 0x0c, 0x08, 0x1e, 0x0f, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0e, 0x2c, 0x3c, 0x1e, 0x0f, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
//same as above, should remove duplicate function later
static uint32_t xorshift32(void) {
    uint32_t x = rng_state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    rng_state = x;
    return x;
}
//same as above, should remove duplicate functions laters
static uint8_t rand_u8(uint8_t max_exclusive) { return (uint8_t)(xorshift32() % max_exclusive); }
static inline uint8_t rand8(void) { return (uint8_t)xorshift32(); }

//set a single pixel in the OLED framebuffer return early if the drop spawns outside bounds
static inline void set_px(uint8_t *buf, uint8_t x, int16_t y) {
    if (y < 0 || y >= OLED_H) return;
    uint16_t idx = (uint16_t)(y >> 3) * OLED_W + x;
    buf[idx] |= (uint8_t)(1u << (y & 7));
}
//set x, y, speed and lenght of the drop with rng seed
static void spawn_drop(drop_t *d) {
    d->x     = rand_u8(OLED_W);
    d->y     = -(int16_t)rand_u8(OLED_H);
    d->speed = 1 + rand_u8(3);
    d->len   = 2 + rand_u8(9);
}
//for each drop we will spawn (14) the loop will spawn them and store them in the array of drops set the drop flag to true
static void init_drops(void) {
    rng_state ^= timer_read32();
    for (uint8_t i = 0; i < NUM_DROPS; i++) {
        spawn_drop(&drops[i]);
        drops[i].y = -(int16_t)rand_u8(OLED_H * 2);
    }
    drops_inited = true;
}
//update the speed of the drops and if its out of bounds spawn it again
static void update_drops(void) {
    for (uint8_t i = 0; i < NUM_DROPS; i++) {
        drops[i].y += drops[i].speed;
        if (drops[i].y - (int16_t)drops[i].len > OLED_H + 2) {
            spawn_drop(&drops[i]);
        }
    }
}
//draw all the drops on screen px by px
static void draw_drops(uint8_t *buf) {
    for (uint8_t i = 0; i < NUM_DROPS; i++) {
        for (uint8_t t = 0; t < drops[i].len; t++) {
            set_px(buf, drops[i].x, drops[i].y - (int16_t)t);
        }
        if (drops[i].y >= OLED_H - 1 && (rand_u8(5) == 0)) {
            uint8_t x = drops[i].x;
            set_px(buf, x, OLED_H - 1);
            if (x > 0)        set_px(buf, x - 1, OLED_H - 1);
            if (x < OLED_W-1) set_px(buf, x + 1, OLED_H - 1);
        }
    }
}
//mostly the same as the above fx glitch but applied to the whole frame buffer for the right oled 128x32
static void apply_logo_tv_fx(uint8_t *buf) {
    uint32_t now   = timer_read32();
    uint32_t phase = now % FX_PERIOD_MS;
    if (phase >= FX_DURATION_MS) return;

    uint16_t half = FX_DURATION_MS / 2;
    uint8_t amt = (phase < half)
        ? (uint8_t)((phase * FX_MAX_PASSES) / half)
        : (uint8_t)(((FX_DURATION_MS - phase) * FX_MAX_PASSES) / half);

    for (uint16_t i = 0; i < OLED_BYTES; i++) {
        uint8_t orig = buf[i];
        if (!orig) continue;

        uint8_t out = orig;
        for (uint8_t p = 0; p < amt; p++) out &= rand8();

        if (amt) {
            uint8_t area  = orig | (orig << 1) | (orig >> 1);
            uint8_t noise = rand8();
            out |= (noise & area);
            if ((rand8() & 0x03) == 0) out ^= (rand8() & area);
        }
        buf[i] = out;
    }

    if (amt >= 2 && (rand8() < 80)) {
        uint8_t  page  = rand_u8(OLED_H / 8);
        uint16_t base  = (uint16_t)page * OLED_W;
        int8_t   shift = (rand8() & 1) ? 1 : -1;

        if (shift > 0) {
            for (int16_t x = OLED_W - 1; x > 0; x--) buf[base + x] = buf[base + x - 1];
            buf[base] = 0;
        } else {
            for (uint16_t x = 0; x < OLED_W - 1; x++) buf[base + x] = buf[base + x + 1];
            buf[base + (OLED_W - 1)] = 0;
        }
    }
}
//render the logo plus rain effect and applies the tv glitch effect
static void oled_render_logo_rain(void) {
    static uint32_t last_step_ms = 0;
    static uint32_t last_call_ms = 0;

    uint32_t now = timer_read32();

    if (last_call_ms && timer_elapsed32(last_call_ms) > 500) {
        drops_inited = false;
    }
    last_call_ms = now;
    //alloc rain drops if needed
    if (!drops_inited) {
        init_drops();
        last_step_ms = now;
    }
    //update the rain drops if needed
    if (timer_elapsed32(last_step_ms) > FRAME_MS) {
        last_step_ms = now;
        update_drops();
    }
    //copies the oled frame plus the brand of sacrifice logo to a new frame in memory
    memcpy_P(frame, raw_logo, OLED_BYTES);
    //applies tv glitch effect to newly created frame
    apply_logo_tv_fx(frame);
    //drops dont need the glitch effect, render them in the frame after the glitch is applied
    draw_drops(frame);
    //draws the new frame to the oled screen
    oled_write_raw((const char *)frame, OLED_BYTES);
}

// ──────────────────────────────────────────────────────────────
// Rotation / task right side rotate 180 
// ──────────────────────────────────────────────────────────────
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_left()) {
        return OLED_ROTATION_180;
    }
    return OLED_ROTATION_0;
}
//we restart the animations and renderers so there are no weird artifacts when oled goes to sleep
bool oled_task_user(void) {
    static bool oled_sleeping = false;

    if (oled_last_activity_ms == 0) {
        oled_last_activity_ms = timer_read32();
    }

    if (oled_sleeping && is_oled_on()) {
        oled_sleeping         = false;
        oled_last_activity_ms = timer_read32();
        oled_clear();
        drops_inited = false;
    }
    //only check with the master side as i have split oled defined in the config
    if (is_keyboard_left()) {
        if (timer_elapsed32(oled_last_activity_ms) > OLED_IDLE_TIMEOUT_MS) {
            if (!oled_sleeping) {
                oled_off();
                oled_sleeping = true;
#ifdef RGB_MATRIX_ENABLE
                //when oled is idle change the rgb animation to signal the kb is sleeping
                rgb_enter_idle();
#endif
            }
            return false;
        }

        if (oled_sleeping) {
            oled_on();
            oled_clear();
            oled_sleeping = false;
#ifdef RGB_MATRIX_ENABLE
            //when we start to type again switch to the previous rgb animation before keyboard was idle
            rgb_exit_idle();
#endif
        }
    }

    if (!is_oled_on()) {
        return false;
    }
    //renders both halves of the keyboard
    if (is_keyboard_left()) {
        oled_render_left();
    } else {
        oled_render_logo_rain();
    }

    return false;
}
//just to check wheter keyboard is active or not so we switch on the oleds and reset the rgb animation if needed
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        oled_last_activity_ms = timer_read32();
#ifdef RGB_MATRIX_ENABLE
        rgb_exit_idle();
#endif
        if (is_keyboard_left() && !is_oled_on()) {
            oled_on();
        }
    }
    return true;
}

#endif // OLED_ENABLE