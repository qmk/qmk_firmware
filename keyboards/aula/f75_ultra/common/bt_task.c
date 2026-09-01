/**
 * @file bt_task.c
 * @brief
 * @author JoyLee
 * @version 2.0.0
 * @date 2023-04-06
 *
 * @copyright Copyright (c) 2023 Westberry Technology Corp., Ltd
 */

#include QMK_KEYBOARD_H

#include "bt_task.h"
#include "uart.h"
#include "usb_main.h"
#include "dynamic_keymap.h"
#include "bled/bled.h"
#include "lib/lib8tion/lib8tion.h"
#include "wwdg.h"

#ifdef BT_DEBUG_MODE
#    define BT_DEBUG_INFO(fmt, ...) dprintf(fmt, ##__VA_ARGS__)
#else
#    define BT_DEBUG_INFO(fmt, ...)
#endif

// ===========================================
// Function declarations
// ===========================================
static void bt_long_pressed_keys_hook(void);
static void bt_long_pressed_keys_cb(uint16_t keycode);
static bool bt_process_record_other(uint16_t keycode, keyrecord_t *record);
static void bt_used_pin_init(void);
static void bt_scan_mode(void);
// static void bt_blink_effects(void);
static void bt_charging_indication(void);
static void bt_bat_low_level_warning(void);
static void bt_bat_low_level_shutdown(void);
static void bt_bat_query_period(void);
static void bt_bat_level_display(void);
static void show_current_keyboard_state(void);
static void bt_indicate(void);
static void factory_reset_indicate(void);
static void usb_indicate(void);

#ifdef RGB_MATRIX_ENABLE
static void open_rgb(void);
static void close_rgb(void);
#endif

// ===========================================
// Constants definitions
// ===========================================
/* Wireless connection timing constants */
#define WL_CONN_TIMEOUT_MS (10 * 1000)     // 10 seconds
#define WL_PAIR_TIMEOUT_MS (1 * 60 * 1000) // 60 seconds
#define WL_PAIR_INTVL_MS (200)             // 5Hz blink for pairing
#define WL_CONN_INTVL_MS (500)             // 2Hz blink for connecting
#define WL_CONNECTED_LAST_MS (2 * 1000)    // Show wl connected status for 2s
#define USB_CONNECTED_LAST_MS (2 * 1000)   // Show USB connected status for 2s

/* Sleep and standby timeouts */
#define LED_OFF_STANDBY_TIMEOUT_MS (5 * 60 * 1000) // 5 minutes
#define ENTRY_SLEEP_TIMEOUT_MS LED_OFF_STANDBY_TIMEOUT_MS
// #define ENTRY_SLEEP_TIMEOUT_MS (30 * 60 * 1000)    // 30 minutes

/* Array size calculations */
#define NUM_LONG_PRESS_KEYS (sizeof(long_pressed_keys) / sizeof(long_pressed_keys_t))
#define LONG_PRESS_DURATION_MS (3 * 1000)

/* Hardware validation helpers */
#define IS_BT_DEVICE(dev) ((dev) >= DEVS_HOST1 && (dev) <= DEVS_HOST3)
#define IS_VALID_DEVICE(dev) ((dev) >= DEVS_USB && (dev) <= DEVS_2_4G)

#define TASK_UPDATE_INTERVAL_MS 1
#define BT_INIT_WAIT_MS 2000

// ===========================================
// Struct definitions
// ===========================================
typedef struct {
    uint32_t press_time;
    uint16_t keycode;
    void (*event_cb)(uint16_t);
} long_pressed_keys_t;

// Indicator status
typedef enum {
    INDICATOR_OFF        = 0,
    INDICATOR_PAIRING    = 1,
    INDICATOR_CONNECTING = 2,
    INDICATOR_CONNECTED  = 3,
    INDICATOR_DISABLED   = 4,
} indicator_state_t;
static indicator_state_t indicator_status = INDICATOR_CONNECTING;

typedef struct PACKED {
    uint32_t blink_time;
    uint32_t full_time;
    uint8_t  blink_count;
    bool     triggered;
    bool     full_triggered;
    bool     blink_state;
    bool     completed;
    bool     full_completed;
} charge_complete_warning_t;

charge_complete_warning_t charge_complete_warning = {0};

extern keymap_config_t keymap_config;

extern bool low_vol_offed_sleep;

uint32_t   bt_init_time = 0;
dev_info_t dev_info     = {0};
bts_info_t bts_info     = {
        .bt_name        = {MM_BT_HOST1_NAME, MM_BT_HOST2_NAME, MM_BT_HOST3_NAME},
        .uart_init      = uart_init,
        .uart_read      = uart_read,
        .uart_transmit  = uart_transmit,
        .uart_receive   = uart_receive,
        .uart_available = uart_available,
        .timer_read32   = timer_read32,
};

// Long press config
// clang-format off
static long_pressed_keys_t long_pressed_keys[] = {
    {.keycode = BT_HOST1, .press_time = 0, .event_cb = bt_long_pressed_keys_cb},
    {.keycode = BT_HOST2, .press_time = 0, .event_cb = bt_long_pressed_keys_cb},
    {.keycode = BT_HOST3, .press_time = 0, .event_cb = bt_long_pressed_keys_cb},
    {.keycode = BT_2_4G, .press_time = 0, .event_cb = bt_long_pressed_keys_cb},
    {.keycode = EE_CLR, .press_time = 0, .event_cb = bt_long_pressed_keys_cb},
    {.keycode = RGB_TEST, .press_time = 0, .event_cb = bt_long_pressed_keys_cb},
};
// clang-format on
static bool indicator_reset_last_time = false;

// RGB control
static uint32_t key_press_time = 0;
static uint32_t close_rgb_time = 0;

bool led_inited = false;

static bool bak_rgb_toggle = false;
static bool sober          = true;
static bool kb_sleep_flag  = false;

// static bool kb_light_sleep_flag = false;
// static bool rgb_status_save     = 1;

// static bool long_pressed_flag = false;

// Device indicator config
static const uint8_t rgb_index_table[] = {MM_BLINK_USB_INDEX, MM_BLINK_HOST1_INDEX, MM_BLINK_HOST2_INDEX, MM_BLINK_HOST3_INDEX, MM_BLINK_2G4_INDEX};
// clang-format off
static const uint8_t rgb_index_color_table[][3] = {
    {MM_BLINK_USB_COLOR},
    {MM_BLINK_HOST1_COLOR},
    {MM_BLINK_HOST2_COLOR},
    {MM_BLINK_HOST3_COLOR},
    {MM_BLINK_2G4_COLOR},
};
// clang-format on

// RGB test related
static const uint8_t rgb_test_color_table[][3] = {
    {100, 0, 0},
    {0, 100, 0},
    {0, 0, 100},
    {100, 100, 100},
};

static uint8_t  rgb_test_index  = 0;
static bool     rgb_test_en     = false;
static uint32_t rgb_test_time   = 0;
static bool     query_vol_flag  = false;
static uint32_t last_total_time = 0;

