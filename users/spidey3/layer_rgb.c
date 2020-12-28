#include QMK_KEYBOARD_H

#include "spidey3.h"
#include "velocikey.h"

uint32_t rgb_mode;
uint16_t rgb_hue;
uint8_t  rgb_sat;
uint8_t  rgb_val;
bool     rgb_saved = 0;

void spidey_glow(void) {
    rgblight_enable();
    rgblight_mode(RGBLIGHT_MODE_TWINKLE + 1);
    rgblight_sethsv(213, 255, 128);
#ifdef VELOCIKEY_ENABLE
    if (velocikey_enabled()) velocikey_toggle();
#endif
}

void eeconfig_init_user_rgb(void) { spidey_glow(); }

// clang-format off

// Convenience macros
#define CORNER_BL(color) { 0, 1, color }
#define CORNER_BR(color) { RGBLED_NUM / 2 - 1, 1, color }
#define CORNER_FR(color) { RGBLED_NUM / 2, 1, color }
#define CORNER_FL(color) { RGBLED_NUM - 1, 1, color }
#define CORNERS(color) {0, 1, color}, {RGBLED_NUM / 2 - 1, 2, color}, { RGBLED_NUM - 1, 1, color }
#define FRONT(inset, color) { RGBLED_NUM / 2 + inset, RGBLED_NUM / 2 - 2 * inset, color }
#define BACK(inset, color) { inset, RGBLED_NUM / 2 - 2 * inset, color }

#define LAYER_OFFSET 0
const rgblight_segment_t PROGMEM _layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(CORNER_BR(HSV_PURPLE));
const rgblight_segment_t PROGMEM _layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(CORNERS(HSV_MAGENTA));
const rgblight_segment_t PROGMEM _layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(CORNERS(HSV_GREEN));

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

// Now define the array of layers. Higher numbered layers take precedence.
const rgblight_segment_t *const PROGMEM _rgb_layers[] = {
    [LAYER_OFFSET + 0] = _layer1_layer,
    [LAYER_OFFSET + 1] = _layer2_layer,
    [LAYER_OFFSET + 2] = _layer3_layer,

    [LOCK_OFFSET + USB_LED_NUM_LOCK]    = _numlock_layer,
    [LOCK_OFFSET + USB_LED_CAPS_LOCK]   = _capslock_layer,
    [LOCK_OFFSET + USB_LED_SCROLL_LOCK] = _scrolllock_layer,

    [MISC_OFFSET + 0] = _gflock_layer,
    [MISC_OFFSET + 1] = _glyphreplace_layer,

    [ACK_OFFSET + ACK_NO]     = _no_layer,
    [ACK_OFFSET + ACK_YES]    = _yes_layer,
    [ACK_OFFSET + ACK_MEH]    = _meh_layer,
    [ACK_OFFSET + ACK_HUH]    = _huh_layer,

    [ACK_OFFSET + ACK_HUH + 1] = NULL
};

// clang-format on 

const uint8_t PROGMEM _n_rgb_layers = sizeof(_rgb_layers) / sizeof(_rgb_layers[0]) - 1;

void clear_rgb_layers() {
    dprint("clear_rgb_layers()\n");
    for (uint8_t i = 0; i < _n_rgb_layers; i++) {
        rgblight_set_layer_state(i, false);
    }
}

void do_rgb_layers(layer_state_t state, uint8_t start, uint8_t end) {
    for (uint8_t i = start; i < end; i++) {
        bool is_on = layer_state_cmp(state, i);
        dprintf("layer[%u]=%u\n", i, is_on);
        rgblight_set_layer_state(LAYER_OFFSET + i - 1, is_on);
    }
}

extern rgblight_config_t rgblight_config;
extern rgblight_status_t rgblight_status;

#if defined(RGBLIGHT_STARTUP_ANIMATION)

#define STARTUP_ANIMATION_SATURATION 200
#define STARTUP_ANIMATION_VALUE 255
#define STARTUP_ANIMATION_FADE_STEP 5
#define STARTUP_ANIMATION_CYCLE_STEP 2
#define STARTUP_ANIMATION_RAMP_TO_STEPS 70
#define STARTUP_ANIMATION_STEP_TIME 10
#define STARTUP_ANIMATION_INITIAL_DELAY 500

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

