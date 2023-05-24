/*
Copyright 2019 Basic I/O Instruments(Scott Wei) <scot.wei@gmail.com>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <avr/pgmspace.h>
#include "report.h"
#include "host.h"
#include "host_driver.h"
#include "keyboard.h"
#include "action.h"
#include "led.h"

#include "sendchar.h"
#include "debug.h"
#ifdef SLEEP_LED_ENABLE
#include "sleep_led.h"
#endif
#include "suspend.h"

#include "usb_descriptor.h"
#include "lufa.h"
#include "quantum.h"
#include <util/atomic.h>

#include "print.h"

#include "ble.h"
#include "usart.h"

keyboard_config_t ble_config;

static uint8_t bluefruit_keyboard_leds = 0;

static void bluefruit_serial_send(uint8_t);

void send_str(const char *str)
{
    uint8_t c;
    while ((c = pgm_read_byte(str++)))
        uart1_putc(c);
}

void serial_send(uint8_t data)
{
    dprintf("Sending: %u\n", data);
}

void send_bytes(uint8_t data)
{
    char hexStr[3];
    sprintf(hexStr, "%02X", data);
    for (int j = 0; j < sizeof(hexStr) - 1; j++)
    {
        uart1_putc(hexStr[j]);
    }
}

#ifdef BLUEFRUIT_TRACE_SERIAL
static void bluefruit_trace_header(void)
{
    dprintf("+------------------------------------+\n");
    dprintf("| HID report to Bluefruit via serial |\n");
    dprintf("+------------------------------------+\n|");
}

static void bluefruit_trace_footer(void)
{
    dprintf("|\n+------------------------------------+\n\n");
}
#endif

static void bluefruit_serial_send(uint8_t data)
{
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
static void send_keyboard(report_keyboard_t *report);
static void send_mouse(report_mouse_t *report);
static void send_system(uint16_t data);
static void send_consumer(uint16_t data);

host_driver_t bluefruit_driver = {
    keyboard_leds,
    send_keyboard,
    send_mouse,
    send_system,
    send_consumer};

host_driver_t null_driver = {};

static uint8_t keyboard_leds(void)
{
    return bluefruit_keyboard_leds;
}

static void send_keyboard(report_keyboard_t *report)
{
#ifdef BLUEFRUIT_TRACE_SERIAL
    bluefruit_trace_header();
#endif
    dprintf("Sending...\n");

    send_str(PSTR("AT+BLEKEYBOARDCODE="));

    for (uint8_t i = 0; i < KEYBOARD_EPSIZE; i++)
    {
        send_bytes(report->raw[i]);
        if (i < (KEYBOARD_EPSIZE - 1))
        {
            send_str(PSTR("-"));
        }
    }

    send_str(PSTR("\r\n"));
#ifdef BLUEFRUIT_TRACE_SERIAL
    bluefruit_trace_footer();
#endif
}

static void send_mouse(report_mouse_t *report)
{
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

static void send_system(uint16_t data)
{
}

/*
+-----------------+-------------------+-------+
| Consumer Key    | Bit Map           | Hex   |
+-----------------+-------------------+-------+
| Home            | 00000001 00000000 | 01 00 |
| KeyboardLayout  | 00000010 00000000 | 02 00 |
| Search          | 00000100 00000000 | 04 00 |
| Snapshot        | 00001000 00000000 | 08 00 |
| VolumeUp        | 00010000 00000000 | 10 00 |
| VolumeDown      | 00100000 00000000 | 20 00 |
| Play/Pause      | 01000000 00000000 | 40 00 |
| Fast Forward    | 10000000 00000000 | 80 00 |
| Rewind          | 00000000 00000001 | 00 01 |
| Scan Next Track | 00000000 00000010 | 00 02 |
| Scan Prev Track | 00000000 00000100 | 00 04 |
| Random Play     | 00000000 00001000 | 00 08 |
| Stop            | 00000000 00010000 | 00 10 |
+-------------------------------------+-------+
*/
#define CONSUMER2BLUEFRUIT(usage) \
    (usage == AUDIO_MUTE ? 0x00e2 : (usage == AUDIO_VOL_UP ? 0x00e9 : (usage == AUDIO_VOL_DOWN ? 0x00ea : (usage == TRANSPORT_NEXT_TRACK ? 0x00b5 : (usage == TRANSPORT_PREV_TRACK ? 0x00b6 : (usage == TRANSPORT_STOP ? 0x00b7 : (usage == TRANSPORT_STOP_EJECT ? 0x00b8 : (usage == TRANSPORT_PLAY_PAUSE ? 0x00b1 : (usage == AL_CC_CONFIG ? 0x0183 : (usage == AL_EMAIL ? 0x018c : (usage == AL_CALCULATOR ? 0x0192 : (usage == AL_LOCAL_BROWSER ? 0x0196 : (usage == AC_SEARCH ? 0x021f : (usage == AC_HOME ? 0x0223 : (usage == AC_BACK ? 0x0224 : (usage == AC_FORWARD ? 0x0225 : (usage == AC_STOP ? 0x0226 : (usage == AC_REFRESH ? 0x0227 : (usage == AC_BOOKMARKS ? 0x022a : 0)))))))))))))))))))

static void send_consumer(uint16_t data)
{
    static uint16_t last_data = 0;
    if (data == last_data)
        return;
    last_data = data;

    uint16_t bitmap = CONSUMER2BLUEFRUIT(data);

#ifdef BLUEFRUIT_TRACE_SERIAL
    dprintf("\nData: ");
    debug_hex16(data);
    dprintf("; bitmap: ");
    debug_hex16(bitmap);
    dprintf("\n");
    bluefruit_trace_header();
#endif
    send_str(PSTR("AT+BLEHIDCONTROLKEY=0x"));
    send_bytes((bitmap >> 8) & 0xFF);
    send_bytes(bitmap & 0xFF);
    send_str(PSTR("\r\n"));
#ifdef BLUEFRUIT_TRACE_SERIAL
    bluefruit_trace_footer();
#endif
}

void usart_init(void)
{
    uart1_init(UART_BAUD_SELECT_DOUBLE_SPEED(76800, 8000000L));
    wait_ms(250);

    send_str(PSTR("\r\n"));
    send_str(PSTR("\r\n"));
    send_str(PSTR("\r\n"));
}