// static uint32_t caps_blink_time = 0;
// static uint8_t  caps_blink_cnt  = 0;
// static bool     caps_blink_flag = false;

static uint32_t EE_CLR_press_cnt  = 0;
static uint32_t EE_CLR_press_time = 0;
static bool     EE_CLR_flag       = false;

// Battery query
/* Battery level indicator */
uint8_t query_index[] = BAT_LEVEL_DISPLAY_INDEX;

bt_mode_t mode = MODE_WORKING;

// USB related
static uint32_t USB_switch_time = 0;

static bool is_in_charging_state   = false;
static bool is_in_full_power_state = false;

extern bool show_chrg;
extern bool show_chrg_full;

#include "command.h"
#include "action.h"

void register_mouse(uint8_t mouse_keycode, bool pressed);
/** \brief Utilities for actions. (FIXME: Needs better description)
 *
 * FIXME: Needs documentation.
 */
__attribute__((weak)) void register_code(uint8_t code) {
    if (dev_info.devs) {
        bts_process_keys(code, 1, dev_info.devs, keymap_config.no_gui, BT_KEY_NUM);
        bts_task(dev_info.devs);
        while (bts_is_busy()) {
            wait_ms(1);
        }
    } else {
        if (code == KC_NO) {
            return;

#ifdef LOCKING_SUPPORT_ENABLE
        } else if (KC_LOCKING_CAPS_LOCK == code) {
#    ifdef LOCKING_RESYNC_ENABLE
            // Resync: ignore if caps lock already is on
            if (host_keyboard_leds() & (1 << USB_LED_CAPS_LOCK)) return;
#    endif
            add_key(KC_CAPS_LOCK);
            send_keyboard_report();
            wait_ms(TAP_HOLD_CAPS_DELAY);
            del_key(KC_CAPS_LOCK);
            send_keyboard_report();

        } else if (KC_LOCKING_NUM_LOCK == code) {
#    ifdef LOCKING_RESYNC_ENABLE
            if (host_keyboard_leds() & (1 << USB_LED_NUM_LOCK)) return;
#    endif
            add_key(KC_NUM_LOCK);
            send_keyboard_report();
            wait_ms(100);
            del_key(KC_NUM_LOCK);
            send_keyboard_report();

        } else if (KC_LOCKING_SCROLL_LOCK == code) {
#    ifdef LOCKING_RESYNC_ENABLE
            if (host_keyboard_leds() & (1 << USB_LED_SCROLL_LOCK)) return;
#    endif
            add_key(KC_SCROLL_LOCK);
            send_keyboard_report();
            wait_ms(100);
            del_key(KC_SCROLL_LOCK);
            send_keyboard_report();
#endif

        } else if (IS_BASIC_KEYCODE(code)) {
            // TODO: should push command_proc out of this block?
            if (command_proc(code)) return;

            // Force a new key press if the key is already pressed
            // without this, keys with the same keycode, but different
            // modifiers will be reported incorrectly, see issue #1708
            if (is_key_pressed(code)) {
                del_key(code);
                send_keyboard_report();
            }
            add_key(code);
            send_keyboard_report();
        } else if (IS_MODIFIER_KEYCODE(code)) {
            add_mods(MOD_BIT(code));
            send_keyboard_report();

#ifdef EXTRAKEY_ENABLE
        } else if (IS_SYSTEM_KEYCODE(code)) {
            host_system_send(KEYCODE2SYSTEM(code));
        } else if (IS_CONSUMER_KEYCODE(code)) {
            host_consumer_send(KEYCODE2CONSUMER(code));
#endif

        } else if (IS_MOUSE_KEYCODE(code)) {
            register_mouse(code, true);
        }
    }
}

/** \brief Utilities for actions. (FIXME: Needs better description)
 *
 * FIXME: Needs documentation.
 */
__attribute__((weak)) void unregister_code(uint8_t code) {
    if (dev_info.devs) {
        bts_process_keys(code, 0, dev_info.devs, keymap_config.no_gui, BT_KEY_NUM);
        bts_task(dev_info.devs);
        while (bts_is_busy()) {
            wait_ms(1);
        }
    } else {
        if (code == KC_NO) {
            return;

#ifdef LOCKING_SUPPORT_ENABLE
        } else if (KC_LOCKING_CAPS_LOCK == code) {
#    ifdef LOCKING_RESYNC_ENABLE
            // Resync: ignore if caps lock already is off
            if (!(host_keyboard_leds() & (1 << USB_LED_CAPS_LOCK))) return;
#    endif
            add_key(KC_CAPS_LOCK);
            send_keyboard_report();
            del_key(KC_CAPS_LOCK);
            send_keyboard_report();

        } else if (KC_LOCKING_NUM_LOCK == code) {
#    ifdef LOCKING_RESYNC_ENABLE
            if (!(host_keyboard_leds() & (1 << USB_LED_NUM_LOCK))) return;
#    endif
            add_key(KC_NUM_LOCK);
            send_keyboard_report();
            del_key(KC_NUM_LOCK);
            send_keyboard_report();

        } else if (KC_LOCKING_SCROLL_LOCK == code) {
#    ifdef LOCKING_RESYNC_ENABLE
            if (!(host_keyboard_leds() & (1 << USB_LED_SCROLL_LOCK))) return;
#    endif
            add_key(KC_SCROLL_LOCK);
            send_keyboard_report();
            del_key(KC_SCROLL_LOCK);
            send_keyboard_report();
#endif

        } else if (IS_BASIC_KEYCODE(code)) {
            del_key(code);
            send_keyboard_report();
        } else if (IS_MODIFIER_KEYCODE(code)) {
            del_mods(MOD_BIT(code));
            send_keyboard_report();

#ifdef EXTRAKEY_ENABLE
        } else if (IS_SYSTEM_KEYCODE(code)) {
            host_system_send(0);
        } else if (IS_CONSUMER_KEYCODE(code)) {
            host_consumer_send(0);
#endif

        } else if (IS_MOUSE_KEYCODE(code)) {
            register_mouse(code, false);
        }
    }
}

void do_code16(uint16_t code, void (*f)(uint8_t));

