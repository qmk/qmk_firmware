// Copyright 2024 Su (@isuua)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "raw_hid.h"
#include "usb_util.h"
#include QMK_KEYBOARD_H

#include "hal.h"
#include "debounce.h"

extern USBDriver USBD1;

#ifdef MATRIX_MASKED
const matrix_row_t matrix_mask[MATRIX_ROWS] = {
    0x63FFF, 0x7FFFF, 0x7FFFF, 0x7FFFF, 0x7FFFF, 0x7FFFF,
};
#endif

#define FACTORY_DEFAULT_RGB_MODE RGB_MATRIX_JELLYBEAN_RAINDROPS
#define FACTORY_DEFAULT_RGBLIGHT_MODE 9
#define CUSTOM_RGB_MODE 45
#define KEY_NUM 98
#define STARTUP_INIT_DELAY_MS 500
static bool light_test_mode = false;
static uint8_t current_debounce           = 5;

static bool reset_triggered               = false;
static uint32_t reset_timer               = 0;

uint8_t encoder_layer                     = 0;
static uint8_t last_dip_state             = 0;
uint8_t dip_state                         = 0;
static uint8_t local_dip_state            = 0;

static bool mac_mode                      = false;
static bool m_key_pressed                 = false;
static bool win_lock                      = false;
static bool caps_lock                     = false;
static bool num_lock                      = false;
static bool mo1_pressed                   = false;
static uint16_t hold_counter              = 0;
static bool encoder_light_enabled         = true;
static bool pdot_pressed                  = false;

static bool flash_active                  = false;
static uint32_t flash_start               = 0;
static bool mac_switch_triggered          = false;

static bool custom_mode_pending           = false;
static uint32_t custom_mode_timer         = 0;


typedef struct {
    bool fn_pressed;
    bool m_pressed;
    uint32_t fn_m_timer;
    bool mac_mode;
    bool mac_mode_changed;
} key_state_t;

static key_state_t key_state = {0};

typedef enum {
    ENCODER_MODE_VOLUME = 0,
    ENCODER_MODE_BRIGHTNESS = 1,
    ENCODER_MODE_PAGE = 2,
    ENCODER_MODE_DEFAULT = ENCODER_MODE_VOLUME
} encoder_mode_t;

encoder_mode_t current_encoder_mode = ENCODER_MODE_DEFAULT;

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} user_color_t;


void custom_color_set_enabled(bool enabled);
void custom_color_init(void);
bool custom_color_is_enabled(void);
bool custom_color_has_valid_data(void);
bool custom_color_flush_task(void);
const user_color_t *custom_color_get_table(void);
void custom_color_activate_and_persist(void);
void custom_color_clear_runtime(void);
#ifdef VIA_ENABLE
static void reset_custom_color_and_restore_default_mode(void);
#endif
static void clear_encoder_ring_light(void);
static bool usb_enumerated = false;
// Small settings are packed into the 32-bit eeconfig_user() word.
typedef union {
    uint32_t raw;
    struct {
        uint8_t mac_mode    : 1;
        uint8_t flag        : 1;
        uint8_t devs        : 3;
        uint8_t custom_mode : 1;
        uint8_t win_lock    : 1;
        uint8_t debounce    : 6;
    };
} user_config_t;

static user_config_t user_config;

typedef union {
    uint32_t raw;
    struct {
        uint8_t flag : 1;
        uint8_t devs : 3;
    };
} confinfo_t;

static confinfo_t confinfo;



void eeconfig_userconfig_update(void) {
    eeconfig_update_user(user_config.raw);
}

uint32_t eeconfig_userconfig_read(void) {
    return eeconfig_read_user();
}

void eeconfig_confinfo_update(uint32_t raw) {
    confinfo.raw       = raw;
    user_config.flag   = confinfo.flag;
    user_config.devs   = confinfo.devs;
    eeconfig_userconfig_update();
}

uint32_t eeconfig_confinfo_read(void) {
    user_config.raw    = eeconfig_userconfig_read();
    confinfo.flag      = user_config.flag;
    confinfo.devs      = user_config.devs;
    return confinfo.raw;
}

