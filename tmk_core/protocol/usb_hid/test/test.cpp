#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <util/delay.h>
#include <Arduino.h>

// USB HID host
#include "Usb.h"
#include "hid.h"
#include "hidboot.h"
#include "parser.h"

// LUFA
#include "lufa.h"

#include "debug.h"

#include "leonardo_led.h"


static USB     usb_host;
static HIDBoot<HID_PROTOCOL_KEYBOARD>    kbd(&usb_host);
static KBDReportParser kbd_parser;

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
}

static void HID_setup()
{
    // Arduino Timer startup: wiring.c
    init();

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

    print_enable = true;
    debug_enable = true;
    debug_matrix = true;
    debug_keyboard = true;
    debug_mouse = true;

    LUFA_setup();
    sei();

    // wait for startup of sendchar routine
    while (USB_DeviceState != DEVICE_STATE_Configured) ;
    if (debug_enable) {
        _delay_ms(1000);
    }

    HID_setup();
    
    debug("init: done\n");
    for (;;) {
        usb_host.Task();

#if !defined(INTERRUPT_CONTROL_ENDPOINT)
        // LUFA Task for control request
        USB_USBTask();
#endif
    }
        
    return 0;
}