static bool    is_enabled;
static uint8_t old_hue;
static uint8_t old_sat;
static uint8_t old_val;
static uint8_t old_mode;
static uint8_t old_base_mode;
static startup_animation_state_t startup_animation_state = DISABLED;
static uint16_t rgblight_startup_loop_timer;

void startup_animation_init(void) {
    is_enabled = rgblight_config.enable;
    old_hue    = rgblight_config.hue;
    old_sat    = rgblight_config.sat;
    old_val    = rgblight_config.val;
    old_mode   = rgblight_config.mode;
    old_base_mode   = rgblight_status.base_mode;
    
    if (!is_enabled)
        rgblight_enable_noeeprom();
}
#endif

void keyboard_post_init_user_rgb(void) {
    // Enable the LED layers
    rgblight_layers = _rgb_layers;
    do_rgb_layers(default_layer_state, LAYER_BASE_DEFAULT + 1, LAYER_BASE_REGULAR);
    do_rgb_layers(layer_state, LAYER_BASE_REGULAR, LAYER_BASE_END);

#if defined(RGBLIGHT_STARTUP_ANIMATION)
    startup_animation_init();
    startup_animation_state = WAITING;
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
                    dprintf("WAITING counter=%u\n", counter);
                    if (counter < STARTUP_ANIMATION_INITIAL_DELAY / STARTUP_ANIMATION_STEP_TIME) {
                        counter++;
                    } else {
                        startup_animation_state = START;
                    }
                    break;

                case RESTART:
                    dprintln("RESTART");
                    startup_animation_init();
                case START:
                    dprintln("START");
                    startup_animation_state = FADE_OLD;
                    counter = old_val;
                    // No break! Just roll into FADE_OLD in the same iteration...

                case FADE_OLD:
                    dprintf("FADE_OLD counter=%u\n", counter);
                    if (counter >= STARTUP_ANIMATION_FADE_STEP) {
                        rgblight_sethsv_noeeprom(old_hue, old_sat, counter);
                        counter -= STARTUP_ANIMATION_FADE_STEP;
                    } else {
                        counter = 0;
                        startup_animation_state = FADE_IN;
                        rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
                    }
                    break;

                case FADE_IN:
                    dprintf("FADE_IN counter=%u\n", counter);
                    if (counter < STARTUP_ANIMATION_VALUE) {
                        rgblight_sethsv_noeeprom(old_hue, STARTUP_ANIMATION_SATURATION, counter);
                        counter += STARTUP_ANIMATION_FADE_STEP;
                    } else {
                        counter = 255;
                        startup_animation_state = CYCLE;
                    }
                    break;

                case CYCLE:
                    dprintf("CYCLE counter=%u\n", counter);
                    if (counter >= STARTUP_ANIMATION_CYCLE_STEP) {
                        rgblight_sethsv_noeeprom((counter + old_hue) % 255, STARTUP_ANIMATION_SATURATION, STARTUP_ANIMATION_VALUE);
                        counter -= STARTUP_ANIMATION_CYCLE_STEP;
                    } else {
                        if ( 
#ifdef RGBLIGHT_EFFECT_BREATHING
                            (old_base_mode == RGBLIGHT_MODE_BREATHING) ||
#endif
#ifdef RGBLIGHT_EFFECT_SNAKE
                            (old_base_mode == RGBLIGHT_MODE_SNAKE) ||
#endif
#ifdef RGBLIGHT_EFFECT_KNIGHT
                            (old_base_mode == RGBLIGHT_MODE_KNIGHT) ||
#endif
#ifdef RGBLIGHT_EFFECT_TWINKLE
                            (old_base_mode == RGBLIGHT_MODE_TWINKLE) ||
#endif
                            !is_enabled) {
                            counter = STARTUP_ANIMATION_VALUE;
                            startup_animation_state = RAMP_DOWN;
                        } else if (
#ifdef RGBLIGHT_EFFECT_STATIC_GRADIENT
                            (old_base_mode == RGBLIGHT_MODE_STATIC_GRADIENT) ||
#endif
#ifdef RGBLIGHT_EFFECT_RAINBOW_MOOD
                            (old_base_mode == RGBLIGHT_MODE_RAINBOW_MOOD) ||
#endif
#ifdef RGBLIGHT_EFFECT_RAINBOW_SWIRL
                            (old_base_mode == RGBLIGHT_MODE_RAINBOW_SWIRL) ||
#endif
#ifdef RGBLIGHT_EFFECT_RAINBOW_CHRISTMAS
                            (old_base_mode == RGBLIGHT_MODE_CHRISTMAS) ||
#endif
#ifdef RGBLIGHT_EFFECT_RAINBOW_RGB_TEST_
                            (old_base_mode == RGBLIGHT_MODE_RGB_TEST) ||
#endif
                            (old_base_mode == RGBLIGHT_MODE_STATIC_LIGHT)) {
                            counter = 0;
                            startup_animation_state = RAMP_TO;
                        } else {
                            startup_animation_state = CLEAN_UP;
                        }
                    }
                    break;

                case RAMP_DOWN:
                    dprintf("RAMP_DOWN counter=%u\n", counter);
                    if (counter >= STARTUP_ANIMATION_FADE_STEP) {
                        rgblight_sethsv_noeeprom(old_hue, STARTUP_ANIMATION_SATURATION, counter);
                        counter -= STARTUP_ANIMATION_FADE_STEP;
                    } else {
                        startup_animation_state = CLEAN_UP;
                    }
                    break;

                case RAMP_TO:
                    dprintf("RAMP_TO s=%u, v=%u, counter=%u\n", old_sat, old_val, counter);
                    uint8_t steps = STARTUP_ANIMATION_RAMP_TO_STEPS;
                    if (counter < steps) {
                        uint8_t s = STARTUP_ANIMATION_SATURATION + counter * (((float)old_sat - STARTUP_ANIMATION_SATURATION) / (float)steps);
                        uint8_t v = STARTUP_ANIMATION_VALUE + counter * (((float)old_val - STARTUP_ANIMATION_VALUE) / (float)steps);
                        rgblight_sethsv_noeeprom(old_hue, s, v);
                        counter++;
                    } else {
                        startup_animation_state = CLEAN_UP;
                    }
                    break;

                case CLEAN_UP:
                    dprintln("CLEAN_UP");
                    rgblight_mode_noeeprom(old_mode);
                    if (is_enabled) {
                        rgblight_sethsv_noeeprom(old_hue, old_sat, old_val);
                    } else {
                        rgblight_disable_noeeprom();
                        // Hack!
                        // rgblight_sethsv_noeeprom() doesn't update these if rgblight is disabled,
                        // but if we do it before disabling we get an ugly flash.
                        // Note this is probably broken on splits.
                        rgblight_config.hue = old_hue;
                        rgblight_config.sat = old_sat;
                        rgblight_config.val = old_val;
                    }
                    startup_animation_state = DONE;
                    dprintln("DONE");
                    break;

                default:
                    break;
            }
        }
    }
