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
#include <stdbool.h>
#include "wait.h"
#include "keycode.h"
#include "host.h"
#include "keymap.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "timer.h"
#include "keyboard.h"
#include "bootloader.h"
#include "action_layer.h"
#include "action_util.h"
#include "eeconfig.h"
#include "sleep_led.h"
#include "led.h"
#include "command.h"
#include "backlight.h"
#include "quantum.h"
#include "version.h"

#ifdef MOUSEKEY_ENABLE
#include "mousekey.h"
#endif

#ifdef PROTOCOL_PJRC
	#include "usb_keyboard.h"
		#ifdef EXTRAKEY_ENABLE
		#include "usb_extra.h"
	#endif
#endif

#ifdef PROTOCOL_VUSB
	#include "usbdrv.h"
#endif

#ifdef AUDIO_ENABLE
    #include "audio.h"
#endif /* AUDIO_ENABLE */


static bool command_common(uint8_t code);
static void command_common_help(void);
static void print_version(void);
static void print_status(void);
static bool command_console(uint8_t code);
static void command_console_help(void);
#ifdef MOUSEKEY_ENABLE
static bool mousekey_console(uint8_t code);
static void mousekey_console_help(void);
#endif

static void switch_default_layer(uint8_t layer);


command_state_t command_state = ONESHOT;


bool command_proc(uint8_t code)
{
    switch (command_state) {
        case ONESHOT:
            if (!IS_COMMAND())
                return false;
            return (command_extra(code) || command_common(code));
            break;
        case CONSOLE:
            if (IS_COMMAND())
                return (command_extra(code) || command_common(code));
            else
                return (command_console_extra(code) || command_console(code));
            break;
#ifdef MOUSEKEY_ENABLE
        case MOUSEKEY:
            mousekey_console(code);
            break;
#endif
        default:
            command_state = ONESHOT;
            return false;
    }
    return true;
}

/* TODO: Refactoring is needed. */
/* This allows to define extra commands. return false when not processed. */
bool command_extra(uint8_t code) __attribute__ ((weak));
bool command_extra(uint8_t code)
{
    (void)code;
    return false;
}

bool command_console_extra(uint8_t code) __attribute__ ((weak));
bool command_console_extra(uint8_t code)
{
    (void)code;
    return false;
}


/***********************************************************
 * Command common
 ***********************************************************/
static void command_common_help(void)
{
	print(                            "\n\t- Magic -\n"
		STR(MAGIC_KEY_DEBUG       ) ":	Debug Message Toggle\n"
		STR(MAGIC_KEY_DEBUG_MATRIX) ":	Matrix Debug Mode Toggle - Show keypresses in matrix grid\n"
		STR(MAGIC_KEY_DEBUG_KBD   ) ":	Keyboard Debug Toggle - Show keypress report\n"
		STR(MAGIC_KEY_DEBUG_MOUSE ) ":	Debug Mouse Toggle\n"
		STR(MAGIC_KEY_VERSION     ) ":	Version\n"
		STR(MAGIC_KEY_STATUS      ) ":	Status\n"
		STR(MAGIC_KEY_CONSOLE     ) ":	Activate Console Mode\n"

#if MAGIC_KEY_SWITCH_LAYER_WITH_CUSTOM
		STR(MAGIC_KEY_LAYER0      ) ":	Switch to Layer 0\n"
		STR(MAGIC_KEY_LAYER1      ) ":	Switch to Layer 1\n"
		STR(MAGIC_KEY_LAYER2      ) ":	Switch to Layer 2\n"
		STR(MAGIC_KEY_LAYER3      ) ":	Switch to Layer 3\n"
		STR(MAGIC_KEY_LAYER4      ) ":	Switch to Layer 4\n"
		STR(MAGIC_KEY_LAYER5      ) ":	Switch to Layer 5\n"
		STR(MAGIC_KEY_LAYER6      ) ":	Switch to Layer 6\n"
		STR(MAGIC_KEY_LAYER7      ) ":	Switch to Layer 7\n"
		STR(MAGIC_KEY_LAYER8      ) ":	Switch to Layer 8\n"
		STR(MAGIC_KEY_LAYER9      ) ":	Switch to Layer 9\n"
#endif

#if MAGIC_KEY_SWITCH_LAYER_WITH_FKEYS
		                            "F1-F10:	Switch to Layer 0-9 (F10 = L0)\n"
#endif

#if MAGIC_KEY_SWITCH_LAYER_WITH_NKEYS
		                            "0-9:	Switch to Layer 0-9\n"
#endif

		STR(MAGIC_KEY_LAYER0_ALT  ) ":	Switch to Layer 0 (alternate)\n"

		STR(MAGIC_KEY_BOOTLOADER    ) ":	Jump to Bootloader\n"
		STR(MAGIC_KEY_BOOTLOADER_ALT) ":	Jump to Bootloader (alternate)\n"

#ifdef KEYBOARD_LOCK_ENABLE
		STR(MAGIC_KEY_LOCK        ) ":	Lock Keyboard\n"
#endif

		STR(MAGIC_KEY_EEPROM      ) ":	Print EEPROM Settings\n"
		STR(MAGIC_KEY_EEPROM_CLEAR) ":	Clear EEPROM\n"

#ifdef NKRO_ENABLE
		STR(MAGIC_KEY_NKRO        ) ":	NKRO Toggle\n"
#endif

#ifdef SLEEP_LED_ENABLE
		STR(MAGIC_KEY_SLEEP_LED   ) ":	Sleep LED Test\n"
#endif
    );
}

