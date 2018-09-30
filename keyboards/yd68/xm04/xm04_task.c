#include <stdint.h>
#include <string.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include "keycode.h"
//#include "serial.h"
#include "host.h"
#include "action.h"
#include "action_util.h"
#include "lufa.h"
#include "xm04_task.h"
#include "print.h"
#include "debug.h"
#include "timer.h"
#include "wait.h"
#include "command.h"
#include "bootloader.h"

bool force_usb = false;
#ifndef NO_BT_STATUS_CHECK
//static bool host_connected = false;
//static bool usb_nkro_status = false;
static bool usb_connected = false;
//static uint16_t disconnect_timer = 0; 
//static uint8_t disconnect_s=0;
//static uint16_t check_timer = 0;
#endif
uint32_t kb_idle_timer = 0; 

bool dozing = false;
bool sleeping = false;
bool no_sleep = false;

void xm04_task_init(void)
{
    kb_idle_timer = timer_read32();
}

void xm04_task(void)
{

    /* Bluetooth mode when ready */
    if (!force_usb) {
        if (host_get_driver() != &xm04_driver) {
            clear_keyboard(); //Prevents stuck keys.
            print("Bluetooth\n");
#ifdef NKRO_ENABLE
            xmo04_nkro_last = keymap_config.nkro;
            keymap_config.nkro = false;
#endif
            host_set_driver(&xm04_driver);
        } else if (!usb_connected && (USB_DeviceState == DEVICE_STATE_Configured)) {
            force_usb = 1;
            usb_connected = 1;
        }
    } else {
        if (host_get_driver() != &lufa_driver) {
            usb_connected = 1;
            clear_keyboard();
            print("USB\n");
#ifdef NKRO_ENABLE
            keymap_config.nkro = xmo04_nkro_last;
#endif
            host_set_driver(&lufa_driver);
        } else if (USB_DeviceState != DEVICE_STATE_Configured) {
            force_usb = 0;
            usb_connected = 0;
        }            
    }
    if (!no_sleep && (!dozing && (timer_elapsed32(kb_idle_timer) > 30000))) {
        dozing = 1;
    }
    if (bt_powered() && (dozing && (timer_elapsed32(kb_idle_timer) > 3600000))) {
        sleeping = 1;
        turn_off_bt();
  }
}




bool command_extra(uint8_t code)
{
    switch (code) {
        case KC_B:
            clear_keyboard();
            print("\n\nbootloader... ");
            wait_ms(500);
            bootloader_jump(); // not return
            break;
        case KC_U:
            if (force_usb) {
                print("Auto mode\n");
                force_usb = false;
            } else {
                print("USB mode\n");
                force_usb = true;
            }
            return true;
        case KC_P:
            no_sleep ^= 1;
            return true;
        default:
                return false;   // yield to default command
    }
    return true;
}
