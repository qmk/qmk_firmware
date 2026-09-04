
#include QMK_KEYBOARD_H
#include "split_util.h"

// Trackball custom keycodes
enum custom_keycodes {
    DPI_UP = SAFE_RANGE,
    DPI_DN,
    DPI_RST,
    TL_MEDIA,
};

// DPI presets, cycled with the core pointing device CPI API
static const uint16_t dpi_presets[] = {400, 600, 800, 1200, 1600, 2400, 3200};
#define DPI_PRESET_COUNT (sizeof(dpi_presets) / sizeof(dpi_presets[0]))
#define DPI_DEFAULT_INDEX 2 // 800

static uint8_t dpi_index = DPI_DEFAULT_INDEX;

static void dpi_cycle(bool up) {
    int8_t new_index = (int8_t)dpi_index + (up ? 1 : -1);
    if (new_index < 0)
        new_index = 0;
    if (new_index >= (int8_t)DPI_PRESET_COUNT)
        new_index = (int8_t)DPI_PRESET_COUNT - 1;
    if (new_index != dpi_index) {
        dpi_index = (uint8_t)new_index;
        pointing_device_set_cpi(dpi_presets[dpi_index]);
    }
}

static void dpi_reset(void) {
    dpi_index = DPI_DEFAULT_INDEX;
    pointing_device_set_cpi(dpi_presets[dpi_index]);
}

// TL_MEDIA: tap = toggle media layer, hold = RALT (AltGr)
// Plain keycode (like the original): tap/hold keycodes inside combos are
// buffered by the combo engine and the tap/hold engine sees them late.
// Only addition vs the original: while TL_MEDIA is held, pressing any other
// key engages RALT immediately, so accented keys are never missed.
static uint16_t tl_media_t0      = 0;
static bool     tl_media_pending = false;
static bool     tl_media_hold    = false;

void keyboard_post_init_user(void) {
    keymap_config.nkro = true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
   switch (keycode) {

        case DPI_UP:
            if (record->event.pressed) {
                dpi_cycle(true);
            }
            return false;
        case DPI_DN:
            if (record->event.pressed) {
                dpi_cycle(false);
            }
            return false;
        case DPI_RST:
            if (record->event.pressed) {
                dpi_reset();
            }
            return false;

        case TL_MEDIA:
            if (record->event.pressed) {
                tl_media_t0      = timer_read();
                tl_media_pending = true;
            } else {
                if (tl_media_pending) {
                    layer_invert(1);  // quick press -> toggle media layer
                    tl_media_pending = false;
                } else if (tl_media_hold) {
                    unregister_code(KC_RALT);
                    tl_media_hold = false;
                }
            }
            return false;

        case KC_TAB:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_RALT)) {
                    del_mods(MOD_BIT(KC_RALT));
                    add_mods(MOD_BIT(KC_LALT));
                    register_code(KC_TAB);
                    del_mods(MOD_BIT(KC_LALT));
                    add_mods(MOD_BIT(KC_RALT));
                    return false;
                }
            }

    }

    // Any other key pressed while TL_MEDIA is pending -> AltGr immediately
    if (tl_media_pending && record->event.pressed && !IS_NOEVENT(record->event)) {
        register_code(KC_RALT);
        tl_media_pending = false;
        tl_media_hold    = true;
    }
    return true;
}

void housekeeping_task_user(void) {
    // Fallback: TL_MEDIA held past the term with no other key -> AltGr anyway
    if (tl_media_pending && timer_elapsed(tl_media_t0) > TAPPING_TERM) {
        register_code(KC_RALT);
        tl_media_pending = false;
        tl_media_hold    = true;
    }
}

// - COMBOS 
const uint16_t PROGMEM qmk_combo[] =  {MO(3), TL_MEDIA, KC_DEL, COMBO_END};
const uint16_t PROGMEM game_combo[] = {MO(3), TL_MEDIA, COMBO_END};

combo_t key_combos[] = {
    COMBO(qmk_combo, TG(4)),
    COMBO(game_combo, TG(2)),
};

#define LSFT_CAPS MT(MOD_LSFT,KC_CAPS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


    [0] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),


    [1] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),


    [2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),


    [3] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [4] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
};

// - ENCODER 
static char encoder_status[16] = "               ";

bool encoder_update_user(uint8_t index, bool clockwise) { 

    switch (get_highest_layer(layer_state)) {
        case 0:
        case 2:                               
            if (clockwise) {
                tap_code(KC_VOLU);
                snprintf(encoder_status, sizeof(encoder_status), "VOL+");
            } else {
                tap_code(KC_VOLD);
                snprintf(encoder_status, sizeof(encoder_status), "VOL-");
            }
            break;
        
        case 1:
            if (clockwise) {
                tap_code(KC_MNXT);
                snprintf(encoder_status, sizeof(encoder_status), "NEXT");
            } else {
                tap_code(KC_MPRV);
                snprintf(encoder_status, sizeof(encoder_status), "PREV");
            }
            break;

        case 3:
            if (clockwise) {
                dpi_cycle(true);
                snprintf(encoder_status, sizeof(encoder_status), "DPI+\n%4d", pointing_device_get_cpi());
            } else {
                dpi_cycle(false);
                snprintf(encoder_status, sizeof(encoder_status), "DPI-\n%4d", pointing_device_get_cpi());
            }
            break;
    }
    return false;
}

// - OLED
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

bool oled_task_user(void) {
    if (is_keyboard_left()) {
        return false;
    }

    oled_write_P(PSTR("LYR: "), false);
    switch (get_highest_layer(layer_state)) {
        case 0: oled_write_P(PSTR("BASE "), false); break;
        case 1: oled_write_P(PSTR("MEDIA"), false); break;
        case 2: oled_write_P(PSTR("GAME "), false); break;
        case 3: oled_write_P(PSTR("NAV  "), false); break;
        case 4: oled_write_P(PSTR("QMK  "), false); break;
        default: oled_write_P(PSTR("???  "), false); break;
    }

    oled_advance_page(true);
    
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.caps_lock ? PSTR("CAP  ") : PSTR("     "), false);

    oled_advance_page(true);
    oled_advance_page(true);
    oled_advance_page(true);
    oled_advance_page(true);
    oled_advance_page(true);

    oled_write_P(PSTR("ENC:\n"), false);
    oled_write(encoder_status, false);

    return false;
}

#endif