static void print_version(void)
{
	// print version & information
    print("\n\t- Version -\n");
    print("DESC: " STR(DESCRIPTION) "\n");
    print("VID: " STR(VENDOR_ID) "(" STR(MANUFACTURER) ") "
          "PID: " STR(PRODUCT_ID) "(" STR(PRODUCT) ") "
          "VER: " STR(DEVICE_VER) "\n");
#ifdef SKIP_VERSION
    print("BUILD:  (" __DATE__ ")\n");
#else
    print("BUILD: " STR(QMK_VERSION) " (" __TIME__ " " __DATE__ ")\n");
#endif

    /* build options */
    print("OPTIONS:"

#ifdef PROTOCOL_PJRC
	    " PJRC"
#endif
#ifdef PROTOCOL_LUFA
	    " LUFA"
#endif
#ifdef PROTOCOL_VUSB
	    " VUSB"
#endif
#ifdef BOOTMAGIC_ENABLE
	    " BOOTMAGIC"
#endif
#ifdef MOUSEKEY_ENABLE
	    " MOUSEKEY"
#endif
#ifdef EXTRAKEY_ENABLE
	    " EXTRAKEY"
#endif
#ifdef CONSOLE_ENABLE
	    " CONSOLE"
#endif
#ifdef COMMAND_ENABLE
	    " COMMAND"
#endif
#ifdef NKRO_ENABLE
	    " NKRO"
#endif
#ifdef KEYMAP_SECTION_ENABLE
	    " KEYMAP_SECTION"
#endif

	    " " STR(BOOTLOADER_SIZE) "\n");

    print("GCC: " STR(__GNUC__) "." STR(__GNUC_MINOR__) "." STR(__GNUC_PATCHLEVEL__)
#if defined(__AVR__)
          " AVR-LIBC: " __AVR_LIBC_VERSION_STRING__
          " AVR_ARCH: avr" STR(__AVR_ARCH__)
#endif
		  "\n");

	return;
}

static void print_status(void)
{

    print("\n\t- Status -\n");

    print_val_hex8(host_keyboard_leds());
#ifndef PROTOCOL_VUSB
    // these aren't set on the V-USB protocol, so we just ignore them for now
    print_val_hex8(keyboard_protocol);
    print_val_hex8(keyboard_idle);
#endif
#ifdef NKRO_ENABLE
    print_val_hex8(keymap_config.nkro);
#endif
    print_val_hex32(timer_read32());

#ifdef PROTOCOL_PJRC
    print_val_hex8(UDCON);
    print_val_hex8(UDIEN);
    print_val_hex8(UDINT);
    print_val_hex8(usb_keyboard_leds);
    print_val_hex8(usb_keyboard_idle_count);
#endif

#ifdef PROTOCOL_PJRC
#   if USB_COUNT_SOF
    print_val_hex8(usbSofCount);
#   endif
#endif
	return;
}

