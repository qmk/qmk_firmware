#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#    include "lufa.h"
#    include "split_util.h"
#endif
#ifdef AUDIO_ENABLE
#    include "audio.h"
#endif
#ifdef SSD1306OLED
#    include "ssd1306.h"
#endif

#ifdef RGBLIGHT_ENABLE
// Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
uint8_t                  RGB_current_mode;
HSV                      CURRENT_COLOR;
void keyboard_post_init_user(void) {
    rgblight_enable();  // Enables RGB, without saving settings
    rgblight_mode(RGBLIGHT_MODE_CHRISTMAS);
    RGB_current_mode = rgblight_config.mode;
}
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number { _QWERTY = 0, _COLEMAK, _DVORAK, _LOWER, _RAISE };

enum custom_keycodes { QWERTY = SAFE_RANGE, COLEMAK, DVORAK, LOWER, RAISE, RGBRST };

#define LOWER MO(1)
#define RAISE MO(2)

// HELIX_ROWS == 5
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {[_QWERTY] = LAYOUT(
KC_GRV,
            KC_1,
            KC_2,
            KC_3,
            KC_4,
            KC_5,
            KC_6,
            KC_7,
            KC_8,
            KC_9,
            KC_0,
            KC_DEL,
            KC_TAB,
            KC_Q,
            KC_W,
            KC_E,
            KC_R,
            KC_T,
            KC_Y,
            KC_U,
            KC_I,
            KC_O,
            KC_P,
            KC_BSPC,
            KC_CAPS,
            KC_A,
            KC_S,
            KC_D,
            KC_F,
            KC_G,
            KC_H,
            KC_J,
            KC_K,
            KC_L,
            KC_SCLN,
            KC_ENT,
            KC_LSFT,
            KC_Z,
            KC_X,
            KC_C,
            KC_V,
            KC_B,
            KC_QUOT,
            KC_NUHS,
            KC_N,
            KC_M,
            KC_COMM,
            KC_DOT,
            KC_SLSH,
            KC_RSFT,
            KC_LCTL,
            KC_ESC,
            KC_LGUI,
            KC_LALT,
            MO(2),
            MO(1),
            KC_SPC,
            KC_SPC,
            KC_RALT,
            KC_LEFT,
            KC_UP,
            KC_DOWN,
            KC_RGHT,
            KC_RCTL
),

                                                              [_LOWER] = LAYOUT(
KC_F1,
            KC_F2,
            KC_F3,
            KC_F4,
            KC_F5,
            KC_F6,
            KC_F7,
            KC_F8,
            KC_F9,
            KC_F10,
            KC_F11,
            KC_F12,
            KC_TRNS,
            KC_TRNS,
            KC_BRID,
            KC_BRIU,
            KC_TRNS,
            KC_TRNS,
            KC_PSCR,
            KC_INS,
            KC_TRNS,
            KC_MINS,
            KC_EQL,
            KC_TRNS,
            KC_TRNS,
            KC_MUTE,
            KC_VOLD,
            KC_VOLU,
            KC_MPLY,
            KC_TRNS,
            KC_TRNS,
            KC_TRNS,
            KC_TRNS,
            KC_LBRC,
            KC_RBRC,
            KC_TRNS,
            KC_TRNS,
            KC_NUBS,
            KC_TRNS,
            KC_TRNS,
            KC_TRNS,
            KC_TRNS,
            KC_TRNS,
            KC_TRNS,
            KC_TRNS,
            KC_TRNS,
            KC_TRNS,
            KC_TRNS,
            KC_TRNS,
            KC_TRNS,
            KC_TRNS,
            KC_TRNS,
            KC_TRNS,
            KC_TRNS,
            KC_TRNS,
            KC_TRNS,
            KC_TRNS,
            KC_TRNS,
            KC_TRNS,
            KC_HOME,
            KC_PGUP,
            KC_PGDN,
            KC_END,
            KC_TRNS
),

                                                              [_RAISE] = LAYOUT(
KC_NO,
            KC_NO,
            KC_NO,
            KC_NO,
            KC_NO,
            KC_NO,
            KC_NO,
            KC_NO,
            KC_NO,
            KC_NO,
            KC_NO,
            KC_NO,
            RGB_M_R,
            RGB_M_K,
            RGB_M_SN,
            RGB_M_SW,
            RGB_TOG,
            KC_NO,
            KC_NO,
            RGB_MOD,
            RGB_RMOD,
            KC_NO,
            KC_NO,
            KC_NO,
            RGB_M_G,
            RGB_M_B,
            RGB_M_P,
            RGB_M_T,
            RGB_M_X,
            KC_NO,
            KC_NO,
            RGB_HUI,
            RGB_HUD,
            KC_NO,
            KC_NO,
            KC_NO,
            KC_NO,
            KC_NO,
            KC_NO,
            KC_NO,
            KC_NO,
            KC_NO,
            KC_NO,
            KC_NO,
            KC_NO,
            KC_NO,
            KC_NO,
            KC_NO,
            KC_NO,
            KC_NO,
            KC_NO,
            KC_NO,
            KC_NO,
            KC_NO,
            KC_TRNS,
            KC_NO,
            KC_NO,
            KC_NO,
            KC_NO,
            KC_NO,
            KC_NO,
            KC_NO,
            KC_NO,
            KC_NO
                                                                  )};

