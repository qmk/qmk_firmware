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


/* LED ping configuration */
#define TMK_LED
//#define LEONARDO_LED
#if defined(TMK_LED)
// For TMK converter and Teensy
#define LED_TX_INIT    (DDRD  |=  (1<<6))
#define LED_TX_ON      (PORTD |=  (1<<6))
#define LED_TX_OFF     (PORTD &= ~(1<<6))
#define LED_TX_TOGGLE  (PORTD ^=  (1<<6))
#elif defined(LEONARDO_LED)
// For Leonardo(TX LED)
#define LED_TX_INIT    (DDRD  |=  (1<<5))
#define LED_TX_ON      (PORTD &= ~(1<<5))
#define LED_TX_OFF     (PORTD |=  (1<<5))
#define LED_TX_TOGGLE  (PORTD ^=  (1<<5))
#else
#define LED_TX_INIT
#define LED_TX_ON
#define LED_TX_OFF
#define LED_TX_TOGGLE
#endif


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

    host_set_driver(&lufa_driver);
    keyboard_init();

    LUFA_setup();
    HID_setup();
    /* NOTE: Don't insert time consuming job here.
     * It'll cause unclear initialization failure when DFU reset(worm start).
     */
    sei();

    // wait for startup of sendchar routine
    while (USB_DeviceState != DEVICE_STATE_Configured) ;
    if (debug_enable) {
        _delay_ms(1000);
    }

    debug("init: done\n");

uint16_t timer;
    for (;;) {
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
