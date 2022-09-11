// Copyright 2022 Joshua Diamond josh@windowoffire.com (@spidey3)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "spidey3.h"
#include "velocikey.h"
#include <lib/lib8tion/lib8tion.h>

uint32_t rgb_mode;
uint16_t rgb_hue;
uint8_t  rgb_sat;
uint8_t  rgb_val;
bool     rgb_saved = 0;

extern bool     spi_gflock;
extern uint16_t spi_replace_mode;

static void set_rgb_default(void) {
    rgblight_enable();
    rgblight_sethsv(RGBLIGHT_DEFAULT_HUE, RGBLIGHT_DEFAULT_SAT, RGBLIGHT_DEFAULT_VAL);
    rgblight_mode(RGBLIGHT_DEFAULT_MODE);
#ifdef VELOCIKEY_ENABLE
    if (velocikey_enabled()) velocikey_toggle();
#endif
}

// clang-format off

// Convenience macros
#define NONE { RGBLIGHT_END_SEGMENTS }
#define CORNER_BL(color) { 0, 1, color }
#define CORNER_BR(color) { RGBLED_NUM / 2 - 1, 1, color }
#define CORNER_FR(color) { RGBLED_NUM / 2, 1, color }
#define CORNER_FL(color) { RGBLED_NUM - 1, 1, color }
#define CORNERS(color) {0, 1, color}, {RGBLED_NUM / 2 - 1, 2, color}, { RGBLED_NUM - 1, 1, color }
#define FRONT(inset, color) { RGBLED_NUM / 2 + inset, RGBLED_NUM / 2 - 2 * inset, color }
#define BACK(inset, color) { inset, RGBLED_NUM / 2 - 2 * inset, color }

const rgblight_segment_t PROGMEM _none[] = NONE;

#define LAYER_OFFSET 0
// No indicator for base layer
const rgblight_segment_t PROGMEM _layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(CORNERS(HSV_MAGENTA));  // _NUMPAD
const rgblight_segment_t PROGMEM _layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(CORNERS(HSV_GREEN));    // _FN

#define LOCK_OFFSET 3
const rgblight_segment_t PROGMEM _numlock_layer[]    = RGBLIGHT_LAYER_SEGMENTS(FRONT(3, HSV_YELLOW));
const rgblight_segment_t PROGMEM _capslock_layer[]   = RGBLIGHT_LAYER_SEGMENTS(CORNER_FL(HSV_AZURE));
const rgblight_segment_t PROGMEM _scrolllock_layer[] = RGBLIGHT_LAYER_SEGMENTS(CORNER_FR(HSV_ORANGE));

#define MISC_OFFSET 6
const rgblight_segment_t PROGMEM _gflock_layer[]       = RGBLIGHT_LAYER_SEGMENTS(BACK(1, HSV_ORANGE));
const rgblight_segment_t PROGMEM _glyphreplace_layer[] = RGBLIGHT_LAYER_SEGMENTS(FRONT(1, HSV_ORANGE));

#define ACK_OFFSET 8
const rgblight_segment_t PROGMEM _no_layer[]     = RGBLIGHT_LAYER_SEGMENTS(FRONT(1, HSV_RED));
const rgblight_segment_t PROGMEM _yes_layer[]    = RGBLIGHT_LAYER_SEGMENTS(FRONT(1, HSV_GREEN));
const rgblight_segment_t PROGMEM _meh_layer[]    = RGBLIGHT_LAYER_SEGMENTS(FRONT(1, HSV_YELLOW));
const rgblight_segment_t PROGMEM _huh_layer[]    = RGBLIGHT_LAYER_SEGMENTS(CORNERS(HSV_YELLOW), FRONT(1, HSV_BLUE), BACK(1, HSV_BLUE));

#define UNICODE_OFFSET 12
const rgblight_segment_t PROGMEM _uc_mac_layer[]  = RGBLIGHT_LAYER_SEGMENTS(CORNER_BR(HSV_PURPLE));
// No indicator for UC_LNX
// UC_WIN disabled in config.h
// UC_BSD not implemented
const rgblight_segment_t PROGMEM _uc_winc_layer[] = RGBLIGHT_LAYER_SEGMENTS(CORNER_BR(HSV_CYAN));
const rgblight_segment_t PROGMEM _uc_emacs_layer[] = RGBLIGHT_LAYER_SEGMENTS(CORNER_BR(HSV_GREEN));