void eeconfig_confinfo_default(void) {
    user_config.raw         = 0;
    user_config.flag        = true;
    user_config.mac_mode    = false;
    user_config.custom_mode = false;
    user_config.win_lock    = false;
    user_config.debounce    = 5;

    eeconfig_userconfig_update();

    confinfo.flag = user_config.flag;
    confinfo.devs = user_config.devs;

    // 首次初始化时设置默认灯效
    rgb_matrix_mode(FACTORY_DEFAULT_RGB_MODE);
    rgblight_mode_noeeprom(FACTORY_DEFAULT_RGBLIGHT_MODE);
}

void eeconfig_confinfo_init(void) {
    user_config.raw = eeconfig_userconfig_read();
    if (!user_config.raw) {
        eeconfig_confinfo_default();
    }

    confinfo.flag      = user_config.flag;
    confinfo.devs      = user_config.devs;
    mac_mode           = user_config.mac_mode;
    key_state.mac_mode = mac_mode;
    win_lock           = user_config.win_lock;
    current_debounce   = user_config.debounce ? user_config.debounce : 5;
}

void keyboard_post_init_kb(void) {
    eeconfig_confinfo_init();
    custom_color_init();

    uint8_t saved_mode = rgb_matrix_get_mode();
    bool should_restore_custom = (saved_mode == CUSTOM_RGB_MODE) && user_config.custom_mode && custom_color_has_valid_data();

    if (should_restore_custom) {
        custom_color_set_enabled(true);
        custom_mode_pending = false;
        rgb_matrix_mode(CUSTOM_RGB_MODE);
        eeconfig_update_rgblight_current();
        dprintf("[BOOT] restore custom rgb mode=%u\n", CUSTOM_RGB_MODE);
    } else {
        bool need_clear_custom_mode = user_config.custom_mode && !custom_color_has_valid_data();
        custom_color_set_enabled(false);
        custom_mode_pending = false;

        if (need_clear_custom_mode) {
            user_config.custom_mode = 0;
            eeconfig_userconfig_update();
        }

        if (saved_mode == CUSTOM_RGB_MODE) {
            rgb_matrix_mode(FACTORY_DEFAULT_RGB_MODE);
            eeconfig_update_rgblight_current();
        } else {
            rgb_matrix_mode(saved_mode ? saved_mode : FACTORY_DEFAULT_RGB_MODE);
        }
    }

    // 让呼吸灯从较亮的相位开始，避免上电时从灭到极暗的跳变导致闪烁
    extern rgblight_config_t rgblight_config;
    extern animation_status_t animation_status;
    if (rgblight_config.enable) {
        uint8_t mode = rgblight_config.mode;
        if (mode >= RGBLIGHT_MODE_BREATHING && mode <= (RGBLIGHT_MODE_BREATHING + 3)) {
            // 跳过呼吸周期的最低谷（val≈34），从较亮位置开始
            animation_status.restart = false;
            animation_status.pos     = 32;
            animation_status.last_timer = 0;
            rgblight_effect_breathing(&animation_status);
        }
    }

#ifdef LED_POWER_EN_PIN
    gpio_set_pin_output(LED_POWER_EN_PIN);
    gpio_write_pin_low(LED_POWER_EN_PIN);
#endif

#ifdef USB_POWER_EN_PIN
    gpio_write_pin_low(USB_POWER_EN_PIN);
    gpio_set_pin_output(USB_POWER_EN_PIN);
#endif

    keyboard_post_init_user();
}

void suspend_power_down_kb(void) {
#ifdef LED_POWER_EN_PIN
    gpio_write_pin_low(LED_POWER_EN_PIN);
#endif

#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_suspend_state(true);
#endif

    gpio_set_pin_output(C14);
    gpio_write_pin_low(C14);
    gpio_set_pin_output(C15);
    gpio_write_pin_low(C15);

    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    bool usb_active = usb_connected_state();

    // 恢复编码器引脚为输入上拉
    gpio_set_pin_input_high(C14);
    gpio_set_pin_input_high(C15);

#ifdef LED_POWER_EN_PIN
    gpio_write_pin(LED_POWER_EN_PIN, usb_active);
#endif

#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_suspend_state(!usb_active);
#endif

    suspend_wakeup_init_user();
}



