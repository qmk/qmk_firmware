/* Copyright 2022 Basic I/O Instruments (Scott Wei)
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

#include "action.h"
#include "host.h"
#include "host_driver.h"
#include "keyboard.h"
#include "led.h"
#include "report.h"
#include <avr/pgmspace.h>

#include "debug.h"
#include "sendchar.h"
#ifdef SLEEP_LED_ENABLE
#    include "sleep_led.h"
#endif
#include "suspend.h"

#include "command.h"
#include "lufa.h"
#include "quantum.h"
#include "usb_descriptor.h"
#include <util/atomic.h>

#include "print.h"

#include "ble.h"
#include "usart.h"

#define BATT_FULL 912
#define BATT_EMPTY 796

#define BUFF_SIZE 25

#ifdef BLE_NAME
#    define AT_NAME_CMD "AT+GAPDEVNAME=" BLE_NAME "\r\n"
#else
#    define AT_NAME_CMD "AT+GAPDEVNAME=BIOI BLE DEVICE\r\n"
#endif

keyboard_config_t kb_config;

bool force_ble = false;

static uint8_t bluefruit_keyboard_leds = 0;

static void bluefruit_serial_send(uint8_t);

void send_str(const char *str) {
    uint8_t c;
    while ((c = pgm_read_byte(str++)))
        uart1_putc(c);
}

void uart_getln(char *buffer, uint8_t bufferlimit) {
    while (--bufferlimit) {
        *buffer = uart1_getc();
        if (*buffer == '\r' || *buffer == '\n') {
            break;
        }
        buffer++;
    }
    *buffer = 0;
    uart1_flush();
}

void serial_send(uint8_t data) {
    dprintf("Sending: %u\n", data);
}

void send_bytes(uint8_t data) {
    char hexStr[3];
    sprintf(hexStr, "%02X", data);
    for (int j = 0; j < 2; j++) {
        uart1_putc(hexStr[j]);
    }
}

#ifdef BLUEFRUIT_TRACE_SERIAL
static void bluefruit_trace_header(void) {
    dprintf("+------------------------------------+\n");
    dprintf("| HID report to Bluefruit via serial |\n");
    dprintf("+------------------------------------+\n|");
}

static void bluefruit_trace_footer(void) {
    dprintf("|\n+------------------------------------+\n\n");
}
#endif

static void bluefruit_serial_send(uint8_t data) {
#ifdef BLUEFRUIT_TRACE_SERIAL
    dprintf(" ");
    debug_hex8(data);
    dprintf(" ");
#endif
    serial_send(data);
}

/*------------------------------------------------------------------*
 * Host driver
 *------------------------------------------------------------------*/

static uint8_t keyboard_leds(void);
static void    send_keyboard(report_keyboard_t *report);
static void    send_mouse(report_mouse_t *report);

// host_driver_t struct changed since the VIA_PROTOCOL_VERSION 0x000B

#if VIA_PROTOCOL_VERSION < 0x000B
static void   send_system(uint16_t data);
static void   send_consumer(uint16_t data);
host_driver_t bluefruit_driver = {keyboard_leds, send_keyboard, send_mouse, send_system, send_consumer};
#elif VIA_PROTOCOL_VERSION >= 0x000B
static void   send_extra(report_extra_t *report);
host_driver_t bluefruit_driver = {keyboard_leds, send_keyboard, send_mouse, send_extra};
#endif

host_driver_t null_driver = {};

static uint8_t keyboard_leds(void) {
    return bluefruit_keyboard_leds;
}

static void send_keyboard(report_keyboard_t *report) {
#ifdef BLUEFRUIT_TRACE_SERIAL
    bluefruit_trace_header();
#endif

    send_str(PSTR("AT+BLEKEYBOARDCODE="));

#ifdef CONSOLE_ENABLE
    uprint_hex8(report->raw[0]);
#endif

    send_bytes(report->raw[0]);

#ifdef CONSOLE_ENABLE
    uprintf("-");
#endif

    send_str(PSTR("-"));

#ifdef CONSOLE_ENABLE
    uprint_hex8(report->raw[1]);
#endif

    send_bytes(report->raw[1]);

    for (uint8_t i = 2; i < KEYBOARD_EPSIZE; i++) {
        if (report->raw[i] != 0) {
#ifdef CONSOLE_ENABLE
            uprintf("-");
#endif
            send_str(PSTR("-"));
#ifdef CONSOLE_ENABLE
            uprint_hex8(report->raw[i]);
#endif
            send_bytes(report->raw[i]);
        }
    }

#ifdef CONSOLE_ENABLE
    uprintf("\r\n");
#endif
    send_str(PSTR("\r\n"));

#ifdef BLUEFRUIT_TRACE_SERIAL
    bluefruit_trace_footer();
#endif
}