// define variables for reactive RGB
bool TOG_STATUS = false;

void persistent_default_layer_set(uint16_t default_layer) {
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
#ifdef AUDIO_ENABLE
                PLAY_SONG(tone_qwerty);
#endif
                persistent_default_layer_set(1UL << _QWERTY);
            }
            return false;
            break;
        case COLEMAK:
            if (record->event.pressed) {
#ifdef AUDIO_ENABLE
                PLAY_SONG(tone_colemak);
#endif
                persistent_default_layer_set(1UL << _COLEMAK);
            }
            return false;
            break;
        case DVORAK:
            if (record->event.pressed) {
#ifdef AUDIO_ENABLE
                PLAY_SONG(tone_dvorak);
#endif
                persistent_default_layer_set(1UL << _DVORAK);
            }
            return false;
            break;
        case LOWER:
            if (record->event.pressed) {
                // not sure how to have keyboard check mode and set it to a variable, so my work around
                // uses another variable that would be set to true after the first time a reactive key is pressed.
                if (TOG_STATUS) {  // TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
                } else {
                    TOG_STATUS = !TOG_STATUS;
#ifdef RGBLIGHT_ENABLE
                    RGB_current_mode = rgblight_config.mode;
                    CURRENT_COLOR    = (HSV){rgblight_config.hue, rgblight_config.sat, rgblight_config.val};
                    rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
                    rgblight_sethsv(HSV_BLUE);
#endif
                }
                layer_on(_LOWER);
            } else {
#ifdef RGBLIGHT_ENABLE
                rgblight_mode(RGB_current_mode);
                rgblight_sethsv(CURRENT_COLOR.h, CURRENT_COLOR.s, CURRENT_COLOR.v);
                CURRENT_COLOR = (HSV){rgblight_config.hue, rgblight_config.sat, rgblight_config.val};
#endif
                TOG_STATUS = false;
                layer_off(_LOWER);
            }
            return false;
            break;
        case RAISE:
            if (record->event.pressed) {
                // not sure how to have keyboard check mode and set it to a variable, so my work around
                // uses another variable that would be set to true after the first time a reactive key is pressed.
                if (TOG_STATUS) {  // TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
                } else {
                    TOG_STATUS = !TOG_STATUS;
#ifdef RGBLIGHT_ENABLE
                    RGB_current_mode = rgblight_config.mode;
                    CURRENT_COLOR    = (HSV){rgblight_config.hue, rgblight_config.sat, rgblight_config.val};
                    rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
                    rgblight_sethsv(HSV_RED);
#endif
                }
                layer_on(_RAISE);
            } else {
#ifdef RGBLIGHT_ENABLE
                rgblight_mode(RGB_current_mode);
                rgblight_sethsv(CURRENT_COLOR.h, CURRENT_COLOR.s, CURRENT_COLOR.v);
                CURRENT_COLOR = (HSV){rgblight_config.hue, rgblight_config.sat, rgblight_config.val};
#endif
                layer_off(_RAISE);
                TOG_STATUS = false;
            }
            return false;
            break;
            // led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
        case RGB_MOD:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                rgblight_mode(RGB_current_mode);
                rgblight_step();
                RGB_current_mode = rgblight_config.mode;
            }