extern bool send_report(uint8_t endpoint, const void *data, int len);

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }

    // 本地追踪 Caps/Num 锁定状态，避免等 USB 主机回复延迟
    if (keycode == KC_CAPS && record->event.pressed) {
        caps_lock = !caps_lock;
        dprintf("CAPS toggled: %s\n", caps_lock ? "ON" : "OFF");
    }
    if (keycode == KC_NUM && record->event.pressed) {
        num_lock = !num_lock;
        dprintf("NUM  toggled: %s\n", num_lock ? "ON" : "OFF");
    }

    if (keycode == KC_R && key_state.fn_pressed) {
        if (record->event.pressed) {
            if (!reset_triggered) {
                reset_triggered = true;
                reset_timer = timer_read32();
            }
        } else {
            if (reset_triggered && timer_elapsed32(reset_timer) < 3000) {
                reset_triggered = false;
            }
        }
        return false;
    }

    if (keycode == MO(1)) {
        key_state.fn_pressed = record->event.pressed;
        mo1_pressed = record->event.pressed;
        if (record->event.pressed) {
            key_state.fn_m_timer = timer_read32();
        }
    }

    if (keycode == KC_PDOT) {
        pdot_pressed = record->event.pressed;
    }

    if ((keycode == MO(1) || keycode == KC_PDOT) && key_state.fn_pressed && pdot_pressed && record->event.pressed) {
        encoder_light_enabled = !encoder_light_enabled;
        return false;
    }

    if (key_state.fn_pressed && record->event.pressed) {
        switch (keycode) {
            case KC_F1:
                current_encoder_mode = ENCODER_MODE_VOLUME;
                return false;
            case KC_F2:
                current_encoder_mode = ENCODER_MODE_PAGE;
                return false;
            case KC_F3:
                current_encoder_mode = ENCODER_MODE_BRIGHTNESS;
                return false;
        }
    }

if (keycode == KC_LGUI || keycode == KC_RGUI) {
    if (!key_state.mac_mode && mo1_pressed && record->event.pressed) {
        win_lock = !win_lock;
        user_config.win_lock = win_lock ? 1 : 0;
        eeconfig_userconfig_update();
        return false;
    }

    if (!key_state.mac_mode && win_lock && record->event.pressed) {
        return false;
    }


}

    if (keycode == KC_M) {
        key_state.m_pressed = record->event.pressed;

        if (key_state.fn_pressed) {
            if (record->event.pressed) {
                mac_switch_triggered = false;
                dprintf("FN+M pressed, timer started\n");
            }
            return false;
        }

        return true;
    }

    if (keycode == KC_COPY) {
        if (record->event.pressed) {
            register_code(KC_LCTL);
            tap_code(KC_C);
            unregister_code(KC_LCTL);
        }
        return false;
    } else if (keycode == KC_PASTE || keycode == KC_PSTE) {
        if (record->event.pressed) {
            register_code(KC_LCTL);
            tap_code(KC_V);
            unregister_code(KC_LCTL);
        }
        return false;
    } else if (keycode == KC_CUT) {
        if (record->event.pressed) {
            register_code(KC_LCTL);
            tap_code(KC_X);
            unregister_code(KC_LCTL);
        }
        return false;
    }

    if (key_state.mac_mode) {
        switch (keycode) {
            case KC_LGUI:
                if (record->event.pressed) register_code(KC_LALT);
                else unregister_code(KC_LALT);
                return false;
            case KC_LALT:
                if (record->event.pressed) register_code(KC_LGUI);
                else unregister_code(KC_LGUI);
                return false;
            case KC_RGUI:
                if (record->event.pressed) register_code(KC_RALT);
                else unregister_code(KC_RALT);
                return false;
            case KC_RALT:
                if (record->event.pressed) register_code(KC_RGUI);
                else unregister_code(KC_RGUI);
                return false;
        }
    }

    switch (keycode) {
        case UG_NEXT:
            if (record->event.pressed) {
                rgblight_step();
            }
            return false;

        case UG_PREV:
            if (record->event.pressed) {
                rgblight_step_reverse();
            }
            return false;

        case RM_HUEU:
            if (record->event.pressed) {
                rgb_matrix_increase_hue();
                eeconfig_update_rgblight_current();
            }
            return false;

        default:
            return true;
    }
}

/******编码器旋钮*******/
#ifdef ENCODER_ENABLE

typedef struct {
    bool active;
    uint32_t timer;
    bool direction;
    uint8_t pos;
    uint8_t circles;
    bool rotating;
} encoder_light_t;

static encoder_light_t encoder_light = {0};
extern const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2];

