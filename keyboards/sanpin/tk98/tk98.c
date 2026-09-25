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

typedef enum {
    kj_win = 0,
    kj_mac,
} system_t;

typedef union {
    uint32_t raw;
    struct {
        uint8_t record_channel : 2;
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

void kj_reset_settings(void);
// void rgb_matrix_start_rec(void);

static uint32_t ee_clr_timer  = 0;
static uint32_t sys_win_timer = 0;
static uint32_t sys_mac_timer = 0;
static uint32_t kj_reset_time = 0;
bool test_white_light_flag   = false;
bool kj_reset_flag           = false;
static bool shifted          = false;
system_t system_status_flag;
bool no_record_fg;
uint32_t rec_time;

void ind_indicators_hook(uint8_t index);
void nkr_indicators_hook(uint8_t index);
blink_rgb_t blink_rgbs[RGB_MATRIX_BLINK_COUNT] = {
    {.index = KJ_RGB_BLINK_INDEX_VAI, .interval = 250, .times = 3, .color = {.r = 0x00, .g = 0x00, .b = 0x00}, .blink_cb = NULL},
    {.index = KJ_RGB_BLINK_INDEX_VAD, .interval = 250, .times = 3, .color = {.r = 0x00, .g = 0x00, .b = 0x00}, .blink_cb = NULL},
    {.index = KJ_RGB_BLINK_INDEX_SPI, .interval = 250, .times = 3, .color = {.r = 0x00, .g = 0x00, .b = 0x00}, .blink_cb = NULL},
    {.index = KJ_RGB_BLINK_INDEX_SPD, .interval = 250, .times = 3, .color = {.r = 0x00, .g = 0x00, .b = 0x00}, .blink_cb = NULL},
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
                    if (!no_record_fg) return false;

                    if (!blink_rgb->flip) {  
                        // rgb_matrix_set_color(KJ_RGB_BLINK_INDEX_REC, blink_rgb->color.r, blink_rgb->color.g, blink_rgb->color.b);
                    } 
                } break;
                case ind_state_exec: {
                    if (rgbrec_is_started()) {
                        return false;
                    }

                    if (blink_rgb->flip) {
                            rgb_matrix_set_color(KJ_RGB_INDEX_CAPS, WIITE_B, WIITE_B, WIITE_B);
                            rgb_matrix_set_color(KJ_RGB_INDEX_NUM, WIITE_B, WIITE_B, WIITE_B);
                            rgb_matrix_set_color(KJ_RGB_INDEX_WIN_LOCK, WIITE_B, WIITE_B, WIITE_B);
                    } else {
                            rgb_matrix_set_color(KJ_RGB_INDEX_CAPS, 0x00, 0x00, 0x00);
                            rgb_matrix_set_color(KJ_RGB_INDEX_NUM, 0x00, 0x00, 0x00);
                            rgb_matrix_set_color(KJ_RGB_INDEX_WIN_LOCK, 0x00, 0x00, 0x00);
                    }
                } break;
                default: break;
            }
            return false;
        } break;
#undef KJ_RGB_BLINK_INDEX_REC
#ifdef KJ_RGB_BLINK_INDEX_REC
        case KJ_RGB_BLINK_INDEX_REC: {
        } break;