static void print_eeconfig(void)
{

// Print these variables if NO_PRINT or USER_PRINT are not defined.
#if !defined(NO_PRINT) && !defined(USER_PRINT)

    print("default_layer: "); print_dec(eeconfig_read_default_layer()); print("\n");

    debug_config_t dc;
    dc.raw = eeconfig_read_debug();
    print("debug_config.raw: "); print_hex8(dc.raw); print("\n");
    print(".enable: "); print_dec(dc.enable); print("\n");
    print(".matrix: "); print_dec(dc.matrix); print("\n");
    print(".keyboard: "); print_dec(dc.keyboard); print("\n");
    print(".mouse: "); print_dec(dc.mouse); print("\n");

    keymap_config_t kc;
    kc.raw = eeconfig_read_keymap();
    print("keymap_config.raw: "); print_hex8(kc.raw); print("\n");
    print(".swap_control_capslock: "); print_dec(kc.swap_control_capslock); print("\n");
    print(".capslock_to_control: "); print_dec(kc.capslock_to_control); print("\n");
    print(".swap_lalt_lgui: "); print_dec(kc.swap_lalt_lgui); print("\n");
    print(".swap_ralt_rgui: "); print_dec(kc.swap_ralt_rgui); print("\n");
    print(".no_gui: "); print_dec(kc.no_gui); print("\n");
    print(".swap_grave_esc: "); print_dec(kc.swap_grave_esc); print("\n");
    print(".swap_backslash_backspace: "); print_dec(kc.swap_backslash_backspace); print("\n");
    print(".nkro: "); print_dec(kc.nkro); print("\n");

#ifdef BACKLIGHT_ENABLE
    backlight_config_t bc;
    bc.raw = eeconfig_read_backlight();
    print("backlight_config.raw: "); print_hex8(bc.raw); print("\n");
    print(".enable: "); print_dec(bc.enable); print("\n");
    print(".level: "); print_dec(bc.level); print("\n");
#endif /* BACKLIGHT_ENABLE */

#endif /* !NO_PRINT */

}

