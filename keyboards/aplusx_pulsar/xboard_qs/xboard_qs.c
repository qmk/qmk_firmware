/* Copyright 2024 Aplusx Inc.
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

#include "xboard_qs.h"

static bool     INIT3S_on = false;
static bool     INIT3S_led_on = false;
static uint16_t INIT3S_timer;           // for custom key, INIT_3S

static bool     kvm_pc_sel      = false;
static uint16_t kvm_timer;
static bool     kvm_sel_on      = false;

static bool isMacMode = false;
static uint8_t Status_LED_Bright;
#define kvm_deadtime    100

typedef union {
    uint32_t raw;
    struct {
        bool    eeprom_kvm_pc_sel :1;
        uint8_t eeprom_Status_LED_Bright;       //
    };
} keyboard_config_t;

keyboard_config_t keyboard_config;

void kvm_switch(bool pc_num){
    gpio_write_pin_high(GPIO_KM_OE);
    gpio_write_pin_low(GPIO_KM_PWEN);
    if (!pc_num) gpio_write_pin_low(GPIO_KM_SEL);
    else   gpio_write_pin_high(GPIO_KM_SEL);
    gpio_write_pin_low(GPIO_KM_OE);

    kvm_timer = timer_read();
    kvm_sel_on = true;
}

void keyboard_pre_init_kb(void) {
    gpio_set_pin_output(GPIO_KM_OE);       // H/W power on default = 0
    gpio_set_pin_output(GPIO_KM_SEL);      // H/W power on default = 0
    gpio_set_pin_output(GPIO_KM_PWEN);     // H/W power on default = 1

    keyboard_pre_init_user();
}

void keyboard_post_init_kb(void) {
    keyboard_config.raw = eeconfig_read_kb();                 // Read the config from EEPROM
    kvm_pc_sel      = keyboard_config.eeprom_kvm_pc_sel;
    kvm_switch(kvm_pc_sel);

    Status_LED_Bright = keyboard_config.eeprom_Status_LED_Bright;   // 0 = 초기값, 1~5 = 50~250의 5단계 밝기
    if (Status_LED_Bright == 0) Status_LED_Bright = 5;

    keyboard_post_init_user();
}

#define HCS(report) host_consumer_send(record->event.pressed ? report : 0); return false
#define HSS(report) host_system_send(record->event.pressed ? report : 0); return false

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) { return false; }
    switch (keycode) {
        case INIT_3S:
            if (record->event.pressed){
                INIT3S_timer = timer_read();
                INIT3S_on    = true;
            }
            else{
                INIT3S_on   = false;
            }
            break;

        case KC_DICTATION:
            HCS(0xCF);
        case KC_DO_NOT_DISTURB:
            HSS(0x9B);
        case KC_LOCK_SCREEN:
            HCS(0x19E);

        case KC_WIN_MODE:
            set_single_persistent_default_layer(0);
            isMacMode = false;
            return false;

        case KC_MAC_MODE:
            set_single_persistent_default_layer(2);
            isMacMode = true;
            return false;

        case KC_TMODE:
            if (record->event.pressed) {
                if (get_highest_layer(layer_state|default_layer_state) >= 2) {
                    set_single_persistent_default_layer(2);
                    isMacMode = true;
                } else {
                    set_single_persistent_default_layer(0);
                    isMacMode = false;
                }
            }
            return false;

        case KC_PC1:
            if (record->event.pressed) {
                if (kvm_pc_sel) {
                    kvm_pc_sel = 0;
                    kvm_switch(0);

                    keyboard_config.eeprom_kvm_pc_sel = kvm_pc_sel;
                    eeconfig_update_kb(keyboard_config.raw); // Writes the new status to EEPROM
                }
            }
            return false;

        case KC_PC2:
            if (record->event.pressed) {
                if (!kvm_pc_sel){
                    kvm_pc_sel = 1;
                    kvm_switch(1);

                    keyboard_config.eeprom_kvm_pc_sel = kvm_pc_sel;
                    eeconfig_update_kb(keyboard_config.raw); // Writes the new status to EEPROM
                }
            }
            return false;

        case KC_TPC:
            if (record->event.pressed) {
                kvm_pc_sel = !kvm_pc_sel;
                if (kvm_pc_sel) kvm_switch(1);
                else kvm_switch(0);
                keyboard_config.eeprom_kvm_pc_sel = kvm_pc_sel; //
                eeconfig_update_kb(keyboard_config.raw); // Writes the new status to EEPROM
            }
            return false;

        case KC_S_LED:                                  // Change Status LED Brightness
            if (record->event.pressed) {
                if (++Status_LED_Bright > 5) {
                    Status_LED_Bright = 1;
                };
                keyboard_config.eeprom_Status_LED_Bright = Status_LED_Bright; //
                eeconfig_update_kb(keyboard_config.raw); // Writes the new status to EEPROM
            }
            return false;

        default:
            return true;   // Process all other keycodes normally
    }
    return true;
}

bool isRecording = false;           // dynamic macro REC. LED
bool isRecordingLedOn = false;
static uint16_t recording_timer;

void housekeeping_task_kb(void) {

    if (kvm_sel_on == true){
        if (timer_elapsed(kvm_timer) > kvm_deadtime ) {
            gpio_write_pin_high(GPIO_KM_PWEN);
            kvm_sel_on = false;                             //// 키보드 리셋이 필요?
        }
    }

    if (INIT3S_on == true){
        if (timer_elapsed(INIT3S_timer) > 3000){
            INIT3S_on = false;
            INIT3S_led_on = true;
            INIT3S_timer = timer_read();
        }
    }
    if (INIT3S_led_on == true){
        if(timer_elapsed(INIT3S_timer) > 2000){
            eeconfig_init();
            soft_reset_keyboard();
        }
    }

    if (isRecording){
        if(timer_elapsed(recording_timer) > 500)
        {
            isRecordingLedOn = !isRecordingLedOn;
            recording_timer  = timer_read();
        }
    }
}

#ifdef DYNAMIC_MACRO_ENABLE
__attribute__((weak)) void dynamic_macro_record_start_user(int8_t direction) {
    isRecording = true;
    isRecordingLedOn = true;
    recording_timer = timer_read();
}
__attribute__((weak)) void dynamic_macro_record_end_user(int8_t direction) {
    isRecording = false;
    isRecordingLedOn = false;
}
#endif

bool rgb_matrix_indicators_kb(void)  {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }

    uint8_t Status_LED_Bright_value = Status_LED_Bright * 50;

    led_t host_leds = host_keyboard_led_state();

    if (host_leds.caps_lock) {
        rgb_matrix_set_color(72, Status_LED_Bright_value, Status_LED_Bright_value, Status_LED_Bright_value);
    }
    if (host_leds.scroll_lock) {
        rgb_matrix_set_color(22, Status_LED_Bright_value, Status_LED_Bright_value, Status_LED_Bright_value);
    }

    if (INIT3S_led_on == true){         // Factory Reset ; all LED is RED
        rgb_matrix_set_color_all(0xff, 0, 0);
    }

    if (keymap_config.no_gui){                // WIN key Lock
        rgb_matrix_set_color(99, Status_LED_Bright_value, Status_LED_Bright_value, Status_LED_Bright_value);
    }

    if (isRecordingLedOn) {             // Dynamic Macro Recording LED Blink
        rgb_matrix_set_color(38, Status_LED_Bright_value, Status_LED_Bright_value, Status_LED_Bright_value);
    }

    if (get_highest_layer(layer_state|default_layer_state) >= 2) {
        rgb_matrix_set_color(24,Status_LED_Bright_value,0,0);       // WIN-MAC key
        isMacMode = true;

        if (kvm_pc_sel)  rgb_matrix_set_color(103,Status_LED_Bright_value,0,0);     // MAC Mode & PC2
        else            rgb_matrix_set_color(101,Status_LED_Bright_value,0,0);      // MAC Mode & PC1

    } else {
        rgb_matrix_set_color(24,0,0,Status_LED_Bright_value);       // WIN-MAC key
        isMacMode = false;

        if (kvm_pc_sel)  rgb_matrix_set_color(103,0,0,Status_LED_Bright_value);       // Windows Mode & PC2
        else            rgb_matrix_set_color(101,0,0,Status_LED_Bright_value);        // Windows Mode & PC1
    }

    return false; // return TRUE;
}