__attribute__((weak)) void register_code16(uint16_t code) {
    if (dev_info.devs) {
        if (QK_MODS_GET_MODS(code) & 0x1) {
            if (QK_MODS_GET_MODS(code) & 0x10)
                bts_process_keys(KC_RCTL, 1, dev_info.devs, keymap_config.no_gui, BT_KEY_NUM);
            else
                bts_process_keys(KC_LCTL, 1, dev_info.devs, keymap_config.no_gui, BT_KEY_NUM);
        }
        if (QK_MODS_GET_MODS(code) & 0x2) {
            if (QK_MODS_GET_MODS(code) & 0x10)
                bts_process_keys(KC_RSFT, 1, dev_info.devs, keymap_config.no_gui, BT_KEY_NUM);
            else
                bts_process_keys(KC_LSFT, 1, dev_info.devs, keymap_config.no_gui, BT_KEY_NUM);
        }
        if (QK_MODS_GET_MODS(code) & 0x4) {
            if (QK_MODS_GET_MODS(code) & 0x10)
                bts_process_keys(KC_RALT, 1, dev_info.devs, keymap_config.no_gui, BT_KEY_NUM);
            else
                bts_process_keys(KC_LALT, 1, dev_info.devs, keymap_config.no_gui, BT_KEY_NUM);
        }
        if (QK_MODS_GET_MODS(code) & 0x8) {
            if (QK_MODS_GET_MODS(code) & 0x10)
                bts_process_keys(KC_RGUI, 1, dev_info.devs, keymap_config.no_gui, BT_KEY_NUM);
            else
                bts_process_keys(KC_LGUI, 1, dev_info.devs, keymap_config.no_gui, BT_KEY_NUM);
        }
        bts_process_keys(QK_MODS_GET_BASIC_KEYCODE(code), 1, dev_info.devs, keymap_config.no_gui, BT_KEY_NUM);
    } else {
        if (IS_MODIFIER_KEYCODE(code) || code == KC_NO) {
            do_code16(code, register_mods);
        } else {
            do_code16(code, register_weak_mods);
        }
        register_code(code);
    }
}

__attribute__((weak)) void unregister_code16(uint16_t code) {
    if (dev_info.devs) {
        if (QK_MODS_GET_MODS(code) & 0x1) {
            if (QK_MODS_GET_MODS(code) & 0x10)
                bts_process_keys(KC_RCTL, 0, dev_info.devs, keymap_config.no_gui, BT_KEY_NUM);
            else
                bts_process_keys(KC_LCTL, 0, dev_info.devs, keymap_config.no_gui, BT_KEY_NUM);
        }
        if (QK_MODS_GET_MODS(code) & 0x2) {
            if (QK_MODS_GET_MODS(code) & 0x10)
                bts_process_keys(KC_RSFT, 0, dev_info.devs, keymap_config.no_gui, BT_KEY_NUM);
            else
                bts_process_keys(KC_LSFT, 0, dev_info.devs, keymap_config.no_gui, BT_KEY_NUM);
        }
        if (QK_MODS_GET_MODS(code) & 0x4) {
            if (QK_MODS_GET_MODS(code) & 0x10)
                bts_process_keys(KC_RALT, 0, dev_info.devs, keymap_config.no_gui, BT_KEY_NUM);
            else
                bts_process_keys(KC_LALT, 0, dev_info.devs, keymap_config.no_gui, BT_KEY_NUM);
        }
        if (QK_MODS_GET_MODS(code) & 0x8) {
            if (QK_MODS_GET_MODS(code) & 0x10)
                bts_process_keys(KC_RGUI, 0, dev_info.devs, keymap_config.no_gui, BT_KEY_NUM);
            else
                bts_process_keys(KC_LGUI, 0, dev_info.devs, keymap_config.no_gui, BT_KEY_NUM);
        }
        bts_process_keys(QK_MODS_GET_BASIC_KEYCODE(code), 0, dev_info.devs, keymap_config.no_gui, BT_KEY_NUM);
    } else {
        unregister_code(code);
        if (IS_MODIFIER_KEYCODE(code) || code == KC_NO) {
            do_code16(code, unregister_mods);
        } else {
            do_code16(code, unregister_weak_mods);
        }
    }
}

// ===========================================
// Thread definitions
// ===========================================
static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {
    (void)arg;
    chRegSetThreadName("blinker");
    while (true) {
        bts_task(dev_info.devs);
        chThdSleepMilliseconds(1);
    }
}

// ===========================================
// Initialization functions
// ===========================================
void bt_init(void) {
    bts_init(&bts_info);
    bt_used_pin_init();

    dev_info.raw = eeconfig_read_user();
    if (!dev_info.raw) {
        dev_info.devs      = DEVS_USB;
        dev_info.last_devs = DEVS_HOST1;
        eeconfig_update_user(dev_info.raw);
    }

    bt_init_time = timer_read32();

    chThdCreateStatic(waThread1, sizeof(waThread1), HIGHPRIO, Thread1, NULL);

    // If the device is not USB, we need to set the scan mode
    bt_scan_mode();

    bts_send_name(DEVS_HOST1);
    wait_ms(10);

    if (dev_info.devs != DEVS_USB) {
        usbDisconnectBus(&USB_DRIVER);
        usbStop(&USB_DRIVER);
    }

    gpio_set_pin_output(A14);
    if (dev_info.devs == DEVS_USB) {
        gpio_write_pin_low(A14);
    } else {
        gpio_write_pin_high(A14);
    }

    // rgb_status_save = rgb_matrix_config.enable;
}

// ===========================================
// Bluetooth task functions
// ===========================================
void bt_task(void) {
    static uint32_t last_time = 0;

    // Handle initialization sequence after delay
    if ((bt_init_time != 0) && (timer_elapsed32(bt_init_time) >= BT_INIT_WAIT_MS)) {
        bt_init_time = 0;

        // bts_send_name(DEVS_HOST1);
        // wait_ms(10);
        bts_send_vendor(v_en_sleep_bt);

        switch (dev_info.devs) {
            case DEVS_HOST1: {
                bts_send_vendor(v_host1);
                // bts_send_name(DEVS_HOST1);
            } break;
            case DEVS_HOST2: {
                bts_send_vendor(v_host2);
                // bts_send_name(DEVS_HOST2);
            } break;
            case DEVS_HOST3: {
                bts_send_vendor(v_host3);
                // bts_send_name(DEVS_HOST3);
            } break;
            case DEVS_2_4G: {
                bts_send_vendor(v_2_4g);
            } break;
            default: {
                bts_send_vendor(v_usb);
                dev_info.devs = DEVS_USB;
                eeconfig_update_user(dev_info.raw);
            } break;
        }

        // bts_send_vendor(v_en_sleep_bt);
        // wait_ms(200);
        // bts_send_vendor(v_en_sleep_wl);
    }

    // Update task at regular intervals
    if (timer_elapsed32(last_time) >= TASK_UPDATE_INTERVAL_MS) {
        last_time = timer_read32();

        // extern void Charge_Chat(void);
        // Charge_Chat();

        if (dev_info.devs != DEVS_USB) {
#ifdef RGB_MATRIX_ENABLE
            close_rgb();
#endif
        }
    }

    bt_long_pressed_keys_hook();

    bt_scan_mode();
}

