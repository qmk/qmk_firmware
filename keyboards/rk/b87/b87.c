// Copyright 2024 yangzheng20003 (@yangzheng20003)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

typedef union {
    uint32_t raw;
    struct {
        uint8_t flag : 1;
        uint8_t devs : 3;
    };
} confinfo_t;
confinfo_t confinfo;

typedef struct {
    bool active;
    uint32_t timer;
    uint32_t interval;
    uint32_t times;
    uint8_t index;
    RGB rgb;
} hs_rgb_indicator_t;

enum layers {
    _BL = 0,
    _FL,
    _MBL,
    _MFL,
    _FBL, 
};

hs_rgb_indicator_t hs_rgb_indicators[HS_RGB_INDICATOR_COUNT];
hs_rgb_indicator_t hs_rgb_bat[HS_RGB_BAT_COUNT];

void rgb_blink_dir(void);
void hs_reset_settings(void);
void rgb_matrix_hs_indicator(void);
void rgb_matrix_hs_indicator_set(uint8_t index, RGB rgb, uint32_t interval, uint8_t times);

#define keymap_is_mac_system() ((get_highest_layer(default_layer_state) == _MBL) || (get_highest_layer(default_layer_state) == _MFL))
#define keymap_is_base_layer() ((get_highest_layer(default_layer_state) == _BL)  || (get_highest_layer(default_layer_state) == _FL))

uint32_t bat_indicator_cnt = true;
static uint32_t ee_clr_timer = 0;

void eeconfig_confinfo_update(uint32_t raw) {

    eeconfig_update_kb(raw);
}

uint32_t eeconfig_confinfo_read(void) {

    return eeconfig_read_kb();
}

void eeconfig_confinfo_default(void) {

    confinfo.flag = true;
    eeconfig_confinfo_update(confinfo.raw);
}

void eeconfig_confinfo_init(void) {

    confinfo.raw = eeconfig_confinfo_read();
    if (!confinfo.raw) {
        eeconfig_confinfo_default();
    }
}

