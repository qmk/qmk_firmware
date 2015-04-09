/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>
//#include <avr/wdt.h>
#include "wd.h" // in order to use watchdog in interrupt mode
#include <avr/sleep.h>
#include <util/delay.h>
#include <avr/power.h>
#include "keyboard.h"
#include "matrix.h"
#include "host.h"
#include "action.h"
#include "iwrap.h"
#ifdef PROTOCOL_VUSB
#   include "vusb.h"
#   include "usbdrv.h"
#endif
#include "uart.h"
#include "suart.h"
#include "timer.h"
#include "debug.h"
#include "keycode.h"
#include "command.h"


static void sleep(uint8_t term);
static bool console(void);
static bool console_command(uint8_t c);
static uint8_t key2asc(uint8_t key);


/*
static void set_prr(void)
{
    power_adc_disable();
    power_spi_disable();
    power_twi_disable();
#ifndef TIMER_H
    //power_timer0_disable(); // used in timer.c
#endif
    power_timer1_disable();
    power_timer2_disable();
}
*/

/*
static void pullup_pins(void)
{
    // DDRs are set to 0(input) by default.
#ifdef PORTA
    PORTA = 0xFF;
#endif
    PORTB = 0xFF;
    PORTC = 0xFF;
    PORTD = 0xFF;
#ifdef PORTE
    PORTE = 0xFF;
#endif
#ifdef PORTE
    PORTF = 0xFF;
#endif
}
*/


#ifdef PROTOCOL_VUSB
static void disable_vusb(void)
{
    // disable interrupt & disconnect to prevent host from enumerating
    USB_INTR_ENABLE &= ~(1 << USB_INTR_ENABLE_BIT);
    usbDeviceDisconnect();
}

static void enable_vusb(void)
{
    USB_INTR_ENABLE |= (1 << USB_INTR_ENABLE_BIT);
    usbDeviceConnect();
}

static void init_vusb(void)
{
    uint8_t i = 0;

    usbInit();
    disable_vusb();
    /* fake USB disconnect for > 250 ms */
    while(--i){
        _delay_ms(1);
    }
    enable_vusb();
}
#endif

void change_driver(host_driver_t *driver)
{
    /*
    host_clear_keyboard_report();
    host_swap_keyboard_report();
    host_clear_keyboard_report();
    host_send_keyboard_report();
    */
    clear_keyboard();
    _delay_ms(1000);
    host_set_driver(driver);
}


static bool sleeping = false;
static bool insomniac = false;   // TODO: should be false for power saving
static uint16_t last_timer = 0;

int main(void)
{
    MCUSR = 0;
    clock_prescale_set(clock_div_1);
    WD_SET(WD_OFF);

    // power saving: the result is worse than nothing... why?
    //pullup_pins();
    //set_prr();

#ifdef PROTOCOL_VUSB
    disable_vusb();
#endif
    uart_init(115200);
    keyboard_init();
    print("\nSend BREAK for UART Console Commands.\n");

    // TODO: move to iWRAP/suart file
    print("suart init\n");
    // suart init
    // PC4: Tx Output IDLE(Hi)
    PORTC |= (1<<4);
    DDRC  |= (1<<4);
    // PC5: Rx Input(pull-up)
    PORTC |= (1<<5);
    DDRC  &= ~(1<<5);
    // suart receive interrut(PC5/PCINT13)
    PCMSK1 = 0b00100000;
    PCICR  = 0b00000010;

    host_set_driver(iwrap_driver());

    print("iwrap_init()\n");
    iwrap_init();
    iwrap_call();

    last_timer = timer_read();
    while (true) {
#ifdef PROTOCOL_VUSB
        if (host_get_driver() == vusb_driver())
            usbPoll();
#endif
        keyboard_task();
#ifdef PROTOCOL_VUSB
        if (host_get_driver() == vusb_driver())
            vusb_transfer_keyboard();
#endif
        // TODO: depricated
        if (matrix_is_modified() || console()) {
            last_timer = timer_read();
            sleeping = false;
        } else if (!sleeping && timer_elapsed(last_timer) > 4000) {
            sleeping = true;
            iwrap_check_connection();
        }

        // TODO: suspend.h
        if (host_get_driver() == iwrap_driver()) {
            if (sleeping && !insomniac) {
                _delay_ms(1);   // wait for UART to send
                iwrap_sleep();
                sleep(WDTO_60MS);
            }
        }
    }
}

static void sleep(uint8_t term)
{
    WD_SET(WD_IRQ, term);

    cli();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_bod_disable();
    sei();
    sleep_cpu();
    sleep_disable();

    WD_SET(WD_OFF);
}