// ===========================================
// Key processing function
// ===========================================
bool bt_process_record(uint16_t keycode, keyrecord_t *record) {
    bool retval = true;

    if (record->event.pressed) {
        BT_DEBUG_INFO("\n\nkeycode = [0x%x], pressed time: [%d]\n\n", keycode, record->event.time);
        BT_DEBUG_INFO("\n devs     = [%d] \
                    \n sleeped       = [%d] \
                    \n low_vol       = [%d] \
                    \n low_vol_offed = [%d] \
                    \n normal_vol    = [%d] \
                    \n pairing       = [%d] \
                    \n paired        = [%d] \
                    \n come_back     = [%d] \
                    \n come_back_err = [%d] \
                    \n mode_switched = [%d] \
                    \n pvol          = [%d]\n\n\n",
                      dev_info.devs, bts_info.bt_info.sleeped, bts_info.bt_info.low_vol, bts_info.bt_info.low_vol_offed, bts_info.bt_info.normal_vol, bts_info.bt_info.pairing, bts_info.bt_info.paired, bts_info.bt_info.come_back, bts_info.bt_info.come_back_err, bts_info.bt_info.mode_switched, bts_info.bt_info.pvol);

        // if (!rgb_matrix_config.enable) {
        //     if (rgb_status_save) {
        //         rgb_matrix_enable_noeeprom();
        //         if (host_keyboard_led_state().caps_lock) {
        //             setPinOutputPushPull(LED_CAPS_LOCK_PIN);
        //             gpio_write_pin_high(LED_CAPS_LOCK_PIN);
        //             // gpio_write_pin(LED_CAPS_LOCK_PIN, 1);
        //         }
        //         kb_light_sleep_flag = false;
        //     }
        // }

        if (indicator_status != INDICATOR_OFF) {
            last_total_time = timer_read32();
        }
    }

    retval = bt_process_record_other(keycode, record);

    if (dev_info.devs != DEVS_USB) {
        if (retval != false) {
            while (bts_is_busy()) {
                wait_ms(1);
            }
            if ((keycode > QK_MODS) && (keycode <= QK_MODS_MAX)) {
                if (QK_MODS_GET_MODS(keycode) & 0x1) {
                    if (QK_MODS_GET_MODS(keycode) & 0x10)
                        bts_process_keys(KC_RCTL, record->event.pressed, dev_info.devs, keymap_config.no_gui, BT_KEY_NUM);
                    else
                        bts_process_keys(KC_LCTL, record->event.pressed, dev_info.devs, keymap_config.no_gui, BT_KEY_NUM);
                }
                if (QK_MODS_GET_MODS(keycode) & 0x2) {
                    if (QK_MODS_GET_MODS(keycode) & 0x10)
                        bts_process_keys(KC_RSFT, record->event.pressed, dev_info.devs, keymap_config.no_gui, BT_KEY_NUM);
                    else
                        bts_process_keys(KC_LSFT, record->event.pressed, dev_info.devs, keymap_config.no_gui, BT_KEY_NUM);
                }
                if (QK_MODS_GET_MODS(keycode) & 0x4) {
                    if (QK_MODS_GET_MODS(keycode) & 0x10)
                        bts_process_keys(KC_RALT, record->event.pressed, dev_info.devs, keymap_config.no_gui, BT_KEY_NUM);
                    else
                        bts_process_keys(KC_LALT, record->event.pressed, dev_info.devs, keymap_config.no_gui, BT_KEY_NUM);
                }
                if (QK_MODS_GET_MODS(keycode) & 0x8) {
                    if (QK_MODS_GET_MODS(keycode) & 0x10)
                        bts_process_keys(KC_RGUI, record->event.pressed, dev_info.devs, keymap_config.no_gui, BT_KEY_NUM);
                    else
                        bts_process_keys(KC_LGUI, record->event.pressed, dev_info.devs, keymap_config.no_gui, BT_KEY_NUM);
                }
                retval = bts_process_keys(QK_MODS_GET_BASIC_KEYCODE(keycode), record->event.pressed, dev_info.devs, keymap_config.no_gui, BT_KEY_NUM);
            } else {
                retval = bts_process_keys(keycode, record->event.pressed, dev_info.devs, keymap_config.no_gui, BT_KEY_NUM);
            }
        }
    }

#ifdef RGB_MATRIX_ENABLE
    open_rgb();
#endif

    return retval;
}

// ===========================================
// Device switch function
// ===========================================
void bt_switch_mode(uint8_t last_mode, uint8_t now_mode, uint8_t reset) {
    // Enable RGB if it was previously enabled
    // if (!rgb_matrix_config.enable && rgb_status_save) {
    //     rgb_matrix_enable_noeeprom();
    //     kb_light_sleep_flag = false;
    // }
    // wwdg_pause();
    // Handle USB driver state changes
    bool usb_sws = !!last_mode ? !now_mode : !!now_mode;
    if (usb_sws) {
        if (!!now_mode) {
            usbDisconnectBus(&USB_DRIVER);
            usbStop(&USB_DRIVER);
        } else {
            init_usb_driver(&USB_DRIVER);
        }
    }

    // Reset wireless indicator timer if switching between different devices
    if (last_mode != now_mode) {
        last_total_time = timer_read32();
    }

    // Update device state
    dev_info.devs = now_mode;
    if ((dev_info.devs != DEVS_USB) && (dev_info.devs != DEVS_2_4G)) {
        dev_info.last_devs = dev_info.devs;
    } else if (dev_info.devs == DEVS_USB) {
        USB_switch_time = timer_read32();
    }
    // Set hardware control pin
    if (dev_info.devs == DEVS_USB) {
        gpio_write_pin_low(A14);
    } else {
        gpio_write_pin_high(A14);
    }

    // Reset BT connection state
    bts_info.bt_info.pairing        = false;
    bts_info.bt_info.paired         = false;
    bts_info.bt_info.come_back      = false;
    bts_info.bt_info.come_back_err  = false;
    bts_info.bt_info.mode_switched  = false;
    bts_info.bt_info.indictor_rgb_s = 0;

    eeconfig_update_user(dev_info.raw);

    // Handle indicator status and send vendor commands
    switch (dev_info.devs) {
        case DEVS_HOST1: {
            if (reset != false) {
                // Reset - enter pairing mode
                indicator_status          = 1;
                indicator_reset_last_time = true;
                // bts_send_name(DEVS_HOST1);
                // bts_send_vendor(v_host1);
                bts_send_vendor(v_pair);
            } else {
                indicator_status          = 2;
                indicator_reset_last_time = true;
                bts_send_vendor(v_host1);
            }
        } break;
        case DEVS_HOST2: {
            if (reset != false) {
                // Reset - enter pairing mode
                indicator_status          = 1;
                indicator_reset_last_time = true;
                // bts_send_name(DEVS_HOST2);
                // bts_send_vendor(v_host2);
                bts_send_vendor(v_pair);
            } else {
                indicator_status          = 2;
                indicator_reset_last_time = true;
                bts_send_vendor(v_host2);
            }
        } break;
        case DEVS_HOST3: {
            if (reset != false) {
                // Reset - enter pairing mode
                indicator_status          = 1;
                indicator_reset_last_time = true;
                // bts_send_name(DEVS_HOST3);
                // bts_send_vendor(v_host3);
                bts_send_vendor(v_pair);
            } else {
                indicator_status          = 2;
                indicator_reset_last_time = true;
                bts_send_vendor(v_host3);
            }
        } break;
        case DEVS_2_4G: {
            if (reset != false) {
                // Reset - enter pairing mode
                indicator_status          = 1;
                indicator_reset_last_time = true;
                bts_send_vendor(v_pair);
            } else {
                indicator_status          = 2;
                indicator_reset_last_time = true;
                bts_send_vendor(v_2_4g);
            }
        } break;
        case DEVS_USB: {
            bts_send_vendor(v_usb);
        } break;
        default:
            break;
    }
    // wwdg_resume();
}