static void send_mouse(report_mouse_t *report) {
#ifdef BLUEFRUIT_TRACE_SERIAL
    bluefruit_trace_header();
#endif
    bluefruit_serial_send(0xFD);
    bluefruit_serial_send(0x00);
    bluefruit_serial_send(0x03);
    bluefruit_serial_send(report->buttons);
    bluefruit_serial_send(report->x);
    bluefruit_serial_send(report->y);
    bluefruit_serial_send(report->v); // should try sending the wheel v here
    bluefruit_serial_send(report->h); // should try sending the wheel h here
    bluefruit_serial_send(0x00);
#ifdef BLUEFRUIT_TRACE_SERIAL
    bluefruit_trace_footer();
#endif
}

#if VIA_PROTOCOL_VERSION < 0x000B

static void send_extra(uint8_t report_id, uint16_t data) {
    uprint_hex8(data);
    uprintf("\r\n");
    char hexStr[9];
    sprintf(hexStr, "%04X", data);
    send_str(PSTR("AT+BLEHIDCONTROLKEY=0x"));
    for (int j = 0; j < sizeof(hexStr) - 1; j++) {
        uart1_putc(hexStr[j]);
    }
    send_str(PSTR("\r\n"));
    uprintf("%s \r\n", hexStr);
}

static void send_system(uint16_t data) {
#    ifdef EXTRAKEY_ENABLE
    send_extra(REPORT_ID_SYSTEM, data);
#    endif
}

static void send_consumer(uint16_t data) {
#    ifdef EXTRAKEY_ENABLE
    send_extra(REPORT_ID_SYSTEM, data);
#    endif
}

#elif VIA_PROTOCOL_VERSION >= 0x000B
static void   send_extra(report_extra_t *report) {
    uprint_hex8(report->usage);
    uprintf("\r\n");
    char hexStr[9];
    sprintf(hexStr, "%04X", report->usage);
    send_str(PSTR("AT+BLEHIDCONTROLKEY=0x"));
    for (int j = 0; j < sizeof(hexStr) - 1; j++) {
        uart1_putc(hexStr[j]);
    }
    send_str(PSTR("\r\n"));
    uprintf("%s \r\n", hexStr);
}
#endif

void ble_clear_keyboard(void) {
    send_str(PSTR("AT+BLEKEYBOARDCODE=00-00\r\n"));
    wait_ms(5);
    send_str(PSTR("AT+BLEKEYBOARDCODE=00-00\r\n"));
    wait_ms(5);
    send_str(PSTR("AT+BLEKEYBOARDCODE=00-00\r\n"));
    wait_ms(5);
    send_str(PSTR("\r\n"));
    send_str(PSTR("\r\n"));
    send_str(PSTR("\r\n"));
}

void enable_ble_batt(void) {
    send_str(PSTR("AT+BLEBATTEN=1\r\n"));
    wait_ms(100);
    send_str(PSTR("ATZ\r\n"));
    wait_ms(100);
}

void reset_ble_batt(void) {
#ifdef CONSOLE_ENABLE
    print("Resetting BLE Battery Level\r\n");
#endif
    send_str(PSTR("AT+BLEBATTVAL=100\r\n"));
    wait_ms(100);
}

void update_ble_batt(void) {
    int vbat = 0;
    int pbat = 0;

    char vbat_adc[BUFF_SIZE];
    vbat_adc[0] = '\0';

    char bat_val[8];
    bat_val[0] = '\0';

    send_str(PSTR("AT+HWADC=6\r\n"));
    uart_getln(vbat_adc, BUFF_SIZE);

    vbat     = atoi(vbat_adc);
    double p = (double)(vbat - BATT_EMPTY) * 100 / (BATT_FULL - BATT_EMPTY);
    pbat     = (int)p;

    if (pbat > 0) {
        sprintf(bat_val, "%d", pbat);
    } else {
        // Process unexpected value
    }

    char bat_cmd[BUFF_SIZE] = "AT+BLEBATTVAL=";
    strcat(bat_cmd, bat_val);
    strcat(bat_cmd, "\r\n\0");

#ifdef CONSOLE_ENABLE
    print("Updating BLE battery level\r\n");
    uprintf("vbat_adc %s  \r\n", vbat_adc);
    uprintf("vbat: %d  \r\n", vbat);
    uprintf("pbat: %d  \r\n", pbat);
    uprintf("bat_val: %s  \r\n", bat_val);
    uprintf("AT_CMD: %s  \r\n", bat_cmd);
#endif

    uart1_puts(bat_cmd);
    wait_ms(200);
}