// Now define the array of layers. Higher numbered layers take precedence.
const rgblight_segment_t *const PROGMEM _rgb_layers[] = {
    [LAYER_OFFSET + _BASE]   = _none,
    [LAYER_OFFSET + _NUMPAD] = _layer1_layer,
    [LAYER_OFFSET + _FN]     = _layer2_layer,

    [LOCK_OFFSET + USB_LED_NUM_LOCK]    = _numlock_layer,
    [LOCK_OFFSET + USB_LED_CAPS_LOCK]   = _capslock_layer,
    [LOCK_OFFSET + USB_LED_SCROLL_LOCK] = _scrolllock_layer,

    [MISC_OFFSET + 0] = _gflock_layer,
    [MISC_OFFSET + 1] = _glyphreplace_layer,

    [ACK_OFFSET + ACK_NO]     = _no_layer,
    [ACK_OFFSET + ACK_YES]    = _yes_layer,
    [ACK_OFFSET + ACK_MEH]    = _meh_layer,
    [ACK_OFFSET + ACK_HUH]    = _huh_layer,

    [UNICODE_OFFSET + UC_MAC]  = _uc_mac_layer,
    [UNICODE_OFFSET + UC_LNX]  = _none,
    [UNICODE_OFFSET + UC_WIN]  = _none,
    [UNICODE_OFFSET + UC_BSD]  = _none,
    [UNICODE_OFFSET + UC_WINC] = _uc_winc_layer,
    [UNICODE_OFFSET + UC_EMACS] = _uc_emacs_layer,

    [UNICODE_OFFSET + UC__COUNT] = NULL
};

// clang-format on

const uint8_t PROGMEM _n_rgb_layers = sizeof(_rgb_layers) / sizeof(_rgb_layers[0]) - 1;

void clear_rgb_layers() {
    for (uint8_t i = 0; i < _n_rgb_layers; i++) {
        rgblight_set_layer_state(i, false);
    }
}

void do_rgb_layers(layer_state_t state, uint8_t start, uint8_t end) {
    for (uint8_t i = start; i < end; i++) {
        bool is_on = layer_state_cmp(state, i);
        rgblight_set_layer_state(LAYER_OFFSET + i, is_on);
    }
}

void do_rgb_unicode(void) {
    uint8_t uc_mode = get_unicode_input_mode();
    for (uint8_t i = 0; i < UC__COUNT; i++) {
        bool is_on = i == uc_mode;
        rgblight_set_layer_state(UNICODE_OFFSET + i, is_on);
    }
}

void do_rgb_all(void) {
    do_rgb_layers(default_layer_state, LAYER_BASE_DEFAULT, LAYER_BASE_REGULAR);
    do_rgb_layers(layer_state, LAYER_BASE_REGULAR, LAYER_BASE_END);
    do_rgb_unicode();
    rgblight_set_layer_state(MISC_OFFSET + 0, spi_gflock);
    rgblight_set_layer_state(MISC_OFFSET + 1, spi_replace_mode != SPI_NORMAL);
}

// flags. 0 = no change, 1 = increment, -1 = decrement.
int8_t change_hue = 0;
int8_t change_sat = 0;
int8_t change_val = 0;

// timer to control color change speed
uint16_t       change_timer = 0;
const uint16_t change_tick  = 15;

extern rgblight_config_t rgblight_config;
extern rgblight_status_t rgblight_status;

#if defined(RGBLIGHT_STARTUP_ANIMATION)

#    define STARTUP_ANIMATION_SATURATION 200
#    define STARTUP_ANIMATION_VALUE 255
#    define STARTUP_ANIMATION_FADE_STEP 5
#    define STARTUP_ANIMATION_CYCLE_STEP 2
#    define STARTUP_ANIMATION_RAMP_TO_STEPS 70
#    define STARTUP_ANIMATION_STEP_TIME 10
#    define STARTUP_ANIMATION_INITIAL_DELAY 0  // milliseconds, must be < 255 * STEP_TIME

// clang-format off
typedef enum {
    DISABLED,
    WAITING,
    RESTART,
    START,
    FADE_OLD,
    FADE_IN,
    CYCLE,
    RAMP_DOWN,
    RAMP_TO,
    CLEAN_UP,
    DONE
} startup_animation_state_t;
// clang-format on