#endif
}

layer_state_t default_layer_state_set_user_rgb(layer_state_t state) {
    do_rgb_layers(state, 1u, LAYER_BASE_REGULAR);
    return state;
}

layer_state_t layer_state_set_user_rgb(layer_state_t state) {
    do_rgb_layers(state, LAYER_BASE_REGULAR, LAYER_BASE_END);
    return state;
}

bool led_update_user_rgb(led_t led_state) {
    dprintf("num=%u, cap=%u, scl=%u, cmp=%u, kan=%u\n", led_state.num_lock, led_state.caps_lock, led_state.scroll_lock, led_state.compose, led_state.kana);

    rgblight_set_layer_state(LOCK_OFFSET + USB_LED_NUM_LOCK, led_state.num_lock);
    rgblight_set_layer_state(LOCK_OFFSET + USB_LED_CAPS_LOCK, led_state.caps_lock);
    rgblight_set_layer_state(LOCK_OFFSET + USB_LED_SCROLL_LOCK, led_state.scroll_lock);

    return true;
}

void rgb_layer_ack_yn(bool yn) { rgb_layer_ack(yn ? ACK_YES : ACK_NO); }

void rgb_layer_ack(layer_ack_t n) {
    uint8_t layer = ACK_OFFSET + n;
    dprintf("rgb_layer_ack(%u) ==> %u\n", n, layer);
    rgblight_blink_layer(layer, RGB_LAYER_ACK_DURATION);
}

extern keymap_config_t   keymap_config;
extern rgblight_config_t rgblight_config;

extern bool     spi_gflock;
extern uint16_t spi_replace_mode;

bool process_record_user_rgb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case SPI_GLO:
                spidey_glow();
                return false;
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

        case SPI_LNX:
        case SPI_OSX:
        case SPI_WIN:
            rgb_layer_ack(ACK_MEH);
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
            rgb_layer_ack_yn(rgblight_config.enable);
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
    }
}
