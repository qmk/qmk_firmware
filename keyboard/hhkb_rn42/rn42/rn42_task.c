#include <stdint.h>
#include "keycode.h"
#include "serial.h"
#include "host.h"
#include "action.h"
#include "action_util.h"
#include "lufa.h"
#include "rn42_task.h"
#include "print.h"
#include "debug.h"
#include "timer.h"
#include "command.h"
#include "battery.h"

static bool config_mode = false;
static bool force_usb = false;

static void status_led(bool on)
{
    if (on) {
        DDRE  |=  (1<<6);
        PORTE &= ~(1<<6);
    } else {
        DDRE  |=  (1<<6);
        PORTE |=  (1<<6);
    }
}

void rn42_task_init(void)
{
    battery_init();
}

void rn42_task(void)
{
    int16_t c;
    if (config_mode) {
        // Config mode: print output from RN-42
        while ((c = serial_recv2()) != -1) {
            // without flow control it'll fail to receive data when flooded
            xprintf("%c", c);
        }
    } else {
        // Raw mode: interpret output report of LED state
        while ((c = serial_recv2()) != -1) {
            // LED Out report: 0xFE, 0x02, 0x01, <leds>
            // To get the report over UART set bit3 with SH, command.
            static enum {LED_INIT, LED_FE, LED_02, LED_01} state = LED_INIT;
            switch (state) {
                case LED_INIT:
                    if (c == 0xFE) state = LED_FE;
                    else           state = LED_INIT;
                    break;
                case LED_FE:
                    if (c == 0x02) state = LED_02;
                    else           state = LED_INIT;
                    break;
                case LED_02:
                    if (c == 0x01) state = LED_01;
                    else           state = LED_INIT;
                    break;
                case LED_01:
                    dprintf("LED status: %02X\n", c);
                    rn42_set_leds(c);
                    state = LED_INIT;
                    break;
                default:
                    state = LED_INIT;
            }
        }
    }

    /* Bluetooth mode when ready */
    if (!config_mode && !force_usb) {
        if (!rn42_rts() && host_get_driver() != &rn42_driver) {
            clear_keyboard();
            host_set_driver(&rn42_driver);
        } else if (rn42_rts() && host_get_driver() != &lufa_driver) {
            clear_keyboard();
            host_set_driver(&lufa_driver);
        }
    }


    static uint16_t prev_timer = 0;
    uint16_t e = timer_elapsed(prev_timer);
    if (e > 1000) {
        /* every second */
        prev_timer += e/1000*1000;

        /* Low voltage alert */
        uint8_t bs = battery_status();
        if (bs == LOW_VOLTAGE) {
            battery_led(LED_ON);
        } else {
            battery_led(LED_CHARGER);
        }

        static uint8_t prev_status = UNKNOWN;
        if (bs != prev_status) {
            prev_status = bs;
            switch (bs) {
                case FULL_CHARGED:  xprintf("FULL_CHARGED\n"); break;
                case CHARGING:      xprintf("CHARGING\n"); break;
                case DISCHARGING:   xprintf("DISCHARGING\n"); break;
                case LOW_VOLTAGE:   xprintf("LOW_VOLTAGE\n"); break;
                default:            xprintf("UNKNOWN STATUS\n"); break;
            };
        }

        /* every minute */
        uint32_t t = timer_read32()/1000;
        if (t%60 == 0) {
            uint16_t v = battery_voltage();
            uint8_t h = t/3600;
            uint8_t m = t%3600/60;
            uint8_t s = t%60;
            xprintf("%02u:%02u:%02u\t%umV\n", h, m, s, v);
            /* TODO: xprintf doesn't work for this.
            xprintf("%02u:%02u:%02u\t%umV\n", (t/3600), (t%3600/60), (t%60), v);
            */
        }
    }


    /* Connection monitor */
    if (rn42_linked()) {
        status_led(true);
    } else {
        status_led(false);
    }
}



/******************************************************************************
 * Command
 ******************************************************************************/