static rgblight_config_t         old_config;
static uint8_t                   old_base_mode;
static startup_animation_state_t startup_animation_state = DISABLED;
static uint16_t                  rgblight_startup_loop_timer;

void startup_animation_init(void) {
    old_config.raw = rgblight_config.raw;
    old_base_mode  = rgblight_status.base_mode;

    if (!old_config.enable) rgblight_enable_noeeprom();
}
#endif

void keyboard_post_init_user_rgb(void) {
    // Enable the LED layers
    rgblight_layers = _rgb_layers;
    do_rgb_all();

#if defined(RGBLIGHT_STARTUP_ANIMATION)
    startup_animation_init();
    startup_animation_state = STARTUP_ANIMATION_INITIAL_DELAY ? WAITING : START;
#endif
}

void matrix_scan_user_rgb(void) {
#if defined(RGBLIGHT_STARTUP_ANIMATION)
    if (startup_animation_state != DONE && is_keyboard_master()) {
        if (startup_animation_state == START || timer_elapsed(rgblight_startup_loop_timer) > STARTUP_ANIMATION_STEP_TIME) {
            static uint8_t counter;
            rgblight_startup_loop_timer = timer_read();

            switch (startup_animation_state) {
                case WAITING:
#    ifdef STARTUP_ANIMATION_DEBUG
                    dprintf("sua WAITING counter=%u\n", counter);
#    endif
                    if (counter < STARTUP_ANIMATION_INITIAL_DELAY / STARTUP_ANIMATION_STEP_TIME) {
                        counter++;
                    } else {
                        startup_animation_state = START;
                    }
                    break;

                case RESTART:
#    ifdef STARTUP_ANIMATION_DEBUG
                    dprintln("sua RESTART");
#    endif
                    startup_animation_init();
                case START:
#    ifdef STARTUP_ANIMATION_DEBUG
                    dprintln("sua START");
#    endif
                    startup_animation_state = FADE_OLD;
                    counter                 = old_config.val;
                    // No break! Just roll into FADE_OLD in the same iteration...

                case FADE_OLD:
#    ifdef STARTUP_ANIMATION_DEBUG
                    dprintf("sua FADE_OLD counter=%u\n", counter);
#    endif
                    if (counter >= STARTUP_ANIMATION_FADE_STEP) {
                        rgblight_sethsv_noeeprom(old_config.hue, old_config.sat, counter);
                        counter -= STARTUP_ANIMATION_FADE_STEP;
                    } else {
                        counter                 = 0;
                        startup_animation_state = FADE_IN;
                        rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
                    }
                    break;

                case FADE_IN:
#    ifdef STARTUP_ANIMATION_DEBUG
                    dprintf("sua FADE_IN counter=%u\n", counter);
#    endif
                    if (counter < STARTUP_ANIMATION_VALUE) {
                        rgblight_sethsv_noeeprom(old_config.hue, STARTUP_ANIMATION_SATURATION, counter);
                        counter += STARTUP_ANIMATION_FADE_STEP;
                    } else {
                        counter                 = 255;
                        startup_animation_state = CYCLE;
                    }
                    break;

                case CYCLE:
#    ifdef STARTUP_ANIMATION_DEBUG
                    dprintf("sua CYCLE counter=%u\n", counter);
#    endif
                    if (counter >= STARTUP_ANIMATION_CYCLE_STEP) {
                        rgblight_sethsv_noeeprom((counter + old_config.hue) % 255, STARTUP_ANIMATION_SATURATION, STARTUP_ANIMATION_VALUE);
                        counter -= STARTUP_ANIMATION_CYCLE_STEP;
                    } else {
                        if (
#    ifdef RGBLIGHT_EFFECT_BREATHING
                            (old_base_mode == RGBLIGHT_MODE_BREATHING) ||
#    endif
#    ifdef RGBLIGHT_EFFECT_SNAKE
                            (old_base_mode == RGBLIGHT_MODE_SNAKE) ||
#    endif
#    ifdef RGBLIGHT_EFFECT_KNIGHT
                            (old_base_mode == RGBLIGHT_MODE_KNIGHT) ||
#    endif
#    ifdef RGBLIGHT_EFFECT_TWINKLE
                            (old_base_mode == RGBLIGHT_MODE_TWINKLE) ||
#    endif
                            !old_config.enable) {
                            counter                 = STARTUP_ANIMATION_VALUE;
                            startup_animation_state = RAMP_DOWN;
                        } else if (
#    ifdef RGBLIGHT_EFFECT_STATIC_GRADIENT
                            (old_base_mode == RGBLIGHT_MODE_STATIC_GRADIENT) ||
#    endif
#    ifdef RGBLIGHT_EFFECT_RAINBOW_MOOD
                            (old_base_mode == RGBLIGHT_MODE_RAINBOW_MOOD) ||
#    endif
#    ifdef RGBLIGHT_EFFECT_RAINBOW_SWIRL
                            (old_base_mode == RGBLIGHT_MODE_RAINBOW_SWIRL) ||
#    endif
#    ifdef RGBLIGHT_EFFECT_RAINBOW_CHRISTMAS
                            (old_base_mode == RGBLIGHT_MODE_CHRISTMAS) ||
#    endif
#    ifdef RGBLIGHT_EFFECT_RAINBOW_RGB_TEST
                            (old_base_mode == RGBLIGHT_MODE_RGB_TEST) ||
#    endif
                            (old_base_mode == RGBLIGHT_MODE_STATIC_LIGHT)) {
                            counter                 = 0;
                            startup_animation_state = RAMP_TO;
                        } else {
                            startup_animation_state = CLEAN_UP;
                        }
                    }
                    break;

                case RAMP_DOWN:
#    ifdef STARTUP_ANIMATION_DEBUG
                    dprintf("sua RAMP_DOWN counter=%u\n", counter);
#    endif
                    rgblight_sethsv_noeeprom(old_config.hue, STARTUP_ANIMATION_SATURATION, counter);
                    if (counter >= STARTUP_ANIMATION_FADE_STEP) {
                        counter -= STARTUP_ANIMATION_FADE_STEP;
                    } else {
                        startup_animation_state = CLEAN_UP;
                    }
                    break;

                case RAMP_TO: {
#    ifdef STARTUP_ANIMATION_DEBUG
                    dprintf("sua RAMP_TO s=%u, v=%u, counter=%u\n", old_config.sat, old_config.val, counter);
#    endif
                    uint8_t steps = STARTUP_ANIMATION_RAMP_TO_STEPS;
                    if (counter < steps) {
                        uint8_t s = STARTUP_ANIMATION_SATURATION + counter * (((float)old_config.sat - STARTUP_ANIMATION_SATURATION) / (float)steps);
                        uint8_t v = STARTUP_ANIMATION_VALUE + counter * (((float)old_config.val - STARTUP_ANIMATION_VALUE) / (float)steps);
                        rgblight_sethsv_noeeprom(old_config.hue, s, v);
                        counter++;
                    } else {
                        startup_animation_state = CLEAN_UP;
                    }
                } break;

                case CLEAN_UP:
#    ifdef STARTUP_ANIMATION_DEBUG
                    dprintln("sua CLEAN_UP");
#    endif
                    rgblight_reload_from_eeprom();
                    startup_animation_state = DONE;
#    ifdef STARTUP_ANIMATION_DEBUG
                    dprintln("sua DONE");
#    endif
                    break;

                default:
                    break;
            }
        }
    }
#endif

    if (change_hue != 0 || change_val != 0 || change_sat != 0) {
        if (timer_elapsed(change_timer) > change_tick) {
            HSV hsv = rgblight_get_hsv();
            hsv.h += change_hue;
            hsv.s = change_sat > 0 ? qadd8(hsv.s, (uint8_t)change_sat) : qsub8(hsv.s, (uint8_t)-change_sat);
            hsv.v = change_val > 0 ? qadd8(hsv.v, (uint8_t)change_val) : qsub8(hsv.v, (uint8_t)-change_val);
            rgblight_sethsv_noeeprom(hsv.h, hsv.s, hsv.v);
            change_timer = timer_read();
        }
    }
}