bool dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0:
            if (active) local_dip_state |= (0x01U << 0);
            else local_dip_state &= ~(0x01U << 0);
            break;
        case 1:
            if (active) local_dip_state |= (0x01U << 1);
            else local_dip_state &= ~(0x01U << 1);
            break;
        default:
            break;
    }

    dip_state = local_dip_state;

    if (local_dip_state != last_dip_state) {
        switch (local_dip_state) {
            case 0:
                encoder_layer = 2;
                break;
            case 1:
                encoder_layer = 0;
                break;
            case 2:
                encoder_layer = 1;
                break;
        }
        last_dip_state = local_dip_state;
    }

    return true;
}

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
        return false;
    }

    if (index == 0) {
        if (encoder_light_enabled) {
            encoder_light.active = true;
            encoder_light.timer = timer_read32();
            encoder_light.direction = clockwise;
            encoder_light.rotating = true;
        }

#ifdef ENCODER_MAP_ENABLE
        uint8_t target_layer = encoder_layer;
        uint16_t keycode = dynamic_keymap_get_encoder(target_layer, index, clockwise);

        if (keycode == KC_NO) {
            return false;
        }

        if (keycode == RM_VALD || keycode == RM_VALU) {
            if (clockwise) rgb_matrix_increase_val();
            else rgb_matrix_decrease_val();
            return false;
        }
        if (keycode == KC_VOLU || keycode == KC_VOLD) {
            tap_code16(keycode);

            return false;
        }

        if (keycode == KC_COPY) {
            register_code(KC_LCTL);
            tap_code(KC_C);
            unregister_code(KC_LCTL);
        } else if (keycode == KC_PASTE || keycode == KC_PSTE) {
            register_code(KC_LCTL);
            tap_code(KC_V);
            unregister_code(KC_LCTL);
        } else if (keycode == KC_CUT) {
            register_code(KC_LCTL);
            tap_code(KC_X);
            unregister_code(KC_LCTL);
        } else {
            tap_code16(keycode);
        }

        if (IS_QK_MACRO(keycode) || IS_RGB_KEYCODE(keycode) || IS_RGB_MATRIX_KEYCODE(keycode) ||
            IS_BACKLIGHT_KEYCODE(keycode) || IS_LED_MATRIX_KEYCODE(keycode) || IS_UNDERGLOW_KEYCODE(keycode)) {
            keyrecord_t record = {
                .event = {
                    .key = {.row = 0xFF, .col = 0xFF},
                    .pressed = true,
                    .time = timer_read()
                },
                .keycode = keycode
            };

            process_record_quantum(&record);
            wait_ms(ENCODER_MAP_KEY_DELAY);
            record.event.pressed = false;
            record.event.time = timer_read();
            process_record_quantum(&record);
        }
#endif
    }

    return false;
}
#endif


