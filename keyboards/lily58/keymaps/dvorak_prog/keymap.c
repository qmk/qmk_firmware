#include QMK_KEYBOARD_H
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef WPM_ESTIMATED_WORD_SIZE
#    define WPM_ESTIMATED_WORD_SIZE 5
#endif
#ifndef WPM_SAMPLE_SECONDS
#    define WPM_SAMPLE_SECONDS 5
#endif
#ifndef WPM_SAMPLE_PERIODS
#    define WPM_SAMPLE_PERIODS 25
#endif

bool wpm_keycode(uint16_t keycode);
bool wpm_keycode_kb(uint16_t keycode);
bool wpm_keycode_user(uint16_t keycode);

#ifdef WPM_ALLOW_COUNT_REGRESSION
uint8_t wpm_regress_count(uint16_t keycode);
#endif

void    set_current_wpm(uint8_t);
uint8_t get_current_wpm(void);
void    update_wpm(uint16_t);

void decay_wpm(void);
enum layer_number {
  _DVORAK = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

char wpm_str[10];

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*================================================================================================================
 * PROGRAMMER DVORAK
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   7  |   5  |   3  |   1  |  9   |                    |   0  |   2  |   4  |   6  |   8  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   :  |   <  |   >  |   P  |   Y  |                    |   F  |   G  |   C  |   R  |   L  |  ?   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   O  |   E  |   U  |   I  |-------.    ,-------|   D  |   H  |   T  |   N  |   S  |  -   |
 * |------+------+------+------+------+------|DELETE |    |BACKSSP|------+------+------+------+------+------|
 * |LShift|   "  |   Q  |   J  |   K  |   X  |-------|    |-------|   B  |   M  |   W  |   V  |   Z  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
 [_DVORAK] = LAYOUT(
  KC_ESC,   KC_7,           KC_5,       KC_3,       KC_1,    KC_9,                              KC_0,    KC_2,    KC_4,     KC_6,   KC_8,   KC_GRAVE,
  KC_TAB,   KC_SEMICOLON,   KC_COMMA,   KC_DOT,     KC_P,    KC_Y,                              KC_F,    KC_G,    KC_C,     KC_R,   KC_L,   KC_SLASH,
  KC_LCTL,  KC_A,           KC_O,       KC_E,       KC_U,    KC_I,                              KC_D,    KC_H,    KC_T,     KC_N,   KC_S,   KC_MINS,
  KC_LSFT,  KC_QUOTE,       KC_Q,       KC_J,       KC_K,    KC_X,  KC_DELETE,  KC_BACKSPACE,   KC_B,    KC_M,    KC_W,     KC_V,   KC_Z,   KC_RSFT,
                            KC_LALT,    KC_LGUI,    MO(_LOWER),     KC_SPC,     KC_ENT,         MO(_RAISE),     KC_BSPC, KC_RALT
),
//================================================================================================================


/*================================================================================================================
 * LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |   *  |   )  |   +  |   ]  |   !  |  #   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |  F1  |  F2  |  F3  |  F4  |                    |      |      |      |      |      |  @   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |  F5  |  F6  |  F7  |  F8  |-------.    ,-------|      |      |      |      |      |   _  |
 * |------+------+------+------+------+------|DELETE |    |BACKSSP|------+------+------+------+------+------|
 * |   ~  |   $  |  F9  |  F10 |  F11 |  F12 |-------|    |-------|      |   h  |   j  |   k  |  l   |   |  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI | 	    | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_LOWER] = LAYOUT(
  _______,  _______,     _______, _______,  _______,  _______,                   KC_ASTERISK,KC_RIGHT_PAREN, KC_PLUS,    KC_RIGHT_BRACKET,   KC_EXCLAIM, KC_HASH,
  _______,  _______,     KC_F1,   KC_F2,    KC_F3,    KC_F4,                     _______,    _______,        _______,    _______,            _______,    KC_AT,
  _______,  _______,     KC_F5,   KC_F6,    KC_F7,    KC_F8,                     _______,    _______,        _______,    _______,            _______,    KC_UNDERSCORE,
  KC_TILD,  KC_DOLLAR,  KC_F9,    KC_F10,   KC_F11,   KC_F12, _______, _______,  _______,    KC_H,           KC_J,       KC_K,               KC_L,       KC_PIPE,
                             _______,    _______,    XXXXXXX, _______, _______,  _______, _______, _______
),
//================================================================================================================


/*================================================================================================================
 * RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   &  |  [   |   {  |   }  |   (  |   =  |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |      |      |   7  |   8  |  9   |                    |      |  +   |   -  |  =   |      |   ^  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |CpsLck|      |      |   4  |   5  |  6   |-------.    ,-------|      | [    |  ]   |   *  |	     |      |
 * |------+------+------+------+------+------|DELETE |    |BACKSSP|------+------+------+------+------+------|
 * |      |      |   0  |   1  |   2  |  3   |-------|    |-------|      |left  |down  |  up  |right |   \  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |      |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_RAISE] = LAYOUT(
  KC_AMPERSAND, KC_LEFT_BRACKET, KC_LEFT_CURLY_BRACE, KC_RIGHT_CURLY_BRACE, KC_LEFT_PAREN, KC_EQUAL,        		          _______, _______, _______, _______,  _______, _______,
  KC_QUOTE,  	_______, 	          _______,            KC_7,                 KC_8,    	     KC_9,                          _______, KC_PLUS, KC_MINUS,KC_EQL,   _______, KC_CIRCUMFLEX,
  KC_CAPS,  	_______,    	      _______,   	        KC_4,   		          KC_5,   	     KC_6,                          _______, KC_LBRC, KC_RBRC, _______,  _______, _______,
  _______,   	_______,   	        KC_0,   	          KC_1,  		            KC_2,  	       KC_3,    _______,   _______,   _______, KC_LEFT, KC_DOWN,  KC_UP,  KC_RIGHT, KC_BSLS,
                             	 	                             _______,        _______,		_______,   _______,    _______,  XXXXXXX, _______, _______
),
//================================================================================================================


/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |RGB ON| HUE+ | SAT+ | VAL+ |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      | MODE | HUE- | SAT- | VAL- |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ADJUST] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                             _______, _______, _______, _______, _______,  _______, _______, _______
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
   sprintf(wpm_str, "WPM: %03d", get_current_wpm());
    oled_write_ln(wpm_str, false);
  
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    oled_write(read_logo(), false);
  }
    return false;
}
#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  return true;
}
#include "wpm.h"
#include "timer.h"
#include "keycode.h"
#include "quantum_keycodes.h"
#include "action_util.h"
#include <math.h>

// WPM Stuff
static uint8_t  current_wpm = 0;
static uint32_t wpm_timer   = 0;

/* The WPM calculation works by specifying a certain number of 'periods' inside
 * a ring buffer, and we count the number of keypresses which occur in each of
 * those periods.  Then to calculate WPM, we add up all of the keypresses in
 * the whole ring buffer, divide by the number of keypresses in a 'word', and
 * then adjust for how much time is captured by our ring buffer.  The size
 * of the ring buffer can be configured using the keymap configuration
 * value `WPM_SAMPLE_PERIODS`.
 *
 */
#define MAX_PERIODS (WPM_SAMPLE_PERIODS)
#define PERIOD_DURATION (1000 * WPM_SAMPLE_SECONDS / MAX_PERIODS)

static int16_t period_presses[MAX_PERIODS] = {0};
static uint8_t current_period              = 0;
static uint8_t periods                     = 1;

#if !defined(WPM_UNFILTERED)
/* LATENCY is used as part of filtering, and controls how quickly the reported
 * WPM trails behind our actual instantaneous measured WPM value, and is
 * defined in milliseconds.  So for LATENCY == 100, the displayed WPM is
 * smoothed out over periods of 0.1 seconds.  This results in a nice,
 * smoothly-moving reported WPM value which nevertheless is never more than
 * 0.1 seconds behind the typist's actual current WPM.
 *
 * LATENCY is not used if WPM_UNFILTERED is defined.
 */
#    define LATENCY (100)
static uint32_t smoothing_timer = 0;
static uint8_t  prev_wpm        = 0;
static uint8_t  next_wpm        = 0;
#endif

void set_current_wpm(uint8_t new_wpm) {
    current_wpm = new_wpm;
}
uint8_t get_current_wpm(void) {
    return current_wpm;
}

bool wpm_keycode(uint16_t keycode) {
    return wpm_keycode_kb(keycode);
}

__attribute__((weak)) bool wpm_keycode_kb(uint16_t keycode) {
    return wpm_keycode_user(keycode);
}

__attribute__((weak)) bool wpm_keycode_user(uint16_t keycode) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) || (keycode >= QK_MODS && keycode <= QK_MODS_MAX)) {
        keycode = keycode & 0xFF;
    } else if (keycode > 0xFF) {
        keycode = 0;
    }
    if ((keycode >= KC_A && keycode <= KC_0) || (keycode >= KC_TAB && keycode <= KC_SLASH)) {
        return true;
    }

    return false;
}

