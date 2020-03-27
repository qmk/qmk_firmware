#include <stdint.h>
#include <string.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
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
#include "wait.h"
#include "command.h"
#include "battery.h"
#include "keycode_config.h"

extern keymap_config_t keymap_config;

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
#ifdef NKRO_ENABLE
    rn42_nkro_last = keymap_config.nkro;
#endif
}

void rn42_task(void)
{
    int16_t c;
    // Raw mode: interpret output report of LED state
    while ((c = rn42_getc()) != -1) {
        // LED Out report: 0xFE, 0x02, 0x01, <leds>
        // To get the report over UART set bit3 with SH, command.
        static enum {LED_INIT, LED_FE, LED_02, LED_01} state = LED_INIT;
        switch (state) {
            case LED_INIT:
                if (c == 0xFE) state = LED_FE;
                else {
                    if (0x0 <= c && c <= 0x7f) xprintf("%c", c);
                    else xprintf(" %02X", c);
                }
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

    /* Switch between USB and Bluetooth */
    if (!config_mode) { // not switch while config mode
        if (!force_usb && !rn42_rts()) {
            if (host_get_driver() != &rn42_driver) {
                clear_keyboard();
#ifdef NKRO_ENABLE
                rn42_nkro_last = keymap_config.nkro;
                keymap_config.nkro = false;
#endif
                host_set_driver(&rn42_driver);
            }
        } else {
            if (host_get_driver() != &lufa_driver) {
                clear_keyboard();
#ifdef NKRO_ENABLE
                keymap_config.nkro = rn42_nkro_last;
#endif
                host_set_driver(&lufa_driver);
            }
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

        /* every minute */
        uint32_t t = timer_read32()/1000;
        if (t%60 == 0) {
            uint16_t v = battery_voltage();
            uint8_t h = t/3600;
            uint8_t m = t%3600/60;
            uint8_t s = t%60;
            dprintf("%02u:%02u:%02u\t%umV\n", h, m, s, v);
            /* TODO: xprintf doesn't work for this.
            xprintf("%02u:%02u:%02u\t%umV\n", (t/3600), (t%3600/60), (t%60), v);
            */
        }
    }


    /* Connection monitor */
    if (!rn42_rts() && rn42_linked()) {
        status_led(true);
    } else {
        status_led(false);
    }
}



/******************************************************************************
 * Command
 ******************************************************************************/
static host_driver_t *prev_driver = &rn42_driver;

static void enter_command_mode(void)
{
    prev_driver = host_get_driver();
    clear_keyboard();
    host_set_driver(&rn42_config_driver);   // null driver; not to send a key to host
    rn42_disconnect();
    while (rn42_linked()) ;

    print("Entering config mode ...\n");
    wait_ms(1100);          // need 1 sec
    SEND_COMMAND("$$$");
    wait_ms(600);           // need 1 sec
    rn42_print_response();
    const char *s = SEND_COMMAND("v\r\n");
    if (strncmp("v", s, 1) != 0) SEND_COMMAND("+\r\n"); // local echo on
}

static void exit_command_mode(void)
{
    print("Exiting config mode ...\n");
    SEND_COMMAND("---\r\n");    // exit

    rn42_autoconnect();
    clear_keyboard();
    host_set_driver(prev_driver);
}

static void init_rn42(void)
{
    // RN-42 configure
    if (!config_mode) enter_command_mode();
    SEND_COMMAND("SF,1\r\n");  // factory defaults
    SEND_COMMAND("S-,TmkBT\r\n");
    SEND_COMMAND("SS,Keyboard/Mouse\r\n");
    SEND_COMMAND("SM,4\r\n");  // auto connect(DTR)
    SEND_COMMAND("SW,8000\r\n");   // Sniff disable
    SEND_COMMAND("S~,6\r\n");   // HID profile
    SEND_COMMAND("SH,003C\r\n");   // combo device, out-report, 4-reconnect
    SEND_COMMAND("SY,FFF4\r\n");   // transmit power -12
    SEND_COMMAND("R,1\r\n");
    if (!config_mode) exit_command_mode();
}

#if 0
// Switching connections
// NOTE: Remote Address doesn't work in the way manual says.
// EEPROM address for link store
#define RN42_LINK0  (uint8_t *)128
#define RN42_LINK1  (uint8_t *)140
#define RN42_LINK2  (uint8_t *)152
#define RN42_LINK3  (uint8_t *)164
static void store_link(uint8_t *eeaddr)
{
    enter_command_mode();
    SEND_STR("GR\r\n"); // remote address
    const char *s = rn42_gets(500);
    if (strcmp("GR", s) == 0) s = rn42_gets(500);   // ignore local echo
    xprintf("%s(%d)\r\n", s, strlen(s));
    if (strlen(s) == 12) {
        for (int i = 0; i < 12; i++) {
            eeprom_write_byte(eeaddr+i, *(s+i));
            dprintf("%c ", *(s+i));
        }
        dprint("\r\n");
    }
    exit_command_mode();
}

static void restore_link(const uint8_t *eeaddr)
{
    enter_command_mode();
    SEND_COMMAND("SR,Z\r\n");   // remove remote address
    SEND_STR("SR,");            // set remote address from EEPROM
    for (int i = 0; i < 12; i++) {
        uint8_t c = eeprom_read_byte(eeaddr+i);
        rn42_putc(c);
        dprintf("%c ", c);
    }
    dprintf("\r\n");
    SEND_COMMAND("\r\n");
    SEND_COMMAND("R,1\r\n");    // reboot
    exit_command_mode();
}

static const char *get_link(uint8_t * eeaddr)
{
    static char s[13];
    for (int i = 0; i < 12; i++) {
        uint8_t c = eeprom_read_byte(eeaddr+i);
        s[i] = c;
    }
    s[12] = '\0';
    return s;
}
#endif

static void pairing(void)
{
    enter_command_mode();
    SEND_COMMAND("SR,Z\r\n");   // remove remote address
    SEND_COMMAND("R,1\r\n");    // reboot
    exit_command_mode();
}

bool command_extra(uint8_t code)
{
    uint32_t t;
    uint16_t b;
    switch (code) {
        case KC_H:
        case KC_SLASH: /* ? */
            print("\n\n----- Bluetooth RN-42 Help -----\n");
            print("i:       RN-42 info\n");
            print("b:       battery voltage\n");
            print("Del:     enter/exit RN-42 config mode\n");
            print("Slck:    RN-42 initialize\n");
#if 0
            print("1-4:     restore link\n");
            print("F1-F4:   store link\n");
#endif
            print("p:       pairing\n");

            if (config_mode) {
                return true;
            } else {
                print("u:       toggle Force USB mode\n");
                return false;   // to display default command help
            }
        case KC_P:
            pairing();
            return true;
#if 0
        /* Store link address to EEPROM */
        case KC_F1:
            store_link(RN42_LINK0);
            return true;
        case KC_F2:
            store_link(RN42_LINK1);
            return true;
        case KC_F3:
            store_link(RN42_LINK2);
            return true;
        case KC_F4:
            store_link(RN42_LINK3);
            return true;
        /* Restore link address to EEPROM */
        case KC_1:
            restore_link(RN42_LINK0);
            return true;
        case KC_2:
            restore_link(RN42_LINK1);
            return true;
        case KC_3:
            restore_link(RN42_LINK2);
            return true;
        case KC_4:
            restore_link(RN42_LINK3);
            return true;
#endif
        case KC_I:
            print("\n----- RN-42 info -----\n");
            xprintf("protocol: %s\n", (host_get_driver() == &rn42_driver) ? "RN-42" : "LUFA");
            xprintf("force_usb: %X\n", force_usb);
            xprintf("rn42: %s\n", rn42_rts() ? "OFF" : (rn42_linked() ? "CONN" : "ON"));
            xprintf("rn42_autoconnecting(): %X\n", rn42_autoconnecting());
            xprintf("config_mode: %X\n", config_mode);
            xprintf("USB State: %s\n",
                    (USB_DeviceState == DEVICE_STATE_Unattached) ? "Unattached" :
                    (USB_DeviceState == DEVICE_STATE_Powered) ? "Powered" :
                    (USB_DeviceState == DEVICE_STATE_Default) ? "Default" :
                    (USB_DeviceState == DEVICE_STATE_Addressed) ? "Addressed" :
                    (USB_DeviceState == DEVICE_STATE_Configured) ? "Configured" :
                    (USB_DeviceState == DEVICE_STATE_Suspended) ? "Suspended" : "?");
            xprintf("battery: ");
            switch (battery_status()) {
                case FULL_CHARGED:  xprintf("FULL"); break;
                case CHARGING:      xprintf("CHARG"); break;
                case DISCHARGING:   xprintf("DISCHG"); break;
                case LOW_VOLTAGE:   xprintf("LOW"); break;
                default:            xprintf("?"); break;
            };
            xprintf("\n");
            xprintf("RemoteWakeupEnabled: %X\n", USB_Device_RemoteWakeupEnabled);
            xprintf("VBUS: %X\n", USBSTA&(1<<VBUS));
            t = timer_read32()/1000;
            uint8_t d = t/3600/24;
            uint8_t h = t/3600;
            uint8_t m = t%3600/60;
            uint8_t s = t%60;
            xprintf("uptime: %02u %02u:%02u:%02u\n", d, h, m, s);
#if 0
            xprintf("LINK0: %s\r\n", get_link(RN42_LINK0));
            xprintf("LINK1: %s\r\n", get_link(RN42_LINK1));
            xprintf("LINK2: %s\r\n", get_link(RN42_LINK2));
            xprintf("LINK3: %s\r\n", get_link(RN42_LINK3));
#endif
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
        case KC_U:
            if (config_mode) return false;
            if (force_usb) {
                print("Auto mode\n");
                force_usb = false;
            } else {
                print("USB mode\n");
                force_usb = true;
            }
            return true;
        case KC_DELETE:
            /* RN-42 Command mode */
            if (rn42_autoconnecting()) {
                enter_command_mode();

                command_state = CONSOLE;
                config_mode = true;
            } else {
                exit_command_mode();

                command_state = ONESHOT;
                config_mode = false;
            }
            return true;
        case KC_SCROLLLOCK:
            init_rn42();
            return true;
#ifdef NKRO_ENABLE
        case KC_N:
            if (host_get_driver() != &lufa_driver) {
                // ignored unless USB mode
                return true;
            }
            return false;
#endif
        default:
            if (config_mode)
                return true;
            else
                return false;   // yield to default command
    }
    return true;
}

/*
 * RN-42 Command mode
 * sends charactors to the module
 */
static uint8_t code2asc(uint8_t code);
bool command_console_extra(uint8_t code)
{
    rn42_putc(code2asc(code));
    return true;
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