static bool command_common(uint8_t code)
{

#ifdef KEYBOARD_LOCK_ENABLE
    static host_driver_t *host_driver = 0;
#endif

    switch (code) {

#ifdef SLEEP_LED_ENABLE

		// test breathing sleep LED
        case MAGIC_KC(MAGIC_KEY_SLEEP_LED):
            print("Sleep LED Test\n");
            sleep_led_toggle();
            led_set(host_keyboard_leds());
            break;
#endif

		// print stored eeprom config
        case MAGIC_KC(MAGIC_KEY_EEPROM):
            print("eeconfig:\n");
            print_eeconfig();
            break;

		// clear eeprom
        case MAGIC_KC(MAGIC_KEY_EEPROM_CLEAR):
            print("Clearing EEPROM\n");
	    eeconfig_init();
            break;

#ifdef KEYBOARD_LOCK_ENABLE

		// lock/unlock keyboard
        case MAGIC_KC(MAGIC_KEY_LOCK):
            if (host_get_driver()) {
                host_driver = host_get_driver();
                clear_keyboard();
                host_set_driver(0);
                print("Locked.\n");
            } else {
                host_set_driver(host_driver);
                print("Unlocked.\n");
            }
            break;
#endif

		// print help
        case MAGIC_KC(MAGIC_KEY_HELP):
        case MAGIC_KC(MAGIC_KEY_HELP_ALT):
            command_common_help();
            break;

		// activate console
        case MAGIC_KC(MAGIC_KEY_CONSOLE):
            debug_matrix   = false;
            debug_keyboard = false;
            debug_mouse    = false;
            debug_enable   = false;
            command_console_help();
            print("C> ");
            command_state = CONSOLE;
            break;

        // jump to bootloader
        case MAGIC_KC(MAGIC_KEY_BOOTLOADER):
        case MAGIC_KC(MAGIC_KEY_BOOTLOADER_ALT):
            clear_keyboard(); // clear to prevent stuck keys
            print("\n\nJumping to bootloader... ");
            #ifdef AUDIO_ENABLE
	            stop_all_notes();
                shutdown_user();
            #else
	            wait_ms(1000);
            #endif
            bootloader_jump(); // not return
            break;

        // debug toggle
        case MAGIC_KC(MAGIC_KEY_DEBUG):
            debug_enable = !debug_enable;
            if (debug_enable) {
                print("\ndebug: on\n");
            } else {
                print("\ndebug: off\n");
                debug_matrix   = false;
                debug_keyboard = false;
                debug_mouse    = false;
            }
            break;

        // debug matrix toggle
        case MAGIC_KC(MAGIC_KEY_DEBUG_MATRIX):
            debug_matrix = !debug_matrix;
            if (debug_matrix) {
                print("\nmatrix: on\n");
                debug_enable = true;
            } else {
                print("\nmatrix: off\n");
            }
            break;

        // debug keyboard toggle
        case MAGIC_KC(MAGIC_KEY_DEBUG_KBD):
            debug_keyboard = !debug_keyboard;
            if (debug_keyboard) {
                print("\nkeyboard: on\n");
                debug_enable = true;
            } else {
                print("\nkeyboard: off\n");
            }
            break;

        // debug mouse toggle
        case MAGIC_KC(MAGIC_KEY_DEBUG_MOUSE):
            debug_mouse = !debug_mouse;
            if (debug_mouse) {
                print("\nmouse: on\n");
                debug_enable = true;
            } else {
				print("\nmouse: off\n");
            }
            break;

		// print version
        case MAGIC_KC(MAGIC_KEY_VERSION):
        	print_version();
		    break;

		// print status
		case MAGIC_KC(MAGIC_KEY_STATUS):
			print_status();
            break;

#ifdef NKRO_ENABLE

		// NKRO toggle
        case MAGIC_KC(MAGIC_KEY_NKRO):
            clear_keyboard(); // clear to prevent stuck keys
            keymap_config.nkro = !keymap_config.nkro;
            if (keymap_config.nkro) {
                print("NKRO: on\n");
            } else {
                print("NKRO: off\n");
            }
            break;
#endif

		// switch layers

		case MAGIC_KC(MAGIC_KEY_LAYER0_ALT):
            switch_default_layer(0);
            break;

#if MAGIC_KEY_SWITCH_LAYER_WITH_CUSTOM

		case MAGIC_KC(MAGIC_KEY_LAYER0):
            switch_default_layer(0);
            break;

		case MAGIC_KC(MAGIC_KEY_LAYER1):
            switch_default_layer(1);
            break;

		case MAGIC_KC(MAGIC_KEY_LAYER2):
            switch_default_layer(2);
            break;

		case MAGIC_KC(MAGIC_KEY_LAYER3):
            switch_default_layer(3);
            break;

		case MAGIC_KC(MAGIC_KEY_LAYER4):
            switch_default_layer(4);
            break;

		case MAGIC_KC(MAGIC_KEY_LAYER5):
            switch_default_layer(5);
            break;

		case MAGIC_KC(MAGIC_KEY_LAYER6):
            switch_default_layer(6);
            break;

		case MAGIC_KC(MAGIC_KEY_LAYER7):
            switch_default_layer(7);
            break;

		case MAGIC_KC(MAGIC_KEY_LAYER8):
            switch_default_layer(8);
            break;

		case MAGIC_KC(MAGIC_KEY_LAYER9):
            switch_default_layer(9);
            break;
#endif


#if MAGIC_KEY_SWITCH_LAYER_WITH_FKEYS

        case KC_F1 ... KC_F9:
            switch_default_layer((code - KC_F1) + 1);
            break;
        case KC_F10:
            switch_default_layer(0);
            break;
#endif

#if MAGIC_KEY_SWITCH_LAYER_WITH_NKEYS

        case KC_1 ... KC_9:
            switch_default_layer((code - KC_1) + 1);
            break;
        case KC_0:
            switch_default_layer(0);
            break;
#endif

        default:
            print("?");
            return false;
    }
    return true;
}