#if defined(WPM_ALLOW_COUNT_REGRESSION)
__attribute__((weak)) uint8_t wpm_regress_count(uint16_t keycode) {
    bool weak_modded = (keycode >= QK_LCTL && keycode < QK_LSFT) || (keycode >= QK_RCTL && keycode < QK_RSFT);

    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) || (keycode >= QK_MODS && keycode <= QK_MODS_MAX)) {
        keycode = keycode & 0xFF;
    } else if (keycode > 0xFF) {
        keycode = 0;
    }
    if (keycode == KC_DELETE || keycode == KC_BACKSPACE) {
        if (((get_mods() | get_oneshot_mods()) & MOD_MASK_CTRL) || weak_modded) {
            return WPM_ESTIMATED_WORD_SIZE;
        } else {
            return 1;
        }
    } else {
        return 0;
    }
}
#endif

// Outside 'raw' mode we smooth results over time.

void update_wpm(uint16_t keycode) {
    if (wpm_keycode(keycode) && period_presses[current_period] < INT16_MAX) {
        period_presses[current_period]++;
    }
#if defined(WPM_ALLOW_COUNT_REGRESSION)
    uint8_t regress = wpm_regress_count(keycode);
    if (regress && period_presses[current_period] > INT16_MIN) {
        period_presses[current_period]--;
    }
#endif
}

