#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <util/delay.h>

// USB HID host
#include "Usb.h"
#include "hid.h"
#include "hidboot.h"
#include "parser.h"
#include "usbhub.h"

// LUFA
#include "lufa.h"

#include "timer.h"
#include "sendchar.h"
#include "debug.h"
#include "keyboard.h"

#include "leonardo_led.h"


static USB     usb_host;
static HIDBoot<HID_PROTOCOL_KEYBOARD>    kbd(&usb_host);
static KBDReportParser kbd_parser;
static USBHub hub1(&usb_host);  // one hub is enough for HHKB pro2
/* may be needed  for other device with more hub
static USBHub hub2(&usb_host);
static USBHub hub3(&usb_host);
static USBHub hub4(&usb_host);
static USBHub hub5(&usb_host);
static USBHub hub6(&usb_host);
static USBHub hub7(&usb_host);
*/

static void LUFA_setup(void)
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

static void HID_setup()
{
    if (usb_host.Init() == -1) {
        debug("HID init: failed\n");
        LED_TX_OFF;
    }
  
    _delay_ms(200);
      
    kbd.SetReportParser(0, (HIDReportParser*)&kbd_parser);
}

int main(void)
{
    // LED for debug
    LED_TX_INIT;
    LED_TX_ON;

    debug_enable = true;
/*
    debug_matrix = true;
    debug_keyboard = true;
    debug_mouse = true;
*/

    host_set_driver(&lufa_driver);
    keyboard_init();

    LUFA_setup();
    sei();

uint8_t ret;
    // wait for startup of sendchar routine
    while (USB_DeviceState != DEVICE_STATE_Configured) ;
    if (debug_enable) {
        _delay_ms(1000);
    }

    debug("init: start\n");
    HID_setup();
    
    debug("init: done\n");

uint16_t timer;
// to see loop pulse with oscillo scope
DDRF = (1<<7);
    for (;;) {
PORTF ^= (1<<7);
        keyboard_task();

timer = timer_read();
        usb_host.Task();
timer = timer_elapsed(timer);
if (timer > 100) {
    debug("host.Task: "); debug_hex16(timer);  debug("\n");
}

#if !defined(INTERRUPT_CONTROL_ENDPOINT)
        // LUFA Task for control request
        USB_USBTask();
#endif
    }
        
    return 0;
}
