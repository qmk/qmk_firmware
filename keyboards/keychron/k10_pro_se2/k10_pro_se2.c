/* Copyright 2024 @ Keychron (https://www.keychron.com)
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

#include "quantum.h"
#include "keychron_task.h"
#ifdef FACTORY_TEST_ENABLE
#    include "factory_test.h"
#    include "keychron_common.h"
#endif
#ifdef LK_WIRELESS_ENABLE
#    include "lkbt51.h"
#    include "wireless.h"
#    include "transport.h"
#    include "keychron_wireless_common.h"
#    include "battery.h"
#endif

#define POWER_ON_LED_DURATION 3000
static uint32_t power_on_indicator_timer;

#ifdef LK_WIRELESS_ENABLE
pin_t bt_led_pins[]   = BT_HOST_LED_PIN_LIST;
pin_t p24g_led_pins[] = P24G_HOST_LED_PIN_LIST;
#endif

bool dip_switch_update_kb(uint8_t index, bool active) {
    if (index == 0) {
        default_layer_set(1UL << (active ? 0 : 2));
    }
    dip_switch_update_user(index, active);

    return true;
}

void keyboard_post_init_kb(void) {
#ifdef LK_WIRELESS_ENABLE
    palSetLineMode(BT_MODE_SELECT_PIN, PAL_MODE_INPUT);
#    ifdef P2P4_MODE_SELECT_PIN
    palSetLineMode(P2P4_MODE_SELECT_PIN, PAL_MODE_INPUT);
#    elif defined(USB_MODE_SELECT_PIN)
    palSetLineMode(USB_MODE_SELECT_PIN, PAL_MODE_INPUT);
#    endif

    lkbt51_init(false);
    wireless_init();
#endif

    power_on_indicator_timer = timer_read32();
    keyboard_post_init_user();
}

bool keychron_task_kb(void) {
    if (power_on_indicator_timer) {
        if (timer_elapsed32(power_on_indicator_timer) > POWER_ON_LED_DURATION) {
            power_on_indicator_timer = 0;

            if (!host_keyboard_led_state().caps_lock) writePin(LED_CAPS_LOCK_PIN, !LED_PIN_ON_STATE);
#ifdef LK_WIRELESS_ENABLE
            writePin(BAT_LOW_LED_PIN, !BAT_LOW_LED_PIN_ON_STATE);
            writePin(COMMON_BT_LED_PIN, !COMMON_BT_LED_PIN_ON_STATE);
            writePin(COMMON_P24G_LED_PIN, !COMMON_BT_LED_PIN_ON_STATE);
            if (get_transport() == TRANSPORT_USB) {
                for (uint8_t i = 0; i < sizeof(bt_led_pins) / sizeof(pin_t); i++)
                    writePin(bt_led_pins[i], !HOST_LED_PIN_ON_STATE);
                for (uint8_t i = 0; i < sizeof(p24g_led_pins) / sizeof(pin_t); i++)
                    writePin(p24g_led_pins[i], !HOST_LED_PIN_ON_STATE);
            }
#endif
        } else {
            writePin(LED_CAPS_LOCK_PIN, LED_PIN_ON_STATE);
#ifdef LK_WIRELESS_ENABLE
            writePin(BAT_LOW_LED_PIN, BAT_LOW_LED_PIN_ON_STATE);
            switch (get_transport()) {
                case TRANSPORT_P2P4:
                    writePin(COMMON_P24G_LED_PIN, COMMON_BT_LED_PIN_ON_STATE);
                    break;
                case TRANSPORT_BLUETOOTH:
                    writePin(COMMON_BT_LED_PIN, COMMON_BT_LED_PIN_ON_STATE);
                    break;
                default:
                    writePin(COMMON_P24G_LED_PIN, COMMON_BT_LED_PIN_ON_STATE);
                    writePin(COMMON_BT_LED_PIN, COMMON_BT_LED_PIN_ON_STATE);
                    for (uint8_t i = 0; i < sizeof(bt_led_pins) / sizeof(pin_t); i++)
                        writePin(bt_led_pins[i], HOST_LED_PIN_ON_STATE);
                    for (uint8_t i = 0; i < sizeof(p24g_led_pins) / sizeof(pin_t); i++)
                        writePin(p24g_led_pins[i], HOST_LED_PIN_ON_STATE);
                    break;
            }
#endif
        }
    }

    return true;
}

#ifdef LK_WIRELESS_ENABLE
bool lpm_is_kb_idle(void) {
    return power_on_indicator_timer == 0 && !factory_reset_indicating();
}
#endif
#if 0
bool wireless_pre_task_kb(void) {
#    ifdef TRANSPORT_SOFT_SWITCH_ENABLE
    if (get_transport() == 0) {
        uint8_t mode = eeprom_read_transport();
        if (mode == 0) {
            mode = TRANSPORT_USB;
            eeprom_update_transport(mode);
        }

        set_transport(mode);
    }
#    else
    static uint8_t  dip_switch_state = 0;
    static uint32_t time             = 0;

    if (time == 0) {
        uint8_t pins_state = (readPin(BT_MODE_SELECT_PIN) << 1)
#        ifdef P2P4_MODE_SELECT_PIN
                             | readPin(P2P4_MODE_SELECT_PIN)
#        elif defined(USB_MODE_SELECT_PIN)
                             | readPin(USB_MODE_SELECT_PIN)
#        endif
            ;

        if (pins_state != dip_switch_state) {
            dip_switch_state = pins_state;
            time             = timer_read32();
        }
    }

    if ((time && timer_elapsed32(time) > 100) || get_transport() == TRANSPORT_NONE) {
        uint8_t pins_state = (readPin(BT_MODE_SELECT_PIN) << 1)
#        ifdef P2P4_MODE_SELECT_PIN
                             | readPin(P2P4_MODE_SELECT_PIN)
#        elif defined(USB_MODE_SELECT_PIN)
                             | readPin(USB_MODE_SELECT_PIN)
#        endif
            ;

        if (pins_state == dip_switch_state) {
            time = 0;

            switch (dip_switch_state) {
                case 0x01:
                    set_transport(TRANSPORT_BLUETOOTH);
                    break;
                case 0x02:
#        ifdef P2P4_MODE_SELECT_PIN
                    set_transport(TRANSPORT_P2P4);
#        elif defined(USB_MODE_SELECT_PIN)
                    set_transport(TRANSPORT_USB);
#        endif
                    break;
                case 0x03:
#        ifdef P2P4_MODE_SELECT_PIN
                    set_transport(TRANSPORT_USB);
#        endif
                    break;
                default:
                    break;
            }
        } else {
            dip_switch_state = pins_state;
            time             = timer_read32();
        }
    }
#    endif
    return false;
}
#endif
#if 0
void wireless_pre_task(void) {
    static uint8_t  dip_switch_state = 0;
    static uint32_t time             = 0;

    if (time == 0) {
        uint8_t pins_state = (readPin(BT_MODE_SELECT_PIN) << 1);

        if (pins_state != dip_switch_state) {
            dip_switch_state = pins_state;
            time             = timer_read32();
        }
    }

    if ((time && timer_elapsed32(time) > 100) || get_transport() == TRANSPORT_NONE) {
        uint8_t pins_state = (readPin(BT_MODE_SELECT_PIN) << 1);

        if (pins_state == dip_switch_state) {
            time = 0;

            if (pins_state == 0)
                set_transport(TRANSPORT_BLUETOOTH);
            else
                set_transport(TRANSPORT_USB);
        } else {
            dip_switch_state = pins_state;
            time             = timer_read32();
        }
    }
}
#endif