/******背光指示灯*******/
#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (rgb_matrix_get_suspend_state()) {
        return false;
    }
    if (light_test_mode) {
        for (uint8_t i = 0; i <= 106; i++) {
            rgb_matrix_set_color(i, 0xFF, 0xFF, 0xFF);
        }
        return true;
    }
       if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }

    if (rgb_matrix_get_mode() == CUSTOM_RGB_MODE) {
        if (rgb_matrix_is_enabled()) {
            const user_color_t *tbl = custom_color_get_table();
            for (uint8_t i = led_min; i < led_max && i < KEY_NUM; i++) {
                rgb_matrix_set_color(i, tbl[i].r, tbl[i].g, tbl[i].b);
            }
        } else {
            for (uint8_t i = led_min; i < led_max && i < KEY_NUM; i++) {
                rgb_matrix_set_color(i, 0, 0, 0);
            }
        }

        // NUM 指示灯
        if (host_keyboard_led_state().num_lock) {
            rgb_matrix_set_color(29, 0xFF, 0xFF, 0xFF);
        } else if (!rgb_matrix_is_enabled()) {
            rgb_matrix_set_color(29, 0, 0, 0);
        }
        // WIN 锁指示灯
        if (win_lock) {
            rgb_matrix_set_color(88, 0xFF, 0xFF, 0xFF);
        } else if (!rgb_matrix_is_enabled()) {
            rgb_matrix_set_color(88, 0, 0, 0);
        }
        // Caps Lock 指示灯
        if (host_keyboard_led_state().caps_lock) {
            rgb_matrix_set_color(52, 0xFF, 0xFF, 0xFF);
            for (uint8_t i = 98; i <= 106; i++) rgb_matrix_set_color(i, 0xFF, 0xFF, 0xFF);
        } else if (!rgb_matrix_is_enabled()) {
            rgb_matrix_set_color(52, 0, 0, 0);
        }
        return true;
    }

    if (mo1_pressed) {
        if (m_key_pressed) {
            hold_counter++;
            if (hold_counter > 188) {
                mac_mode = !mac_mode;
                hold_counter = 0;
            }
        } else {
            hold_counter = 0;
        }
    } else {
        hold_counter = 0;
    }


    bool host_caps = host_keyboard_led_state().caps_lock;
    bool host_num  = host_keyboard_led_state().num_lock;
    caps_lock = host_caps;
    num_lock  = host_num;
    uint8_t cur_mode = rgb_matrix_get_mode();
    bool slow_effect = (cur_mode == RGB_MATRIX_JELLYBEAN_RAINDROPS || cur_mode == RGB_MATRIX_RAINDROPS);

    static uint32_t off_color_88  = 0;
    static uint32_t off_color_29  = 0;
    static uint32_t off_color_52  = 0;
    static bool     first_init    = true;
    static bool     prev_caps_s   = false;
    static bool     prev_num_s    = false;
    static bool     prev_win_s    = false;

    if (first_init) {
        first_init = false;
        do { uint16_t r = timer_read(); hsv_t h = { (uint8_t)r, (uint8_t)(r >> 3) | 0x80, rgb_matrix_config.hsv.v }; rgb_t rg = hsv_to_rgb(h); off_color_88 = ((uint32_t)rg.r << 16) | ((uint32_t)rg.g << 8) | rg.b; } while(0);
        do { uint16_t r = timer_read(); hsv_t h = { (uint8_t)(r >> 8), (uint8_t)r | 0x80, rgb_matrix_config.hsv.v }; rgb_t rg = hsv_to_rgb(h); off_color_29 = ((uint32_t)rg.r << 16) | ((uint32_t)rg.g << 8) | rg.b; } while(0);
        do { uint16_t r = timer_read(); hsv_t h = { (uint8_t)(r >> 4), (uint8_t)(r >> 2) | 0x80, rgb_matrix_config.hsv.v }; rgb_t rg = hsv_to_rgb(h); off_color_52 = ((uint32_t)rg.r << 16) | ((uint32_t)rg.g << 8) | rg.b; } while(0);
        prev_caps_s = host_caps;
        prev_num_s  = host_num;
        prev_win_s  = win_lock;
    }

    #define GEN_OFF_COLOR(var, shift1, shift2) do { \
        uint16_t rnd = timer_read(); \
        hsv_t hsv = { (uint8_t)(rnd >> shift1), (uint8_t)(rnd >> shift2) | 0x80, rgb_matrix_config.hsv.v }; \
        rgb_t rgb = hsv_to_rgb(hsv); \
        var = ((uint32_t)rgb.r << 16) | ((uint32_t)rgb.g << 8) | rgb.b; \
    } while(0)

    if (prev_caps_s != host_caps) { prev_caps_s = host_caps; if (!host_caps && slow_effect && rgb_matrix_is_enabled()) { GEN_OFF_COLOR(off_color_52, 4, 2); } }
    if (prev_num_s  != host_num)  { prev_num_s  = host_num;  if (!host_num  && slow_effect && rgb_matrix_is_enabled()) { GEN_OFF_COLOR(off_color_29, 8, 0); } }
    if (prev_win_s  != win_lock)  { prev_win_s  = win_lock;  if (!win_lock  && slow_effect && rgb_matrix_is_enabled()) { GEN_OFF_COLOR(off_color_88, 0, 3); } }


    if (win_lock) {
        rgb_matrix_set_color(88, 0xFF, 0xFF, 0xFF);
    } else if (slow_effect) {
        rgb_matrix_set_color(88, rgb_matrix_is_enabled() ? ((off_color_88 >> 16) & 0xFF) : 0, rgb_matrix_is_enabled() ? ((off_color_88 >> 8) & 0xFF) : 0, rgb_matrix_is_enabled() ? (off_color_88 & 0xFF) : 0);
    } else if (!rgb_matrix_is_enabled()) {
        rgb_matrix_set_color(88, 0, 0, 0);
    }

    if (host_num) {
        rgb_matrix_set_color(29, 0xFF, 0xFF, 0xFF);
    } else if (slow_effect) {
        rgb_matrix_set_color(29, rgb_matrix_is_enabled() ? ((off_color_29 >> 16) & 0xFF) : 0, rgb_matrix_is_enabled() ? ((off_color_29 >> 8) & 0xFF) : 0, rgb_matrix_is_enabled() ? (off_color_29 & 0xFF) : 0);
    } else if (!rgb_matrix_is_enabled()) {
        rgb_matrix_set_color(29, 0, 0, 0);
    }


    if (host_caps && !(mo1_pressed && m_key_pressed)) {
        rgb_matrix_set_color(52, 0xFF, 0xFF, 0xFF);
        for (uint8_t i = 98; i <= 106; i++) rgb_matrix_set_color(i, 0xFF, 0xFF, 0xFF);
    } else if (host_caps && (mo1_pressed && m_key_pressed)) {
        rgb_matrix_set_color(52, 0x00, 0x00, 0x00);
        for (uint8_t i = 98; i <= 106; i++) rgb_matrix_set_color(i, 0x00, 0x00, 0x00);
    } else if (slow_effect) {
        rgb_matrix_set_color(52, rgb_matrix_is_enabled() ? ((off_color_52 >> 16) & 0xFF) : 0, rgb_matrix_is_enabled() ? ((off_color_52 >> 8) & 0xFF) : 0, rgb_matrix_is_enabled() ? (off_color_52 & 0xFF) : 0);
    } else if (!rgb_matrix_is_enabled()) {
        rgb_matrix_set_color(52, 0, 0, 0);
    }


    if (key_state.fn_pressed && key_state.m_pressed) {
        if (timer_elapsed32(key_state.fn_m_timer) >= 3000 && !mac_switch_triggered) {
            mac_mode = !mac_mode;
            key_state.mac_mode = mac_mode;
            user_config.mac_mode = mac_mode ? 1 : 0;

            win_lock = false;
            user_config.win_lock = 0;

            eeconfig_userconfig_update();


            mac_switch_triggered = true;
            flash_active = true;
            flash_start = timer_read32();

            for (uint8_t i = 98; i <= 106; i++) {
                rgb_matrix_set_color(i, 0xFF, 0xFF, 0xFF);
            }
        }
    }
    if ((!key_state.fn_pressed || !key_state.m_pressed) && mac_switch_triggered) {
        mac_switch_triggered = false;
    }

    if (encoder_light.active && encoder_light_enabled) {
        extern rgblight_config_t rgblight_config;
        uint8_t hue = rgblight_config.hue;
        uint8_t sat = rgblight_config.sat;
        uint8_t val = rgblight_config.val;
        if (val < 150) val = 200;

        for (uint8_t i = 98; i <= 106; i++) {
            rgb_matrix_set_color(i, 0, 0, 0);
        }

        uint32_t elapsed = timer_elapsed32(encoder_light.timer);

        if (elapsed >= 500) {
            encoder_light.active = false;
            encoder_light.rotating = false;
            for (uint8_t i = 98; i <= 106; i++) {
                rgb_matrix_set_color(i, 0, 0, 0);
            }
        } else if (encoder_light.rotating) {
            uint32_t angle = (elapsed * 720) / 500;

            if (encoder_light.direction) {
                encoder_light.pos = (9 - ((angle / 40) % 9)) % 9;
            } else {
                encoder_light.pos = (angle / 40) % 9;
            }

            for (uint8_t j = 0; j < 3; j++) {
                int8_t led_pos;

                if (encoder_light.direction) led_pos = encoder_light.pos - j;
                else led_pos = encoder_light.pos + j;

                if (led_pos < 0) led_pos += 9;
                if (led_pos >= 9) led_pos -= 9;

                uint8_t led_index = 98 + led_pos;
                uint8_t brightness = val * (3 - j) / 3;

                hsv_t color = {hue, sat, brightness};
                rgb_t rgb = hsv_to_rgb(color);
                rgb_matrix_set_color(led_index, rgb.r, rgb.g, rgb.b);
            }
        }
    }

    if (flash_active) {
        uint32_t elapsed = timer_elapsed32(flash_start);

        if (elapsed < 2000) {
            bool light_on = ((elapsed / 200) % 2) == 0;
            if (light_on) {
                for (uint8_t i = 98; i <= 106; i++) {
                    rgb_matrix_set_color(i, 0xFF, 0xFF, 0xFF);
                }
            }
        } else {
            flash_active = false;
        }
    }

    return true;
}
#endif