/***********************************************************
 * Command console
 ***********************************************************/
static void command_console_help(void)
{
    print("\n\t- Console -\n"
          "ESC/q:	quit\n"
#ifdef MOUSEKEY_ENABLE
          "m:	mousekey\n"
#endif
    );
}

static bool command_console(uint8_t code)
{
    switch (code) {
        case KC_H:
        case KC_SLASH: /* ? */
            command_console_help();
            break;
        case KC_Q:
        case KC_ESC:
            command_state = ONESHOT;
            return false;
#ifdef MOUSEKEY_ENABLE
        case KC_M:
            mousekey_console_help();
            print("M> ");
            command_state = MOUSEKEY;
            return true;
#endif
        default:
            print("?");
            return false;
    }
    print("C> ");
    return true;
}


#ifdef MOUSEKEY_ENABLE
/***********************************************************
 * Mousekey console
 ***********************************************************/
static uint8_t mousekey_param = 0;

static void mousekey_param_print(void)
{
// Print these variables if NO_PRINT or USER_PRINT are not defined.
#if !defined(NO_PRINT) && !defined(USER_PRINT)
    print("\n\t- Values -\n");
    print("1: delay(*10ms): "); pdec(mk_delay); print("\n");
    print("2: interval(ms): "); pdec(mk_interval); print("\n");
    print("3: max_speed: "); pdec(mk_max_speed); print("\n");
    print("4: time_to_max: "); pdec(mk_time_to_max); print("\n");
    print("5: wheel_max_speed: "); pdec(mk_wheel_max_speed); print("\n");
    print("6: wheel_time_to_max: "); pdec(mk_wheel_time_to_max); print("\n");
#endif /* !NO_PRINT */

}

//#define PRINT_SET_VAL(v)  print(#v " = "); print_dec(v); print("\n");
#define PRINT_SET_VAL(v)  xprintf(#v " = %d\n", (v))
static void mousekey_param_inc(uint8_t param, uint8_t inc)
{
    switch (param) {
        case 1:
            if (mk_delay + inc < UINT8_MAX)
                mk_delay += inc;
            else
                mk_delay = UINT8_MAX;
            PRINT_SET_VAL(mk_delay);
            break;
        case 2:
            if (mk_interval + inc < UINT8_MAX)
                mk_interval += inc;
            else
                mk_interval = UINT8_MAX;
            PRINT_SET_VAL(mk_interval);
            break;
        case 3:
            if (mk_max_speed + inc < UINT8_MAX)
                mk_max_speed += inc;
            else
                mk_max_speed = UINT8_MAX;
            PRINT_SET_VAL(mk_max_speed);
            break;
        case 4:
            if (mk_time_to_max + inc < UINT8_MAX)
                mk_time_to_max += inc;
            else
                mk_time_to_max = UINT8_MAX;
            PRINT_SET_VAL(mk_time_to_max);
            break;
        case 5:
            if (mk_wheel_max_speed + inc < UINT8_MAX)
                mk_wheel_max_speed += inc;
            else
                mk_wheel_max_speed = UINT8_MAX;
            PRINT_SET_VAL(mk_wheel_max_speed);
            break;
        case 6:
            if (mk_wheel_time_to_max + inc < UINT8_MAX)
                mk_wheel_time_to_max += inc;
            else
                mk_wheel_time_to_max = UINT8_MAX;
            PRINT_SET_VAL(mk_wheel_time_to_max);
            break;
    }
}