// ===========================================
// Other key processing functions
// ===========================================
static bool bt_process_record_other(uint16_t keycode, keyrecord_t *record) {
    if (dev_info.devs == DEVS_2_4G) {
        if ((keycode == BT_USB) || (keycode >= BT_HOST1 && keycode <= BT_HOST3)) return false;
    }
    if (dev_info.devs >= DEVS_HOST1 && dev_info.devs <= DEVS_HOST3) {
        if (keycode == BT_2_4G || keycode == BT_USB) return false;
    }
    if (dev_info.devs == DEVS_USB) {
        if (keycode >= BT_HOST1 && keycode <= BT_2_4G) return false;
    }

    // Update long press time
    for (uint8_t i = 0; i < NUM_LONG_PRESS_KEYS; i++) {
        if (keycode == long_pressed_keys[i].keycode) {
            if (record->event.pressed) {
                long_pressed_keys[i].press_time = timer_read32();
            } else {
                long_pressed_keys[i].press_time = 0;
            }
            break;
        }
    }

    switch (keycode) {
        case BT_HOST1: {
            if (record->event.pressed) {
                if (dev_info.devs != DEVS_HOST1) {
                    bt_switch_mode(dev_info.devs, DEVS_HOST1, false);
                }
            }
        } break;
        case BT_HOST2: {
            if (record->event.pressed) {
                if (dev_info.devs != DEVS_HOST2) {
                    bt_switch_mode(dev_info.devs, DEVS_HOST2, false);
                }
            }
        } break;
        case BT_HOST3: {
            if (record->event.pressed) {
                if (dev_info.devs != DEVS_HOST3) {
                    bt_switch_mode(dev_info.devs, DEVS_HOST3, false);
                }
            }
        } break;
        case BT_2_4G: {
            if (record->event.pressed) {
                if (dev_info.devs != DEVS_2_4G) {
                    bt_switch_mode(dev_info.devs, DEVS_2_4G, false);
                }
            }
        } break;
        case BT_USB: {
            if (record->event.pressed) {
                bt_switch_mode(dev_info.devs, DEVS_USB, false);
            }
        } break;

        case BT_VOL: {
            if (record->event.pressed) {
                bts_send_vendor(v_query_vol);
                query_vol_flag = true;
            } else {
                query_vol_flag = false;
            }
        } break;

        case EE_CLR: {
        } break;

        case RGB_TEST: {
            if (record->event.pressed) {
                if (rgb_test_en) {
                    rgb_test_en    = false;
                    rgb_test_index = 0;
                }
            }
        } break;

        default:
            return true;
    }

    return false;
}

// ===========================================
// 长按键处理
// ===========================================
static void bt_long_pressed_keys_cb(uint16_t keycode) {
    switch (keycode) {
        case BT_HOST1:
        case BT_HOST2:
        case BT_HOST3:
        case BT_2_4G: {
            uint8_t target_dev = keycode - BT_HOST1 + DEVS_HOST1;
            if (dev_info.devs == target_dev) {
                bt_switch_mode(dev_info.devs, target_dev, true);
            }
        } break;

        case EE_CLR: {
            if (!EE_CLR_flag) {
                EE_CLR_flag       = true;
                EE_CLR_press_time = timer_read32();
                EE_CLR_press_cnt  = 1;
                rgb_matrix_enable_noeeprom();
            }
        } break;

        case RGB_TEST: {
            if (rgb_test_en != true) {
                rgb_test_en    = true;
                rgb_test_index = 1;
                rgb_test_time  = timer_read32();
            }
        } break;

        default:
            break;
    }
}

static void bt_long_pressed_keys_hook(void) {
    for (uint8_t i = 0; i < NUM_LONG_PRESS_KEYS; i++) {
        if ((long_pressed_keys[i].press_time != 0) && (timer_elapsed32(long_pressed_keys[i].press_time) >= LONG_PRESS_DURATION_MS)) {
            long_pressed_keys[i].event_cb(long_pressed_keys[i].keycode);
            long_pressed_keys[i].press_time = 0;
        }
    }
}

// ===========================================
// Pin init functions
// ===========================================
static void bt_used_pin_init(void) {
#if defined(MM_BT_MODE_PIN) && defined(MM_2G4_MODE_PIN)
    gpio_set_pin_input_high(MM_BT_MODE_PIN);
    gpio_set_pin_input_high(MM_2G4_MODE_PIN);
#endif

#if defined(MM_CABLE_PIN) && defined(MM_CHARGE_PIN)
    gpio_set_pin_input_high(MM_CABLE_PIN);
    gpio_set_pin_input_high(MM_CHARGE_PIN);
#endif

#ifdef RGB_MATRIX_SHUTDOWN_PIN
    gpio_set_pin_output_open_drain(RGB_MATRIX_SHUTDOWN_PIN);
    gpio_write_pin_high(RGB_MATRIX_SHUTDOWN_PIN);
    // wait_ms(10);
    // gpio_write_pin_high(RGB_MATRIX_SHUTDOWN_PIN);
#endif
}

static void bt_scan_mode(void) {
#if defined(MM_BT_MODE_PIN) && defined(MM_2G4_MODE_PIN)
    uint8_t        now_mode;
    static uint8_t old_mode;
    static bool    first_call = true;

    if (gpio_read_pin(MM_BT_MODE_PIN) && !gpio_read_pin(MM_2G4_MODE_PIN)) {
        now_mode = 0;
        if (dev_info.devs != DEVS_2_4G) bt_switch_mode(dev_info.devs, DEVS_2_4G, false); // 2_4G mode
    }
    if (gpio_read_pin(MM_2G4_MODE_PIN) && !gpio_read_pin(MM_BT_MODE_PIN)) {
        now_mode = 1;
        if ((dev_info.devs == DEVS_USB) || (dev_info.devs == DEVS_2_4G)) bt_switch_mode(dev_info.devs, dev_info.last_devs, false); // BT mode
    }
    if (gpio_read_pin(MM_BT_MODE_PIN) && gpio_read_pin(MM_2G4_MODE_PIN)) {
        now_mode = 2;
        if (dev_info.devs != DEVS_USB) bt_switch_mode(dev_info.devs, DEVS_USB, false); // usb mode
    }

    // Skip RGB reinit on first call (during bt_init) - RGB is already initialized during boot
    if (first_call) {
        old_mode   = now_mode;
        first_call = false;
        return;
    }

    if ((old_mode != now_mode) && !bts_info.bt_info.low_vol) {
        old_mode = now_mode;

        gpio_write_pin_low(RGB_MATRIX_SHUTDOWN_PIN);
        wait_ms(1);
        gpio_write_pin_high(RGB_MATRIX_SHUTDOWN_PIN);

        rgb_matrix_init();
    }

#endif
}

