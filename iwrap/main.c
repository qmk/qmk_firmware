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
#include "iwrap.h"
#ifdef HOST_VUSB
#   include "vusb.h"
#   include "usbdrv.h"
#endif
#include "uart.h"
#include "suart.h"
#include "timer.h"
#include "debug.h"
#include "usb_keycodes.h"
#include "command.h"


static void sleep(uint8_t term);
static bool console(void);
static uint8_t console_command(uint8_t c);
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


#ifdef HOST_VUSB
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
    host_clear_keyboard_report();
    host_swap_keyboard_report();
    host_clear_keyboard_report();
    host_send_keyboard_report();
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

    print_enable = true;
    debug_enable = false;

#ifdef HOST_VUSB
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
#ifdef HOST_VUSB
        if (host_get_driver() == vusb_driver())
            usbPoll();
#endif
        keyboard_proc();
#ifdef HOST_VUSB
        if (host_get_driver() == vusb_driver())
            vusb_transfer_keyboard();
#endif
        if (matrix_is_modified() || console()) {
            last_timer = timer_read();
            sleeping = false;
        } else if (!sleeping && timer_elapsed(last_timer) > 4000) {
            sleeping = true;
            iwrap_check_connection();
        }

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

ISR(WDT_vect)
{
    // wake up
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

uint8_t command_extra()
{
    return console_command(key2asc(host_get_first_key()));
}

static uint8_t console_command(uint8_t c)
{
    switch (c) {
        case 'h':
        case '?':
            print("\nCommands for Bluetooth(WT12/iWRAP):\n");
            print("r: reset. software reset by watchdog\n");
            print("i: insomniac. prevent KB from sleeping\n");
            print("c: iwrap_call. CALL for BT connection.\n");
#ifdef HOST_VUSB
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
#ifdef HOST_VUSB
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
        case KB_A: return 'a';
        case KB_B: return 'b';
        case KB_C: return 'c';
        case KB_D: return 'd';
        case KB_E: return 'e';
        case KB_F: return 'f';
        case KB_G: return 'g';
        case KB_H: return 'h';
        case KB_I: return 'i';
        case KB_J: return 'j';
        case KB_K: return 'k';
        case KB_L: return 'l';
        case KB_M: return 'm';
        case KB_N: return 'n';
        case KB_O: return 'o';
        case KB_P: return 'p';
        case KB_Q: return 'q';
        case KB_R: return 'r';
        case KB_S: return 's';
        case KB_T: return 't';
        case KB_U: return 'u';
        case KB_V: return 'v';
        case KB_W: return 'w';
        case KB_X: return 'x';
        case KB_Y: return 'y';
        case KB_Z: return 'z';
        case KB_1: return '1';
        case KB_2: return '2';
        case KB_3: return '3';
        case KB_4: return '4';
        case KB_5: return '5';
        case KB_6: return '6';
        case KB_7: return '7';
        case KB_8: return '8';
        case KB_9: return '9';
        case KB_0: return '0';
        case KB_ENTER: return '\n';
        case KB_ESCAPE: return 0x1B;
        case KB_BSPACE: return '\b';
        case KB_TAB: return '\t';
        case KB_SPACE: return ' ';
        case KB_MINUS: return '-';
        case KB_EQUAL: return '=';
        case KB_LBRACKET: return '[';
        case KB_RBRACKET: return ']';
        case KB_BSLASH: return '\\';
        case KB_NONUS_HASH: return '\\';
        case KB_SCOLON: return ';';
        case KB_QUOTE: return '\'';
        case KB_GRAVE: return '`';
        case KB_COMMA: return ',';
        case KB_DOT: return '.';
        case KB_SLASH: return '/';
        default: return 0x00;
    }
}