static void mousekey_param_dec(uint8_t param, uint8_t dec)
{
    switch (param) {
        case 1:
            if (mk_delay > dec)
                mk_delay -= dec;
            else
                mk_delay = 0;
            PRINT_SET_VAL(mk_delay);
            break;
        case 2:
            if (mk_interval > dec)
                mk_interval -= dec;
            else
                mk_interval = 0;
            PRINT_SET_VAL(mk_interval);
            break;
        case 3:
            if (mk_max_speed > dec)
                mk_max_speed -= dec;
            else
                mk_max_speed = 0;
            PRINT_SET_VAL(mk_max_speed);
            break;
        case 4:
            if (mk_time_to_max > dec)
                mk_time_to_max -= dec;
            else
                mk_time_to_max = 0;
            PRINT_SET_VAL(mk_time_to_max);
            break;
        case 5:
            if (mk_wheel_max_speed > dec)
                mk_wheel_max_speed -= dec;
            else
                mk_wheel_max_speed = 0;
            PRINT_SET_VAL(mk_wheel_max_speed);
            break;
        case 6:
            if (mk_wheel_time_to_max > dec)
                mk_wheel_time_to_max -= dec;
            else
                mk_wheel_time_to_max = 0;
            PRINT_SET_VAL(mk_wheel_time_to_max);
            break;
    }
}

static void mousekey_console_help(void)
{
    print("\n\t- Mousekey -\n"
          "ESC/q:	quit\n"
          "1:	delay(*10ms)\n"
          "2:	interval(ms)\n"
          "3:	max_speed\n"
          "4:	time_to_max\n"
          "5:	wheel_max_speed\n"
          "6:	wheel_time_to_max\n"
          "\n"
          "p:	print values\n"
          "d:	set defaults\n"
          "up:	+1\n"
          "down:	-1\n"
          "pgup:	+10\n"
          "pgdown:	-10\n"
          "\n"
          "speed = delta * max_speed * (repeat / time_to_max)\n");
    xprintf("where delta: cursor=%d, wheel=%d\n"
            "See http://en.wikipedia.org/wiki/Mouse_keys\n", MOUSEKEY_MOVE_DELTA,  MOUSEKEY_WHEEL_DELTA);
}

static bool mousekey_console(uint8_t code)
{
    switch (code) {
        case KC_H:
        case KC_SLASH: /* ? */
            mousekey_console_help();
            break;
        case KC_Q:
        case KC_ESC:
            if (mousekey_param) {
                mousekey_param = 0;
            } else {
                print("C> ");
                command_state = CONSOLE;
                return false;
            }
            break;
        case KC_P:
            mousekey_param_print();
            break;
        case KC_1:
        case KC_2:
        case KC_3:
        case KC_4:
        case KC_5:
        case KC_6:
            mousekey_param = numkey2num(code);
            break;
        case KC_UP:
            mousekey_param_inc(mousekey_param, 1);
            break;
        case KC_DOWN:
            mousekey_param_dec(mousekey_param, 1);
            break;
        case KC_PGUP:
            mousekey_param_inc(mousekey_param, 10);
            break;
        case KC_PGDN:
            mousekey_param_dec(mousekey_param, 10);
            break;
        case KC_D:
            mk_delay = MOUSEKEY_DELAY/10;
            mk_interval = MOUSEKEY_INTERVAL;
            mk_max_speed = MOUSEKEY_MAX_SPEED;
            mk_time_to_max = MOUSEKEY_TIME_TO_MAX;
            mk_wheel_max_speed = MOUSEKEY_WHEEL_MAX_SPEED;
            mk_wheel_time_to_max = MOUSEKEY_WHEEL_TIME_TO_MAX;
            print("set default\n");
            break;
        default:
            print("?");
            return false;
    }
    if (mousekey_param) {
        xprintf("M%d> ", mousekey_param);
    } else {
        print("M>" );
    }
    return true;
}
#endif


/***********************************************************
 * Utilities
 ***********************************************************/
uint8_t numkey2num(uint8_t code)
{
    switch (code) {
        case KC_1: return 1;
        case KC_2: return 2;
        case KC_3: return 3;
        case KC_4: return 4;
        case KC_5: return 5;
        case KC_6: return 6;
        case KC_7: return 7;
        case KC_8: return 8;
        case KC_9: return 9;
        case KC_0: return 0;
    }
    return 0;
}

static void switch_default_layer(uint8_t layer)
{
    xprintf("L%d\n", layer);
    default_layer_set(1UL<<layer);
    clear_keyboard();
}