void led_config_all(void) {
    if (!led_inited) {
        // #ifdef RGB_MATRIX_SHUTDOWN_PIN
        //         gpio_set_pin_output_open_drain(RGB_MATRIX_SHUTDOWN_PIN);
        //         gpio_write_pin_high(RGB_MATRIX_SHUTDOWN_PIN);
        // #endif
        // gpio_set_pin_output_open_drain(LED_CAPS_LOCK_PIN);
        // if (host_keyboard_led_state().caps_lock) {
        //     gpio_write_pin_high(LED_CAPS_LOCK_PIN);
        // }
        gpio_set_pin_output(LED_CAPS_LOCK_PIN);
        gpio_write_pin(LED_CAPS_LOCK_PIN, (host_keyboard_led_state().caps_lock));

        led_inited = true;
    }
}

void led_deconfig_all(void) {
    if (led_inited) {
        // #ifdef RGB_MATRIX_SHUTDOWN_PIN
        //         gpio_set_pin_output_open_drain(RGB_MATRIX_SHUTDOWN_PIN);
        //         gpio_write_pin_low(RGB_MATRIX_SHUTDOWN_PIN);
        // #endif
        // gpio_write_pin(LED_CAPS_LOCK_PIN, 0);
        // gpio_set_pin_output_open_drain(LED_CAPS_LOCK_PIN);
        // gpio_write_pin_low(LED_CAPS_LOCK_PIN);
        gpio_write_pin_low(LED_CAPS_LOCK_PIN);

        led_inited = false;
    }
}

// ===========================================
// No operation standby functions
// ===========================================
void cansel_chrg_full_indicate(void) {
    // is_in_charging_state   = false;
    // is_in_full_power_state = false;
    // memset(&charge_complete_warning, 0, sizeof(charge_complete_warning_t));

    show_chrg      = false;
    show_chrg_full = false;
}

// ===========================================
// RGB close functions
// ===========================================
static void close_rgb(void) {
    if (!key_press_time) {
        key_press_time = timer_read32();
        return;
    }

    if (sober) {
        if (kb_sleep_flag || (timer_elapsed32(key_press_time) >= ENTRY_SLEEP_TIMEOUT_MS)) {
            // wwdg_pause();
            // bak_rgb_toggle = rgb_matrix_config.enable;
            bak_rgb_toggle = rgb_matrix_is_enabled();
            // bak_rgb_toggle = rgb_status_save;
            sober          = false;
            close_rgb_time = timer_read32();
            rgb_matrix_disable_noeeprom();

            cansel_chrg_full_indicate();

#ifdef RGB_MATRIX_SHUTDOWN_PIN
            // gpio_set_pin_output_open_drain(RGB_MATRIX_SHUTDOWN_PIN);
            gpio_write_pin_low(RGB_MATRIX_SHUTDOWN_PIN);
#endif
        }
    } else {
        if (!rgb_matrix_config.enable) {
            if (timer_elapsed32(close_rgb_time) >= ENTRY_STOP_TIMEOUT) {
                if (led_inited) {
                    led_deconfig_all();
                }
#ifdef ENTRY_STOP_MODE
                lp_system_sleep();
#endif
                open_rgb();
            }
        }
    }
}

// ===========================================
// Open RGB functions
// ===========================================
static void open_rgb(void) {
    key_press_time = timer_read32();

    if (!sober) {
        // wwdg_resume();
        if (bak_rgb_toggle) {
            kb_sleep_flag       = false;
            low_vol_offed_sleep = false;
            rgb_matrix_enable_noeeprom();

#ifdef RGB_MATRIX_SHUTDOWN_PIN
            // setPinOutputPushPull(RGB_MATRIX_SHUTDOWN_PIN);
            gpio_write_pin_high(RGB_MATRIX_SHUTDOWN_PIN);
#endif
        }
        if (!led_inited) {
            led_config_all();
        }
        sober = true;
    }
}

// ===========================================
// Bt indicator functions
// ===========================================
static void bt_indicate(void) {
    uint8_t         rgb_index      = rgb_index_table[dev_info.devs];
    static uint32_t last_time      = 0;
    static uint32_t last_long_time = 0;
    static uint8_t  last_status    = 0;
    static bool     rgb_flip       = false;
    static RGB      rgb            = {0};

    if (last_status != indicator_status) {
        last_status     = indicator_status;
        last_total_time = timer_read32();
    }

    if (indicator_reset_last_time != false) {
        indicator_reset_last_time = false;
        last_time                 = 0;
    }

    switch (indicator_status) {
        case INDICATOR_PAIRING: {
            if ((last_time == 0) || (timer_elapsed32(last_time) >= WL_PAIR_INTVL_MS)) {
                last_time = timer_read32();
                rgb_flip  = !rgb_flip;
                if (rgb_flip) {
                    rgb.r = rgb_index_color_table[dev_info.devs][0];
                    rgb.g = rgb_index_color_table[dev_info.devs][1];
                    rgb.b = rgb_index_color_table[dev_info.devs][2];
                } else {
                    rgb = (RGB){.r = 0, .g = 0, .b = 0};
                }
            }

            if (bts_info.bt_info.paired) {
                last_long_time   = timer_read32();
                indicator_status = INDICATOR_CONNECTED;
                break;
            }

            if (timer_elapsed32(last_total_time) >= WL_PAIR_TIMEOUT_MS) {
                indicator_status = INDICATOR_OFF;
                kb_sleep_flag    = true;
            }
        } break;

        case INDICATOR_CONNECTING: {
            if ((last_time == 0) || (timer_elapsed32(last_time) >= WL_CONN_INTVL_MS)) {
                last_time = timer_read32();
                rgb_flip  = !rgb_flip;
                if (rgb_flip) {
                    rgb.r = rgb_index_color_table[dev_info.devs][0];
                    rgb.g = rgb_index_color_table[dev_info.devs][1];
                    rgb.b = rgb_index_color_table[dev_info.devs][2];
                } else {
                    rgb = (RGB){.r = 0, .g = 0, .b = 0};
                }
            }

            if (bts_info.bt_info.paired) {
                // if (host_keyboard_led_state().caps_lock) {
                //     setPinOutputPushPull(LED_CAPS_LOCK_PIN);
                //     gpio_write_pin_high(LED_CAPS_LOCK_PIN);
                // }
                last_long_time   = timer_read32();
                indicator_status = INDICATOR_CONNECTED;
                break;
            }

            // if (host_keyboard_led_state().caps_lock) {
            //     gpio_set_pin_output_open_drain(LED_CAPS_LOCK_PIN);
            //     gpio_write_pin_low(LED_CAPS_LOCK_PIN);
            // }

            if (timer_elapsed32(last_total_time) >= WL_CONN_TIMEOUT_MS) {
                indicator_status = INDICATOR_OFF;
                kb_sleep_flag    = true;
            }
        } break;

        case INDICATOR_CONNECTED: {
            if ((timer_elapsed32(last_long_time) < WL_CONNECTED_LAST_MS)) {
                rgb.r = rgb_index_color_table[dev_info.devs][0];
                rgb.g = rgb_index_color_table[dev_info.devs][1];
                rgb.b = rgb_index_color_table[dev_info.devs][2];
            } else {
                indicator_status = INDICATOR_OFF;
            }
        } break;

        case INDICATOR_DISABLED: {
            rgb = (RGB){.r = 0, .g = 0, .b = 0};
        } break;

        default: {
            rgb_flip = false;
            if (!kb_sleep_flag) {
                if (!bts_info.bt_info.paired) {
                    if (!bts_info.bt_info.pairing) {
                        indicator_status = INDICATOR_CONNECTING;
                        break;
                    }
                    indicator_status = INDICATOR_CONNECTING;
                    if (dev_info.devs == DEVS_2_4G) {
                        bt_switch_mode(dev_info.devs, DEVS_2_4G, false);
                    } else {
                        bt_switch_mode(dev_info.devs, dev_info.last_devs, false);
                    }
                }
            }
        } break;
    }

    if (indicator_status) {
        rgb_matrix_set_color(rgb_index, rgb.r, rgb.g, rgb.b);
    }
}