#endif
            return false;
            break;
        case RGB_RMOD:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                rgblight_mode(RGB_current_mode);
                rgblight_step_reverse();
                RGB_current_mode = rgblight_config.mode;
            }
#endif
            return false;
            break;
            // Estos faltan agregar...
            // RGB_SPI,RGB_VAI,RGB_SAI,
            // RGB_SPD,RGB_VAD,RGB_SAD,
        case RGB_M_R:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                rgblight_mode(RGBLIGHT_MODE_RAINBOW_MOOD + 1);
                RGB_current_mode = rgblight_config.mode;
            }
#endif
            return false;
            break;
        case RGB_M_K:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                rgblight_mode(RGBLIGHT_MODE_KNIGHT + 1);
                RGB_current_mode = rgblight_config.mode;
            }
#endif
            return false;
            break;
        case RGB_M_SN:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                rgblight_mode(RGBLIGHT_MODE_SNAKE + 3);
                RGB_current_mode = rgblight_config.mode;
            }
#endif
            return false;
            break;
        case RGB_M_SW:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL + 3);
                RGB_current_mode = rgblight_config.mode;
            }
#endif
            return false;
            break;
        case RGB_M_G:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                rgblight_mode(RGBLIGHT_MODE_TWINKLE + 5);
                RGB_current_mode = rgblight_config.mode;
            }
#endif
            return false;
            break;
        case RGB_M_B:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                rgblight_mode(RGBLIGHT_MODE_BREATHING + 2);
                RGB_current_mode = rgblight_config.mode;
            }
#endif
            return false;
            break;
        case RGB_M_P:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
                RGB_current_mode = rgblight_config.mode;
            }
#endif
            return false;
            break;
        case RGB_M_T:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                rgblight_mode(RGBLIGHT_MODE_RGB_TEST);
                RGB_current_mode = rgblight_config.mode;
            }
#endif
            return false;
            break;
        case RGB_M_X:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                rgblight_mode(RGBLIGHT_MODE_CHRISTMAS);
                RGB_current_mode = rgblight_config.mode;
            }
#endif
            return false;
            break;
        case RGB_HUI:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                rgblight_mode(RGB_current_mode);
                RGB_current_mode = rgblight_config.mode;
                rgblight_increase_hue();
                CURRENT_COLOR = (HSV){rgblight_config.hue, rgblight_config.sat, rgblight_config.val};
            }
#endif
            return false;
            break;
        case RGB_HUD:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                rgblight_mode(RGB_current_mode);
                RGB_current_mode = rgblight_config.mode;
                rgblight_decrease_hue();
                CURRENT_COLOR = (HSV){rgblight_config.hue, rgblight_config.sat, rgblight_config.val};
            }
#endif
            return false;
            break;
        case RGBRST:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                eeconfig_update_rgblight_default();
                rgblight_enable();
                RGB_current_mode = rgblight_config.mode;
            }
#endif
            break;
    }
    return true;
}

void matrix_init_user(void) {
#ifdef AUDIO_ENABLE
    startup_user();
#endif
#ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
    CURRENT_COLOR    = (HSV){rgblight_config.hue, rgblight_config.sat, rgblight_config.val};
#endif
// SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED
    iota_gfx_init(!has_usb());  // turns on the display
#endif
}

#ifdef AUDIO_ENABLE

void startup_user() {
    _delay_ms(20);  // gets rid of tick
}

void shutdown_user() {
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void) { music_scale_user(); }

void music_scale_user(void) { PLAY_SONG(music_scale); }

#endif

// SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