void keyboard_post_init_kb(void) {

#ifdef CONSOLE_ENABLE
    debug_enable = true;
#endif

    eeconfig_confinfo_init();

#ifdef LED_POWER_EN_PIN
    gpio_set_pin_output(LED_POWER_EN_PIN);
    gpio_write_pin_high(LED_POWER_EN_PIN);
    gpio_set_pin_output(A9);
    gpio_write_pin_high(A9);

    gpio_set_pin_output(D2);
    gpio_write_pin_high(D2);

#endif

#ifdef USB_POWER_EN_PIN
    gpio_write_pin_low(USB_POWER_EN_PIN);
    gpio_set_pin_output(USB_POWER_EN_PIN);
#endif

#ifdef HS_BAT_CABLE_PIN
    setPinInputHigh(HS_BAT_CABLE_PIN);
#endif
    keyboard_post_init_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {

    if (process_record_user(keycode, record) != true) {
        return false;
    }
    switch (keycode) {
        case EE_CLR:{
            if (record->event.pressed) {
                ee_clr_timer = timer_read32(); 
            } else {
                ee_clr_timer = 0; 
            }
            return false;
            break;
        }
        case RGB_SPI:{
            if (record->event.pressed) {
                if (rgb_matrix_get_speed() >= (RGB_MATRIX_SPD_STEP * 5)) {
                    rgb_blink_dir();
                }
            }
            return true;
        } break;

        case RGB_SPD: {
            if (record->event.pressed) {
                if (rgb_matrix_get_speed() <= RGB_MATRIX_SPD_STEP) {
                    rgb_blink_dir();
                    rgb_matrix_set_speed(RGB_MATRIX_SPD_STEP);
                    return false;
                }
            }
            return true;
        } break;

        case RGB_VAI: {
            if (record->event.pressed) {
                if (rgb_matrix_get_val() >= (RGB_MATRIX_MAXIMUM_BRIGHTNESS - RGB_MATRIX_VAL_STEP)) {
                    rgb_blink_dir();
                }
            }
            return true;
        } break;

        case RGB_VAD: {
            if (record->event.pressed) {
                if (rgb_matrix_get_val() <= RGB_MATRIX_VAL_STEP) {
                    rgb_blink_dir();
                    rgb_matrix_set_color_all(0x00, 0x00, 0x00);
                }
            }
            return true;
        } break;

        case TO(_BL): {
            if (record->event.pressed) {
                rgb_matrix_hs_indicator_set(HS_RGB_BLINK_INDEX_WIN, (RGB){RGB_WHITE}, 250, 3);
                if (keymap_is_mac_system()) {
                    set_single_persistent_default_layer(_BL);               
                    layer_move(0); 
                }
            }
            return false;
        } break;

        case TO(_MBL): {
            if (record->event.pressed) {
                rgb_matrix_hs_indicator_set(HS_RGB_BLINK_INDEX_MAC, (RGB){RGB_WHITE}, 250, 3);
                if (!keymap_is_mac_system()) {
                    set_single_persistent_default_layer(_MBL);               
                    layer_move(0); 
                }
            }
            return false;
        } break;
        default:
            return true;
    }

    return false;
}

void rgb_blink_dir(void){
    rgb_matrix_hs_indicator_set(HS_RGB_BLINK_INDEX_VAI, (RGB){RGB_WHITE}, 250, 3);
    rgb_matrix_hs_indicator_set(HS_RGB_BLINK_INDEX_VAD, (RGB){RGB_WHITE}, 250, 3);
    rgb_matrix_hs_indicator_set(HS_RGB_BLINK_INDEX_SPI, (RGB){RGB_WHITE}, 250, 3);
   
}

bool hs_reset_settings_user(void) {
    
    for(uint8_t i = 0; i < HS_RGB_INDICATOR_COUNT; i ++){
        rgb_matrix_hs_indicator_set(i, (RGB){RGB_WHITE}, 250, 3);
    }

    return true;
}
void rgb_matrix_hs_indicator_set(uint8_t index, RGB rgb, uint32_t interval, uint8_t times) {
    for (int i = 0; i < HS_RGB_INDICATOR_COUNT; i++) {
        if (!hs_rgb_indicators[i].active) {
            hs_rgb_indicators[i].active = true;
            hs_rgb_indicators[i].timer = timer_read32();
            hs_rgb_indicators[i].interval = interval;
            hs_rgb_indicators[i].times = times * 2;
            hs_rgb_indicators[i].index = index;
            hs_rgb_indicators[i].rgb = rgb;
            break;
        }
    }
}

void rgb_matrix_hs_indicator(void) {
    for (int i = 0; i < HS_RGB_INDICATOR_COUNT; i++) {
        if (hs_rgb_indicators[i].active) {
            if (timer_elapsed32(hs_rgb_indicators[i].timer) >= hs_rgb_indicators[i].interval) {
                hs_rgb_indicators[i].timer = timer_read32();

                if (hs_rgb_indicators[i].times) {
                    hs_rgb_indicators[i].times--;
                }

                if (hs_rgb_indicators[i].times <= 0) {
                    hs_rgb_indicators[i].active = false;
                    hs_rgb_indicators[i].timer = 0x00;
                }
            }

            if (hs_rgb_indicators[i].times % 2) {
                rgb_matrix_set_color(hs_rgb_indicators[i].index, hs_rgb_indicators[i].rgb.r, hs_rgb_indicators[i].rgb.g, hs_rgb_indicators[i].rgb.b);
            } else {
                rgb_matrix_set_color(hs_rgb_indicators[i].index, 0x00, 0x00, 0x00);
            }
        }
    }
}

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {

    if (rgb_matrix_indicators_advanced_user(led_min, led_max) != true) {
        return false;
    }

    if (ee_clr_timer && timer_elapsed32(ee_clr_timer) > 3000) {
        hs_reset_settings();
        ee_clr_timer = 0;  
    }
    
    if (host_keyboard_led_state().caps_lock)
        rgb_matrix_set_color(HS_RGB_INDEX_CAPS, RGB_WHITE);
    else
        rgb_matrix_set_color(HS_RGB_INDEX_CAPS, RGB_BLACK);
    if (!keymap_is_mac_system() && keymap_config.no_gui)
        rgb_matrix_set_color(HS_RGB_INDEX_WIN_LOCK, RGB_WHITE);
    else
        rgb_matrix_set_color(HS_RGB_INDEX_WIN_LOCK, RGB_BLACK);
    rgb_matrix_set_color(2, RGB_BLACK);
        
    rgb_matrix_hs_indicator();

    return true;
}

void hs_reset_settings(void) {
    eeconfig_init();
    eeconfig_update_rgb_matrix_default();

    keymap_config.raw = eeconfig_read_keymap();
#if defined(NKRO_ENABLE) && defined(FORCE_NKRO)
    keymap_config.nkro = 1;
    eeconfig_update_keymap(keymap_config.raw);
#endif
    if (hs_reset_settings_user() != true) {
        return;
    }
    keyboard_post_init_kb();
}