// ===========================================
// USB indicator functions
// ===========================================
static void usb_indicate(void) {
    if (USB_DRIVER.state == USB_ACTIVE) {
        if (timer_elapsed32(USB_switch_time) < USB_CONNECTED_LAST_MS) {
            rgb_matrix_set_color(rgb_index_table[DEVS_USB], rgb_index_color_table[DEVS_USB][0], rgb_index_color_table[DEVS_USB][1], rgb_index_color_table[DEVS_USB][2]);
        }
    } else {
        USB_switch_time = timer_read32();
    }
}

// ===========================================
// Battery low level warning functions
// ===========================================
static void bt_bat_low_level_warning(void) {
    static bool     Low_power_bink    = false;
    static uint32_t Low_power_time    = 0;
    static bool     low_level_warning = false;

    // if (bts_info.bt_info.low_vol) {
    if ((bts_info.bt_info.pvol <= 5) && !low_level_warning) {
        low_level_warning = true;
    } else if ((bts_info.bt_info.pvol >= 30) && low_level_warning) {
        low_level_warning = false;
    }

    if (low_level_warning) {
        rgb_matrix_set_color_all(RGB_OFF);

        if (timer_elapsed32(Low_power_time) >= 500) {
            Low_power_bink = !Low_power_bink;
            Low_power_time = timer_read32();
        }
        if (Low_power_bink) {
            rgb_matrix_set_color(CHRGE_LOW_LEVEL_INDICATOR_INDEX, CHRGE_LOW_LEVEL_INDICATOR_COLOR);
        } else {
            rgb_matrix_set_color(CHRGE_LOW_LEVEL_INDICATOR_INDEX, RGB_OFF);
        }
    } else {
        Low_power_bink = false;
    }
}

static void bt_charging_indication(void) {
    const uint8_t leds[] = {80, 81, 82, 83, 84};

    static uint32_t entry_chrg_time = 0;
    static uint32_t entry_full_time = 0;

    extern bool is_charging(void);
    extern bool is_fully_charged(void);

    if (is_charging()) {
        if (is_fully_charged()) {
            entry_full_time = timer_read32();
            if (timer_elapsed32(entry_chrg_time) >= 500) {
                // show_chrging = true;
                if (!is_in_charging_state) {
                    is_in_charging_state = true;
                    if (!charge_complete_warning.triggered) {
                        charge_complete_warning.triggered   = true;
                        charge_complete_warning.blink_count = 0;
                        charge_complete_warning.blink_time  = timer_read32();
                        charge_complete_warning.blink_state = false;
                        charge_complete_warning.completed   = false;

                        // chrg_total_time = timer_read32();

                        show_chrg = true;
                    }
                }
            }

            if (!charge_complete_warning.completed) {
                // if (!charge_complete_warning.completed && charge_complete_warning.blink_count < 11) {
                // if (!charge_complete_warning.completed && timer_elapsed32(chrg_total_time) < 10000) {
                // if (timer_elapsed32(charge_complete_warning.chrg_total_time) < 10000) {

                if (timer_elapsed32(charge_complete_warning.blink_time) >= 500) {
                    charge_complete_warning.blink_time  = timer_read32();
                    charge_complete_warning.blink_state = !charge_complete_warning.blink_state;

                    // Count complete on/off cycles (increment on falling edge)
                    if (charge_complete_warning.blink_state) {
                        charge_complete_warning.blink_count++;
                        if (charge_complete_warning.blink_count > 9) {
                            charge_complete_warning.completed   = true;
                            charge_complete_warning.blink_state = false;

                            show_chrg = false;
                        }
                    }
                }

                if (charge_complete_warning.blink_state) {
                    for (uint8_t i = 0; i < 5; i++) {
                        rgb_matrix_set_color(leds[i], 0, 100, 0);
                    }
                } else {
                    for (uint8_t i = 0; i < 5; i++) {
                        rgb_matrix_set_color(leds[i], RGB_OFF);
                    }
                }
            }
            // else {
            //     charge_complete_warning.completed = true;

            //     show_chrg = false;
            // }
            // }
        } else {
            // Charge pin indicates full - trigger only if not already displayed
            entry_chrg_time = timer_read32();
            if (timer_elapsed32(entry_full_time) >= 000) {
                // if ((dev_info.devs != DEVS_USB) && (bts_info.bt_info.pvol >= 100)) {
                if (!is_in_full_power_state) {
                    is_in_full_power_state = true;
                    if (!charge_complete_warning.full_triggered) {
                        charge_complete_warning.full_triggered = true;
                        charge_complete_warning.full_time      = timer_read32();

                        show_chrg_full = true;
                    }
                }
                // }
            }

            if (!charge_complete_warning.full_completed) {
                if (timer_elapsed32(charge_complete_warning.full_time) <= 10000) {
                    for (uint8_t i = 0; i < 5; i++) {
                        rgb_matrix_set_color(leds[i], 0, 100, 0);
                    }
                } else {
                    charge_complete_warning.full_completed = true;

                    show_chrg_full = false;
                }
            }
        }

        // }
    } else {
        is_in_charging_state   = false;
        is_in_full_power_state = false;
        memset(&charge_complete_warning, 0, sizeof(charge_complete_warning_t));

        entry_chrg_time = timer_read32();
        entry_full_time = timer_read32();
    }
}