#endif
        default: { 
            if (test_white_light_flag) {
                return false;
            }

            if (rgbrec_is_started()) {
                return false;
            }
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

    confinfo.record_channel    = 0;
    confinfo.record_last_mode  = 0x00;
    confinfo.sleep_timeout     = 7;
    confinfo.rgb_ligth_mode    = 0;
    confinfo.kj_rgblight_mode  = 0;
    confinfo.kj_cut_f_layer    = false;
    confinfo.kj_esc_grv        = false;

    if (system_status_flag == kj_mac) { 
        set_single_persistent_default_layer(_MBL);               
        layer_move(0); 
    }

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
    // keymap_config.no_gui = 0;
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

#ifdef KJ_RGB_BLINK_INDEX_REC
    rgb_matrix_blink_set_interval_times(KJ_RGB_BLINK_INDEX_REC, 200, 0xFF);
    rgb_matrix_blink_set(KJ_RGB_BLINK_INDEX_REC);
#endif

    if (!keymap_is_mac_system()) { 
        system_status_flag = kj_win;
    } else {
        system_status_flag = kj_mac;
    }

    keyboard_post_init_user();
    rgbrec_init(confinfo.record_channel);
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        case MO(_FL): {
            if (!record->event.pressed && rgbrec_is_started()) {
                if (no_record_fg == true) {
                    no_record_fg = false;
                    rgbrec_register_record(keycode, record);
                }
                no_record_fg = true;
            }
            break;
        }
        case RP_END:
        case RP_P0:
        case RP_P1:
        case RP_P2:
        case RM_NEXT:
            break;
        default: {
            if (rgbrec_is_started()) {
                if (!IS_QK_MOMENTARY(keycode) && record->event.pressed) {
                    rgbrec_register_record(keycode, record);

                    return false;
                }
            }
        } break;
    }

    if (rgbrec_is_started() && (!(keycode == RP_P0 || keycode == RP_P1 || keycode == RP_P2 || keycode == RP_END 
    || keycode == RM_NEXT || keycode == MO(_FL)))) {

        return false;
    }

    return true;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {

    if (process_record_user(keycode, record) != true) {
        return false;
    }

    if (test_white_light_flag && record->event.pressed && keycode != KC_SPC) {
        test_white_light_flag = false;
        rgb_matrix_set_color_all(0x00, 0x00, 0x00);
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
        case KC_RWKZ: { 
            if (record->event.pressed && !rgbrec_is_started()) {
                register_code(KC_LCMD);
                register_code(KC_SPC);
            } else {
                unregister_code(KC_LCMD);
                unregister_code(KC_SPC);
            }
            return true;
        } break;
        case KC_CKXS:{ 
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_UP);
            } else {
                unregister_code(KC_LCTL);
                unregister_code(KC_UP);
            }
            return false;
        } break;
        case KC_YYIN: { 
            if (record->event.pressed && !rgbrec_is_started()) {
                register_code(KC_LCMD);
                register_code(KC_H);
            } else {
                unregister_code(KC_LCMD);
                unregister_code(KC_H);
            }
            return true;
        } break;
        case KC_DESK: { 
            if (record->event.pressed && !rgbrec_is_started()) {
                register_code(KC_LCMD);
                register_code(KC_D);
            } else {
                unregister_code(KC_LCMD);
                unregister_code(KC_D);
            }
            return true;
        } break;
        case RM_SPDU: {
            if (rgbrec_is_started()) return false;
            if (record->event.pressed) {
                if (rgb_matrix_get_speed() >= (55 + RGB_MATRIX_SPD_STEP * 4)) {
                    rgb_matrix_blink_set_interval_times(KJ_RGB_BLINK_INDEX_SPI, 250, 3);
                    rgb_matrix_blink_set(KJ_RGB_BLINK_INDEX_SPI);
                }
            }
        } break;
        case RM_SPDD: {
            if (rgbrec_is_started()) return false;
            if (record->event.pressed) {
                if (rgb_matrix_get_speed() <= (55 + RGB_MATRIX_SPD_STEP*1)) {
                    rgb_matrix_blink_set_interval_times(KJ_RGB_BLINK_INDEX_SPD, 250, 3);
                    rgb_matrix_blink_set(KJ_RGB_BLINK_INDEX_SPD);
                    rgb_matrix_set_speed(55 + (RGB_MATRIX_SPD_STEP*0));
                    return false;
                }
            }
        } break;
        case RM_VALU: {
            if (rgbrec_is_started()) return false;
            if (record->event.pressed) {
                if (rgb_matrix_get_val() >= (RGB_MATRIX_MAXIMUM_BRIGHTNESS - RGB_MATRIX_VAL_STEP)) {
                    rgb_matrix_blink_set_interval_times(KJ_RGB_BLINK_INDEX_VAI, 250, 3);
                    rgb_matrix_blink_set(KJ_RGB_BLINK_INDEX_VAI);
                } 
            }
        } break;
        case RM_VALD: {
            if (rgbrec_is_started()) return false;
            if (record->event.pressed) {
                if (rgb_matrix_get_val() <= RGB_MATRIX_VAL_STEP) {
                    rgb_matrix_blink_set_interval_times(KJ_RGB_BLINK_INDEX_VAD, 250, 3);
                    rgb_matrix_blink_set(KJ_RGB_BLINK_INDEX_VAD);
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
                sys_win_timer = timer_read32();
            } else {
                sys_win_timer = 0;
            }
            return false;
        } break;
        case TO(_MBL): {
            if (record->event.pressed) {
                sys_mac_timer = timer_read32();
            } else {
                sys_mac_timer = 0;
            }
            return false;
        } break;       
        case RP_P0: {
            if (record->event.pressed) {
                rgbrec_end(confinfo.record_channel,false);
                confinfo.record_channel = 0;
                rgbrec_read_current_channel(confinfo.record_channel);
                eeconfig_confinfo_update();
                rgbrec_show(confinfo.record_channel);
                ind_set_blink(ind_state_none);
            }
            return false;
        } break;
        case RP_P1: {
            if (record->event.pressed) {
                rgbrec_end(confinfo.record_channel,false);
                confinfo.record_channel = 1;
                rgbrec_read_current_channel(confinfo.record_channel);
                eeconfig_confinfo_update();
                rgbrec_show(confinfo.record_channel);
                ind_set_blink(ind_state_none);
            }
            return false;
        } break;
        case RP_P2: {
            if (record->event.pressed) {
                rgbrec_end(confinfo.record_channel,false);
                confinfo.record_channel = 2;
                rgbrec_read_current_channel(confinfo.record_channel);
                eeconfig_confinfo_update();
                rgbrec_show(confinfo.record_channel);
                ind_set_blink(ind_state_none);
            }
            return false;
        } break;
        case RP_END: {
            if (record->event.pressed) {
                if (rgb_matrix_get_mode() != RGB_MATRIX_CUSTOM_RGBR_PLAY) {

                    return false;
                }
                if (!rgbrec_is_started()) {
                    rgbrec_start(confinfo.record_channel);
                    no_record_fg = false;
                    rec_time     = timer_read32();
                    rgbrec_set_close_all(HSV_BLACK);
                    ind_set_blink(ind_state_blinkon);
                } else {
                    rec_time = 0;
                    rgbrec_end(confinfo.record_channel,true);
                    ind_set_blink(ind_state_none);
                }
                eeconfig_confinfo_update();
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
                if (rgb_matrix_get_mode() == RGB_MATRIX_CUSTOM_RGBR_PLAY) {
                    if (rgbrec_is_started()) {
                        rgbrec_read_current_channel(confinfo.record_channel);
                        rgbrec_end(confinfo.record_channel,false);
                        no_record_fg = false;
                    }
                    if (confinfo.record_last_mode != 0xFF)
                        rgb_matrix_mode(confinfo.record_last_mode);
                    else
                        rgb_matrix_mode(RGB_MATRIX_DEFAULT_MODE);
                    eeconfig_confinfo_update();
                    return false;
                }
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
                if (keymap_config.no_gui && !rgbrec_is_started()) {
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
                if (keymap_config.no_gui && !rgbrec_is_started()) {
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

void rgb_matrix_start_rec(void) {
    static bool rec_filp;
    if (rgbrec_is_started()) {
        if (!rec_time || timer_elapsed32(rec_time) > 250) {
            rec_time = timer_read32();
            rec_filp = !rec_filp;
        }
        if (rec_filp) {
            #ifdef KJ_RGB_BLINK_INDEX_REC
                rgb_matrix_set_color(KJ_RGB_BLINK_INDEX_REC, WIITE_B, WIITE_B, WIITE_B);
            #endif
        } else {
            #ifdef KJ_RGB_BLINK_INDEX_REC
                rgb_matrix_set_color(KJ_RGB_BLINK_INDEX_REC, 0x00, 0x00, 0x00);
            #endif
        }
    } else {
        rec_time = 0;
        rec_filp = false;
    }
}

void kj_blink_rgb_matrix(uint8_t r, uint8_t g, uint8_t b) {
    int i;
    for(i = 0;i < RGB_MATRIX_LED_COUNT;i++){
        rgb_matrix_set_color(i, r,g,b);
    }
}

void housekeeping_task_user(void) { // loop

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
#endif

    if (ee_clr_timer && timer_elapsed32(ee_clr_timer) > 3000) {
        kj_reset_settings();
        ee_clr_timer = 0;
    }

    if (sys_mac_timer && timer_elapsed32(sys_mac_timer) > 3000) {
        ind_set_blink(ind_state_blink3);
        system_status_flag = kj_mac;
        if (!keymap_is_mac_system()) {
            set_single_persistent_default_layer(_MBL);
            layer_move(0);
        }
        sys_mac_timer = 0;
    }

    if (sys_win_timer && timer_elapsed32(sys_win_timer) > 3000) {
        ind_set_blink(ind_state_blink3);
        system_status_flag = kj_win;
        if (keymap_is_mac_system()) {
            set_single_persistent_default_layer(_BL);
            layer_move(0);
        }
        sys_win_timer = 0;
    }

    if (!rgbrec_is_started()) {
        if (host_keyboard_led_state().caps_lock){
            rgb_matrix_set_color(KJ_RGB_INDEX_CAPS,RGB_WHITE);
        } else {
            rgb_matrix_set_color(KJ_RGB_INDEX_CAPS,RGB_BLACK);
        }

        if (host_keyboard_led_state().num_lock){
            rgb_matrix_set_color(KJ_RGB_INDEX_NUM,RGB_WHITE);
        } else {
            rgb_matrix_set_color(KJ_RGB_INDEX_NUM,RGB_BLACK);
        }

        if (host_keyboard_led_state().scroll_lock){
            
        }

        if (!rgbrec_is_started() && !keymap_is_mac_system() && keymap_config.no_gui) {
            rgb_matrix_set_color(KJ_RGB_INDEX_WIN_LOCK,RGB_WHITE);
        } else {
            rgb_matrix_set_color(KJ_RGB_INDEX_WIN_LOCK,RGB_BLACK);
        }
    }
    
    // rgb_matrix_start_rec();

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
