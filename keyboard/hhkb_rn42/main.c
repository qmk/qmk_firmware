#include <avr/io.h>
#include <avr/power.h>
#include <avr/wdt.h>
#include "lufa.h"
#include "print.h"
#include "sendchar.h"
#include "rn42.h"
#include "serial.h"
#include "keyboard.h"
#include "command.h"
#include "keycode.h"
#include "action.h"
#include "action_util.h"
#include "wait.h"


bool config_mode = false;

static void SetupHardware(void)
{
    /* Disable watchdog if enabled by bootloader/fuses */
    MCUSR &= ~(1 << WDRF);
    wdt_disable();

    /* Disable clock division */
    clock_prescale_set(clock_div_1);

    // Leonardo needs. Without this USB device is not recognized.
    USB_Disable();

    USB_Init();

    // for Console_Task
    USB_Device_EnableSOFEvents();
    print_set_sendchar(sendchar);
}

static bool force_usb = false;
int main(void)  __attribute__ ((weak));
int main(void)
{
    SetupHardware();
    sei();

    /* wait for USB startup to get ready for debug output */
    uint8_t timeout = 255;  // timeout when USB is not available(Bluetooth)
    while (timeout-- && USB_DeviceState != DEVICE_STATE_Configured) {
        wait_ms(4);
#if defined(INTERRUPT_CONTROL_ENDPOINT)
        ;
#else
        USB_USBTask();
#endif
    }
    print("USB configured.\n");

    rn42_init();
    print("RN-42 init\n");

    /* init modules */
    keyboard_init();

    if (rn42_ready()) {
        host_set_driver(&rn42_driver);
    } else {
        host_set_driver(&lufa_driver);
    }

#ifdef SLEEP_LED_ENABLE
    sleep_led_init();
#endif

    print("Keyboard start.\n");
    while (1) {
/*
        while (USB_DeviceState == DEVICE_STATE_Suspended) {
            suspend_power_down();
            if (USB_Device_RemoteWakeupEnabled && suspend_wakeup_condition()) {
                    USB_Device_SendRemoteWakeup();
            }
        }
*/

        keyboard_task();

#if !defined(INTERRUPT_CONTROL_ENDPOINT)
        USB_USBTask();
#endif

        int16_t c;
        if (config_mode) {
            while ((c = serial_recv2()) != -1) xprintf("%c", c);
        } else {
            while ((c = serial_recv2()) != -1) {
                // LED Out report: 0xFE, 0x02, 0x01, <leds>
                // To get the report over UART set bit3 with SH, command.
                static enum {LED_INIT, LED_FE, LED_02, LED_01} state = LED_INIT;
                xprintf("%X\n", c);
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
                        // TODO: move to rn42.c and make accessible with keyboard_leds()
                        xprintf("LED status: %X\n", c);
                        state = LED_INIT;
                        break;
                    default:
                        state = LED_INIT;
                }
            }
        }

        /* Bluetooth mode when ready */
        if (!config_mode && !force_usb) {
            if (rn42_ready() && host_get_driver() != &rn42_driver) {
                clear_keyboard();
                host_set_driver(&rn42_driver);
            } else if (!rn42_ready() && host_get_driver() != &lufa_driver) {
                clear_keyboard();
                host_set_driver(&lufa_driver);
            }
        }
    }
}

static bool local_echo = false;
bool command_extra(uint8_t code)
{
    static host_driver_t *prev_driver = &rn42_driver;
    switch (code) {
        case KC_H:
        case KC_SLASH: /* ? */
            print("\n\n----- Bluetooth RN-42 Help -----\n");
            print("w:   toggle RN-42 config mode(enter/exit)\n");
            print("l:   toggle print module output(local echo)\n");
            print("a:   Bluetooth auto connect\n");
            print("del: Bluetooth disconnect\n");
            print("i:   info\n");

            if (config_mode) {
                return true;
            } else {
                print("u:   force USB mode\n");
                return false;   // to display default command help
            }
        case KC_W:
            if (!config_mode) {
                print("\nEnter RN-42 config mode\n");
                print("type $$$ to enter RN-42 command mode\n");
                print("type Delete to disconnect Bluetooth connection\n");
                command_state = CONSOLE;
                config_mode = true;
                prev_driver = host_get_driver();
                clear_keyboard();
                host_set_driver(&rn42_config_driver);
            } else {
                print("\nExit RN-42 config mode\n");
                command_state = ONESHOT;
                config_mode = false;
                clear_keyboard();
                host_set_driver(prev_driver);
            }
            return true;
        case KC_L:
            if (local_echo) {
                print("local echo off\n");
                local_echo = false;
            } else {
                print("local echo on\n");
                local_echo = true;
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
        case KC_A:
            print("auto connect\n");
            rn42_autoconnect();
            return true;
        case KC_DELETE:
            print("disconnect\n");
            rn42_disconnect();
            //rn42_putc('\0');    // see 5.3.4.4 DISCONNECT KEY of User's Guide
            return true;
        case KC_I:
            print("\nRN-42 info\n");
            xprintf("protocol: %s\n", (host_get_driver() == &rn42_driver) ? "RN-42" : "LUFA");
            xprintf("force_usb: %X\n", force_usb);
            xprintf("rn42_ready(): %X\n", rn42_ready());
            xprintf("config_mode: %X\n", config_mode);
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
            if (local_echo) xprintf("%c", code2asc(code));
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