static void bt_bat_low_level_shutdown(void) {
    if (bts_info.bt_info.low_vol_offed) {
        kb_sleep_flag       = true;
        low_vol_offed_sleep = true;
    }
}

// ===========================================
// Battery query display functions
// ===========================================
static void bt_bat_query_period(void) {
    static uint32_t query_vol_time = 0;
    // if (!kb_light_sleep_flag && !bt_init_time && !kb_sleep_flag && (bts_info.bt_info.paired) && timer_elapsed32(query_vol_time) > 4000) {
    if (!bt_init_time && !kb_sleep_flag && (bts_info.bt_info.paired) && timer_elapsed32(query_vol_time) > 4000) {
        // if (!bt_init_time && !kb_sleep_flag && (bts_info.bt_info.paired) && timer_elapsed32(query_vol_time) >= 10000) {
        query_vol_time = timer_read32();
        bts_send_vendor(v_query_vol);
    }
}

static void bt_bat_level_display(void) {
    if (query_vol_flag) {
        for (uint8_t i = 0; i < 80; i++) {
            rgb_matrix_set_color(i, RGB_OFF);
        }
        uint8_t pvol      = bts_info.bt_info.pvol;
        uint8_t led_count = (pvol < 10) ? 1 : ((pvol / 10) > 10 ? 10 : pvol / 10);

        RGB color;
        if (pvol < 30) {
            color = (RGB){RGB_RED}; // 红色
        } else {
            color = (RGB){RGB_GREEN}; // 绿色
        }

        for (uint8_t i = 0; i < led_count; i++) {
            rgb_matrix_set_color(query_index[i], color.r, color.g, color.b);
        }
    }
}

static void show_current_keyboard_state(void) {
    // Show current device and system status when FN layer is active
    // Check if any FN layer (1, 3, or 5) is active via MO()
    bool fn_layer_active = layer_state_is(1) || layer_state_is(3) || layer_state_is(5);

    if (fn_layer_active) {
        // Show current device status (USB, BT1, BT2, BT3, 2.4G)
        rgb_matrix_set_color(rgb_index_table[dev_info.devs], RGB_WHITE);

        // Show current system status based on default layer
        uint8_t base_layer = get_highest_layer(default_layer_state);
        if (base_layer == 0) {
            rgb_matrix_set_color(LED_W_INDEX, RGB_WHITE); // Windows
        } else if (base_layer == 2) {
            rgb_matrix_set_color(LED_Q_INDEX, RGB_WHITE); // Mac
        } else if (base_layer == 4) {
            rgb_matrix_set_color(LED_E_INDEX, RGB_WHITE); // Third system
        }
    }
}

static void factory_reset_indicate(void) {
    if (EE_CLR_flag) {
        for (uint8_t i = 0; i < 80; i++) {
            rgb_matrix_set_color(i, 0, 0, 0);
        }
        if (timer_elapsed32(EE_CLR_press_time) > 300) {
            EE_CLR_press_time = timer_read32();
            EE_CLR_press_cnt++;
        }
        if (EE_CLR_press_cnt >= 7) {
            EE_CLR_press_cnt  = 0;
            EE_CLR_press_time = 0;
            EE_CLR_flag       = false;

            eeconfig_init();
            keymap_config.no_gui = false;

            mode = MODE_WORKING;

            // bts_send_vendor(v_clear);
            // wait_ms(1000);

            // if (dev_info.devs != DEVS_USB) {
            //     last_total_time = timer_read32();
            //     // indicator_status = INDICATOR_CONNECTING;
            //     if ((dev_info.devs != DEVS_USB) && (dev_info.devs != DEVS_2_4G)) {
            //         bt_switch_mode(DEVS_USB, dev_info.last_devs, false);
            //     }
            //     if (dev_info.devs == DEVS_2_4G) {
            //         bt_switch_mode(DEVS_USB, DEVS_2_4G, false);
            //     }
            // }
        }
        if (EE_CLR_press_cnt & 0x1) {
            for (uint8_t i = 0; i < 80; i++) {
                rgb_matrix_set_color(i, 0x64, 0x64, 0x64);
            }
        }
    }
}

// ===========================================
// Main RGB indicator functions
// ===========================================
bool bt_indicators_advanced(uint8_t led_min, uint8_t led_max) {
    // if (kb_light_sleep_flag) {
    //     rgb_matrix_set_color_all(RGB_OFF);
    // }

    bt_bat_query_period();

    if ((dev_info.devs != DEVS_USB) && (gpio_read_pin(MM_CABLE_PIN))) {
        bt_bat_low_level_warning();
    }

    // Show the current keyboard state
    show_current_keyboard_state();

    if (dev_info.devs == DEVS_USB) {
        usb_indicate();
    } else {
        bt_indicate();
        if (gpio_read_pin(MM_CABLE_PIN)) {
            // bt_bat_low_level_warning();
            bt_bat_level_display();
            bt_bat_low_level_shutdown();
        }
    }

#if defined(MM_CABLE_PIN) && defined(MM_CHARGE_PIN)
    // Charging status indicator
    bt_charging_indication();
#endif

    // Factory reset
    factory_reset_indicate();

    // rgb test
    if (rgb_test_en) {
        if (timer_elapsed32(rgb_test_time) >= 1000) {
            rgb_test_time = timer_read32();
            rgb_test_index++;
            if (rgb_test_index > 4) {
                rgb_test_index = 1;
            }
        }

        for (uint8_t i = led_min; i < led_max; i++) {
            rgb_matrix_set_color(i, rgb_test_color_table[rgb_test_index - 1][0], rgb_test_color_table[rgb_test_index - 1][1], rgb_test_color_table[rgb_test_index - 1][2]);
        }
    }

    return true;
}

void bt_housekeeping_task(void) {
#ifdef MULTIMODE_ENABLE
    extern void housekeeping_task_bt(void);
    housekeeping_task_bt();
#endif

#ifdef USB_SUSPEND_CHECK_ENABLE
    static uint32_t usb_suspend_timer = 0;
    static uint32_t usb_suspend       = false;

    if (dev_info.devs == DEVS_USB) {
        if (USB_DRIVER.state != USB_ACTIVE) {
            // USB suspend state
            if (!usb_suspend_timer) {
                // Start timer
                usb_suspend_timer = timer_read32();
            } else if (timer_elapsed32(usb_suspend_timer) > 10000) {
                // Suspend for more than 10 seconds, turn off backlight
                if (!usb_suspend) {
                    // If not in suspend state before, execute suspend operation
                    usb_suspend = true;
                    led_deconfig_all();
                }
                usb_suspend_timer = 0;
            }
        } else {
            // USB active state, reset timer
            if (usb_suspend_timer) {
                usb_suspend_timer = 0;
                if (usb_suspend) {
                    // If previously in suspend state, restore backlight
                    usb_suspend = false;
                    led_config_all();
                }
            }
        }
    } else {
        if (usb_suspend) {
            usb_suspend_timer = 0;
            usb_suspend       = false;
            led_config_all();
        }
    }
#endif
}