void shutdown_user_rgb(void) {
    clear_rgb_layers();
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    for (int i = 0; i < RGBLED_NUM; i++) {
        rgblight_setrgb_at(0xFF, 0x80 * (i % 2), 0, i);
    }
}

layer_state_t default_layer_state_set_user_rgb(layer_state_t state) {
    do_rgb_layers(state, LAYER_BASE_DEFAULT, LAYER_BASE_REGULAR);
    return state;
}

layer_state_t layer_state_set_user_rgb(layer_state_t state) {
    do_rgb_layers(state, LAYER_BASE_REGULAR, LAYER_BASE_END);
    return state;
}

bool led_update_user_rgb(led_t led_state) {
    rgblight_set_layer_state(LOCK_OFFSET + USB_LED_NUM_LOCK, led_state.num_lock);
    rgblight_set_layer_state(LOCK_OFFSET + USB_LED_CAPS_LOCK, led_state.caps_lock);
    rgblight_set_layer_state(LOCK_OFFSET + USB_LED_SCROLL_LOCK, led_state.scroll_lock);

    return true;
}

void rgb_layer_ack_yn(bool yn) { rgb_layer_ack(yn ? ACK_YES : ACK_NO); }

void rgb_layer_ack(layer_ack_t n) {
    uint8_t layer = ACK_OFFSET + n;
    rgblight_blink_layer(layer, RGB_LAYER_ACK_DURATION);
}