void module_disconnect(void) {
    send_str(PSTR("AT+GAPDISCONNECT\r\n"));
    wait_ms(100);
    send_str(PSTR("AT+GAPDISCONNECT\r\n"));
    wait_ms(100);
}

void module_delbonds(void) {
    send_str(PSTR("AT+GAPDELBONDS\r\n"));
    wait_ms(100);
    send_str(PSTR("AT+GAPDELBONDS\r\n"));
    wait_ms(100);
    send_str(PSTR("ATZ\r\n"));
    wait_ms(500);
}

void rgb_power_off(void) {
#ifdef RGB_BL_CONTROL_PIN
    setPinOutput(RGB_UG_CONTROL_PIN);
    writePinLow(RGB_BL_CONTROL_PIN);
#endif
#ifdef RGB_UG_CONTROL_PIN
    setPinOutput(RGB_UG_CONTROL_PIN);
    writePinHigh(RGB_UG_CONTROL_PIN);
#endif
#ifdef BIOI_HARPE65
    send_str(PSTR("AT+HWGPIOMODE=19,1\r\n"));
    wait_ms(50);
    send_str(PSTR("AT+HWGPIOMODE=19,1\r\n"));
    wait_ms(50);
    send_str(PSTR("AT+HWGPIO=19,0\r\n"));
    wait_ms(50);
    send_str(PSTR("AT+HWGPIO=19,0\r\n"));
    wait_ms(50);
#endif
}

void rgb_logical_off(void) {
#if defined(RGBLIGHT_ENABLE)
    rgblight_disable();
#endif
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_disable();
#endif
}

void rgb_power_on(void) {
#ifdef BIOI_MANTA
    rgblight_enable();
#endif
#ifdef RGB_BL_CONTROL_PIN
    setPinOutput(RGB_UG_CONTROL_PIN);
    writePinHigh(RGB_BL_CONTROL_PIN);
#endif
#ifdef RGB_UG_CONTROL_PIN
    setPinOutput(RGB_UG_CONTROL_PIN);
    writePinLow(RGB_UG_CONTROL_PIN);
#endif
#ifdef BIOI_HARPE65
    send_str(PSTR("AT+HWGPIOMODE=19,1\r\n"));
    wait_ms(50);
    send_str(PSTR("AT+HWGPIOMODE=19,1\r\n"));
    wait_ms(50);
    send_str(PSTR("AT+HWGPIO=19,1\r\n"));
    wait_ms(50);
    send_str(PSTR("AT+HWGPIO=19,1\r\n"));
    wait_ms(50);
#endif
}

void rgb_logical_on(void) {
#if defined(RGBLIGHT_ENABLE)
    rgblight_enable();
#endif
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_enable();
#endif
}

void force_rgb_off(void) {
    rgb_logical_off();
    rgb_power_off();
    kb_config.raw       = eeconfig_read_kb();
    kb_config.rgb_power = 0;
    eeconfig_update_kb(kb_config.raw);
}

void force_rgb_on(void) {
    rgb_logical_on();
    rgb_power_on();
    kb_config.raw       = eeconfig_read_kb();
    kb_config.rgb_power = 1;
    eeconfig_update_kb(kb_config.raw);
}

void skog_reboot_rgb_strip_only(void) {
    // Reserved function for SKOG Reboot
#if defined(RGBLIGHT_ENABLE)
    rgblight_set_clipping_range(0, 5);
    rgblight_setrgb_range(0, 0, 0, 5, 9);
#endif
}

void skog_reboot_rgb_logo_only(void) {
    // Reserved function for SKOG Reboot
#if defined(RGBLIGHT_ENABLE)
    rgblight_set_clipping_range(4, 5);
    rgblight_setrgb_range(0, 0, 0, 0, 4);
#endif
}