void matrix_scan_user(void) {
    iota_gfx_task();  // this is what updates the display continuously
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
    if (memcmp(dest->display, source->display, sizeof(dest->display))) {
        memcpy(dest->display, source->display, sizeof(dest->display));
        dest->dirty = true;
    }
}

// assign the right code to your layers for OLED display
#    define L_BASE 0
#    define L_LOWER (1 << _LOWER)
#    define L_RAISE (1 << _RAISE)
static void render_logo(struct CharacterMatrix *matrix) {
    static const char helix_logo[] PROGMEM = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0};
    matrix_write_P(matrix, helix_logo);
    // matrix_write_P(&matrix, PSTR(" Split keyboard kit"));
}

static void render_rgbled_status(bool full, struct CharacterMatrix *matrix) {
#    ifdef RGBLIGHT_ENABLE
    char buf[30];
    if (RGBLIGHT_MODES > 1 && rgblight_config.enable) {
        if (full) {
            snprintf(buf, sizeof(buf), " LED %2d: %d,%d,%d ", rgblight_config.mode, rgblight_config.hue / RGBLIGHT_HUE_STEP, rgblight_config.sat / RGBLIGHT_SAT_STEP, rgblight_config.val / RGBLIGHT_VAL_STEP);
        } else {
            snprintf(buf, sizeof(buf), "[%2d] ", rgblight_config.mode);
        }
        matrix_write(matrix, buf);
    }
#    endif
}

static void render_layer_status(struct CharacterMatrix *matrix) {
    // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
    char buf[10];
    matrix_write_P(matrix, PSTR("Layer: "));
    switch (layer_state) {
        case L_BASE:
            matrix_write_P(matrix, PSTR("Default"));
            break;
        case L_RAISE:
            matrix_write_P(matrix, PSTR("Raise"));
            break;
        case L_LOWER:
            matrix_write_P(matrix, PSTR("Lower"));
            break;
        default:
            matrix_write_P(matrix, PSTR("Undef-"));
            snprintf(buf, sizeof(buf), "%ld", layer_state);
            matrix_write(matrix, buf);
    }
}

void render_status(struct CharacterMatrix *matrix) {
    // Render to mode icon
    static const char os_logo[][2][3] PROGMEM = {{{0x95, 0x96, 0}, {0xb5, 0xb6, 0}}, {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}}};
    if (keymap_config.swap_lalt_lgui == false) {
        matrix_write_P(matrix, os_logo[0][0]);
        matrix_write_P(matrix, PSTR("\n"));
        matrix_write_P(matrix, os_logo[0][1]);
    } else {
        matrix_write_P(matrix, os_logo[1][0]);
        matrix_write_P(matrix, PSTR("\n"));
        matrix_write_P(matrix, os_logo[1][1]);
    }

    matrix_write_P(matrix, PSTR(" "));
    render_layer_status(matrix);
    matrix_write_P(matrix, PSTR("\n"));

    // Host Keyboard LED Status
    matrix_write_P(matrix, (host_keyboard_leds() & (1 << USB_LED_NUM_LOCK)) ? PSTR("NUMLOCK") : PSTR("       "));
    matrix_write_P(matrix, (host_keyboard_leds() & (1 << USB_LED_CAPS_LOCK)) ? PSTR("CAPS") : PSTR("    "));
    matrix_write_P(matrix, (host_keyboard_leds() & (1 << USB_LED_SCROLL_LOCK)) ? PSTR("SCLK") : PSTR("    "));
    matrix_write_P(matrix, PSTR("\n"));
    render_rgbled_status(true, matrix);
}

void iota_gfx_task_user(void) {
    struct CharacterMatrix matrix;

#    if DEBUG_TO_SCREEN
    if (debug_enable) {
        return;
    }
#    endif

    matrix_clear(&matrix);
    if (is_master) {
        render_status(&matrix);
    } else {
        render_logo(&matrix);
        render_rgbled_status(false, &matrix);
        render_layer_status(&matrix);
    }
    matrix_update(&display, &matrix);
}

#endif