/******上位机通信*******/
#ifdef VIA_ENABLE
void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    uint8_t *command_id = &(data[0]);
    uint8_t *channel    = &(data[1]);
    uint8_t *value_id   = &(data[2]);

    if (*command_id == 0x07 && *channel == 0x13 && *value_id == 0x04) {
        if (length >= 4) {
            light_test_mode = (data[3] == 0x01);
        }
        return;
    }
    if (*command_id == 0x07 && *channel == 0x03 && *value_id == 0x02) {
        if (length >= 4) {
            if (data[3] == 0x2d) {
                custom_color_set_enabled(true);
                user_config.custom_mode = 1;
                rgb_matrix_mode(CUSTOM_RGB_MODE);
                eeconfig_update_rgblight_current();
            } else if (data[3] == 0x00) {
                custom_color_set_enabled(false);
                user_config.custom_mode = 0;
                rgb_matrix_mode(1);
                eeconfig_update_rgblight_current();
            }
            eeconfig_userconfig_update();
        }
        return;
    }

    if (*command_id == 0x07 && *channel == 0x13 && *value_id == 0x01) {
        if (length >= 4 && data[3] == 0x01) {
            eeconfig_init();
            reset_custom_color_and_restore_default_mode();
            wait_ms(100);
        }
        return;
    }

    if (*command_id == 0x07 && *channel == 0x13 && *value_id == 0x02) {
        if (length >= 4 && data[3] == 0x01) {
            wb32_usb_disconnect(&USBD1);
            wait_ms(2000);
            wb32_usb_connect(&USBD1);
        }
        return;
    }

    if (*command_id == 0x07 && *channel == 0x13 && *value_id == 0x03) {
        if (length >= 4 && data[3] == 0x01) {
            eeconfig_init();
            reset_custom_color_and_restore_default_mode();
            wait_ms(50);
            bootloader_jump();
        }
        return;
    }
}
#endif

