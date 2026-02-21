// Copyright 2025 lucky(@lucky-zang)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "rgb_record/rgb_record.h"
#include "rgb_record/rgb_rgblight.h"

#include "usb_main.h"
#include "rgb_matrix_blink.h"

enum layers {
    _BL = 0,
    _FL,
    _MBL,
    _MFL,
    _FBL,
};

typedef union {
    uint32_t raw;
    struct {
        uint8_t sleep_timeout : 3;
        uint8_t rgb_ligth_mode : 4;
        uint8_t kj_rgblight_mode : 4;
        uint8_t kj_cut_f_layer: 1;
        uint8_t kj_esc_grv: 1;

        uint8_t record_last_mode ;
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
    void (*blink_cb)(uint8_t);
} kj_rgb_indicator_t;

#define keymap_is_mac_system() ((get_highest_layer(default_layer_state) == _MBL))

static uint32_t ee_clr_timer = 0;
bool test_white_light_flag   = false;
bool kj_reset_flag           = false;
static uint32_t kj_reset_time = 0;
static bool shifted          = false;

void kj_reset_settings(void);
void ind_indicators_hook(uint8_t index);
void nkr_indicators_hook(uint8_t index);
blink_rgb_t blink_rgbs[RGB_MATRIX_BLINK_COUNT] = {
    {.index = RGB_MATRIX_BLINK_INDEX_IND, .interval = 250, .times = 3, .color = {.r = 0x00, .g = 0x00, .b = 0x00}, .blink_cb = ind_indicators_hook},
    {.index = RGB_MATRIX_BLINK_INDEX_ALL, .interval = 250, .times = 3, .color = {.r = WIITE_B, .g = 0x00, .b = 0x00}, .blink_cb = nkr_indicators_hook},
};

void nkr_indicators_hook(uint8_t index) {
    if (index == RGB_MATRIX_BLINK_INDEX_ALL) {
        if ((blink_rgbs[RGB_MATRIX_BLINK_COUNT - 1].color.r == WIITE_B) && (blink_rgbs[RGB_MATRIX_BLINK_COUNT - 1].color.g == 0x00) && (blink_rgbs[RGB_MATRIX_BLINK_COUNT - 1].color.b == 0x00)) {
            if (rgb_matrix_blink_set_color(index, 0x00, 0x00, WIITE_B) != true) {
                dprintf("RGB_BLUE again\n");
            }
            rgb_matrix_blink_set_times(index, 1);
            rgb_matrix_blink_set(index);
            dprintf("GREEM\r\n");
        } else if ((blink_rgbs[RGB_MATRIX_BLINK_COUNT - 1].color.r == 0x00) && (blink_rgbs[RGB_MATRIX_BLINK_COUNT - 1].color.g == 0x00) && (blink_rgbs[RGB_MATRIX_BLINK_COUNT - 1].color.b == WIITE_B)) {
            if (rgb_matrix_blink_set_color(index, 0x00, WIITE_B, 0x00) != true) {
                dprintf("RGB_GREEN again\n");
            }
            rgb_matrix_blink_set_times(index, 1);
            rgb_matrix_blink_set(index);
            dprintf("BLUE\r\n");
        }
    }
}

typedef enum {
    ind_state_none = 0,
    ind_state_exec,
    ind_state_blink3,
    ind_state_blinkon,
    ind_state_blinkoff,
} ind_status_t;

ind_status_t ind_status = ind_state_none;

void ind_indicators_hook(uint8_t index) {

    switch(ind_status) {
        case ind_state_none: {
            rgb_matrix_blink_set_color(index, 0x00, 0x00, 0x00);
            rgb_matrix_blink_set_interval_times(index, 50, 0xFF);
        } break;
        case ind_state_blink3: {
            rgb_matrix_blink_set_color(index, 0xFF, 0xFF, 0xFF);
            rgb_matrix_blink_set_interval_times(index, 250, 3);
            ind_status = ind_state_exec;
        } break;
        case ind_state_blinkon: {
            RGB rgb;
            HSV hsv = {.h = 0, .s = 0};
            hsv.v = rgb_matrix_get_val();

            rgb = hsv_to_rgb(hsv); 
            rgb_matrix_blink_set_color(index, rgb.r , rgb.g, rgb.b);
            rgb_matrix_blink_set_interval_times(index, 500, 1);
        } break;
        case ind_state_blinkoff: {
            ind_status = ind_state_none;
            ind_indicators_hook(index);
        } break;
        case ind_state_exec: {
            ind_status = ind_state_none;
            ind_indicators_hook(index);
        } break;
        default: break;
    }

    rgb_matrix_blink_set(index);
}

void ind_set_blink(ind_status_t status) {
    ind_status = status;
    rgb_matrix_blink_set_remain_time(RGB_MATRIX_BLINK_INDEX_IND, 0x00);
    ind_indicators_hook(RGB_MATRIX_BLINK_INDEX_IND);
}

bool rgb_matrix_blink_user(blink_rgb_t *blink_rgb) {

    switch (blink_rgb->index) {
        case RGB_MATRIX_BLINK_INDEX_BAT: {
            if (ind_status != ind_state_none) {
                return false;
            }
            if(test_white_light_flag == true) {
                return false;
            }

            if (blink_rgb->flip) {
                if (blink_rgb->color.r) {

                }  
            }else {
                
            }
            return false;
        } break;

        case RGB_MATRIX_BLINK_INDEX_IND: {
            
            switch(ind_status) {
                case ind_state_none: {
                    return false;
                } break;
                case ind_state_blinkon:
                case ind_state_blinkoff: {

                    if (!blink_rgb->flip) {  
                        
                    } 
                } break;
                case ind_state_exec: {

                    if (blink_rgb->flip) {
                        for (uint8_t i = 1; i < (RGB_MATRIX_LED_COUNT - RGBLED_NUM); i++) {
                            rgb_matrix_set_color(i, WIITE_B, WIITE_B, WIITE_B);
                        }
                    } else {
                        for (uint8_t i = 1; i < (RGB_MATRIX_LED_COUNT - RGBLED_NUM); i++) {
                            rgb_matrix_set_color(i, 0x00, 0x00, 0x00);
                        }
                    }
                } break;
                default: break;
            }
            return false;
        } break;
        default: { 
 
        } break;
    }

    return true;
}

void eeconfig_confinfo_update(void) {

    eeconfig_update_kb(confinfo.raw);
}

uint32_t eeconfig_confinfo_read(void) {

    return eeconfig_read_kb();
}

uint8_t kj_get_sleep_timeout(void){
    return confinfo.sleep_timeout;
}

void kj_set_sleep_timeout(uint8_t sleep_timeout){
    confinfo.sleep_timeout = sleep_timeout;
}


void eeconfig_confinfo_default(void) {

    confinfo.record_last_mode  = 0x00;
    confinfo.sleep_timeout     = 7;
    confinfo.rgb_ligth_mode    = 0;
    confinfo.kj_rgblight_mode  = 0;
    confinfo.kj_cut_f_layer    = false;
    confinfo.kj_esc_grv        = false;

    eeconfig_init_user_datablock();
    eeconfig_confinfo_update();
    rgb_matrix_mode(13);
#if defined(NKRO_ENABLE) && defined(FORCE_NKRO)
    keymap_config.nkro = 1;
    eeconfig_update_keymap(&keymap_config);
#endif

#ifdef RGBLIGHT_ENABLE
    rgblight_mode(14);
#endif

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
#endif

#ifdef USB_POWER_EN_PIN
    gpio_write_pin_low(USB_POWER_EN_PIN);
    gpio_set_pin_output(USB_POWER_EN_PIN);
#endif

#ifdef RGB_MATRIX_BLINK_INDEX_BAT
    rgb_matrix_blink_set_interval_times(RGB_MATRIX_BLINK_INDEX_BAT, 200, 0xFF);
    rgb_matrix_blink_set(RGB_MATRIX_BLINK_INDEX_BAT);
#endif

#ifdef RGB_MATRIX_BLINK_INDEX_IND
    rgb_matrix_blink_set_interval_times(RGB_MATRIX_BLINK_INDEX_IND, 200, 0xFF);
    rgb_matrix_blink_set(RGB_MATRIX_BLINK_INDEX_IND);
#endif

    keyboard_post_init_user();
}

void usb_power_connect(void) {

#    ifdef USB_POWER_EN_PIN
    gpio_write_pin_low(USB_POWER_EN_PIN);
#    endif
}

void usb_power_disconnect(void) {

#    ifdef USB_POWER_EN_PIN
    gpio_write_pin_high(USB_POWER_EN_PIN);
#    endif
}

void suspend_power_down_kb(void) {

#    ifdef LED_POWER_EN_PIN
    gpio_write_pin_low(LED_POWER_EN_PIN);
#    endif

    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {

#    ifdef LED_POWER_EN_PIN
    gpio_write_pin_high(LED_POWER_EN_PIN);
#    endif

    suspend_wakeup_init_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {

    if (test_white_light_flag && record->event.pressed) {
        test_white_light_flag = false;
        rgb_matrix_set_color_all(0x00, 0x00, 0x00);
    }

    typedef struct {
        uint16_t base_key;    
        uint16_t win_key;     
        uint16_t mac_key;     
        bool is_consumer;     
    } fnmap_t;

    static const fnmap_t fn_map_table[] = {
        {KC_1,   KC_F1,   KC_BRID, false},
        {KC_2,   KC_F2,   KC_BRIU, false},
        {KC_3,   KC_F3,   KC_ZLYX, false},  
        {KC_4,   KC_F4,   KC_JJSS, false},  
        {KC_5,   KC_F5,   0x00CF,  true},   
        {KC_6,   KC_F6,   KC_QPJT, false},  
        {KC_7,   KC_F7,   KC_MPRV, false},
        {KC_8,   KC_F8,   KC_MPLY, false},
        {KC_9,   KC_F9,   KC_MNXT, false},
        {KC_0,   KC_F10,  KC_MUTE, false},
        {KC_MINS,KC_F11,  KC_VOLD, false},
        {KC_EQL, KC_F12,  KC_VOLU, false},
        {KC_F1,  KC_BRID, KC_F1,   false},
        {KC_F2,  KC_BRIU, KC_F2,   false},
        {KC_F3,  KC_ZHCK, KC_F3,   false},   
        {KC_F4,  KC_WSCH, KC_F4,   false},
        {KC_F5,  KC_MCF,  KC_F5,   false},   
        {KC_F6,  KC_MSEL, KC_F6,   false},
        {KC_F7,  KC_MPRV, KC_F7,   false},
        {KC_F8,  KC_MPLY, KC_F8,   false},
        {KC_F9,  KC_MNXT, KC_F9,   false},
        {KC_F10, KC_MUTE, KC_F10,  false},
        {KC_F11, KC_VOLD, KC_F11,  false},
        {KC_F12, KC_VOLU, KC_F12,  false},
    };

    if (confinfo.kj_cut_f_layer) {
        for (uint8_t i = 0; i < ARRAY_SIZE(fn_map_table); i++) {
            if (keycode == fn_map_table[i].base_key) {
                bool is_mac = keymap_is_mac_system();
                const fnmap_t *entry = &fn_map_table[i];
                
                if (record->event.pressed) {
                    if (is_mac) {
                        if (entry->is_consumer) {
                            host_consumer_send(entry->mac_key);
                        } else {
                            switch (entry->mac_key) {
                                case KC_QPJT:
                                    register_code(KC_LCMD);
                                    register_code(KC_LSFT);
                                    register_code(KC_3);
                                    break;
                                case KC_ZLYX:
                                    register_code(KC_LCTL);
                                    register_code(KC_UP);
                                    break;
                                case KC_JJSS:
                                    register_code(KC_LCMD);
                                    register_code(KC_SPC);
                                    break;
                                default:
                                    register_code(entry->mac_key);
                                    break;
                            }
                        }
                    } else {
                        switch (entry->win_key) {
                            case KC_ZHCK: 
                                register_code(KC_LCTL);
                                register_code(KC_LALT);
                                register_code(KC_TAB);
                                break;
                            case KC_MCF:
                                register_code(KC_LWIN);
                                register_code(KC_H);
                                break;
                            default:
                                register_code(entry->win_key);
                                break;
                        }
                    }
                } else {
                    if (is_mac) {
                        if (entry->is_consumer) {
                            host_consumer_send(0);
                        } else {
                            switch (entry->mac_key) {
                                case KC_QPJT:
                                    unregister_code(KC_LCMD);
                                    unregister_code(KC_LSFT);
                                    unregister_code(KC_3);
                                    break;
                                case KC_ZLYX:
                                    unregister_code(KC_LCTL);
                                    unregister_code(KC_UP);
                                    break;
                                case KC_JJSS:
                                    unregister_code(KC_LCMD);
                                    unregister_code(KC_SPC);
                                    break;
                                default:
                                    unregister_code(entry->mac_key);
                                    break;
                            }
                        }
                    } else {
                        switch (entry->win_key) {
                            case KC_ZHCK: 
                                unregister_code(KC_LCTL);
                                unregister_code(KC_LALT);
                                unregister_code(KC_TAB);
                                break;
                            case KC_MCF:
                                unregister_code(KC_LWIN);
                                unregister_code(KC_H);
                                break;
                            default:
                                unregister_code(entry->win_key);
                                break;
                        }
                    }
                }
                return false;
            }
        }
    }

    switch (keycode) {
        case QK_GESC: {
            static bool grave_esc_was_shifted = false;
            if (record->event.pressed) {
                grave_esc_was_shifted = shifted;
                register_code16(shifted ? KC_GRAVE : KC_ESCAPE);
            } else {
                unregister_code16(grave_esc_was_shifted ? KC_GRAVE : KC_ESCAPE);
            }
            return false;   
        } break;
        case KC_LSFT:
        case KC_RSFT: {
            shifted = record->event.pressed;
            return true;
        } break;
        case KJ_ESC: {
			if (record->event.pressed) {
				confinfo.kj_esc_grv = !confinfo.kj_esc_grv;
				eeconfig_confinfo_update();	
			}
			return false;
		}
		case KC_ESC: {
			if (!confinfo.kj_esc_grv) { 
				if (record->event.pressed) {
					register_code16(KC_ESC);
				} else {
					unregister_code16(KC_ESC);
				}
			} else {
				if (record->event.pressed) {
					register_code16(KC_GRV);
				} else {
					unregister_code16(KC_GRV);
				}
			}
			
			return false;
		}
        case KC_FTOG:{
            if (record->event.pressed) {
                confinfo.kj_cut_f_layer = !confinfo.kj_cut_f_layer;
                eeconfig_confinfo_update();
            }
            return false;
            break;
        }
        case NK_TOGG: {
            if (record->event.pressed) {
                rgb_matrix_blink_set_color(RGB_MATRIX_BLINK_INDEX_ALL, WIITE_B, 0x00, 0x00);
                rgb_matrix_blink_set_times(RGB_MATRIX_BLINK_INDEX_ALL, 1);
                rgb_matrix_blink_set(RGB_MATRIX_BLINK_INDEX_ALL);
            }
        } break;
        case KC_CUT:
        case KC_COPY:
        case KC_PASTE:
        case KC_FIND: {
            uint16_t combo = (keycode == KC_CUT) ? KC_X :
                             (keycode == KC_COPY) ? KC_C :
                             (keycode == KC_PASTE) ? KC_V : KC_F;
            if (record->event.pressed) {
                register_code16(KC_LCTL);
                register_code16(combo);
            } else {
                unregister_code16(KC_LCTL);
                unregister_code16(combo);
            }
            return false;
        }
        case QK_BOOT: {
            if (record->event.pressed) {
                rgb_matrix_disable_noeeprom();
                gpio_write_pin_low(LED_POWER_EN_PIN);
                kj_reset_flag = true;
                kj_reset_time = timer_read32();
                return false;
            }
        } break;
        case KC_TEST: {
            if (record->event.pressed) {
                test_white_light_flag = true;
            }
            return false;
        } break;
        case KC_RWCK: { 
            if (record->event.pressed) {
                register_code(KC_LALT);
                register_code(KC_TAB);
            } else {
                unregister_code(KC_LALT);
                unregister_code(KC_TAB);
            }
            return true;
        } break;
        case KC_YYIN: { 
            if (record->event.pressed) {
                register_code(KC_LCMD);
                register_code(KC_H);
            } else {
                unregister_code(KC_LCMD);
                unregister_code(KC_H);
            }
            return true;
        } break;
        case KC_DESK: { 
            if (record->event.pressed) {
                register_code(KC_LCMD);
                register_code(KC_D);
            } else {
                unregister_code(KC_LCMD);
                unregister_code(KC_D);
            }
            return true;
        } break;
        case RM_SPDU: {
            if (record->event.pressed) {
                if (rgb_matrix_get_speed() >= (55 + RGB_MATRIX_SPD_STEP * 4)) {
                    ind_set_blink(ind_state_blink3);
                }
            }
        } break;
        case RM_SPDD: {
            if (record->event.pressed) {
                if (rgb_matrix_get_speed() <= (55 + RGB_MATRIX_SPD_STEP*1)) {
                    ind_set_blink(ind_state_blink3);
                    rgb_matrix_set_speed(55 + (RGB_MATRIX_SPD_STEP*0));
                    return false;
                }
            }
        } break;
        case RM_VALU: {
            if (record->event.pressed) {
                if (rgb_matrix_get_val() >= (RGB_MATRIX_MAXIMUM_BRIGHTNESS - RGB_MATRIX_VAL_STEP)) {
                    ind_set_blink(ind_state_blink3);
                } 
            }
        } break;
        case RM_VALD: {
            if (record->event.pressed) {
                if (rgb_matrix_get_val() <= RGB_MATRIX_VAL_STEP) {
                    ind_set_blink(ind_state_blink3);
                    if (!keymap_config.no_gui && !host_keyboard_led_state().caps_lock) {
                        if (rgb_matrix_get_val() != 0) {
                            for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
                                rgb_matrix_set_color(i, 0, 0, 0);
                            }
                        }
                    } 
                } 
            }
        } break;
        case EE_CLR: {
            if (record->event.pressed) {
                ee_clr_timer = timer_read32();
            } else {
                ee_clr_timer = 0;
            }
            return false;
        } break;
        case TO(_BL): {
            if (record->event.pressed) {
                if (keymap_is_mac_system()) {
                    set_single_persistent_default_layer(_BL);
                    layer_move(0);
                }
            }
            return false;
        } break;
        case TO(_MBL): {
            if (record->event.pressed) {
                if (!keymap_is_mac_system()) {
                    set_single_persistent_default_layer(_MBL);
                    layer_move(0);
                }
            }
            return false;
        } break;       
#ifdef RGBLIGHT_ENABLE
        case RL_MOD: {
            if (record->event.pressed) {
                im_rgblight_increase(confinfo.rgb_ligth_mode);
                eeconfig_confinfo_update();
            }
            return false;
        } break;
        case RL_MOD1:{ 
            if (record->event.pressed) {
                 confinfo.kj_rgblight_mode ++;
                if (confinfo.kj_rgblight_mode > 3) {
                    confinfo.kj_rgblight_mode = 0;
                }
                eeconfig_confinfo_update();
            }
            return false;
        }break;
#endif
        case RM_NEXT: {
            if (record->event.pressed) {
                record_rgbmatrix_increase(&(confinfo.record_last_mode));
                eeconfig_confinfo_update();
            }
            return false;
        } break;
        case RM_HUED: {
            if (record->event.pressed) {
                record_color_hsv(false);
            }
            return false;
        } break;
        case RM_HUEU: {
            if (record->event.pressed) {
                record_color_hsv(true);
            }
            return false;
        } break;
        case KC_LCMD: {
            if (keymap_is_mac_system()) {
                if (keymap_config.no_gui) {
                    if (record->event.pressed) {
                        register_code16(KC_LCMD);
                    } else {
                        unregister_code16(KC_LCMD);
                    }
                    return false;
                }
            }
            return true;
        } break;
        case KC_RCMD: {
            if (keymap_is_mac_system()) {
                if (keymap_config.no_gui) {
                    if (record->event.pressed) {
                        register_code16(KC_RCMD);
                    } else {
                        unregister_code16(KC_RCMD);
                    }
                }
            }
            return true;
        } break;
        default:
            break;
    }

    return true;
}

bool kj_reset_settings_user(void) {
    rgb_matrix_blink_set_color(RGB_MATRIX_BLINK_INDEX_ALL, WIITE_B, WIITE_B, WIITE_B);
    rgb_matrix_blink_set_interval_times(RGB_MATRIX_BLINK_INDEX_ALL, 250, 3);
    rgb_matrix_blink_set(RGB_MATRIX_BLINK_INDEX_ALL);

    return true;
}

void kj_blink_rgb_matrix(uint8_t r, uint8_t g, uint8_t b) {
    int i;
    for(i = 0;i < RGB_MATRIX_LED_COUNT;i++){
        rgb_matrix_set_color(i, r,g,b);
    }
}

void housekeeping_task_user(void) { 

    if (kj_reset_flag) {
        if (timer_elapsed32(kj_reset_time) > 100) {
            kj_reset_time = timer_read32();
            eeconfig_disable();
            bootloader_jump();
        }
    }
}

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {

#ifdef RGBLIGHT_ENABLE
    if (rgb_matrix_indicators_advanced_rgblight(led_min, led_max) != true) {
        return false;
    }

    extern LED_TYPE rgb_matrix_ws2812_array[RGB_MATRIX_LED_COUNT];
    const uint8_t mirror_map[][2] = {
        {75, 82}, {74, 83}, {73, 84}, {72, 85}, 
    };

    for (uint8_t i = 0; i < ARRAY_SIZE(mirror_map); i++) {
        uint8_t src = mirror_map[i][0];
        uint8_t dst = mirror_map[i][1];
        uint8_t r = rgb_matrix_ws2812_array[src].r;
        uint8_t g = rgb_matrix_ws2812_array[src].g;
        uint8_t b = rgb_matrix_ws2812_array[src].b;
        rgb_matrix_set_color(dst, r, g, b);
    }

    kj_mode_rgblight_1(confinfo.kj_rgblight_mode);
#endif

    if (ee_clr_timer && timer_elapsed32(ee_clr_timer) > 3000) {
        kj_reset_settings();
        ee_clr_timer = 0;
    }

    if (host_keyboard_led_state().caps_lock){
        
    } else {
        
    }

    if (host_keyboard_led_state().num_lock){
        
    } 

    if (host_keyboard_led_state().scroll_lock){
        
    }

    if (!keymap_is_mac_system() && keymap_config.no_gui) {
        rgb_matrix_set_color(KJ_RGB_INDEX_WIN_LOCK,RGB_WHITE);
    } 

    rgb_matrix_blink_task(led_min, led_max);
    return true;
}

void kj_reset_settings(void) {
    eeconfig_init();
    
#ifdef RGBLIGHT_ENABLE
    extern void rgblight_init(void);
    is_rgblight_initialized = false;
    rgblight_init();
    eeconfig_update_rgblight_default();
    rgblight_enable();
#endif

    eeconfig_update_rgb_matrix_default();
    eeconfig_read_keymap(&keymap_config); 

    if (kj_reset_settings_user() != true) {
        return;
    }

    keyboard_post_init_kb();
}