void module_reset(void) {
    // Do resetting twice
    for (int i = 0; i < 2; i++) {
        send_str(PSTR("\r\n"));
        wait_ms(100);
        send_str(PSTR("AT+BAUDRATE=9600\r\n"));
        wait_ms(100);
        uart1_init(UART_BAUD_SELECT_DOUBLE_SPEED(115200, 8000000L));
        send_str(PSTR("\r\n"));
        send_str(PSTR("\r\n"));
        send_str(PSTR("\r\n"));
        wait_ms(100);
        send_str(PSTR("AT+BAUDRATE=9600\r\n"));
        wait_ms(100);

        // Try setting baudrate back to 9600 for those module was set to 76800
        uart1_init(UART_BAUD_SELECT_DOUBLE_SPEED(76800, 8000000L));
        send_str(PSTR("\r\n"));
        wait_ms(100);
        send_str(PSTR("AT+BAUDRATE=9600\r\n"));
        wait_ms(100);

        // Try setting baudrate back to 9600 for those module was set to 57600
        uart1_init(UART_BAUD_SELECT_DOUBLE_SPEED(57600, 8000000L));
        send_str(PSTR("\r\n"));
        wait_ms(100);
        send_str(PSTR("AT+BAUDRATE=9600\r\n"));
        wait_ms(100);

        // Try setting baudrate back to 9600 for those module was set to 34800
        uart1_init(UART_BAUD_SELECT_DOUBLE_SPEED(38400, 8000000L));
        send_str(PSTR("\r\n"));
        wait_ms(100);
        send_str(PSTR("AT+BAUDRATE=9600\r\n"));
        wait_ms(100);
    }

    uart1_init(UART_BAUD_SELECT_DOUBLE_SPEED(9600, 8000000L));
    send_str(PSTR("\r\n"));
    wait_ms(100);
    send_str(PSTR("\r\n"));
    wait_ms(100);
    send_str(PSTR("\r\n"));
    wait_ms(100);
    send_str(PSTR("AT+FACTORYRESET\r\n"));
    wait_ms(500);

    // Do initializing twice
    for (int i = 0; i < 2; i++) {
        send_str(PSTR("ATE=0\r\n"));
        wait_ms(100);
        send_str(PSTR("AT+HWGPIOMODE=5,0\r\n"));
        wait_ms(100);
        send_str(PSTR("AT+BLEHIDEN=1\r\n"));
        wait_ms(100);
#ifndef NO_BAT_LEVEL
        send_str(PSTR("AT+BLEBATTEN=1\r\n"));
        wait_ms(100);
#endif
        send_str(PSTR("AT+BLEKEYBOARDEN=1\r\n"));
        wait_ms(100);

        send_str(PSTR("AT+BLEPOWERLEVEL=4\r\n"));
        wait_ms(100);
        send_str(PSTR("AT+HWMODELED=DISABLE\r\n"));
        wait_ms(100);
    }
    wait_ms(100);
    send_str(PSTR(AT_NAME_CMD));
    wait_ms(100);
    send_str(PSTR("ATZ\r\n"));
    wait_ms(500);
    for (int i = 0; i < 2; i++) {
        send_str(PSTR("AT+BAUDRATE=76800\r\n"));
        wait_ms(250);
    }

    uart1_init(UART_BAUD_SELECT_DOUBLE_SPEED(76800, 8000000L));
    wait_ms(250);
}

void usart_init(void) {
    uart1_init(UART_BAUD_SELECT_DOUBLE_SPEED(76800, 8000000L));
    wait_ms(250);

    send_str(PSTR("\r\n"));
    send_str(PSTR("\r\n"));
    send_str(PSTR("\r\n"));
}

bool command_extra(uint8_t code) {
    switch (code) {
        case KC_R:
            module_reset();
            return true;
        case KC_X:
            // Need more test here
            // module_disconnect();
            // module_delbonds();
            return true;
#ifndef NO_BAT_LEVEL
        case KC_V:
            update_ble_batt();
            return true;
#endif
        case KC_B:
            force_ble = !force_ble;
            return true;
        case KC_G:
            force_rgb_off();
            return true;
        case KC_H:
            force_rgb_on();
            return true;
        case KC_LBRC:
            skog_reboot_rgb_strip_only();
            return true;
        case KC_RBRC:
            skog_reboot_rgb_logo_only();
            return true;
        default:
            return false;
    }
}