bool command_extra(uint8_t code)
{
    uint32_t t;
    uint16_t b;
    static host_driver_t *prev_driver = &rn42_driver;
    switch (code) {
        case KC_H:
        case KC_SLASH: /* ? */
            print("\n\n----- Bluetooth RN-42 Help -----\n");
            print("Del: enter/exit config mode(auto_connect/disconnect)\n");
            print("i:   RN-42 info\n");
            print("b:   battery voltage\n");

            if (config_mode) {
                return true;
            } else {
                print("u:   Force USB mode\n");
                return false;   // to display default command help
            }
        case KC_DELETE:
            if (rn42_autoconnecting()) {
                prev_driver = host_get_driver();
                clear_keyboard();
                _delay_ms(500);
                host_set_driver(&rn42_config_driver);   // null driver; not to send a key to host
                rn42_disconnect();
                print("\nRN-42: disconnect\n");
                print("Enter config mode\n");
                print("type $$$ to start and + for local echo\n");
                command_state = CONSOLE;
                config_mode = true;
            } else {
                rn42_autoconnect();
                print("\nRN-42: auto_connect\n");
                print("Exit config mode\n");
                command_state = ONESHOT;
                config_mode = false;
                //clear_keyboard();
                host_set_driver(prev_driver);
            }
            return true;
        case KC_U:
            if (config_mode) return false;
            if (force_usb) {
                print("Auto mode\n");
                force_usb = false;
            } else {
                print("USB mode\n");
                force_usb = true;
                clear_keyboard();
                host_set_driver(&lufa_driver);
            }
            return true;
        case KC_I:
            print("\n----- RN-42 info -----\n");
            xprintf("protocol: %s\n", (host_get_driver() == &rn42_driver) ? "RN-42" : "LUFA");
            xprintf("force_usb: %X\n", force_usb);
            xprintf("rn42_autoconnecting(): %X\n", rn42_autoconnecting());
            xprintf("rn42_linked(): %X\n", rn42_linked());
            xprintf("rn42_rts(): %X\n", rn42_rts());
            xprintf("config_mode: %X\n", config_mode);
            xprintf("VBUS: %X\n", USBSTA&(1<<VBUS));
            xprintf("battery_charging: %X\n", battery_charging());
            xprintf("battery_status: %X\n", battery_status());
            return true;
        case KC_B:
            // battery monitor
            t = timer_read32()/1000;
            b = battery_voltage();
            xprintf("BAT: %umV\t", b);
            xprintf("%02u:",   t/3600);
            xprintf("%02u:",   t%3600/60);
            xprintf("%02u\n",  t%60);
            return true;
        default:
            if (config_mode)
                return true;
            else
                return false;   // exec default command
    }
    return true;
}

static uint8_t code2asc(uint8_t code);
bool command_console_extra(uint8_t code)
{
    switch (code) {
        default:
            rn42_putc(code2asc(code));
            return true;
    }
    return false;
}

// convert keycode into ascii charactor
static uint8_t code2asc(uint8_t code)
{
    bool shifted = (get_mods() & (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))) ? true : false;
    switch (code) {
        case KC_A: return (shifted ? 'A' : 'a');
        case KC_B: return (shifted ? 'B' : 'b');
        case KC_C: return (shifted ? 'C' : 'c');
        case KC_D: return (shifted ? 'D' : 'd');
        case KC_E: return (shifted ? 'E' : 'e');
        case KC_F: return (shifted ? 'F' : 'f');
        case KC_G: return (shifted ? 'G' : 'g');
        case KC_H: return (shifted ? 'H' : 'h');
        case KC_I: return (shifted ? 'I' : 'i');
        case KC_J: return (shifted ? 'J' : 'j');
        case KC_K: return (shifted ? 'K' : 'k');
        case KC_L: return (shifted ? 'L' : 'l');
        case KC_M: return (shifted ? 'M' : 'm');
        case KC_N: return (shifted ? 'N' : 'n');
        case KC_O: return (shifted ? 'O' : 'o');
        case KC_P: return (shifted ? 'P' : 'p');
        case KC_Q: return (shifted ? 'Q' : 'q');
        case KC_R: return (shifted ? 'R' : 'r');
        case KC_S: return (shifted ? 'S' : 's');
        case KC_T: return (shifted ? 'T' : 't');
        case KC_U: return (shifted ? 'U' : 'u');
        case KC_V: return (shifted ? 'V' : 'v');
        case KC_W: return (shifted ? 'W' : 'w');
        case KC_X: return (shifted ? 'X' : 'x');
        case KC_Y: return (shifted ? 'Y' : 'y');
        case KC_Z: return (shifted ? 'Z' : 'z');
        case KC_1: return (shifted ? '!' : '1');
        case KC_2: return (shifted ? '@' : '2');
        case KC_3: return (shifted ? '#' : '3');
        case KC_4: return (shifted ? '$' : '4');
        case KC_5: return (shifted ? '%' : '5');
        case KC_6: return (shifted ? '^' : '6');
        case KC_7: return (shifted ? '&' : '7');
        case KC_8: return (shifted ? '*' : '8');
        case KC_9: return (shifted ? '(' : '9');
        case KC_0: return (shifted ? ')' : '0');
        case KC_ENTER: return '\n';
        case KC_ESCAPE: return 0x1B;
        case KC_BSPACE: return '\b';
        case KC_TAB: return '\t';
        case KC_SPACE: return ' ';
        case KC_MINUS: return (shifted ? '_' : '-');
        case KC_EQUAL: return (shifted ? '+' : '=');
        case KC_LBRACKET: return (shifted ? '{' : '[');
        case KC_RBRACKET: return (shifted ? '}' : ']');
        case KC_BSLASH: return (shifted ? '|' : '\\');
        case KC_NONUS_HASH: return (shifted ? '|' : '\\');
        case KC_SCOLON: return (shifted ? ':' : ';');
        case KC_QUOTE: return (shifted ? '"' : '\'');
        case KC_GRAVE: return (shifted ? '~' : '`');
        case KC_COMMA: return (shifted ? '<' : ',');
        case KC_DOT: return (shifted ? '>' : '.');
        case KC_SLASH: return (shifted ? '?' : '/');
        case KC_DELETE: return '\0';    // Delete to disconnect
        default: return ' ';
    }
}
