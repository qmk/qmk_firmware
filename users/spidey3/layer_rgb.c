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
    rgblight_mode(RGBLIGHT_MODE_TWINKLE + 4);
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

    [ACK_OFFSET + ACK_MEH + 1] = NULL
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
static bool              startup_animation_done = false;

void keyboard_post_init_user_rgb(void) {
    // Enable the LED layers
    rgblight_layers = _rgb_layers;
    do_rgb_layers(default_layer_state, LAYER_BASE_DEFAULT + 1, LAYER_BASE_REGULAR);
    do_rgb_layers(layer_state, LAYER_BASE_REGULAR, LAYER_BASE_END);

    // Startup animation
    {
        bool    is_enabled = rgblight_config.enable;
        uint8_t old_hue    = rgblight_config.hue;
        uint8_t old_sat    = rgblight_config.sat;
        uint8_t old_val    = rgblight_config.val;
        uint8_t old_mode   = rgblight_config.mode;

        bool ramp_down =
#ifdef RGBLIGHT_EFFECT_BREATHING
            (rgblight_status.base_mode == RGBLIGHT_MODE_BREATHING) ||
#endif
#ifdef RGBLIGHT_EFFECT_SNAKE
            (rgblight_status.base_mode == RGBLIGHT_MODE_SNAKE) ||
#endif
#ifdef RGBLIGHT_EFFECT_KNIGHT
            (rgblight_status.base_mode == RGBLIGHT_MODE_KNIGHT) ||
#endif
#ifdef RGBLIGHT_EFFECT_TWINKLE
            (rgblight_status.base_mode == RGBLIGHT_MODE_TWINKLE) ||
#endif
            !is_enabled;

        bool ramp_to =
#ifdef RGBLIGHT_EFFECT_STATIC_GRADIENT
            (rgblight_status.base_mode == RGBLIGHT_MODE_STATIC_GRADIENT) ||
#endif
#ifdef RGBLIGHT_EFFECT_RAINBOW_MOOD
            (rgblight_status.base_mode == RGBLIGHT_MODE_RAINBOW_MOOD) ||
#endif
#ifdef RGBLIGHT_EFFECT_RAINBOW_SWIRL
            (rgblight_status.base_mode == RGBLIGHT_MODE_RAINBOW_SWIRL) ||
#endif
#ifdef RGBLIGHT_EFFECT_RAINBOW_CHRISTMAS
            (rgblight_status.base_mode == RGBLIGHT_MODE_CHRISTMAS) ||
#endif
#ifdef RGBLIGHT_EFFECT_RAINBOW_RGB_TEST_
            (rgblight_status.base_mode == RGBLIGHT_MODE_RGB_TEST) ||
#endif
            (rgblight_status.base_mode == RGBLIGHT_MODE_STATIC_LIGHT);

#define STARTUP_ANIMATION_SATURATION 200
#define STARTUP_ANIMATION_VALUE 255
#define STARTUP_ANIMATION_STEP 5

        rgblight_enable_noeeprom();
        if (rgblight_config.enable) {
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
            for (uint8_t i = 0; i < STARTUP_ANIMATION_VALUE; i += STARTUP_ANIMATION_STEP) {
                rgblight_sethsv_noeeprom(old_hue, STARTUP_ANIMATION_SATURATION, i);
                matrix_scan();
                wait_ms(10);
            }
            for (uint8_t i = 255; i > 0; i -= STARTUP_ANIMATION_STEP) {
                rgblight_sethsv_noeeprom((i + old_hue) % 255, STARTUP_ANIMATION_SATURATION, STARTUP_ANIMATION_VALUE);
                matrix_scan();
                wait_ms(10);
            }

            if (ramp_down) {
                dprintln("ramp_down");
                for (uint8_t i = STARTUP_ANIMATION_VALUE; i > 0; i -= STARTUP_ANIMATION_STEP) {
                    rgblight_sethsv_noeeprom(old_hue, STARTUP_ANIMATION_SATURATION, i);
                    matrix_scan();
                    wait_ms(10);
                }
            } else if (ramp_to) {
                dprintf("ramp_to s=%u, v=%u\n", old_sat, old_val);
                uint8_t steps = 50;
                for (uint8_t i = 0; i < steps; i++) {
                    uint8_t s = STARTUP_ANIMATION_SATURATION + i * (((float)old_sat - STARTUP_ANIMATION_SATURATION) / (float)steps);
                    uint8_t v = STARTUP_ANIMATION_VALUE + i * (((float)old_val - STARTUP_ANIMATION_VALUE) / (float)steps);
                    rgblight_sethsv_noeeprom(old_hue, s, v);
                    matrix_scan();
                    wait_ms(10);
                }
            }
            rgblight_mode_noeeprom(old_mode);
        }
        if (is_enabled) {
            rgblight_sethsv_noeeprom(old_hue, old_sat, old_val);
        } else {
            rgblight_disable_noeeprom();
            // Hack!
            // rgblight_sethsv_noeeprom() doesn't update these if rgblight is disabled,
            // but if do it before disabling we get an ugly flash.
            rgblight_config.hue = old_hue;
            rgblight_config.sat = old_sat;
            rgblight_config.val = old_val;
        }
        dprint("done\n");
        startup_animation_done = true;
    }
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
            rgb_layer_ack_yn(debug_enable);
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