void decay_wpm(void) {
    int32_t presses = period_presses[0];
    for (int i = 1; i <= periods; i++) {
        presses += period_presses[i];
    }
    if (presses < 0) {
        presses = 0;
    }
    int32_t  elapsed  = timer_elapsed32(wpm_timer);
    uint32_t duration = (((periods)*PERIOD_DURATION) + elapsed);
    int32_t  wpm_now  = (60000 * presses) / (duration * WPM_ESTIMATED_WORD_SIZE);

    if (wpm_now < 0) // set some reasonable WPM measurement limits
        wpm_now = 0;
    if (wpm_now > 240) wpm_now = 240;

    if (elapsed > PERIOD_DURATION) {
        current_period                 = (current_period + 1) % MAX_PERIODS;
        period_presses[current_period] = 0;
        periods                        = (periods < MAX_PERIODS - 1) ? periods + 1 : MAX_PERIODS - 1;
        elapsed                        = 0;
        wpm_timer                      = timer_read32();
    }
    if (presses < 2) // don't guess high WPM based on a single keypress.
        wpm_now = 0;

#if defined(WPM_LAUNCH_CONTROL)
    /*
     * If the `WPM_LAUNCH_CONTROL` option is enabled, then whenever our WPM
     * drops to absolute zero due to no typing occurring within our sample
     * ring buffer, we reset and start measuring fresh, which lets our WPM
     * immediately reach the correct value even before a full sampling buffer
     * has been filled.
     */
    if (presses == 0) {
        current_period    = 0;
        periods           = 0;
        wpm_now           = 0;
        period_presses[0] = 0;
    }
#endif // WPM_LAUNCH_CONTROL

#if defined(WPM_UNFILTERED)
    current_wpm = wpm_now;
#else
    int32_t latency = timer_elapsed32(smoothing_timer);
    if (latency > LATENCY) {
        smoothing_timer = timer_read32();
        prev_wpm        = current_wpm;
        next_wpm        = wpm_now;
    }

    current_wpm = prev_wpm + (latency * ((int)next_wpm - (int)prev_wpm) / LATENCY);
#endif
}