static bool console(void)
{
        // Send to Bluetoot module WT12
        static bool breaked = false;
        if (!uart_available())
            return false;
        else {
            uint8_t c;
            c = uart_getchar();
            uart_putchar(c);
            switch (c) {
                case 0x00: // BREAK signal
                    if (!breaked) {
                        print("break(? for help): ");
                        breaked = true;
                    }
                    break;
                case '\r':
                    uart_putchar('\n');
                    iwrap_buf_send();
                    break;
                case '\b':
                    iwrap_buf_del();
                    break;
                default:
                    if (breaked) {
                        print("\n");
                        console_command(c);
                        breaked = false;
                    } else {
                        iwrap_buf_add(c);
                    }
                    break;
            }
            return true;
        }
}

bool command_extra(uint8_t code)
{
    return console_command(key2asc(code));
}

static bool console_command(uint8_t c)
{
    switch (c) {
        case 'h':
        case '?':
            print("\nCommands for Bluetooth(WT12/iWRAP):\n");
            print("r: reset. software reset by watchdog\n");
            print("i: insomniac. prevent KB from sleeping\n");
            print("c: iwrap_call. CALL for BT connection.\n");
#ifdef PROTOCOL_VUSB
            print("u: USB mode. switch to USB.\n");
            print("w: BT mode. switch to Bluetooth.\n");
#endif
            print("k: kill first connection.\n");
            print("Del: unpair first pairing.\n");
            print("\n");
            return 0;
        case 'r':
            print("reset\n");
            WD_AVR_RESET();
            return 1;
        case 'i':
            insomniac = !insomniac;
            if (insomniac)
                print("insomniac\n");
            else
                print("not insomniac\n");
            return 1;
        case 'c':
            print("iwrap_call()\n");
            iwrap_call();
            return 1;
#ifdef PROTOCOL_VUSB
        case 'u':
            print("USB mode\n");
            init_vusb();
            change_driver(vusb_driver());
            //iwrap_kill();
            //iwrap_sleep();
            // disable suart receive interrut(PC5/PCINT13)
            PCMSK1 &= ~(0b00100000);
            PCICR  &= ~(0b00000010);
            return 1;
        case 'w':
            print("iWRAP mode\n");
            change_driver(iwrap_driver());
            disable_vusb();
            // enable suart receive interrut(PC5/PCINT13)
            PCMSK1 |= 0b00100000;
            PCICR  |= 0b00000010;
            return 1;
#endif
        case 'k':
            print("kill\n");
            iwrap_kill();
            return 1;
        case 0x7F:  // DELETE
            print("unpair\n");
            iwrap_unpair();
            return 1;
    }
    return 0;
}

// convert keycode into ascii charactor
static uint8_t key2asc(uint8_t key)
{
    switch (key) {
        case KC_A: return 'a';
        case KC_B: return 'b';
        case KC_C: return 'c';
        case KC_D: return 'd';
        case KC_E: return 'e';
        case KC_F: return 'f';
        case KC_G: return 'g';
        case KC_H: return 'h';
        case KC_I: return 'i';
        case KC_J: return 'j';
        case KC_K: return 'k';
        case KC_L: return 'l';
        case KC_M: return 'm';
        case KC_N: return 'n';
        case KC_O: return 'o';
        case KC_P: return 'p';
        case KC_Q: return 'q';
        case KC_R: return 'r';
        case KC_S: return 's';
        case KC_T: return 't';
        case KC_U: return 'u';
        case KC_V: return 'v';
        case KC_W: return 'w';
        case KC_X: return 'x';
        case KC_Y: return 'y';
        case KC_Z: return 'z';
        case KC_1: return '1';
        case KC_2: return '2';
        case KC_3: return '3';
        case KC_4: return '4';
        case KC_5: return '5';
        case KC_6: return '6';
        case KC_7: return '7';
        case KC_8: return '8';
        case KC_9: return '9';
        case KC_0: return '0';
        case KC_ENTER: return '\n';
        case KC_ESCAPE: return 0x1B;
        case KC_BSPACE: return '\b';
        case KC_TAB: return '\t';
        case KC_SPACE: return ' ';
        case KC_MINUS: return '-';
        case KC_EQUAL: return '=';
        case KC_LBRACKET: return '[';
        case KC_RBRACKET: return ']';
        case KC_BSLASH: return '\\';
        case KC_NONUS_HASH: return '\\';
        case KC_SCOLON: return ';';
        case KC_QUOTE: return '\'';
        case KC_GRAVE: return '`';
        case KC_COMMA: return ',';
        case KC_DOT: return '.';
        case KC_SLASH: return '/';
        default: return 0x00;
    }
}