void custom_color_activate_and_persist(void) {
    custom_color_set_enabled(true);
    user_config.custom_mode = 1;
    eeconfig_userconfig_update();
    rgb_matrix_mode(CUSTOM_RGB_MODE);
    eeconfig_update_rgblight_current();
}

#ifdef VIA_ENABLE
static void reset_custom_color_and_restore_default_mode(void) {
    eeconfig_confinfo_init();
    custom_color_clear_runtime();
    user_config.custom_mode = 0;
    eeconfig_userconfig_update();
    custom_mode_pending = false;
    rgb_matrix_mode(FACTORY_DEFAULT_RGB_MODE);
    eeconfig_update_rgblight_current();
}
#endif

static void clear_encoder_ring_light(void) {
#ifdef RGB_MATRIX_ENABLE
    for (uint8_t i = 98; i <= 106; i++) {
        rgb_matrix_set_color(i, 0, 0, 0);
    }
#endif
}

void housekeeping_task_user(void) {
    custom_color_flush_task();

    bool usb_active = usb_connected_state();
    if (usb_enumerated && !usb_active) {
        usb_enumerated = false;

#ifdef LED_POWER_EN_PIN
        gpio_write_pin_low(LED_POWER_EN_PIN);
#endif

#ifdef RGB_MATRIX_ENABLE
        rgb_matrix_set_suspend_state(true);
#endif
    }

    if (!usb_enumerated && usb_active) {
        usb_enumerated = true;

#ifdef LED_POWER_EN_PIN
        gpio_write_pin_high(LED_POWER_EN_PIN);
#endif

#ifdef RGB_MATRIX_ENABLE
        rgb_matrix_set_suspend_state(false);
#endif
        clear_encoder_ring_light();
    }
    if (custom_mode_pending && timer_elapsed32(custom_mode_timer) >= 3000) {
        custom_mode_pending = false;
        if (custom_color_is_enabled()) {
            rgb_matrix_mode(CUSTOM_RGB_MODE);
            eeconfig_update_rgblight_current();
        }
    }

    if (reset_triggered && timer_elapsed32(reset_timer) >= 3000) {
        reset_triggered = false;
        keyrecord_t record = {
            .event = {
                .key = {.row = 0xFF, .col = 0xFF},
                .pressed = true,
                .time = timer_read()
            },
            .keycode = EE_CLR
        };
        process_record_quantum(&record);
    }
}


