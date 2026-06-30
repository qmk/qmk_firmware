/* Copyright 2023 temp4gh
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "spi_master.h"
#include "host_driver.h"
#include "config.h"

#include "k715_pro.h"
#include "btspi.h"

const is31fl3733_led_t PROGMEM g_is31fl3733_leds[IS31FL3733_LED_COUNT] =
{
    {0, SW7_CS1,    SW9_CS1,    SW8_CS1},
    {0, SW7_CS3,    SW9_CS3,    SW8_CS3},
    {0, SW7_CS4,    SW9_CS4,    SW8_CS4},
    {0, SW7_CS5,    SW9_CS5,    SW8_CS5},
    {0, SW7_CS6,    SW9_CS6,    SW8_CS6},
    {0, SW7_CS7,    SW9_CS7,    SW8_CS7},
    {0, SW7_CS8,    SW9_CS8,    SW8_CS8},
    {0, SW7_CS9,    SW9_CS9,    SW8_CS9},
    {0, SW7_CS10,   SW9_CS10,   SW8_CS10},
    {0, SW7_CS11,   SW9_CS11,   SW8_CS11},
    {0, SW7_CS12,   SW9_CS12,   SW8_CS12},
    {0, SW7_CS13,   SW9_CS13,   SW8_CS13},
    {0, SW7_CS14,   SW9_CS14,   SW8_CS14},
    {0, SW7_CS15,   SW9_CS15,   SW8_CS15},
    {0, SW4_CS1,    SW6_CS1,    SW5_CS1},
    {0, SW4_CS2,    SW6_CS2,    SW5_CS2},
    {0, SW4_CS3,    SW6_CS3,    SW5_CS3},
    {0, SW4_CS4,    SW6_CS4,    SW5_CS4},
    {0, SW4_CS5,    SW6_CS5,    SW5_CS5},
    {0, SW4_CS6,    SW6_CS6,    SW5_CS6},
    {0, SW4_CS7,    SW6_CS7,    SW5_CS7},
    {0, SW4_CS8,    SW6_CS8,    SW5_CS8},
    {0, SW4_CS9,    SW6_CS9,    SW5_CS9},
    {0, SW4_CS10,   SW6_CS10,   SW5_CS10},
    {0, SW4_CS11,   SW6_CS11,   SW5_CS11},
    {0, SW4_CS12,   SW6_CS12,   SW5_CS12},
    {0, SW4_CS13,   SW6_CS13,   SW5_CS13},
    {0, SW4_CS14,   SW6_CS14,   SW5_CS14},
    {0, SW4_CS15,   SW6_CS15,   SW5_CS15},
    {0, SW1_CS1,    SW3_CS1,    SW2_CS1},
    {0, SW1_CS2,    SW3_CS2,    SW2_CS2},
    {0, SW1_CS3,    SW3_CS3,    SW2_CS3},
    {0, SW1_CS4,    SW3_CS4,    SW2_CS4},
    {0, SW1_CS5,    SW3_CS5,    SW2_CS5},
    {0, SW1_CS6,    SW3_CS6,    SW2_CS6},
    {0, SW1_CS7,    SW3_CS7,    SW2_CS7},
    {0, SW1_CS8,    SW3_CS8,    SW2_CS8},
    {0, SW1_CS9,    SW3_CS9,    SW2_CS9},
    {0, SW1_CS10,   SW3_CS10,   SW2_CS10},
    {0, SW1_CS11,   SW3_CS11,   SW2_CS11},
    {0, SW1_CS12,   SW3_CS12,   SW2_CS12},
    {0, SW1_CS13,   SW3_CS13,   SW2_CS13},
    {0, SW1_CS14,   SW3_CS14,   SW2_CS14},
    {0, SW1_CS15,   SW3_CS15,   SW2_CS15},
    {1, SW7_CS1,    SW9_CS1,    SW8_CS1},
    {1, SW7_CS2,    SW9_CS2,    SW8_CS2},
    {1, SW7_CS3,    SW9_CS3,    SW8_CS3},
    {1, SW7_CS4,    SW9_CS4,    SW8_CS4},
    {1, SW7_CS5,    SW9_CS5,    SW8_CS5},
    {1, SW7_CS6,    SW9_CS6,    SW8_CS6},
    {1, SW7_CS7,    SW9_CS7,    SW8_CS7},
    {1, SW7_CS8,    SW9_CS8,    SW8_CS8},
    {1, SW7_CS9,    SW9_CS9,    SW8_CS9},
    {1, SW7_CS10,   SW9_CS10,   SW8_CS10},
    {1, SW7_CS11,   SW9_CS11,   SW8_CS11},
    {1, SW7_CS12,   SW9_CS12,   SW8_CS12},
    {1, SW7_CS13,   SW9_CS13,   SW8_CS13},
    {1, SW7_CS14,   SW9_CS14,   SW8_CS14},
    {1, SW7_CS15,   SW9_CS15,   SW8_CS15},
    {1, SW4_CS1,    SW6_CS1,    SW5_CS1},
    {1, SW4_CS2,    SW6_CS2,    SW5_CS2},
    {1, SW4_CS3,    SW6_CS3,    SW5_CS3},
    {1, SW4_CS4,    SW6_CS4,    SW5_CS4},
    {1, SW4_CS5,    SW6_CS5,    SW5_CS5},
    {1, SW4_CS6,    SW6_CS6,    SW5_CS6},
    {1, SW4_CS7,    SW6_CS7,    SW5_CS7},
    {1, SW4_CS8,    SW6_CS8,    SW5_CS8},
    {1, SW4_CS9,    SW6_CS9,    SW5_CS9},
    {1, SW4_CS10,   SW6_CS10,   SW5_CS10},
    {1, SW4_CS11,   SW6_CS11,   SW5_CS11},
    {1, SW4_CS12,   SW6_CS12,   SW5_CS12},
    {1, SW4_CS13,   SW6_CS13,   SW5_CS13},
    {1, SW4_CS14,   SW6_CS14,   SW5_CS14},
    {1, SW4_CS15,   SW6_CS15,   SW5_CS15},
    {1, SW1_CS1,    SW3_CS1,    SW2_CS1},
    {1, SW1_CS2,    SW3_CS2,    SW2_CS2},
    {1, SW1_CS3,    SW3_CS3,    SW2_CS3},
    {1, SW1_CS5,    SW3_CS5,    SW2_CS5},
    {1, SW1_CS6,    SW3_CS6,    SW2_CS6},
    {1, SW1_CS7,    SW3_CS7,    SW2_CS7},
    {1, SW1_CS8,    SW3_CS8,    SW2_CS8},
    {1, SW1_CS9,    SW3_CS9,    SW2_CS9},
    {1, SW1_CS10,   SW3_CS10,   SW2_CS10},
    {1, SW1_CS11,   SW3_CS11,   SW2_CS11},
    {1, SW1_CS12,   SW3_CS12,   SW2_CS12},
    {1, SW1_CS13,   SW3_CS13,   SW2_CS13},
    {1, SW1_CS14,   SW3_CS14,   SW2_CS14},
    {1, SW1_CS15,   SW3_CS15,   SW2_CS15},
    {0, SW7_CS2,    SW9_CS2,    SW8_CS2},
    {1, SW1_CS4,    SW3_CS4,    SW2_CS4}
};

static void send_ble_hid_report(uint8_t report_type, uint8_t *hid_report_buf, uint8_t data_len)
{
    switch(report_type)
    {
        case BLE_HID_REPORT_TYPE_NORMAL_KEY:
        {
            k715bt_send_spi_extend_single_packet(report_type, hid_report_buf, data_len);
            break;
        }

        case BLE_HID_REPORT_TYPE_EXTRA_KEY:
        {
            k715bt_send_spi_extend_single_packet(report_type, hid_report_buf, data_len);
            break;
        }

        default:
        {
            break;
        }
    }
}

static uint8_t k715_ble_leds(void)
{
    return 0;
}

static void k715_send_keyboard(report_keyboard_t *report)
{
    uint8_t raw_data[KEYBOARD_REPORT_KEYS + 2];

    raw_data[0] = report->mods;
    raw_data[1] = 0;
    for(int i = 0; i < KEYBOARD_REPORT_KEYS; i++)
    {
        raw_data[2 + i] = report->keys[i];
    }

    send_ble_hid_report(BLE_HID_REPORT_TYPE_NORMAL_KEY, raw_data, KEYBOARD_REPORT_KEYS + 2);
}

#ifdef NKRO_ENABLE
static void k715_send_nkro(report_nkro_t *report)
{
    uint8_t raw_data[NKRO_REPORT_BITS + 2];

    raw_data[0] = report->mods;
    raw_data[1] = 0;
    for(int i = 0; i < NKRO_REPORT_BITS; i++)
    {
        raw_data[2 + i] = report->bits[i];
    }

    send_ble_hid_report(BLE_HID_REPORT_TYPE_ALL_KEY, raw_data, NKRO_REPORT_BITS + 2);
}
#endif

static void k715_send_mouse(report_mouse_t *report)
{
}

static void k715_send_extra(report_extra_t *report)
{
    if(report->report_id == REPORT_ID_CONSUMER)
    {
        uint8_t extra_buf[6];

        memset(extra_buf, 0, sizeof(extra_buf));
        memcpy(extra_buf, &report->usage, 2);
        send_ble_hid_report(BLE_HID_REPORT_TYPE_EXTRA_KEY, extra_buf, sizeof(extra_buf));
    }
}

static host_driver_t k715_ble_driver =
{
#ifdef NKRO_ENABLE
    k715_ble_leds, k715_send_keyboard, k715_send_nkro, k715_send_mouse,  k715_send_extra
#else
    k715_ble_leds, k715_send_keyboard, NULL, k715_send_mouse,  k715_send_extra
#endif
};

static bool _swtich_bt_driver(void)
{
    if(host_get_driver() == &k715_ble_driver)
    {
        return false;
    }

    clear_keyboard();

#ifdef NKRO_ENABLE
    keymap_config.nkro = true;
#else
    keymap_config.nkro = false;
#endif

    host_set_driver(&k715_ble_driver);
    return true;
}

void k715bt_bt_swtich_ble_driver(void)
{
    if(is_bt_mode_enabled())
    {
        _swtich_bt_driver();
    }
}

void k715_rgb_matrix_flags_init(void)
{
    rgb_matrix_enable();
    rgb_matrix_set_flags(NORMAL_LED_FLAG_BIT);
}

void k715_bt_init(void)
{
    k715_ble_spi_init();
    k715_rgb_matrix_flags_init();
}

bool led_update_kb(led_t led_state)
{
    bool res = led_update_user(led_state);

    if(res)
    {
        update_caps_led();
    }

    return res;
}

bool process_record_kb_bt(uint16_t keycode, keyrecord_t *record)
{
    static uint8_t chn = 0;

    switch(keycode)
    {
        case BT_CHN1:
        case BT_CHN2:
        case BT_CHN3:
            if(is_bt_mode_enabled())
            {
                if(record->event.pressed)
                {
                    chn = keycode - BT_CHN1 + 1;
                    k715_bt_start_pair(chn);
                }
                else
                {
                    chn = 0;
                }
            }
            break;

        default:
            break;
    }

    return true;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record)
{
    if(!process_record_user(keycode, record))
    {
        return false;
    }

    return process_record_kb_bt(keycode, record);
}

void bluetooth_task(void)
{
    k715bt_bt_swtich_ble_driver();
    check_read_spi_data();
}

void keyboard_post_init_kb(void)
{
    k715_bt_init();
    keyboard_post_init_user();
}