extern keymap_config_t   keymap_config;
extern rgblight_config_t rgblight_config;

bool process_record_user_rgb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
                // clang-format off
            case SPI_GLO: set_rgb_default(); return false;

            case RGB_HUI: change_timer = timer_read(); change_hue =  1; return false;
            case RGB_HUD: change_timer = timer_read(); change_hue = -1; return false;
            case RGB_SAI: change_timer = timer_read(); change_sat =  1; return false;
            case RGB_SAD: change_timer = timer_read(); change_sat = -1; return false;
            case RGB_VAI: change_timer = timer_read(); change_val =  1; return false;
            case RGB_VAD: change_timer = timer_read(); change_val = -1; return false;
                // clang-format on
        }
    } else {
        bool rgb_done = false;
        switch (keycode) {
            case RGB_HUI:
            case RGB_HUD:
                change_hue = 0;
                rgb_done   = true;
                break;
            case RGB_SAI:
            case RGB_SAD:
                change_sat = 0;
                rgb_done   = true;
                break;
            case RGB_VAI:
            case RGB_VAD:
                change_val = 0;
                rgb_done   = true;
                break;
        }

        if (rgb_done) {
            HSV final = rgblight_get_hsv();
            rgblight_sethsv(final.h, final.s, final.v);
        }
    }

    return true;
}

void post_process_record_user_rgb(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Acks follow...
        case DEBUG:
            if (debug_matrix || debug_keyboard)
                rgb_layer_ack(ACK_HUH);
            else if (debug_enable)
                rgb_layer_ack(ACK_YES);
            else
                rgb_layer_ack(ACK_NO);
            break;

        case SPI_GFLOCK:
            rgb_layer_ack_yn(spi_gflock);
            rgblight_set_layer_state(MISC_OFFSET + 0, spi_gflock);
            break;

        case SPI_NORMAL ... SPI_FRAKTR:
            rgb_layer_ack_yn(spi_replace_mode != SPI_NORMAL);
            rgblight_set_layer_state(MISC_OFFSET + 1, spi_replace_mode != SPI_NORMAL);
            break;

        case RGB_TOG:
            // Hack - we only get called on the press for RGB_TOG, 
            // but the flag is only flipped on the release...
            rgb_layer_ack_yn(!rgblight_config.enable);
            break;

#ifdef VELOCIKEY_ENABLE
        case VLK_TOG:
            rgb_layer_ack_yn(velocikey_enabled());
            break;
#endif

#ifdef NKRO_ENABLE
        case NK_TOGG:
        case NK_ON:
        case NK_OFF:
            rgb_layer_ack_yn(keymap_config.nkro);
            break;
#endif

#if defined(UNICODE_COMMON_ENABLE)
        case UC_M_MA:
        case UC_M_LN:
        case UC_M_WI:
        case UC_M_BS:
        case UC_M_WC:
        case UC_M_EM:

        case UC_MOD:
        case UC_RMOD:
            rgb_layer_ack(ACK_MEH);
            do_rgb_unicode();
            break;
#endif
    }
}
